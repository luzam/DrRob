<<<<<<< HEAD
#include "../include/InterfaceX.h"
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
SDL_Surface* InterfaceX::load_img( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if ( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
        if ( optimizedImage != NULL )
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255, 255, 0 ) );
    }
    else
    {
        std::cout<<"Erreur Chargement image"<<std::endl;
    }
    return optimizedImage;
}
void InterfaceX::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool InterfaceX::init()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
    _screen = SDL_SetVideoMode( _SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, SDL_SWSURFACE |SDL_DOUBLEBUF );
    if ( _screen == NULL )
        return false;
    SDL_WM_SetCaption( "Dr.Robotnik Mean Bean Machine - Zamunerstein Hoarau ROB4 2011", NULL );
    return true;
}

bool InterfaceX::resize_files()
{
    int nbJoueursX=round((_nbJoueurs+0.1)/2);
    double d_h_ini=_dashboard_ini->h;

    int resizedDashW = ((double)_screen->h/2)*((double)_dashboard_ini->w)/((double)_dashboard_ini->h);
    std::cout<<"Taille dash W resized : "<<resizedDashW<<std::endl;
    if(nbJoueursX*resizedDashW<=_screen->w) //On verifie que les dash rentrent bien dans l'ecran <---->
    {
        std::cout<<"Assez de place en W"<<std::endl;
        if (_nbJoueurs<=2)
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h);
        else
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h/2);
    }
    else   //si c'est trop grand, on calcule la taille des dash en fonction de _screen->w/NbJoueurx
    {
        std::cout<<"PAS Assez de place en W--> resize en H"<<std::endl;
        img_zoom_pixel_W(_dashboard_ini,_screen->w/nbJoueursX);

    }
    _ratio=(double)_dashboard->h/d_h_ini;
    _background=rotozoomSurfaceXY(_background_ini,0,1/((double)_background_ini->w/(double)_screen->w),1/((double)_background_ini->h/(double)_screen->h),1);
    std::cout<<"Resize des blobs"<<std::endl;
    double ratioBlob = (_taille_blob_ini)/d_h_ini;
    int nb_blobs_par_h=12;
    double taille_blob =_dashboard->h*nb_blobs_par_h*_taille_blob_ini/d_h_ini;
    std::cout<<"taille_blobs_h : "<<taille_blob<<" Ratio : "<<ratioBlob<<std::endl;
    _blobs=img_zoom_pixel_H(_blobs_ini,taille_blob);
    _taille_blob=taille_blob/12;
    std::cout<<"Un blob mesure : "<<_taille_blob<<" px de coté"<<std::endl;
    return true;
}

/** @brief Calcule les positions des differents dashboard
*
*
*/
bool InterfaceX::compute_vDash()
{
    int nbJoueursX=2;
    if(_nbJoueurs>2)
        nbJoueursX=round((_nbJoueurs+0.1)/2);
    std::cout<<"xNb joueurs en X :  "<<nbJoueursX<<std::endl;

    int posX=0,posY=0;
    if(_nbJoueurs>2)
        posY=_screen->h/2-_dashboard->h;
    for (int j=0; j<_nbJoueurs; j++)
    {
        _vDash.at(j).setX(posX);
        _vDash.at(j).setY(posY);
        posX+=_dashboard->w;
        if(j==nbJoueursX-1 && _nbJoueurs>2)
        {
            posX=0;
            posY+=_dashboard->h;
        }
    }
    int decalage=(_screen->w -nbJoueursX*_dashboard->w)/2;
    for (int j=0; j<_nbJoueurs; j++)
    {
        _vDash.at(j).setX(_vDash.at(j).x()+decalage);
    }
    return true;
}
bool InterfaceX::decouper_sprite()
{


    return true;
}
void InterfaceX::blit_fond()
{
    apply_surface(0,0,_background,_screen,NULL);
}
void InterfaceX::blits(std::vector<DashBoard> dashBoards)
{
    blit_fond();
    blit_dash();
    blit_blobs(dashBoards);
}
void InterfaceX::blit_dash()
{
    for(size_t j=0; j<_vDash.size(); j++) //Affichage des dashboard en utilisant le vecteur de coordonnee
        apply_surface(_vDash.at(j).x(),_vDash.at(j).y(),_dashboard,_screen,NULL);
}

