#include "DataG.hh"
#include "PanneauData.hh"
DataG::DataG  ( Data * d, QWidget* parent) : QTabBar(parent), detail( QIcon("../../ressources/outilsBar/zoomInAction.png"), "",this), left (QIcon("../../ressources/outilsBar/left.jpg"), "",this), right( QIcon("../../ressources/outilsBar/right.jpg"), "",this)    {
	this->curent = 0;
	this->detail.setFixedSize( 30, 30);
	this->left.setFixedSize( 30, 30);
	this->right.setFixedSize( 30, 30);
	connect(&this->detail, SIGNAL(clicked()), this, SLOT(detailPanel()));
	connect(&this->left, SIGNAL(clicked()), this, SLOT(displayLeft()));
	connect(&this->right, SIGNAL(clicked()), this, SLOT(displayRight()));
	this->d = d;
	
	this->send.push_back ( new Data ( new boost::dynamic_bitset<> (*(d->getSeq())), d->getType()));

	this->grid = new QHBoxLayout (this);
	this->addTrame();
	this->predicateData();
	this->grid->addWidget(&this->detail);
	this->grid->addWidget(&this->left);
	this->grid->addWidget(&this->right);

    this->setTabsClosable(true);
}

DataG::~DataG()	{
	this->send.clear();
    qDebug()<<"Destruction DATAG";
}

void DataG::predicateData ()	{
	
    int id_src  = Graphe::noeudFromIp(lireAdresseIp(send[0], 0));
    int id_dest = Graphe::noeudFromIp(lireAdresseIp(send[0], 1));
	vector<Cable *> path;
	vector<int> id_path;
	int ip_dest = id_dest;

	Graphe::genererChemin(id_src, id_src, ip_dest, path, true);
	if ( path.empty())	{
      return;
	}
	int size_p = path.size();
	extremite * destExt;
	Cable * cable;
	Noeud * n = Graphe::get()->getSommets()[id_src];
	for(int i = size_p - 1; i > -1; i--){
		cable = path[i];
		destExt = cable->getInverseExt(n);

		n = destExt->noeud;
		id_path.push_back (n->getIdNoeud());
	}
	std::cout << std::endl;
	int i = 0;
	while ( id_path[i] != id_dest)	{
		 bool found = false;
		Station * s_src = dynamic_cast <Station *> ( Graphe::get()->getSommets()[id_path[i]]);
		Routeur * r_src = dynamic_cast <Routeur *> ( Graphe::get()->getSommets()[id_path[i]]);
		if ( (s_src != nullptr) || (r_src != nullptr))	{
			for (int j = i+1; j < id_path.size() && !found; j++)	{
				Station * s_dest = dynamic_cast <Station *> ( Graphe::get()->getSommets()[id_path[j]]);
				Routeur * r_dest = dynamic_cast <Routeur *> ( Graphe::get()->getSommets()[id_path[j]]);
				if ( s_dest || r_dest)	{
					this->send.push_back ( new Data ( new boost::dynamic_bitset<> (*(send[0]->getSeq())), send[0]->getType()));
					desencapsule_trame (send[send.size()-1]);
					extremite e1; e1.noeud = Graphe::get()->getSommets()[id_path[i]]; e1.interface = 0;
					extremite e2; e2.noeud = Graphe::get()->getSommets()[id_path[j]]; e2.interface = 0;
					encapsule_paquet ( &e1, &e2, send[send.size()-1]);
					i = j;
					found = true;
				}
			}
			if ( !found) i++;
		}
		else
			i++;
	}
	this->send.push_back ( new Data ( new boost::dynamic_bitset<> (*(send[0]->getSeq())), send[0]->getType()));
	desencapsule_trame (send[send.size()-1]);
	this->send.push_back ( new Data ( new boost::dynamic_bitset<> (*(send[send.size()-1]->getSeq())), send[send.size()-1]->getType()));
	desencapsule_paquet (send[send.size()-1]);		
	this->send.push_back ( new Data ( new boost::dynamic_bitset<> (*(send[send.size()-1]->getSeq())), send[send.size()-1]->getType()));
	desencapsule_segment (send[send.size()-1]);	
}

std::string readMessage(Data * d){
    boost::dynamic_bitset<> tmp = *d->getSeq();
	int deb = 0, fin = 0;
	if ( d->getType() == 1) deb = 192;
	if ( d->getType() == 2) deb = 352;
	if ( d->getType() == 3) {
		deb = 464;
		fin = 32;
	}
    // std::cout << tmp << std::endl;
    std::string res = "";
    for (int i = deb; i < (int)tmp.size() - fin; i+=8)    {
        char c = (char)0;
        for ( int j = i%8; j < 8; j++)
            if ( tmp[i+j])
                c = c | ( 1<<(7-j));
        res += c;
    }
    return res;
}

