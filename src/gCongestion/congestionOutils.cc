#include "congestionOutil.hh"

float CalculRTT(Congestion *g){
	if(g->getCwnd() == 1)
		return baseRTT;
	else
		return (float) (1.0f - alpha) * g->getBaseRtt() + (alpha * baseRTT);
}

float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data, int id1, int id2){
	float latency = 0.0f;
	float sr = (1500 / graphe->getMatrice()[id1][id2]->getDebitAcc());
	float Or = (data->getOriginialStringSize()/graphe->getMatrice()[id1][id2]->getDebitAcc());
	float rtt2 = 2*congestion->getBaseRtt();
	latency += rtt2 + Or;

	for (int i = 0; i < congestion->getCpt(); ++i)
	{
		latency += ( sr + rtt2 - (pow(2.0, congestion->getCpt()-1) * sr));
	}

	return latency;
}
