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
/*!
 * \brief verifier_schema
 * \param fichier_xml : ficher a lire
 * \return bool : si fichier est valide
 */
bool verifier_schema(QFile * fichier_xml);
/*!
 * \brief ouvrirlXml
 * \param nomfichier : le nom de fichier
 * \param mode :mode d'ouvrir le fichier(lecture ou ecriteur)
 * \return QFile : le fichier
 */

QFile * ouvrirlXml(QString nomfichier, QIODevice::OpenMode mode);
/*!
 * \brief lireXml
 * lecture d'un fichier xml
 * \param nomfichier : le nom de fichier
 */

void lireXml(QString nomfichier);
/*!
 * \brief ecrireXml
 * ecrire dansun  fichier xml
 * \param fichier : le nom de fichier
 */

void ecrireXml(QString fichier);



/*!
         * \brief Serialise un graphe dans un fichier DOT
         * Ecrit tout d'abord l'entête de graphe puis les sommets enfin les arcs avec des paramètres de couleur de formes differents
         * \param filename nom du fichier d'entrée
         * \param graphe à ecrire dans le fichier
*/
void ecrireDot(std::string filename, Graphe* graphe);



#endif
