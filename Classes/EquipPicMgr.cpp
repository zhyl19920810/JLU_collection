//
//  EquipPicMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#include "EquipPicMgr.hpp"


void EquipPicMgr::initEquipPic(const char* aStrArray[], int aArrayLen)
{
    stEquipPicData tmp;
    int index=0;
    int equipNumber=atoi(aStrArray[index++]);
    strncpy(tmp.resource, aStrArray[index++], MAX_EQUIP_NAME);
    equipPicMap[equipNumber]=tmp;
}


EquipPicMgr::EquipPicMgr(){}

EquipPicMgr::~EquipPicMgr()
{
    equipPicMap.clear();
}


bool EquipPicMgr::loadConf()
{
    bool bRet=false;
    do
    {
        equipPicMap.clear();
        
        g_loadtxt("csv/equipPic.txt", EquipPicMgr::equipPicTxtFile, ",", this);
        bRet=true;
    }while (0);
    
    return bRet;
}

EquipPicMgr::stEquipPicData* EquipPicMgr::getEquipPicMap(int equipNumber)
{
    auto it=equipPicMap.find(equipNumber);
    if (it!=equipPicMap.end())
    {
        return &it->second;
    }
    CCASSERT(false,"can not find the kantai");
}

