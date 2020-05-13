#include "QWidget"
#include "QTextEdit"
#include "QLabel"
#include "QLCDNumber"
#include "gSimulation.hh"
#include "QString"
#include <QThread>

class gSimulation;
class PanneauEvents : public QWidget
{
    Q_OBJECT
private:
  QLabel *evenements;
  static QTextEdit *txt;
  QLCDNumber *timer_simulation;
public:
    PanneauEvents();
    ~PanneauEvents();
   static void affichage(QString text);
public slots:
   void afftime();
};




