#ifndef GAME_H
#define GAME_H
<<<<<<< HEAD
#include "Controls.h"
#include "SDL.h"
=======

>>>>>>> 8e24d3493df2b5f427d2df04b6680b8717f3fb14
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
    std::vector<std::vector<int> > _commandes;
    InterfaceX* _X;
    Clock _clock;
<<<<<<< HEAD
    int _nbJoueurs;
    int _nbAI;
=======
    int _nbJoueurs;
    std::vector<bool> *_turningBool;
>>>>>>> 8e24d3493df2b5f427d2df04b6680b8717f3fb14
    int *_combo;
public :

    Game(int u):_commandes(),_clock(),_nbJoueurs(1),_nbAI(0)
    {
        _X = new InterfaceX(800,700);
        std::cout<<"Game()\n";
    }

    std::vector<DashBoard> dashBoards()const{return _dashBoards;}
    void initBlobs(){
        srand(time(NULL));
        Blobs randBlob;
    for(int i=0;i<101;i++){
        randBlob.setBlob(Color(rand()%5), NO_STATE,NO_LINK);
        std::cout<<randBlob.color()<<std::endl;
        _randBlobs.push_front(randBlob);
        }
    }
    void resize_commandes();
    void go();
    void repartitionCombo();


};

#endif
