#include "MainWindow.h"
#include "ui_mainwindow.h" // Обязательный заголовочный файл, генерируемый uic
#include "AddEditForm.h"
#include "PistolFactory.h"
#include "RifleFactory.h"
#include "ColdSteelFactory.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow), _unit("Спецназ РФ") {
    
    // Инициализируем компоненты, созданные в Qt Designer
    _ui->setupUi(this);
    
    setWindowTitle(QString::fromStdString("Управление вооружением: " + _unit.GetName()));
    _ui->weaponComboBox->setMaxVisibleItems(5);

    // Привязываем сигналы кнопок из UI к нашим слотам
    connect(_ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddWeapon);
    connect(_ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditWeapon);
    connect(_ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteWeapon);

    // Начальное заполнение данными с помощью фабрик логики
    PistolFactory pFact;
    RifleFactory rFact;
    ColdSteelFactory cFact;

    _unit.AddWeapon(pFact.Create());
    _unit.AddWeapon(rFact.Create());
    _unit.AddWeapon(cFact.Create());

    updateUiFields();
}

MainWindow::~MainWindow() {
    delete _ui; // Освобождаем память интерфейса
}

void MainWindow::updateUiFields() {
    _ui->weaponComboBox->clear();
    const auto& list = _unit.GetWeapons();

    // Заполнение выпадающего списка
    for (size_t i = 0; i < list.size(); ++i) {
        QString itemText = QString("%1. %2 (%3 руб.)")
                               .arg(i + 1)
                               .arg(QString::fromStdString(list[i]->GetName()))
                               .arg(list[i]->GetPrice());
        _ui->weaponComboBox->addItem(itemText);
    }

    // Обновление метки со стоимостью
    double cost = _unit.CalculateTotalCost();
    _ui->totalCostLabel->setText(QString("Общая стоимость вооружения: %1 руб.").arg(cost));

    // Доступность кнопок управления зависит от наличия элементов
    _ui->editButton->setEnabled(!list.empty());
    _ui->deleteButton->setEnabled(!list.empty());
}

void MainWindow::onAddWeapon() {
    AddEditForm form(this);
    if (form.exec() == QDialog::Accepted) {
        AbstractWeapon* newW = form.getResultWeapon();
        if (newW) {
            _unit.AddWeapon(newW);
            updateUiFields();
        }
    }
}

void MainWindow::onEditWeapon() {
    int idx = _ui->weaponComboBox->currentIndex();
    if (idx < 0) return;

    AbstractWeapon* currentW = _unit.GetWeapons()[idx];
    AddEditForm form(currentW, this); 

    if (form.exec() == QDialog::Accepted) {
        AbstractWeapon* updatedW = form.getResultWeapon();
        if (updatedW) {
            _unit.ReplaceWeapon(idx, updatedW);
            updateUiFields();
        }
    }
}

void MainWindow::onDeleteWeapon() {
    int idx = _ui->weaponComboBox->currentIndex();
    if (idx < 0) return;

    auto result = QMessageBox::question(this, "Подтверждение", "Вы действительно хотите удалить выбранное оружие?",
                                        QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        _unit.RemoveWeapon(idx);
        updateUiFields();
    }
}