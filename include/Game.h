#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "Blobs.h"
#include "MoteurPhy.h"
#include "DashBoard.h"
#include "Clock.h"
#include <vector>
#include <list>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <iostream> // temporaire

class Game
{
protected :
    std::vector<DashBoard> _dashBoards;
    std::list<Blobs> _randBlobs;
    Clock _clock;
public :

    Game(int nbJoueurs,int taille): _clock()
    {
        std::cout<<"Game()\n";
        assert(nbJoueurs>0);
        for(int c=0; c<nbJoueurs; c++)
            _dashBoards.push_back(DashBoard(taille,new Grille<Blobs>(),&_randBlobs));

    }

    std::vector<DashBoard> dashBoards()const{return _dashBoards;}
    void initBlobs(){
        Blobs randBlob;
    srand(time(NULL));
    for(int i=0;i<1;i++){
        randBlob.setBlob(Color(rand() % 6 + 1), NO_STATE,NO_LINK);
        _randBlobs.push_front(randBlob);
        }
    }
    void go();


};

#endif
