#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>//temporaire
#include <assert.h>
#include <vector>
#include "Blobs.h"
#include "time.h"
#include "stdlib.h"
class Grille{

protected :
    std::vector<Blobs> _grille;
    void checkLink();
    void checkState();
    void checkHole();
    void checkCombo();
    void setLink(int l, int c, int n, int s, int e, int w);
    public :
    Grille():_grille(18*6){
        std::cout<<"grille()\n";
    for(int c=0;c<18*6;c++)
    std::fill(_grille.begin(), _grille.end(), Blobs());
    std::cout<<"FIN grille()\n";
    }

    ~Grille(){
    }
    bool checkLoose();
    void check();
    int checkDark(int size);
    void switchBlobs(int l1,int c1,int l2,int c2);
    Blobs* operator()(int ligne,int col)
    {
        assert(6*ligne+col<18*6);
        return &(_grille.at(6*ligne + col));
    }
    void operator()(int ligne,int col,Blobs value)
    {
        assert(6*ligne+col<18*6);
        _grille.at(6*ligne + col) = value;
    }
};

#endif
