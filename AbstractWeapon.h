#pragma once
#include <string>

class AbstractWeapon {
protected:
    std::string _nameOfWeapon;
    double _price;
    double _weight;

public:
    AbstractWeapon(const std::string& name, double price, double weight) {
        if (name.empty() || name.find_first_not_of(" \t\n\r") == std::string::npos) {
            _nameOfWeapon = "неизвестно";
        } else {
            _nameOfWeapon = name;
        }
        _price = (price < 0.0) ? 0.0 : price;
        _weight = (weight < 0.0) ? 0.0 : weight;
    }

    virtual ~AbstractWeapon() {}

    std::string GetName() const { return _nameOfWeapon; }
    double GetPrice() const { return _price; }
    double GetWeight() const { return _weight; }
};