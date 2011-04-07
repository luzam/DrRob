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
        if(colBlobCourant() == 5*_taille||(*_grille)(ligneBlobCourant(),colBlobCourant()+1)!=0)
        {
            if((*_grille)(ligneBlobCourant(),colBlobCourant()-1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()-_taille);
        }
        _orientation = DROITE;
        break;
    case BAS :
        if(colBlobCourant() == 0||(*_grille)(ligneBlobCourant(),colBlobCourant()-1)!=0)
        {
            if((*_grille)(ligneBlobCourant(),colBlobCourant()+1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()+_taille);
        }
        _orientation = GAUCHE;
        break;
    case GAUCHE :
        _orientation = HAUT;
        break;
    case DROITE :
        if(ligneBlobCourant()==13||(*_grille)(ligneBlobCourant()+1,colBlobCourant())!=0)
        {
            if(colBlobCourant()==0)
                return;
            _posBlobPivot.setY(_posBlobPivot.y()-_taille);
        }
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
        if(colBlobCourant() == 5*_taille||(*_grille)(ligneBlobCourant(),colBlobCourant()+1)!=0)
        {
            if((*_grille)(ligneBlobCourant(),colBlobCourant()-1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()-_taille);
        }
        _orientation = DROITE;
        break;
    case HAUT :
        if(colBlobCourant() == 0||(*_grille)(ligneBlobCourant(),colBlobCourant()-1)!=0)
        {
            if((*_grille)(ligneBlobCourant(),colBlobCourant()+1)!=0)
                return;
            _posBlobPivot.setX(_posBlobPivot.x()+_taille);
        }
        _orientation = GAUCHE;
        break;
    case DROITE :
        _orientation = HAUT;
        break;
    case GAUCHE :
        if(ligneBlobCourant()==13||(*_grille)(ligneBlobCourant()+1,colBlobCourant())!=0)
        {
            if(colBlobCourant()==0)
                return;
            _posBlobPivot.setY(_posBlobPivot.y()-_taille);
        }
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
    if((*_grille)((int)(nextPosX/_taille),colBlobCourant())!=0)
    {
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
        else if((*_grille)(ligneBlobCourant(),colBlobCourant()-2)!=0)
            return;
        break;
    case BAS :
        if(colBlobCourant() == 0)
            return;
        else if((*_grille)(ligneBlobCourant()+1,colBlobCourant()-1)!=0)
            return;
        break;
    case HAUT :
    case DROITE :
        if(colBlobCourant() == 0)
            return;
        else  if((*_grille)(ligneBlobCourant(),colBlobCourant()-1)!=0)
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
        else if((*_grille)(ligneBlobCourant(),colBlobCourant()+2)!=0)
            return;
        break;
    case BAS :
        if(colBlobCourant() == 5*_taille)
            return;
        else if((*_grille)(ligneBlobCourant()+1,colBlobCourant()+1)!=0)
            return;
        break;
    case HAUT :
    case GAUCHE :
        if(colBlobCourant() == 5*_taille)
            return;
        else if((*_grille)(ligneBlobCourant(),colBlobCourant()+1)!=0)
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
std::vector<Position> MoteurPhy::majCombo()
{
    char *img = (char *)malloc(6*13);
    std::multimap<unsigned char,Position> key;

    std::cout<<"Grille"<<std::endl;
    //écriture de la grille dans un unsigned char
    for(int l=0; l<13; l++)
    {
        for(int c=0; c<6; c++)
            sprintf(&img[l*6+c],"%d",(*_grille)(l,c));
    }
    for(int l=0; l<13; l++)
    {
        for(int c=0; c<6; c++)
            std::cout<<(img)[l*6+c];
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"labeled"<<std::endl;

    // récupération des connectedComponents labelled
    int width = 6, height =13;
    unsigned char *out_uc = (unsigned char *)malloc(width*height);
    ConnectedComponents cc(6);
    cc.connected(img, out_uc, width, height,
                 std::equal_to<unsigned char>(),
                 false);
    for(int r=0; r<height; ++r)
    {
        for(int c=0; c<width; ++c)
            putchar('0'+out_uc[r*width+c]);
        putchar('\n');
    }
    // récupération des label dans un vector
    for(int l=0; l<13; l++)
        for(int c=0; c<6; c++)
            key.insert(std::pair<unsigned char,Position>(out_uc[l*6+c], Position(l,c)));

    std::cout<<std::endl<<"taille map : "<<key.size()<<std::endl;
    std::multimap<unsigned char,Position>::iterator it;
    std::set<unsigned char> keyset;
    // suppression des zones inférieurs à quatre et des absences de blobs
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end();
            ++it)
        if(key.count((*it).first)<4||(*_grille)((*it).second.x(),(*it).second.y())==0)//et BIM
            keyset.insert((*it).first);
    for(std::set<unsigned char>::iterator its = keyset.begin(); its!=keyset.end(); ++its)
        key.erase((*its));
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end();
            ++it)
        std::cout << "  {  " << (int)((*it).first) << ", [" << (*it).second.x() << ","<< (*it).second.y()<< "]  }" << std::endl;
    keyset.clear();
    //on récuper les label des combos restant
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end(); ++it)
        keyset.insert((*it).first);
    if(key.empty())
    {
        if(_comboAct!=0)
            _launchCombo = true;
    }
    else
    {
        for(std::set<unsigned char>::iterator its = keyset.begin(); its!=keyset.end(); ++its)
            _comboAct+=key.count(*its);

    }
    keyset.clear();
    std::vector<Position> retourPos;// recupéré les comboté dans un vecteur pour animation
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end(); ++it)
        ;//TO DO : dire aux blobs du combo de dégager
    std::cout<<"Combo : " << _comboAct << std::endl;
    free(out_uc);
    free(img);
    return retourPos;
}

/** @brief make blobs fall after a combote
  *
  * (documentation goes here)
  */
std::vector<Position> MoteurPhy::fall(){



    return std::vector<Position>();
}


