#include "../include/DashBoard.h"

/** @brief main loop for each DashBoard
  *
  * (documentation goes here)
  */
void DashBoard::go()
{

    if(!_looser&&_grille->checkLoose())
    {
        _grille->animFallin(_moteurPhy->taille());
        _masterBlob.setColor(BLANK);
        _slaveBlob.setColor(BLANK);
        _looser = _grille->checkLoose();
        return;
    }
    if(_looser)
    {
        return;
    }

    if(_moteurPhy->fixed())
    {
        _masterBlob.setColor(BLANK);
        _slaveBlob.setColor(BLANK);
    }


    std::cout<<"\n\nmoteur phy : \nfalling : "<<_moteurPhy->falling()<<"\ncomboting : "<<_moteurPhy->comboting()<<"\n\n\n";
    if(_nextDarkBlobs!=0 && _moteurPhy->fixed())
    {
        _nextDarkBlobs-=_grille->checkDark(_nextDarkBlobs);
        //return;
    }
    if(_moteurPhy->comboting()==0 && _moteurPhy->falling()==0 && _grille->checkLanding()==0)
    {
        _go = true;
        //return;
    }
    if(_go && _moteurPhy->falling()==0 && _moteurPhy->comboting()==0&& _grille->checkLanding()==0 && _grille->checkFalling() == 0 )
    {

        if(_moteurPhy->fixed()&& _nextDarkBlobs==0)
        {
            if(_newDelay--==0){
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
            _newDelay = 2;}
        }

        if(_moteurPhy->falling()==0 && _moteurPhy->comboting()==0&& _grille->checkLanding()==0 && _go)
        {
            bool land = _moteurPhy->moove(&_master,&_slave);
            if(land&&_landing)
            {

                _masterBlob.setState(LANDING);
                _masterBlob.setLanding(LANDING_ANIM_TIME);

                _slaveBlob.setLanding(LANDING_ANIM_TIME);
                _slaveBlob.setState(LANDING);

                _landing = false;
            }
            else if(!land)
            {
                _landing = true;
            }

        }

    }



    if(_combo!=0 && _moteurPhy->comboting()==0 && _moteurPhy->falling()==0 && !_moteurPhy->fixed())
    {
        _launchCombo=true;
    }

}

void DashBoard::resetCombo()
{
    _launchCombo = false;
    _score+=_combo*10;
    _combo =0;
    _moteurPhy->setCombo(0);
}
void DashBoard::addDarkBlob()
{
    _nextDarkBlobs++;
}


