#include "../include/InterfaceX.h"
/**
* Permet de charger les images optimisees pour l'ecran
**/
SDL_Surface* InterfaceX::load_img( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    return SDL_DisplayFormatAlpha( loadedImage );
}
/**
* Permet de blitter les surfaces a l'ecran
**/
void InterfaceX::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
/**
* Initrialisations des SDL et SDL ttf
**/
bool InterfaceX::init_SDL()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
    if(_SCREEN_HEIGHT==0 || _SCREEN_WIDTH==0)
        _screen = SDL_SetVideoMode( 0, 0, _SCREEN_BPP, SDL_HWSURFACE |SDL_DOUBLEBUF | SDL_FULLSCREEN );
    else
        _screen = SDL_SetVideoMode( _SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, SDL_HWSURFACE |SDL_DOUBLEBUF );
    _SCREEN_HEIGHT=_screen->h;
    _SCREEN_WIDTH=_screen->w;
    if ( _screen == NULL )
        return false;
    SDL_WM_SetCaption( "Dr.Robotnik Mean Bean Machine - Zamunerstein Hoarau ROB4 2011", NULL );
    if ( TTF_Init() == -1 )
        return false;

    return true;
}
/**
* Blit dans le dash les prochains blobs
**/
void InterfaceX::blit_nextBlob(Blobs* master,Blobs* slave,int n)
{
    blit_un_blob(slave,_offset_nextBlob.x()+_vDash[n].x(),_offset_nextBlob.y()+_vDash[n].y()-2*_taille_blob);
    blit_un_blob(master,_offset_nextBlob.x()+_vDash[n].x(),_offset_nextBlob.y()+_vDash[n].y()-_taille_blob);
}
/**
* Afficher le gagnant de la partie
**/
void InterfaceX::winner(int i)
{
    TTF_Font *font= TTF_OpenFont("ARIAL.TTF",_taille_text*1.5);
    SDL_Color textcolor = {255,255,255,0};
    std::ostringstream oss;
    oss<<i+1;
    SDL_Surface* _winner=NULL;
    SDL_Surface* _rectWin=NULL;
    _winner=TTF_RenderText_Solid(font,("Joueur "+oss.str()+" gagne").c_str(),textcolor);
    _rectWin = SDL_CreateRGBSurface(SDL_HWSURFACE, _screen->w,_winner->h*2,32/*_screen->format->BytesPerPixel*/, 0, 0, 0, 0);
    SDL_FillRect(_rectWin, NULL, SDL_MapRGB(_screen->format, 10, 10, 10));
    apply_surface(0,_screen->h/2-_rectWin->h/2,_rectWin,_screen,NULL);
    apply_surface(_screen->w/2-_winner->w/2,_screen->h/2-_winner->h/2,_winner,_screen,NULL);
    SDL_FreeSurface(_winner);
    SDL_FreeSurface(_rectWin);
}
/**
* Joue l'animation du menu
**/
int InterfaceX::play_anim_menu(int init,int fin)
{
    int continuer=1;
    SDL_Event event;
    _offset_menu.x=init;
    int offsetmenux=_offset_menu.x;
    Clock _clock;
    int val=6*_ratio_menu;
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        Uint8 *keystates = SDL_GetKeyState( NULL );
        SDL_PollEvent(&event);



        if(_clock.tic(5))
        {
            blit_menu();
            if(fin-init>=0)
                offsetmenux+=val;
            else
                offsetmenux-=val;

            if(fin>=init)//Si on avance
            {
                if(offsetmenux>=fin)
                {
                    _offset_menu.x=fin;
                    return 0;
                }
            }
            else//si on recule
            {
                if(offsetmenux<=fin)
                {
                    _offset_menu.x=fin;
                    return 0;
                }
            }

            _offset_menu.x=offsetmenux;
            SDL_Flip(_screen);
        }
        if(keystates[SDLK_BACKSPACE] && fin>=init)//On retourne au debut
        {

            while(continuer)
            {

                if(_clock.tic(5))
                {
                    blit_menu();
                    offsetmenux-=val;
                    if(offsetmenux<=init)
                    {
                        _offset_menu.x=init;
                        return -1;
                    }
                    _offset_menu.x=offsetmenux;
                    SDL_Flip(_screen);
                }


            }
        }
    }
    return 1;

}
/**
* Ecran de selection du nombre de joueurs
**/
int InterfaceX::select_nbJoueurs()
{
    int continuer=1;
    blit_menu();
    blit_cursor();
    SDL_Flip(_screen);
    Uint8 *keystates = SDL_GetKeyState( NULL );
    std::ostringstream nbj;
    std::ostringstream nba;
    std::string njoueurs;
    std::string nai;
    SDL_Surface* nbJoueurs=NULL;
    SDL_Surface* nbAI=NULL;
    TTF_Font *font= TTF_OpenFont("ARIAL.TTF",_taille_text);
    SDL_Color textcolor = {240,240,240,0};
    SDL_Event event;
    Clock _clock;
    _offset_menu.x=2*_offset_menu.w;
    int curseur=1;
    int nb_lines=2;
    Position _offset_nbj;
    int decalage_text=20;
    int offx_ini=80*_ratio_menu+_decalage_menu_x;
    int offy_ini=87*_ratio_menu+_decalage_menu_y;
    _offset_nbj.setX(offx_ini+decalage_text*_ratio_menu);
    _offset_nbj.setY(offy_ini-10*_ratio_menu);
    int saut=35*_ratio_menu;
    SDL_EnableKeyRepeat(100,50);
    nbj.str("");
    nbj<<_nbJoueurs;
    nbJoueurs=TTF_RenderText_Solid(font,(nbj.str()).c_str(),textcolor);
    nba.str("");
    nba<<_nbAI;
    nbAI=TTF_RenderText_Solid(font,(nba.str()).c_str(),textcolor);
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {

        while(SDL_PollEvent(&event)) /* On attend un �nement qu'on r�p� dans event */
        {
            keystates = SDL_GetKeyState( NULL );
            nbj.str("");
            nbj<<_nbJoueurs;
            nbJoueurs=TTF_RenderText_Solid(font,(nbj.str()).c_str(),textcolor);
            nba.str("");
            nba<<_nbAI;
            nbAI=TTF_RenderText_Solid(font,(nba.str()).c_str(),textcolor);

            if((_nbJoueurs>=10||_nbAI>=10 )&& (_nbJoueurs<100&&_nbAI<100))
            {
                _offset_cursor.setX(offx_ini-10*_ratio_menu);
                _offset_nbj.setX(offx_ini+(decalage_text-10)*_ratio_menu);
            }
            else if(_nbJoueurs>=100||_nbAI>=100)
            {
                _offset_cursor.setX(offx_ini-20*_ratio_menu);
                _offset_nbj.setX(offx_ini+(decalage_text-20)*_ratio_menu);
            }
            else
            {
                _offset_cursor.setX(offx_ini);
                _offset_nbj.setX(offx_ini+decalage_text*_ratio_menu);
            }

            if (event.type==SDL_QUIT)  /* Si c'est un �nement QUITTER */
            {
                continuer = 0; /* On met le bool� �, donc la boucle va s'arr�r */
            }


            if (keystates[SDLK_ESCAPE]){ /* Appui sur la touche Echap, on arr� le programme */
                //on desalloue
                SDL_FreeSurface(nbJoueurs);
                SDL_FreeSurface(nbAI);
                TTF_CloseFont(font);
                return -1;}
            if(keystates[SDLK_UP])
            {
                if(curseur==1)
                {
                    _offset_cursor.setY(_offset_cursor.y()+(nb_lines-1)*saut);
                    curseur=nb_lines;
                }
                else
                {
                    _offset_cursor.setY(_offset_cursor.y()-saut);
                    curseur--;
                }
            }
            if(keystates[SDLK_DOWN])
            {
                if(curseur==nb_lines)
                {
                    _offset_cursor.setY(_offset_cursor.y()-(nb_lines-1)*saut);
                    curseur=1;
                }
                else
                {
                    _offset_cursor.setY(_offset_cursor.y()+saut);
                    curseur++;
                }

            }
            if(keystates[SDLK_BACKSPACE])
            {//free
                SDL_FreeSurface(nbJoueurs);
                SDL_FreeSurface(nbAI);
                TTF_CloseFont(font);
                return -1;
            }
            if(keystates[SDLK_RIGHT])
            {
                if(curseur==1)
                    _nbJoueurs++;
                else
                    _nbAI++;

            }
            if(keystates[SDLK_LEFT])
            {
                if(curseur==1 && _nbJoueurs>0)
                    _nbJoueurs--;
                else if(_nbAI>0)
                    _nbAI--;

            }
            if(keystates[SDLK_RETURN])
            {
                //free
                SDL_FreeSurface(nbJoueurs);
                SDL_FreeSurface(nbAI);
                TTF_CloseFont(font);
                return 0;
            }


        }
        if(_clock.tic(15))
        {
            blit_menu();
            blit_cursor();
            apply_surface(_offset_nbj.x(),_offset_nbj.y(),nbJoueurs,_screen,NULL);
            apply_surface(_offset_nbj.x(),_offset_nbj.y()+saut,nbAI,_screen,NULL);
            SDL_Flip(_screen);
        }
    }
        SDL_FreeSurface(nbJoueurs);
                SDL_FreeSurface(nbAI);
                TTF_CloseFont(font);
    return 1;
}

