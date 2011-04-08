#include "../include/InterfaceX.h"
#include <direct.h>
SDL_Surface* InterfaceX::load_image( std::string filename )
{
    //L'image qui est charg�e
    SDL_Surface* loadedImage = NULL;

    //L'image optimis�e qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );

    //Si l'image est charg�e
    if( loadedImage != NULL )
    {
        //Cr�ation de l'image optimis�e
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Lib�ration de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si la cr�ation de l'image optimis�e s'est bien pass�e
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //On retourne l'image optimis�e
    return optimizedImage;
}
void InterfaceX::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool InterfaceX::init()
{
    //Initialisation de tous les sous-syst�mes de SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Mise en place de l'�cran
    _screen = SDL_SetVideoMode( _SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, SDL_SWSURFACE );

    //S'il y a une erreur lors de la mise en place de l'�cran
    if( _screen == NULL )
    {
        return false;
    }

    //Mise en place de la barre caption
    SDL_WM_SetCaption( "Split the faces", NULL );

    //Si tout s'est bien pass�
    return true;
}
bool InterfaceX::load_files()
{
    if(_chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
    //Chargement de la feuille de sprite
    _blobs = load_image( "puyo3.png" );

    //S'il y a eu un probl�me au chargement de la feuille de sprites
    if( _blobs == NULL )
    {
        return false;
    }

    //Si tout s'est bien pass�
    return true;
}
void InterfaceX::clean_up()
{
    //On lib�re la feuille de sprites
    SDL_FreeSurface( _blobs );
    SDL_FreeSurface(_background);
    //On quitte SDL
    SDL_Quit();
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

    //On coupe la partie en haut � gauche (premier sprite)
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = SHEET_WIDTH/2;
    clip[ 0 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en haut � droite (second sprite)
    clip[ 1 ].x = SHEET_WIDTH/2;
    clip[ 1 ].y = 0;
    clip[ 1 ].w = SHEET_WIDTH/2;
    clip[ 1 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en bas � gauche (troisi�me sprite)
    clip[ 2 ].x = 0;
    clip[ 2 ].y = SHEET_HEIGHT/2;
    clip[ 2 ].w = SHEET_WIDTH/2;
    clip[ 2 ].h = SHEET_HEIGHT/2;

    //On coupe la partie en bas � droite (quatri�me sprite)
    clip[ 3 ].x = SHEET_WIDTH/2;
    clip[ 3 ].y = SHEET_HEIGHT/2;
    clip[ 3 ].w = SHEET_WIDTH/2;
    clip[ 3 ].h = SHEET_HEIGHT/2;

    //On remplit l'�cran de blanc
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

    //On applique les sprites sur l'�cran
    apply_surface( 0, 0, faces, screen, &clip[ 0 ] );
    apply_surface( SCREEN_WIDTH-(SHEET_WIDTH/2), 0, faces, screen, &clip[ 1 ] );
    apply_surface( 0, SCREEN_HEIGHT-(SHEET_HEIGHT/2), faces, screen, &clip[ 2 ] );
    apply_surface( SCREEN_WIDTH-(SHEET_WIDTH/2), SCREEN_HEIGHT-(SHEET_HEIGHT/2), faces, screen, &clip[ 3 ] );

    //Mise � jour de l'�cran
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //Tant que l'utilisateur n'a pas quitter
    while( quit == false )
    {
        //Tant qu'il y a un �v�nement
        while( SDL_PollEvent( &event ) )
        {
            //Si l'utilisateur � appuyer sur le X de la fen�tre
            if( event.type == SDL_QUIT )
            {
                //On quitte le programme
                quit = true;
            }
        }
    }

    //On lib�re les images et on quitte SDL
    clean_up();*/
