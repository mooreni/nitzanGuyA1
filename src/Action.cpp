#include "Action.h"
extern Simulation* backup;

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

void BaseAction::error(string errorMsg)
{
    this->errorMsg = errorMsg;
    
}

const string &BaseAction::getErrorMsg() const
{
    return errorMsg;
}

void BaseAction::setStatus(ActionStatus newStatus)
{
    status = newStatus;
}

const string BaseAction::toString(ActionStatus status) const
{
    if(status==ActionStatus::ERROR){
        return "ERROR";
    }
    return "COMPLETED";
}

//step Action
SimulateStep::SimulateStep(const int numOfSteps) : BaseAction(), numOfSteps(numOfSteps)
{
}

void SimulateStep::act(Simulation &simulation)
{
    for(int i=0;i<numOfSteps;i++){
        simulation.step();
    }
    complete();
}

const string SimulateStep::toString() const
{
    return "step " + std::to_string(numOfSteps) + " " + BaseAction::toString(getStatus()) + "\n";
}

SimulateStep *SimulateStep::clone() const
{
    SimulateStep* s = new SimulateStep(numOfSteps);
    s->setStatus(this->getStatus());
    return s;
}

//plan Action
AddPlan::AddPlan(const string & settlementName, const string & selectionPolicy):
BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy)
{
    error("Cannot create this plan.");
}

void AddPlan::act(Simulation & simulation)
{
    int currPC = simulation.getPlanCounter();
    SelectionPolicy* policy = simulation.definePolicy(selectionPolicy);
    simulation.addPlan(simulation.getSettlement(settlementName), policy);
    if(currPC == simulation.getPlanCounter()){ //Checks if a new plan was created
        setStatus(ActionStatus::ERROR);
        cout << getErrorMsg() << endl;
        delete policy;
    }
    else{
        complete();
    }
}

const string AddPlan::toString() const
{
    return "plan " + settlementName + " " + selectionPolicy + " " + BaseAction::toString(getStatus()) + "\n";
}

AddPlan * AddPlan::clone() const
{
    AddPlan* p = new AddPlan(settlementName, selectionPolicy);
    p->setStatus(this->getStatus());
    return p;
}

//settlment Action
AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType):
BaseAction(), settlementName(settlementName), settlementType(settlementType)
{
    error("Settlement already exists.");
}

void AddSettlement::act(Simulation &simulation)
{
    Settlement* s = new Settlement(settlementName, settlementType);
    bool added = simulation.addSettlement(s);
    if(added){ //Checks if the settlement was added 
        complete();
    }
    else{
        setStatus(ActionStatus::ERROR);
        cout << getErrorMsg() << endl;
    }
}

AddSettlement *AddSettlement::clone() const
{
    AddSettlement* s = new AddSettlement(settlementName, settlementType);
    s->setStatus(this->getStatus());
    return s;

}

const string AddSettlement::toString() const
{
    Settlement s(settlementName, settlementType);
    return "settlement " + settlementName + " " + s.toString(settlementType) + " " + 
    BaseAction::toString(getStatus()) + "\n";
}

//facility Action
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
BaseAction(), facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore)
{
    error("Facility already exists.");
}

void AddFacility::act(Simulation &simulation)
{
    FacilityType f(facilityName, facilityCategory, price,
        lifeQualityScore, economyScore, environmentScore);
    bool added = simulation.addFacility(f);
    if(added){
        complete();
    }
    else{
        setStatus(ActionStatus::ERROR);
        cout << getErrorMsg() << endl;
    }
}

AddFacility *AddFacility::clone() const
{
    AddFacility* f = new AddFacility(facilityName, facilityCategory, price,
        lifeQualityScore, economyScore, environmentScore);
    f->setStatus(this->getStatus());
    return f;
}

const string AddFacility::toString() const
{
    FacilityType f(facilityName, facilityCategory, price,
        lifeQualityScore, economyScore, environmentScore);
    return "facility " + facilityName + " " + f.toString(facilityCategory) + " " + 
    to_string(price) + " " + to_string(lifeQualityScore) + " " + to_string(economyScore) + " " +
    to_string(environmentScore) + BaseAction::toString(getStatus()) + "\n";
}

