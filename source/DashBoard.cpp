#include "../include/DashBoard.h"

/** @brief main loop for each DashBoard
  *
  * (documentation goes here)
  */
void DashBoard::go()
{
    if(_looser)
        return;
    _moteurPhy->majCombo();
    _moteurPhy->fall();
    _grille->check();
    _looser = _grille->checkLoose();
    std::cout<<"\n\nmoteur phy : \nfalling : "<<_moteurPhy->falling()<<"\ncomboting : "<<_moteurPhy->comboting()<<"\n\n\n";
    if(_moteurPhy->fixed())
    {
        _masterBlob.setColor(BLANK);
        _slaveBlob.setColor(BLANK);
    }
    if(_go && _moteurPhy->falling()==0 && _moteurPhy->comboting()==0)
    {
        if(_moteurPhy->fixed()&& _nextDarkBlobs==0)
        {
            std::cout<<"blob suivant\n";
            std::cout<<"MASTER COLOR ::::::"<<_nextMaster.color()<<std::endl;
            _masterBlob.setBlob(_nextMaster);
            _slaveBlob.setBlob(_nextSlave);
            _moteurPhy->setFixed(false);

            ++_it;
            if(_it==_nextBlobs->end())
                ++_it;
            _nextMaster.setBlob(*_it);
            ++_it;
            if(_it==_nextBlobs->end())
                ++_it;
            _nextSlave.setBlob(*_it);
            _moteurPhy->nextBlobs(_masterBlob,_slaveBlob);
        }

        if(_moteurPhy->falling()==0 && _moteurPhy->comboting()==0)
            _moteurPhy->moove(&_master,&_slave);
    }

    if(_nextDarkBlobs!=0 && _moteurPhy->fixed())
        _nextDarkBlobs-=_grille->checkDark(_nextDarkBlobs);

    if(_moteurPhy->comboting()!=0 && _moteurPhy->falling()==0 )
    {
        //TO DO : animation comboting
        _go = false;
        _moteurPhy->setComboting(_moteurPhy->comboting()-1);
        std::cout<<"---------------->>>>>>>>>>>>>>>>"<<_moteurPhy->comboting()<<"\n";
        if(_moteurPhy->comboting()==0)
        {

     _combo =(_combo==0)?_moteurPhy->combo():(_combo!=0&&_combo<6)?_combo+2*_moteurPhy->combo():(_combo>6&&_combo<12)?_combo+4*_moteurPhy->combo():_combo+6*_moteurPhy->combo();
        }
    }
    if(_moteurPhy->turningDirect()!=0)
    {
        int taille = _moteurPhy->taille()*0.5;
        switch(_moteurPhy->orientation())
        {
        case HAUT :
            _slave.setX(_slave.x()+taille);
            _slave.setY(_slave.y()+taille);
            break;
        case BAS :
            _slave.setX(_slave.x()-taille);
            _slave.setY(_slave.y()-taille);
            break;
        case GAUCHE :
            _slave.setX(_slave.x()+taille);
            _slave.setY(_slave.y()-taille);
            break;
        case DROITE :
            _slave.setX(_slave.x()-taille);
            _slave.setY(_slave.y()+taille);
            break;
        }
        _moteurPhy->setTurningDirect(_moteurPhy->turningDirect()-1);
    }
    if(_moteurPhy->turningHoraire()!=0)
    {
        int taille = _moteurPhy->taille()*0.8;
        switch(_moteurPhy->orientation())
        {
        case HAUT :
            _slave.setX(_slave.x()-taille);
            _slave.setY(_slave.y()+taille);
            break;
        case BAS :
            _slave.setX(_slave.x()+taille);
            _slave.setY(_slave.y()-taille);
            break;
        case GAUCHE :
            _slave.setX(_slave.x()+taille);
            _slave.setY(_slave.y()+taille);
            break;
        case DROITE :
            _slave.setX(_slave.x()-taille);
            _slave.setY(_slave.y()-taille);
            break;
        }
        _moteurPhy->setTurningHoraire(_moteurPhy->turningHoraire()-1);
    }
    if(_moteurPhy->falling()!=0)
    {
        _go = false;
        _moteurPhy->setFalling(_moteurPhy->falling()-1);

    }
    if(_moteurPhy->comboting()==0 && _moteurPhy->falling()==0)
        _go = true;


    if(_combo!=0 && _moteurPhy->comboting()==0 && _moteurPhy->falling()==0 )
    {
        if(--_delay==0){
        _launchCombo=true;
        _delay = 100;
        }
        std::cout<<"COMBO ->>>>>>> "<<_combo<<"\n";
    }
}

void DashBoard::resetCombo()
{
    _launchCombo = false;
    _combo =0;
    _moteurPhy->setCombo(0);
}
void DashBoard::addDarkBlob()
{
    _nextDarkBlobs++;
}


