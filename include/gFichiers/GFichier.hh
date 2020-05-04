#ifndef GFICHIER_H
#define GFICHIER_H

#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "Graphe.hh"


bool verifier_schema(QFile * fichier_xml);

QFile * ouvrirlXml(QString nomfichier, QIODevice::OpenMode mode);

void lireXml(QString nomfichier, Graphe *graphe);

void ecrireXml(QString fichier, Graphe * graphe);


#endif
