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
#ifdef WIN32
#define WINDOWS
#endif
#ifdef X64
#define WINDOWS
#endif
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include "../include/Color.h"
#include "../include/Link.h"
#include "../include/State.h"
#include "../include/Blobs.h"
#include "../include/Position.h"
#include <time.h>
class InterfaceX
{
protected:
    const int _SCREEN_WIDTH;
    const int _SCREEN_HEIGHT;
    const int _SCREEN_BPP;
    std::vector<std::vector<SDL_Surface*> > _blobsIMG_ini;
    std::vector<std::vector<SDL_Surface*> > _blobsIMG;

    const int _taille_blob_ini;
    double _taille_blob;
    int _decalage_menu_x;
    int _decalage_menu_y;
    double _ratio_avat_ini;
    int _nbJoueurs;
    double _ratio_menu;
    Position _offset_grille;
    Position _offset_nextBlob;
    Position _offset_score;
    Position _offset_avatar;
    Position _offset_cursor;
    SDL_Rect _offset_menu;
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
    SDL_Surface *_menu_ini;
    SDL_Surface *_menu;
    SDL_Surface *_cursor_ini;
    SDL_Surface *_cursor;
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Color _textColor;
    int _grille_W;
    int _grille_H;
public:
    InterfaceX(int w,int h):_SCREEN_WIDTH(w),_SCREEN_HEIGHT(h),
    _SCREEN_BPP(32),_blobsIMG_ini(),_taille_blob_ini(16),_taille_blob(16),_decalage_menu_x(0),_decalage_menu_y(0), _ratio_avat_ini(54.0/80.0),_offset_grille(),_offset_nextBlob()
    ,_offset_score(),_ratio(1),_vDash(),_dashboard(NULL),_background(NULL),_blobs(NULL),_screen(NULL),_dashboard_ini(NULL),_background_ini(NULL)
    ,_blobs_ini(NULL),_event(),_font(NULL)
    {
         = new std::vector<std::vector<SDL_Surface*> >(COLOR)
        _offset_menu.w=_SCREEN_WIDTH;
        _offset_menu.h=_SCREEN_HEIGHT;
        _offset_menu.x=0;
        _offset_menu.y=0;
        _offset_cursor.setX(83);
        _offset_cursor.setY(73);

    init_SDL();
    load_files();

    }
    ~InterfaceX()
    {
        std::cout<<"Fermeture interface"<<std::endl;
        clean_up();
        std::cout<<"Interface fermee avec succes"<<std::endl;
    }
    void menu();
    void compute_game();
    SDL_Surface* load_img( std::string filename );
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
    bool init_SDL();
    bool load_files();
    void clean_up();
    int taille_blob()const{return _taille_blob;}
    void setNbJoueurs(int n){_nbJoueurs=n;}
    Position offset_grille()const
    {
        return _offset_grille;
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
    void play_anim_menu();
    int select_nbJoueurs();
    void blit_cursor();
    void decouper_sprite();
    void blit_avatars();
    void blit_un_blob(Blobs* blob,int x,int y);
    void blit_blobs_mobiles(Position pmaster,Position pslave,Blobs* master,Blobs* slave,int n);
    void blits(std::vector<DashBoard> dashBoards);
    void blit_menu();
    void resize_menu();
    void blit_nextBlob(Blobs* master,Blobs* slave,int n);
    void blit_blobs(std::vector<DashBoard> dashBoards);
    SDL_Rect offset_sprite(int color,int link,int state);
};
#endif // INTERFACEX_H_INCLUDED

