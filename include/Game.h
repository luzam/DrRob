#ifndef GAME_H
#define GAME_H

#include "Blob.h"

#include "MoteurPhy.h"
#include "DashBoard.h"
#include "Clock.h"
#include <vector>
#include <assert.h>

class Game
{
protected :
    std::vector<DashBoard> _dashBoards;
    Clock _clock;
public :

    Game(int nbJoueurs): _clock()
    {
        assert(nbJoueurs>1);
        for(int c=0; c<nbJoueurs; c++)
            _dashBoards.push_back(DashBoard());
    }



};

#endif
