#ifndef MOTEURPHY_H
#define MOTEURPHY_H

#include "Position.h"
#include "Grille.h"
enum Orientation{ HAUT,BAS,DROITE,GAUCHE};
class MoteurPhy{

        protected :
    int _taille;
    Position _posBlobPivot;
    int _vitesseBlob;
    int _orientation;
    Grille _grille;
    int _ligneBlobCourant=0;
    int _colBlobCourant = 2;

    public :
    MoteurPhy(int taille,int vitesseBlob,const Grille& grille):
    _taille(taille),_posBlobPivot(2*_taille,0),_vitesseBlob(vitesseBlob),_orientation( HAUT),_grille(grille){};
    MoteurPhy(){}
    ~MoteurPhy(){}

    void rotationHoraire();
    void rotationAntiHoraire();
    void gauche();
    void droite();
    void speedUp();
    void speedToNormal();
    void majCombo();



};


#endif // MOTEURPHY_H
