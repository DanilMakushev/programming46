#include "AddEditForm.h"
#include "ColdSteel.h"
#include "Pistol.h"
#include "Rifle.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

int AddEditForm::activeWindowsCount = 0;

AddEditForm::AddEditForm(QWidget *parent)
    : QDialog(parent), _weaponToEdit(nullptr), _resultWeapon(nullptr) {
    setWindowTitle("Добавить оружие");
    SetupUi();
    OnTypeChanged(0); // По умолчанию холодное оружие
}

AddEditForm::AddEditForm(AbstractWeapon* weapon, QWidget *parent)
    : QDialog(parent), _weaponToEdit(weapon), _resultWeapon(nullptr) {
    setWindowTitle("Редактировать оружие");
    SetupUi();

    // Блокируем смену типа при редактировании
    _typeComboBox->setEnabled(false);

    // Заполняем базовые поля
    _nameEdit->setText(QString::fromStdString(weapon->GetName()));
    _priceSpin->setValue(weapon->GetPrice());
    _weightSpin->setValue(weapon->GetWeight());

    // Определяем конкретный тип и заполняем специфичные поля
    if (auto cold = dynamic_cast<ColdSteel*>(weapon)) {
        _typeComboBox->setCurrentIndex(0);
        _bladeLengthSpin->setValue(cold->GetBladeLength());
    }
    else if (auto pistol = dynamic_cast<Pistol*>(weapon)) {
        _typeComboBox->setCurrentIndex(1);
        _caliberEdit->setText(QString::fromStdString(pistol->GetCaliber()));
        _fireTypeComboBox->setCurrentText(QString::fromStdString(pistol->GetFireType()));
        _magazineCapacitySpin->setValue(pistol->GetMagazineCapacity());
        _rateOfFireSpin->setValue(pistol->GetRateOfFire());
        _velocitySpin->setValue(pistol->GetInitialBulletVelocity());
        _rangeSpin->setValue(pistol->GetAimingRange());
        _concealableCheck->setChecked(pistol->IsConcealable());
    }
    else if (auto rifle = dynamic_cast<Rifle*>(weapon)) {
        _typeComboBox->setCurrentIndex(2);
        _caliberEdit->setText(QString::fromStdString(rifle->GetCaliber()));
        _fireTypeComboBox->setCurrentText(QString::fromStdString(rifle->GetFireType()));
        _magazineCapacitySpin->setValue(rifle->GetMagazineCapacity());
        _rateOfFireSpin->setValue(rifle->GetRateOfFire());
        _velocitySpin->setValue(rifle->GetInitialBulletVelocity());
        _rangeSpin->setValue(rifle->GetAimingRange());
        _foldableStockCheck->setChecked(rifle->IsFoldableStock());
        _rifleTypeComboBox->setCurrentText(QString::fromStdString(rifle->GetRifleType()));
    }

    OnTypeChanged(_typeComboBox->currentIndex());
}

AddEditForm::~AddEditForm() {}

int AddEditForm::exec() {
    if (activeWindowsCount >= 2) {
        QMessageBox::critical(this, "Предупреждение", "Невозможно открыть окно! Максимальное количество одновременно открытых окон: 2.");
        return QDialog::Rejected;
    }
    activeWindowsCount++;
    int result = QDialog::exec();
    activeWindowsCount--;
    return result;
}

