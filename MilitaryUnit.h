#pragma once
#include "AbstractWeapon.h"
#include <string>
#include <vector>

class MilitaryUnit {
private:
    std::string _name;
    std::vector<AbstractWeapon*> _weapons;

public:
    MilitaryUnit(const std::string& name) : _name(name) {}

    void AddWeapon(AbstractWeapon* weapon) {
        if (weapon) _weapons.push_back(weapon);
    }

    void RemoveWeapon(int index) {
        if (index >= 0 && index < static_cast<int>(_weapons.size())) {
            delete _weapons[index];
            _weapons.erase(_weapons.begin() + index);
        }
    }

    void ReplaceWeapon(int index, AbstractWeapon* newWeapon) {
        if (index >= 0 && index < static_cast<int>(_weapons.size()) && newWeapon) {
            delete _weapons[index];
            _weapons[index] = newWeapon;
        }
    }

    double CalculateTotalCost() const {
        double total = 0;
        for (auto w : _weapons) total += w->GetPrice();
        return total;
    }

    const std::vector<AbstractWeapon*>& GetWeapons() const { return _weapons; }

    ~MilitaryUnit() {
        for (auto w : _weapons) delete w;
    }

    std::string GetName() const { return _name; }
};