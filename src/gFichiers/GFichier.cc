#include "GFichier.hh"

bool verifier_schema(QFile *fichier_xml){

    return false;
}

QFile * ouvrirlXml(QString nomFichier, QIODevice::OpenMode mode){
    QFile * fichier = new QFile(nomFichier);
    if(! fichier->open(mode)){
        fichier->close();
        return nullptr;
    }
    return fichier;
}

void lireXml(QString nomFichier, EspaceTravail * espaceTravail){
    Graphe * graphe = Graphe::get();
    graphe->~Graphe();

    QFile * fichier = ouvrirlXml(nomFichier, QIODevice::ReadOnly);
    if(!fichier){
        // erreur

        //std::cout << "erreur lecture "<<std::endl;
        espaceTravail->showDialogError("Erreur de lecture du fichier!");
        return;
    }

    // if(! verifier_schema(fichier))
    //     return;

    QDomDocument document;
    if(!document.setContent(fichier)){
        // erreur parser

        //std::cout << "erreur parser "<<std::endl;
        espaceTravail->showDialogError("Erreur parser fichier");
        return;
    }
    //Simulateur
    QDomElement root = document.documentElement();
    QDomNode equipements = root.firstChild();
    QDomNode noeuds = equipements.firstChild();

    QDomNode noeud = noeuds.firstChild();
    while(!noeud.isNull()){
        QDomElement ne = noeud.toElement();
        Noeud * n;
        NoeudG * nG;
        QString type = ne.toElement().attribute("type");
        if(type.compare("STATION", Qt::CaseInsensitive) == 0){
            nG = new StationG(espaceTravail);
            n  = new Station(dynamic_cast<StationG*>(nG));
        }
        else if(type.compare("ROUTEUR", Qt::CaseInsensitive) == 0){
            nG = new RouteurG(espaceTravail);
            n=   new Routeur(dynamic_cast<RouteurG*>(nG));
        }
        else if(type.compare("SWITCH", Qt::CaseInsensitive) == 0){
            nG = new SwitchG(espaceTravail);
            n = new Switch(dynamic_cast<SwitchG*>(nG));
        }
        else if(type.compare("HUB", Qt::CaseInsensitive) == 0){
            nG = new HubG(espaceTravail);
            n =  new Hub(dynamic_cast<HubG*>(nG));
        }

        n->setIdNoeud(ne.attribute("id").toInt());
        n->setNbPort(ne.attribute("nbPort").toInt());
        QDomNode element = noeud.firstChild(); //position
        QPointF position;
        position.setX(element.toElement().attribute("x").toDouble());
        position.setY(element.toElement().attribute("y").toDouble());
        espaceTravail->addNoeud(nG, position);
        element = element.nextSibling(); //nom
        n->setNom(element.toElement().text().toStdString());
        element = element.nextSibling(); // Interfaces
        QDomNode interface = element.firstChild(); // premiere interface
        int i = 0;
        while(!interface.isNull()){
            QDomElement element = interface.firstChild().toElement(); //nomInterface
            InterfaceFE * ife = n->getInterface(i);
            ife->setNomInterface(element.text().toStdString());
            element = element.nextSiblingElement(); // adresseIP
            ife->setAdresseIP(element.text().toStdString());
            element = element.nextSiblingElement(); // adresseRes
            ife->setAdresseRes(element.text().toStdString());
            element = element.nextSiblingElement(); // masque
            ife->setMasque(element.text().toStdString());
            //element = element.nextSiblingElement(); // mac
            //ife->setAdresseMac(element.text().toStdString());
            i++;
            interface = interface.nextSibling();
        }
        element = element.nextSibling(); // Table de routage
        QDomNode route = element.firstChild(); // premiere route
        while(!route.isNull()){
            QDomElement element = route.firstChild().toElement(); // adresseRes
            Route * r = new Route();
            r->adresseReseau = element.text().toStdString();
            element = element.nextSiblingElement(); // masque
            r->masque = element.text().toStdString();
            element = element.nextSiblingElement(); //passerelle
            r->passerelle = element.text().toStdString();
            n->setTableRoutage(r);

            route = route.nextSibling();
        }
        noeud = noeud.nextSibling();
    }

    QDomNode cables = noeuds.nextSibling();
    QDomNode cable = cables.firstChild();
    while(!cable.isNull()){
        CableG * cG = new CableG();
        Cable * c = new Cable(cG);
        c->setId(cable.toElement().attribute("id").toInt());
        cableT type = static_cast<cableT>(cable.toElement().attribute("type").toInt());
        c->setType(type);
        QDomElement element = cable.firstChild().toElement(); // debitMax
        c->setDebitMax(element.text().toInt());
        element = element.nextSiblingElement(); // debitAcc
        c->setDebitAcc(element.text().toFloat());
        element = element.nextSiblingElement(); // latence
        c->setLatence(element.text().toFloat());
        element = element.nextSiblingElement(); // MTU
        c->setMTU(element.text().toInt());
        element = element.nextSiblingElement(); // Noeud A
        int interface1 = element.attribute("interface").toInt();
        Noeud * noeudA = Graphe::getSommets()[element.text().toInt()];
        NoeudG * noeudAG = noeudA->getParent();
        element = element.nextSiblingElement(); // Noeud B
        int interface2 = element.attribute("interface").toInt();
        Noeud * noeudB = Graphe::getSommets()[element.text().toInt()];
        NoeudG * noeudBG = noeudB->getParent();
        noeudAG->addLine(cG, true);
        noeudAG->moveCable(noeudAG->pos());

        noeudBG->addLine(cG, false);
        noeudBG->moveCable(noeudBG->pos());
        cG->setZValue(-1);
        espaceTravail->getScene()->addItem(cG);
        //std::cout << noeudB->getNom()<<" "<<interface1<<" "<<noeudB->getNom()<<" "<<interface2<<std::endl;
        c->connexionNoeuds(noeudA, interface1, noeudB, interface2);

        cable = cable.nextSibling();
    }

    fichier->close();

}

