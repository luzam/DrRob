#include "../include/MoteurPhy.h"

/** @brief Clock rotation of current blobs if possible
  *
  * (documentation goes here)
  */
void MoteurPhy:: rotationHoraire(Position* master,Position* slave)
{
    switch(_orientation)
    {
    case HAUT :
        if(colBlobCourant() == 0&&(*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK )
            return;
        if(colBlobCourant() == 5||(*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK)
        {
            if((*(*_grille)(ligneBlobCourant(),colBlobCourant()-1)).color()!=BLANK)
                return;
            (_posBlobPivot).setX((_posBlobPivot).x()-_taille);
        }
        _orientation = DROITE;
        break;
    case BAS :
        if(colBlobCourant() == 0&&(*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK )
            return;
        if(colBlobCourant() == 0||(*(*_grille)(ligneBlobCourant(),colBlobCourant()-1)).color()!=BLANK)
        {
            if((*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK)
                return;
            (_posBlobPivot).setX((_posBlobPivot).x()+_taille);
        }
        _orientation = GAUCHE;
        break;
    case GAUCHE :
        _orientation = HAUT;
        break;
    case DROITE :
    bool up = false;
        if(ligneBlobCourant()>=16)
            up = true;
       else if(ligneBlobCourant()==18||(*(*_grille)(ligneBlobCourant()+2,colBlobCourant())).color()!=BLANK)
            up = true;
        if(up){
            if(colBlobCourant()==0)
                return;
            (_posBlobPivot).setY((_posBlobPivot).y()-_taille);
        }
        _orientation = BAS;
        break;
    }
    std::cout<<"roration-> orientation "<<_orientation<<std::endl;
    _turningHoraire=TURNING_ANIM_TIME;
    majPosition(master,slave);
    //TO DO : Turning clock_wise
}


/** @brief direct rotation of current blobs if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::rotationAntiHoraire(Position* master,Position* slave)
{

    switch(_orientation)
    {
    case BAS :
        if(colBlobCourant() == 0&&(*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK )
            return;
        if(colBlobCourant() == 5||(*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK )
        {
            if((*(*_grille)(ligneBlobCourant(),colBlobCourant()-1)).color()!=BLANK)
                return;
            (_posBlobPivot).setX((_posBlobPivot).x()-_taille);
        }
        _orientation = DROITE;
        break;
    case HAUT :
        if(colBlobCourant() == 0&&(*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK )
            return;
        if(colBlobCourant() == 0||(*(*_grille)(ligneBlobCourant(),colBlobCourant()-1)).color()!=BLANK)
        {
            if((*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK)
                return;
            (_posBlobPivot).setX((_posBlobPivot).x()+_taille);
        }
        _orientation = GAUCHE;
        break;
    case DROITE :
        _orientation = HAUT;
        break;
    case GAUCHE :
    bool up = false;
        if(ligneBlobCourant()>=16)
            up = true;
        else if(ligneBlobCourant()==18||(*(*_grille)(ligneBlobCourant()+2,colBlobCourant())).color()!=BLANK)
            up = true;
          if (up)
        {
            if(colBlobCourant()==0)
                return;
            (_posBlobPivot).setY((_posBlobPivot).y()-_taille);
        }
        _orientation = BAS;
        break;
    }
    std::cout<<"rotation-> orientation "<<_orientation<<std::endl;
    _turningDirect=TURNING_ANIM_TIME;
    majPosition(master,slave);

    // TO DO : turning Direct_wise
}
/** @brief Moove current blobs, if possible
  *
  * (documentation goes here)
  */
int MoteurPhy::moove(Position* master,Position* slave)
{
    std::cout<<(_posBlobPivot).x()<<" , "<<(_posBlobPivot).y()<<std::endl;
    std::cerr<<"touching : "<<(_touching)<<std::endl;
    bool touch = false;
    switch(_orientation)
    {
    case HAUT :
        if(((_posBlobPivot).y()+_vitesseBlob)>=17*_taille)
        {
            touch = true;
            break;
        }
        else if(((*_grille)((int)(((_posBlobPivot).y()+_vitesseBlob)/_taille+1),colBlobCourant()))->color()!=BLANK)
            touch = true;
        break;
    case BAS :
        if((_posBlobPivot).y()+_vitesseBlob>=16*_taille)
        {
            touch = true;
            break;
        }
        else if((*(*_grille)((int)(((_posBlobPivot).y()+_vitesseBlob+_taille)/_taille+1),colBlobCourant())).color()!=BLANK)
            touch = true;
        break;
    case GAUCHE :
        if(((_posBlobPivot).y()+_vitesseBlob)>=17*_taille)
        {
            touch = true;
            break;
        }
        else if((*(*_grille)((int)(((_posBlobPivot).y()+_vitesseBlob)/_taille+1),colBlobCourant())).color()!=BLANK||
                (*(*_grille)((int)(((_posBlobPivot).y()+_vitesseBlob)/_taille+1),colBlobCourant()-1)).color()!=BLANK)
            touch = true;
        break;
    case DROITE :
        if(((_posBlobPivot).y()+_vitesseBlob)>=17*_taille)
        {
            touch = true;
            break;
        }
        else if((*(*_grille)((int)(((_posBlobPivot).y()+_vitesseBlob)/_taille+1),colBlobCourant())).color()!=BLANK||
                (*(*_grille)((int)(((_posBlobPivot).y()+_vitesseBlob)/_taille+1),colBlobCourant()+1)).color()!=BLANK)
            touch = true;
        break;
    }

    if(touch)
    {
        _posBlobPivot.setY((((_posBlobPivot.y()+_vitesseBlob)/_taille))*_taille);

        if((_touching) !=0)
        {
            std::cerr<<"touching : "<<(_touching)<<std::endl;
            (_touching)--;
            if((_touching)==0)
            {
                _fixed = true;
                ajoutGrille();
            }
        }
        else
        {
            (_touching) = TOUCHING_ANIM_TIME;

            std::cerr<<"touching : "<<(_touching)<<std::endl;
        }
    }
    else
        (_posBlobPivot).setY((_posBlobPivot).y()+_vitesseBlob);
    majPosition(master,slave);
return _touching;
}
/** @brief fixes a blob to the grind
  *
  * (documentation goes here)
  */
void MoteurPhy::ajoutGrille()
{
    std::cout<<(_posBlobPivot).x()<<" , "<<(_posBlobPivot).y()<<std::endl;
    std::cout<<"ajout blob : "<<(ligneBlobCourant())<<" "<<colBlobCourant()<<"<---------"<<_colorMaster<<std::endl;
    ((*_grille)((ligneBlobCourant()),(colBlobCourant())))->setColor(_colorMaster);
    ((*_grille)((ligneBlobCourant()),(colBlobCourant())))->setLink(0);
    switch(_orientation)
    {
    case HAUT :
        (*(*_grille)((ligneBlobCourant())-1,(colBlobCourant()))).setColor(_colorSlave);
        (*(*_grille)((ligneBlobCourant())-1,(colBlobCourant()))).setLink(0);
        break;
    case BAS :
        (*(*_grille)((ligneBlobCourant())+1,(colBlobCourant()))).setColor(_colorSlave);
        (*(*_grille)((ligneBlobCourant())+1,(colBlobCourant()))).setLink(0);
        break;
    case GAUCHE :
        (*(*_grille)((ligneBlobCourant()),(colBlobCourant())-1)).setColor(_colorSlave);
        (*(*_grille)((ligneBlobCourant()),(colBlobCourant())-1)).setLink(0);
        break;
    case DROITE :
        (*(*_grille)((ligneBlobCourant()),(colBlobCourant())+1)).setColor(_colorSlave);
        (*(*_grille)((ligneBlobCourant()),(colBlobCourant())+1)).setLink(0);
        break;
    }
    _landing = LANDING_ANIM_TIME;

}



/** @brief mooves current blob left if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::gauche(Position* master,Position* slave)
{
    std::cout<<"gauche"<<std::endl;
    switch(_orientation)
    {
    case GAUCHE :
        if(colBlobCourant() == 1)
            return;
        else if((*(*_grille)(ligneBlobCourant(),colBlobCourant()-2)).color()!=BLANK)
            return;
        break;
    case BAS :
        if(colBlobCourant() == 0)
            return;
        else if((*(*_grille)(ligneBlobCourant()+1,colBlobCourant()-1)).color()!=BLANK)
            return;
        break;
    case HAUT :
    case DROITE :
        if(colBlobCourant() == 0)
            return;
        else  if((*(*_grille)(ligneBlobCourant(),colBlobCourant()-1)).color()!=BLANK)
            return;
        break;
    }
    (_posBlobPivot).setX((_posBlobPivot).x()-_taille);
    majPosition(master,slave);
}

/** @brief Mooves current blobs right if possible
  *
  * (documentation goes here)
  */
void MoteurPhy::droite(Position* master,Position* slave)
{
    std::cout<<"droite"<<std::endl;
    switch(_orientation)
    {
    case DROITE :
        if(colBlobCourant() == 4)
            return;
        else if((*(*_grille)(ligneBlobCourant(),colBlobCourant()+2)).color()!=BLANK)
            return;
        break;
    case BAS :
        if(colBlobCourant() == 5)
            return;
        else if((*(*_grille)(ligneBlobCourant()+1,colBlobCourant()+1)).color()!=BLANK)
            return;
        break;
    case HAUT :
    case GAUCHE :
        if(colBlobCourant() == 5)
            return;
        else if((*(*_grille)(ligneBlobCourant(),colBlobCourant()+1)).color()!=BLANK)
            return;
        break;
    }
    (_posBlobPivot).setX((_posBlobPivot).x()+_taille);
    majPosition(master,slave);
}

/** @brief Speed up
  *
  * (documentation goes here)
  */
void MoteurPhy::speedUp()
{
    //_vitesseBlob=(_vitesseBlob<50)?_vitesseBlob+10:_vitesseBlob;
    _speedUp = true;
}

/** @brief Speed to normal
  *
  * (documentation goes here)
  */
void MoteurPhy::speedToNormal()
{
    _speedUp = false;
}
/** @brief re-organizes grid after sub-combo
  *
  * (documentation goes here)
  */
void MoteurPhy::majCombo()
{
    char *img = (char *)malloc(6*18);
    std::multimap<unsigned char,Position> key;
    int combo = 0;

    std::cout<<"Grille"<<std::endl;
    //écriture de la grille dans un unsigned char
    for(int l=0; l<18; l++)
    {
        for(int c=0; c<6; c++)
            std::cout<<((*_grille)(l,c))->color();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;


    for(int l=0; l<18; l++)
    {
        for(int c=0; c<6; c++)
            (img)[l*6+c]=(*_grille)(l,c)->color();
    }
    std::cout<<"Image"<<std::endl;

    for(int l=0; l<18; l++)
    {
        for(int c=0; c<6; c++)
            std::cout<<(img)[l*6+c];
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"labeled"<<std::endl;


    // récupération des connectedComponents labelled
    int width = 6, height =18;
    unsigned char *out_uc = (unsigned char *)malloc(width*height);
    std::cout<<"BLA1"<<std::endl;
    ConnectedComponents cc(7);
    std::cout<<"BLA2"<<std::endl;
    cc.connected(img, out_uc, width, height,
                 std::equal_to<unsigned char>(),
                 false);
    std::cout<<"BLA3"<<std::endl;
    for(int r=0; r<height; ++r)
    {
        for(int c=0; c<width; ++c)
            putchar('0'+out_uc[r*width+c]);
        putchar('\n');
    }
    // récupération des label dans un vector
    for(int l=0; l<18; l++)
        for(int c=0; c<6; c++)
            key.insert(std::pair<unsigned char,Position>(out_uc[l*6+c], Position(l,c)));

    std::cout<<std::endl<<"taille map : "<<key.size()<<std::endl;
    std::multimap<unsigned char,Position>::iterator it;
    std::set<unsigned char> keyset;
    // suppression des zones inférieurs à quatre et des absences de blobs
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end();
            ++it)
        if(key.count((*it).first)<4||((*_grille)((*it).second.x(),(*it).second.y()))->color()==BLANK||((*_grille)((*it).second.x(),(*it).second.y()))->color()==DARK)//et BIM
            keyset.insert((*it).first);
  /*  if(keyset.empty())
        _fixed = true;*/
    for(std::set<unsigned char>::iterator its = keyset.begin(); its!=keyset.end(); ++its)
        key.erase((*its));
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end(); ++it)
        std::cout << "  {  " << (int)((*it).first) << ", [" << (*it).second.x() << ","<< (*it).second.y()<< "]  }" << std::endl;
    keyset.clear();
    //on récuper les label des combos restant
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end(); ++it)
        keyset.insert((*it).first);
    if(!key.empty())
    {
        for(std::set<unsigned char>::iterator its = keyset.begin(); its!=keyset.end(); ++its)
            combo+=key.count(*its);
        _comboting = COMBOTING_ANIM_TIME;
        if(combo!=0)
            _combo = combo;

    }
    keyset.clear();
    for (std::multimap<unsigned char, Position>::iterator it = key.begin(); it != key.end(); ++it)
    {
        if(((*_grille)((*it).second.x(),(*it).second.y()))->current()==0)
            ((*_grille)((*it).second.x(),(*it).second.y()))->setComboting(COMBOTING_ANIM_TIME);
    }
    std::cout<<"Combo : " << _combo << std::endl;
    free(out_uc);
    free(img);
    for(int l=0; l<18; l++)
    {
        for(int c=0; c<6; c++)
        {
            std::cout<<(((*_grille)(l,c))->color());
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

}

/** @brief make blobs fall after a combote
  *
  * (documentation goes here)
  */
void MoteurPhy::fall()
{
    int maxBlank = 0;
    for(int col=0; col<6; col++)
    {
        int blanks = 0;
        for(int ligne=17; ligne>=0; ligne--)
        {
            if(((*_grille)(ligne,col))->color()==BLANK)
                blanks+=_taille;
            else if(blanks!=0 &&(*_grille)(ligne,col)->current()==0 )
            {
                ((*_grille)(ligne,col))->setFalling(blanks);
                ((*_grille)(ligne,col))->setFallingDepth(blanks);
                ((*_grille)(ligne,col))->setFallingCol(blanks/_taille);

                maxBlank=(blanks>maxBlank)?blanks:maxBlank;
            }
        }
    }
    _falling = maxBlank;
    std::cout<<"MMMMMMMMAXBLANK->>>>>>>>>>>>>>>>>>>>>> " <<_falling<<std::endl;
}

/** @brief updating position of blobs
  *
  * (documentation goes here)
  */
void MoteurPhy::majPosition(Position* master, Position* slave)
{
    master->setX(_posBlobPivot.x());
    master->setY(_posBlobPivot.y());
    switch(_orientation)
    {

    case HAUT :
        slave->setX(_posBlobPivot.x());
        slave->setY(_posBlobPivot.y()-_taille);
        break;
    case BAS :
        slave->setX(_posBlobPivot.x());
        slave->setY(_posBlobPivot.y()+_taille);
        break;
    case GAUCHE :
        slave->setX(_posBlobPivot.x()-_taille);
        slave->setY(_posBlobPivot.y());
        break;
    case DROITE :
        slave->setX(_posBlobPivot.x()+_taille);
        slave->setY(_posBlobPivot.y());
        break;
    }
}

