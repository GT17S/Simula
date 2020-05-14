#include "gSimulation.hh"

gSimulation::gSimulation()
{
    timer= new QTimer();
    time= new QTime(0,0);
}

gSimulation::gSimulation(etat_s _etat, QTimer *_timer)
{
    etat=_etat;
    timer=_timer;
}

void gSimulation::setTimer(QTimer *_timer)
{
   timer=_timer;
}

void gSimulation::setTime(QTime *_time)
{
   time=_time;
}

void gSimulation::setEtat(etat_s _etat)
{
    etat=_etat;
}

void gSimulation::arreter()
{
    setEtat(ARRET);
    time->setHMS(0,0,0);
    timer->stop();
}

void gSimulation::demarrer()
{
    setEtat(DEMARRER);
    timer->start(1000);
}

void gSimulation::pause()
{
    setEtat(PAUSE);
    timer->stop();
}

void gSimulation::reset()
{
   arreter();
    time->setHMS(0,0,0);
   demarrer();
}

gSimulation::~gSimulation()
{
    delete timer;
    delete time;
}
QTime *gSimulation::time;
QTimer *gSimulation::timer;
