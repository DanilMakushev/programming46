#pragma once
#include "AbstractWeapon.h"


class WeaponFactory {
public:
    virtual AbstractWeapon* Create() = 0;
    virtual ~WeaponFactory() {}
}; 