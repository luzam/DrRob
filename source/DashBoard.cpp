#include "../include/DashBoard.h"

/** @brief main loop for each DashBoard
  *
  * (documentation goes here)
  */
void DashBoard::go()
{

    if(_moteurPhy->comboting()!=0)
    {
        ;//anim comboting
    }
    else if(_moteurPhy->falling()!=0)
    {
        ;//anim falling
    }
    else if(_moteurPhy->fixed())
    {
        std::cout<<"blob suivant\n";
        _masterBlob.setBlob(_nextMaster);
        _slaveBlob.setBlob(_nextSlave);
        std::cout<<"MASTER COLOR ::::::"<<_nextMaster.color()<<std::endl;
        _nextMaster.setBlob(*(++_it));
        _nextSlave.setBlob(*(++_it));
        _moteurPhy->nextBlobs(_masterBlob,_slaveBlob);
    }
    else
    {
        if(checkCombo()) //check combo fini -> lancer combo game
        {
            ;//launchcombo?

        }
    }
    _moteurPhy->moove(&_master,&_slave);
}




