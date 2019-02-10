#ifndef QUARTIERGENERAL_H
#define QUARTIERGENERAL_H
#include "District.h"
class QuartierGeneral : public District
{
public:
    QuartierGeneral();
    ~QuartierGeneral();
    void recruter(int nbRecrues);
};

#endif // QUARTIERGENERAL_H
