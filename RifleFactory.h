#pragma once
#include "WeaponFactory.h"
#include "Rifle.h"

class RifleFactory : public WeaponFactory {
public:
    AbstractWeapon* Create() override {
        return new Rifle("СВД", 85000.0, 4.3, "7.62x54mmR", "Полуавтоматический", 10, 30, 830, 1200, false, "Снайперская винтовка");
    }
};