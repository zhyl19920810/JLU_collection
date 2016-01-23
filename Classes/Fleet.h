//
//  FleetPlayerGot.h
//  kancolle_alpha
//
//  Created by 岩林张 on 8/1/15.
//
//

#ifndef __kancolle_alpha__FleetPlayerGot__
#define __kancolle_alpha__FleetPlayerGot__

#include "cocos2d.h"
#include "kantai.h"
#include "fleetDB.h"
#include <vector>

USING_NS_CC;




typedef enum
{
    Fleet_Free,
    Fleet_Battle,
    Fleet_Expedition,
    Fleet_Error,
}FleetState;


class Fleet:public Ref
{
    friend class DBInit;
public:
    static Fleet* create(int fleetKey,LoadState state);
    void init(int fleetKey,LoadState state);
    
    int getFleetKey() const {return fleetKey;}
    void setFleetName(const std::string& _fleetName);
    std::string getFleetName() const {return fleetName;}
    void setFleetState(FleetState _fleetState);
    FleetState getFleetState() const {return fleetState;}

    int KantaiSize();
    ~Fleet(){}
public:
    std::vector<Kantai*> ship;
    
protected:
    Fleet();
    
private:
    int fleetKey;
    
    std::string fleetName;
    
    FleetState fleetState;

};





#endif /* defined(__kancolle_alpha__FleetPlayerGot__) */
