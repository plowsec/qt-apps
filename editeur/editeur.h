#ifndef EDITEUR_H
#define EDITEUR_H

#include <QtGui>
#include "view.h"

class Editeur : public QMainWindow
{
    Q_OBJECT
public:
    Editeur();
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
    QMenu *menuFichier;
    QToolBar *tool;
    QMouseEvent *evt;
    bool clic;
};

#endif // EDITEUR_H
