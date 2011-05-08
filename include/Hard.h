#ifndef HARD_H
#define HARD_H

#include "ai.h"
#include <vector>
#include "Color.h"
#include "Orientation.h"

class Hard : public Ai
{
protected :
    std::vector<int> _lineUp;
    int _colMin;
    int _debilismeAleatoire;
public :
    Hard(int taille,Grille* grille,std::list<Blobs>* randBlobs):Ai(taille,grille,randBlobs),_lineUp(6,BLANK),_debilismeAleatoire(2),_colMin(0) {}
    virtual ~Hard() {}

    virtual void think()
    {
        int l1=-1,l2=-1;
        _moteurPhy->speedToNormal();
        /*  if(--_debilismeAleatoire == 0)
          {
              easy();
              _debilismeAleatoire = 5;
              return;
          }*/
        majLineUp();
        majLineEmpty();
        l1 = checkLigne(_masterBlob.color());
        l2 = checkLigne(_slaveBlob.color());
        std::cerr<< "colmin : " << _colMin << "\n"<<std::endl;
        std::cerr<< "l1 : " << l1 << "\n"<<std::endl;
        std::cerr<< "l2 : " << l2 << "\n"<<std::endl;

        if(rand()%20==0)
        if(_moteurPhy->colBlobCourant()==2){
        if(rand()%2==0)
             _moteurPhy->gauche(&_master,&_slave);
            else
                _moteurPhy->droite(&_master,&_slave);
            if(rand()%2==0)
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            else
                _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        }
        if(rand()%5==0)
        {
            if(_moteurPhy->colBlobCourant()<3)
                _moteurPhy->gauche(&_master,&_slave);
            else
                _moteurPhy->droite(&_master,&_slave);
            return;

        }

        if(l1==-1 && l2 == -1)
        {
            if(rand()%2==0)
            {
                gauche(_colMin);
                std::cerr<< "5-\n ";
            }
            else if(rand()%2==0)
            {
                droite(_colMin);
                std::cerr<< "10-\n ";

            }
            else
            {
                verticalBas(_colMin);
                std::cerr<< "11-\n ";

            }
            return;

        }
        /* if(l1 == l2 )
         {
             vertical(l1);
             std::cerr<< "1-\n ";
             return;
         }*/
        if(l1-l2 == 1 || l1-l2 == -1)
        {
            if(l2>l1)
            {
                droite(l1);
                std::cerr<< "2-\n ";

                return;
            }
            else
            {
                gauche(l1);
                std::cerr<< "3-\n ";

                return;
            }
        }
        if(l1==-1 && l2 != -1)
        {
            verticalBas(l2);
            std::cerr<< "4-\n ";
            return;
        }
        if(l2 == -1 && l1!=  -1)
        {
            verticalHaut(l1);
            std::cerr<< "6-\n ";
            return;
        }
        verticalHaut(l1);
        std::cerr<< "7-\n ";
        return;




        return;

    }

    void majLineUp()
    {
        for(int c=0; c<6; ++c)
            for(int l=4; l<18; l++)
                if((*_grille)(l,c)->color()!=BLANK)
                {
                    _lineUp[c] = (*_grille)(l,c)->color();
                }
        for(int i=0; i<6; ++i)
            std::cerr<<_lineUp[i];
        std::cerr<<std::endl;
    }
    void majLineEmpty()
    {
        int max[6] = {-1,-1,-1,-1,-1,-1};
        int min= 0;
        for(int c=0; c<6; ++c)
            for(int l=0; l<18; l++)
                if((*_grille)(l,c)->color()==BLANK)
                {
                    max[c] = l;
                }

        for(int i=0; i<6; ++i)
        {
            if(rand()%2==0)
            {
                if(min<=max[i])
                {
                    min = max[i];
                    _colMin = i;
                }
            }
            else
            {
                if(min<max[i])
                {
                    min = max[i];
                    _colMin = i;
                }
            }
        }




    }

    /*     for(int i=0;i<6;++i)
     std::cerr<<_lineUp[i];
     std::cerr<<std::endl;*/


    void  vertical(int col)
    {
        if(_moteurPhy->orientation()==HAUT ||_moteurPhy->orientation()== BAS)
        {
            if(rand()%10==0)
            _moteurPhy->speedUp();
            return;
        }
        else if(_moteurPhy->orientation()==DROITE)
        {
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        }
        else
        {
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            return;
        }
        gotocol(col);
        return;

    }

    int checkLigne(int color)
    {

        for(int i=0; i<6; ++i)
            if(color == _lineUp[i])
            {
                return i;
            }
        return -1;

    }
    void droite(int col)
    {
        switch(_moteurPhy->orientation())
        {
        case DROITE :
            break;
        case HAUT :
        case GAUCHE :
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        case BAS :
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            return;
        }
        gotocol(col);
        return;
    }
    void gauche(int col)
    {
        switch(_moteurPhy->orientation())
        {
        case GAUCHE :
            break;
        case BAS :
        case DROITE :
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        case HAUT :
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            return;
        }
        gotocol(col);
        return;

    }
    void  verticalBas(int col)
    {
        if(_moteurPhy->orientation()== BAS)
        {
            gotocol(col);
            return;
        }
        else if(_moteurPhy->orientation()==HAUT)
        {
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        }
        else if(_moteurPhy->orientation()==DROITE)
        {
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        }
        else
        {
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            return;
        }


    }
    void  verticalHaut(int col)
    {
        std::cerr<< "orienation : "<< _moteurPhy->orientation()<< "\n";
        if(_moteurPhy->orientation()== HAUT)
        {
            gotocol(col);
            return;
        }
        else if(_moteurPhy->orientation()==BAS)
        {
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        }
        else if(_moteurPhy->orientation()==GAUCHE)
        {
            _moteurPhy->rotationHoraire(&_master,&_slave);
            return;
        }
        else
        {
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            return;
        }


    }
    void gotocol(int col)
    {
        std::cerr<< "goto\n ";

        if(_moteurPhy->colBlobCourant()>col)
        {
            _moteurPhy->gauche(&_master,&_slave);
            return;
        }
        if(_moteurPhy->colBlobCourant()<col)
        {
            _moteurPhy->droite(&_master,&_slave);
            return;
        }
        if(rand()%10==0)
        _moteurPhy->speedUp();
        return;
    }
    void easy()
    {
        int comp = rand()%21;
        switch(comp)
        {
        case 0 :
            _moteurPhy->rotationAntiHoraire(&_master,&_slave);
            break;
        case 1 :
            _moteurPhy->rotationHoraire(&_master,&_slave);
            break;
        case 2 :
        case 3 :
        case 4 :
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 :
            _moteurPhy->droite(&_master,&_slave);
            break;
        case 10 :
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            _moteurPhy->gauche(&_master,&_slave);
            break;
        case 18:
        case 19:
        case 20:
            break;
        case 21:
        if(rand()%10==0)
            _moteurPhy->speedUp();
            break;

        default :
            break;

        }
    }
};

#endif

