#ifndef ROUTEG_H
#define ROUTEG_H
#include <QObject>

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QWidget>
#include <QToolBox>
#include "QSignalMapper"
class RouteG: public QWidget
{
    friend class Dialog;

    Q_OBJECT
private:
QGridLayout *gridLayoutinterface ;
QLineEdit 	*nextHope	;
QLineEdit 	*AdresseRes	;
QLineEdit     *mask ;
QLineEdit     *resName ;
QPushButton *supprimer ;
QPushButton *appliquer ;
QGroupBox *portGroupBox ;
QFormLayout *layout ;
static int key;
void createInputs(QString _nextHope,QString _AdresseRes,QString _mask);
void createLabels();
public:

    RouteG(QString _nextHope=QString(),QString _AdresseRes=QString(),QString _mask=QString());

    ~RouteG();

private slots:
    void deleteroute();
};

#endif // ROUTE_H
