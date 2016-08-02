//
//  SupplyInfo.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/2/16.
//
//

#include "SupplyInfo.hpp"
#include "Player.h"
#include "Fleet.h"
#include "portSupplyLayer.h"
#include "ViewMgr.hpp"
#include "Sound.hpp"

NS_KCL_BEGIN



SupplyImp* SupplyImp::create()
{
    auto pRet=new SupplyImp;
    if (pRet&&pRet->init())
    {
        
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool SupplyImp::init()
{
    bool bRet=false;
    do
    {
        consumeAmmo=0;
        consumeFuel=0;
        ammoST.clear();
        fuelST.clear();
        
        bRet=true;
    }while(0);
    return bRet;
}

void SupplyImp::addConsumeAmmo(int position, int ammo)
{
    SND->playEffect("soundSE/supplyButton.mp3");
    consumeAmmo+=ammo;
    ammoST.insert(std::pair<int, int>(position,ammo));
}

void SupplyImp::addConsumeFuel(int position, int fuel)
{
    SND->playEffect("soundSE/supplyButton.mp3");
    consumeFuel+=fuel;
    fuelST.insert(std::pair<int, int>(position,fuel));
}


int SupplyImp::minusConsumeAmmo(int position)
{
    SND->playEffect("soundSE/supplyButton.mp3");
    auto it=ammoST.find(position);
    CCASSERT(it!=ammoST.end(), "the position do not exist in \"function minusConsumeAmmo\"");
    int minusAmmo=it->second;
    consumeAmmo-=minusAmmo;
    ammoST.erase(it);
    
    return minusAmmo;
}

int SupplyImp::minusConsumeFuel(int position)
{
    SND->playEffect("soundSE/supplyButton.mp3");
    auto it=fuelST.find(position);
    CCASSERT(it!=fuelST.end(), "the position do not exist in \"function minusConsumeFuel\"");
    int minusFuel=it->second;
    consumeFuel-=minusFuel;
    fuelST.erase(it);
    
    return minusFuel;
}


void SupplyImp::refresh()
{
    consumeAmmo=0;
    consumeFuel=0;
    ammoST.clear();
    fuelST.clear();
}


bool SupplyImp::canFillUpAmmo(kancolle::Kantai *kantai)
{
    int ammo=kantai->getMaxAmmo()-kantai->getCurrAmmo();
    if (!ammo) {
        return false;
    }
    int haveAmmo=sPlayer.getAmmo();
    if (haveAmmo<(consumeAmmo+ammo))
    {
        return false;
    }
    return true;
}


bool SupplyImp::canFillUpFuel(kancolle::Kantai *kantai)
{
    int fuel=kantai->getMaxFuel()-kantai->getCurrFuel();
    if (!fuel) {
        return false;
    }
    int haveFuel=sPlayer.getFuel();
    if (haveFuel<(consumeFuel+fuel))
    {
        return false;
    }
    return true;
}


void SupplyImp::callAmmoButton(Fleet* fleet)
{
    auto panel=dynamic_cast<PortSupplyLayer*>(VIEW_MGR->getPanel(PanelType::PORT_SUPPLY));
    
    vector<int> positionST(6);
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    
    int sum=0;
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        int position=it->first;
        auto kantai=fleet->getShip(position);
        int ammoValue=it->second;
        --positionST[position-1];
        if (!positionST[position-1])  panel->setUnitReset(position);
        kantai->setCurrAmmo(kantai->getMaxAmmo());
        sum+=ammoValue;
    }
    ammoST.clear();
    sPlayer.minusAmmo(sum);
    consumeAmmo=0;
}


void SupplyImp::callFuelButton(Fleet* fleet)
{
    auto panel=dynamic_cast<PortSupplyLayer*>(VIEW_MGR->getPanel(PanelType::PORT_SUPPLY));
    
    vector<int> positionST(6);
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    
    int sum=0;
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        int position=it->first;
        auto kantai=fleet->getShip(position);
        int fuelValue=it->second;
        --positionST[position-1];
        if (!positionST[position-1]) panel->setUnitReset(position);
        kantai->setCurrFuel(kantai->getMaxFuel());
        sum+=fuelValue;
    }
    fuelST.clear();
    sPlayer.minusFuel(sum);
    consumeFuel=0;
}


void SupplyImp::callMidButton(Fleet* fleet)
{
    auto panel=dynamic_cast<PortSupplyLayer*>(VIEW_MGR->getPanel(PanelType::PORT_SUPPLY));
    
    int fuelSum=0;
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        int position=it->first;
        auto kantai=fleet->getShip(position);
        int fuelValue=it->second;
        
        panel->setUnitReset(position);
        kantai->setCurrFuel(kantai->getMaxFuel());
        fuelSum+=fuelValue;
    }
    fuelST.clear();
    
    int ammoSum=0;
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        int position=it->first;
        auto kantai=fleet->getShip(position);
        int ammoValue=it->second;
        
        panel->setUnitReset(position);
        kantai->setCurrAmmo(kantai->getMaxAmmo());
        ammoSum+=ammoValue;
    }
    ammoST.clear();
    
    sPlayer.minusFuel(fuelSum);
    sPlayer.minusAmmo(ammoSum);
    consumeAmmo=0;
    consumeFuel=0;
}






NS_KCL_END
