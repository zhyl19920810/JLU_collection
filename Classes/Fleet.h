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

enum FleetState
{
    KANTAI_UNUSE=120,
    KANTAI_ATTACK,
    KANTAI_PVP,
    KANTAI_EXPEDITION
};

//#define CC_GETVALUE(varType,varName)\
//public: varType get##varName(void) const {return varName;}\
//
//#define CC_RWVALUE(varType,varName)\
//public: varType get##varName(void) const {return varName;}\
//public: void set##varName(varType var) {varName=var;}\


class Fleet:public Ref
{
    CC_GETVALUE(int, fleetKey);
    CC_RWVALUE(std::string, fleetName);
    CC_RWVALUE(FleetState, fleetState);
public:
    Fleet(int _fleetKey,const std::string& _fleetName,FleetState _fleetState);
    
    Fleet(int _fleetKey):fleetKey(_fleetKey){}
    
    //create
    static Fleet* create(int _fleetKey);
    
    static Fleet* create(std::string& enemyName);

    void setFleetName(const std::string& _fleetName);
    
    void setFleetState(FleetState _fleetState);
    
    bool addShipNoDatabase(Kantai* kantai);
    
    int size();
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
