#include "Simulation.h"

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

        }
        else if(parsedArgs[0]=="plan"){

        }

    }
}

void Simulation::start()
{
    //To Implement
}

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy)
{
    //To Implement
}

void Simulation::addAction(BaseAction *action)
{
    //To Implement
}

bool Simulation::addSettlement(Settlement *settlement)
{
    settlements.push_back(settlement);
    return true;
}

bool Simulation::addFacility(FacilityType facility)
{
    //To Implement
    return false;
}

bool Simulation::isSettlementExists(const string &settlementName)
{
    //To Implement
    return false;
}

Settlement *Simulation::getSettlement(const string &settlementName)
{
    //To Implement
    return nullptr;
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


