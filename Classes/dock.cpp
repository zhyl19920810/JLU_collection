//
//  dock.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "dock.hpp"
#include "dockDB.hpp"
#include "RepairFactorMgr.hpp"


void Dock::initDock(int playerKey)
{
    this->playerKey=playerKey;
    this->maxDockSize=sPlayer.getMaxDockSize();
    std::vector<DockDBData>  data;
    DockDB::getInstance()->initDockDB(playerKey,data);
    
    dock.resize(maxDockSize);
    for (auto it=data.begin(); it!=data.end(); ++it)
    {

        if (it->completeTime<=0)
        {
            Kantai* kantai=sPlayer.getKantaiByKantaiKey(it->kantaiKey);
            finishRepairKantai(kantai, it->position);
        }
        else
        {
            DockData tmp;
            tmp.kantai=sPlayer.getKantaiByKantaiKey(it->kantaiKey);
            tmp.remainTime=it->completeTime;
            dock[it->position-1]=tmp;
        }
    }
    startCircle();
}

void Dock::buildNewDock()
{
    DockData tmp;
    dock.push_back(tmp);
}

void Dock::repairKantai(Kantai *kantai, int position)
{
    CCASSERT(position>=1&&position<=maxDockSize, "position is out of range");
    CCASSERT(dock[position-1].kantai!=NULL, "there is a ship in the position");
    
    kantai->setKantaiState(KantaiState::Repairing);
    float lostHp=static_cast<float>(kantai->getMaxHp()-kantai->getCurrHp());
    
    float steelFactor=sRepairFactorMgr.getSteelFactor(kantai->getKantaiNumber());
    int consumeSteel=static_cast<int>(steelFactor*lostHp);
    sPlayer.minusSteel(consumeSteel);

    
    float ammoFactor=sRepairFactorMgr.getAmmoFactor(kantai->getKantaiNumber());
    int consumeAmmo=static_cast<int>(ammoFactor*lostHp);
    sPlayer.minusAmmo(consumeAmmo);
    
    int repairTime=calRepairTime(kantai,lostHp);
    sDockDB->insertKantai(playerKey, kantai->getKantaiKey(), position, repairTime);
    DockData tmp;
    tmp.kantai=kantai;
    tmp.remainTime=repairTime;
    dock[position-1]=tmp;
}

int Dock::calAugValue(int currLV)
{
    return sqrt(currLV)*10+50;
}


const Dock::DockData&  Dock::getDockData(int position)
{
    CCASSERT(position>=1&&position<=maxDockSize,"can not get the dock");
    return dock[position-1];
}

bool Dock::haveDock(int position)
{
    if (position<=0||position>maxDockSize)
    {
        log("position is not exist");
        return false;
    }
    return dock[position-1].kantai?true:false;
}


void Dock::startCircle()
{
    std::function<void(float)> f1=std::bind(&Dock::repairTimeCircle, this,std::placeholders::_1);
    Director::getInstance()->getScheduler()->schedule(f1, this, 1, false, "dockRemainTime");
}

void Dock::endCircle()
{
    Director::getInstance()->getScheduler()->unschedule("dockRemainTime", this);
}

void Dock::repairTimeCircle(float dt)
{
    for (int i=0;i<dock.size();++i)
    {
        auto unit=dock[i];
        if (unit.kantai)
        {
            --unit.remainTime;
            if (unit.remainTime<=0)
            {
                finishRepairKantai(unit.kantai, i+1);
            }
        }
    }
}

void Dock::cancelRepairKantai(Kantai *kantai, int position)
{
    CCASSERT(kantai, "can not cancel the repaired kantai");
    sDockDB->deleteKantai(playerKey, kantai->getKantaiKey());
    kantai->setKantaiState(KantaiState::Free);
    dock[position-1].kantai=NULL;
    dock[position-1].remainTime=0;
}


void Dock::finishRepairKantai(Kantai *kantai, int position)
{
    CCASSERT(kantai, "can not finish the repaired kantai");
    sDockDB->deleteKantai(playerKey, kantai->getKantaiKey());
    kantai->setKantaiState(KantaiState::Free);
    kantai->setCurrHp(kantai->getMaxHp());
    dock[position-1].kantai=NULL;
    dock[position-1].remainTime=0;
}


int Dock::calRepairTime(Kantai *kantai,int lostHp)
{
    float ratio=0;
    switch (kantai->getKantaiType())
    {
        case KantaiType::Submarine:
            ratio=0.5;
            break;
        case KantaiType::Destroyer:
        case KantaiType::Light_Cruiser:
        case KantaiType::Torpedo_Cruiser:
        case KantaiType::Training_Cruiser:
        case KantaiType::Seaplane_Carrier:
        case KantaiType::Diving_Carrier:
        case KantaiType::Landing_craft:
            ratio=1;
            break;
        case KantaiType::Heavy_Cruiser:
        case KantaiType::Air_Cruiser:
        case KantaiType::Battle_Cruiser:
        case KantaiType::Light_Carrier:
        case KantaiType::Diving_Mothership:
            ratio=1.5;
            break;
        case KantaiType::Battleship:
        case KantaiType::Battle_Carrier:
        case KantaiType::Carrier:
        case KantaiType::Armor_Carrier:
        case KantaiType::Workboat:
            ratio=2.0;
            break;
        default:
            break;
    }
    if (kantai->getCurrLV()<=11)
    {
        return kantai->getCurrLV()*10*ratio*lostHp+30;
    }
    int augmentValue=calAugValue(kantai->getCurrLV());
    return (kantai->getCurrLV()*5+augmentValue)*ratio*lostHp+30;
}