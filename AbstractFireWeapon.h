#pragma once
#include "AbstractWeapon.h"
#include <string>


class AbstractFireWeapon : public AbstractWeapon {
protected:
    std::string _caliber;
    std::string _fireType;
    int _magazineCapacity;
    int _rateOfFire;
    int _initialBulletVelocity;
    int _aimingRange;


public:
    AbstractFireWeapon(const std::string& name, double price, double weight, 
                        const std::string& caliber, const std::string& fireType,
                        int magazineCapacity, int rateOfFire,
                        int initialBulletVelocity, int aimingRange)
        :   AbstractWeapon(name, price, weight), 
            _caliber(caliber), _fireType(fireType),
            _magazineCapacity(magazineCapacity), _rateOfFire(rateOfFire),
            _initialBulletVelocity(initialBulletVelocity), _aimingRange(aimingRange) {}
    
    std::string GetCaliber() const { return _caliber; }
    std::string GetFireType() const { return _fireType; }
    int GetMagazineCapacity() const { return _magazineCapacity; }
    int GetRateOfFire() const { return _rateOfFire; }
    int GetInitialBulletVelocity() const { return _initialBulletVelocity; }
    int GetAimingRange() const { return _aimingRange; }
};