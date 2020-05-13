#ifndef GFICHIER_H
#define GFICHIER_H

#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Graphe.hh"


class Graphe;

bool verifier_schema(QFile * fichier_xml);

QFile * ouvrirlXml(QString nomfichier, QIODevice::OpenMode mode);

void lireXml(QString nomfichier, Graphe *graphe);

void ecrireXml(QString fichier, Graphe * graphe);


/*!
         * \brief Serialise un graphe dans un fichier DOT
         * Ecrit tout d'abord l'entête de graphe puis les sommets enfin les arcs avec des paramètres de couleur de formes differents
         * \param filename nom du fichier d'entrée
         * \param graphe à ecrire dans le fichier
*/
void ecrireDot(std::string filename, Graphe* graphe);


#endif