void AddEditForm::SetupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();
    formLayout->setObjectName("formLayout"); // Присваиваем имя для поиска макета

    _typeComboBox = new QComboBox(this);
    _typeComboBox->addItems({"Холодное оружие", "Пистолет", "Винтовка"});
    formLayout->addRow("Тип оружия:", _typeComboBox);

    _nameEdit = new QLineEdit(this);
    formLayout->addRow("Название:", _nameEdit);

    _priceSpin = new QDoubleSpinBox(this);
    _priceSpin->setRange(0.0, 1000000.0);
    _priceSpin->setSuffix(" руб.");
    formLayout->addRow("Цена:", _priceSpin);

    _weightSpin = new QDoubleSpinBox(this);
    _weightSpin->setRange(0.0, 100.0);
    _weightSpin->setSuffix(" кг");
    formLayout->addRow("Вес:", _weightSpin);

    // Специфичные поля
    _bladeLengthSpin = new QDoubleSpinBox(this);
    _bladeLengthSpin->setRange(0.0, 200.0);
    _bladeLengthSpin->setSuffix(" см");
    formLayout->addRow("Длина лезвия:", _bladeLengthSpin);

    _caliberEdit = new QLineEdit(this);
    formLayout->addRow("Калибр:", _caliberEdit);

    // Заменяем текстовое поле режима огня на выпадающий список
    _fireTypeComboBox = new QComboBox(this);
    _fireTypeComboBox->addItems({"Одиночный", "Автоматический", "Полуавтоматический", "Отсечка по 3 выстрела"});
    formLayout->addRow("Режим огня:", _fireTypeComboBox);

    _magazineCapacitySpin = new QSpinBox(this);
    _magazineCapacitySpin->setRange(0, 200);
    formLayout->addRow("Емкость магазина:", _magazineCapacitySpin);

    _rateOfFireSpin = new QSpinBox(this);
    _rateOfFireSpin->setRange(0, 2000);
    formLayout->addRow("Скорострельность (в/мин):", _rateOfFireSpin);

    _velocitySpin = new QSpinBox(this);
    _velocitySpin->setRange(0, 3000);
    formLayout->addRow("Нач. скорость пули (м/с):", _velocitySpin);

    _rangeSpin = new QSpinBox(this);
    _rangeSpin->setRange(0, 5000);
    formLayout->addRow("Прицельная дальность (м):", _rangeSpin);

    _concealableCheck = new QCheckBox("Допускает скрытое ношение", this);
    formLayout->addRow("Скрытное ношение:", _concealableCheck);

    _foldableStockCheck = new QCheckBox("Складной приклад", this);
    formLayout->addRow("Складной приклад:", _foldableStockCheck);

    // Заменяем текстовое поле типа винтовки на выпадающий список
    _rifleTypeComboBox = new QComboBox(this);
    _rifleTypeComboBox->addItems({"Штурмовая винтовка", "Снайперская винтовка", "Охотничий карабин", "Гладкоствольное ружье"});
    formLayout->addRow("Тип винтовки:", _rifleTypeComboBox);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* okBtn = new QPushButton("ОК", this);
    QPushButton* cancelBtn = new QPushButton("Отмена", this);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);

    connect(_typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddEditForm::OnTypeChanged);
    connect(okBtn, &QPushButton::clicked, this, &AddEditForm::OnOkClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void AddEditForm::OnTypeChanged(int index) {
    // Безопасно находим наш QFormLayout
    QFormLayout* formLayout = findChild<QFormLayout*>("formLayout");
    if (!formLayout) return;

    bool isCold = (index == 0);
    bool isPistol = (index == 1);
    bool isRifle = (index == 2);
    bool isFirearm = (isPistol || isRifle);

    // Переключаем видимость СТРОК целиком (вместе с текстовыми Label)
    formLayout->setRowVisible(_bladeLengthSpin, isCold);

    formLayout->setRowVisible(_caliberEdit, isFirearm);
    formLayout->setRowVisible(_fireTypeComboBox, isFirearm);
    formLayout->setRowVisible(_magazineCapacitySpin, isFirearm);
    formLayout->setRowVisible(_rateOfFireSpin, isFirearm);
    formLayout->setRowVisible(_velocitySpin, isFirearm);
    formLayout->setRowVisible(_rangeSpin, isFirearm);

    formLayout->setRowVisible(_concealableCheck, isPistol);

    formLayout->setRowVisible(_foldableStockCheck, isRifle);
    formLayout->setRowVisible(_rifleTypeComboBox, isRifle);
}

bool AddEditForm::ValidateInput() {
    if (_nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Название' не должно быть пустым!");
        return false;
    }
    if (_typeComboBox->currentIndex() > 0) {
        if (_caliberEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните калибр огнестрельного оружия!");
            return false;
        }
    }
    return true;
}

void AddEditForm::OnOkClicked() {
    if (!ValidateInput()) return;

    std::string name = _nameEdit->text().toStdString();
    double price = _priceSpin->value();
    double weight = _weightSpin->value();

    if (_typeComboBox->currentIndex() == 0) {
        _resultWeapon = new ColdSteel(name, price, weight, _bladeLengthSpin->value());
    }
    else if (_typeComboBox->currentIndex() == 1) {
        std::vector<std::string> holsters = {"Стандартная"};
        _resultWeapon = new Pistol(name, price, weight,
                                   _caliberEdit->text().toStdString(),
                                   _fireTypeComboBox->currentText().toStdString(), // Считываем из ComboBox
                                   _magazineCapacitySpin->value(),
                                   _rateOfFireSpin->value(),
                                   _velocitySpin->value(),
                                   _rangeSpin->value(),
                                   _concealableCheck->isChecked(),
                                   holsters);
    }
    else if (_typeComboBox->currentIndex() == 2) {
        _resultWeapon = new Rifle(name, price, weight,
                                  _caliberEdit->text().toStdString(),
                                  _fireTypeComboBox->currentText().toStdString(), // Считываем из ComboBox
                                  _magazineCapacitySpin->value(),
                                  _rateOfFireSpin->value(),
                                  _velocitySpin->value(),
                                  _rangeSpin->value(),
                                  _foldableStockCheck->isChecked(),
                                  _rifleTypeComboBox->currentText().toStdString()); // Считываем из ComboBox
    }

    accept();
}