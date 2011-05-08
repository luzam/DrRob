#ifndef MOTEURPHY_H
#define MOTEURPHY_H


#define TOUCHING_ANIM_TIME 6
#define FALLING_ANIM_TIME 0
#define COMBOTING_ANIM_TIME 120
#define TURNING_ANIM_TIME 6

#include <stdio.h>
#include "Position.h"
#include "Grille.h"
#include "Tree.h"
#include "conected.h"
#include "Blobs.h"
#include "Orientation.h"
#include <map>
#include <set>
#include <iostream> //temporaire

class MoteurPhy{

        protected :
    int _taille;
    Position _posBlobPivot;
    size_t _colorMaster;
    size_t _colorSlave;
    int _vitesseBlob;
    int _orientation;
    int _combo;
    bool _fixed;
    Grille* _grille;
    int _touching;
    int _comboting;
    int _falling;
    int _landing;
    int _turningDirect;
    int _turningHoraire;
    bool _speedUp;
    const int ligneBlobCourant()const{return (int)((_posBlobPivot).y()/_taille);}
    void ajoutGrille();


    public :
    MoteurPhy(int taille,Grille* grille):
    _taille(taille), _grille(grille){init(taille);}
    ~MoteurPhy(){
    delete _grille;
    }
    void init(int taille){
        _taille = taille;
        _posBlobPivot.setX(2*taille);
        _posBlobPivot.setY(6*taille);
        _vitesseBlob = taille/2;
        _orientation = HAUT;
        _combo = 0;
        _fixed = false;
        _touching = 0;
        _comboting = 0;
        _falling = 0;
        _landing = 0;
        _turningDirect = 0;
        _turningHoraire = 0;
        _speedUp = false;
    }
    const int colBlobCourant()const{return (int)((_posBlobPivot).x()/_taille);}
    void rotationHoraire(Position* master,Position* slave);
    void rotationAntiHoraire(Position* master,Position* slave);
    void gauche(Position* master,Position* slave);
    void droite(Position* master,Position* slave);
    void speedUp();
    void speedToNormal();
    void majCombo();
    void fall();
    int moove(Position* master,Position* slave);
    int combo()const{return _combo;}
    void nextBlobs(Blobs master, Blobs slave){
        _posBlobPivot.setX(2*_taille);
        _posBlobPivot.setY(6*_taille);
        _orientation = HAUT;
    _colorMaster = master.color();
    _colorSlave = slave.color();}
    bool fixed()const{return _fixed;}
    int falling()const{return _falling;}
    void setFalling(int falling){_falling = falling;}
    int turningDirect()const{return _turningDirect;}
    void setTurningDirect(int turning){_turningDirect = turning;}
    int turningHoraire()const{return _turningHoraire;}
    void setTurningHoraire(int turning){_turningHoraire = turning;}
    void setFixed(bool fixed){_fixed = fixed;}
    void setComboting(int comboting){_comboting = comboting;}
    void setCombo(int combo){_combo = combo;}
    int comboting()const{return _comboting;}
    int orientation()const{return _orientation;}
    void majPosition(Position* master,Position* slave);
    int taille()const{return _taille;}
    void setLanding(int landing){ _landing = landing;}
    bool speedUpBool()const{return _speedUp;}


};


#endif // MOTEURPHY_H
