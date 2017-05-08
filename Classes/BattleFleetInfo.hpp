//
//  BattleFleet.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#ifndef BattleFleet_hpp
#define BattleFleet_hpp

#include "SystemHeader.h"
#include "BattleCharacterInfo.hpp"


NS_KCL_BEGIN

USING_NS_CC;

class BattleFleet:public Ref
{
public:
    static BattleFleet* create();
    bool init();
    ~BattleFleet();
    void AddShip(BattleCharacterInfo* info);
    
    std::vector<BattleCharacterInfo*> m_vBattleShip;
};




//////////////////////////////////////////////////////////////////////

//#include "cocos2d.h"
//#include "CharacterInfo.h"
//#define MAX_SHIPS_PER_FLEET 6
//
//class Fleet{
//public:
//    
//    Fleet(int fleetNumber);
//    bool addShip(CharacterInfo* newShip);
//    bool switchShip(CharacterInfo* newShip, int index);
//    bool removeShip(int index);
//    CharacterInfo* getShip(int index);
//    inline int getIndex(){ return FleetNumber; }
//    inline int size(){ return ships.size(); }
//private:
//    std::vector<CharacterInfo*> ships;
//    int FleetNumber;
//};








NS_KCL_END


#endif /* BattleFleet_hpp */
