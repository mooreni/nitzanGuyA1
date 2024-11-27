#include "Simulation.h"

Simulation::Simulation(const string &configFilePath)
{
}

void Simulation::start()
{
}

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy)
{
}

void Simulation::addAction(BaseAction *action)
{
}

bool Simulation::addSettlement(Settlement *settlement)
{
    return false;
}

bool Simulation::addFacility(FacilityType facility)
{
    return false;
}

bool Simulation::isSettlementExists(const string &settlementName)
{
    return false;
}

Settlement *Simulation::getSettlement(const string &settlementName)
{
    return nullptr;
}

Plan &Simulation::getPlan(const int planID)
{
    // TODO: insert return statement here
}

void Simulation::step()
{
}

void Simulation::close()
{
}

void Simulation::open()
{
}
