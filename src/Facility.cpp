#include "Facility.h"

// FacilityType Class
FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score)
{}

const string &FacilityType::getName() const
{
    return name;
}

int FacilityType::getCost() const
{
    return price;
}

int FacilityType::getLifeQualityScore() const
{
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const
{
    return environment_score;
}

int FacilityType::getEconomyScore() const
{
    return economy_score;
}

FacilityCategory FacilityType::getCategory() const
{
    return FacilityCategory();
}


// Facility Class
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), settlementName(settlementName), timeLeft(price), status(FacilityStatus::UNDER_CONSTRUCTIONS)
{

}

Facility::Facility(const FacilityType &type, const string &settlementName): 
FacilityType(type), settlementName(settlementName), timeLeft(price), status(FacilityStatus::UNDER_CONSTRUCTIONS)
{
}

const string &Facility::getSettlementName() const
{
    return settlementName;
}

const int Facility::getTimeLeft() const
{
    // should check if time starts with price-1
    return timeLeft;
}

FacilityStatus Facility::step()
{
   timeLeft--;
   if (timeLeft==0){
    status = (FacilityStatus::OPERATIONAL);
   }
   return status;
}

void Facility::setStatus(FacilityStatus status)
{
    this->status = status;
}

const FacilityStatus &Facility::getStatus() const
{
    return status;
}

const string toString(FacilityCategory category)
{
    switch (category) {
        case FacilityCategory::ECONOMY:   return "Economy";
        case FacilityCategory::ENVIRONMENT: return "Environment";
        case FacilityCategory::LIFE_QUALITY:  return "Life quality";
    }
}

const string toString(FacilityStatus status)
{
switch (status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:   return "Under construction";
        case FacilityStatus::OPERATIONAL: return "Operational";
    }
}


const string Facility::toString() const
{
    return string("Facility name: " + name + "\n" +
                "Settlement name: " + settlementName + "\n" +
                "Category: " + ::toString(category) + "\n" +
                "Price: " + std::to_string(price) + "\n" +
                "Life quality score: " + std::to_string(lifeQuality_score) + "\n" +
                "Economy score: " + std::to_string(economy_score) + "\n" +
                "Environment score: " + std::to_string(environment_score) + "\n" +
                "Constraction status: " + ::toString(status) + "\n" +
                "Remaining constraction time: " + std::to_string(timeLeft) + "\n");
}