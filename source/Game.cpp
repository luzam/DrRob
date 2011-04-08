#include "../include/Game.h"

/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::go()
{
    SDL_Surface *ecran = NULL;
    SDL_Event event; /* La variable contenant l'évènement */
    int continuer = 1; /* Notre booléen pour la boucle */


    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("DrRob", NULL);

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        SDL_WaitEvent(&event); /* On attend un évènement qu'on récupère dans event */
        switch(event.type) /* On teste le type d'évènement */
        {
        case SDL_QUIT: /* Si c'est un évènement QUITTER */
            continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                continuer = 0;
                 break;
                default : break;
            }
            break;
        }
        for(int i=0; i<_dashBoards.size(); i++)
            _dashBoards.at(i).moteurPhy().moove();
        //on blit tout
        // SDL_blit ...
        //SDL_Flip(ecran); /* On met à jour l'affichage */
    }

}

