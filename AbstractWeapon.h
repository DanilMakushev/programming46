#pragma once
#include <string>


class AbstractWeapon {
protected:
    std::string _nameOfWeapon;
    double _price;
    double _weight;


public:
    AbstractWeapon(const std::string& name, double price, double weight)
        : _nameOfWeapon(name), _price(price), _weight(weight) {}
    virtual ~AbstractWeapon() {}
    
    std::string GetName() const { return _nameOfWeapon; }
    double GetPrice() const { return _price; }
    double GetWeight() const { return _weight; }
};