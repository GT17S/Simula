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
#include "QString"
#include "QSignalMapper"

class InterfaceG : public QWidget
{
    friend class Dialog;
    Q_OBJECT

public:

    InterfaceG(QString _AdresseIP=QString(),QString _AdresseMac=QString(),QString _AdresseRes=QString(),QString _mask=QString(),QString _interfaceName=QString(),bool _liaison=false);
    ~InterfaceG();


private:
void createInputs(QString _AdresseIP,QString _AdresseMac,QString _AdresseRes,QString _mask,QString _interfaceName,bool _liaison);
void createLabels();
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
