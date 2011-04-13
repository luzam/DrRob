#include "../include/Grille.h"


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Grille::checkHole() {}
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
void Grille::check()
{
    checkHole();
    checkLink();
    checkState();

}
