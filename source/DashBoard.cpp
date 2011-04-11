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
    else if(_moteurPhy->touching()!=0)
    {
        ;
    }
    else
    {
        if(checkCombo()) //check combo fini -> lancer combo game
        {
            ;
            std::cout<<"blob suivant\n";
            _masterBlob.setBlob(*(++_it));
            _slaveBlob.setBlob(*(++_it));
            _moteurPhy->nextBlobs(_masterBlob,_slaveBlob);
        }
    }
    _moteurPhy->moove(&_master,&_slave);
}




