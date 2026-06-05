#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include "AbstractWeapon.h"

class AddEditForm : public QDialog {
    Q_OBJECT
private:
    // поля ввода
    QComboBox* _typeComboBox;
    QLineEdit* _nameEdit;
    QDoubleSpinBox* _priceSpin;
    QDoubleSpinBox* _weightSpin;

    // Холодное оружие
    QDoubleSpinBox* _bladeLengthSpin;

    // Огнестрельное оружие
    QLineEdit* _caliberEdit;
    QComboBox* _fireTypeComboBox;
    QSpinBox* _magazineCapacitySpin;
    QSpinBox* _rateOfFireSpin;
    QSpinBox* _velocitySpin;
    QSpinBox* _rangeSpin;

    // Пистолет / Винтовка
    QCheckBox* _concealableCheck;
    QCheckBox* _foldableStockCheck;
    QComboBox* _rifleTypeComboBox;

    // Указатели для отслеживания режима работы
    AbstractWeapon* _weaponToEdit;
    AbstractWeapon* _resultWeapon;

    // Счётчик для контроля количества открытых окон
    static int activeWindowsCount;

    void SetupUi();
    bool ValidateInput();

private slots:
    void OnTypeChanged(int index);
    void OnOkClicked();

public:
    explicit AddEditForm(QWidget *parent = nullptr);
    explicit AddEditForm(AbstractWeapon* weapon, QWidget *parent = nullptr);
    ~AddEditForm();

    AbstractWeapon* getResultWeapon() const { return _resultWeapon; }

    int exec() override;
};