#include "QWidget"
#include "QTextEdit"
#include "QLabel"
#include "QLCDNumber"

class PanneauEvents : public QWidget
{
private:
  QLabel *evenements;
  static QTextEdit *txt;
  QLCDNumber *timer_simulation;
public:
    PanneauEvents();
    ~PanneauEvents();
   static void affichage(QString text);

};
