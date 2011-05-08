#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "Blobs.h"
#include "Position.h"
#include "MoteurPhy.h"
#include "Orientation.h"
//#include "SDLttf.h"
#include <vector>
#include <list>

#include <iostream> // temporaire


class DashBoard
{

protected :
    bool _looser;
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
    bool _launchCombo;
    Position posFen;
    int _nextDarkBlobs;
    bool _landing;
    int _newDelay;
    int _score;

public :
    DashBoard(int taille,Grille* grille,std::list<Blobs>* randBlobs):_looser(false),_combo(0),
        _grille(grille),_nextBlobs(randBlobs),_it((*_nextBlobs).begin()),_go(false),_launchCombo(false),
        _nextDarkBlobs(0),_landing(true),_newDelay(2),_score(0)
    {
        _moteurPhy = new MoteurPhy(taille,grille);
         _masterBlob.setBlob(*(++_it));
        _slaveBlob.setBlob(*(++_it));
        _nextMaster.setColor((++_it)->color());
        _nextSlave.setColor((++_it)->color());
        _moteurPhy->nextBlobs(_masterBlob,_slaveBlob);
    }
    virtual ~DashBoard(){
    delete _moteurPhy;

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
    void setCombo(int combo){_combo = combo;}
    void resetCombo();
    bool launchCombo()const{return _launchCombo;}
    int combo()const{return _combo;}
    void addDarkBlob();
    bool looser()const{return _looser;}
    int score()const{return _score;}
    virtual void think() = 0;

};


#endif