void InterfaceX::blit_un_blob(Blobs* blob,int x,int y){
    SDL_Rect offset=offset_sprite(blob->color(),blob->link(),blob->state());
    apply_surface(x,y,_blobs,_screen,&offset);


}
void InterfaceX::blit_blobs_mobiles(Position pmaster,Position pslave,Blobs* master,Blobs* slave)
{
    blit_un_blob(master,pmaster.x(),pmaster.y());
    blit_un_blob(slave,pslave.x(),pslave.y());
}
void InterfaceX::blit_blobs(std::vector<DashBoard> dashBoards)
{

    int blobx,bloby;
    int offsetgrillex;
    int offsetgrilley;
    for(size_t j=0; j<dashBoards.size(); j++)
    {
        for(int l=0; l<6; l++)
        {
            for(int c=0; c<13; c++)
            {
                if( ((*(dashBoards.at(j).grille()))(l,c))->color()!=BLANK)
                {
                    //On se place au debut de la grille
                    offsetgrillex=(_offset_dash_grille).x()+_vDash.at(j).x();
                    offsetgrilley=(_offset_dash_grille).y()+_vDash.at(j).y();
                    //On calcule les coordonnées des blobs
                    blobx=l*_taille_blob;
                    bloby=c*_taille_blob;

                    blit_un_blob(((*(dashBoards.at(j).grille()))(l,c)),offsetgrillex+blobx,offsetgrilley+bloby);
                }
            }
        }
    }




}
SDL_Rect InterfaceX::offset_sprite(int color,int link,int etat)
{
    SDL_Rect r;
    int tb=_taille_blob;
    std::cout<<"Taille blob : "<<tb<<std::endl;
    r.h=tb;
    r.w=tb;
    r.x=link*tb;
    r.y=2*color*tb;
    std::cout<<"Sprite x : "<<r.x<<" y : "<<r.y<<std::endl;

    return r;
}
bool InterfaceX::compute_offsets()
{
    std::cout<<"Calcul offsets"<<std::endl;

    _offset_dash_grille.setX((9)*(_ratio));
    _offset_dash_grille.setY((32-_taille_blob_ini)*(_ratio));
    std::cout<<"Offset grille : "<<(_offset_dash_grille).x()<<"x"<<(_offset_dash_grille).y()<<"  RATIO : "<<1/_ratio<<std::endl;
    return true;
}

