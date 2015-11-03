//
//  Player.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/6/15.
//
//

#include "Player.h"
#include <algorithm>


Player* Player::player=nullptr;

Player* Player::getInstance()
{
    if (!player) {
        player=new (std::nothrow)Player();
    }
    return player;
}


Player::Player()
{
    //调入
    fleetData.resize(4);
}

void Player::initDatabaseData(std::unordered_map<int,Fleet*>& _fleetData,std::unordered_map<int,Kantai*>& _kantaiData,std::unordered_map<int,Equip*>& _equipData)
{
    for_each(_kantaiData.begin(),_kantaiData.end(),[&](const std::pair<int,Kantai*>& temp)
             {
                 kantaiData.push_back(temp.second);
             });
    
    for (int i=0; i<_fleetData.size(); ++i)
    {
        auto it=_fleetData.find(i+1);
        fleetData[i]=it->second;
    }

    
    
    for_each(_equipData.begin(),_equipData.end(),[&](const std::pair<int,Equip*>& temp)
             {
                 equipData.push_back(temp.second);
             });
}

//////////////////////player attr set///////////////////////////////////
void Player::setPlayerName(const std::string &name)
{
    playerName=name;
    PlayerDB::getInstance()->modifyPlayerName(playerKey,playerName);
}

void Player::setPlayerSign(const std::string &name)
{
    playerSign=name;
    PlayerDB::getInstance()->modifyPlayerSign(playerKey, name);
}

void Player::setCurrLV(int _currLV)
{
    currLV=_currLV;
    PlayerDB::getInstance()->modifyCurrLV(playerKey, _currLV);
}

void Player::setPlayerCurrExp(int _playerCurrExp)
{
    playerCurrExp=_playerCurrExp;
    PlayerDB::getInstance()->modifyPlayerCurrExp(playerKey, _playerCurrExp);
}

void Player::setFuel(int _fuel)
{
    fuel=_fuel;
    PlayerDB::getInstance()->modifyFuel(playerKey, _fuel);
}

void Player::setAmmo(int _ammo)
{
    ammo=_ammo;
    PlayerDB::getInstance()->modifyAmmo(playerKey, _ammo);
}

void Player::setSteel(int _steel)
{
    steel=_steel;
    PlayerDB::getInstance()->modifySteel(playerKey, _steel);
}

void Player::setAluminium(int _aluminium)
{
    aluminium=_aluminium;
    PlayerDB::getInstance()->modifyAluminium(playerKey, _aluminium);
}

void Player::setMaxDockSize(int _dockSize)
{
    maxDockSize=_dockSize;
    PlayerDB::getInstance()->modifyMaxDockSize(playerKey,_dockSize);
}

void Player::setMaxMissionSize(int _maxFleetSize)
{
    maxFleetSize=_maxFleetSize;
    PlayerDB::getInstance()->modifyMaxMissionSize(playerKey, _maxFleetSize);
}



//equip
void Player::buildNewEquip(int _equipNumber,int _kantaiKey,int _position)
{
    if (_kantaiKey!=-1)
    {
        Kantai* kantai;
        auto it=kantaiData.begin();
        
        while (it!=kantaiData.end())
        {
            if ((*it)->getkantaiKey()==_kantaiKey)
            {
                kantai=*it;
                break;
            }
            ++it;
        }
        
        if (it==kantaiData.end())
        {
            CCASSERT(false, "can not find the kantai in the function buildNewEquip");
        }
        int _equipKey=EquipDB::getInstance()->getNewEquipByNumber(_equipNumber,_kantaiKey,_position);
        Equip* _equip=new Equip(_equipKey,_equipNumber);
        kantai->equipGrid[_position-1]=_equip;
        equipData.push_back(_equip);
    }
    else
    {
        int _equipKey=EquipDB::getInstance()->getNewEquipByNumber(_equipNumber);
        Equip* _equip=new Equip(_equipKey,_equipNumber);
        equipData.push_back(_equip);
    }
}

void Player::deleteEquipByEquipKey(int _equipKey)
{
    Equip* equip;
    
    auto it=equipData.begin();
    
    while (it!=equipData.end())
    {
        if ((*it)->getequipKey()==_equipKey)
        {
            equip=*it;
            equipData.erase(it);
            delete equip;
            return;
        }
        ++it;
    }
    CCASSERT(false,"can not find the equip in deleteEquipByEquipKey");
    
}


void Player::deleteEquip(int _equipKey)
{
      deleteEquipByEquipKey(_equipKey);
      EquipDB::getInstance()->deleteEquipKey(_equipKey, 0);
}

void Player::deleteEquip(Kantai& kantai,int _position)
{
    int _equipKey=kantai.equipGrid[_position-1]->getequipKey();
    kantai.equipGrid[_position-1]=NULL;
    
    deleteEquipByEquipKey(_equipKey);
    EquipDB::getInstance()->deleteEquipKey(_equipKey, 1);
}

void Player::removeEquip(Kantai& kantai,int _position)
{
    int _equipKey=kantai.equipGrid[_position-1]->getequipKey();
    kantai.equipGrid[_position-1]=NULL;
    EquipDB::getInstance()->deleteEquipRelation(_equipKey);
}

Equip* Player::findEquipByEquipKey(int _equipKey)
{
    Equip* equip;
    
    auto it=equipData.begin();
    
    while (it!=equipData.end())
    {
        if ((*it)->getequipKey()==_equipKey)
        {
            equip=*it;
            return equip;
        }
        ++it;
    }

    CCASSERT(false, "can not find the equip in the findEquipByEquipKey");
    return equip;
}


