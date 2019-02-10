#include "District.h"
#include "Joueur.h"
#include "QuartierGeneral.h"

District::District() : id(0), nbVoisins(5),idJoueur(0)
{
    for(int i=0; i<5;i++)
        voisins[i]=0;
}
District::District(int idDistrict) : id(idDistrict), nbVoisins(5),idJoueur(0)
{
    for(int i=0; i<5;i++)
        voisins[i]=0;
}
int District::getId()
{
    return id;
}

int District::getTroupes()
{
    return troupes;
}

int District::getJoueur()
{
    return idJoueur;
}
void District::recruter(int recrues)
{
    if(isQG())
        setTroupes(getTroupes()+recrues);
    else
        return;
}
bool District::isQG()
{
    int QGs[6]={9,5,13,17,28,30};
    for (int i=0;i<6;i++)
    {
        if(id==QGs[i])
            return true;
        else
            return false;
    }
}

bool District::isVoisin(District *district)
{
    int i=0;
    for(i=0;i<nbVoisins;i++)
    {
        if(voisins[i]==district->getId())
            return true;
    }
    return false;
}
void District::setJoueur(int player)
{
    idJoueur = player;
}

void District::setTroupes(int nouvellesTroupes)
{
    troupes = nouvellesTroupes;
}
int District::getVoisin(int index)
{
    return voisins[index];
}
void District::setVoisins(int newVoisins, int index)
{
    voisins[index]=newVoisins;
}

void District::attaquer(int nbSoldats, District *destination)
{
    if(isVoisin(destination))
    {
        int defenseurs = destination->getTroupes();
        if(nbSoldats>defenseurs)
        {
            destination->setJoueur(getJoueur());
            destination->setTroupes(nbSoldats-1);


            setTroupes(getTroupes()-nbSoldats);
        }
        else
        {
            destination->setTroupes(getTroupes()-1);
            setTroupes(getTroupes()-nbSoldats);
        }
    }
    else
        return;
}
void District::deplacer(int nbTroupes, District *destination)
{
    if(isVoisin(destination))
    {
        if(destination->getJoueur()==getJoueur())
        {
            destination->setTroupes(destination->getTroupes()+nbTroupes);
            setTroupes(getTroupes()-nbTroupes);
        }
        else if(destination->getJoueur()==0)
        {
            destination->setTroupes(destination->getTroupes()+nbTroupes);
            setTroupes(getTroupes()-nbTroupes);
            destination->setJoueur(getJoueur());
        }
        else
        {
            attaquer(nbTroupes,destination);
        }
    }
    else
        return;
}
