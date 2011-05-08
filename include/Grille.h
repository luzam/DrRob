#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>//temporaire
#include <assert.h>
#include <vector>
#include "Blobs.h"
#include "time.h"
#include "stdlib.h"
#define LANDING_ANIM_TIME 12


class Grille{

protected :
    std::vector<Blobs> _grille;

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
    int checkFalling();
    int checkLanding();
    void check();
    void checkLink();
    void checkState();
    void checkHole();
    void checkCombo();
    int checkDark(int size);
    int checkMaxCombo();
    void animFallin(int taille);
    void switchBlobs(int l1,int c1,int l2,int c2);
    void init();
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
