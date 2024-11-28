#include "Action.h"

//Interface Action
BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::ERROR)
{
}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::complete()
{
    status=ActionStatus::COMPLETED;
}

const string &BaseAction::getErrorMsg() const
{
    return "ERROR: "+ errorMsg;
}

void BaseAction::setStatus(ActionStatus newStatus)
{
    status = newStatus;
}

//Step Action
SimulateStep::SimulateStep(const int numOfSteps) : BaseAction(), numOfSteps(numOfSteps)
{
}

void SimulateStep::act(Simulation &simulation)
{
    for(int i=0;i<numOfSteps;i++){
        simulation.step();
    }
    setStatus(ActionStatus::COMPLETED);
}

const string SimulateStep::toString() const
{
    return "step" + std::to_string(numOfSteps);
}

SimulateStep *SimulateStep::clone() const
{
    SimulateStep* s = new SimulateStep(numOfSteps);
    s->setStatus(this->getStatus());
    return s;
}
