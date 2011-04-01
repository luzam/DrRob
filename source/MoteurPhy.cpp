#include "../include/MoteurPhy.h"

void MoteurPhy::speedUp(){
    _vitesseBlob+=1;
}

void MoteurPhy::speedToNormal(){
    _vitesseBlob = 1;
}

void MoteurPhy::droite(){
    switch(_orientation){
    case DROITE : if(_posBlobPivot.x()/_taille == 4*_taille)
                    return;
                   if(_grille((int)(_posBlobPivot.x()/_taille)==0)

     }
}