bool InterfaceX::load_files()
{
#ifdef WINDOWS
    if (_chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#else
    if (chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#endif
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return errno;
    }

    std::cout<< cCurrentPath<<std::endl;
    _background_ini = load_img("background.png");
    _dashboard_ini = load_img("dashboard.png");
    _blobs_ini = load_img( "blobs.png" );

    if ( _blobs_ini == NULL || _background_ini==NULL || _blobs_ini==NULL)
    {
        std::cout<<"Erreur chargement"<<std::endl;
        return false;
    }
    return true;
}
void InterfaceX::clean_up()
{
    SDL_FreeSurface( _blobs );
    SDL_FreeSurface( _background);
    SDL_FreeSurface(_background);
    SDL_Quit();
}

SDL_Surface* InterfaceX::img_zoom_pixel_W(SDL_Surface *surface1,int pixel)
{
    double carre=pixel;
    double carre2=surface1->w;
    double zoom=(double)carre/(double)carre2;
    SDL_Surface *tmp=rotozoomSurfaceXY(surface1,0,zoom,zoom,1);
    SDL_FreeSurface(surface1);
    return tmp;
}
SDL_Surface* InterfaceX::img_zoom_pixel_H(SDL_Surface *surface1,int pixel)
{
    double carre=pixel;
    double carre2=surface1->h;
    double zoom=(double)carre/(double)carre2;
    SDL_Surface *tmp=rotozoomSurfaceXY(surface1,0,zoom,zoom,1);
    SDL_FreeSurface(surface1);
    return tmp;
}

/*int main( int argc, char* args[] )
{
    //Ce qui va nous permettre de quitter
    bool quit = false;

    //Initialisation
    if( init() == false )
    {
        return 1;
    }

    //Chargement des fichiers
    if( load_files() == false )
    {
        return 1;
    }

    //On coupe la partie en haut à gauche (premier sprite)
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = SHEET_WIDTH/2;
    clip[ 0 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en haut à droite (second sprite)
    clip[ 1 ].x = SHEET_WIDTH/2;
    clip[ 1 ].y = 0;
    clip[ 1 ].w = SHEET_WIDTH/2;
    clip[ 1 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en bas à gauche (troisième sprite)
    clip[ 2 ].x = 0;
    clip[ 2 ].y = SHEET_HEIGHT/2;
    clip[ 2 ].w = SHEET_WIDTH/2;
    clip[ 2 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en bas à droite (quatrième sprite)
    clip[ 3 ].x = SHEET_WIDTH/2;
    clip[ 3 ].y = SHEET_HEIGHT/2;
    clip[ 3 ].w = SHEET_WIDTH/2;
    clip[ 3 ].h = SHEET_HEIGHT/2;

    //On remplit l'écran de blanc
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

    //On applique les sprites sur l'écran
    apply_surface( 0, 0, faces, screen, &clip[ 0 ] );
    apply_surface( SCREEN_WIDTH-(SHEET_WIDTH/2), 0, faces, screen, &clip[ 1 ] );
    apply_surface( 0, SCREEN_HEIGHT-(SHEET_HEIGHT/2), faces, screen, &clip[ 2 ] );
    apply_surface( SCREEN_WIDTH-(SHEET_WIDTH/2), SCREEN_HEIGHT-(SHEET_HEIGHT/2), faces, screen, &clip[ 3 ] );

    //Mise à jour de l'écran
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //Tant que l'utilisateur n'a pas quitter
    while( quit == false )
    {
        //Tant qu'il y a un événement
        while( SDL_PollEvent( &event ) )
        {
            //Si l'utilisateur à appuyer sur le X de la fenêtre
            if( event.type == SDL_QUIT )
            {
                //On quitte le programme
                quit = true;
            }
        }
    }

    //On libère les images et on quitte SDL
    clean_up();*/
=======
#include "../include/InterfaceX.h"
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
SDL_Surface* InterfaceX::load_img( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if ( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
        if ( optimizedImage != NULL )
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255, 255, 0 ) );
    }
    else
    {
        std::cout<<"Erreur Chargement image"<<std::endl;
    }
    return optimizedImage;
}
void InterfaceX::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool InterfaceX::init()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
    _screen = SDL_SetVideoMode( _SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, SDL_SWSURFACE |SDL_DOUBLEBUF );
    if ( _screen == NULL )
        return false;
    SDL_WM_SetCaption( "Dr.Robotnik Mean Bean Machine - Zamunerstein Hoarau ROB4 2011", NULL );
    return true;
}
bool InterfaceX::resize_img_W(double pixel)
{
    _dashboard=img_zoom_pixel_W(_dashboard_ini,pixel);
////////

    return true;
}
bool InterfaceX::resize_img_H(double pixel)
{

    _dashboard=img_zoom_pixel_H(_dashboard_ini,pixel);
    /*  int nb_blobs_par_h=12;
      double taille_blob =_dashboard->h*ratio*nb_blobs_par_h;
      _blobs=img_zoom_pixel_H(_blobs_ini,taille_blob);*/

    return true;
}
bool InterfaceX::resize_files()
{
    int nbJoueursX=round((_nbJoueurs+0.1)/2);
    double d_h_ini=_dashboard_ini->h;

    int resizedDashW = ((double)_screen->h/2)*((double)_dashboard_ini->w)/((double)_dashboard_ini->h);
    std::cout<<"Taille dash W resized : "<<resizedDashW<<std::endl;
    if(nbJoueursX*resizedDashW<=_screen->w) //On verifie que les dash rentrent bien dans l'ecran <---->
    {
        std::cout<<"Assez de place en W"<<std::endl;
        if (_nbJoueurs<=2)
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h);
        else
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h/2);
    }
    else   //si c'est trop grand, on calcule la taille des dash en fonction de _screen->w/NbJoueurx
    {
        std::cout<<"PAS Assez de place en W--> resize en H"<<std::endl;
        resize_img_W(_screen->w/nbJoueursX);

    }
    _ratio=(double)_dashboard->h/d_h_ini;
    _background=rotozoomSurfaceXY(_background_ini,0,1/((double)_background_ini->w/(double)_screen->w),1/((double)_background_ini->h/(double)_screen->h),1);
    std::cout<<"Resize des blobs"<<std::endl;
    double ratioBlob = (_taille_blob_ini)/d_h_ini;
    int nb_blobs_par_h=12;
    double taille_blob =_dashboard->h*nb_blobs_par_h*_taille_blob_ini/d_h_ini;
    std::cout<<"taille_blobs_h : "<<taille_blob<<" Ratio : "<<ratioBlob<<std::endl;
    _blobs=img_zoom_pixel_H(_blobs_ini,taille_blob);
    _taille_blob=taille_blob/12;
    std::cout<<"Un blob mesure : "<<_taille_blob<<" px de coté"<<std::endl;
    return true;
}

