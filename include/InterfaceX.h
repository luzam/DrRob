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
    SDL_Surface *_background;
    SDL_Surface *_screen;
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Color _textColor;
public:
    // InterfaceX(int nbJoueurs):_SREEN_WIDTH
    SDL_Surface* load_image( std::string filename );
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
    bool init();

};
#endif // INTERFACEX_H_INCLUDED
