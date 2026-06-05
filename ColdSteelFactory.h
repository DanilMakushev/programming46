#pragma once
#include "WeaponFactory.h"
#include "AbstractWeapon.h"
#include "ColdSteel.h"


class ColdSteelFactory : public WeaponFactory {
public:
    AbstractWeapon* Create() override {
        return new ColdSteel("Штык-нож", 5000.0, 0.3, 15.0);
    }
};