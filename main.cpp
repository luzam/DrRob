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

int main( int argc, char* argv[] )
{
    //////////////////////CREATION D'UNE GRILLE DE TEST
    srand(time(NULL));
    Grille<Blobs>* maGrille = new Grille<Blobs>();
    for(int l=0; l<6; l++)
    {
        for(int c=0; c<13; c++)
        {
            (*(*maGrille)(l,c)).setColor(Color(rand() %6));
        }
        std::cout<<""<<std::endl;
    }
    bool quit=false;
    //  Game drRob(1,16);
    ////////////////////////////////CREATION DE L'INTERFACE DE TEST
    InterfaceX i(1);
    i.init();
    i.load_files();
    i.resize_files();
    i.compute_vDash();
    i.compute_offsets();
    std::cout<<"Screen : "<<i.screen()->w<<"x"<<i.screen()->h<<std::endl;
    i.apply_surface(0,0,i.background(),i.screen(),NULL);
/////////////////////////////////BLIT DES ELEMENTS
    for(size_t j=0; j<i.vDash().size(); j++) //Affichage des coordonnées du vecteur de coordonnee des dashboard
        std::cout<<"Dash  "<<i.vDash().at(j).x()<<" :: "<<i.vDash().at(j).y()<<std::endl;

    for(size_t j=0; j<i.vDash().size(); j++) //Affichage des dashboard en utilisant le vecteur de coordonnee
        i.apply_surface(i.vDash().at(j).x(),i.vDash().at(j).y(),i.dashboard(),i.screen(),NULL);
    std::cout<<"Blobs : "<<i.blobs()->w<<"x"<<i.blobs()->h<<std::endl;

    SDL_Rect offset_sprite;
    int blobx,bloby;
    int offsetgrillex;
    int offsetgrilley;
    for(int l=0; l<6; l++)
    {
        for(int c=0; c<13; c++)
        {
            if((*(*maGrille)(l,c)).color()!=BLANK)
            {
                //On se place au debut de la grille
                offsetgrillex=(i.offset_grille()).x()+i.vDash().at(0).x();
                offsetgrilley=(i.offset_grille()).y()+i.vDash().at(0).y();
                //On calcule les coordonnées des blobs
                blobx=l*i.taille_blob();
                bloby=c*i.taille_blob();
                std::cout<<"blob  "<<blobx<<" :: "<<bloby<<std::endl;

                offset_sprite=i.offset_sprite((*(*maGrille)(l,c)).color(),(*(*maGrille)(l,c)).link(),(*(*maGrille)(l,c)).state());
                std::cout<<"Offset  "<<offset_sprite.x<<" :: "<<offset_sprite.y<<std::endl;
                i.apply_surface(offsetgrillex+blobx,offsetgrilley+bloby,i.blobs(),i.screen(),&offset_sprite);
            }
        }
    }


    if( SDL_Flip( i.screen() ) == -1 )
    {
        return 1;
    }
    while( quit == false )
    {
        while( SDL_PollEvent(i.event()) )
        {
            if( (*i.event()).type == SDL_QUIT )
            {
                quit = true;
            }
        }
    }
//    drRob.go();
    //dash.moteurPhy().majCombo();
    return 0;
}

