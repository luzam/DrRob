#ifndef GAME_H
#define GAME_H
#include "MoteurPhy.h"
#include "Grille.h"
#include "DashBoard.h"
#include <vector>


class Game : public MoteurPhy
{
protected :
    Grille* _grille;
    vector<DashBoard> dashBoards;
    Clock clock;


public :



};

#endif
