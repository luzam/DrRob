#include "../include/DashBoard.h"

/** @brief main loop for each DashBoard
  *
  * (documentation goes here)
  */
void DashBoard::go()
{
    int combo = _moteurPhy->majCombo();
    _moteurPhy->fall();
    _grille->check();
    std::cout<<"\n\nmoteur phy : \nfalling : "<<_moteurPhy->falling()<<"\ncomboting : "<<_moteurPhy->comboting()<<"\n\n\n";
    if(_go && _moteurPhy->falling()==0 && _moteurPhy->comboting()==0/* && _moteurPhy->bimming==0*/)
    {
        if(_moteurPhy->fixed())
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
        _moteurPhy->moove(&_master,&_slave);
    }


    if(_moteurPhy->comboting()!=0)
    {
        //TO DO : animation comboting
        _go = false;
        _moteurPhy->setComboting(_moteurPhy->comboting()-1);
        std::cout<<"---------------->>>>>>>>>>>>>>>>"<<_moteurPhy->comboting()<<"\n";


    }
    if(_moteurPhy->falling()!=0)
    {
        _go = false;
        //_masterBlob.setColor(BLANK);
        //_slaveBlob.setColor(BLANK);
        _moteurPhy->setFalling(_moteurPhy->falling()-1);

    }
    if(_moteurPhy->comboting()==0 && _moteurPhy->falling()==0)
        _go = true;


    _combo+=combo;
    if(_combo!=0 && combo==0)
    {
        _launchCombo=true;
        std::cout<<"COMBO ->>>>>>> "<<_combo<<"\n";
    }
}

void DashBoard::resetCombo()
{
    _launchCombo = false;
    _combo =0;
}



