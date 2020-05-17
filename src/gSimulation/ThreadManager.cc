#include "ThreadManager.hh"


ThreadManager::ThreadManager(): QObject(){
	mutexmap["Cable"] = new std::mutex();
}


ThreadManager::~ThreadManager(){
	MovingData.clear();
	WorkingThreads.clear();

}
void ThreadManager::sendConcurrent(int i){

}

void ThreadManager::initStation(){
	for(auto item : Graphe::get()->getSommets()){
		Station* tmp = dynamic_cast<Station*>(item);
		if(tmp){
			WorkingThreads.push_back(std::thread(&Station::mainlocal,tmp, mutexmap["Cable"]));
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

