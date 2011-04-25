<<<<<<< HEAD
#include "../include/InterfaceX.h"
#ifdef WIN32
#define WINDOWS
#endif
#ifdef X64
#define WINDOWS
#endif
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include "../include/Color.h"
#include "../include/Link.h"
#include "../include/State.h"
#include "../include/Blobs.h"
#include "../include/Position.h"
#include <time.h>
#include <sstream>
SDL_Surface* InterfaceX::load_img( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if ( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
        if ( optimizedImage != NULL )
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255, 255, 0 ) );
    }
    else
    {
        std::cout<<"Erreur Chargement image"<<std::endl;
    }
    return optimizedImage;
}
void InterfaceX::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
bool InterfaceX::init_SDL()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
    _screen = SDL_SetVideoMode( _SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, SDL_SWSURFACE |SDL_DOUBLEBUF );
    if ( _screen == NULL )
        return false;
    SDL_WM_SetCaption( "Dr.Robotnik Mean Bean Machine - Zamunerstein Hoarau ROB4 2011", NULL );
    return true;
}
void InterfaceX::blit_nextBlob(Blobs* master,Blobs* slave,int n)
{

    blit_un_blob(slave,_offset_nextBlob.x()+_vDash[n].x(),_offset_nextBlob.y()+_vDash[n].y()-2*_taille_blob);
    blit_un_blob(master,_offset_nextBlob.x()+_vDash[n].x(),_offset_nextBlob.y()+_vDash[n].y()-_taille_blob);

}
int InterfaceX::play_anim_menu(int init,int fin)
{
    int continuer=1;
    clock_t tinit,tfinal;
    double t;
    SDL_Event event;
    _offset_menu.x=init;
    int offsetmenux=_offset_menu.x;
    tinit=clock();
    std::cout<<" init : "<<init<<" fin : "<<fin<<std::endl;
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        tfinal=clock();
        Uint8 *keystates = SDL_GetKeyState( NULL );
        blit_menu();
        SDL_PollEvent(&event);
        t=(double)(tfinal-tinit)/CLOCKS_PER_SEC;
        //std::cout<<"T : "<<t<<std::endl;
        if(keystates[SDLK_BACKSPACE] && fin>=init)//On retourne au debut
        {
            tinit=tfinal=clock();

            while(continuer)
            {
                blit_menu();
                tfinal=clock();
                t=(double)(tfinal-tinit)/CLOCKS_PER_SEC;
                if(t>0.001)
                {
                    tinit=clock();
                        offsetmenux-=3;
                        if(offsetmenux<=init)
                        {
                            _offset_menu.x=init;
                            return 0;
                        }
                }
                    _offset_menu.x=offsetmenux;
                    std::cout<<"recule position x : "<<_offset_menu.x<<std::endl;
                    SDL_Flip(_screen);
                }
        }

    if(t>0.001)
    {
        if(fin-init>=0)
            offsetmenux+=3;
        else
            offsetmenux-=3;
        tinit=clock();
    }
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
    std::cout<<"position x : "<<_offset_menu.x<<std::endl;
    SDL_Flip(_screen);
}
return 1;

}
int InterfaceX::select_nbJoueurs()
{
    int continuer=1;
    SDL_Event event;
    clock_t tinit,tfinal;
    std::cout<<"Curseur = "<<_cursor->w<<"x"<<_cursor->h<<" Position x = "<<_offset_cursor.x()<<" y = "<<_offset_cursor.y()<<std::endl;
    float t;
    tinit=clock();
    _offset_menu.x=2*_offset_menu.w;
    int curseur=1;
    int NplayerMAX=4;
    int saut=22*_ratio_menu;
    SDL_EnableKeyRepeat(100,50);
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        blit_menu();
        blit_cursor();
        tfinal=clock();
        while(SDL_PollEvent(&event)) /* On attend un évènement qu'on récupère dans event */
        {
            if (event.type==SDL_QUIT)  /* Si c'est un évènement QUITTER */
            {
                continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
            }
            Uint8 *keystates = SDL_GetKeyState( NULL );

            if (keystates[SDLK_ESCAPE]) /* Appui sur la touche Echap, on arrête le programme */
                continuer = 0;
            if(keystates[SDLK_UP])
            {
                if(curseur==1)
                {
                    _offset_cursor.setY(_offset_cursor.y()+(NplayerMAX-1)*saut);
                    curseur=NplayerMAX;
                }
                else
                {
                    _offset_cursor.setY(_offset_cursor.y()-saut);
                    curseur--;
                }
            }
            if(keystates[SDLK_DOWN])
            {
                if(curseur==NplayerMAX)
                {
                    _offset_cursor.setY(_offset_cursor.y()-(NplayerMAX-1)*saut);
                    curseur=1;
                }
                else
                {
                    _offset_cursor.setY(_offset_cursor.y()+saut);
                    curseur++;
                }

            }
            if(keystates[SDLK_RETURN])
            {
                continuer=0;
            }

        }

        t=(tfinal-tinit);
        if(t>15)
        {
        }
        SDL_Flip(_screen);
    }

    return curseur;
}
void InterfaceX::menu()
{
    #ifdef WINDOWS
    if (_chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#else
    if (chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#endif
    char cCurrentPath[FILENAME_MAX];

    GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));


    std::cout<< cCurrentPath<<std::endl;
    resize_menu();
    TTF_Init();
    int continuer=1;
    SDL_Event event;
    SDL_Surface *text;
    TTF_Font *font= TTF_OpenFont("ARIAL.TTF",30);
    clock_t tinit,tfinal;
    float t;
    SDL_Color textcolor = {255,200,255};
    int nbjoueurs=1;
    tinit=clock();
    int position_menu=1;
    std::ostringstream oss;
    std::string njoueurs;
    SDL_EnableKeyRepeat(100,50);
    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        tfinal=clock();
        oss.str("");
        oss<<nbjoueurs;
        text=TTF_RenderText_Solid(font,(oss.str()).c_str(),textcolor);
       // text=TTF_RenderText_Solid(font,"TEST",textcolor);

        while(SDL_PollEvent(&event)) /* On attend un évènement qu'on récupère dans event */
        {
            if (event.type==SDL_QUIT)  /* Si c'est un évènement QUITTER */
            {
                continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
            }
            Uint8 *keystates = SDL_GetKeyState( NULL );

            if (keystates[SDLK_ESCAPE]) /* Appui sur la touche Echap, on arrête le programme */
                continuer = 0;
            if(keystates[SDLK_RETURN])
            {
                if(_offset_menu.x<2*_offset_menu.w){
                    play_anim_menu(_offset_menu.w,2*_offset_menu.w);
                    position_menu++;
                }
                //continuer=0;
                std::cout<<"AVANCE"<<std::endl;
            }
            if(keystates[SDLK_DOWN]){
                nbjoueurs++;
            }
            if(keystates[SDLK_UP]){
                if(nbjoueurs>1)
                nbjoueurs--;
            }
            if(keystates[SDLK_BACKSPACE])
            {
                if(_offset_menu.x>=2*_offset_menu.w)
                {
                    play_anim_menu(_offset_menu.x,_offset_menu.x-_offset_menu.w);
                    position_menu--;
                    std::cout<<"RECULE"<<std::endl;
                }
            }
        }
        blit_menu();
        t=(tfinal-tinit);
        if(t>150 && _offset_menu.x<2*_offset_menu.w)
        {
            if(_offset_menu.x==0)
                _offset_menu.x+=_offset_menu.w;
            else
                _offset_menu.x-=_offset_menu.w;
            tinit=clock();

        }
        apply_surface(0,0,text,_screen,NULL);

        SDL_Flip(_screen);
    }

}
void InterfaceX::compute_game()
{
    //On fait tous les resize en fonction du nombre de joueurs
    std::cout<<"Resize des Fichiers...";
    resize_files();
    std::cout<<"OK"<<std::endl;
    compute_vDash();
    compute_offsets();
}
bool InterfaceX::resize_files()
{
    std::cout<<" NBJOUEURS :"<<_nbJoueurs<<std::endl;
    int nbJoueursX=_nbJoueurs;
    if(_nbJoueurs>2)
        nbJoueursX=round(((double)_nbJoueurs+0.1)/2.0);
    int d_h_ini=_dashboard_ini->h;
    int resizedDashW ;
    if(_nbJoueurs>2)
        resizedDashW = (double)((_screen->h/2)*(_dashboard_ini->w)/(_dashboard_ini->h));
    else
        resizedDashW = (double)((_screen->h)*(_dashboard_ini->w)/(_dashboard_ini->h));

    std::cout<<"Taille dash W resized : "<<resizedDashW<<std::endl;
    if(nbJoueursX*resizedDashW<=_screen->w) //On verifie que les dash rentrent bien dans l'ecran <---->
    {
        std::cout<<"Assez de place en W"<<std::endl;
        if (_nbJoueurs<=2)
        {
            std::cout<<"resize h"<<std::endl;
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h);
            std::cout<<"resize h terminé"<<std::endl;
        }
        else
        {
            _dashboard=img_zoom_pixel_H(_dashboard_ini,_screen->h/2);
        }
    }
    else   //si c'est trop grand, on calcule la taille des dash en fonction de _screen->w/NbJoueurx
    {
        std::cout<<"PAS Assez de place en W--> resize en H"<<std::endl;
        _dashboard=img_zoom_pixel_W(_dashboard_ini,_screen->w/nbJoueursX);
    }
    double d_h=_dashboard->h;
    _ratio=d_h/(double)d_h_ini;


    std::cout<<"Resize des blobs"<<std::endl;
    int nb_blobs_par_h=12;
    int nb_blobs_par_w=20;
    double taille_blob_H =(double)_blobs_ini->h*_ratio;
    double taille_blob_W =(double)_blobs_ini->w*_ratio;
    std::cout<<"taille_blobs_h : "<<taille_blob_H<<" Ratio : "<<_ratio<<std::endl;
    std::cout<<"taille_blobs_w : "<<taille_blob_W<<" Ratio : "<<_ratio<<std::endl;
    // _blobs=img_zoom_pixel_W(_blobs_ini,taille_blob_W);
    int dw;
    int dh;
    double zoom=taille_blob_H/(double)_blobs_ini->h;
    double zoom_optimal=zoom;
    rotozoomSurfaceSize(_blobs_ini->w,_blobs_ini->h,0,zoom,&dw,&dh);
    std::cout<<"dw(double) : "<<(dw/20.0)<<" dh(int) :"<<(int)(dw/20.0)<<std::endl;
    std::cout<<"zoom initial : "<<zoom<<std::endl;
    while(dw/20.0!=(int)(dw/20.0))
    {
        zoom_optimal+=0.001;
        rotozoomSurfaceSize(_blobs_ini->w,_blobs_ini->h,0,zoom_optimal,&dw,&dh);
        std::cout<<"dw(double) : "<<(dw/20.0)<<" dh(int) :"<<(int)(dw/20.0)<<std::endl;
        std::cout<<"dw : "<<(dw)<<" dh :"<<(dh)<<std::endl;

    }
    std::cout<<"dw optimal : "<<(dw)<<" dh optimal :"<<(dh)<<std::endl;
    std::cout<<"zoom optimal : "<<zoom_optimal<<std::endl;
    _blobs=img_zoom_pixel_W(_blobs_ini,dw);
    //_blobs=rotozoomSurface(_blobs_ini,0,zoom_optimal,0);
    std::cout<<"dw obtenu : "<<_blobs->w<<" dh obtenu :"<<_blobs->h<<std::endl;

    _taille_blob=(double)_blobs->w/20.0;
    std::cout<<"1.Un blob mesure(double) : "<<_taille_blob<<" px de coté"<<std::endl;
    _taille_blob=(int)(_blobs->h/12.0);
    std::cout<<"2.Un blob mesure(int) : "<<_taille_blob<<" px de coté"<<std::endl;
    _grille_W=12*_taille_blob;
    _grille_H=6*_taille_blob;


    std::cout<<"avatar iniw : "<<_avatars_ini->w<<" ratio ini avat : "<<_ratio_avat_ini<<" ratio : "<<_ratio<<std::endl;

    int taille_avat_W=_avatars_ini->w*_ratio_avat_ini*_ratio;
    std::cout<<"Taille avatar w : "<<taille_avat_W<<std::endl;
    _avatars=img_zoom_pixel_W(_avatars_ini,taille_avat_W);
    std::cout<<"TAILLE BLOB ini : "<<_taille_blob_ini<<std::endl;
    std::cout<<"TAILLE BLOB /20 : "<<_blobs->w/20<<std::endl;
    std::cout<<"TAILLE BLOB final : "<<_taille_blob<<std::endl;


    return true;
}
void InterfaceX::resize_menu()
{
    std::cout<<"Le menu = "<<_menu_ini->w<<"x"<<_menu_ini->h<<std::endl;
    double ratio_menu=(double)_menu_ini->h/(double)_menu_ini->w;

    if(_SCREEN_HEIGHT<_SCREEN_WIDTH*3*ratio_menu)
    {
        _menu=img_zoom_pixel_H(_menu_ini,_SCREEN_HEIGHT);
        _decalage_menu_x=ceil((_SCREEN_WIDTH-_menu->w/3)/2.0);
    }
    else
    {
        _menu=img_zoom_pixel_W(_menu_ini,_SCREEN_WIDTH*3);
        _decalage_menu_y=ceil((_SCREEN_HEIGHT-_menu->h)/2.0);
    }
    _ratio_menu=(double)_menu->h/(double)_menu_ini->h;

    _offset_menu.w=ceil(_menu->w/3);
    _offset_menu.h=_menu->h;

    std::cout<<"Le menu final = "<<_menu->w<<"x"<<_menu->h<<std::endl;
    _offset_cursor.setX(_offset_cursor.x()*_ratio_menu+_decalage_menu_x);
    _offset_cursor.setY(_offset_cursor.y()*_ratio_menu+_decalage_menu_y);
    _cursor=rotozoomSurface(_cursor_ini,0,_ratio_menu,0);
    _background=rotozoomSurfaceXY(_background_ini,0,1/((double)_background_ini->w/(double)_screen->w),1/((double)_background_ini->h/(double)_screen->h),1);

}
/** @brief Calcule les positions des differents dashboard
*
*
*/
bool InterfaceX::compute_vDash()
{
    int nbJoueursX;
    if(_nbJoueurs>2)
        nbJoueursX=round((_nbJoueurs+0.1)/2);
    else
        nbJoueursX=_nbJoueurs;

    std::cout<<"NB joueurs en X :  "<<nbJoueursX<<std::endl;
    Position pinit(0,0);
    for(int i=0; i<_nbJoueurs; i++)
    {
        _vDash.push_back(pinit);
        std::cout<<" VDASH["<<i<<"] = "<<_vDash[i].x()<<"x"<<_vDash[i].y()<<std::endl;
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
    int decalagex=(_screen->w -nbJoueursX*_dashboard->w)/2;
    int decalagey=0;
    if(_nbJoueurs<=2)
        decalagey=(_screen->h-(ceil((double)nbJoueursX/2.0))*_dashboard->h)/2;
    for (int j=0; j<_nbJoueurs; j++)
    {
        _vDash.at(j).setX(_vDash.at(j).x()+decalagex);
        _vDash.at(j).setY(_vDash.at(j).y()+decalagey);
    }
    for (size_t j=0; j<_vDash.size(); j++)
    {
        std::cout<<"_vDash["<<j<<"] : "<<_vDash[j].x()<<"x"<<_vDash[j].y()<<std::endl;
    }

    return true;
}

void InterfaceX::blit_fond()
{
    apply_surface(0,0,_background,_screen,NULL);
}
void InterfaceX::blits(std::vector<DashBoard> dashBoards)
{
    blit_fond();
    blit_dash();
    blit_blobs(dashBoards);
    blit_avatars();
}
void InterfaceX::blit_dash()
{
    for(size_t j=0; j<_vDash.size(); j++) //Affichage des dashboard en utilisant le vecteur de coordonnee
        apply_surface(_vDash.at(j).x(),_vDash.at(j).y(),_dashboard,_screen,NULL);
}

void InterfaceX::blit_un_blob(Blobs* blob,int x,int y)
{
    SDL_Rect offset=offset_sprite(blob->color(),blob->link(),blob->state());
    apply_surface(x,y,_blobs,_screen,&offset);


}
void InterfaceX::blit_cursor()
{
    apply_surface(_offset_cursor.x(),_offset_cursor.y(),_cursor,_screen,NULL);

}
void InterfaceX::blit_menu()
{
    apply_surface(0,0,_background,_screen,NULL);
    apply_surface(_decalage_menu_x,_decalage_menu_y,_menu,_screen,&_offset_menu);
}
void InterfaceX::blit_avatars()
{
    SDL_Rect offset_img;
    srand(time(NULL));
    offset_img.w=(int)(80*_ratio*_ratio_avat_ini);
    offset_img.h=(int)(56*_ratio*_ratio_avat_ini);
    int cpt=0;
    for(size_t j=0; j<_vDash.size(); j++)
    {

        offset_img.x=(rand()%6)*ceil(offset_img.w+4.0*_ratio*_ratio_avat_ini);//*_ratio*_ratio_avat_ini);
        if(cpt>12)
            cpt=0;
        offset_img.y=cpt*ceil(offset_img.h+6.0*_ratio*_ratio_avat_ini);//*_ratio*_ratio_avat_ini);
        std::cout<<"w : "<<offset_img.w<<" h : "<<offset_img.h<<" x : "<<offset_img.x<<" y : "<<offset_img.y<<std::endl;
        apply_surface(_vDash.at(j).x()+_offset_avatar.x(),_vDash.at(j).y()+_offset_avatar.y(),_avatars,_screen,&offset_img);
        cpt++;
    }
}
void InterfaceX::blit_blobs_mobiles(Position pmaster,Position pslave,Blobs* master,Blobs* slave,int n)
{
    blit_un_blob(master,pmaster.x()+_offset_grille.x()+_vDash[n].x(),pmaster.y()+_offset_grille.y()+_vDash[n].y());
    blit_un_blob(slave,pslave.x()+_offset_grille.x()+_vDash[n].x(),pslave.y()+_offset_grille.y()+_vDash[n].y());
}
void InterfaceX::blit_blobs(std::vector<DashBoard> dashBoards)
{

    int blobx,bloby;
    int offsetgrillex;
    int offsetgrilley;
    for(size_t j=0; j<dashBoards.size(); j++)
    {
        for(int l=0; l<13; l++)
        {
            for(int c=0; c<6; c++)
            {
                if( ((*(dashBoards.at(j).grille()))(l,c))->color()!=BLANK)
                {
                    //On se place au debut de la grille
                    offsetgrillex=(_offset_grille).x()+_vDash.at(j).x();
                    if( ((*(dashBoards.at(j).grille()))(l,c))->state()==FALLING)
                        offsetgrilley=(_offset_grille).y()+_vDash.at(j).y()-((*(dashBoards.at(j).grille()))(l,c))->current()+((*(dashBoards.at(j).grille()))(l,c))->fallingDepth();
                    else
                        offsetgrilley=(_offset_grille).y()+_vDash.at(j).y();
                    //On calcule les coordonnées des blobs
                    blobx=c*_taille_blob;
                    bloby=l*_taille_blob;

                    blit_un_blob(((*(dashBoards.at(j).grille()))(l,c)),offsetgrillex+blobx,offsetgrilley+bloby);
                }
            }
        }
    }
}
SDL_Rect InterfaceX::offset_sprite(int color,int link,int etat)
{
    SDL_Rect r;
    int tb=_taille_blob;
    std::cout<<"Taille blob : "<<tb<<std::endl;
    r.h=tb;
    r.w=tb;
    r.x=link*tb;
    r.y=2*color*tb;
    std::cout<<"Sprite x : "<<r.x<<" y : "<<r.y<<std::endl;
    return r;
}
bool InterfaceX::compute_offsets()
{
    _offset_grille.setX(ceil((8.0)*(_ratio)));
    _offset_grille.setY(ceil((31.0-_taille_blob_ini)*(_ratio)));
    _offset_nextBlob.setX(ceil((128)*_ratio));
    _offset_nextBlob.setY(ceil((78)*_ratio));
    _offset_avatar.setX(ceil((105)*_ratio));
    _offset_avatar.setY(ceil((178)*_ratio));

    return true;
}

bool InterfaceX::load_files()
{
#ifdef WINDOWS
    if (_chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#else
    if (chdir("img")==-1)
        std::cout<<"Erreur dossier"<<std::endl;
#endif
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return errno;
    }

    std::cout<< cCurrentPath<<std::endl;
    _background_ini = load_img("background.png");
    _dashboard_ini = load_img("dashboard.png");
    _blobs_ini = load_img( "blobs.png" );
    _avatars_ini = load_img("avatars.png");
    _menu_ini = load_img("menu.png");
    _cursor_ini = load_img("cursor.png");
    if ( _blobs_ini == NULL || _background_ini==NULL || _blobs_ini==NULL)
    {
        std::cout<<"Erreur chargement"<<std::endl;
        return false;
    }
    return true;
}
void InterfaceX::clean_up()
{
    SDL_FreeSurface( _blobs );
    SDL_FreeSurface( _background);
    SDL_FreeSurface(_background);
    SDL_FreeSurface(_avatars);
    SDL_FreeSurface(_menu);
    SDL_FreeSurface(_cursor);
    SDL_Quit();
}

SDL_Surface* InterfaceX::img_zoom_pixel_W(SDL_Surface *surface_a_resize,int taille_desiree_W)
{
    double td_W=taille_desiree_W;
    double sar_W=surface_a_resize->w;
    double zoom=(double)td_W/(double)sar_W;
    SDL_Surface *surface_resized=rotozoomSurfaceXY(surface_a_resize,0,zoom,zoom,0);
    SDL_FreeSurface(surface_a_resize);
    return surface_resized;
}
SDL_Surface* InterfaceX::img_zoom_pixel_H(SDL_Surface *surface_a_resize,int taille_desiree_H)
{
    double td_H=taille_desiree_H;
    double sar_H=surface_a_resize->h;
    double zoom=(double)td_H/(double)sar_H;
    SDL_Surface *surface_resized=rotozoomSurfaceXY(surface_a_resize,0,zoom,zoom,0);
    SDL_FreeSurface(surface_a_resize);
    return surface_resized;
}
void InterfaceX::decouper_sprite(){
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
    for(int i=0;i<SIZE_COLOR-1;i++){
        for(int j=0;j<40;j++){
            _blobsIMG_ini[i][j]=SDL_CreateRGBSurface (SDL_HWSURFACE |SDL_SRCALPHA, _taille_blob_ini, _taille_blob_ini, 32, rmask, gmask, bmask, amask );

        }
    }
    if(SDL_MUSTLOCK(_blobs_ini))
    SDL_UnlockSurface(_blobs_ini);

}

