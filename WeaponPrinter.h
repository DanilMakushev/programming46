#pragma once
#include "Rifle.h"
#include "MilitaryUnit.h"
#include <iostream>

class WeaponPrinter {
public:
    void PrintUnitReport(const MilitaryUnit& unit) {
        std::cout << "ОТЧЕТ ПО ПОДРАЗДЕЛЕНИЮ: " << unit.GetName() << std::endl;

        const auto& weapons = unit.GetWeapons();
        
        for (int i{}; i < weapons.size(); ++i) {
            std::cout << i + 1 << ". ";
            PrintDetailedInfo(weapons[i]);
            std::cout << "----------------------------------------" << std::endl;
        }

        std::cout << "ИТОГО объектов: " << weapons.size() << std::endl;
        std::cout << "ОБЩАЯ СТОИМОСТЬ: " << unit.CalculateTotalCost() << " руб." << std::endl;
    }

    void PrintDetailedInfo(AbstractWeapon* weapon) {
        std::string typeLabel = "Оружие";
        if (dynamic_cast<Pistol*>(weapon)) {
            typeLabel = "Пистолет";
        } else if (dynamic_cast<Rifle*>(weapon)) {
            typeLabel = "Винтовка";
        } else if (dynamic_cast<ColdSteel*>(weapon)) {
            typeLabel = "Холодное оружие";
        }

        std::cout << "Тип: " << typeLabel << " | Название: " << weapon->GetName() << std::endl;
        std::cout << "   [Цена: " << weapon->GetPrice() << " руб. | Вес: " << weapon->GetWeight() << " кг]" << std::endl;

        if (auto fireW = dynamic_cast<AbstractFireWeapon*>(weapon)) {
            std::cout << "   Характеристики: Калибр " << fireW->GetCaliber() 
                      << ", Магазин: " << fireW->GetMagazineCapacity() << " патр." << std::endl;

            if (auto p = dynamic_cast<Pistol*>(weapon)) {
                std::cout << "   Скрытое ношение: " << (p->IsConcealable() ? "Да" : "Нет") << std::endl;
            }
            if (auto r = dynamic_cast<Rifle*>(weapon)) {
                std::cout << "   Тип винтовки: " << r->GetRifleType() << std::endl;
            }
        } 
        else if (auto coldW = dynamic_cast<ColdSteel*>(weapon)) {
            std::cout << "   Характеристики: Длина лезвия " << coldW->GetBladeLength() << " см" << std::endl;
        }
    }
};