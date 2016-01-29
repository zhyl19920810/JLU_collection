//
//  RepairFactorMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#include "RepairFactorMgr.hpp"

RepairFactorMgr::RepairFactorMgr()
{
}

RepairFactorMgr::~RepairFactorMgr()
{
    repairFactorMap.clear();
}


bool RepairFactorMgr::loadConf()
{
    bool bRet=false;
    do
    {
        repairFactorMap.clear();
        g_loadtxt("csv/repairFactor.txt", RepairFactorMgr::repairFactorTxtFile, ",", this);
        bRet=true;
    }
    while (0);
    return bRet;
}

void RepairFactorMgr::initRepairFactorMap(const char **aStrArray, int aArrayLen)
{
    stRepairFactorData tmp;
    int index=0;
    int kantaiNumber=atoi(aStrArray[index++]);
    tmp.steelFactor=atof(aStrArray[index++]);
    tmp.ammoFactor=atof(aStrArray[index++]);
    repairFactorMap[kantaiNumber]=tmp;
}