void DataG::detailPanel ()  {
	QGridLayout *gridLayout = new QGridLayout();
	QTextEdit 	*srcMac	 = new QTextEdit ( adresseMac ( send[curent]).c_str()),
				*destMac = new QTextEdit ( adresseMac ( send[curent], 1).c_str()),
				*ethType = new QTextEdit( send[curent]->getType() < 3 ? "n/a" : "Ethernet"),
				*fcs	 = new QTextEdit ( send[curent]->getType() < 3 ? "n/a" : QString ("%1").arg(lireFCS (send[curent]))),
				*len	 = new QTextEdit ( send[curent]->getType() < 2 ? "n/a" : QString ("%1").arg(lireLongueurPaquet (send[curent]))),
				*ipid	 = new QTextEdit ( send[curent]->getType() < 2 ? "n/a" : QString ("%1").arg(lireIdIp (send[curent]))),
				*offset	 = new QTextEdit ( send[curent]->getType() < 2 ? "n/a" : QString ("%1").arg(lireOffsetPaquet (send[curent]))),
				*cs		 = new QTextEdit ( send[curent]->getType() < 2 ? "n/a" : QString ("%1").arg(lireSommePaquet (send[curent]))),
				*srcIp	 = new QTextEdit ( send[curent]->getType() < 2 ? "n/a" : lireAdresseIp (send[curent], 0).c_str()),
				*destIp	 = new QTextEdit ( send[curent]->getType() < 2 ? "n/a" : lireAdresseIp (send[curent], 1).c_str()),
				* pSrc	 = new QTextEdit ( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (send[curent], 0))),
				* pDest	 = new QTextEdit ( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (send[curent], 1))),
				* nSeq	 = new QTextEdit ( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lireNumeroSequence (send[curent]))),
				* nAck	 = new QTextEdit ( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lireNumeroAck (send[curent]))),
				* fen	 = new QTextEdit ( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lireFenetre (send[curent]))),
				* tcs	 = new QTextEdit ( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lireSommeSegment (send[curent]))),
				* donne	 = new QTextEdit ( readMessage ( send[curent]).c_str()),
				* tFlag	 = new QTextEdit (findTcpFlags(send[curent]).c_str());


	srcMac->setReadOnly(true);
	destMac->setReadOnly(true);
	ethType->setReadOnly(true);
	fcs->setReadOnly(true);
	len->setReadOnly(true);
	ipid->setReadOnly(true);
	offset->setReadOnly(true);
	cs->setReadOnly(true);
	srcIp->setReadOnly(true);
	destIp->setReadOnly(true);
	pSrc->setReadOnly(true);
	pDest->setReadOnly(true);
	nSeq->setReadOnly(true);
	nAck->setReadOnly(true);
	fen->setReadOnly(true);
	tcs->setReadOnly(true);
	donne->setReadOnly(true);
	tFlag->setReadOnly(true);



	QLabel 		*type = new QLabel	 ( dataType ( send[curent]).c_str()),
				* ttl = new QLabel ( "TTL : " +( send[curent]->getType() < 2 ? "n/a" : QString ("%1").arg(lireTTL (send[curent])))),
				* flag;
	if ( send[curent]->getType() < 2)
		flag = new QLabel ("Flag : n/f");
	else	{
		if ( lireFlagPaquet(send[curent]) == 2 || lireFlagPaquet(send[curent]) == 3)
			flag = new QLabel ("Flag : df");
		else if (lireFlagPaquet(send[curent]) == 1 || lireFlagPaquet(send[curent]) == 3) 
			flag = new QLabel ("Flag : mf");
		else
			flag = new QLabel ("No Flags");
	}
	flag->setFixedWidth (80);
	
	gridLayout->addWidget( new QLabel("Type :"), 0, 0, 1, 2);
	gridLayout->addWidget( type, 0, 1, 1, 1);
	gridLayout->addWidget( new QLabel("En-tête trame"), 1, 0, 1, 2);
	gridLayout->addWidget( new QLabel("Mac Source"), 2, 0, 1, 1);
	gridLayout->addWidget( srcMac, 2, 1, 1, 4);
	gridLayout->addWidget( new QLabel("Mac destination"), 3, 0, 1, 1);    
	gridLayout->addWidget( destMac, 3, 1, 1, 4);
	gridLayout->addWidget( ethType, 4, 0, 1, 1);
	gridLayout->addWidget( new QLabel ("Données"), 4, 1, 1, 4);
	gridLayout->addWidget( new QLabel ("FCS : "), 5, 0, 1, 1);
	gridLayout->addWidget( fcs, 5, 1, 1, 1);    
	gridLayout->addWidget( new QLabel ("En-tête paquet"), 6, 0, 1, 2);
	gridLayout->addWidget( new QLabel ("Version: IPv4   IHL : 20"), 7, 0, 1, 1);
	gridLayout->addWidget( new QLabel ("Service : n/a"), 7, 1, 1, 1);
	gridLayout->addWidget( new QLabel ("Longueur : "), 7, 2, 1, 1);
	gridLayout->addWidget( len, 7, 3, 1, 2);
	gridLayout->addWidget( new QLabel("Ip Id : "), 8, 0, 1, 1);
	gridLayout->addWidget( ipid, 8, 1, 1, 1);
	gridLayout->addWidget( flag, 8, 2, 1, 1);
	gridLayout->addWidget( new QLabel("Offset : "), 8, 3, 1, 1);
	gridLayout->addWidget( offset, 8, 4, 1, 1);
	gridLayout->addWidget( ttl, 9, 0, 1, 1);
	gridLayout->addWidget( new QLabel ("Protocole : TCP"), 9, 1, 1, 1);
	gridLayout->addWidget( new QLabel ("Checksum : "), 9, 2, 1, 1);
	gridLayout->addWidget( cs, 9, 3, 1, 2);
	gridLayout->addWidget( new QLabel ("Adresse source : "), 10, 0, 1, 1);
	gridLayout->addWidget( srcIp, 10, 1, 1, 4);
	gridLayout->addWidget( new QLabel ("Adresse destinataire : "), 11, 0, 1, 1);
	gridLayout->addWidget( destIp, 11, 1, 1, 4);
	gridLayout->addWidget( new QLabel ("En-tête segment"), 12, 0, 1, 2);
	gridLayout->addWidget( new QLabel ("Port Source : "), 13, 0, 1, 1);
	gridLayout->addWidget( pSrc, 13, 1, 1, 1);
	gridLayout->addWidget( new QLabel ("Port Destination : "), 13, 2, 1, 1);
	gridLayout->addWidget( pDest, 13, 3, 1, 1);
	gridLayout->addWidget( new QLabel ("Numéro de Séquence"), 14, 0, 1, 3);
	gridLayout->addWidget( nSeq, 14, 1, 1, 3);
	gridLayout->addWidget( new QLabel ("Numéro ACK"), 15, 0, 1, 3);
	gridLayout->addWidget( nAck, 15, 1, 1, 3);
	gridLayout->addWidget( new QLabel("THL : 20  Reservé : n/a"), 16, 0, 1, 3);
	gridLayout->addWidget( tFlag, 16, 1, 1, 1);
	gridLayout->addWidget( new QLabel ("Fenetre : "), 16, 2, 1, 1);
	gridLayout->addWidget( fen, 16, 3, 1, 2);
	gridLayout->addWidget( new QLabel ("Checksum : "), 17, 0, 1, 1);
	gridLayout->addWidget( tcs, 17, 1, 1, 1);
	gridLayout->addWidget( new QLabel ("Pointeur de données urgentes : n/a"), 17, 2, 1, 2);
	gridLayout->addWidget( new QLabel ("Options : n/a"), 18, 0, 1, 1);
	gridLayout->addWidget( new QLabel ("Donnée"), 19, 0, 1, 2);
	gridLayout->addWidget( donne, 20, 0, 1, 4);

	QWidget *w = new QWidget();
	gridLayout->setVerticalSpacing (0);
	w->setLayout(gridLayout);
	w->setWindowTitle("Détail Data");
	w->setFixedSize( 600, 550);
	w->show();
}

