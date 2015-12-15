//
//  MissionNode.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#ifndef __kancolle_alpha__MissionNode__
#define __kancolle_alpha__MissionNode__

#include "cocos2d.h"
#include "Fleet.h"
#include "Compass.h"

USING_NS_CC;

enum MissionNodeType
{
    node_enemy,
    node_item,
    node_empty,
    node_boss,
    node_home,
    node_disaster
};


class MissionNode
{
public:
    MissionNode();
    
    void setType(const std::string& type);
    
    void available(Fleet* allies);
    
    Fleet* parseEnemyFleet(const std::string &name);
    
    Compass_Direction compassDirection;
    
    MissionNodeType type;
    
    Point position;
    
    Fleet* enemyFleet;
    
    std::vector<MissionNode*> children;
};




#endif /* defined(__kancolle_alpha__MissionNode__) */
