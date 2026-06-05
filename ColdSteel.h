#pragma once
#include "AbstractWeapon.h"
#include <string>

class ColdSteel : public AbstractWeapon {
private:
    double _bladeLength;

public:
    ColdSteel(const std::string& name, double price, double weight, double bladeLength)
        : AbstractWeapon(name, price, weight) 
    {
        _bladeLength = (bladeLength < 0.0) ? 0.0 : bladeLength;
    }

    double GetBladeLength() const { return _bladeLength; }
};