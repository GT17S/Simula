#ifndef __HH_MANAGER__
#define __HH_MANAGER__

#include <QObject>

#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>


#include "Data.hh"
#include "Graphe.hh"
#include "NoeudG.hh"
#include "Station.hh"
#include "gSimulation.hh"

class gSimulation;
class Station;

class ThreadManager : public QObject {
Q_OBJECT

private:
	std::vector<Data*> MovingData;
	std::vector<std::thread> WorkingThreads;
	std::map<std::string, std::mutex*> mutexmap;	
	gSimulation* gestionnaire;
	// Ajouté par Massi
	std::vector<Station *> workingStations;
	
	
	bool findWorker ( Station * s);
public:
	ThreadManager(gSimulation* gestionnaire);
	~ThreadManager();

	void initStation();

	
	void joinall();
public slots:
	void createWorker ( NoeudG * n);

};

#endif
