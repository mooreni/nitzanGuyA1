#include "Simulation.h"
#include <algorithm>
using namespace std;
/*Notes:
Valgrind check, copy it into the terminal: valgrind --leak-check=full --show-reachable=yes bin/simulation config_file.txt
To Do:
    1.Start + Add Action: Finish how simulation understands the action inputs.
        1.1. At the top of Simulation.h, I added "include action.h". For now i left it out cause we didnt fully write Action yet.
    2.Rule of 5: Destructor-V, CopyConstruct-V, operator=-V, CopyConstruct2-V, operator=2-V, 
*/

Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions()
{
    readConfig(configFilePath);
}

vector<BaseAction*> Simulation::getActionsLog()
{
    return actionsLog;
}

void Simulation::readConfig(const string &configFilePath)
{
    std::ifstream configFile(configFilePath);   //Opens the configFile
    string line;
    //Goes over the configFile line by line
    while(getline(configFile,line)){       
        vector<string> parsedArgs = Auxiliary::parseArguments(line);
        
        //Depends on what the line is, adds it to the correct list:
        if(parsedArgs[0]=="settlement"){
            Settlement* s = new Settlement(parsedArgs[1], static_cast<SettlementType>(stoi(parsedArgs[2])));
            addSettlement(s);
        }
        else if(parsedArgs[0]=="facility"){
            FacilityType f(parsedArgs[1], static_cast<FacilityCategory>(stoi(parsedArgs[2])), stoi(parsedArgs[3]),
                stoi(parsedArgs[4]), stoi(parsedArgs[5]), stoi(parsedArgs[6]));
            addFacility(f);
        }
        else if(parsedArgs[0]=="plan"){
            SelectionPolicy* policy = definePolicy(parsedArgs[2]);
            addPlan(getSettlement(parsedArgs[1]), policy);
        }
    }
}

SelectionPolicy *Simulation::definePolicy(const string &policyShortcut)
{
    if (policyShortcut == "nve") {
        return new NaiveSelection();  // Create and return NaiveSelection object
    }
    else if (policyShortcut == "bal") {
        return new BalancedSelection(0,0,0);  // Create and return BalancedSelection object
    }
    else if (policyShortcut == "env") {
        return new SustainabilitySelection();  // Create and return EnvironmentSelection object
    }
    else if (policyShortcut == "eco") {
        return new EconomySelection();  // Create and return EconomySelection object
    }
    else {
        return nullptr;  // If no match, return nullptr
    }
}

const int Simulation::getPlanCounter()
{
    return planCounter;
}

void Simulation::start()
{
    open();
    cout << "The simulation has started" << "\n";
    while (isRunning)
    {
        string userInput;
        getline(std::cin, userInput);
        vector<string> parsedArgs = Auxiliary::parseArguments(userInput);
        //This will understand what action is called for now, and call to addAction
    } 
}

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy)
{
    if(settlement != nullptr){
        bool validPlan = (isSettlementExists(settlement->getName())&&(selectionPolicy)!=nullptr);
        if(validPlan){
            Plan p(planCounter,*settlement,selectionPolicy,facilitiesOptions);
            plans.push_back(p);
            planCounter++;
        }
    }
}

void Simulation::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement)
{
    bool exists = isSettlementExists(settlement->getName());
    if(exists){
        delete settlement;
        return false;
    }
    settlements.push_back(settlement);
    return true;
}

bool Simulation::addFacility(FacilityType facility)
{
    bool exists = any_of(facilitiesOptions.begin(), facilitiesOptions.end(), [&facility](const FacilityType& f) {
                        return f.getName() == facility.getName();
                    });
    if(exists){
        return false;
    }
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isSettlementExists(const string &settlementName)
{
    bool exists = any_of(settlements.begin(), settlements.end(), [settlementName](const Settlement* s) {
                        return s->getName() == settlementName;
                    });
    return exists;
}

Settlement* Simulation::getSettlement(const string &settlementName)
{
    for (Settlement* settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return settlement;  // Return the pointer to the matching settlement
        }
    }
    return nullptr;  // Return nullptr if no match is found
}

