#ifndef MOTEURPHY_H
#define MOTEURPHY_H

#define TOUCHING_ANIM_TIME 10
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
enum Orientation{ HAUT,BAS,DROITE,GAUCHE};
class MoteurPhy{

        protected :
    int _taille;
    Position* _posBlobPivot;
    Color _colorMaster;
    Color _colorSlave;
    int _vitesseBlob;
    int _orientation;
    int _comboAct;
    bool _launchCombo;
    Grille<Blobs>* _grille;
    int _ligneBlobCourant;
    int _colBlobCourant;
    int _touching;
    int _comboting;
    const int ligneBlobCourant()const{return (int)((*_posBlobPivot).y()/_taille);}
    const int colBlobCourant()const{return (int)((*_posBlobPivot).x()/_taille);}
    void ajoutGrille();


    public :
    MoteurPhy(int taille,Grille<Blobs>* grille):
    _taille(taille),_vitesseBlob(2),_orientation( HAUT),_comboAct(0),_launchCombo(false),
    _grille(grille),_ligneBlobCourant(0),_colBlobCourant(2),_touching(0),_comboting(0){_posBlobPivot = new Position(2*_taille,0);}
    ~MoteurPhy(){}

    void rotationHoraire();
    void rotationAntiHoraire();
    void gauche();
    void droite();
    void speedUp();
    void speedToNormal();
    int majCombo();
    void fall();
    void moove();
    void ComboActReInit(){_comboAct = 0;_launchCombo=false;}
    int comboAct()const{return _comboAct;}
    void nextBlobs(Blobs master, Blobs slave){
    _colorMaster = master.color();
    _colorSlave = slave.color();}
    bool launchCombo()const{ return _launchCombo;}
    void setLaunchCombo(bool combo){_launchCombo=combo;}


};


#endif // MOTEURPHY_H
