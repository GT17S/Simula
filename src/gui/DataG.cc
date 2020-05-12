#include "DataG.hh"

DataG::DataG  ( Data * d, QWidget* parent) : QTabBar(parent), detail( QIcon("../../ressources/search.png"), "",this), grid(this)    {

	this->detail.setFixedSize( 30, 30);
	connect(&this->detail, SIGNAL(clicked()), this, SLOT(detailPanel()));
	this->d = d;
	this->addTrame();
	this->grid.addWidget(&this->detail);
}

void DataG::detailPanel ()  {
	QGridLayout *gridLayout = new QGridLayout();
	QTextEdit 	*srcMac	 = new QTextEdit ( adresseMac ( this->d).c_str()),
				*destMac = new QTextEdit ( adresseMac ( this->d, 1).c_str()),
				*ethType = new QTextEdit( this->d->getType() < 3 ? "n/a" : "Ethernet"),
				*fcs	 = new QTextEdit ( this->d->getType() < 3 ? "n/a" : QString ("%1").arg(lireFCS (this->d))),
				*len	 = new QTextEdit ( this->d->getType() < 2 ? "n/a" : QString ("%1").arg(lireLongueurPaquet (this->d))),
				*ipid	 = new QTextEdit ( this->d->getType() < 2 ? "n/a" : QString ("%1").arg(lireIdIp (this->d))),
				*offset	 = new QTextEdit ( this->d->getType() < 2 ? "n/a" : QString ("%1").arg(lireOffsetPaquet (this->d))),
				*cs		 = new QTextEdit ( this->d->getType() < 2 ? "n/a" : QString ("%1").arg(lireSommePaquet (this->d))),
				*srcIp	 = new QTextEdit ( this->d->getType() < 2 ? "n/a" : lireAdresseIp (this->d, 0).c_str()),
				*destIp	 = new QTextEdit ( this->d->getType() < 2 ? "n/a" : lireAdresseIp (this->d, 1).c_str()),
				* pSrc	 = new QTextEdit ( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (this->d, 0))),
				* pDest	 = new QTextEdit ( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (this->d, 1))),
				* nSeq	 = new QTextEdit ( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lireNumeroSequence (this->d))),
				* nAck	 = new QTextEdit ( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lireNumeroAck (this->d))),
				* fen	 = new QTextEdit ( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lireFenetre (this->d))),
				* tcs	 = new QTextEdit ( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lireSommeSegment (this->d))),
				* donne	 = new QTextEdit ( showMessage ( this->d).c_str()),
				* tFlag	 = new QTextEdit (findTcpFlags(this->d).c_str());


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



	QLabel 		*type = new QLabel	 ( dataType ( this->d).c_str()),
				* ttl = new QLabel ( "TTL : " +( this->d->getType() < 2 ? "n/a" : QString ("%1").arg(lireTTL (this->d)))),
				* flag;
	if ( this->d->getType() < 2)
		flag = new QLabel ("Flag : n/f");
	else	{
		if ( lireFlagPaquet(this->d) == 2 || lireFlagPaquet(this->d) == 3)
			flag = new QLabel ("Flag : df");
		else if (lireFlagPaquet(this->d) == 1 || lireFlagPaquet(this->d) == 3) 
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

std::string messageClaire ( boost::dynamic_bitset<> seq)	{
	
	std::cout << seq << std::endl;
	std::string res = "";
	for (int i = 0; i < (int)seq.size(); i+=8)	{
		char c = (char)0;
		for ( int j = i%8; j < 8; j++)	
			if ( seq[i+j])
				c = c | ( 1<<(7-j));
		res += c;
	}
	return res;
}

void DataG::addMessage ()	{
	QLabel * m = new QLabel( showMessage ( this->d).c_str());
	this->grid.addWidget( m);		
}

void DataG::addSegment ()	{
	QLabel * src = new QLabel( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (this->d, 0)));
	QLabel * dest = new QLabel( this->d->getType() < 1 ? "n/a" : QString ("%1").arg(lirePortTcp (this->d, 1)));
	src->setMinimumWidth(50);
	src->setMaximumWidth(50);
	dest->setMinimumWidth(50);
	dest->setMaximumWidth(50);
	this->grid.addWidget( src);		
	this->grid.addWidget( dest);		
	this->addMessage ();
}

void DataG::addPaquet ()	{
	QLabel * src = new QLabel( this->d->getType() < 2 ? "n/a" : lireAdresseIp (this->d, 0).c_str());
	QLabel * dest = new QLabel( this->d->getType() < 2 ? "n/a" : lireAdresseIp (this->d, 1).c_str());
	src->setMinimumWidth(115);
	src->setMaximumWidth(115);
	dest->setMinimumWidth(115);
	dest->setMaximumWidth(115);		
	this->grid.addWidget( src);		
	this->grid.addWidget( dest);
	this->addSegment ();
}

void DataG::addTrame ()	{
	QLabel * src = new QLabel( d->getType() < 3 ? "n/f" : adresseMac ( this->d, 0).c_str());
	QLabel * dest = new QLabel(  d->getType() < 3 ? "n/f" : adresseMac ( this->d, 0).c_str());
	src->setMinimumWidth(105);
	src->setMaximumWidth(105);
	dest->setMinimumWidth(105);
	dest->setMaximumWidth(105);		
	
	this->grid.addWidget( src);		
	this->grid.addWidget( dest);		
	this->addPaquet ();
}
