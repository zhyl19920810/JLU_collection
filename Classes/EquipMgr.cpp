//
//  EquipMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//



#include "EquipMgr.hpp"




EquipMgr::EquipMgr()
{}

EquipMgr::~EquipMgr()
{
    equipMap.clear();
}

bool EquipMgr::loadConf()
{
    bool bRet=false;
    do
    {
        equipMap.clear();
        g_loadtxt("equip.txt", EquipMgr::equipMapTxtFile, ",", this);
        bRet=true;
    }
    while (0);
    return bRet;
}

void EquipMgr::initEquipMap(const char **aStrArray, int aArrayLen)
{
    stEquipData tmp;
    int index=0;
    tmp.equipNumber=atoi(aStrArray[index++]);
    strncpy(tmp.equipName, aStrArray[index++], MAX_NAME_STRING);
    tmp.equipScope=static_cast<EquipScope>(atoi(aStrArray[index++]));
    tmp.equipType=static_cast<EquipType>(atoi(aStrArray[index++]));
    tmp.isPlane=atoi(aStrArray[index++])?true:false;
    tmp.firePower=atoi(aStrArray[index++]);
    tmp.AviTorpedo=atoi(aStrArray[index++]);
    tmp.AviBomb=atoi(aStrArray[index++]);
    tmp.antiAir=atoi(aStrArray[index++]);
    tmp.antiSubmarine=atoi(aStrArray[index++]);
    tmp.searchEnemy=atoi(aStrArray[index++]);
    tmp.hitRate=atoi(aStrArray[index++]);
    tmp.dodge=atoi(aStrArray[index++]);
    tmp.range=atoi(aStrArray[index++]);
    tmp.armor=atoi(aStrArray[index++]);
    auto tempVec=splitText(aStrArray[index++],"#");
    for (int i=0; i<tempVec.size(); ++i)
    {
        tmp.supKantaiType[i]=(static_cast<KantaiType>(atoi(tempVec[i].c_str())));
    }
    
    equipMap[tmp.equipNumber]=tmp;
}





