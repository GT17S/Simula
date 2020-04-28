#ifndef CABLE_H
#define CABLE_H


/*!
 * \file Cable.h
 * \brief Cable
 * \author Nadjibian
 * \version 0.1
 */


#include "Noeud.hh"
#include<string>


#ifndef CABLET_H
#define CABLET_H
/*!
 * \enum cableT
 * \brief Type du cable
 */

typedef enum {
  DROIT =0, /*!< Cable droit */
  CROISE /*!< Cable croisé */
} cableT;

#endif
/*!
 * \class Cable
 * \brief La classe Cable représentant un Cable.
 */

class Noeud;

class Cable{
private:
  static int nbCables; /*!< Nombre de cables */
  static int i; /*!< Générateur des ID */

  int id; /*!< Identificateur du cable */
  int debitMax; /*!< Débit maximum du câble */
  float debitAcc; /*!< Débit actuel du câble */
  float latence; /*!< Latence du cable */ //refrence to congestion
  int MTU; /*! < Taille maximale du paquet transmis */
  cableT type; /*!< Type du cable */
  Noeud* ext1; /*!< Le Noeud à l'extremitie 1 */
  Noeud* ext2; /*!< Le Noeud à l'extremitie 2*/
public:

  /*!
   *
   * \brief Construceur
   * Constructeur de la classe Cable
   * \param type : voir #type
   * \param debitMax : voir #debitMax
   */
  Cable(cableT type = DROIT, int debitMax = 100, int MTU = 1500);

  /*!
   * \brief Destructeur
   * Destructeur de la classe noeud
   */
  ~Cable();

  /*!
   * \brief getId
   * \return Identificateur du cable (int)
   */
  int getId() const{ return id;}
  /*!
   * \brief getDebitMax
   * \return Débit maximum du câble (int)
   */
  int getDebitMax() const{return debitMax;}
  /*!
   * \brief getLatence
   * \return La latence sur un cable (float)
   */
  float getLatence() const;
  /*!
   * \brief getDebitAcc
   * \return Le débit actuel (float)
   */
  float getDebitAcc() const{ return debitAcc;}
  /*!
   * \brief getMTU
   * \return voir #MTU
   */
  int getMTU(){return MTU;}
  /*!
   * \brief getType
   * \return Le type du cable (cableT)
   */
  cableT getType() const{return type;}

  /*!
   * \brief getExt1
   * \return Le premier Noeud a l'extremitie (Noeud)
   */
  Noeud * getExt1() const{return ext1;}
  /*!
   * \brief getExt2
   * \return Le deuxième Noeud a l'extremitie (Noeud)
   */
  Noeud * getExt2() const{return ext2;}


  /*!
   * \brief setNbCables
   * Modifier le nombre de cables
   * \param nbCable : nombre de cabls (int).
   */
  static void setNbCables(int nbCable);
  /*!
   * \brief setId
   * Modifier l'identificateur du noeud
   * \param idCable : id du cable (int) doit être unique.
   */
  void setId(int idCable);
  /*!
   * \brief setDebitMax
   * Modifier Débit maximum du câble
   * \param Débit maximum du câble : débit maximum du cable (int).
   */
  void setDebitMax(int debitMax);
  /*!
   * \brief setDebitAcc
   * Modifier le débit actuel
   * \param debitAcc : débit actuel (float).
   */
  void setDebitAcc(float debitAcc);
  /*!
   * \brief setLatence
   * Modifier la latence
   * \param latence : la latence du cable.
   */
  void setLatence(float latence);
  /*!
   * \brief setType
   * Modifier le type du cable
   * \param type : type du cable (cableT).
   */
  void setType(const cableT &type);
  /*!
   * \brief setMTU
   * Modifier la taille maximale du paquet transmis par le cable, #MTU
   * \param MTU
   */
  void setMTU(int MTU);
  /*!
   * \brief setExt1
   * Modifier le noeud a l'extremitie
   * \param noeud1 : noeud (Noeud).
   */
  void setExt1(Noeud *noeud1);
  /*!
   * \brief setExt2
   * Modifier le noeud a l'extremitie
   * \param noeud2 : noeud (Noeud).
   */
  void setExt2(Noeud *noeud1);

  /*!
   * \brief estBienConnecte
   * Méthode qui permet de vérifier si les deux noeuds sont bien connectés
   * \return vrai si bien connécté, faux sinon.
   */
  bool estBienConnecte();
  /*!
   * \brief connexionNoeuds
   * Etablir une connexion entre, deux noeuds avec le cable
   * \param N1 : voir #ext1
   * \param interface1 : numero de l'interface dans N1
   * \param N2 : voir #ext2
   * \param interface2 : numero de l'interface dans N2
   * \return vrai si la connexion est établie, faux sinon (Destruction du cable)
   */
  bool connexionNoeuds(Noeud * N1, int interface1, Noeud * N2, int interface2);
};
#endif
