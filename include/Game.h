#ifndef GAME_H
#define GAME_H
#include "Controls.h"
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
#include "Easy.h"
#include "Hard.h"
#include "Joueur.h"

#include <iostream> // temporaire

class Game
{
protected :
    std::vector<DashBoard *> _dashBoards;
    std::list<Blobs> _randBlobs;
    InterfaceX* _X;
    Clock _clock;
    int _nbJoueurs;
    int _nbAI;
    int *_combo;
public :

    Game():_clock(),_nbJoueurs(1),_nbAI(1)
    {
        _X = new InterfaceX(600,500);
        std::cout<<"Game()\n";
    }

    std::vector<DashBoard *> dashBoards()const{return _dashBoards;}
    void initBlobs(){
        srand(time(NULL));
        Blobs randBlob;
    for(int i=0;i<101;i++){
        randBlob.setBlob(Color(rand()%5), NO_STATE,NO_LINK);
        std::cout<<randBlob.color()<<std::endl;
        _randBlobs.push_front(randBlob);
        }
    }
    void go();
    void repartitionCombo(bool winner);


};

#endif
