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
#include "arsenalDB.hpp"
#include "databaseInit.h"


NS_KCL_BEGIN


DataBaseMgr* DataBaseMgr::m_instance=NULL;

DataBaseMgr* DataBaseMgr::getInstance()
{
    if (!m_instance)
    {
        m_instance=new DataBaseMgr;
        if (!m_instance->init())
        {
            CC_SAFE_DELETE(m_instance);
        }
    }
    return m_instance;
}


bool DataBaseMgr::init()
{
    m_equipDB=new EquipDB;
    m_kantaiDB=new KantaiDB;
    m_arsenalDB=new ArsenalDB;
    m_dockDB=new DockDB;
    m_playerDB=new PlayerDB;
    m_fleetDB=new  FleetDB;
    
    return true;
}

FleetDB* DataBaseMgr::getFleetDB()
{
    return m_fleetDB;
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

void DataBaseMgr::initDB(const std::string &path, int playerKey)
{
    DBBase::init(path);
    DBInit _dbInit;
    _dbInit.initDB(playerKey);
}


void DataBaseMgr::destroy()
{
    CC_SAFE_DELETE(m_instance);
}


DataBaseMgr::~DataBaseMgr()
{
    CC_SAFE_DELETE(m_fleetDB);
    CC_SAFE_DELETE(m_equipDB);
    CC_SAFE_DELETE(m_kantaiDB);
    CC_SAFE_DELETE(m_playerDB);
    CC_SAFE_DELETE(m_dockDB);
    CC_SAFE_DELETE(m_arsenalDB);
}


NS_KCL_END
