#include "../include/Game.h"
#include "../include/InterfaceX.h"
/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::go()
{
    std::cout<<"On lance le menu"<<std::endl;
    _X->menu();
<<<<<<< HEAD
    _nbJoueurs=_X->NbJoueurs();
    _nbAI=_X->NbAI();
    resize_commandes();
=======
    _nbJoueurs=_X->select_nbJoueurs();
    std::cout<<"Nombre de joueurs : "<<_nbJoueurs<<std::endl;
    _X->setNbJoueurs(_nbJoueurs);
    _turningBool = new std::vector<bool>(_nbJoueurs,false);
>>>>>>> 8e24d3493df2b5f427d2df04b6680b8717f3fb14
    _X->compute_game();
    assert(_nbJoueurs>0);
    initBlobs();
    for(int c=0; c<_nbJoueurs; c++)
        _dashBoards.push_back(DashBoard(_X->taille_blob(),new Grille(),&_randBlobs));
    _combo = (int *) calloc(_nbJoueurs,sizeof(int));

    SDL_Event event; /* La variable contenant l'évènement */
    //SDL_EnableKeyRepeat(100,50);
    int continuer = 1; /* Notre booléen pour la boucle */
    int shining=0;
    int cpt=0;
    _X->blits(_dashBoards);

    // SDL_Init(SDL_INIT_VIDEO);

    // ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    // SDL_WM_SetCaption("DrRob", NULL);

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
            if (keystates[SDLK_LEFT])
                _dashBoards.at(1).moteurPhy()->gauche(_dashBoards.at(1).masterPos(),_dashBoards.at(1).slavePos());
            if (keystates[SDLK_RIGHT])
                _dashBoards.at(1).moteurPhy()->droite(_dashBoards.at(1).masterPos(),_dashBoards.at(1).slavePos());
            if (keystates[SDLK_DOWN])
                _dashBoards.at(1).moteurPhy()->speedUp();
            else
                _dashBoards.at(1).moteurPhy()->speedToNormal();
            if (keystates[SDLK_UP] && !_turningBool->at(1) ){
                _dashBoards.at(1).moteurPhy()->rotationHoraire(_dashBoards.at(1).masterPos(),_dashBoards.at(1).slavePos());
                _turningBool->at(1) = true;}
            if(!keystates[SDLK_UP] )
                _turningBool->at(1) = false;


               //*/ joueur 2
            if (keystates[SDLK_s])
                _dashBoards.at(0).moteurPhy()->gauche(_dashBoards.at(0).masterPos(),_dashBoards.at(0).slavePos());
            if (keystates[SDLK_f])
                _dashBoards.at(0).moteurPhy()->droite(_dashBoards.at(0).masterPos(),_dashBoards.at(0).slavePos());
            if (keystates[SDLK_d])
                _dashBoards.at(0).moteurPhy()->speedUp();
            else
                _dashBoards.at(0).moteurPhy()->speedToNormal();
            if (keystates[SDLK_e])
                _dashBoards.at(0).moteurPhy()->rotationHoraire(_dashBoards.at(0).masterPos(),_dashBoards.at(0).slavePos());
            //*/
        }
        if(_clock.tic(30)){
        if(cpt>=4){
        shining = (shining==0)?1:0;
        cpt=0;
        }
        else
        cpt++;
        for(size_t i=0; i<_dashBoards.size(); i++){
            _dashBoards.at(i).go();
            if(_dashBoards.at(i).launchCombo())
            {
                _combo[i] = _dashBoards.at(i).combo();
                _dashBoards.at(i).resetCombo();
            }
        }
        repartitionCombo();
        _X->blits(_dashBoards);
        for(size_t i=0; i<_dashBoards.size(); i++)
        {
            _X->blit_blobs_mobiles((*_dashBoards.at(i).masterPos()),(*_dashBoards.at(i).slavePos()),
                                   _dashBoards.at(i).masterBlob(),_dashBoards.at(i).slaveBlob(),(int)i,shining);
            _X->blit_nextBlob(_dashBoards.at(i).nextMaster(),_dashBoards.at(i).nextSlave(),(int)i);

        }
        SDL_Flip(_X->screen());
        }
    }
}
/** @brief main loop
  *
  * (documentation goes here)
  */
void Game::repartitionCombo()
{
    if(_dashBoards.size()==1)
        return;
    srand(time(NULL));
    int target =0;
    for(size_t i=0;i<_dashBoards.size();++i)
    {
        if(_combo[i]!=0)
        {
            while(_combo[i]!=0){
                do{
                target = rand() % _dashBoards.size();
                }while(target==(int)i );//|| _dashBoards[target].looser());
                _dashBoards[target].addDarkBlob();
                _combo[i]--;
            }
        }
    }
}
void Game::resize_commandes(){
_commandes.resize(_nbJoueurs,std::vector<int> (SIZE_COMMANDS));
}

