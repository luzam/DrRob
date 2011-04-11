#include "../include/Game.h"

/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::go()
{
    initBlobs();
    SDL_Surface *ecran = NULL;
    SDL_Event event; /* La variable contenant l'�v�nement */
    int continuer = 1; /* Notre bool�en pour la boucle */


    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("DrRob", NULL);

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        SDL_WaitEvent(&event); /* On attend un �v�nement qu'on r�cup�re dans event */
        switch(event.type) /* On teste le type d'�v�nement */
        {
        case SDL_QUIT: /* Si c'est un �v�nement QUITTER */
            continuer = 0; /* On met le bool�en � 0, donc la boucle va s'arr�ter */
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arr�te le programme */
                continuer = 0;
                 break;
            case SDLK_LEFT :
                _dashBoards.at(0).moteurPhy()->gauche();
                break;
            case SDLK_RIGHT :
                _dashBoards.at(0).moteurPhy()->droite();
                break;
            case SDLK_DOWN :
                _dashBoards.at(0).moteurPhy()->speedUp();
                break;
            case SDLK_UP :
                _dashBoards.at(0).moteurPhy()->rotationHoraire();
                break;

                default : break;
            }
            break;
        }

        for(size_t i=0; i<_dashBoards.size(); i++)
            _dashBoards.at(i).go();
        //on blit tout
        // SDL_blit ...
        //SDL_Flip(ecran); /* On met � jour l'affichage */
    }

}

