#ifndef AI_H
#define AI_H

#include "DashBoard.h"
#include <time.h>
#include <stdlib.h>


class Ai : public DashBoard{
protected :

public :

Ai(int taille,Grille* grille,std::list<Blobs>* randBlobs):DashBoard(taille,grille,randBlobs){
srand(time(NULL));
}
virtual void go(){std :: cerr<< "AI";}
virtual void think() = 0;
int next_rand(){return rand();}

virtual ~Ai() {}

};


#endif
