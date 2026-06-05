#pragma once
#include "AbstractFireWeapon.h"
#include <vector>
#include <string>

class Pistol : public AbstractFireWeapon {
private:
    bool _isConcealable;
    std::vector<std::string> _holsters;

public:
    Pistol(const std::string& name, double price, double weight,
           const std::string& caliber, const std::string& fireType,
           int magazineCapacity, int rateOfFire,
           int initialBulletVelocity, int aimingRange,
           bool isConcealable, const std::vector<std::string>& holsters)
        : AbstractFireWeapon(name, price, weight, caliber, fireType,
                             magazineCapacity, rateOfFire, initialBulletVelocity, aimingRange),
        _isConcealable(isConcealable), _holsters(holsters) {}

    bool IsConcealable() const { return _isConcealable; }
    const std::vector<std::string>& GetHolsters() const { return _holsters; }
};