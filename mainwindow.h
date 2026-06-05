#pragma once
#include <QMainWindow>
#include "MilitaryUnit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *_ui;
    MilitaryUnit _unit;

    void updateUiFields();

private slots:
    void onAddWeapon();
    void onEditWeapon();
    void onDeleteWeapon();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};