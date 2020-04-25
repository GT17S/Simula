#ifndef CABLE_H
#define CABLE_H


/*!
 * \file Cable.h
 * \brief Cable
 * \author Nadjibian
 * \version 0.1
 */


#include "../include/logiqueReseau/Noeud.hh"
#include<string>

/*!
 * \enum cableT
 * \brief Type du cable
 */

typedef enum {
  DROIT =0,
  CROISE
} cableT;

/*!
 * \class Cable
 * \brief La classe Cable représentant un Cable.
 */

class Cable{
private:
  static int nbCables; /*!< Nombre de cables */
  int id;/*!< Identificateur du cable */
  int debitMax;/*!< Débit maximum sur un câble */
  float debitAcc;/*!< Débit actuel sur un câble */
  float latence;/*!< Latence sur un cable */ //refrence to congestion
  static int i;//augmenter l'id
  cableT type;/*!< Type du cable */
  Noeud* ext1;/*!< Le premier Noeud a l'extremitie */
  Noeud* ext2;/*!< Le deuxième Noeud a l'extremitie */
public:
  /*!
   * Constructeur par défaut de la classe Cable
   * \brief Constructeur par défaut
   */
  Cable();
  /*!
   *  Constructeur de la classe Cable
   * \brief Construceur
   * \param type : Type du cable
   * \param debitMax : Débit maximum du câble
   * \param ext1 : Le premier Noeud a l'extremitie
   * \param ext2 : Le deuxième Noeud a l'extremitie
   */
  Cable(cableT type,int debitMax,Noeud* ext1, Noeud* ext2);
  /*!
   *  Constructeur par copie de la classe Cable
   * \brief Construceur
   * \param c : Cable
   */
  Cable(Cable& c);

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
   * \brief getType
   * \return Le type du cable (cableT)
   */
  cableT getType() const{return type;}
  /*!
   * \brief getDebitAcc
   * \return Le débit actuel (float)
   */
  float getDebitAcc() const{ return debitAcc;}
  /*!
   * \brief getNbCables
   * \return Le nombre du cables (int)
   */
  static int getNbCables(){return nbCables;}
  /*!
   * \brief getExt1
   * \return Le premier Noeud a l'extremitie (Noeud)
   */
  Noeud *getExt1() const{return ext1;}
  /*!
   * \brief getExt2
   * \return Le deuxième Noeud a l'extremitie (Noeud)
   */
  Noeud *getExt2() const{return ext2;}


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
   * Méthode qui permet de vérifier c'est deux noeud sont bien connectés
   * \return bool
   */
  bool estBienConnecte() const;

};
#endif
