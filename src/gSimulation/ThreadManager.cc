#include "ThreadManager.hh"


ThreadManager::ThreadManager(gSimulation* _gestionnaire) : QObject (nullptr) {
	mutexmap["Cable"] = new std::mutex();
	gestionnaire = _gestionnaire;
}


ThreadManager::~ThreadManager(){
	joinall();
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
        workingStations[i]->setRun(false);
      if(WorkingThreads[i].joinable())
			WorkingThreads[i].join();
	}

    WorkingThreads.clear();
    workingStations.clear();
    std::cout <<  std::endl << "Destruction :" << WorkingThreads.size() <<  std::endl  << workingStations.size() << std::endl;
}

void ThreadManager::removeStation(NoeudG* n){
       std::cout << "Je retire une station" << std::endl;
       auto tmp = n->getChild();

       for (unsigned int i = 0; i < workingStations.size(); i++){
               if ( workingStations[i] == tmp){
                    workingStations[i]->setRun(false);
                    if(WorkingThreads[i].joinable())
                          WorkingThreads[i].join();

                    WorkingThreads.erase(WorkingThreads.begin() +i);
                    workingStations.erase(workingStations.begin()+i);
              }
               }
       std::cout << "Destrcutio d'un seul thread: " <<WorkingThreads.size() << "    "  << workingStations.size() << std::endl;

}


// Ajouté par Massi
bool ThreadManager::findWorker ( Station * s)	{
    bool found = false;
    for (unsigned int i = 0; i < workingStations.size() && !found; i++)
		if ( workingStations[i] == s)
			found = true;
	return found;
}


// Ajouté par Massi
void ThreadManager::createWorker ( NoeudG * n)	{
	Station * s = dynamic_cast <Station *> (n->getChild());
	if ( s == nullptr) return;
	if ( findWorker ( s)) return;
	WorkingThreads.push_back(std::thread(&Station::mainlocal, s, mutexmap["Cable"], gestionnaire));	
	workingStations.push_back(s);

    std::cout << "Création: " <<WorkingThreads.size() << "    "  << workingStations.size() << std::endl;

}
