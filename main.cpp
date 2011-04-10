#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include "include/SDL_rotozoom.h"
#include <iostream>
#include <time.h>
#include "include/Color.h"
#include "include/InterfaceX.h"
//#endif
//#include "include/DashBoard.h"
#include "include/Game.h"
//#include "include/Game.h"

//*//main lucas
int main( int argc, char* argv[] )
{
    //////////////////////CREATION D'UNE GRILLE DE TEST
    srand(time(NULL));
    int r=0;
    Grille<Blobs>* maGrille = new Grille<Blobs>();
    for(int l=0; l<6; l++)
    {
        for(int c=0; c<13; c++)
        {
            std::cout<<Color(rand() %6);

            (*maGrille)(l,c).setColor(Color(rand() %6+1));
          //  std::cout<<((*maGrille)(l,c)).color();
        }
        std::cout<<""<<std::endl;
    }
    bool quit=false;
  //  Game drRob(1,16);
  ////////////////////////////////CREATION DE L'INTERFACE DE TEST
    InterfaceX i(4);
    i.init();
    i.load_files();
    i.resize_files();
    i.compute_vDash();
    i.compute_offsets();
    std::cout<<"screen x : "<<i.screen()->w<<" screen y : "<<i.screen()->h<<std::endl;
    i.apply_surface(0,0,i.background(),i.screen(),NULL);
/////////////////////////////////BLIT DES ELEMENTS
    for(size_t j=0; j<i.vDash().size(); j++) //Affichage des coordonnées du vecteur de coordonnee des dashboard
        std::cout<<"x : "<<i.vDash().at(j).x()<<" y : "<<i.vDash().at(j).y()<<std::endl;

    for(size_t j=0; j<i.vDash().size(); j++) //Affichage des dashboard en utilisant le vecteur de coordonnee
        i.apply_surface(i.vDash().at(j).x(),i.vDash().at(j).y(),i.dashboard(),i.screen(),NULL);
    std::cout<<"Blobs : "<<i.blobs()->w<<"x"<<i.blobs()->h<<std::endl;

    for(size_t j=0; j<i.vDash().size(); j++) //affichage des blobs utilisant le veteur et l'offset de la grille
        i.apply_surface((i.offset_grille()).x()+i.vDash().at(j).x(),(i.offset_grille()).y()+i.vDash().at(j).y(),i.blobs(),i.screen(),NULL);


    if( SDL_Flip( i.screen() ) == -1 )
    {
        return 1;
    }
    while( quit == false )
    {
        while( SDL_PollEvent( &(i.event()) ))
        {
            if( i.event().type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }
//    drRob.go();
    //dash.moteurPhy().majCombo();
    return 0;
}

/*//main antoine
#include "include/MoteurPhy.h"
#include "include/Game.h"
#include "include/InterfaceX.h"
<<<<<<< HEAD
int main( int argc, char* args[] ){
    bool quit=false;
    std::cout<<"DrRob cree par Antoine Hoarau"<<std::endl;
    Grille* grille = new Grille('t');
    MoteurPhy turboteur(8,1,grille);
    turboteur.majCombo();
    InterfaceX i(4);
    i.init();
    i.load_files();
    i.resize_files();
    //Mise à jour de l'écran
    i.apply_surface(0,0,i.background(),i.screen(),NULL);
    i.apply_surface(0,0,i.dashboard(),i.screen(),NULL);
    i.apply_surface(0,0,i.blobs(),i.screen(),NULL);
    if( SDL_Flip( i.screen() ) == -1 )
    {
        return 1;
    }
    while( quit == false )
    {
        while( SDL_PollEvent( &(i.event()) ))
        {
            if( i.event().type == SDL_QUIT )
            {
                quit = true;
            }
        }
=======
//*
int main( int argc, char* args[] ){
    bool quit=false;
    std::cout<<"DrRob cree par Antoine Hoarau"<<std::endl;
    Grille* grille = new Grille('t');
    MoteurPhy turboteur(8,1,grille);
    turboteur.majCombo();
    InterfaceX i(1);
    i.init();
    i.load_files();
    //Mise à jour de l'écran
    i.apply_surface(0,0,i.background(),i.screen(),NULL);
    i.apply_surface(0,0,i.blobs(),i.screen(),NULL);
    if( SDL_Flip( i.screen() ) == -1 )
    {
        return 1;
    }
    while( quit == false )
    {
        while( SDL_PollEvent( &(i.event()) ) )
        {
            if( i.event().type == SDL_QUIT )
            {
                quit = true;
            }
        }
>>>>>>> 34e72849bb5c128eb5c85d0323267dfb9fc06bd8
    }
>>>>>>> 836f6b904f659c1ecb7f7c3d71c60d9a972d4ef5:main.cpp
    return 0;
}
//*/

/*

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
        std::cout<<"SDL erreur"<<std::endl;
        return false;
    }

    //on met en place l'ecran
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //Si il y a une erreur lors de la mise en place de l'ecran
    if( screen == NULL )
    {
        std::cout<<"Screen erreur"<<std::endl;
        return false;
    }

    //Initialisation de SDL_ttf
    if( TTF_Init() == -1 )
    {
        std::cout<<"TTF erreur"<<std::endl;
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
    font = TTF_OpenFont( "ARIAL.TTF", 28 );

    //si il y a un probleme au chargement du fond
    if( background == NULL )
    {
        std::cout<<"background erreur"<<std::endl;
        return false;
    }

    //Si il y a une erreur au chargement du font
    if( font == NULL )
    {
        std::cout<<"Font erreur"<<std::endl;
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
    std::cout<<"Debut programme"<<std::endl;
    //ce qui va nous permettre de quitter
    bool quit = false;

    //Initialisation
    if( init() == false )
    {
        std::cout<<"init erreur"<<std::endl;
        return 1;
    }

    //Chargement des fichiers
    if( load_files() == false )
    {
        std::cout<<"load erreur"<<std::endl;
        return 2;
    }

    //application du texte
    message = TTF_RenderText_Solid( font, "Test pour sdl_ttf", textColor );

    //Si il y a une erreur lors de l'application du texte
    if( message == NULL )
    {
        std::cout<<"message erreur"<<std::endl;
        return 1;
    }

    //Application des surfaces(images) sur l'ecran
    apply_surface( 0, 0, background, screen );
    apply_surface( 200, 200, message, screen );

    //mise à jour de l'ecran
    if( SDL_Flip( screen ) == -1 )
    {
        std::cout<<"Flip erreur"<<std::endl;
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
*/
