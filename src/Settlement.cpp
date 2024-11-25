#include "Settlement.h"

Settlement::Settlement(const string& name, SettlementType type) : name(name) , type(type)
{
}

const string& Settlement::getName() const
{
    return name;
}

SettlementType Settlement::getType() const
{
    return type;
}

const string Settlement::toString() const
{
    string ret ("Settlement Name: " + getName() + ", Type: ");
    SettlementType tempType = getType();
    if(tempType==SettlementType::CITY)
        ret.append("City");
    else if(tempType==SettlementType::METROPOLIS)
        ret.append("Metropolis");
    else if(tempType==SettlementType::VILLAGE)
        ret.append("Village");
    return ret;
}
