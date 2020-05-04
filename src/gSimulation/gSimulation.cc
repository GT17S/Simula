#include "gSimulation.hh"

gSimulation::gSimulation()
{
    timer= new QTimer();
    time= new QTime(0,0);
}

gSimulation::gSimulation(etat_s _etat, QTimer *_timer)
{
    this->etat=_etat;
    this->timer=_timer;
}

void gSimulation::setTimer(QTimer *_timer)
{
    this->timer=_timer;
}

void gSimulation::setTime(QTime *_time)
{
    this->time=_time;
}

void gSimulation::setEtat(etat_s _etat)
{
    this->etat=_etat;
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
    this->arreter();
    this->time->setHMS(0,0,0);
    this->demarrer();
}

gSimulation::~gSimulation()
{
    delete timer;
    delete time;
}
