#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QtWidgets>

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
    QChar map[13][13];
    QChar mapSauvegarde[12][12];
private slots:
    void buildMenu();
    void buildInterface();
    void keyPressEvent(QKeyEvent *);
    void setPosXY(int x, int y);
    void setRelativePosXY(int x, int y);
    int getPosX();
    int getPosY();
    void deplacerJoueur(int x, int y);
    void setOldPosXY(int x, int y);
    int getOldPosX();
    int getOldPosY();
    void setNiveau(int c);
    int getLvl();
    void chargerNiveau(int ch);
    void execEditor();
    void recommencer();
    int compterNiveaux();
    void chargerNiveauSuivant();
    void chargerNiveauPrecedent();
    void execOptions();
    void aide();
    void setGraphs();
    void annuler();

private:
    QMenu *menuFichier;
    QMenu *menuTriche;
    QMenu *menuEdition;
    QMenu *menuAide;
    QStatusBar *barre;
    QAction *actionAide;
    QAction *actionEditor;
    QAction *actionOptions;
    QAction *actionQuitter;
    QAction *actionRecommencer;
    QAction *actionNiveauSuivant;
    QAction *actionNiveauPrecedent;
    QAction *actionAnnuler;
    QGraphicsScene *scene;
    QGraphicsItem *carte[12][12];
    int posX;
    int posY;
    int oldPosX;
    int oldPosY;
    int nombreCoups;
    QString fond;
    QString mur;
    QString personnage;
    QString caisse;
    QString caisse_ok;
    QString objectif;
    QString niveau;
    QString chaine;
};

#endif // WINDOW_H
