#include "../include/MoteurPhy.h"

/** @brief Clock rotation of current blobs if possible
  *
  * (documentation goes here)
  */
void MoteurPhy:: rotationHoraire()
{
    switch(_orientation)
    {
    case HAUT :
        if(colBlobCourant() == 5*_taille||_grille(ligneBlobCourant(),colBlobCourant()+1)!=0)
        {
            if(_grille(ligneBlobCourant(),colBlobCourant()-1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()-_taille);
        }
        _orientation = DROITE;
        break;
    case BAS :
        if(colBlobCourant() == 0||_grille(ligneBlobCourant(),colBlobCourant()-1)!=0)
        {
            if(_grille(ligneBlobCourant(),colBlobCourant()+1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()+_taille);
        }
        _orientation = GAUCHE;
        break;
    case GAUCHE :
        _orientation = HAUT;
        break;
    case DROITE :
        if(_grille(ligneBlobCourant()+1,colBlobCourant())!=0)
            _posBlobPivot.setY(_posBlobPivot.y()-_taille);
        _orientation = BAS;
        break;
    }
    //TO DO : Turning clock_wise
}


/** @brief direct rotation of current blobs if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::rotationAntiHoraire()
{
    switch(_orientation)
    {
    case BAS :
        if(colBlobCourant() == 5*_taille||_grille(ligneBlobCourant(),colBlobCourant()+1)!=0)
        {
            if(_grille(ligneBlobCourant(),colBlobCourant()-1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()-_taille);
        }
        _orientation = DROITE;
        break;
    case HAUT :
        if(colBlobCourant() == 0||_grille(ligneBlobCourant(),colBlobCourant()-1)!=0)
        {
            if(_grille(ligneBlobCourant(),colBlobCourant()+1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()+_taille);
        }
        _orientation = GAUCHE;
        break;
    case DROITE :
        _orientation = HAUT;
        break;
    case GAUCHE :
        if(_grille(ligneBlobCourant()+1,colBlobCourant())!=0)
            _posBlobPivot.setY(_posBlobPivot.y()-_taille);
        _orientation = BAS;
        break;
    }
    // TO DO : turning Direct_wise
}
/** @brief Moove current blobs, if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::moove()
{
    int nextPosX = _posBlobPivot.y()+_vitesseBlob;
    if(_grille((int)(nextPosX/_taille),colBlobCourant())!=0){
        nextPosX = (((int)(nextPosX/_taille))-1)*_taille;
        //TO DO : Touching
    }
    _posBlobPivot.setX(nextPosX);

}


/** @brief mooves current blob left if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::gauche()
{
    switch(_orientation)
    {
    case GAUCHE :
        if(colBlobCourant() == _taille)
            return;
        else if(_grille(ligneBlobCourant(),colBlobCourant()-2)!=0)
            return;
        break;
    case BAS :
        if(colBlobCourant() == 0)
            return;
        else if(_grille(ligneBlobCourant()+1,colBlobCourant()-1)!=0)
            return;
        break;
    case HAUT :
    case DROITE :
        if(colBlobCourant() == 0)
            return;
        else  if(_grille(ligneBlobCourant(),colBlobCourant()-1)!=0)
            return;
        break;
    }
    _posBlobPivot.setX(_posBlobPivot.x()-_taille);
}

/** @brief Mooves current blobs right if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::droite()
{
    switch(_orientation)
    {
    case DROITE :
        if(colBlobCourant() == 4*_taille)
            return;
        else if(_grille(ligneBlobCourant(),colBlobCourant()+2)!=0)
            return;
        break;
    case BAS :
        if(colBlobCourant() == 5*_taille)
            return;
        else if(_grille(ligneBlobCourant()+1,colBlobCourant()+1)!=0)
            return;
        break;
    case HAUT :
    case GAUCHE :
        if(colBlobCourant() == 5*_taille)
            return;
        else if(_grille(ligneBlobCourant(),colBlobCourant()+1)!=0)
            return;
        break;
    }
    _posBlobPivot.setX(_posBlobPivot.x()+_taille);
}

/** @brief Speed up
  *
  * (documentation goes here)
  */
void MoteurPhy::speedUp()
{
    _vitesseBlob=(_vitesseBlob<50)?_vitesseBlob+1:_vitesseBlob;
}

/** @brief Speed to normal
  *
  * (documentation goes here)
  */
void MoteurPhy::speedToNormal()
{
    _vitesseBlob = 1;
}
/** @brief re-organizes grid after sub-combo
  *
  * (documentation goes here)
  */
void MoteurPhy::majCombo() {

}

