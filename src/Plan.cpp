#include "Plan.h"

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
plan_id(planId), settlement(new Settlement(settlement)), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions),
numFacilitiesAtTime((static_cast<int>(settlement.getType()))+1), status(PlanStatus::AVALIABLE)
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

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy)
{
    this->selectionPolicy = selectionPolicy;
}

void Plan::step()
{
}

void Plan::printStatus()
{
    std::cout << "The current status is: " << toString(status) << "\n";
}

const vector<Facility *> &Plan::getFacilities() const
{
    return facilities;
}

void Plan::addFacility(Facility *facility)
{

}


const string Plan::toString(PlanStatus status) const
{
    switch (status)
    {
        case PlanStatus::AVALIABLE:   return "Available";
        case PlanStatus::BUSY: return "Busy"; 
    }

}

const string Plan::toString() const
{
    return string("Plan Id: " + std::to_string(plan_id) + "\n" +
                "Settlement name: " + settlement->getName() + "\n" +
                "Selection policy: " + selectionPolicy->toString() + "\n" +
                "Plan status: " + Plan::toString(status) + "\n");

}
