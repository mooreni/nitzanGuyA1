#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
        //Added functions
        SelectionPolicy* getPolicy();
        const string toString(const PlanStatus& status) const;
        const string toString(const vector<Facility*>& facilities) const;
        const string getSettlmentName() const;
        const int getId() const;
        void partialMovePlan(const Plan& other);
        
        //Rule of Five
        ~Plan();
        Plan (const Plan& other);
        Plan& operator=(const Plan& other) = delete;
        Plan (Plan&& other);
        Plan& operator=(Plan&& other) = delete;

    private:
        int plan_id;
        const Settlement* settlement;
        SelectionPolicy* selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;

        unsigned int numFacilitiesAtTime; //Added Variable

};