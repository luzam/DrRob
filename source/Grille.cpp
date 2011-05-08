#include "../include/Grille.h"


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::checkHole()
{
    bool falling = false;
    for(int l=17; l>=0; --l)
        for(int c=5; c>=0; --c)
            if((_grille)[6*l+c].state()==FALLING)
            {
                if((_grille)[6*l+c].current()!=0)
                {
                    _grille[6*l+c].setFalling(_grille[l*6+c].current()-_tailleBlob/6);
                    if((_grille)[6*l+c].current()<=0)
                    {
                        switchBlobs(l,c,l+_grille[6*l+c].fallingCol(),c);
                        _grille[6*l+c].setState(NO_STATE);

                        std::cout<<"->[ "<<l<<" --> "<< l+_grille[6*l+c].fallingCol()<< " ] <\n";
                    }
                }
            }
            else if((_grille)[6*l+c].state()==FALLIN_ANIM)
            {
                if((_grille)[6*l+c].current()!=0)
                {
                    _grille[6*l+c].setFallingAnim(_grille[l*6+c].current()-_tailleBlob/6);
                }
            }
            else if((_grille)[6*l+c].state()==LANDING)
            {
                if((_grille)[6*l+c].current()>0)
                    _grille[6*l+c].setLanding(_grille[l*6+c].current()-1);
                if(_grille[6*l+c].current()==0)
                    _grille[6*l+c].setState(NO_STATE);
            }

}

int Grille::checkFalling()
{
    int max = 0;
    for(int l=17; l>=0; --l)
        for(int c=5; c>=0; --c)
            if((_grille)[6*l+c].state()==FALLING)
                max = (max <=_grille[6*l+c].current())?_grille[6*l+c].current() : max;
    return max;

}

int Grille::checkLanding()
{
    int max = 0;
    for(int l=17; l>=0; --l)
        for(int c=5; c>=0; --c)
            if((_grille)[6*l+c].state()==LANDING)
                max = (max <=_grille[6*l+c].current())?_grille[6*l+c].current() : max;
    return max;

}
int Grille::checkMaxCombo()
{
    int max = 0;
    for(int l=17; l>=0; --l)
        for(int c=5; c>=0; --c)
            if((_grille)[6*l+c].state()==COMBOTING)
                max = (max <=_grille[6*l+c].current())?_grille[6*l+c].current() : max;
    return max;

}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::checkState()
{
    for(int l=0; l<18; l++)
        for(int c=0; c<6; c++)
            if(_grille.at(6*l+c).color()==BLANK)
            {
                _grille.at(6*l+c).setState(NO_STATE);
                _grille.at(6*l+c).setLink(NO_LINK);
            }

}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::checkLink()
{
    for(int l=0; l<18; l++)
        for(int c=0; c<6; c++)
        {
            int s=0,n=0,w=0,e=0;
            int color = _grille.at(6*l+c).color();
            if(color==BLANK||color==DARK)
                continue;
            if(l!=17)
                if(_grille[(l+1)*6+c].color()==color)
                    s=1;
            if(l!=0)
                if(_grille[(l-1)*6+c].color()==color)
                    n=1;
            if(c!=5)
                if(_grille[l*6+c+1].color()==color)
                    e=1;
            if(c!=0)
                if(_grille[l*6+c-1].color()==color)
                    w=1;
            setLink(l,c,n,s,e,w);
        }


}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::setLink(int l, int c, int n, int s, int e, int w)
{
    if(n)
    {
        if(s)
        {
            if(w)
            {
                if(e)
                    _grille.at(6*l+c).setLink(SEWN);
                else
                    _grille.at(6*l+c).setLink(WNS);
            }
            else
            {
                if(e)
                    _grille.at(6*l+c).setLink(SEN);
                else
                    _grille.at(6*l+c).setLink(SN);
            }
        }
        else
        {
            if(w)
            {
                if(e)
                    _grille.at(6*l+c).setLink(EWN);
                else
                    _grille.at(6*l+c).setLink(WN);
            }
            else
            {
                if(e)
                    _grille.at(6*l+c).setLink(NE);
                else
                    _grille.at(6*l+c).setLink(N);
            }
        }
    }
    else
    {
        if(s)
        {
            if(w)
            {
                if(e)
                    _grille.at(6*l+c).setLink(EWS);
                else
                    _grille.at(6*l+c).setLink(SW);
            }
            else
            {
                if(e)
                    _grille.at(6*l+c).setLink(SE);
                else
                    _grille.at(6*l+c).setLink(S);
            }
        }
        else
        {
            if(w)
            {
                if(e)
                    _grille.at(6*l+c).setLink(EW);
                else
                    _grille.at(6*l+c).setLink(W);
            }
            else
            {
                if(e)
                    _grille.at(6*l+c).setLink(E);
                else
                    _grille.at(6*l+c).setLink(NO_LINK);
            }
        }
    }
}
/** @brief (one liner)
   *
   * (documentation goes here)
   */
