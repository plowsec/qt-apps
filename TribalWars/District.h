#ifndef DISTRICT_H
#define DISTRICT_H

class District
{
public:
    District();
    District(int idDistrict);
//    ~District();

    void deplacer(int nbTroupes, District *destination);
    void attaquer(int nbSoldats, District *destination);
    void setJoueur(int player);
    int getJoueur();
    int getTroupes();
    void setTroupes(int nouvellesTroupes);
    bool isVoisin(District *district);
    void setVoisins(int newVoisins,int index);
    int getVoisin(int index);
    void recruter(int recrues);
    bool isQG();

    int getId();
private:
    int id;
    int troupes;
    int nbVoisins;
    int voisins[5];
    int idJoueur;
};

#endif // DISTRICT_H
