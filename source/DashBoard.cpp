#include "../include/DashBoard.h"

/** @brief main loop for each DashBoard
  *
  * (documentation goes here)
  */
void DashBoard::go()
{

    bool retour =false;

    if(_looser)
        return;
   // if(_moteurPhy->falling()==0 && _moteurPhy->comboting() ==0 )
     //   retour = true;
   // _grille->check();
    //_moteurPhy->fall();
   // if((_moteurPhy->falling()!=0 || _moteurPhy->comboting() !=0) && retour )
     //   return ;
   // _moteurPhy->setFalling(_grille->checkFalling());

    //if(_moteurPhy->falling()==0)
      //  _moteurPhy->majCombo();
    _looser = _grille->checkLoose();
    std::cerr<<"comboting "<<_moteurPhy->comboting()<<"\n";
    std::cerr<<"falling   "<<_moteurPhy->falling()<<"\n";
    std::cerr<<"falling grille   "<<_grille->checkFalling()<<"\n";
    if(_moteurPhy->fixed())
        std::cerr<<"fixed     "<<"\n";
    if(_go)
        std::cerr<<"go     "<<"\n";
    std::cerr<<"\n";
    if(_moteurPhy->fixed())
    {
        _masterBlob.setColor(BLANK);
        _slaveBlob.setColor(BLANK);
    }


  //  if(_moteurPhy->falling()!=0)
    //{
    //    _go = false;
   //     _moteurPhy->setFalling(_moteurPhy->falling()-1);
      //  return;

  //  }
  /*  if(_moteurPhy->comboting()!=0 && _moteurPhy->falling()==0 )
    {
        //TO DO : animation comboting
        _go = false;
        _moteurPhy->setComboting(_moteurPhy->comboting()-1);
        std::cout<<"---------------->>>>>>>>>>>>>>>>"<<_moteurPhy->comboting()<<"\n";
        if(_moteurPhy->comboting()==0)
        {

            _combo =(_combo==0)?_moteurPhy->combo():(_combo!=0&&_combo<6)?_combo+2*_moteurPhy->combo():(_combo>6&&_combo<12)?_combo+4*_moteurPhy->combo():_combo+6*_moteurPhy->combo();
        }//return;
    }*/

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
    if(_go && _moteurPhy->falling()==0 && _moteurPhy->comboting()==0&& _grille->checkLanding()==0)
    {

        if(_moteurPhy->fixed()&& _nextDarkBlobs==0 )
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

            //  }
            //_delay = 100;
        }

         if(_moteurPhy->falling()==0 && _moteurPhy->comboting()==0&& _grille->checkLanding()==0 && _go)
        {
            int touching = _moteurPhy->moove(&_master,&_slave);
            if(touching!=0){
            _masterBlob.setState(LANDING);
            _slaveBlob.setState(LANDING);
            _masterBlob.setLanding(touching);
            _slaveBlob.setLanding(touching);
            }
        }
    }



    if(_combo!=0 && _moteurPhy->comboting()==0 && _moteurPhy->falling()==0 )
    {
        if(--_delay==0)
        {
            _launchCombo=true;
            std::cerr<<"COMBO ->>>>>>> "<<_combo<<"\n";
            _delay = 100;
        }
        //   return;
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


