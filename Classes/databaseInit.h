//
//  databaseInit.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#ifndef __kancolle_alpha__databaseInit__
#define __kancolle_alpha__databaseInit__

#include "cocos2d.h"
#include "databaseBase.h"
#include "Player.h"


class DBInit:public DBBase
{
public:
    Player* initDB(int _playerKey);
    
private:
    Player* initPlayer(int _playerKey);
    
    void initFleet(const Player* player,std::unordered_map<int,Fleet*>& _kantaiFleet);
    
    void initKantai(const Player* player,std::unordered_map<int,Kantai*>& _kantaiMap);
    
    void initEquip(const Player* player,std::unordered_map<int,Equip*>& _kantaiEquip);
    
    void initFleetKantai(const Player *player,std::unordered_map<int,std::pair<int, int>>& _fleetKantaiMap);
    
    void initKantaiEquip(const Player *player,std::unordered_map<int,std::pair<int, int>>& _kantaiEquipMap);
    
};



#endif /* defined(__kancolle_alpha__databaseInit__) */
