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
    void portsWidget();
    void routageWidget(int nbres);
    void delSignal();

    std::vector<QWidget *> getPorts() const;
    void setPorts(const std::vector<QWidget *> &value);

private:

    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QToolBox *toolRoutage,*toolInterface;
    QPushButton *ajouterRoute,*supprimerRoute,*ajouterInterface,*supprimerInterface;
    QWidget *routeWidget,*intWidget;
    QGridLayout *routeLayout,*interfaceLayout;
    int numberRoutes=0;


    std::vector<QPushButton *> buttons;
    std::vector<QWidget *> ports;
private slots:
    void ked(int i);
    void addRoute();
    void addInterface();
    void deleteInterface();
    void deleteRoute(int s);
    void deleteRoute();
};

#endif // DIALOG_H
