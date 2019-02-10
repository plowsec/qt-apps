#include "Joueur.h"
#include "District.h"
#include "QuartierGeneral.h"

Joueur::Joueur() : pseudo("I.A."),nbDistricts(1),troupesTotales(15)
{
}
Joueur::Joueur(QString name, int idQG) : pseudo(name),nbDistricts(1),troupesTotales(15)
{
}
