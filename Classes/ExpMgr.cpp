//
//  ExpMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#include "ExpMgr.hpp"

NS_KCL_BEGIN

void ExpMgr::initPlayerExpMap(const char* aStrArray[], int aArrayLen)
{
    int index=0;
    int lv=atoi(aStrArray[index++]);
    int exp=atoi(aStrArray[index++]);
    playerExpMap[lv]=exp;
}
void ExpMgr::initKantaiExpMap(const char* aStrArray[], int aArrayLen)
{
    int index=0;
    int lv=atoi(aStrArray[index++]);
    int exp=atoi(aStrArray[index++]);
    kantaiExpMap[lv]=exp;
}

ExpMgr::ExpMgr(){}

ExpMgr::~ExpMgr()
{
    playerExpMap.clear();
    kantaiExpMap.clear();
}


bool ExpMgr::loadConf()
{
    bool bRet=false;
    do
    {
        playerExpMap.clear();
        kantaiExpMap.clear();
        
        g_loadtxt("csv/playerExp.txt", ExpMgr::playerExpMapTxtFile, ",", this);
        g_loadtxt("csv/kantaiExp.txt", ExpMgr::kantaiExpMapTxtFile, ",", this);
        bRet=true;
    }while (0);
    
    return bRet;
}

int ExpMgr::getKantaiUpdateExp(int lv)
{
    CCASSERT(lv>0&&lv<=MAX_KANTAI_LV,"input the mistake lv");
    if (MAX_KANTAI_LV==lv)
    {
        return INT_MAX;
    }
    return kantaiExpMap[lv];
}

int ExpMgr::getPlayerUpdateExp(int lv)
{
    CCASSERT(lv>0&&lv<=MAX_PLAYER_LV,"input the mistake lv");
    if (MAX_PLAYER_LV==lv)
    {
        return INT_MAX;
    }
    return playerExpMap[lv];
}

NS_KCL_END