/**
* Permet d'enregistrer les controles persos
**/
int InterfaceX::controls()
{
    SDL_Surface *text=NULL;
    SDL_Surface *joueur=NULL;
    std::ostringstream nbj;

    TTF_Font *font= TTF_OpenFont("ARIAL.TTF",_taille_text);
    SDL_Color textcolor = {255,255,255,0};
    SDL_Event event;
    Clock _clock;

    int continuer=1;
    nbj.str("");
    nbj<<1;
    std::string njoueur="Joueur "+nbj.str();
    joueur=TTF_RenderText_Solid(font,njoueur.c_str(),textcolor);
    blit_fond();
    SDL_Flip(_screen);
    std::vector<std::string> controls;
    controls.push_back("GAUCHE");
    controls.push_back("DROITE");
    controls.push_back("BAS");
    controls.push_back("TOURNER DROITE");
    controls.push_back("TOURNER GAUCHE");
    for(int i=0; i<_nbJoueurs; ++i)
    {
        nbj.str("");
        nbj<<(i+1);
        njoueur="Joueur "+nbj.str();
        joueur=TTF_RenderText_Solid(font,njoueur.c_str(),textcolor);


        for(int j=0; j<_nbJoueurs; ++j)
        {
            continuer=1;
            text=TTF_RenderText_Solid(font,controls[j].c_str(),textcolor);
            while(continuer)
            {
                while(SDL_PollEvent(&event)) /* On attend un �nement qu'on r�p� dans event */
                {
                    if(event.type==SDL_KEYDOWN)
                    {
                        _commandes[i][j]=event.key.keysym.sym;
                        continuer=0;
                    }


                    blit_fond();
                    apply_surface(_screen->w/2-text->w/2,_screen->h/2-text->h/2,text,_screen,NULL);
                    apply_surface(_screen->w/2-joueur->w/2,_screen->h/4-joueur->h/2,joueur,_screen,NULL);
                    SDL_Flip(_screen);
                }
            }
        }
        continuer=1;
    }
    SDL_FreeSurface(text);
    SDL_FreeSurface(joueur);
    TTF_CloseFont(font);
    return 1;
}

