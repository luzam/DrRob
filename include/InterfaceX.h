#ifndef INTERFACEX_H_INCLUDED
#define INTERFACEX_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

class InterfaceX
{
protected:
    const int _SCREEN_WIDTH;
    const int _SCREEN_HEIGHT;
    const int _SCREEN_BPP;
    double _dash_W;
    double _dash_H;
    SDL_Surface *_blobs;
    SDL_Surface *_background;
    SDL_Surface *_screen;
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Color _textColor;
public:
    InterfaceX(int nbJoueurs):_SCREEN_WIDTH(640),_SCREEN_HEIGHT(480),_SCREEN_BPP(32)
    {
        if(nbJoueurs>2)
        {
            _dash_H=_SCREEN_HEIGHT/2;
            _dash_W=11/14*_dash_H;
        }
        else
        {
            _dash_H=_SCREEN_HEIGHT;
            _dash_W=_SCREEN_WIDTH/2;
        }


    }
    ~InterfaceX()
    {
        std::cout<<"Fermeture interface"<<std::endl;
        clean_up();
        std::cout<<"Interface fermee avec succes"<<std::endl;
    }
    SDL_Surface* load_image( std::string filename );
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
    bool init();
    bool load_files();
    void clean_up();
    SDL_Surface* screen(){return _screen;}
    SDL_Event event(){return _event;}
    SDL_Surface* blobs(){return _blobs;}
    SDL_Surface* background(){return _background;}
};
#endif // INTERFACEX_H_INCLUDED
