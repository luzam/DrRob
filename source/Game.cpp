#include "../include/Game.h"
#include "../include/InterfaceX.h"
/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::go()
{
    SDL_Event event; /* La variable contenant l'évènement */
    SDL_EnableKeyRepeat(1,10000);
    int continuer = 1; /* Notre booléen pour la boucle */
    _X->blits(_dashBoards);

   // SDL_Init(SDL_INIT_VIDEO);

   // ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
   // SDL_WM_SetCaption("DrRob", NULL);

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        SDL_PollEvent(&event); /* On attend un évènement qu'on récupère dans event */
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
            case SDLK_LEFT :
                _dashBoards.at(0).moteurPhy()->gauche(_dashBoards.at(0).masterPos(),_dashBoards.at(0).slavePos());
                break;
            case SDLK_RIGHT :
                _dashBoards.at(0).moteurPhy()->droite(_dashBoards.at(0).masterPos(),_dashBoards.at(0).slavePos());
                break;
            case SDLK_DOWN :
                _dashBoards.at(0).moteurPhy()->speedUp();
                break;
            case SDLK_UP :
                _dashBoards.at(0).moteurPhy()->rotationHoraire(_dashBoards.at(0).masterPos(),_dashBoards.at(0).slavePos());
                break;

                default : break;
            }
            break;
        }
        _X->blits(_dashBoards);
        for(size_t i=0; i<_dashBoards.size(); i++)
            _dashBoards.at(i).go();

        for(size_t i=0; i<_dashBoards.size(); i++){
            _X->blit_blobs_mobiles((*_dashBoards.at(i).masterPos()),(*_dashBoards.at(i).slavePos()),
                                   _dashBoards.at(i).masterBlob(),_dashBoards.at(i).slaveBlob(),(int)i);
            _X->blit_nextBlob(_dashBoards.at(i).nextMaster(),_dashBoards.at(i).nextSlave(),(int)i);

        }
        SDL_Flip(_X->screen());
    }

}

