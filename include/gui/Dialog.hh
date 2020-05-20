#ifndef DIALOG_H
#define DIALOG_H
#include <QObject>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QToolBox>
#include <QMainWindow>
#include <QGridLayout>
#include "Noeud.hh"

class Noeud;
class Dialog : public QDialog
{
    Q_OBJECT

public:

    Dialog(Noeud * parent);
    ~Dialog();


    void generalWidget();
    void configurationWidget();
    void interfaceWidget(int nbPorts);
    void routageWidget(int nbres);
    void showConfig(Noeud *src);

private:

    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QToolBox *toolRoutage,*toolInterface;
    QPushButton *ajouterRoute,*supprimerRoute,*ajouterInterface,*supprimerInterface;
    QWidget *routeWidget,*intWidget;
    QGridLayout *routeLayout,*interfaceLayout;
    int numberRoutes=0;
    QLineEdit 	*NomStation;
    QSignalMapper* mapperInterface,*mapperRoute,*mapperRouteAp,*mapperInterfaceAp;



    std::vector<QPushButton *> buttons;
    std::vector<QWidget *> ports;
private slots:
    void addRoute();
    void deleteRouteG(int i);
    void deleteInterfaceG(int i);
    void addInterface();
    void createWidget();
    void createSignals();
    void appliquerInterface(int );
    void appliquerRoute(int );

};

#endif // DIALOG_H
