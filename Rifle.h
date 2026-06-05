#pragma once 
#include "AbstractFireWeapon.h"
#include <string>

class Rifle : public AbstractFireWeapon {
private:
    bool _isFoldableStock;
    std::string _rifleType;

public:
    Rifle(const std::string& name, double price, double weight,
            const std::string& caliber, const std::string& fireType,
            int magazineCapacity, int rateOfFire,
            int initialBulletVelocity, int aimingRange,
            bool isFoldableStock, const std::string& rifleType)
        : AbstractFireWeapon(name, price, weight, caliber, fireType,
                             magazineCapacity, rateOfFire, initialBulletVelocity, aimingRange),
          _isFoldableStock(isFoldableStock) 
    {
        if (rifleType.empty() || rifleType.find_first_not_of(" \t\n\r") == std::string::npos) {
            _rifleType = "неизвестно";
        } else {
            _rifleType = rifleType;
        }
    }

    bool IsFoldableStock() const { return _isFoldableStock; }
    std::string GetRifleType() const { return _rifleType; }
};