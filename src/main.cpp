#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation* backup = nullptr;
void test();

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    //Simulation simulation(configurationFile);
    test();

    /*simulation.start();
     if(backup!=nullptr){
         delete backup;
         backup = nullptr;
     }*/
    return 0;
}




void test(){
    Settlement s1("Kfar",SettlementType::VILLAGE);
    cout << s1.toString() << endl;
    std::vector<FacilityType> options = {FacilityType("Hotel", FacilityCategory::ECONOMY, 1, 1,2,1), 
                                        FacilityType("Park", FacilityCategory::ENVIRONMENT, 2, 2, 3, 2),
                                        FacilityType("School", FacilityCategory::LIFE_QUALITY, 2, 2, 1, 3)};
    SelectionPolicy* s2 = new NaiveSelection();
    SelectionPolicy* s = new BalancedSelection(0,0,0);
    Plan* p = new Plan(1, s1, s2, options);
    cout << p->toString() << endl;
    p->step();
    vector<Facility*> vec = p->getFacilities();
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        cout << vec[i]->toString() << endl;
    }
    p->step();
    p->setSelectionPolicy(s);
    p->step();
    vec = p->getFacilities();
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        cout << vec[i]->toString() << endl;
    }
    cout << p->toString() << endl;
}