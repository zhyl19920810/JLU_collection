//
//  arsenal.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#include "arsenal.hpp"
#include "TimeUtil.hpp"

NS_KCL_BEGIN


void Arsenal::initArsenal(int playerKey)
{
    this->playerKey=playerKey;
    this->maxArsenalSize=sPlayer.getMaxDockSize();
    std::vector<ArsenalDBData> data;
    ArsenalDB::getInstance()->initArsenalDB(playerKey, data);
    
    
    arsenal.resize(maxArsenalSize);
    auto currTime=TimeUtil::getTimestamp();
    for (auto it=data.begin(); it!=data.end(); ++it)
    {
        ArsenalData tmp;
        tmp.kantaiNumber=it->kantaiNumber;
        tmp.completeTime=it->completeTime;
        if (it->completeTime<=currTime)
        {
            tmp.finished=true;
        }
        else
        {
            tmp.finished=false;
        }
        
        arsenal[it->position-1]=tmp;
    }
}

void Arsenal::buildNewArsenal()
{
    ArsenalData tmp;
    arsenal.push_back(tmp);
}

void Arsenal::buildNewKantai(int position, int fuel, int steel, int ammo, int aluminium, int developMaterial,bool fastRepair)
{
    CCASSERT(position>=1&&position<=maxArsenalSize, "position is out of range");
    CCASSERT(arsenal[position-1].kantaiNumber==0, "there is a ship in the position");
    
    int kantaiNumber=metaPhysics->poipoipoi(fuel, steel, ammo, aluminium, developMaterial);
    sPlayer.minusAluminium(aluminium);
    sPlayer.minusAmmo(ammo);
    sPlayer.minusFuel(fuel);
    sPlayer.minusSteel(steel);
    int buildTime=sKantaiMgr.GetKantaiMap(kantaiNumber)->buildTime;
    ino64_t completeTime=buildTime+TimeUtil::getTimestamp();
    sArsenalDB->insertKantai(playerKey, kantaiNumber, position, completeTime);
    
    ArsenalData tmp;
    tmp.kantaiNumber=kantaiNumber;
    tmp.completeTime=completeTime;
    tmp.finished=false;
    arsenal[position-1]=tmp;
}


void Arsenal::buildTimeCircle(float dt)
{
    auto currTime=TimeUtil::getTimestamp();
    for (int i=0; i<arsenal.size(); ++i)
    {
        auto unit=arsenal[i];
        if ((unit.kantaiNumber)&&(!unit.finished))
        {
            if (unit.completeTime>=currTime)
            {
                unit.finished=true;
            }
        }
    }
}

void Arsenal::finishBuildingKantai(int position)
{
    CCASSERT(position>=1&&position<=maxArsenalSize, "position is out of range");
    int kantaiNumber=arsenal[position-1].kantaiNumber;
    CCASSERT(kantaiNumber, "there is not a ship in the position");
    sArsenalDB->deleteKantai(playerKey, position);
    arsenal[position-1].kantaiNumber=0;
    arsenal[position-1].completeTime=0;
    arsenal[position-1].finished=false;
    sPlayer.buildNewKantai(kantaiNumber);
}

bool Arsenal::isBuildingFinished(int position)
{
    CCASSERT(position>=1&&position<=maxArsenalSize, "position is out of range");
    CCASSERT(arsenal[position-1].kantaiNumber!=0, "there is a ship in the position");
    return arsenal[position-1].finished;
}

//void Arsenal::startCircle()
//{
//    std::function<void(float)> f1=std::bind(&Arsenal::buildTimeCircle, this,std::placeholders::_1);
//    Director::getInstance()->getScheduler()->schedule(f1, this, 1, false, "ArsenalBuildTime");
//}
//
//void Arsenal::endCircle()
//{
//    Director::getInstance()->getScheduler()->unschedule("ArsenalBuildTime", this);
//}

bool Arsenal::haveShip(int position)
{
    CCASSERT(position>=1&&position<=maxArsenalSize, "position is out of range");
    return arsenal[position-1].kantaiNumber!=0;
}

NS_KCL_END