Kantai* Player::findKantaiByKantaiKey(int _kantaiKey)
{
    Kantai* _kantai;
    
    auto it=kantaiData.begin();
    
    while (it!=kantaiData.end())
    {
        if ((*it)->getkantaiKey()==_kantaiKey)
        {
            _kantai=*it;
            return _kantai;
        }
        ++it;
    }
    
    CCASSERT(false, "can not find the equip in the findKantaiByKantaiKey");
    return _kantai;
}



void Player::changeEquipPosition(int _equipKey, int _kantaiKey, int _position)
{
    auto _equip=findEquipByEquipKey(_equipKey);
    
    auto _kantai=findKantaiByKantaiKey(_kantaiKey);
    
    _kantai->equipGrid[_position-1]=_equip;
    
    EquipDB::getInstance()->changeEquipPosition(_equipKey, _kantaiKey, _position);
}


void Player::buildNewKantai(int _kantaiNumber)
{
    XMLControl* kantaiXML=new XMLBaseControl;
    ValueVector _kantaiData=kantaiXML->ReadKantaiXML(_kantaiNumber);
    int _kantaiKey=KantaiDB::getInstance()->getNewKantaiByNumber(_kantaiData);
    auto _equipKey=KantaiDB::getInstance()->getNewKantaiEquip(_kantaiKey, _kantaiData);
    
    
    //init kantai in cache
    Kantai* _kantai=new Kantai(_kantaiKey, _kantaiData);
    kantaiData.push_back(_kantai);
    
    
    int size=static_cast<int>(_equipKey.size());
    for (int i=0;i<size;++i)
    {
        Equip* equip=new Equip(_equipKey[i].first, _equipKey[i].second);
        _kantai->equipGrid[i]=equip;
        equipData.push_back(equip);
    }
}

void Player::deleteKantai(int _kantaiKey)
{
    Kantai* _kantai;
    
    auto it=kantaiData.begin();
    while (it!=kantaiData.end())
    {
        if ((*it)->getkantaiKey()==_kantaiKey)
        {
            _kantai=*it;
            break;
        }
        ++it;
    }
    
    if (it==kantaiData.end())
    {
        CCASSERT(false, "have no kantai in deleteKantai");
    }
    
    for (auto it=_kantai->equipGrid.begin(); it!=_kantai->equipGrid.end(); ++it)
    {
        Equip* equipTemp=*it;
        if (equipTemp)
        {
            int _equipKey=equipTemp->getequipKey();
            auto equipIt=find(equipData.begin(),equipData.end(),equipTemp);
            equipData.erase(equipIt);
             delete equipTemp;
            *it=0;
            EquipDB::getInstance()->deleteEquipKey(_equipKey, true);
        }
    }
    
    kantaiData.erase(it);
    delete _kantai;
    
    KantaiDB::getInstance()->deleteKantaiKey(_kantaiKey, false);
}

void Player::deleteKantai(Fleet& _fleet,int _position)
{
    Kantai* kantaiTemp=_fleet.ship[_position-1];
    _fleet.ship[_position-1]=NULL;
    
    int _kantaiKey=kantaiTemp->getkantaiKey();
    Kantai* _kantai;
    
    auto it=kantaiData.begin();
    while (it!=kantaiData.end())
    {
        if ((*it)->getkantaiKey()==_kantaiKey)
        {
            _kantai=*it;
            break;
        }
        ++it;
    }
    
    if (it==kantaiData.end())
    {
        CCASSERT(false, "have no kantai in deleteKantai");
    }
    
    for (auto it=_kantai->equipGrid.begin(); it!=_kantai->equipGrid.end(); ++it)
    {
        Equip* equipTemp=*it;
        int _equipKey=equipTemp->getequipKey();
        auto equipIt=find(equipData.begin(),equipData.end(),equipTemp);
        equipData.erase(equipIt);
        delete equipTemp;
        
        EquipDB::getInstance()->deleteEquipKey(_equipKey, true);
    }
    
    kantaiData.erase(it);
    delete _kantai;
    
    KantaiDB::getInstance()->deleteKantaiKey(_kantaiKey, true);
    
}


void Player::removeKantai(Fleet &_fleet, int _position)
{
    Kantai* kantaiTemp=_fleet.ship[_position-1];
    _fleet.ship[_position]=NULL;
    
    int _kantaiKey=kantaiTemp->getkantaiKey();
    KantaiDB::getInstance()->deleteKantaiFleet(_kantaiKey);
}


void Player::changeKantaiPosition(int _kantaiKey, int _fleetNumber, int _position)
{
    auto _kantai=findKantaiByKantaiKey(_kantaiKey);
    
    fleetData[_fleetNumber-1]->ship[_position-1]=_kantai;
    
    KantaiDB::getInstance()->changeKantaiPosition(_kantaiKey, _fleetNumber, _position);
}







//fleet
void Player::buildNewFleet(int _fleetKey)
{
    const std::string _name="Fleet";
    Fleet* _fleet=new Fleet(_fleetKey,_name,KANTAI_UNUSE);
    fleetData[_fleetKey-1]=_fleet;
    FleetDB::getInstance()->getNewFleetByNumber(_fleetKey);
}




void Player::deleteFleet(int _fleetNumber)
{
    Fleet* _fleet=fleetData[_fleetNumber-1];
    
    for (auto it=_fleet->ship.begin(); it!=_fleet->ship.end(); ++it)
    {
        if (*it)
        {
            int _kantaiKey=(*it)->getkantaiKey();
            KantaiDB::getInstance()->deleteKantaiFleet(_kantaiKey);
        }
    }
    fleetData[_fleetNumber-1]=0;
    delete _fleet;
    
    int _fleetKey=_fleetNumber;
    FleetDB::getInstance()->deleteFleetByKey(_fleetKey);
    
}

Fleet* Player::findFleetByFleetKey(int _fleetKey)
{
    return fleetData[_fleetKey];
    
}
