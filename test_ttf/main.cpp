/*******************************************************/
/** Programme de PERRUCHON Romain pour developpez.com **/
/**               Chapitre V : SDL_TTF                **/
/*******************************************************/

//Les fichiers d'entête
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

//Les attributs de l'ecran (640 * 480)
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Les surfaces
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//La structure d'evenement
SDL_Event event;

//Le font qu'on va utiliser
TTF_Font *font;

//La couleur du font
SDL_Color textColor = { 255, 255, 255 };

SDL_Surface *load_image( std::string filename )
{
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;

    //L'image optimisée que nous utiliserons par la suite
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );

    //Si l'image est chargée correctement
    if( loadedImage != NULL )
    {
        //creation de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //liberation de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //si l'image optimisée créé est bonne
        if( optimizedImage != NULL )
        {
            //transparence
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //on retourne l'image optimisé
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //on blit la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //initialisation de tout les sous-systemes de sdl
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //on met en place l'ecran
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //Si il y a une erreur lors de la mise en place de l'ecran
    if( screen == NULL )
    {
        return false;
    }

    //Initialisation de SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //on met en place la barre caption de la fenetre
    SDL_WM_SetCaption( "TTF Test", NULL );

    //si tout s'est bien passé
    return true;
}

bool load_files()
{
    //chargement du fond
    background = load_image( "background.png" );

    //Ouverture du font
    font = TTF_OpenFont( "CaslonBold.ttf", 28 );

    //si il y a un probleme au chargement du fond
    if( background == NULL )
    {
        return false;
    }

    //Si il y a une erreur au chargement du font
    if( font == NULL )
    {
        return false;
    }

    //Si tout s'est bien passé
    return true;
}

void clean_up()
{
    //Liberation des surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );

    //On ferme le font qu'on a utilisé
    TTF_CloseFont( font );

    //On quitte SDL_ttf
    TTF_Quit();

    //On quitte SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //ce qui va nous permettre de quitter
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

    //application du texte
    message = TTF_RenderText_Solid( font, "Test pour sdl_ttf", textColor );

    //Si il y a une erreur lors de l'application du texte
    if( message == NULL )
    {
        return 1;
    }

    //Application des surfaces(images) sur l'ecran
    apply_surface( 0, 0, background, screen );
    apply_surface( 200, 200, message, screen );

    //mise à jour de l'ecran
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //Tant que l'utilisateur n'a pas quitter
    while( quit == false )
    {
        //tant qu'il y a un evenement dans le handler
        while( SDL_PollEvent( &event ) )
        {
            //Si l'utilisateur ferme la fenetre avec le X
            if( event.type == SDL_QUIT )
            {
                //On quitte le programme
                quit = true;
            }
        }
    }

    //liberation des surface et on quitte sdl
    clean_up();

    return 0;
}
