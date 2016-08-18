//
//  DataBaseMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/18/16.
//
//

#ifndef DataBaseMgr_hpp
#define DataBaseMgr_hpp

#include "cocos2d.h"
#include "SystemHeader.h"


NS_KCL_BEGIN

#define DB_MGR (DataBaseMgr::getInstance())

class EquipDB;
class KantaiDB;
class PlayerDB;
class DockDB;
class ArsenalDB;
class FleetDB;


class DataBaseMgr
{
public:
    static DataBaseMgr* getInstance();
    static void destroy();
    
    EquipDB*    getEquipDB();
    KantaiDB*   getKantaiDB();
    PlayerDB*   getPlayerDB();
    DockDB*     getDockDB();
    ArsenalDB*  getArsenalDB();
    FleetDB*    getFleetDB();
    
    
    void initDB(const std::string& path,int playerKey);
    
    ~DataBaseMgr();
private:
    bool init();
    
    static DataBaseMgr* m_instance;
    
    
private:
    FleetDB*    m_fleetDB;
    EquipDB*    m_equipDB;
    KantaiDB*   m_kantaiDB;
    PlayerDB*   m_playerDB;
    DockDB*     m_dockDB;
    ArsenalDB*  m_arsenalDB;
    
};







NS_KCL_END




#endif /* DataBaseMgr_hpp */
