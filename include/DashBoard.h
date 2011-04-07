#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Blobs.h"
#include "Position.h"
//#include "SDLttf.h"
#include <vector>
class DashBoard : public MoteurPhy{

protected :
Blobs _courantPivot;
Blobs _courantSlave;
Position _pivot;
Position _slave;
std::vector<Blobs> _nextBlobs;
Position posFen;//position relative du dashboard dans la fenetre, a metre dans MoteurX (??)
/* SDLttf texte _score;
SDLttf texte _joueur;*/
std::vector<Blobs> _darkBlobs;

public :
DashBoard(){}

bool checkCombo(){
    if(_launchCombo){
        _launchCombo = false;
        return true;}
    return false;
}

};


#endif
