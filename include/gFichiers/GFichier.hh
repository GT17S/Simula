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

class Graphe;

bool verifier_schema(QFile * fichier_xml);

QFile * ouvrirlXml(QString nomfichier, QIODevice::OpenMode mode);

void lireXml(QString nomfichier);

void ecrireXml(QString fichier);

void ecrireDot(std::string filename);


#endif
