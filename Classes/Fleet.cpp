//
//  FleetPlayerGot.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 8/1/15.
//
//

#include "Fleet.h"

Fleet::Fleet(int _fleetKey,const std::string& _fleetName,FleetState _fleetState):fleetKey(_fleetKey),fleetName(_fleetName),fleetState(_fleetState)
{
    ship.resize(6);
}

bool Fleet::addShipNoDatabase(Kantai *kantai)
{
    if (ship.size()>=6)
    {
        return false;
    }
    ship.push_back(kantai);
    
    return true;
}

Fleet* Fleet::create(std::string &enemyName)
{
    
    
    
    
    
}

Fleet::Fleet()
{
    ship.resize(6);
}


int Fleet::size()
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
    fleetName=_fleetName;
    FleetDB::getInstance()->setFleetName(fleetKey,_fleetName);
}

void Fleet::setFleetState(FleetState _fleetState)
{
    fleetState=_fleetState;
    FleetDB::getInstance()->setFleetState(fleetKey,_fleetState);
}