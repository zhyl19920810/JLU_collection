//
//  dockDB.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#ifndef dockDB_hpp
#define dockDB_hpp

#include "cocos2d.h"
#include "databaseBase.h"

USING_NS_CC;

#define sDockDB DockDB::getInstance()

typedef struct
{
    int kantaiKey;
    int position;
    int completeTime;
}DockDBData;


class DockDB:public DBBase
{
public:
    void initDockDB(int playerKey,std::vector<DockDBData>&  data);
    
    void insertKantai(int playerKey,int kantaiKey,int position,int buildingTime);
    
    void deleteKantai(int playerKey,int kantaiKey);
    
    static DockDB* getInstance();
protected:
    DockDB();
    
    
private:
    static DockDB* dockDB;
    
};

#endif /* dockDB_hpp */


//insert into kantai_in_repair(playerKey,kantaiKey,position,completeTime) Values(1,52,1, strftime('%s','now','+2 hour'));