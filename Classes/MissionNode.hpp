//
//  MissionNode.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef MissionNode_hpp
#define MissionNode_hpp


#include "SystemHeader.h"
#include "BattleFleetInfo.hpp"

NS_KCL_BEGIN


enum MissionNodeType
{
    NODE_ENEMY,
    NODE_ITEM,
    NODE_EMPTY,
    NODE_BOSS,
    NODE_HOME,
    NODE_DISASTER
};

class MissionNode:public Ref
{
public:
    static MissionNode* create();
    ~MissionNode();
    bool init();
    void SetType(std::string type);
    bool Available(BattleFleet *allies);
    void ParseEnemyFleet(std::string enemyFleet);
    CompassDirection           compassDirection;
    MissionNodeType            m_type;
    Point                      position;
    BattleFleet*               m_pBattleFleet;
    std::vector<MissionNode*>  m_vChildren;
};


NS_KCL_END

#endif /* MissionNode_hpp */
