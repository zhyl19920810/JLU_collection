//
//  FleetPlayerGot.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 8/1/15.
//
//

#include "Fleet.h"
#include "DataBaseMgr.hpp"


NS_KCL_BEGIN

Fleet* Fleet::create(int fleetKey,LoadState state)
{
    Fleet* fleet=new Fleet;
    if (fleet) {
        fleet->init(fleetKey, state);
    }
    else
    {
        CCASSERT(false, "can not init the fleet");
    }
    return fleet;
}


void Fleet::init(int fleetKey, LoadState state)
{
    this->fleetKey=fleetKey;
    switch (state)
    {
        case LoadState::INIT_UNIT:
        {
            fleetState=Fleet_Free;
            this->fleetName="new FLEET";
            break;
        }
        case LoadState::READ_KANTAI_DATABASE:
        {
            break;
        }
        default:
            break;
    }
}


Fleet::Fleet()
{
    ship.resize(6);
}


int Fleet::KantaiSize()
{
    int count=0;
    for (int i=0; i<6; ++i)
    {
        if (ship[i])
        {
            ++count;
        }
    }
    return count;
}


void Fleet::setFleetName(const std::string &_fleetName)
{
    CCASSERT(_fleetName.size()<=30, "fleetName is too big");
    fleetName=_fleetName;
    DB_MGR->getFleetDB()->setFleetName(fleetKey,_fleetName);
}

void Fleet::setFleetState(FleetState _fleetState)
{
    
    fleetState=_fleetState;
    DB_MGR->getFleetDB()->setFleetState(fleetKey,_fleetState);
}

NS_KCL_END