void ecrireXml(QString nomFichier){
    // Ouvrir fichier pour ecriture
    QFile * fichier = ouvrirlXml(nomFichier, QIODevice::WriteOnly);
    if(!fichier){
        // erreur
        return;
    }

    QDomDocument document;
    QDomElement root = document.createElement("Simulateur");
    document.appendChild(root);

    QDomElement equipements = document.createElement("Equipements");
    root.appendChild(equipements);

    QDomElement noeuds = document.createElement("Noeuds");
    equipements.appendChild(noeuds);

    for(Noeud * n : Graphe::getSommets()){
        QDomElement noeud = document.createElement("Noeud");
        noeuds.appendChild(noeud);

        typeNoeud typeEnum = n->getTypeNoeud();

        QString type;
        if(typeEnum == STATION)
            type = "STATION";
        else if(typeEnum == ROUTEUR)
            type = "ROUTEUR";
        else if(typeEnum == SWITCH)
            type = "SWITCH";
        else if(typeEnum == HUB)
            type = "HUB";

        noeud.setAttribute("type", type);
        noeud.setAttribute("id", n->getIdNoeud());
        noeud.setAttribute("nbPort", n->getNbPort());

        NoeudG *np = n->getParent();
        if(np){
            QDomElement position = document.createElement("Position");
            noeud.appendChild(position);
            position.setAttribute("x", np->pos().x());
            position.setAttribute("y", np->pos().y());

        }
        QDomElement nom = document.createElement("nom");
        nom.appendChild(document.createTextNode(QString::fromStdString(n->getNom())));
        noeud.appendChild(nom);

        QDomElement interfaces = document.createElement("Interfaces");
        noeud.appendChild(interfaces);

        for(InterfaceFE * i : n->getInterfaces()){
            QDomElement interface = document.createElement("Interface");
            interfaces.appendChild(interface);

            QDomElement nomInterface = document.createElement("nomInterface");
            nomInterface.appendChild(document.createTextNode(QString::fromStdString(i->getNomInterface())));
            interface.appendChild(nomInterface);

            QDomElement adresseIP = document.createElement("adresseIP");
            adresseIP.appendChild(document.createTextNode(QString::fromStdString(i->getAdresseIP())));
            interface.appendChild(adresseIP);

            QDomElement adresseRes = document.createElement("adresseRes");
            adresseRes.appendChild(document.createTextNode(QString::fromStdString(i->getAdresseRes())));
            interface.appendChild(adresseRes);

            QDomElement masque = document.createElement("masque");
            masque.appendChild(document.createTextNode(QString::fromStdString(i->getMasque())));
            interface.appendChild(masque);

            QDomElement adresseMac = document.createElement("adresseMac");
            adresseMac.appendChild(document.createTextNode(QString::fromStdString(i->getAdresseMac())));
            interface.appendChild(adresseMac);

        }

        QDomElement tableRoutage = document.createElement("TableRoutage");
        noeud.appendChild(tableRoutage);
        for(Route * r : n->getTableRoutage()){
            QDomElement route = document.createElement("Route");
            tableRoutage.appendChild(route);

            QDomElement adresseRes = document.createElement("adresseRes");
            adresseRes.appendChild(document.createTextNode(QString::fromStdString(r->adresseReseau)));
            route.appendChild(adresseRes);


            QDomElement masque = document.createElement("masque");
            masque.appendChild(document.createTextNode(QString::fromStdString(r->masque)));
            route.appendChild(masque);
            QDomElement adresseP = document.createElement("adressePasserelle");
            adresseP.appendChild(document.createTextNode(QString::fromStdString(r->passerelle)));
            route.appendChild(adresseP);
        }

    }

    QDomElement cables = document.createElement("Cables");
    equipements.appendChild(cables);

    vector<vector<Cable*>> matrice = Graphe::getMatrice();

    int size_m = matrice.size();
    for (int i = 1; i < size_m; i++) {
        for (int j = 0; j < i; j++) {
            if(matrice[i][j]){
                Cable * c = matrice[i][j];
                QDomElement cable = document.createElement("Cable");
                cables.appendChild(cable);

                cable.setAttribute("id", c->getId());
                cable.setAttribute("type", c->getType());

                QDomElement debitMax = document.createElement("debitMax");
                debitMax.appendChild(document.createTextNode(QString::number(c->getDebitMax())));
                cable.appendChild(debitMax);

                QDomElement debitAcc = document.createElement("debitAcc");
                debitAcc.appendChild(document.createTextNode(QString::number(c->getDebitAcc())));
                cable.appendChild(debitAcc);

                QDomElement latence = document.createElement("latence");
                latence.appendChild(document.createTextNode(QString::number(c->getLatence())));
                cable.appendChild(latence);


                QDomElement MTU = document.createElement("MTU");
                MTU.appendChild(document.createTextNode(QString::number(c->getMTU())));
                cable.appendChild(MTU);

                QDomElement noeudA = document.createElement("NoeudA");
                noeudA.setAttribute("interface", c->getExt1()->interface);
                noeudA.appendChild(document.createTextNode(QString::number(c->getExt1()->noeud->getIdNoeud())));
                cable.appendChild(noeudA);

                QDomElement noeudB = document.createElement("NoeudB");
                noeudB.setAttribute("interface", c->getExt2()->interface);
                noeudB.appendChild(document.createTextNode(QString::number(c->getExt2()->noeud->getIdNoeud())));
                cable.appendChild(noeudB);
            }
        }
    }

    QTextStream output(fichier);
    output << document.toString();

    fichier->close();

}
/*!
         * \brief Serialise un graphe dans un fichier DOT
         * Ecrit tout d'abord l'entête de graphe puis les sommets enfin les arcs avec des paramètres de couleur de formes differents
         * \param filename nom du fichier d'entrée
         * \param graphe à ecrire dans le fichier
*/

