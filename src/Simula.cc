#include <QApplication>
#include <QtWidgets>

#include "simulaGui.hh"



int main( int argc, char ** argv)	{
    QApplication app(argc,argv);
    simulaGui test;
    test.show();


    return app.exec();

}
