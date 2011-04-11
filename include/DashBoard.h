#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Blobs.h"
#include "Position.h"
#include "MoteurPhy.h"
//#include "SDLttf.h"
#include <vector>
#include <list>

#include <iostream> // temporaire


class DashBoard
{

protected :
    MoteurPhy* _moteurPhy;
    int _combo;
    Grille<Blobs>* _grille;
    std::list<Blobs>* _nextBlobs;
    std::list<Blobs>::iterator _it;
    Position _pivot;
    Position _slave;
    Position posFen;//position relative du dashboard dans la fenetre, a metre dans MoteurX (??)
    /* SDLttf texte _score;
    SDLttf texte _joueur;*/
    std::vector<Blobs> _nextDarkBlobs;

public :
    DashBoard(int taille,Grille<Blobs>* grille,std::list<Blobs>* randBlobs):
        _grille(grille),_nextBlobs(randBlobs),_it((*_nextBlobs).begin())
    {
        _moteurPhy = new MoteurPhy(taille,grille);
        _moteurPhy->nextBlobs(*(++_it),*(++_it));
       // std::cout<<"Dashboard()->>>"<<_courantPivot.color()<<std::endl;
    }

    bool checkCombo()
    {
        if(_moteurPhy->launchCombo())
        {
            _combo = _moteurPhy->comboAct();
            _moteurPhy->ComboActReInit();
            return true;
        }
        return false;
    }
    MoteurPhy* moteurPhy()const
    {
        return _moteurPhy;
    }
    void go();

};


#endif
