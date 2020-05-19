#ifndef INTERFACEG_H
#define INTERFACEG_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QWidget>
#include <QToolBox>
#include <QCheckBox>

class InterfaceG : public QWidget
{
    Q_OBJECT

public:

    InterfaceG();
    ~InterfaceG();


private:

QGridLayout *gridLayoutinterface ;
QLineEdit 	*AdresseIP	;
QLineEdit 	*AdresseMac	;
QLineEdit 	*AdresseRes	;
QLineEdit   *mask ;
QLineEdit   *interfaceName ;
QCheckBox   *liaison ;
QPushButton *appliquer,*supprimer;
QGroupBox *portGroupBox ;
QFormLayout *layout ;
private slots:
    void deleteInterfaceG();
};


#endif
