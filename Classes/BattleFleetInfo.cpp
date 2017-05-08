//
//  BattleFleet.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#include "BattleFleetInfo.hpp"


NS_KCL_BEGIN

 BattleFleet* BattleFleet::create()
{
    BattleFleet* pRet=new BattleFleet;
    if(pRet&&pRet->init())
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool BattleFleet::init()
{
    
    bool bRet=false;
    
    do
    {
        m_vBattleShip.resize(MAX_SHIPS_PER_FLEET);
        for (int i=0; i<m_vBattleShip.size(); ++i)
        {
            m_vBattleShip[i]=NULL;
        }
        
        bRet=true;
    }while (0);
    
    return bRet;
}


BattleFleet::~BattleFleet()
{
    release();
}

void BattleFleet::AddShip(BattleCharacterInfo* info)
{
    for (int i=0; i<6; ++i)
    {
        if (!m_vBattleShip[i])
        {
            m_vBattleShip[i]=info;
            break;
        }
    }
}


/////////////////////////////////////////////////////////////

//Fleet::Fleet(int FleetNumber)
//{
//    this->FleetNumber = FleetNumber;
//}
//
//bool Fleet::addShip(CharacterInfo* newShip){
//    if (ships.size() > MAX_SHIPS_PER_FLEET)
//        return false;
//    ships.push_back(newShip);
//    newShip->currentFleet = FleetNumber;
//    return true;
//    
//}
//bool Fleet::switchShip(CharacterInfo* newShip, int index){
//    if (index > ships.size())
//        return false;
//    if (newShip->currentFleet == this->FleetNumber) //the newShip is from current fleet
//    {
//        if (ships[index]->inGameId == newShip->inGameId) //switch with itself, return false
//            return false;
//        int newIndex;
//        for (newIndex = 0; newIndex < ships.size(); newIndex++) //get the index of newShip
//        {
//            if (ships[newIndex]->inGameId == newShip->inGameId)
//                break;
//        }
//        
//        CharacterInfo * temp = ships[index];
//        ships[index] = newShip;
//        ships[newIndex] = temp;
//        
//        return true;
//    }
//    else
//    {
//        ships[index]->currentFleet = -1;
//        ships[index] = newShip;
//        ships[index]->currentFleet = FleetNumber;
//        return true;
//    }
//    
//}
//bool Fleet::removeShip(int index){
//    if (index > ships.size())
//        return false;
//    ships[index]->currentFleet = -1;
//    ships.erase(ships.begin() + index);
//    return true;
//}
//CharacterInfo* Fleet::getShip(int index){
//    if (index > ships.size())
//        return nullptr;
//    return ships[index];
//}
//



NS_KCL_END
