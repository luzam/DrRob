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
    Game drRob(1,16);
    drRob.go();


//    drRob.go();
    //dash.moteurPhy().majCombo();
    return 0;
}

