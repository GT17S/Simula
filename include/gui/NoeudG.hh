#ifndef __H_NOEUDG__
#define __H_NOEUDG__

#include <QGraphicsItem>
#include <Noeud.hh>


class NoeudG : public virtual Noeud , public QGraphicsItem
{
public:
	NoeudG();
	~NoeudG();
	
};


#endif