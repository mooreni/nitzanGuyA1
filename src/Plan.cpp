#include "Plan.h"
#include <sstream>

Plan::Plan(const int planId, const Settlement& settlement, SelectionPolicy* selectionPolicy, const vector<FacilityType>& facilityOptions):
plan_id(planId), settlement(&settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilities(), underConstruction(),
facilityOptions(facilityOptions), life_quality_score(0),economy_score(0),environment_score(0), 
numFacilitiesAtTime((static_cast<int>(settlement.getType()))+1)
{
}

const int Plan::getlifeQualityScore() const
{
    return life_quality_score;
}

const int Plan::getEconomyScore() const
{
    return economy_score;
}

const int Plan::getEnvironmentScore() const
{
    return environment_score;
}

void Plan::setSelectionPolicy(SelectionPolicy* selectionPolicy)
{
    delete this->selectionPolicy;
    this->selectionPolicy = selectionPolicy;
}

void Plan::step()
{
    if(status==PlanStatus::AVALIABLE){
        while (underConstruction.size()<numFacilitiesAtTime)
        {
            Facility* f = new Facility(selectionPolicy->selectFacility(facilityOptions),settlement->getName());
            addFacility(f);
        }
    }

    for(unsigned int i=0;i<underConstruction.size();){
        FacilityStatus s = underConstruction[i]->step();
        if(s==FacilityStatus::OPERATIONAL){
            addFacility(underConstruction[i]);
            life_quality_score+=underConstruction[i]->getLifeQualityScore();
            economy_score+=underConstruction[i]->getEconomyScore();
            environment_score+=underConstruction[i]->getEnvironmentScore();
            underConstruction.erase(underConstruction.begin()+i);
        }
        else{
            i++;
        }
    }
    
    if(underConstruction.size()<numFacilitiesAtTime)
    {
        status=PlanStatus::AVALIABLE;
    }
    else{
        status=PlanStatus::BUSY;
    }

}

void Plan::printStatus()
{
    std::cout << "The current status is: " << toString(status) << "\n";
}

const vector<Facility*>& Plan::getFacilities() const
{
    return facilities;
}

void Plan::addFacility(Facility* facility)
{
    if(facility->getStatus()==FacilityStatus::OPERATIONAL){
        facilities.push_back(facility);
    }
    else{
        underConstruction.push_back(facility);
    }
}

const string Plan::toString() const
{
    std::ostringstream s;
        s << "Plan Id: " << plan_id << "\n"
        << "Settlement name: " << settlement->getName() << "\n"
        << "Plan status: " << Plan::toString(status) << "\n"
        << "Selection policy: " << selectionPolicy->toString() << "\n"
        << "LifeQualityScore: " << life_quality_score << "\n"
        << "EconomyScore: " << economy_score << "\n"
        << "EnvironmentScore: " << environment_score << "\n"
        << Plan::toString(facilities) << "\n"
        << Plan::toString(underConstruction);

    return s.str();
}

const string Plan::toString(PlanStatus status) const
{
    switch (status)
    {
        case PlanStatus::AVALIABLE: return "Available";
        case PlanStatus::BUSY: return "Busy"; 
    }
    return "";
}

const string Plan::toString(vector<Facility*> facilities) const
{
 std::ostringstream s;

    for(unsigned int i = 0; i < facilities.size(); i++){
        if (i > 0) {
            s << "\n";
        }
        s << "FacilityName: " << facilities[i]->getName() << "\n"
        << "FacilityStatus: " << facilities[i]->toString(facilities[i]->getStatus());
    }
    return s.str();
}


//Rule of Five
//Destructor
Plan::~Plan()
{
    delete selectionPolicy;
    for(unsigned int i=0;i<facilities.size();i++){
        delete facilities[i];
    }
    for(unsigned int i=0;i<underConstruction.size();i++){
        delete underConstruction[i];
    }
}

//Copy Constructor
Plan::Plan(const Plan &other) : plan_id(other.plan_id), settlement(other.settlement), 
selectionPolicy(other.selectionPolicy->clone()), status(other.status), facilities(), underConstruction(),
facilityOptions(other.facilityOptions), life_quality_score(other.life_quality_score),
economy_score(other.economy_score),environment_score(other.environment_score), 
numFacilitiesAtTime((static_cast<int>(other.settlement->getType()))+1)
{
    for(unsigned int i=0;i<other.facilities.size();i++){
        facilities.push_back(new Facility(*other.facilities[i]));
    }
    for(unsigned int i=0;i<other.underConstruction.size();i++){
        underConstruction.push_back(new Facility(*other.underConstruction[i]));
    }
}

//Move Constructor
Plan::Plan(Plan&& other):plan_id(other.plan_id), settlement(other.settlement), 
selectionPolicy(other.selectionPolicy), status(other.status), facilities(other.facilities),
underConstruction(other.underConstruction),facilityOptions(other.facilityOptions), 
life_quality_score(other.life_quality_score), economy_score(other.economy_score),environment_score(other.environment_score), 
numFacilitiesAtTime((static_cast<int>(other.settlement->getType()))+1)
{
    other.selectionPolicy=nullptr;
    other.facilities.clear();
    other.underConstruction.clear();

}
