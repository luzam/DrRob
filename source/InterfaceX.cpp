#include "../include/InterfaceX.h"
#ifdef WIN32
#define WINDOWS
#endif
#ifdef X64
#define WINDOWS
#endif
#ifdef WINDOWS
#include <direct.h>
#endif
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
bool InterfaceX::resize_img(double pixel)
{
    double ratio = (_taille_blob)/_dashboard_ini->h;
    std::cout<<"Taille dashboard : "<<_dashboard_ini->w<<"x"<<_dashboard_ini->h<<std::endl;
    std::cout<<"Ratio : "<<ratio<<std::endl;

    _dashboard=img_zoom_pixel(_dashboard_ini,pixel);
    int nb_blobs_par_h=12;
    double taille_blob =_dashboard->h*ratio*nb_blobs_par_h;
    _blobs=img_zoom_pixel(_blobs_ini,taille_blob);
    std::cout<<"Taille dashboard : "<<_dashboard->w<<"x"<<_dashboard->h<<std::endl;
    if (_background==NULL || _blobs==NULL || _background==NULL)
        return false;
    return true;
}

bool InterfaceX::resize_files()
{

    if (_nbJoueurs<=2)
        resize_img(_screen->h);
    else
        resize_img((_screen->h)/2);
    return true;
}
bool InterfaceX::compute_pos_dashboards(){
    for(int i=0;i<_nbJoueurs;i++){


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
    //Chargement de la feuille de sprite
    _background = load_img("background.png");
    _dashboard_ini = load_img("dashboard.png");
    _blobs_ini = load_img( "blobs.png" );

    //S'il y a eu un problème au chargement de la feuille de sprites
    if ( _blobs_ini == NULL || _background==NULL || _blobs_ini==NULL)
    {
        return false;
    }
    //Si tout s'est bien passé
    return true;
}
void InterfaceX::clean_up()
{
    SDL_FreeSurface( _blobs );
    SDL_FreeSurface(_background);
    SDL_Quit();
}

SDL_Surface* InterfaceX::img_zoom_pixel(SDL_Surface *surface1,int pixel)
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
