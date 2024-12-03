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
    SettlementType type = getType();
    ret.append(toString(type));
    return ret;
}

Settlement *Settlement::clone() const
{
    return new Settlement(name,this->getType());
}

const string Settlement::toString(const SettlementType& type) const
{
    string ret;
    if(type==SettlementType::CITY)
        ret.append("City");
    else if(type==SettlementType::METROPOLIS)
        ret.append("Metropolis");
    else if(type==SettlementType::VILLAGE)
        ret.append("Village");
    return ret;
}