/**
* Redimensionne le vecteur de commandes
**/
void InterfaceX::controls_resize(){
_commandes.resize(_nbJoueurs,std::vector<int> (SIZE_COMMANDS,0));
}
/**
* Ecrit les commandes par defaut
**/
void InterfaceX::controls_by_default(){
_commandes.resize(4,std::vector<int> (5));
_commandes[0][CGAUCHE]=SDLK_LEFT;
_commandes[0][CDROITE]=SDLK_RIGHT;
_commandes[0][CBAS]=SDLK_DOWN;
_commandes[0][CHORAIRE]=SDLK_UP;
_commandes[0][CANTIHORAIRE]=SDLK_0;

_commandes[1][CGAUCHE]=SDLK_a;
_commandes[1][CDROITE]=SDLK_d;
_commandes[1][CBAS]=SDLK_s;
_commandes[1][CHORAIRE]=SDLK_w;
_commandes[1][CANTIHORAIRE]=SDLK_q;

_commandes[2][CGAUCHE]=SDLK_g;
_commandes[2][CDROITE]=SDLK_j;
_commandes[2][CBAS]=SDLK_h;
_commandes[2][CHORAIRE]=SDLK_y;
_commandes[2][CANTIHORAIRE]=SDLK_t;

_commandes[3][CGAUCHE]=SDLK_k;
_commandes[3][CDROITE]=SDLK_m;
_commandes[3][CBAS]=SDLK_l;
_commandes[3][CHORAIRE]=SDLK_o;
_commandes[3][CANTIHORAIRE]=SDLK_i;

}
/**
* Ecran de demarrage du jeu ou choix des commandes
**/
int InterfaceX::controls_and_start()
{
    //Ici on connait le nb de joueurs
    // ON realloue le vecteur de commandes
    controls_resize();
    int continuer=1;
    SDL_Event event;
    Clock _clock;
    _offset_menu.x=3*_offset_menu.w;
    int curseur=1;
    int nb_lines=2;
    Uint8 *keystates = SDL_GetKeyState( NULL );
    blit_menu();
    blit_cursor();
    SDL_Flip(_screen);
    Position _offset_nbj;
    //  int offx_ini=80*_ratio_menu+_decalage_menu_x;
    int offy_ini=87*_ratio_menu+_decalage_menu_y;
    _offset_cursor.setY(offy_ini);
    int saut=35*_ratio_menu;
    SDL_EnableKeyRepeat(100,50);
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {

        while(SDL_PollEvent(&event)) /* On attend un �nement qu'on r�p� dans event */
        {

            if (event.type==SDL_QUIT)  /* Si c'est un �nement QUITTER */
            {
                continuer = 0; /* On met le bool� �, donc la boucle va s'arr�r */
            }
            keystates = SDL_GetKeyState( NULL );

            if (keystates[SDLK_ESCAPE]) /* Appui sur la touche Echap, on arr� le programme */
                return -1;
            if(keystates[SDLK_UP])
            {
                if(curseur==1)
                {
                    _offset_cursor.setY(_offset_cursor.y()+(nb_lines-1)*saut);
                    curseur=nb_lines;
                }
                else
                {
                    _offset_cursor.setY(_offset_cursor.y()-saut);
                    curseur--;
                }
            }
            if(keystates[SDLK_DOWN])
            {
                if(curseur==nb_lines)
                {
                    _offset_cursor.setY(_offset_cursor.y()-(nb_lines-1)*saut);
                    curseur=1;
                }
                else
                {
                    _offset_cursor.setY(_offset_cursor.y()+saut);
                    curseur++;
                }

            }
            if(keystates[SDLK_BACKSPACE])
            {
                return -1;
            }

            if(keystates[SDLK_RETURN])
            {
                if(curseur==1)
                {
                    continuer=0;
                }
                else if(curseur==2)
                {
                    controls();
                }
            }


        }
        if(_clock.tic(15))
        {
            blit_menu();
            blit_cursor();
            SDL_Flip(_screen);
        }
    }

    return 1;
}
/**
* Ecran menu principal
**/
int InterfaceX::menu()
{
#ifdef WINDOWS
    _chdir("img");
#else
    chdir("img");
#endif
    char cCurrentPath[FILENAME_MAX];
    GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
    int continuer=1;
    SDL_Event event;

    Clock _clock;
    Uint8 *keystates = SDL_GetKeyState( NULL );
    int position_menu=0;
    SDL_EnableKeyRepeat(100,50);
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {

        while(SDL_PollEvent(&event)) /* On attend un �nement qu'on r�p� dans event */
        {
            if (event.type==SDL_QUIT)  /* Si c'est un �nement QUITTER */
            {
                return -1;
            }
            keystates = SDL_GetKeyState( NULL );

            if (keystates[SDLK_ESCAPE]&& position_menu==0) /* Appui sur la touche Echap, on arr� le programme */
                return -1;
            if(keystates[SDLK_RETURN])
            {
                if(position_menu==0)
                {
                    position_menu++;
                    position_menu+=play_anim_menu(_offset_menu.w,2*_offset_menu.w);

                }
            }
        }
        switch(position_menu)
        {
        case 1://choix des joueurs
            switch(select_nbJoueurs())
            {
            case -1://on veut revenir en arriere
                position_menu--;
                position_menu+= play_anim_menu(_offset_menu.x,_offset_menu.x-_offset_menu.w);
                _offset_cursor.setX(80*_ratio_menu+_decalage_menu_x);
                _offset_cursor.setY(87*_ratio_menu+_decalage_menu_y);
                break;
            case 0://on veut avancer
                position_menu++;
                position_menu+=play_anim_menu(_offset_menu.x,_offset_menu.x+_offset_menu.w);
                break;
            default:
                break;
            }
            break;
        case 2://controls et start
            switch(controls_and_start())
            {
            case -1:
                _offset_cursor.setX(80*_ratio_menu+_decalage_menu_x);
                _offset_cursor.setY(87*_ratio_menu+_decalage_menu_y);
                position_menu--;
                position_menu+=play_anim_menu(_offset_menu.x,_offset_menu.x-_offset_menu.w);
                break;
            case 1:
                continuer=0;
                break;
            default:
                break;
            }
            break;
        default://au debut donc on ne fait rien
            break;


        }

        if(_clock.tic(300))
        {
            blit_menu();
            if(position_menu==0)
            {
                if(_offset_menu.x==0)
                    _offset_menu.x+=_offset_menu.w;
                else
                    _offset_menu.x-=_offset_menu.w;
            }
            SDL_Flip(_screen);
        }
    }
    return 0;

}
/**
* Calcul les positions de tout
**/
void InterfaceX::compute_game()
{
    //On fait tous les resize en fonction du nombre de joueurs
    resize_files();
    compute_vDash();
    compute_offsets();

}
/**
* Redimensionne les blobs pour l'ecran
**/
void InterfaceX::resize_blobs(){
    double taille_blob_H =(double)_blobs_ini->h*_ratio;
    double taille_blob_W =(double)_blobs_ini->w*_ratio;
    int dw,dh;
    double zoom=taille_blob_H/(double)_blobs_ini->h;
    double zoom_optimal=zoom;
    rotozoomSurfaceSize(_blobs_ini->w,_blobs_ini->h,0,zoom,&dw,&dh);
    while(dw/20.0!=(int)(dw/20.0))
    {
        if(ceil(dw)==floor(dw))
            zoom_optimal-=0.001;
        else
            zoom_optimal+=0.001;
        rotozoomSurfaceSize(_blobs_ini->w,_blobs_ini->h,0,zoom_optimal,&dw,&dh);

    }

    _taille_blob=(double)dw/20.0;
    _taille_blob=dw/20;
    _grille_W=17*_taille_blob;
    _grille_H=6*_taille_blob;
    resize_blobsIMG();
}



