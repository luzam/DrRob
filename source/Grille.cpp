#include "../include/Grille.h"


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::checkHole()
{
    for(int l=12; l>=0; --l)
        for(int c=5; c>=0; --c)
            if((_grille)[6*l+c].state()==FALLING)
            {
                if((_grille)[6*l+c].current()!=0)
                {
                    _grille[6*l+c].setFalling(_grille[l*6+c].current()-3);
                    if((_grille)[6*l+c].current()<=0)
                    {
                        switchBlobs(l,c,l+_grille[6*l+c].fallingCol(),c);
                        _grille[6*l+c].setState(NO_STATE);
                        std::cout<<"->[ "<<l<<" --> "<< l+_grille[6*l+c].fallingCol()<< " ] <\n";
                    }
                }
            }

}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::checkState()
{
    for(int l=0; l<13; l++)
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
    for(int l=0; l<13; l++)
        for(int c=0; c<6; c++)
        {
            int s=0,n=0,w=0,e=0;
            int color = _grille.at(6*l+c).color();
            if(color==BLANK)
                continue;
            if(l!=12)
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
    for(int l=0; l<13; l++)
    {
        for(int c=0; c<6; c++)
        {
            std::cout<<_grille[6*l+c].state();
        }
        std::cout<<"\n";
    }
    for(int l=0; l<13; l++)
        for(int c=0; c<6; c++)
            if(_grille[6*l+c].state()==COMBOTING)
            {

                _grille.at(6*l+c).setComboting(_grille.at(6*l+c).current()-1);
                std::cout<<"---------------->>>>>>>>>>>GRILLECPP>>>>>"<<_grille.at(6*l+c).current()<<"\n";
                if(l!=0)
                    if(_grille.at(6*(l-1)+c).color()==DARK)
                    {
                        _grille.at(6*(l-1)+c).setState(COMBOTING);
                        _grille.at(6*(l-1)+c).setComboting(_grille.at(6*(l)+c).current());
                    }
                if(l!=12)
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
    for(int l=0; l<13; l++)
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
    _grille[l2*6+c2].setState(FIXED);
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::check()
{
    checkCombo();
    checkHole();
    checkLink();
    checkState();

}
