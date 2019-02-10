#ifndef ZONETEXTE_H
#define ZONETEXTE_H

#include <QtGui>

class ZoneTexte : public QTextEdit
{
Q_OBJECT
public:
    ZoneTexte();
public slots:
    void setTitre(QString titre);
    void enregistrer();
    void saveAlreadyExist(QString nomFichier);
    void imprimerTexte();

    //ascenseurs
    QString getEmplacement();
    void setEmplacement(QString chemin);

 private:
    QString emplacement;
};

#endif // ZONETEXTE_H
