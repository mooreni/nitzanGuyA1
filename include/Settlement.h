#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        const string &getName() const;
        SettlementType getType() const;
        const string toString() const;
        //Added Functions
        Settlement* clone() const;
        const string toString(const SettlementType& type) const;

        private:
            const string name;
            SettlementType type;
};