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
#include "KantaiPlayerGot.h"
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


class Fleet
{
    CC_GETVALUE(int, fleetKey);
    CC_RWVALUE(std::string, fleetName);
    CC_RWVALUE(FleetState, fleetState);
public:
    Fleet(int _fleetKey,const std::string& _fleetName,FleetState _fleetState);
    
    Fleet(int _fleetKey):fleetKey(_fleetKey){}
    
   // void modifyShip(int location,Kantai* kantai=NULL);
    
    //void setKantai(Kantai* kantai,int position){ship[--position]=kantai;}
    void setFleetName(const std::string& _fleetName);
    
    void setFleetState(FleetState _fleetState);
    
    bool addShipNoDatabase(Kantai* kantai);
    
    int size();
public:
    std::vector<Kantai*> ship;

    
private:
    int fleetKey;
    
    std::string fleetName;
    
    FleetState fleetState;

};







//class Fleet:public Ref
//{
//    
//    CC_SYNTHESIZE(std::string,fleetName,FleetName);
//public:
//    Fleet(std::initializer_list<Kantai*> data,std::string s="第一舰队"):fleetNumber(fleetCount),fleetName(s)
//    {
//        if(data.size()<=6)
//        {
//            //std::for_each(data.begin(), data.end(), fleetData);
//            ++fleetCount;
//        }
//     
//    }
//    
//    Kantai* getFleet(int _kantaiLoc){return fleetData[_kantaiLoc];}
//    
//    void setFleet(int _kantaiLoc,Kantai* _kantai)
//    {
//        if(_kantaiLoc>6)
//        {
//            CCASSERT(false, "this is something wring with set fleet");
//        }
//        else
//        {
//            fleetData[_kantaiLoc]=_kantai;
//        }
//    }
//    
//    
//    
//private:
//    const int fleetNumber;
//    
//    std::array<Kantai*,6> fleetData;
//    
//    int fleetState;
//    
//    
//    static int fleetCount;
//    
//};



#endif /* defined(__kancolle_alpha__FleetPlayerGot__) */
