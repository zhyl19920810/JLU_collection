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

NS_KCL_BEGIN

class FleetDB:public DBBase
{
    friend class DataBaseMgr;
public:
    void getNewFleetByNumber(int fleetKey,const std::string& name,int fleetState);
    
    void deleteFleetByKey(int _fleetKey);
    
    void setFleetName(int _fleetKey,const std::string &_fleetName);
    
    void setFleetState(int _fleetKey,int state);
    
private:
    FleetDB();
    
};


NS_KCL_END

#endif /* defined(__kancolle_alpha__fleetDB__) */
