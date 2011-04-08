#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <assert.h>
#include <vector>
template <typename X>
class Grille{

protected :
    std::vector<X> _grille;
    public :
    Grille():_grille(13*6){
    for(int c=0;c<13*6;c++)
    std::fill(_grille.begin(), _grille.end(), X(0));
    }

    ~Grille(){
    delete[] _grille;
    }
    X operator()(int ligne,int col) const
    {
        assert(6*ligne+col<13*6);
        return _grille.at(6*ligne + col);
    }
    void operator()(int ligne,int col,X value)
    {
        assert(6*ligne+col<13*6);
        _grille.at(6*ligne + col) = value;
    }
};

#endif
