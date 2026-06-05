#pragma once
#include "AbstractWeapon.h"
#include "WeaponFactory.h"
#include "Pistol.h"
#include <vector>


class PistolFactory : public WeaponFactory {
public:
    AbstractWeapon* Create() override {
        std::vector<std::string> holsters = { "Кожаная поясная", "Тактическая набедренная" };
        return new Pistol("ПМ", 15000.0, 0.81, "9x18 мм", "Полуавтоматический", 8, 30, 315, 50, true, holsters);
    }
};