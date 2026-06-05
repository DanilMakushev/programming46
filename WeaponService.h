#pragma once
#include "WeaponFactory.h"
#include "MilitaryUnit.h"


class WeaponService {
public:
    void ArmUnit(MilitaryUnit& unit, WeaponFactory& factory) {
        unit.AddWeapon(factory.Create());
    }
};