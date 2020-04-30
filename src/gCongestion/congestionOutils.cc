#include "../../include/gCongestion/congestionOutil.hh"

float CalculRTT(Congestion *g){
	if(g->getCwnd() == 1)
		return baseRTT;
	else
		return (float) (1.0f - alpha) * g->getBaseRtt() + (alpha * baseRTT);
}

float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data){
	float latency = 0.0f;
}