/**
* Redimensionne les dashboards pour l'ecran
**/
void InterfaceX::resize_dash(){
    int nbJoueursX=_nbJoueurs;
    if(_nbJoueurs>2)
        nbJoueursX=round(((double)_nbJoueurs+0.1)/2.0);
    int d_h_ini=_dashboard_ini->h;
    int resizedDashW ;
    if(_nbJoueurs>2)
        resizedDashW = ((_screen->h/2)*(_dashboard_ini->w)/(_dashboard_ini->h));
    else
        resizedDashW = ((_screen->h)*(_dashboard_ini->w)/(_dashboard_ini->h));

    if(nbJoueursX*resizedDashW<=_screen->w) //On verifie que les dash rentrent bien dans l'ecran <---->
    {
        if (_nbJoueurs<=2)
        {
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h);
        }
        else
        {
            _dashboard=img_zoom_pixel_H(_dashboard_ini,ceil(_screen->h/2));
        }
    }
    else   //si c'est trop grand, on calcule la taille des dash en fonction de _screen->w/NbJoueurx
    {
        _dashboard=img_zoom_pixel_W(_dashboard_ini,ceil(_screen->w/nbJoueursX));
    }
    double d_h=_dashboard->h;
    _ratio=d_h/(double)d_h_ini;
}

