#ifndef JOUEUR_H
#define JOUEUR_H

#include "DashBoard.h"

class Joueur : public DashBoard{

public:
Joueur(int taille,Grille* grille,std::list<Blobs>* randBlobs):DashBoard(taille,grille,randBlobs){}

virtual ~Joueur(){}

virtual void think() {
//joueur dont think
}





};
#endif
