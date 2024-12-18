#include "Plan.h"
#include <sstream>

Plan::Plan(const int planId, const Settlement& settlement, SelectionPolicy* selectionPolicy, const vector<FacilityType>& facilityOptions):
plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilities(), underConstruction(),
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
    if(typeid(*selectionPolicy) == typeid(BalancedSelection)){ //Checks selection Policy type
        int life = this->getlifeQualityScore(); //gets current plan's scores
        int eco = this->getEconomyScore();
        int env = this->getEnvironmentScore();
        //Updates these scores with what the underconstruction facilities will give
        for(unsigned int i=0;i<underConstruction.size();i++){
            life+=underConstruction[i]->getLifeQualityScore();
            eco+=underConstruction[i]->getEconomyScore();
            env+=underConstruction[i]->getEnvironmentScore();
        }
        //casts safely to Balanced Selection and gives it it's new fields
        (static_cast<BalancedSelection*>(selectionPolicy))->setFields(life,eco,env);
    }
    //Deletes the old selection policy and sets plan's current one as the new one
    delete this->selectionPolicy;
    this->selectionPolicy = selectionPolicy;
}

void Plan::step()
{
    if(status==PlanStatus::AVALIABLE){
        while (underConstruction.size()<numFacilitiesAtTime)
        {
            Facility* f = new Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
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
    std::cout << Plan::toString();
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
        << "Settlement name: " << settlement.getName() << "\n"
        << "Plan status: " << Plan::toString(status) << "\n"
        << "Selection policy: " << selectionPolicy->toString() << "\n"
        << "LifeQualityScore: " << life_quality_score << "\n"
        << "EconomyScore: " << economy_score << "\n"
        << "EnvironmentScore: " << environment_score << "\n"
        << Plan::toString(facilities)
        << Plan::toString(underConstruction);

    return s.str();
}

SelectionPolicy *Plan::getPolicy()
{
    return selectionPolicy;
}

const PlanStatus Plan::getStatus() const
{
return status;
}

const string Plan::toString(const PlanStatus &status) const
{
    switch (status)
    {
        case PlanStatus::AVALIABLE: return "AVAILABLE";
        case PlanStatus::BUSY: return "BUSY"; 
    }
    return "";
}

const string Plan::toString(const vector<Facility*>& listToPrint) const
{
 std::ostringstream s;

    for(unsigned int i = 0; i < listToPrint.size(); i++){
        /*if (i > 0) {
            s << "\n";
        }*/
        s << "FacilityName: " << listToPrint[i]->getName() << "\n"
        << "FacilityStatus: " << listToPrint[i]->toString(listToPrint[i]->getStatus()) << "\n";
    }
    return s.str();
}

const string Plan::getSettlmentName() const
{
    return settlement.getName();
}

const int Plan::getId() const
{
    return plan_id;
}

void Plan::partialMovePlan(const Plan &other)
{
    if(&other!=this){
        plan_id = other.plan_id;
        selectionPolicy = other.selectionPolicy->clone();
        status = other.status;
        for(unsigned int i=0;i<facilities.size();i++){
            delete facilities[i];
        }
        facilities.clear();
        for(unsigned int i=0;i<other.facilities.size();i++){
            facilities.push_back(new Facility(*other.facilities[i]));
        }
        for(unsigned int i=0;i<underConstruction.size();i++){
            delete underConstruction[i];
        }
        underConstruction.clear();
        for(unsigned int i=0;i<other.underConstruction.size();i++){
            underConstruction.push_back(new Facility(*other.underConstruction[i]));
        }
        life_quality_score=other.life_quality_score;
        economy_score=other.economy_score;
        environment_score=other.environment_score;
    }
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
numFacilitiesAtTime((static_cast<int>(other.settlement.getType()))+1)
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
selectionPolicy(other.selectionPolicy), status(other.status), facilities(std::move(other.facilities)),
underConstruction(std::move(other.underConstruction)),facilityOptions(other.facilityOptions), 
life_quality_score(other.life_quality_score), economy_score(other.economy_score),environment_score(other.environment_score), 
numFacilitiesAtTime((static_cast<int>(other.settlement.getType()))+1)
{
    other.selectionPolicy=nullptr;
}
