#include "Facility.h"
#include <sstream>
// FacilityType Class
FacilityType::FacilityType(const string& name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score) 
: name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score)
{
}

const string& FacilityType::getName() const
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
    return category;
}

const string FacilityType::toString() const
{
    std::ostringstream s;
    s << "Facility name: " << name << "\n"
    << "Category: " << FacilityType::toString(category) << "\n"
    << "Price: " << std::to_string(price) << "\n" 
    << "Life quality score: " << std::to_string(lifeQuality_score) << "\n"
    << "Economy score: " << std::to_string(economy_score) << "\n" 
    << "Environment score: " << std::to_string(environment_score) << "\n";
    return s.str();
}

//=========================================================
// Facility Class
Facility::Facility(const string& name, const string& settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score) 
: FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price)
{
}

Facility::Facility(const FacilityType& type, const string& settlementName) 
: FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(type.getCost())
{
}

const string& Facility::getSettlementName() const
{
    return settlementName;
}

const int Facility::getTimeLeft() const
{
    return timeLeft;
}

FacilityStatus Facility::step()
{
    timeLeft--;
    if (timeLeft == 0)
    {
        status = (FacilityStatus::OPERATIONAL);
    }
    return status;
}

void Facility::setStatus(FacilityStatus status)
{
    this->status = status;
}

const FacilityStatus& Facility::getStatus() const
{
    return status;
}
    
const string Facility::toString() const
{
    std::ostringstream s;
    s << "Facility name: " << name << "\n"
    << "Settlement name: " << settlementName << "\n" 
    << "Category: " << FacilityType::toString(category) << "\n"
    << "Price: " << std::to_string(price) << "\n" 
    << "Life quality score: " << std::to_string(lifeQuality_score) << "\n"
    << "Economy score: " << std::to_string(economy_score) << "\n" 
    << "Environment score: " << std::to_string(environment_score) << "\n" 
    << "Construction status: " << Facility::toString(status) << "\n" 
    << "Remaining construction time: " << std::to_string(timeLeft) << "\n";
    return s.str();
}

const string FacilityType::toString(const FacilityCategory& category) const
{
    switch (category)
    {
        case FacilityCategory::ECONOMY:
            return "Economy";
        case FacilityCategory::ENVIRONMENT:
            return "Environment";
        case FacilityCategory::LIFE_QUALITY:
            return "Life quality";
    }
    return "";
}

const string Facility::toString(const FacilityStatus& status) const
{
    switch (status)
    {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            return "Under construction";
        case FacilityStatus::OPERATIONAL:
            return "Operational";
    }
    return "";
}
