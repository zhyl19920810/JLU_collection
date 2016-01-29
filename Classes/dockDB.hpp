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
    
}DockDBData;


class DockDB:public DBBase
{
public:
    void initDockDB(int playerKey);
    
    
private:
    
};

#endif /* dockDB_hpp */
