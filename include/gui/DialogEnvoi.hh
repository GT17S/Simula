#ifndef DIALOGENVOI_H
#define DIALOGENVOI_H

/*!
 * \file DialogEnvoi.hh
 * \brief DialogEnvoi
 * \author Medish
 * \version 0.1
 */

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QPushButton>

#include "Noeud.hh"

class DialogEnvoi : public QDialog {
    Q_OBJECT

private :
    QLineEdit * editNoeud1,
              * editNoeud2,
              * editPortSrc,
              * editPortDest,
              * editMessage;
    QCheckBox * checkAck,
              * checkFrag;
    QPushButton * envoyerButton;

    void createForm();
    void showForm(Noeud * n1, Noeud * n2);
public :
    DialogEnvoi(Noeud *n1 = nullptr, Noeud *n2 = nullptr);
    ~DialogEnvoi();

public slots:
    void preparenvoi();
    void onExitDialog(int);

};

#endif
