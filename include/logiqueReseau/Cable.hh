#ifndef CABLE_H
#define CABLE_H


/*!
 * \file Cable.hh
 * \brief Cable
 * \author Nadjibian
 * \version 0.1
 */

#include "Noeud.hh"
#include "CableG.hh"
#include <string>


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

class Noeud;
//class CableG;

#ifndef EXTREMITE_H
#define EXTREMITE_H
/*!
 * \struct extremite
 * \brief Extremité du cable
 */

struct extremite{
    Noeud * noeud; /*!< Noeud */
    int interface; /*!< interface liée*/
};

#endif
/*!
 * \class Cable
 * \brief La classe Cable représentant un Cable.
 */


class Cable{
private:
  static int nbCables; /*!< Nombre de cables */
  static int i; /*!< Générateur des ID */

  int id; /*!< Identificateur du cable */
  int debitMax; /*!< Bande Passante Max */
  float debitAcc; /*!< Bande passante  */
  float latence; /*!< Latence du cable */ //refrence to congestion
  int MTU; /*! < Taille maximale du paquet transmis */
  cableT type; /*!< Type du cable */
  extremite* ext1; /*!< Le Noeud à l'extremitie 1 */
  extremite* ext2; /*!< Le Noeud à l'extremitie 2*/
  CableG * parent;
public:

  /*!
   *
   * \brief Construceur
   * Constructeur de la classe Cable
   * \param type : voir #type
   * \param debitMax : voir #debitMax
   */
  Cable(cableT type = DROIT, int debitMax = 100, int MTU = 1500, CableG * parent = nullptr);

  /*!
   * \brief Destructeur
   * Destructeur de la classe noeud
   */
  ~Cable();

  /*!
   * \brief getId
   * \return Identificateur du cable (int)
   */
  int getId() { return id;}
  /*!
   * \brief getDebitMax
   * \return Débit maximum du câble (int)
   */
  int getDebitMax() const{return debitMax;}
  /*!
   * \brief getLatence
   * \return La latence sur un cable (float)
   */
  float getLatence() {return latence;}
  /*!
   * \brief getDebitAcc
   * \return Le débit actuel (float)
   */
  float getDebitAcc() { return debitAcc;}
  /*!
   * \brief getMTU
   * \return voir #MTU
   */
  int getMTU(){return MTU;}
  /*!
   * \brief getType
   * \return Le type du cable (cableT)
   */
  cableT getType() {return type;}

  /*!
   * \brief getExt1
   * \return Le premier Noeud a l'extremitie (Noeud)
   */
  extremite * getExt1() {return ext1;}
  /*!
   * \brief getExt2
   * \return Le deuxième Noeud a l'extremitie (Noeud)
   */
  extremite * getExt2() {return ext2;}
  /*!
   * \brief getExt
   * \param ext : Le noeud en extrimité 1
   * \return : Le noeud en extrimité 2
   */
  extremite* getExt(Noeud * _noeud){
      return _noeud == ext1->noeud ?  ext1 : _noeud == ext2->noeud  ? ext2 : nullptr;
  }

  extremite * getInverseExt(Noeud * _noeud){
      return _noeud == ext1->noeud ?  ext2 : _noeud == ext2->noeud  ? ext1 : nullptr;
  }

  CableG * getParent(){return parent;}
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
  void setExt1(extremite *noeud1);
  /*!
   * \brief setExt2
   * Modifier le noeud a l'extremitie
   * \param noeud2 : noeud (Noeud).
   */
  void setExt2(extremite *noeud1);

  void setParent(CableG * _parent);

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
