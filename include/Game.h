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
#include "InterfaceX.h"

#include <iostream> // temporaire

class Game
{
protected :
    std::vector<DashBoard> _dashBoards;
    std::list<Blobs> _randBlobs;
    InterfaceX* _X;
    Clock _clock;
public :

    Game(int nbJoueurs):_clock()
    {
        _X = new InterfaceX(nbJoueurs);
        std::cout<<"Game()\n";
        assert(nbJoueurs>0);
        initBlobs();
        for(int c=0; c<nbJoueurs; c++)
            _dashBoards.push_back(DashBoard(_X->taille_blob(),new Grille(),&_randBlobs));

    }

    std::vector<DashBoard> dashBoards()const{return _dashBoards;}
    void initBlobs(){
        Blobs randBlob;
    srand(time(NULL));
    for(int i=0;i<100;i++){
        randBlob.setBlob(Color(rand()%5), NO_STATE,NO_LINK);
        std::cout<<randBlob.color()<<std::endl;
        _randBlobs.push_front(randBlob);
        }
    }
    void go();


};

#endif
