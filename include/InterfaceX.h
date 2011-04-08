#ifndef INTERFACEX_H_INCLUDED
#define INTERFACEX_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "SDL_rotozoom.h"

class InterfaceX
{
protected:
    const int _SCREEN_WIDTH;
    const int _SCREEN_HEIGHT;
    const int _SCREEN_BPP;
    double _dash_W;
    double _dash_H;
    const double _taille_blob;
    SDL_Surface *_blobs;
    const int _nbJoueurs;
    SDL_Rect *offset_dash_grille;
    SDL_Rect *offset_dash_nextBlob;
    SDL_Rect *offset_dash_score;
    SDL_Surface *_dashboard;
    SDL_Surface *_background;
    SDL_Surface *_screen;
    SDL_Surface *_dashboard_ini;
    SDL_Surface *_blobs_ini;
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Color _textColor;
public:
    InterfaceX(int nbJoueurs):_SCREEN_WIDTH(700),_SCREEN_HEIGHT(200),_SCREEN_BPP(32),_taille_blob(16),_nbJoueurs(nbJoueurs)
    {


    }
    ~InterfaceX()
    {
        std::cout<<"Fermeture interface"<<std::endl;
        clean_up();
        std::cout<<"Interface fermee avec succes"<<std::endl;
    }
    SDL_Surface* load_img( std::string filename );
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
    bool init();
    bool load_files();
    void clean_up();
    SDL_Surface* screen(){return _screen;}
    SDL_Event event(){return _event;}
    SDL_Surface* blobs(){return _blobs;}
    SDL_Surface* background(){return _background;}
    SDL_Surface* dashboard(){return _dashboard;}
    bool resize_files();
    SDL_Surface* img_zoom_pixel(SDL_Surface *surface1,int pixel);
    bool resize_img(double pixel);
};
#endif // INTERFACEX_H_INCLUDED
