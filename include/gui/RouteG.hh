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

class RouteG: public QWidget
{
    Q_OBJECT
private:

public:
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

    RouteG();
    ~RouteG();

private slots:
    void deleteroute();
};

#endif // ROUTE_H
