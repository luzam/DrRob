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

    public :
    MoteurPhy(int taille,const Position& posBlobPivot,int vitesseBlob,const Grille& grille):
    _taille(taille),_posBlobPivot(posBlobPivot),_vitesseBlob(vitesseBlob),_orientation( HAUT),_grille(grille){};
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
