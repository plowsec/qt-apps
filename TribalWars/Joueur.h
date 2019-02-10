#ifndef JOUEUR_H
#define JOUEUR_H
#include "District.h"
#include <QtGui>
class Joueur
{
public:
    Joueur();
    Joueur(QString name, int idQG);
    ~Joueur();
private:
    bool isWinner();
    bool isLooser();
    QString getPseudo();
    void setPseudo(QString name);
private:
    int nbDistricts;
    int troupesTotales;
    QString pseudo;
    int m_idQG;
};

#endif // JOUEUR_H
