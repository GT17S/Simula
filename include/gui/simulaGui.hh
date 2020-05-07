
#ifndef __H_SIMULAGUI__
#define __H_SIMULAGUI__ 

#include <QtWidgets>
#include <QIcon>
#include <QVector>
#include <QGridLayout>
#include <QTextEdit>
#include <QWidget>
#include <QLabel>

class simulaGui: public QWidget {
private:
	//Grid
    QGridLayout* mainlayout;
	//Va contenir les 5 widgets
    QVector<QLabelf* > widgets;

public:
	simulaGui();
	~simulaGui();
	

    QGridLayout* getMainlayout(void) const {return mainlayout;};

};


#endif
