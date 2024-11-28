#include "Simulation.h"
#include <algorithm>

Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions()
{
    readConfig(configFilePath);
}

void Simulation::readConfig(const string &configFilePath)
{
    std::ifstream configFile(configFilePath);   //Opens the configFile
    string line;
    //Goes over the configFile line by line
    while(std::getline(configFile,line)){       
        vector<string> parsedArgs = Auxiliary::parseArguments(line);
        
        //Depends on what the line is, adds it to the correct list:
        if(parsedArgs[0]=="settlement"){
            Settlement* s = new Settlement(parsedArgs[1], static_cast<SettlementType>(std::stoi(parsedArgs[2])));
            addSettlement(s);
        }
        else if(parsedArgs[0]=="facility"){
            FacilityType f(parsedArgs[1], static_cast<FacilityCategory>(std::stoi(parsedArgs[2])), std::stoi(parsedArgs[3]),
                std::stoi(parsedArgs[4]), std::stoi(parsedArgs[5]), std::stoi(parsedArgs[6]));
            addFacility(f);
        }
        else if(parsedArgs[0]=="plan"){
            bool validPlan = isSettlementExists(parsedArgs[1])&&((definePolicy(parsedArgs[2]))!=nullptr);
            if(!validPlan){
                std::cout << "Cannot create this plan." << "\n";
            }
            else{
                addPlan(getSettlement(parsedArgs[1]), definePolicy(parsedArgs[2]));
            } 
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

void Simulation::start()
{
    //To Implement
}

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy)
{
    Plan p(planCounter,*settlement,selectionPolicy,facilitiesOptions);
    plans.push_back(p);
    planCounter++;
}

void Simulation::addAction(BaseAction *action)
{
    //To Implement
}

bool Simulation::addSettlement(Settlement *settlement)
{
    bool exists = isSettlementExists(settlement->getName());
    if(!exists){
        std::cout << "Settlement already exists." << "\n";
        return false;
    }
    settlements.push_back(settlement);
    return true;
}

bool Simulation::addFacility(FacilityType facility)
{
    bool exists = std::any_of(facilitiesOptions.begin(), facilitiesOptions.end(), [&facility](const FacilityType& f) {
                        return f.getName() == facility.getName();
                    });
    if(!exists){
        std::cout << "Facility already exists." << "\n";
        return false;
    }
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isSettlementExists(const string &settlementName)
{
    bool exists = std::any_of(settlements.begin(), settlements.end(), [settlementName](const Settlement* s) {
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

Plan &Simulation::getPlan(const int planID)
{
    //To Implement
}

void Simulation::step()
{
    //To Implement
}

void Simulation::close()
{
    //To Implement
}

void Simulation::open()
{
    //To Implement
}


