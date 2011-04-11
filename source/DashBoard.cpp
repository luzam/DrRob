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
    else{
        if(checkCombo()){//check combo fini -> lancer combo game
        ;
        std::cout<<"blob suivant\n";
        _moteurPhy->nextBlobs(*(++_it),*(++_it));}
        _moteurPhy->moove();
        }



    }
