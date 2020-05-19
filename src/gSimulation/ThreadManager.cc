#include "ThreadManager.hh"


ThreadManager::ThreadManager(gSimulation* _gestionnaire): QObject(){
	mutexmap["Cable"] = new std::mutex();
	gestionnaire = _gestionnaire;
}


ThreadManager::~ThreadManager(){
	MovingData.clear();
	WorkingThreads.clear();

}

void ThreadManager::initStation(){
	
	for(auto item : Graphe::get()->getSommets()){
		Station* tmp = dynamic_cast<Station*>(item);
		if(tmp){
			std::cout << "Initialisation du thread de la station "<< item->getIdNoeud() << std::endl;
			//auto controleur = tmp->getControleur();
			WorkingThreads.push_back(std::thread(&Station::mainlocal,tmp, mutexmap["Cable"], gestionnaire));
		}
	}
}

void ThreadManager::joinall(){
	for (unsigned int i = 0; i < WorkingThreads.size(); ++i)
	{
		if(WorkingThreads[i].joinable())
			WorkingThreads[i].join();
	}
}

