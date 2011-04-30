#ifndef CLOCK_H
#define CLOCK_H
#include <SDL.h>

class Clock{

protected :

size_t _temps_prec;
size_t _temps_act;
public :
    Clock():
    _temps_prec(0),_temps_act(0){}
    ~Clock(){}

    bool tic(size_t periodeMinMs){
        bool retour = false;
        _temps_act = SDL_GetTicks();
        if(_temps_act-_temps_prec > periodeMinMs){
        retour = true;
        _temps_prec = _temps_act;
        }
        return retour;
    }
    int temps_prec()const{return _temps_prec;}
    int temps_act()const{return _temps_act;}
};



#endif //CLOCK_H
