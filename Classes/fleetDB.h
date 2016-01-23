//
//  fleetDB.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#ifndef __kancolle_alpha__fleetDB__
#define __kancolle_alpha__fleetDB__

#include "cocos2d.h"
#include "databaseBase.h"

using namespace cocos2d;

class FleetDB:public DBBase
{
public:
    void getNewFleetByNumber(int fleetKey,const std::string& name,int fleetState);
    
    static FleetDB* getInstance();
    
    void deleteFleetByKey(int _fleetKey);
    
    void setFleetName(int _fleetKey,const std::string &_fleetName);
    
    void setFleetState(int _fleetKey,int state);
protected:
    FleetDB();
    
private:
    static FleetDB* fleetDB;
    
};

#endif /* defined(__kancolle_alpha__fleetDB__) */
