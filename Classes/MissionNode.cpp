//
//  MissionNode.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "MissionNode.hpp"
#include "MissonLoader.hpp"
#include "loadTxt.hpp"


NS_KCL_BEGIN


MissionNode::~MissionNode()
{
    if (m_pBattleFleet)
    {
        delete m_pBattleFleet;
    }
    
    for (int i=0; i<m_vChildren.size(); ++i)
    {
        delete m_vChildren[i];
    }
    release();
}


MissionNode* MissionNode::create()
{
    MissionNode* pRet=new MissionNode;
    if (pRet&&pRet->init())
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

bool MissionNode::init()
{
    bool bRet=false;
    do
    {
        m_pBattleFleet=NULL;
        bRet=true;
    }while(0);
    return bRet;
}



bool MissionNode::Available(BattleFleet* allies)
{
    return true;
}

void MissionNode::SetType(std::string type)
{
    if (type == "enemy")
        m_type = NODE_ENEMY;
    else if (type == "boss")
        m_type = NODE_BOSS;
    else if (type == "item")
        m_type = NODE_ITEM;
    else if (type == "home")
        m_type = NODE_HOME;
    else
        m_type= NODE_EMPTY;
}



void MissionNode::ParseEnemyFleet(std::string FleetText)
{
    std::vector<std::string> strings;
    strings=splitText(FleetText,"#");
    if (!strings.empty())
    {
        m_pBattleFleet=BattleFleet::create();
        for (int i = 0; i < strings.size(); i++)
        {
            m_pBattleFleet->AddShip(MissonLoader::getInstance()->LoadCharacterInfo(strings[i]));
        }
    }
}




NS_KCL_END
