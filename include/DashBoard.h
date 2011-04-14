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
    Blobs _masterBlob;
    Blobs _slaveBlob;
    Blobs _nextMaster;
    Blobs _nextSlave;
    Grille* _grille;
    std::list<Blobs>* _nextBlobs;
    std::list<Blobs>::iterator _it;
    Position _master;
    Position _slave;
    bool _go;
    Position posFen;//position relative du dashboard dans la fenetre, a metre dans MoteurX (??)
    /* SDLttf texte _score;
    SDLttf texte _joueur;*/
    std::vector<Blobs> _nextDarkBlobs;

public :
    DashBoard(int taille,Grille* grille,std::list<Blobs>* randBlobs):
        _grille(grille),_nextBlobs(randBlobs),_it((*_nextBlobs).begin()),_go(false)
    {
        _moteurPhy = new MoteurPhy(taille,grille);
         _masterBlob.setBlob(*(++_it));
        _slaveBlob.setBlob(*(++_it));
        _nextMaster.setColor((++_it)->color());
        _nextSlave.setColor((++_it)->color());
        _moteurPhy->nextBlobs(_masterBlob,_slaveBlob);
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
    Grille* grille()const{return _grille;}

    void go();
    Position* masterPos(){return &_master;}
    Position* slavePos(){return &_slave;}
    Blobs* masterBlob(){return &_masterBlob;}
    Blobs* slaveBlob(){return &_slaveBlob;}
    Blobs* nextMaster(){return &_nextMaster;}
    Blobs* nextSlave(){return &_nextSlave;}

};


#endif
