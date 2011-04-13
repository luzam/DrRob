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
#include <map>
#include <set>
#include <iostream> //temporaire

enum Orientation{ HAUT,BAS,DROITE,GAUCHE};
class MoteurPhy{

        protected :
    int _taille;
    Position _posBlobPivot;
    size_t _colorMaster;
    size_t _colorSlave;
    int _vitesseBlob;
    int _orientation;
    int _comboAct;
    bool _launchCombo;
    bool _fixed;
    Grille* _grille;
    int _touching;
    int _comboting;
    int _falling;
    const int ligneBlobCourant()const{return (int)((_posBlobPivot).y()/_taille);}
    const int colBlobCourant()const{return (int)((_posBlobPivot).x()/_taille);}
    int ajoutGrille();


    public :
    MoteurPhy(int taille,Grille* grille):
    _taille(taille),_posBlobPivot(2*taille,0),_vitesseBlob(1),_orientation(HAUT),_comboAct(0),_launchCombo(false),_fixed(false),
    _grille(grille),_touching(0),_comboting(0),_falling(0){std::cout<<"MoteurPhy()\n";}
    ~MoteurPhy(){}

    void rotationHoraire(Position* master,Position* slave);
    void rotationAntiHoraire(Position* master,Position* slave);
    void gauche(Position* master,Position* slave);
    void droite(Position* master,Position* slave);
    void speedUp();
    void speedToNormal();
    int majCombo();
    void fall();
    int moove(Position* master,Position* slave);
    void ComboActReInit(){_comboAct = 0;_launchCombo=false;}
    int comboAct()const{return _comboAct;}
    void nextBlobs(Blobs master, Blobs slave){
        _posBlobPivot.setX(2*_taille);
        _posBlobPivot.setY(0);
        _orientation = HAUT;
    _colorMaster = master.color();
    _colorSlave = slave.color();
    _fixed = false;}
    bool launchCombo()const{ return _launchCombo;}
    bool fixed()const{return _fixed;}
    void setLaunchCombo(bool combo){_launchCombo=combo;}
    int falling()const{return _falling;}
    void setFalling(int falling){_falling = falling;}
    int comboting()const{return _comboting;}
    void majPosition(Position* master,Position* slave);


};


#endif // MOTEURPHY_H
