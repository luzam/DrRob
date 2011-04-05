#ifndef MOTEURPHY_H
#define MOTEURPHY_H

#include "Position.h"
#include "Grille.h"
#include "Tree.h"
#include "conected.h"
#include <map>
#include <set>
enum Orientation{ HAUT,BAS,DROITE,GAUCHE};
class MoteurPhy{

        protected :
    int _taille;
    Position _posBlobPivot;
    int _vitesseBlob;
    int _orientation;
    int _comboAct;
    bool _launchCombo;
    Grille* _grille;
    int _ligneBlobCourant;
    int _colBlobCourant;
    const int ligneBlobCourant()const{return (int)(_posBlobPivot.y()/_taille);}
    const int colBlobCourant()const{return (int)(_posBlobPivot.x()/_taille);}

    public :
    MoteurPhy(int taille,int vitesseBlob,Grille* grille):
    _taille(taille),_posBlobPivot(2*_taille,0),_vitesseBlob(vitesseBlob),_orientation( HAUT),_comboAct(0),_launchCombo(false),_grille(grille),
    _ligneBlobCourant(0),_colBlobCourant(2){};
    MoteurPhy(){} // temporaire pour DashBoard, a supprimer
    ~MoteurPhy(){}

    void rotationHoraire();
    void rotationAntiHoraire();
    void gauche();
    void droite();
    void speedUp();
    void speedToNormal();
    int majCombo();
    void moove();


};


#endif // MOTEURPHY_H
