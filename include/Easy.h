#ifndef EASY_H
#define EASY_H

#include "ai.h"

class Easy : public Ai {

protected :


public :

Easy(int taille,Grille* grille,std::list<Blobs>* randBlobs):Ai(taille,grille,randBlobs){}

virtual void think(){

}
//virtual ~Easy() {}

};


#endif
