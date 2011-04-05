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
    for(int c=0;c<13*6;c++)
        _grille[c] = (5*c)%6;
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
