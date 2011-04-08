#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Blobs.h"
#include "Position.h"
#include "MoteurPhy.h"
//#include "SDLttf.h"
#include <vector>
class DashBoard {

protected :
MoteurPhy _moteurPhy;
int _combo;
Grille<Blobs>* _grille;
Blobs _courantPivot;
Blobs _courantSlave;
Position _pivot;
Position _slave;
std::vector<Blobs>* _nextBlobs;
int nextBlob;
Position posFen;//position relative du dashboard dans la fenetre, a metre dans MoteurX (??)
/* SDLttf texte _score;
SDLttf texte _joueur;*/
std::vector<Blobs> _nextDarkBlobs;

public :
DashBoard(int taille,Grille<Blobs>* grille,std::vector<Blobs>* randBlobs):
_moteurPhy(taille,grille),_grille(grille),_nextBlobs(randBlobs),nextBlob(0){}

bool checkCombo(){
    if(_moteurPhy.launchCombo()){
        _combo = _moteurPhy.comboAct();
        _moteurPhy.ComboActReInit();
        return true;}
    return false;
}
MoteurPhy moteurPhy()const{return _moteurPhy;}

};


#endif