/**
* Redimensionne les avatars pour l'ecran
**/
void InterfaceX::resize_avatars(){

    int taille_avat_W=_avatars_ini->w*_ratio_avat_ini*_ratio;
    _avatars=img_zoom_pixel_W(_avatars_ini,taille_avat_W);

}
/**
* Redimensionne les fichiers pour l'ecran
**/
bool InterfaceX::resize_files()
{

    resize_dash();
    resize_blobs();
    resize_avatars();

    return true;
}
/**
* Redimensionne le menu pour l'ecran
**/
void InterfaceX::resize_menu()
{
    double ratio_menu=(double)_menu_ini->h/(double)_menu_ini->w;
    int nb_menus = (int)(_menu_ini->w/_taille_menu_ini);
    if(_SCREEN_HEIGHT<_SCREEN_WIDTH*nb_menus*ratio_menu)
    {
        _menu=img_zoom_pixel_H(_menu_ini,_SCREEN_HEIGHT);
        _decalage_menu_x=ceil((_SCREEN_WIDTH-_menu->w/nb_menus)/2.0);
    }
    else
    {
        _menu=img_zoom_pixel_W(_menu_ini,_SCREEN_WIDTH*nb_menus);
        _decalage_menu_y=ceil((_SCREEN_HEIGHT-_menu->h)/2.0);
    }
    _ratio_menu=(double)_menu->h/(double)_menu_ini->h;

    _offset_menu.w=ceil(_menu->w/nb_menus);
    _offset_menu.h=_menu->h;

    _offset_cursor.setX(_offset_cursor.x()*_ratio_menu+_decalage_menu_x);
    _offset_cursor.setY(_offset_cursor.y()*_ratio_menu+_decalage_menu_y);
    _cursor=rotozoomSurface(_cursor_ini,0,_ratio_menu,0);
    _background=rotozoomSurfaceXY(_background_ini,0,1/((double)_background_ini->w/(double)_screen->w),1/((double)_background_ini->h/(double)_screen->h),1);
    _taille_menu=ratio_menu*_taille_menu_ini;
    _taille_text*=_ratio_menu;

}

/**
* Calcule la position des dashboards
**/
bool InterfaceX::compute_vDash()
{
    int nbJoueursX;
    _vDash.resize(_nbJoueurs);
    if(_nbJoueurs>2)
        nbJoueursX=round((_nbJoueurs+0.1)/2);
    else
        nbJoueursX=_nbJoueurs;

    Position pinit(0,0);
    for(int i=0; i<_nbJoueurs; i++)
    {
        _vDash[i].setX(pinit.x());
        _vDash[i].setY(pinit.y());
    }
    int posX=0,posY=0;
    if(_nbJoueurs>2)
        posY=_screen->h/2-_dashboard->h;
    for (int j=0; j<_nbJoueurs; j++)
    {
        _vDash.at(j).setX(posX);
        _vDash.at(j).setY(posY);
        posX+=_dashboard->w;
        if(j==nbJoueursX-1 && _nbJoueurs>2)
        {
            posX=0;
            posY+=_dashboard->h;
        }
    }
    int decalagex=ceil((_screen->w -nbJoueursX*_dashboard->w)/2);
    int decalagey=0;
    if(_nbJoueurs<=2)
        decalagey=floor((_screen->h-(ceil((double)nbJoueursX/2.0))*_dashboard->h)/2);
    for (int j=0; j<_nbJoueurs; j++)
    {
        std::cout<<" DECALAGE Y : "<<decalagey<<std::endl;
        _vDash.at(j).setX(_vDash.at(j).x()+decalagex);
        _vDash.at(j).setY(_vDash.at(j).y()+decalagey);
    }


    return true;
}
/**
* Blit le fond noir
**/
void InterfaceX::blit_fond()
{
    apply_surface(0,0,_background,_screen,NULL);
}
/**
* Effectue tous les blits
**/
void InterfaceX::blits(std::vector<DashBoard *> dashBoards)
{
    blit_fond();
    blit_blobs(dashBoards);
    blit_dash();
    blit_scores(dashBoards);
    blit_avatars();
}
/**
* Blit des dashboards
**/
void InterfaceX::blit_dash()
{
    for(size_t j=0; j<_vDash.size(); j++) //Affichage des dashboard en utilisant le vecteur de coordonnee
        apply_surface(_vDash.at(j).x(),_vDash.at(j).y(),_dashboard,_screen,NULL);
}
/**
* Animation quand un blob tombe
**/
int InterfaceX::anim_falling(){
return 17;

}
/**
* Animation quand un blob atterit
**/
int InterfaceX::anim_landing(Blobs* blob)
{
    return (blob->current()%6>=3)?16:17;
}
/**
* Animation quand un blob effectue un combo
**/
int InterfaceX::anim_comboting(Blobs* blob)
{
    if(blob->current()<=4)
        return 33;
    else if((blob->current())>= 30 )
    {
        if((blob->current())%4 >= 3)
            return -1;
        else
            return 0;
    }
    else
        return 32;

}
/**
* Appellee pour les blits de blobs
**/
void InterfaceX::blit_un_blob(Blobs* blob,int x,int y)
{
    switch(blob->state())
    {
    case NO_STATE:
        apply_surface(x,y,_blobsIMG[blob->color()][blob->link()],_screen,NULL);
        break;
    case FALLIN_ANIM :
    case FALLING:
        apply_surface(x,y,_blobsIMG[blob->color()][anim_falling()],_screen,NULL);
        break;
    case LANDING :
        apply_surface(x,y,_blobsIMG[blob->color()][anim_landing(blob)],_screen,NULL);
        break;
    case COMBOTING:
        if(anim_comboting(blob)!=-1)
            apply_surface(x,y,_blobsIMG[blob->color()][anim_comboting(blob)],_screen,NULL);
        break;
    default://ne doit pas arriver mais pour debug
        apply_surface(x,y,_blobsIMG[blob->color()][blob->link()],_screen,NULL);
        break;

    }
}
/**
* Affiche un curseur au menu
**/
void InterfaceX::blit_cursor()
{
    apply_surface(_offset_cursor.x(),_offset_cursor.y(),_cursor,_screen,NULL);
}
void InterfaceX::blit_scores(std::vector<DashBoard *> dashBoards){
    SDL_Surface *score=NULL;
    std::ostringstream sc;
    TTF_Font *font= TTF_OpenFont("ARIAL.TTF",_taille_score*_ratio);
    SDL_Color textcolor = {255,255,255,0};
    for(size_t j=0; j<dashBoards.size(); j++){
        sc.str("");
        sc<<dashBoards[j]->score();
        score=TTF_RenderText_Solid(font,(sc.str()).c_str(),textcolor);
        apply_surface(_vDash[j].x()+_offset_score.x(),_vDash[j].y()+_offset_score.y(),score,_screen,NULL);
    }
    SDL_FreeSurface(score);
    TTF_CloseFont(font);
}

