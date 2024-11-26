#include "SelectionPolicy.h"


//=========================================================
// Naive Selection
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1)
{
}

const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex++;
    if (lastSelectedIndex >= facilitiesOptions.size())
        lastSelectedIndex = 0;
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const
{
    return ("Selection Logic: Naive, Last Selected Index: " + std::to_string(lastSelectedIndex));
}

NaiveSelection *NaiveSelection::clone() const
{
    return new NaiveSelection(*this);
}




//=========================================================
// Balanced Selection
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore)
{
}

const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    int chosenIndex(0);
    int bestDistance(CalculateDistance(facilitiesOptions[0]));
    bool flag(false);
    for (unsigned int i = 1; (i < facilitiesOptions.size()) & (!flag); i++)
    {
        if (bestDistance == 0)
            flag = true;
        else
        {
            int currentDistance = CalculateDistance(facilitiesOptions[i]);
            if (currentDistance < bestDistance)
            {
                chosenIndex = i;
                bestDistance = currentDistance;
            }
        }
    }
    LifeQualityScore+=facilitiesOptions[chosenIndex].getLifeQualityScore();
    EconomyScore+=facilitiesOptions[chosenIndex].getEconomyScore();
    EnvironmentScore+=facilitiesOptions[chosenIndex].getEnvironmentScore();
    return facilitiesOptions[chosenIndex];
}

int BalancedSelection::CalculateDistance(const FacilityType &f)
{
    int life(LifeQualityScore + f.getLifeQualityScore());
    int eco(EconomyScore + f.getEconomyScore());
    int env(EnvironmentScore + f.getEnvironmentScore());
    return (std::max(std::max(life, eco), env) - std::min(std::min(life, eco), env));
}

const string BalancedSelection::toString() const
{
    return ("Selection Logic: Balanced");
}

BalancedSelection* BalancedSelection::clone() const
{
    return new BalancedSelection(*this);
}



//=========================================================
// Economy Selection
EconomySelection::EconomySelection(): lastSelectedIndex(-1)
{
}

const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    bool flag (false);
    for(unsigned int i=lastSelectedIndex+1;!flag;i++){
        if(i>=facilitiesOptions.size())
            i=0;
        if(facilitiesOptions[i].getCategory()==FacilityCategory::ECONOMY){
            lastSelectedIndex=i;
            flag=true;
        }
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string EconomySelection::toString() const
{
    return ("Selection Logic: Economy, Last Selected Index: " + std::to_string(lastSelectedIndex));
}

EconomySelection *EconomySelection::clone() const
{
    return new EconomySelection(*this);
}


//=========================================================
// Sustainability Selection
SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(-1)
{
}

const FacilityType &SustainabilitySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    bool flag (false);
    for(unsigned int i=lastSelectedIndex+1;!flag;i++){
        if(i>=facilitiesOptions.size())
            i=0;
        if(facilitiesOptions[i].getCategory()==FacilityCategory::ENVIRONMENT){
            lastSelectedIndex=i;
            flag=true;
        }
    }
    return facilitiesOptions[lastSelectedIndex];}

const string SustainabilitySelection::toString() const
{
    return ("Selection Logic: Environment, Last Selected Index: " + std::to_string(lastSelectedIndex));
}

SustainabilitySelection *SustainabilitySelection::clone() const
{
    return new SustainabilitySelection(*this);
}
