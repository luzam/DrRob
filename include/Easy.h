#ifndef EASY_H
#define EASY_H

#include "ai.h"

class Easy : public Ai {

protected :


public :

Easy(int taille,Grille* grille,std::list<Blobs>* randBlobs):Ai(taille,grille,randBlobs){}

virtual void think(){
    int comp = rand()%21;
    _moteurPhy->speedToNormal();

    switch(comp){
    case 0 :_moteurPhy->rotationAntiHoraire(&_master,&_slave); break;
    case 1 : _moteurPhy->rotationHoraire(&_master,&_slave); break;
    case 2 :
    case 3 :
    case 4 :
    case 5 :
    case 6 :
    case 7 :
    case 8 :
    case 9 :_moteurPhy->droite(&_master,&_slave); break;
    case 10 :
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:_moteurPhy->gauche(&_master,&_slave); break;
    case 18:
    case 19:
    case 20:   break;
    case 21:_moteurPhy->speedUp();break;

    default : break;

    }
}
//virtual ~Easy() {}

};


#endif
