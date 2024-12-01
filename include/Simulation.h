#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Auxiliary.h"
#include <fstream>
//#include "Action.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
        void start();
        void addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement *getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();
        //Added Functions
        void readConfig(const string &configFilePath);
        SelectionPolicy* definePolicy(const string& policyShortcut); 
        //Rule of Five
        ~Simulation();
        Simulation(const Simulation& other);
        Simulation& operator=(const Simulation& other);
        Simulation(const Simulation&& other);
        Simulation& operator=(const Simulation&& other);

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};