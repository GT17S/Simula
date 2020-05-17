#ifndef __HH_MANAGER__
#define __HH_MANAGER__


#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Data.hh"
#include "Graphe.hh"

class ThreadManager : QObject
{
	Q_OBJECT
private:
	std::vector<Data*> MovingData;
	std::vector<std::thread> WorkingThreads;
	std::map<std::string, std::mutex*> mutexmap;	

public:
	ThreadManager();
	~ThreadManager();

	void initStation();

	void sendConcurrent(int i);
	void joinall();

public slots:
 	void envoieD(){};

};

#endif