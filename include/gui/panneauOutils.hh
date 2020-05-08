#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>
#include <MyQWidget.hh>
class PanneauOutils : public QToolBar, public MyQWidget{
	Q_OBJECT


public:
    PanneauOutils();
	virtual ~PanneauOutils(){};

    void showInfos() override;
public slots:
	void nouveauFichier();
	void ouvrirFichier();
	void sauvegarderFichier();
	void exporterFichier();
	void demarrerSimulation();
	void pauseSimulation();
	void arreterSimulation();
	void resetSimulation();
	void changeMode();
	void envoieD();



};

#endif
