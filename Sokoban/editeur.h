#ifndef EDITEUR_H
#define EDITEUR_H

#include <QtGui>
#include <QtWidgets>
#include "view.h"

class Editeur : public QMainWindow
{
    Q_OBJECT
public:
    Editeur(QWidget *parent = 0);
private slots:
    void buildInterface();
    void buildEcran();
    void changeEtatCaisse();
    void changeEtatCaisseOk();
    void changeEtatSand();
    void changeEtatWall();
    void changeEtatMario();
    void changeEtatObjectif();
    void save();
    void aide();
    void setGraphs();
public:
    QGraphicsItem *carte[12][12];
    QAction *caisse;
    QAction *caisseOk;
    QAction *wall;
    QAction *sand;
    QAction *mario;
    QAction *objectif;
    View *vue;

private:
    QPushButton *bouton;
    QAction *actionEnregistrer;
    QAction *actionAide;
    QMenu *menuFichier;
    QMenu *menuAide;
    QToolBar *tool;
    QMouseEvent *evt;
    QStatusBar *barreEtat;

    bool clic;

    QString Fond;
    QString Mur;
    QString Personnage;
    QString Caisse;
    QString Caisse_ok;
    QString Objectif;
    QString Niveau;
};

#endif // EDITEUR_H
