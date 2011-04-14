#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>//temporaire
#include <assert.h>
#include <vector>
#include "Blobs.h"
class Grille{

protected :
    std::vector<Blobs> _grille;
    void checkLink();
    void checkState();
    void checkHole();
    void checkCombo();
    void setLink(int l, int c, int n, int s, int e, int w);
    public :
    Grille():_grille(13*6){
        std::cout<<"grille()\n";
    for(int c=0;c<13*6;c++)
    std::fill(_grille.begin(), _grille.end(), Blobs());
    std::cout<<"FIN grille()\n";
    }

    ~Grille(){
    }
    void check();
    void switchBlobs(int l1,int c1,int l2,int c2);
    Blobs* operator()(int ligne,int col)
    {
        assert(6*ligne+col<13*6);
        return &(_grille.at(6*ligne + col));
    }
    void operator()(int ligne,int col,Blobs value)
    {
        assert(6*ligne+col<13*6);
        _grille.at(6*ligne + col) = value;
    }
};

#endif
