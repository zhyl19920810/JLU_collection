//
//  DataBaseMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/18/16.
//
//

#include "DataBaseMgr.hpp"
#include "equipDB.h"
#include "kantaiDB.h"
#include "playerDB.h"
#include "fleetDB.h"
#include "dockDB.hpp"
#include "arsenal.hpp"
#include "databaseInit.h"


NS_KCL_BEGIN

DataBaseMgr* DataBaseMgr::getInstance()
{
    if (!m_instance)
    {
        m_instance=new DataBaseMgr;
        m_instance->init();
    }
    return m_instance;
}


bool DataBaseMgr::init()
{
    
}


EquipDB* DataBaseMgr::getEquipDB()
{
    return m_equipDB;
}

KantaiDB* DataBaseMgr::getKantaiDB()
{
    return m_kantaiDB;
}

PlayerDB* DataBaseMgr::getPlayerDB()
{
    return m_playerDB;
}

DockDB*   DataBaseMgr::getDockDB()
{
    return m_dockDB;
}

ArsenalDB* DataBaseMgr::getArsenalDB()
{
    return m_arsenalDB;
}









NS_KCL_END
