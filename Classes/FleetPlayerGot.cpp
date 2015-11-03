//
//  FleetPlayerGot.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 8/1/15.
//
//

#include "FleetPlayerGot.h"

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


//void Fleet::modifyShip(int location, Kantai* kantai)
//{
//    if (!kantai)
//    {
//        ship[location]=nullptr;
//    }
//    else
//    {
//        ship[location]=kantai;
//    }
//    
//}
//

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