//planStatus Action
PrintPlanStatus::PrintPlanStatus(int planId):
BaseAction(), planId(planId)
{
    error("Plan doesn't exist.");
}

void PrintPlanStatus::act(Simulation &simulation)
{
    Plan& p(simulation.getPlan(planId));
    if(p.getId() == -1){
        setStatus(ActionStatus::ERROR);
        cout << "Error:" + getErrorMsg() << endl;
    }
    else{
        p.printStatus();
        complete();
    }
}

PrintPlanStatus * PrintPlanStatus::clone() const
{
    PrintPlanStatus* p = new PrintPlanStatus(planId);
    p->setStatus(this->getStatus());
    return p;
}

const string PrintPlanStatus::toString() const
{
return "planStatus " + to_string(planId) + " " + BaseAction::toString(getStatus()) + "\n";
}

//changePolicy Action
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string & newPolicy):
BaseAction(), planId(planId), newPolicy(newPolicy)
{
    error("Cannot change selection policy.");
}

void ChangePlanPolicy::act(Simulation & simulation)
{
    SelectionPolicy* policy = simulation.definePolicy(newPolicy);
    Plan p = simulation.getPlan(planId);
    if((p.getId()==-1)||(p.getPolicy()==policy)){
        setStatus(ActionStatus::ERROR);
        cout << getErrorMsg() << endl;
    }
    else{
        p.setSelectionPolicy(policy);
        complete();
    }
}

ChangePlanPolicy * ChangePlanPolicy::clone() const
{
    ChangePlanPolicy* c = new ChangePlanPolicy(planId, newPolicy);
    c->setStatus(this->getStatus());
    return c;
}

const string ChangePlanPolicy::toString() const
{
    return "changePolicy " + to_string(planId) + " " + newPolicy + " " + BaseAction::toString(getStatus()) + "\n";
}

//log Action
PrintActionsLog::PrintActionsLog(): BaseAction()
{
}

void PrintActionsLog::act(Simulation &simulation)
{
    vector<BaseAction*> vec = simulation.getActionsLog();
    for(unsigned int i=0; i<vec.size(); i++){
        cout << vec[i]->toString();
    }
    cout<< "\n";
    complete();
}

PrintActionsLog *PrintActionsLog::clone() const
{
    PrintActionsLog* l = new PrintActionsLog();
    l->setStatus(this->getStatus());
    return l;
}

const string PrintActionsLog::toString() const
{
    return "log " + BaseAction::toString(getStatus()) + "\n";
}

//close Action
Close::Close(): BaseAction()
{
}

void Close::act(Simulation &simulation)
{
    simulation.close();
    complete();
}

Close *Close::clone() const
{
    Close* c = new Close();
    c->setStatus(this->getStatus());
    return c;
}

const string Close::toString() const
{
    return "close " + BaseAction::toString(getStatus());
}

//backup Action
BackupSimulation::BackupSimulation(): BaseAction()
{
}

void BackupSimulation::act(Simulation &simulation)
{
    delete backup;
    backup=nullptr;
    backup = new Simulation(simulation);
    complete();
}

BackupSimulation *BackupSimulation::clone() const
{
    BackupSimulation* b = new BackupSimulation();
    b->setStatus(this->getStatus());
    return b;
}

const string BackupSimulation::toString() const
{
    return "backup " + BaseAction::toString(getStatus());
}

//restore Action
RestoreSimulation::RestoreSimulation(): BaseAction()
{
    error("No backup available.");
}

void RestoreSimulation::act(Simulation &simulation)
{
    if(backup==nullptr){
        setStatus(ActionStatus::ERROR);
        cout << getErrorMsg() << endl;
    }
    else{
        simulation = *backup;
        complete();
    }
}

RestoreSimulation *RestoreSimulation::clone() const
{
    RestoreSimulation* r = new RestoreSimulation();
    r->setStatus(this->getStatus());
    return r;
}

const string RestoreSimulation::toString() const
{
    return "restore " + BaseAction::toString(getStatus());
}
