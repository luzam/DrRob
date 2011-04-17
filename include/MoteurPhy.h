#ifndef MOTEURPHY_H
#define MOTEURPHY_H

#define TOUCHING_ANIM_TIME 100
#define FALLING_ANIM_TIME 10
#define COMBOTING_ANIM_TIME 10

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
    int _turningDirect;
    int _turningHoraire;
    const int ligneBlobCourant()const{return (int)((_posBlobPivot).y()/_taille);}
    const int colBlobCourant()const{return (int)((_posBlobPivot).x()/_taille);}
    void ajoutGrille();


    public :
    MoteurPhy(int taille,Grille* grille):
    _taille(taille),_posBlobPivot(2*taille,0),_vitesseBlob(1),_orientation(HAUT),_combo(0),_fixed(false),
    _grille(grille),_touching(0),_comboting(0),_falling(0),_turningDirect(0),_turningHoraire(0){std::cout<<"MoteurPhy()\n";}
    ~MoteurPhy(){}

    void rotationHoraire(Position* master,Position* slave);
    void rotationAntiHoraire(Position* master,Position* slave);
    void gauche(Position* master,Position* slave);
    void droite(Position* master,Position* slave);
    void speedUp();
    void speedToNormal();
    void majCombo();
    void fall();
    void moove(Position* master,Position* slave);
    int combo()const{return _combo;}
    void nextBlobs(Blobs master, Blobs slave){
        _posBlobPivot.setX(2*_taille);
        _posBlobPivot.setY(0);
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
    int comboting()const{return _comboting;}
    int orientation()const{return _orientation;}
    void majPosition(Position* master,Position* slave);
    int taille()const{return _taille;}


};


#endif // MOTEURPHY_H