void ecrireDot(std::string filename){
    //Verifier les attributs
    //assert(graphe);
    //On crée le fichier de destination
    if(filename.empty()){
        filename.assign("autosave.dot");
    }else{
        filename += ".dot";
    }

    //Ouvrir le fichier en écriture
    std::ofstream outfile(filename, std::ofstream::out);
    if(outfile.is_open()){
        //On écrit dans le fichier, l'en tête d'un fichier dot
        outfile << "graph G{ " << std::endl;
        outfile << "rankdir=LR;" << std::endl << "splines=line;" << std::endl << "graph[bgcolor=lightyellow2,splines=true];" << std::endl << "node[ color=yellow, style=filled, shape=polygon, sides=6, fontname=\"Verdana\"] ;" << std::endl;
        //On ecrit les noeuds
        auto nodes = Graphe::getSommets();
        for (auto i = 0; i < (int)nodes.size(); ++i)
        {
            if(dynamic_cast<Routeur*>(nodes[i]))
                outfile << i << " [shape=box , color=red , fontcolor=black , label = \" " << nodes[i]->getNom() << "\" ] ;";
            if(dynamic_cast<Switch*>(nodes[i]) || dynamic_cast<Hub*>(nodes[i]))
                outfile << i << " [shape=ellipse , color=blue , fontcolor=black , label = \" " << nodes[i]->getNom() << "\" ] ;";
            if(dynamic_cast<Station*>(nodes[i]))
                outfile << i << " [shape=octagon , color=green , fontcolor=black , label = \" " << nodes[i]->getNom() << "\" ] ;";

            outfile << std::endl;
        }

        //Ecrire les arcs
        auto  mat = Graphe::getMatrice();
        for (auto i = 0; i < (mat.size()); ++i)
        {
            for (auto j = 0; j < (mat[i].size()); ++j)
            {
                if(mat[i][j]){
                    outfile << i << "--" << j << "[label =\" " << mat[i][j]->getLatence() <<"\" , weight ="  <<  mat[i][j]->getDebitAcc() << "  ,  color =\"green\" , style=dashed ] ;";
                    outfile << std::endl;
                }
            }
        }

        outfile << "}";
        outfile.flush();
        outfile.close();
    }else{
        std::cerr << "Le fichier" + filename + " n'a pas pu être ouvert" << std::endl;
        outfile.close();
        return;
    }
}
