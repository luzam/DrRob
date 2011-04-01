#ifndef GRILLE_H
#define GRILLE_H

class Grille{

protected :
    int* _grille;

    public :
    Grille(){
    _grille = new int[13*6];
    delete[] _grille;
    }
    int operator()(size_t ligne,size_t col) const
    {
        assert(6*ligne+col<13*6);
        return _grille[6*ligne + col];
    }
};

#endif