Plan& Simulation::getPlan(const int planID)
{
    for(unsigned int i=0;i<plans.size();i++){
        if(plans[i].getId()==planID){
            return plans[i];
        }
    }
    //Creating Null plan to emphasize that the wanted plan wasn't found
    //Can be identified by planId -1 or by settlementName "Null"
    Settlement s("Null", SettlementType::VILLAGE);
    NaiveSelection* nve = new NaiveSelection();
    vector<FacilityType> vec;
    Plan p(-1,s,nve,vec);
    return p;
}

void Simulation::step() 
{   //forwards all the plans a single step
    for(Plan p : plans){
        p.step();
    }
}

void Simulation::close()
{   //prints all the plan statuses and changes the running flag
    for(Plan p : plans){
        cout << p.toString() << endl;
    }
    isRunning=false;
}

void Simulation::open()
{
    isRunning=true;
}



//Rule of Five
//Destructor
Simulation::~Simulation()
{
    for(unsigned int i=0;i<actionsLog.size();i++){
        delete actionsLog[i];
    }
    for(unsigned int i=0;i<settlements.size();i++){
        delete settlements[i];
    }
}

//Copy Constructor
Simulation::Simulation(const Simulation &other) : isRunning(other.isRunning), planCounter(other.planCounter), 
actionsLog(), plans(other.plans), settlements(), facilitiesOptions(other.facilitiesOptions)
{
    for(unsigned int i=0;i<other.actionsLog.size();i++){
        actionsLog.push_back(other.actionsLog[i]->clone());
    }
    for(unsigned int i=0;i<other.settlements.size();i++){
        settlements.push_back(other.settlements[i]->clone());
    }
}

//Copy Assignment Operator
Simulation &Simulation::operator=(const Simulation &other)
{
    if(&other!=this){
        isRunning=other.isRunning;
        planCounter=other.planCounter;
        //Deleting current actions
        for(unsigned int i=0;i<actionsLog.size();i++){
            delete actionsLog[i];
        }
        actionsLog.clear();
        //Copying in the other actions
        for(unsigned int i=0;i<other.actionsLog.size();i++){
            actionsLog.push_back((other.actionsLog[i])->clone());
        }
        //Deleting settlements
        for(unsigned int i=0;i<settlements.size();i++){
            delete settlements[i];
        }
        settlements.clear();
        //Copying settlements
        for(unsigned int i=0;i<other.settlements.size();i++){
            settlements.push_back((other.settlements[i])->clone());
        }
        //Copying plans
        plans.clear();
        for(unsigned int i=0;i<other.plans.size();i++){
            Settlement* sett = this->getSettlement(other.plans[i].getSettlmentName());
            Plan p (-1,*sett,nullptr,this->facilitiesOptions);
            p=other.plans[i];
            plans.push_back(p);
        }
        //Copying FacilityOptions
        facilitiesOptions.clear();
        for(unsigned int i=0;i<other.facilitiesOptions.size();i++){
            facilitiesOptions.push_back(facilitiesOptions[i]);
        }
    }
    return *this;
}

//Move Constructor
Simulation::Simulation(const Simulation &&other):
isRunning(other.isRunning), planCounter(other.planCounter), actionsLog(move(other.actionsLog)), plans(move(other.plans)),
settlements(move(other.settlements)), facilitiesOptions(move(other.facilitiesOptions))
{
}

//Move Assignment Operator
Simulation &Simulation::operator=(const Simulation &&other)
{
    if(this != &other){
        //Transfering simple objects by value
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        //Clearing current vectors
        for(unsigned int i=0;i<actionsLog.size();i++){
            delete actionsLog[i];
        }
        actionsLog.clear();
        plans.clear();
        for(unsigned int i=0;i<settlements.size();i++){
            delete settlements[i];
        }
        settlements.clear();
        facilitiesOptions.clear();
        //Moving the new vectors
        actionsLog = move(other.actionsLog);
        plans = move(other.plans);
        settlements = move(other.settlements);
        facilitiesOptions = move(other.facilitiesOptions);

    }
    return *this;
}
