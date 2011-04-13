#include "../include/DashBoard.h"

/** @brief main loop for each DashBoard
  *
  * (documentation goes here)
  */
void DashBoard::go()
{

    if(_moteurPhy->comboting()!=0)
    {

        ;
    }
    else if(_moteurPhy->falling()!=0)
    {
        _masterBlob.setColor(BLANK);
        _slaveBlob.setColor(BLANK);
        _moteurPhy->setFalling(_moteurPhy->falling()-1);
        for(int l=0; l<13; l++)
            for(int c=0; c<6; c++)
                if(((*_grille)(l,c))->state()==FALLING)
                {
                    if(((*_grille)(l,c))->current()!=0)
                    {
                        ((*_grille)(l,c))->setFalling(((*_grille)(l,c))->current()-2);
                        if(((*_grille)(l,c))->current()<=0)
                        {
                            ((*_grille)(l+((*_grille)(l,c))->fallingCol(),c))->setColor(((*_grille)(l,c))->color());
                            ((*_grille)(l,c))->setColor(BLANK);
                        }
                    }
                }
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
        int combo = _moteurPhy->moove(&_master,&_slave);
        _grille->check();
        int comboPlus = 0;
        do //check combo fini -> lancer combo game
        {
            _moteurPhy->fall();
            comboPlus = _moteurPhy->majCombo();
            combo += comboPlus;
        }while(comboPlus!=0);
        //lanbcer COMBO
    }

}




