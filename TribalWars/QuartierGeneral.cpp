#include "QuartierGeneral.h"
#include "Joueur.h"
#include "District.h"


QuartierGeneral::QuartierGeneral()
{
}
void QuartierGeneral::recruter(int nbRecrues)
{
    setTroupes(getTroupes()+nbRecrues);

}
