#include "../include/Game.h"
#include "../include/InterfaceX.h"
/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::go()
{
    while(1)
    {
        bool winner = false;
        int winer = 0;
        int winnerDelay = 100;
        _X->initialisation_debut_jeu();

        if(_X->menu()==-1)
        {
            //On quitte
            return;
        }
        _nbJoueurs=_X->NbJoueurs();
        _nbAI=_X->NbAI();
        _X->setNbJoueurs(_nbJoueurs+_nbAI);
        std::vector<bool> _turningBool(_nbJoueurs,false);
        std::vector<bool> _turninghBool(_nbJoueurs,false);
        _X->compute_game();
        assert(_nbJoueurs+_nbAI>0);
        initBlobs();
        srand(time(NULL));
        _dashBoards.clear();
        for(int c=0; c<_nbJoueurs; c++)
            _dashBoards.push_back(new Joueur(_X->taille_blob(),new Grille((int)(_X->taille_blob())),&_randBlobs));
        for(int c = 0 ; c<_nbAI; c++){
            if(rand()%3==0)
            _dashBoards.push_back(new Easy(_X->taille_blob(),new Grille((int)(_X->taille_blob())),&_randBlobs));
            else
            _dashBoards.push_back(new Hard(_X->taille_blob(),new Grille((int)(_X->taille_blob())),&_randBlobs));
        }
        _combo = (int *) calloc(_nbJoueurs+_nbAI,sizeof(int));
        SDL_Event event;
        int continuer = 1;
        _X->blits(_dashBoards);

        while (continuer) /* TANT QUE la variable ne vaut pas 0 */
        {
            while(SDL_PollEvent(&event)) /* On attend un évènement qu'on récupère dans event */
            {
                if (event.type==SDL_QUIT)  /* Si c'est un évènement QUITTER */
                {
                    continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
                }
                Uint8 *keystates = SDL_GetKeyState( NULL );
                    if (keystates[SDLK_ESCAPE]) /* Appui sur la touche Echap, on arrête le programme */
                    continuer = 0;
                for (int i=0; i<_nbJoueurs; i++)
                {


                    if (keystates[(_X->Commandes())[i][CGAUCHE]])
                        _dashBoards.at(i)->moteurPhy()->gauche(_dashBoards.at(i)->masterPos(),_dashBoards.at(i)->slavePos());
                    if (keystates[(_X->Commandes())[i][CDROITE]])
                        _dashBoards.at(i)->moteurPhy()->droite(_dashBoards.at(i)->masterPos(),_dashBoards.at(i)->slavePos());
                    if (keystates[(_X->Commandes())[i][CBAS]])
                        _dashBoards.at(i)->moteurPhy()->speedUp();
                    else
                        _dashBoards.at(i)->moteurPhy()->speedToNormal();
                    if ((keystates[(_X->Commandes())[i][CHORAIRE]] )&& !_turningBool.at(i) )
                    {
                        _dashBoards.at(i)->moteurPhy()->rotationHoraire(_dashBoards.at(i)->masterPos(),_dashBoards.at(i)->slavePos());
                        _turningBool.at(i) = true;
                    }
                    if(!keystates[(_X->Commandes())[i][CHORAIRE]] )
                        _turningBool.at(i) = false;
                    if (keystates[(_X->Commandes())[i][CANTIHORAIRE]] && !_turninghBool.at(i) )
                    {
                        _dashBoards.at(i)->moteurPhy()->rotationAntiHoraire(_dashBoards.at(i)->masterPos(),_dashBoards.at(i)->slavePos());
                        _turninghBool.at(i) = true;
                    }
                    if(!keystates[(_X->Commandes())[i][CANTIHORAIRE]] )
                        _turninghBool.at(i) = false;

                }
            }

            if(_clock.tic(20))
            {
                for(size_t i=0; i<_dashBoards.size(); i++)
                    if(_dashBoards[i]->moteurPhy()->speedUpBool())
                        _dashBoards.at(i)->go();
                if(_nbJoueurs+_nbAI >1)
                {
                    int jvivant= 0;
                    for(size_t i=0; i<_dashBoards.size(); i++)
                    {
                        if(_dashBoards[i]->looser())
                            jvivant++;
                        else winer=i;
                    }
                    if(jvivant>= _nbJoueurs+_nbAI - 1)
                        winner = true;
                    if(winner && (winnerDelay--)==0)
                    {
                        continuer = 0;
                        _X->winner(winer);
                        SDL_Flip(_X->screen());
                        while(SDL_WaitEvent(&event)){
                        Uint8* keystates = SDL_GetKeyState( NULL );
                        if(keystates[SDLK_RETURN])
                            break;
                        }
                    }
                }
                if(_clock.tac())
                {

                    // ici mises a jours du jeu, horloge plus lente et indépendantes
                    for(size_t i=0; i<_dashBoards.size(); i++)
                    {
                        _dashBoards.at(i)->think();
                        _dashBoards.at(i)->go();
                        if(_dashBoards.at(i)->launchCombo())
                        {
                            _combo[i] = _dashBoards.at(i)->combo()+6*_dashBoards.at(i)->multiplicateur();
                            _dashBoards.at(i)->resetCombo();
                        }
                    }
                }




                //ici les animations indépendantes du fonctionnements du jeu type shining
                _X->blits(_dashBoards);
                repartitionCombo(winner);
                for(size_t i=0; i<_dashBoards.size(); i++)
                    _X->maj_anims(*_dashBoards[i]);
                for(size_t i=0; i<_dashBoards.size(); i++)
                {
                    _X->blit_blobs_mobiles((*_dashBoards.at(i)->masterPos()),(*_dashBoards.at(i)->slavePos()),
                                           _dashBoards.at(i)->masterBlob(),_dashBoards.at(i)->slaveBlob(),(int)i);
                    _X->blit_nextBlob(_dashBoards.at(i)->nextMaster(),_dashBoards.at(i)->nextSlave(),(int)i);

                }
                SDL_Flip(_X->screen());
            }
        }
        for(int c=0; c<_nbJoueurs+_nbAI ; c++)
            delete _dashBoards[c];
        free(_combo);
    }
}
/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::repartitionCombo(bool winner)
{
    if(_dashBoards.size()==1 || winner)
        return;
    srand(time(NULL));
    int target =0;
    for(size_t i=0; i<_dashBoards.size(); ++i)
    {
        if(_combo[i]!=0)
        {
            while(_combo[i]!=0)
            {
                do
                {
                    target = rand() % _dashBoards.size();
                }
                while(target==(int)i || _dashBoards[target]->looser());
                _dashBoards[target]->addDarkBlob();
                _combo[i]--;
            }
        }
    }
}

