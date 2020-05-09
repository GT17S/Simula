#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>

class PanneauOutils : public QToolBar{
	Q_OBJECT
public:
    PanneauOutils();
	virtual ~PanneauOutils(){};

public slots:
	void nouveauFichier(){};
	void ouvrirFichier(){};
	void sauvegarderFichier(){};
	void exporterFichier(){};
	void demarrerSimulation(){};
	void pauseSimulation(){};
	void arreterSimulation(){};
	void resetSimulation(){};
	void changeMode(){};
	void envoieD(){};



};

#endif
