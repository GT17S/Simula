#include "../../include/gCongestion/congestionOutil.hh"

float CalculRTT(Congestion *g){
	if(g->getCwnd() == 1)
		return baseRTT;
	else
		return (float) (1.0f - alpha) * g->getBaseRtt() + (alpha * baseRTT);
}

float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data, int id1, int id2){
	float latency = 0.0f;
	latency += 2*congestion->getBaseRtt() + (gr)

	for (int i = 0; i < count; ++i)
	{
		/* code */
	}

}
