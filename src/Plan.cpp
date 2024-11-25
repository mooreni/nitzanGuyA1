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
}

const vector<Facility *> &Plan::getFacilities() const
{
    // TODO: insert return statement here
}

void Plan::addFacility(Facility *facility)
{
}

const string Plan::toString() const
{
    return string();
}
