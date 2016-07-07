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

NS_KCL_BEGIN

class DBInit:public DBBase
{
public:
    void initDB(int _playerKey);
    
private:
    void initPlayer(int _playerKey);
    
    void initFleet(std::unordered_map<int,Fleet*>& _kantaiFleet);
    
    void initKantai(std::unordered_map<int,Kantai*>& _kantaiMap);
    
    void initEquip(std::unordered_map<int,Equip*>& _kantaiEquip);
    
    void initFleetKantai(std::unordered_map<int,std::pair<int, int>>& _fleetKantaiMap);
    
    void initKantaiEquip(std::unordered_map<int,std::pair<int, int>>& _kantaiEquipMap);
    
    std::vector<int> parsePlaneLoad(char* planeLoad);
    
    std::string convertToStr(std::vector<int> &planeLoadVec);
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__databaseInit__) */