/**
* Affiche le menu
=======
}
/**
* Affiche le menu
**/
void InterfaceX::blit_menu()
{
    apply_surface(0,0,_background,_screen,NULL);
    apply_surface(_decalage_menu_x,_decalage_menu_y,_menu,_screen,&_offset_menu);
}
/**
* Affiche les avatars
**/
void InterfaceX::blit_avatars()
{
    SDL_Rect offset_img;
    srand(time(NULL));
    offset_img.w=(int)(80*_ratio*_ratio_avat_ini);
    offset_img.h=(int)(56*_ratio*_ratio_avat_ini);
    int cpt=0;
    for(size_t j=0; j<_vDash.size(); j++)
    {

        offset_img.x=(rand()%5)*ceil(offset_img.w+4.0*_ratio*_ratio_avat_ini);//*_ratio*_ratio_avat_ini);
        if(cpt>12)
            cpt=0;
        offset_img.y=cpt*ceil(offset_img.h+6.0*_ratio*_ratio_avat_ini);//*_ratio*_ratio_avat_ini);
        apply_surface(_vDash.at(j).x()+_offset_avatar.x(),_vDash.at(j).y()+_offset_avatar.y(),_avatars,_screen,&offset_img);
        cpt++;
    }
}
/**
* Blit des blobs courants
**/
void InterfaceX::blit_blobs_mobiles(Position pmaster,Position pslave,Blobs* master,Blobs* slave,int n)
{
    if(!_shining)
        blit_un_blob(master,pmaster.x()+_offset_grille.x()+_vDash[n].x(),pmaster.y()+_offset_grille.y()+_vDash[n].y());
    else
        apply_surface(pmaster.x()+_offset_grille.x()+_vDash[n].x(),pmaster.y()+_offset_grille.y()+_vDash[n].y(),_blobsIMG[master->color()][18],_screen,NULL);
    blit_un_blob(slave,pslave.x()+_offset_grille.x()+_vDash[n].x(),pslave.y()+_offset_grille.y()+_vDash[n].y());
}
/**
* Blit de la grille de blob
**/
void InterfaceX::blit_blobs(std::vector<DashBoard *> dashBoards)
{

    int blobx,bloby;
    int offsetgrillex;
    int offsetgrilley;
    for(size_t j=0; j<dashBoards.size(); j++)
    {
        for(int l=0; l<18; l++)
        {
            for(int c=0; c<6; c++)
            {
                if( ((*(dashBoards.at(j)->grille()))(l,c))->color()!=BLANK)
                {
                    //On se place au debut de la grille
                    offsetgrillex=(_offset_grille).x()+_vDash.at(j).x();
                    if( ((*(dashBoards.at(j)->grille()))(l,c))->state()==FALLING ||((*(dashBoards.at(j)->grille()))(l,c))->state()==FALLIN_ANIM )
                        offsetgrilley=(_offset_grille).y()+_vDash.at(j).y()-((*(dashBoards.at(j)->grille()))(l,c))->current()+((*(dashBoards.at(j)->grille()))(l,c))->fallingDepth();
                    else
                        offsetgrilley=(_offset_grille).y()+_vDash.at(j).y();
                    //On calcule les coordonnées des blobs
                    blobx=c*_taille_blob;
                    bloby=l*_taille_blob;
                    blit_un_blob(((*(dashBoards.at(j)->grille()))(l,c)),offsetgrillex+blobx,offsetgrilley+bloby);

                }
            }
        }
    }
}
/**
* Calcule les positions des elements du dashboard
**/
bool InterfaceX::compute_offsets()
{
    _offset_grille.setX(ceil((8.0)*(_ratio)));
    _offset_grille.setY(ceil(((33-6*_taille_blob_ini)*(_ratio))));
    _offset_nextBlob.setX(ceil((128)*_ratio));
    _offset_nextBlob.setY(ceil((78)*_ratio));
    _offset_avatar.setX(ceil((105)*_ratio));
    _offset_avatar.setY(ceil((178)*_ratio));
    _offset_score.setX(ceil((114)*(_ratio)));
    _offset_score.setY(ceil((145)*(_ratio)));
    return true;
}
/**
* Charge les images
**/
bool InterfaceX::load_files()
{
#ifdef WINDOWS
    _chdir("img");
#else
    chdir("img");
#endif
    char cCurrentPath[FILENAME_MAX];

    GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));

    _background_ini = load_img("background.png");
    _dashboard_ini = load_img("dashboard.png");
    _blobs_ini = load_img( "blobs.png" );
    _avatars_ini = load_img("avatars.png");
    _menu_ini = load_img("menu.png");
    _cursor_ini = load_img("cursor.png");
    if ( _blobs_ini == NULL || _background_ini==NULL || _avatars_ini==NULL || _cursor_ini ==NULL||_menu_ini==NULL)
    {
        return false;
    }
    return true;
}
/**
* On liberer toute la memoire
**/
void InterfaceX::clean_up()
{
    SDL_FreeSurface(_background_ini);
    SDL_FreeSurface(_background);
    SDL_FreeSurface(_avatars_ini);
    SDL_FreeSurface(_avatars);
    SDL_FreeSurface(_menu);
    SDL_FreeSurface(_menu_ini);
    SDL_FreeSurface(_cursor);
    SDL_FreeSurface(_cursor_ini);
    SDL_FreeSurface(_dashboard_ini);
    SDL_FreeSurface(_dashboard);
    SDL_FreeSurface(_screen);
    SDL_FreeSurface(_blobs_ini);
    TTF_Quit();
    SDL_Quit();
}
/**
* Redimensionne une surface en W
**/
SDL_Surface* InterfaceX::img_zoom_pixel_W(SDL_Surface *surface_a_resize,int taille_desiree_W)
{
    double td_W=taille_desiree_W;
    double sar_W=surface_a_resize->w;
    double zoom=(double)td_W/(double)sar_W;
    SDL_Surface *surface_resized=rotozoomSurfaceXY(surface_a_resize,0,zoom,zoom,0);
    // SDL_FreeSurface(surface_a_resize);
    return surface_resized;
}
/**
* Redimensionne une surface en H
**/
SDL_Surface* InterfaceX::img_zoom_pixel_H(SDL_Surface *surface_a_resize,int taille_desiree_H)
{
    double td_H=taille_desiree_H;
    double sar_H=surface_a_resize->h;
    double zoom=(double)td_H/(double)sar_H;
    SDL_Surface *surface_resized=rotozoomSurfaceXY(surface_a_resize,0,zoom,zoom,0);
    // SDL_FreeSurface(surface_a_resize);
    return surface_resized;
}
/**
* Redimensionne le vector des images de blobs
**/
void InterfaceX::resize_vect()
{
    _blobsIMG_ini.resize(SIZE_COLOR,std::vector<SDL_Surface*> (_nb_blobs));
    _blobsIMG.resize(SIZE_COLOR,std::vector<SDL_Surface*> (_nb_blobs));
    for (int i = 0 ; i < SIZE_COLOR ; ++i)
    {
        for (int j = 0 ; j < _nb_blobs ; ++j)
        {
            _blobsIMG[i][j] = NULL;
            _blobsIMG_ini[i][j] = NULL;
        }
    }

}
/**
* Cree le vector des images de blobs
**/
void InterfaceX::resize_blobsIMG()
{
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
//D'abord on alloue la surface necessaire
    for(int i=0; i<SIZE_COLOR-1; i++)
    {
        for(int j=0; j<_nb_blobs; j++)
        {
            _blobsIMG[i][j]=SDL_CreateRGBSurface (SDL_HWSURFACE |SDL_SRCALPHA, _taille_blob, _taille_blob, 32, rmask, gmask, bmask, amask );
        }
    }
    for(int i=0; i<SIZE_COLOR-1; i++) //0 à 5
        for(int j=0; j<_nb_blobs; j++) //0 à 40
            _blobsIMG[i][j]=img_zoom_pixel_H(_blobsIMG_ini[i][j],_taille_blob);


}
/**
* Decoupe l'image de blobs
**/
void InterfaceX::decouper_sprite()
{
    if(SDL_MUSTLOCK(_blobs_ini))
        SDL_LockSurface(_blobs_ini);
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    for(int i=0; i<SIZE_COLOR-1; i++)
        for(int j=0; j<_nb_blobs; j++)
            _blobsIMG_ini[i][j]=SDL_CreateRGBSurface (SDL_HWSURFACE |SDL_SRCALPHA, _taille_blob_ini, _taille_blob_ini,_blobs_ini->format->BitsPerPixel, rmask, gmask, bmask, amask);
//Puis on lit dans l'image pixel[x+y*pitch]
    int cptx=0,cpty=0;
    Uint32 pixel;
    Uint8 r,g,b,a;
    for(int i=0; i<SIZE_COLOR-1; i++) //0 à 5
    {
        for(int j=0; j<_nb_blobs; j++) //0 à 40
        {
            for(int x=0; x<_taille_blob_ini; ++x)
            {
                for(int y=0; y<_taille_blob_ini; ++y)
                {
                    pixel=getpixel(_blobs_ini,cptx+x,cpty+y);
                    SDL_GetRGBA(pixel, _blobs_ini->format, &r, &g, &b, &a);
                    pixel=SDL_MapRGBA(_blobsIMG_ini[i][j]->format, r, g, b, a);
                    putpixel(_blobsIMG_ini[i][j],x,y,pixel);
                }
            }
            cptx+=_taille_blob_ini;
            if(j==_nb_blobs/2-1)
            {
                cptx=0;
                cpty+=_taille_blob_ini;
            }

        }
        cptx=0;
        cpty+=_taille_blob_ini;
    }

    if(SDL_MUSTLOCK(_blobs_ini))
        SDL_UnlockSurface(_blobs_ini);

}
/**
* Recuperer un pixel d'une surface
**/
Uint32 InterfaceX::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        _screen = SDL_SetVideoMode( _SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, SDL_HWSURFACE |SDL_DOUBLEBUF );

        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       //shouldn't happen, but avoids warnings
    }
}
/**
* Met un pixel dans une surface
**/
void InterfaceX::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
/**
* On met a jour toutes les animations
**/
void InterfaceX::maj_anims(DashBoard& dash)
{
    bool retour =false;
    if(dash.grille()->checkLoose())
    {
        dash.masterBlob()->setColor(BLANK);
        dash.slaveBlob()->setColor(BLANK);
    }
    if(dash.moteurPhy()->falling()==0 && dash.moteurPhy()->comboting() ==0 && dash.grille()->checkLanding()==0)
        retour = true;
    maj_shining();
    dash.moteurPhy()->fall();
    dash.grille()->check();
    dash.grille()->checkCombo();
    if(dash.masterBlob()->state()==LANDING)
    {
        dash.masterBlob()->setLanding(dash.masterBlob()->current()-1);
        dash.slaveBlob()->setLanding(dash.slaveBlob()->current()-1);
        if(dash.masterBlob()->current()==0)
        {
            dash.masterBlob()->setState(NO_STATE);
            dash.slaveBlob()->setState(NO_STATE);

        }
    }
    if((dash.moteurPhy()->falling()!=0 || dash.moteurPhy()->comboting() !=0 || dash.grille()->checkLanding()!=0) && retour )
        return ;
    dash.moteurPhy()->setFalling(dash.grille()->checkFalling());
    if(dash.moteurPhy()->falling()==0)
        dash.moteurPhy()->majCombo();
    if(dash.moteurPhy()->fixed())
    {
        dash.grille()->check();
        dash.grille()->checkCombo();
        dash.masterBlob()->setColor(BLANK);
        dash.slaveBlob()->setColor(BLANK);
    }
    if(dash.moteurPhy()->falling()!=0)
    {
        dash.moteurPhy()->setFalling(dash.moteurPhy()->falling()-1);
    }
    dash.moteurPhy()->setComboting(dash.grille()->checkMaxCombo());
//     std::cerr << "combo : "<< dash.moteurPhy()->comboting() << "\n";
    if(dash.moteurPhy()->comboting()==1||dash.moteurPhy()->comboting()==2)
    {
        if(dash.combo()==0)
            dash.setCombo(dash.moteurPhy()->combo()-3);
        else
            dash.setCombo(6*(dash.moteurPhy()->combo()%4) +(dash.moteurPhy()->combo()%4) );
    }
     //    std::cerr << "combo value : "<< dash.moteurPhy()->combo() << "\n";

    if(dash.moteurPhy()->turningDirect()!=0||dash.moteurPhy()->turningHoraire()!=0)
    {
        int sens = 0;
        int angle = dash.moteurPhy()->turningDirect()+dash.moteurPhy()->turningHoraire();
        if(dash.moteurPhy()->turningDirect()!=0)
        {
            sens = 1;
            dash.moteurPhy()->setTurningDirect(dash.moteurPhy()->turningDirect()-1);
        }
        else
        {
            dash.moteurPhy()->setTurningHoraire(dash.moteurPhy()->turningHoraire()-1);
            sens = -1;
            //return;
        }
        tourne_un_blob(dash.masterPos(),dash.slavePos(),sens,angle,dash.moteurPhy()->orientation());

    }



}
/**
* On fait clignoter le blob pivot
**/
void InterfaceX::maj_shining()
{
    if(_cpt>=15)
    {
        _shining = (_shining==0)?1:0;
        _cpt=0;
    }
    else
        _cpt++;
}
void  InterfaceX::tourne_un_blob(Position* pivot,Position* slave,int sens, int angle,int target)
{
    double x0 = pivot->x();
    double y0 = pivot->y();
    double angle0 = 0;
    switch(target)
    {
    case BAS:
        angle0 = 1.5707;
        break;
    case HAUT :
        angle0 = -1.5707;
        break;
    case GAUCHE :
        angle0 = 3.1415;
        break;
    case DROITE :
        angle0 = 0;
        break;
    }
    double angle_diff = sens * angle * 1.5707 / TURNING_ANIM_TIME;
    slave->setX(x0 + _taille_blob*std::cos(angle0+angle_diff));
    slave->setY(y0 + _taille_blob*std::sin(angle0+angle_diff));
}
/**
* Initialise les parametres du jeu
*
**/
void InterfaceX::initialisation_debut_jeu()
{
    _offset_menu.x=0;
    _offset_menu.y=0;
    _offset_cursor.setX(80*_ratio_menu+_decalage_menu_x);
    _offset_cursor.setY(87*_ratio_menu+_decalage_menu_y);
    _nbJoueurs=1;
    _nbAI=0;
    load_files();
    resize_vect();
    decouper_sprite();
    controls_by_default();
}
