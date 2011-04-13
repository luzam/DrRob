#ifndef INTERFACEX_H_INCLUDED
#define INTERFACEX_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "SDL_rotozoom.h"
#include <vector>
#include "Position.h"
#include "DashBoard.h"
class InterfaceX
{
protected:
    const int _SCREEN_WIDTH;
    const int _SCREEN_HEIGHT;
    const int _SCREEN_BPP;
    const int _taille_blob_ini;
    int _taille_blob;
    double _ratio_avat_ini;
    const int _nbJoueurs;
    Position _offset_dash_grille;
    Position _offset_dash_nextBlob;
    Position _offset_dash_score;
    Position _offset_dash_avatar;
    double _ratio;
    std::vector<Position> _vDash;
    SDL_Surface *_dashboard;
    SDL_Surface *_background;
    SDL_Surface *_blobs;
    SDL_Surface *_avatars;
    SDL_Surface *_avatars_ini;
    SDL_Surface *_screen;
    SDL_Surface *_dashboard_ini;
    SDL_Surface *_background_ini;
    SDL_Surface *_blobs_ini;
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Color _textColor;
    int _grille_W;
    int _grille_H;
public:
    InterfaceX(int nbJoueurs):_SCREEN_WIDTH(800),_SCREEN_HEIGHT(600),
    _SCREEN_BPP(32),_taille_blob_ini(16),_taille_blob(16),_nbJoueurs(nbJoueurs),_offset_dash_grille(),_offset_dash_nextBlob()
    ,_offset_dash_score(),_ratio(1),_vDash(nbJoueurs),_dashboard(NULL),_background(NULL),_blobs(NULL),_screen(NULL),_dashboard_ini(NULL),_background_ini(NULL)
    ,_blobs_ini(NULL),_event(),_font(NULL)
    {
    init();
    load_files();
    resize_files();
    compute_vDash();
    compute_offsets();

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
    int taille_blob()const{return _taille_blob;}
    Position offset_grille()const
    {
        return _offset_dash_grille;
    }
    std::vector<Position> vDash()const
    {
        return _vDash;
    }
    SDL_Surface* screen()const
    {
        return _screen;
    }
    SDL_Event* event()
    {
        return &_event;
    }
    SDL_Surface* blobs()const
    {
        return _blobs;
    }
    SDL_Surface* background()const
    {
        return _background;
    }
    SDL_Surface* dashboard()const
    {
        return _dashboard;
    }
    int grille_H()const{return _grille_H;}
    int grille_W()const{return _grille_W;}
    bool resize_files();
    SDL_Surface* img_zoom_pixel_H(SDL_Surface *surface1,int pixel);
    SDL_Surface* img_zoom_pixel_W(SDL_Surface *surface1,int pixel);
    bool compute_offsets();
    bool compute_vDash();
    void blit_dash();
    void blit_fond();
    void blit_avatars();
    void blit_un_blob(Blobs* blob,int x,int y);
    void blit_blobs_mobiles(Position pmaster,Position pslave,Blobs* master,Blobs* slave,int n);
<<<<<<< HEAD
    void blits(std::vector<DashBoard> dashBoards);
=======
    void blits(std::vector<DashBoard> dashBoards);
    bool decouper_sprite();
>>>>>>> d7d89aca3b22ae17b295081c875b67a45bd8d44a
    void blit_nextBlob(Blobs* master,Blobs* slave,int n);
    void blit_blobs(std::vector<DashBoard> dashBoards);
    SDL_Rect offset_sprite(int color,int link,int state);
};
#endif // INTERFACEX_H_INCLUDED