/** @brief Calcule les positions des differents dashboard
*
*
*/
bool InterfaceX::compute_vDash()
{
    int nbJoueursX=2;
    if(_nbJoueurs>2)
        nbJoueursX=round((_nbJoueurs+0.1)/2);
    std::cout<<"xNb joueurs en X :  "<<nbJoueursX<<std::endl;

    int posX=0,posY=0;
    if(_nbJoueurs>2)
        posY=_screen->h/2-_dashboard->h;
    for (int j=0; j<_nbJoueurs; j++)
    {
        _vDash.at(j).setX(posX);
        _vDash.at(j).setY(posY);
        posX+=_dashboard->w;
        if(j==nbJoueursX-1 && _nbJoueurs>2)
        {
            posX=0;
            posY+=_dashboard->h;
        }
    }
    int decalage=(_screen->w -nbJoueursX*_dashboard->w)/2;
    for (int j=0; j<_nbJoueurs; j++)
    {
        _vDash.at(j).setX(_vDash.at(j).x()+decalage);
    }
    return true;
}
bool InterfaceX::decouper_sprite()
{


    return true;
}
void InterfaceX::blit_fond(){
 apply_surface(0,0,_background,_screen,NULL);
}
void InterfaceX::blits(std::vector<DashBoard> dashBoards){
blit_fond();
blit_dash();
blit_blobs(dashBoards);
}
void InterfaceX::blit_dash(){
    for(size_t j=0; j<_vDash.size(); j++) //Affichage des dashboard en utilisant le vecteur de coordonnee
        apply_surface(_vDash.at(j).x(),_vDash.at(j).y(),_dashboard,_screen,NULL);
}
void InterfaceX::blit_blobs(std::vector<DashBoard> dashBoards)
{
    SDL_Rect offset;
    int blobx,bloby;
    int offsetgrillex;
    int offsetgrilley;
    Grille<Blobs>* grille;
    for(size_t j=0; j<dashBoards.size(); j++)
    {
        grille=(dashBoards.at(j).grille());
        for(int l=0; l<6; l++)
        {
            for(int c=0; c<13; c++)
            {
                if( ((*grille)(l,c))->color()!=BLANK)
                {
                    //On se place au debut de la grille
                    offsetgrillex=(_offset_dash_grille).x()+_vDash.at(j).x();
                    offsetgrilley=(_offset_dash_grille).y()+_vDash.at(j).y();
                    //On calcule les coordonnées des blobs
                    blobx=l*_taille_blob;
                    bloby=c*_taille_blob;
                    //calcul de la position dans le sprite
                    offset=offset_sprite(((*grille)(l,c))->color(),((*grille)(l,c))->link(),((*grille)(l,c))->state());
                    // Blit des Blobs (ahah)
                    apply_surface(offsetgrillex+blobx,offsetgrilley+bloby,_blobs,_screen,&offset);
                }
            }
        }
    }




}
SDL_Rect InterfaceX::offset_sprite(int color,int link,int etat)
{
    SDL_Rect r;
    int tb=_taille_blob;
    std::cout<<"Taille blob : "<<tb<<std::endl;
    r.h=tb;
    r.w=tb;
    r.x=link*tb;
    r.y=2*color*tb;
    std::cout<<"Sprite x : "<<r.x<<" y : "<<r.y<<std::endl;

    return r;
}
bool InterfaceX::compute_offsets()
{
    std::cout<<"Calcul offsets"<<std::endl;

    _offset_dash_grille.setX((9)*(_ratio));
    _offset_dash_grille.setY((32-_taille_blob_ini)*(_ratio));
    std::cout<<"Offset grille : "<<(_offset_dash_grille).x()<<"x"<<(_offset_dash_grille).y()<<"  RATIO : "<<1/_ratio<<std::endl;
    return true;
}