void DataG::addMessage ()	{
	QLabel * m = new QLabel( readMessage ( send[curent]).c_str());
	this->grid->addWidget( m);		
}

void DataG::addSegment ()	{
	QLabel * src = new QLabel( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (send[curent], 0)));
	QLabel * dest = new QLabel( send[curent]->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (send[curent], 1)));
	src->setMinimumWidth(50);
	src->setMaximumWidth(50);
	dest->setMinimumWidth(50);
	dest->setMaximumWidth(50);
	this->grid->addWidget( src);		
	this->grid->addWidget( dest);		
	this->addMessage ();
}

void DataG::addPaquet ()	{
	QLabel * src = new QLabel( send[curent]->getType() < 2 ? "n/a" : lireAdresseIp (send[curent], 0).c_str());
	QLabel * dest = new QLabel( send[curent]->getType() < 2 ? "n/a" : lireAdresseIp (send[curent], 1).c_str());
	src->setMinimumWidth(115);
	src->setMaximumWidth(115);
	dest->setMinimumWidth(115);
	dest->setMaximumWidth(115);		
	this->grid->addWidget( src);		
	this->grid->addWidget( dest);
	this->addSegment ();
}

void DataG::addTrame ()	{
	QLabel * src = new QLabel( send[curent]->getType() < 3 ? "n/f" : adresseMac ( send[curent], 0).c_str());
	QLabel * dest = new QLabel(  send[curent]->getType() < 3 ? "n/f" : adresseMac ( send[curent], 1).c_str());
	src->setMinimumWidth(105);
	src->setMaximumWidth(105);
	dest->setMinimumWidth(105);
	dest->setMaximumWidth(105);		
	
	this->grid->addWidget( src);		
	this->grid->addWidget( dest);		
	this->addPaquet ();
}

void DataG::updatePanel()	{
	delete this->grid;
	this->grid = new QHBoxLayout(this);
	this->addTrame();
	this->grid->addWidget(&this->detail);
	this->grid->addWidget(&this->left);
	this->grid->addWidget(&this->right);	
}

void DataG::displayLeft()	{
	if ( this->curent > 0)	{
		this->curent -= 1;
		this->updatePanel();
	}
}

void DataG::displayRight()	{
	if ( this->curent < (this->send.size()-1))	{
		this->curent += 1;
		this->updatePanel();
	}
}


