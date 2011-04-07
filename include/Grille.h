#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <assert.h>

class Grille{

protected :
    int* _grille;
    public :
    Grille(){
    _grille = new int[13*6];
    for(int c=0;c<13*6;c++)
        _grille[c] = 0;
    }
    Grille(char a){
    _grille = new int[13*6];
    for(int l=0;l<13;l++)
        for(int c=0;c<6;c++){
            if(l<10)
                _grille[l*6+c] = 0;
            else if(l==10){
                if(c<3)
                    _grille[l*6+c] = 2;
                else
                    _grille[l*6+c] = 1;
            }
            else if(l==11){
                if(c<2)
                    _grille[l*6+c] = 2;
                else
                    _grille[l*6+c] = 3;
            }
            else if(l==12){
                if(c<4)
                    _grille[l*6+c] = 3;
                else
                    _grille[l*6+c] = 1;
            }

        }
    }
    ~Grille(){
    delete[] _grille;
    }
    int operator()(int ligne,int col) const
    {
        assert(6*ligne+col<13*6);
        return _grille[6*ligne + col];
    }
};

#endif