void Grille::checkCombo()
{
    std::cout<<"STATE\n";
    for(int l=0; l<18; l++)
    {
        for(int c=0; c<6; c++)
        {
            std::cout<<_grille[6*l+c].state();
        }
        std::cout<<"\n";
    }
    for(int l=0; l<18; l++)
        for(int c=0; c<6; c++)
            if(_grille[6*l+c].state()==COMBOTING)
            {

                _grille.at(6*l+c).setComboting(_grille.at(6*l+c).current()-1);
                if(_grille.at(6*l+c).color()!=DARK)
                {
                    std::cout<<"---------------->>>>>>>>>>>GRILLECPP>>>>>"<<_grille.at(6*l+c).current()<<"\n";
                    if(l!=0)
                        if(_grille.at(6*(l-1)+c).color()==DARK)
                        {
                            _grille.at(6*(l-1)+c).setState(COMBOTING);
                            _grille.at(6*(l-1)+c).setComboting(_grille.at(6*(l)+c).current());
                        }
                    if(l!=17)
                        if(_grille.at(6*(l+1)+c).color()==DARK)
                        {
                            _grille.at(6*(l+1)+c).setState(COMBOTING);
                            _grille.at(6*(l+1)+c).setComboting(_grille.at(6*(l)+c).current());
                        }
                    if(c!=5)
                        if(_grille.at(6*(l)+c+1).color()==DARK)
                        {
                            _grille.at(6*(l)+c+1).setState(COMBOTING);
                            _grille.at(6*(l)+c+1).setComboting(_grille.at(6*(l)+c).current());
                        }
                    if(c!=0)
                        if(_grille.at(6*(l)+c-1).color()==DARK)
                        {
                            _grille.at(6*(l)+c-1).setState(COMBOTING);
                            _grille.at(6*(l)+c-1).setComboting(_grille.at(6*(l)+c).current());
                        }
                }
            }
    for(int l=0; l<18; l++)
        for(int c=0; c<6; c++)
            if(_grille[6*l+c].state()==COMBOTING && _grille[6*l+c].current()<=0 )
                _grille[6*l+c].setColor(BLANK);
}
/** @brief (one liner)
   *
   * (documentation goes here)
   */
void Grille::switchBlobs(int l1,int c1,int l2,int c2)
{
    _grille[l2*6+c2].setColor(_grille[l1*6+c1].color());
    _grille[l1*6+c1].setColor(BLANK);
    _grille[l1*6+c1].setFalling(0);
    _grille[l1*6+c1].setState(NO_STATE);
    _grille[l2*6+c2].setFalling(0);
    _grille[l2*6+c2].setState(LANDING);
    _grille[l2*6+c2].setLanding(LANDING_ANIM_TIME);
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::check()
{
    //checkCombo();
    checkHole();
    checkLink();
    checkState();

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Grille::checkLoose()
{
    return (_grille.at(6*5+2).color()!=BLANK)?true:false;
}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
int Grille::checkDark(int size)
{
    srand(time(NULL));

    int lignPut =(int) size/6;
    int put=6*lignPut;
    std::cout<< "LIGNE PUT "<<lignPut<<std::endl;
    if(lignPut>0)
    {
        int count=0;
        for(int ligne=4 ; ++count<=lignPut; --ligne)
        {
            for(int i=0; i<6; ++i)
            {
                _grille[ligne*6+i].setColor(DARK);
                _grille[ligne*6+i].setState(FALLING);
            }
            if(ligne==0)
                return size; // temporaire
        }
    }
    while(put!=size)
    {
        int col = rand()%6;
        if(_grille[(4-lignPut)*6+col].color()!=DARK)
        {
            _grille[(4-lignPut)*6+col].setColor(DARK) ;
            _grille[(4-lignPut)*6+col].setState(FALLING);
            put++;
        }
    }

    return put;
}

void Grille::init(){
for(int l=0; l<18; l++)
        for(int c=0; c<6; c++){
            _grille[l*6+c].setState(NO_STATE);
            _grille[l*6+c].setColor(BLANK);}

}
void Grille::animFallin(int taille){
    for(int l=0; l<18; l++)
        for(int c=0; c<6; c++){
        _grille[l*6+c].setState(FALLIN_ANIM);
        _grille[l*6+c].setFallingAnim(2*18*taille);
        _grille[l*6+c].setFallingDepth(2*18*taille);
        _grille[l*6+c].setFallingCol(2*18);
        }
}
