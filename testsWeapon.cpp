#include <QtTest>
#include <QObject>
#include <vector>
#include <string>
#include "ColdSteel.h"
#include "Pistol.h"
#include "Rifle.h"

class TestsWeapon : public QObject
{
    Q_OBJECT

private slots:
    void testInvalidNegativeValues() {
        Rifle rifle("АК-74", -50.00, -4.00, "5.45", "Автоматический", -30, -600, -900, -400, true, "Штурмовая винтовка");
        QCOMPARE(rifle.GetPrice(), 0.0);
        QCOMPARE(rifle.GetWeight(), 0.0);
        QCOMPARE(rifle.GetMagazineCapacity(), 0);
        QCOMPARE(rifle.GetRateOfFire(), 0);
    }

    void testInvalidSpaces() {
        Rifle rifle("    ", 50.00, 4.00, "    ", "Автоматический", 30, 600, 900, 400, true, "Штурмовая винтовка");
        QString name = QString::fromStdString(rifle.GetName());
        QString caliber = QString::fromStdString(rifle.GetCaliber());

        QVERIFY2(!name.trimmed().isEmpty(), "will be save name full of spaces");
        QVERIFY2(!caliber.trimmed().isEmpty(), "will be save caliber full of spaces");
    }
};

QTEST_APPLESS_MAIN(TestsWeapon)
#include "testsWeapon.moc"