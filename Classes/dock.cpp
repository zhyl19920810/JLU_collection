//
//  dock.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "dock.hpp"
#include "dockDB.hpp"

void Dock::initDock(int playerKey)
{
    this->maxDockSize=sPlayer.getMaxDockSize();
    std::vector<DockDBData>  data;
    DockDB::getInstance()->initDockDB(playerKey,data);
    
}