bool InterfaceX::load_files()
{
#ifdef WINDOWS
    if (_chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#else
    if (chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#endif
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return errno;
    }

    std::cout<< cCurrentPath<<std::endl;
    _background_ini = load_img("background.png");
    _dashboard_ini = load_img("dashboard.png");
    _blobs_ini = load_img( "blobs.png" );

    if ( _blobs_ini == NULL || _background_ini==NULL || _blobs_ini==NULL)
    {
        std::cout<<"Erreur chargement"<<std::endl;
        return false;
    }
    return true;
}
void InterfaceX::clean_up()
{
    SDL_FreeSurface( _blobs );
    SDL_FreeSurface( _background);
    SDL_FreeSurface(_background);
    SDL_Quit();
}

SDL_Surface* InterfaceX::img_zoom_pixel_W(SDL_Surface *surface1,int pixel)
{
    double carre=pixel;
    double carre2=surface1->w;
    double zoom=(double)carre/(double)carre2;
    SDL_Surface *tmp=rotozoomSurfaceXY(surface1,0,zoom,zoom,1);
    SDL_FreeSurface(surface1);
    return tmp;
}
SDL_Surface* InterfaceX::img_zoom_pixel_H(SDL_Surface *surface1,int pixel)
{
    double carre=pixel;
    double carre2=surface1->h;
    double zoom=(double)carre/(double)carre2;
    SDL_Surface *tmp=rotozoomSurfaceXY(surface1,0,zoom,zoom,1);
    SDL_FreeSurface(surface1);
    return tmp;
}

/*int main( int argc, char* args[] )
{
    //Ce qui va nous permettre de quitter
    bool quit = false;

    //Initialisation
    if( init() == false )
    {
        return 1;
    }

    //Chargement des fichiers
    if( load_files() == false )
    {
        return 1;
    }

    //On coupe la partie en haut à gauche (premier sprite)
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = SHEET_WIDTH/2;
    clip[ 0 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en haut à droite (second sprite)
    clip[ 1 ].x = SHEET_WIDTH/2;
    clip[ 1 ].y = 0;
    clip[ 1 ].w = SHEET_WIDTH/2;
    clip[ 1 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en bas à gauche (troisième sprite)
    clip[ 2 ].x = 0;
    clip[ 2 ].y = SHEET_HEIGHT/2;
    clip[ 2 ].w = SHEET_WIDTH/2;
    clip[ 2 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en bas à droite (quatrième sprite)
    clip[ 3 ].x = SHEET_WIDTH/2;
    clip[ 3 ].y = SHEET_HEIGHT/2;
    clip[ 3 ].w = SHEET_WIDTH/2;
    clip[ 3 ].h = SHEET_HEIGHT/2;

    //On remplit l'écran de blanc
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

    //On applique les sprites sur l'écran
    apply_surface( 0, 0, faces, screen, &clip[ 0 ] );
    apply_surface( SCREEN_WIDTH-(SHEET_WIDTH/2), 0, faces, screen, &clip[ 1 ] );
    apply_surface( 0, SCREEN_HEIGHT-(SHEET_HEIGHT/2), faces, screen, &clip[ 2 ] );
    apply_surface( SCREEN_WIDTH-(SHEET_WIDTH/2), SCREEN_HEIGHT-(SHEET_HEIGHT/2), faces, screen, &clip[ 3 ] );

    //Mise à jour de l'écran
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //Tant que l'utilisateur n'a pas quitter
    while( quit == false )
    {
        //Tant qu'il y a un événement
        while( SDL_PollEvent( &event ) )
        {
            //Si l'utilisateur à appuyer sur le X de la fenêtre
            if( event.type == SDL_QUIT )
            {
                //On quitte le programme
                quit = true;
            }
        }
    }

    //On libère les images et on quitte SDL
    clean_up();*/
>>>>>>> 74d0c2fb173a69cc94fba289722cf1b1a7716709
