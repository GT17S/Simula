#include "ThreadManager.hh"


ThreadManager::ThreadManager(){

}


ThreadManager::~ThreadManager(){
	MovingData.clear();
	WorkingThreads.clear();

}
void ThreadManager::sendConcurrent(int i){

}

void ThreadManager::joinall(){
	for (unsigned int i = 0; i < WorkingThreads.size(); ++i)
	{
		if(WorkingThreads[i].joinable())
			WorkingThreads[i].join();
	}
}

