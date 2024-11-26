#include "Simulation.h"
#include <iostream>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    
    Settlement s1("Kfar",SettlementType::VILLAGE);
    cout << s1.toString() << endl;
    std::vector<FacilityType> options = {Facility("Hotel", "Kfar", FacilityCategory::ECONOMY, 5, 1,1,1)};
    SelectionPolicy* s = new NaiveSelection();
    cout << s->toString() << endl;
    Plan* p = new Plan(5, s1, s, options);
    cout << p->toString() << endl;
    /*Simulation simulation(configurationFile);
     simulation.start();
     if(backup!=nullptr){
         delete backup;
         backup = nullptr;
     }*/
    return 0;
}