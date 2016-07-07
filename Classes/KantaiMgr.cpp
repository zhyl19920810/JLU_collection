//
//  KantaiMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#include "KantaiMgr.hpp"

NS_KCL_BEGIN

KantaiMgr::KantaiMgr()
{}

KantaiMgr::~KantaiMgr()
{
    kantaiMap.clear();
}

bool KantaiMgr::loadConf()
{
    bool bRet=false;
    do
    {
        kantaiMap.clear();
        g_loadtxt("csv/kantai.txt", KantaiMgr::kantaiMapTxtFile, ",", this);
        bRet=true;
    }while (0);
    
    return bRet;
}


void KantaiMgr::initKantaiMap(const char **aStrArray, int aArrayLen)
{
    stKantaiData tmp;
    int index=0;
    tmp.kantaiNumber=atoi(aStrArray[index++]);
    strncpy(tmp.kantaiName, aStrArray[index++], MAX_NAME_STRING);
    strncpy(tmp.kantaiFullName, aStrArray[index++], MAX_NAME_STRING);
    tmp.kantaiType=static_cast<KantaiType>(atoi(aStrArray[index++]));
    tmp.buildTime=atoi(aStrArray[index++]);
    tmp.lv=atoi(aStrArray[index++]);
    tmp.updateLv=atoi(aStrArray[index++]);
    tmp.fuel=atoi(aStrArray[index++]);
    tmp.ammo=atoi(aStrArray[index++]);
    tmp.speed=static_cast<Move_Speed>(atoi(aStrArray[index++]));
    tmp.range=static_cast<Shooting_Range>(atoi(aStrArray[index++]));
    tmp.maxHp=atoi(aStrArray[index++]);
    tmp.transformTimes=atoi(aStrArray[index++]);
    tmp.maxLuck=atoi(aStrArray[index++]);
    tmp.maxAntiSubmarine=atoi(aStrArray[index++]);
    tmp.maxDodge=atoi(aStrArray[index++]);
    tmp.maxAntiAir=atoi(aStrArray[index++]);
    tmp.maxTorpedo=atoi(aStrArray[index++]);
    tmp.maxSearchEnemy=atoi(aStrArray[index++]);
    tmp.maxFirePower=atoi(aStrArray[index++]);
    tmp.maxArmor=atoi(aStrArray[index++]);
    tmp.initSearchEnemy=atoi(aStrArray[index++]);
    tmp.initArmor=atoi(aStrArray[index++]);
    tmp.initLuck=atoi(aStrArray[index++]);
    tmp.initAntiSubmarine=atoi(aStrArray[index++]);
    tmp.initDodge=atoi(aStrArray[index++]);
    tmp.initTorpedo=atoi(aStrArray[index++]);
    tmp.initFirePower=atoi(aStrArray[index++]);
    tmp.initAntiAir=atoi(aStrArray[index++]);
    tmp.kantaiEquipSize=atoi(aStrArray[index++]);
    
    auto tempVec=splitText(aStrArray[index++],"#");
    for (int i=0; i<tempVec.size(); ++i)
    {
        tmp.kantaiEquipInit[i]=(atoi(tempVec[i].c_str()));
    }
    tempVec.clear();
    tempVec=splitText(aStrArray[index++],"#");
    for (int i=0; i<tempVec.size(); ++i)
    {
        tmp.planeLoad[i]=(atoi(tempVec[i].c_str()));
    }
    kantaiMap[tmp.kantaiNumber]=tmp;
}

NS_KCL_END
