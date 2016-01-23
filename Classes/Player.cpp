//
//  Player.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/6/15.
//
//

#include "Player.h"
#include <algorithm>



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


//exp
void Player::LVup()
{
    if (MAX_PLAYER_LV==currLV) {
        CCASSERT(false, "can not update");
    }
    currLV+=1;
    PlayerDB::getInstance()->modifyCurrLV(playerKey, currLV);
}

void Player::addPlayerCurrExp(int addExp)
{
    if (MAX_PLAYER_LV==getCurrLV())
    {
        return;
    }
    this->playerCurrExp+=addExp;
    while (playerCurrExp>=getPlayerUpdateExp())
    {
        this->playerCurrExp-=getPlayerUpdateExp();
        LVup();
        setUpdateExp();
        if (getCurrLV()==MAX_PLAYER_LV)
        {
            this->playerCurrExp=MAX_PLAYER_LV_EXP;
            PlayerDB::getInstance()->modifyCurrLV(playerKey,getCurrLV());
            PlayerDB::getInstance()->modifyPlayerCurrExp(playerKey,getPlayerCurrExp());
            setMaxAttr();
            ///updateExp 用不用加？
            return;
        }
    }
    setMaxAttr();
    PlayerDB::getInstance()->modifyCurrLV(playerKey,getCurrLV());
    PlayerDB::getInstance()->modifyPlayerCurrExp(playerKey,getPlayerCurrExp());
    //updateExp 用不用加？
}

void Player::setMaxAttr()
{
    setMaxAmmo();
    setMaxAluminium();
    setMaxFuel();
    setMaxSteel();
    setMaxKantaiSize();
    setMaxEquipSize();
}

void Player::setMaxAmmo()
{
    maxAmmo=InitPlayerProp::getMaxAmmoByLV(getCurrLV());
}

void Player::setMaxAluminium()
{
    maxAluminium=InitPlayerProp::getMaxAluminiumByLV(getCurrLV());
}

void Player::setMaxFuel()
{
    maxFuel=InitPlayerProp::getMaxFuelByLV(getCurrLV());
}

void Player::setMaxSteel()
{
    maxSteel=InitPlayerProp::getMaxSteelByLV(getCurrLV());
}

void Player::setMaxKantaiSize()
{
    maxKantaiSize=InitPlayerProp::getMaxKantaiSize(getCurrLV());
}

void Player::setMaxEquipSize()
{
    maxEquipSize=InitPlayerProp::getMaxEquipSize(getCurrLV());
}

void Player::setUpdateExp()
{
    playerUpdateExp=sExpMgr.getPlayerUpdateExp(getCurrLV());
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

void Player::addFuel(int addFuel)
{
    int tempFuel=fuel;
    this->fuel+=addFuel;
    if (fuel>getMaxFuel())
    {
        fuel=getMaxFuel();
    }
    if (tempFuel==fuel)
    {
        return;
    }
    PlayerDB::getInstance()->modifyFuel(playerKey, fuel);
}

void Player::addAmmo(int addAmmo)
{
    int tempAmmo=ammo;
    this->ammo+=addAmmo;
    if (ammo>getMaxAmmo())
    {
        ammo=getMaxAmmo();
    }
    if (tempAmmo==ammo)
    {
        return;
    }
    PlayerDB::getInstance()->modifyAmmo(playerKey, ammo);
    
}

void Player::addAluminium(int addAluminium)
{
    int tempAluminium=aluminium;
    this->aluminium+=addAluminium;
    if (aluminium>getMaxAluminium())
    {
        aluminium=getMaxAluminium();
    }
    if (tempAluminium==aluminium) {
        return;
    }
    PlayerDB::getInstance()->modifyAluminium(playerKey, aluminium);
}

void Player::addSteel(int addSteel)
{
    int tempSteel=steel;
    this->steel+=addSteel;
    if (steel>getMaxSteel())
    {
        steel=getMaxSteel();
    }
    if (tempSteel==steel) {
        return;
    }
    PlayerDB::getInstance()->modifySteel(playerKey, steel);
}

bool Player::canMinusFuel(int miFuel)
{
    if (fuel>=miFuel) {
        return true;
    }
    return false;
}

bool Player::canMinusAmmo(int miAmmo)
{
    if (ammo>=miAmmo)
    {
        return true;
    }
    return false;
}

bool Player::canMinusAluminium(int miAluminium)
{
    if (aluminium>=miAluminium) {
        return true;
    }
    return false;
}

bool Player::canMinusSteel(int miSteel)
{
    if (steel>=miSteel) {
        return true;
    }
    return false;
}

void Player::minusFuel(int miFuel)
{
    fuel-=miFuel;
    PlayerDB::getInstance()->modifyFuel(playerKey, fuel);
}
void Player::minusAmmo(int miSteel)
{
    steel-=miSteel;
    PlayerDB::getInstance()->modifySteel(playerKey, steel);
}
void Player::minusAluminium(int miAluminium)
{
    aluminium-=miAluminium;
    PlayerDB::getInstance()->modifyAluminium(playerKey, aluminium);
}
void Player::minusSteel(int miSteel)
{
    steel-=miSteel;
    PlayerDB::getInstance()->modifySteel(playerKey, steel);
}
void Player::setMaxDockSize(int _dockSize)
{
    maxDockSize=_dockSize;
    PlayerDB::getInstance()->modifyMaxDockSize(playerKey,_dockSize);
}

void Player::setMaxMissionSize(int _maxMissionSize)
{
    maxMissionSize=_maxMissionSize;
    PlayerDB::getInstance()->modifyMaxMissionSize(playerKey, _maxMissionSize);
}



//equip
Equip* Player::buildNewEquip(int _equipNumber,int _kantaiKey,int _position)
{
    Equip* _equip=NULL;
    if (_kantaiKey!=-1)
    {
        Kantai* kantai;
        auto it=kantaiData.begin();
        
        while (it!=kantaiData.end())
        {
            if ((*it)->getKantaiKey()==_kantaiKey)
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
        _equip=Equip::create(_equipKey,_equipNumber);
        _equip->setKantai(kantai);
        kantai->equipGrid[_position-1]=_equip;
        equipData.push_back(_equip);
    }
    else
    {
        int _equipKey=EquipDB::getInstance()->getNewEquipByNumber(_equipNumber);
        _equip=Equip::create(_equipKey,_equipNumber);
        equipData.push_back(_equip);
    }
    return _equip;
}

int Player::_deleteEquipByEquipKey(int _equipKey)
{
    Equip* equip;
    int retKantaiKey=-1;
    auto it=equipData.begin();
    
    while (it!=equipData.end())
    {
        if ((*it)->getEquipKey()==_equipKey)
        {
            equip=*it;
            auto kantai=dynamic_cast<Kantai*>(equip->getKantai());
            if (kantai) {
                for (int i=0;i<kantai->getKantaiEquipSize();++i)
                {
                    auto _equip=kantai->equipGrid[i];
                    if (_equip)
                    {
                        if (_equip->getEquipKey()==_equipKey)
                        {
                            retKantaiKey=kantai->getKantaiKey();
                            _equip=NULL;
                            break;
                        }
                    }
                }
            }
            equipData.erase(it);
            delete equip;
            equip=NULL;
            return retKantaiKey;
        }
        ++it;
    }
    CCASSERT(false,"can not find the equip in deleteEquipByEquipKey");
}


int Player::_deleteEquipNodb(Equip *equip)
{
    int retKantaiKey=-1;
    auto kantai=dynamic_cast<Kantai*>(equip->getKantai());
    if (kantai)
    {
        for (int i=0;i<kantai->getKantaiEquipSize();++i)
        {
            auto _equip=kantai->equipGrid[i];
            if (_equip)
            {
                if (_equip==equip)
                {
                    retKantaiKey=kantai->getKantaiKey();
                    _equip=NULL;
                    break;
                }
            }
        }
    }
    auto it=equipData.begin();
    while (it!=equipData.end())
    {
        if (equip==*it) {
            equipData.erase(it);
            delete equip;
            equip=NULL;
            return retKantaiKey;
        }
        ++it;
    }
    CCASSERT(false,"can not find the equip in deleteEquipByEquipKey");
}

void Player::deleteEquip(Equip *_equip)
{
    if (_deleteEquipNodb(_equip))
    {
        EquipDB::getInstance()->deleteEquipKey(_equip->getEquipKey(), 1);
    }
    else
    {
        EquipDB::getInstance()->deleteEquipKey(_equip->getEquipKey(), 0);
    }
    
}

void Player::deleteEquip(int _equipKey)
{
    
    if (_deleteEquipByEquipKey(_equipKey))
    {
        EquipDB::getInstance()->deleteEquipKey(_equipKey, 1);
    }
    else
    {
        EquipDB::getInstance()->deleteEquipKey(_equipKey, 0);
    }
}


void Player::removeEquip(Kantai* kantai,int _position)
{
    int _equipKey=kantai->equipGrid[_position-1]->getEquipKey();
    kantai->equipGrid[_position-1]=NULL;
    EquipDB::getInstance()->deleteEquipRelation(_equipKey);
}

Equip* Player::findEquipByEquipKey(int _equipKey)
{
    Equip* equip;
    
    auto it=equipData.begin();
    
    while (it!=equipData.end())
    {
        if ((*it)->getEquipKey()==_equipKey)
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
        if ((*it)->getKantaiKey()==_kantaiKey)
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
    changeEquipPosition(_equip, _kantai, _position);
}

void Player::changeEquipPosition(Equip *equip, Kantai* kantai, int _position)
{
    auto _kantai=dynamic_cast<Kantai*>(equip->getKantai());
    if (_kantai)
    {
        int prePosition=-1;
        for (int i=0; i<_kantai->getKantaiEquipSize(); ++i)
        {
            if (_kantai->equipGrid[i])
            {
                if (_kantai->equipGrid[i]==equip) {
                    prePosition=i+1;
                    break;
                }
            }
        }
        removeEquip(_kantai, prePosition);
    }
    _changeEquipPosition(equip,kantai,_position);
}


void Player::_changeEquipPosition(Equip* _equip, Kantai* _kantai, int _position)
{
    _kantai->equipGrid[_position-1]=_equip;
    _equip->setKantai(_kantai);
    
    EquipDB::getInstance()->changeEquipPosition(_equip->getEquipKey(), _kantai->getKantaiKey(), _position);
}


Kantai* Player::buildNewKantai(int _kantaiNumber)
{
    Kantai* kantai=Kantai::create(-1, _kantaiNumber, LoadState::INIT_UNIT);
    int _kantaiKey=KantaiDB::getInstance()->getNewKantaiByNumber(kantai->kantaiNumber);
    vector<int> equipVec;
    for (int i=0; i<kantai->getKantaiEquipSize(); ++i)
    {
        int tmp=kantai->kantaiImp->kantaiEquipInit[i];
        if (tmp) {
            equipVec.push_back(tmp);
        }
    }
    auto _equipKey=KantaiDB::getInstance()->getNewKantaiEquip(_kantaiKey, equipVec);
    kantai->kantaiKey=_kantaiKey;
    kantaiData.push_back(kantai);
    
    int size=static_cast<int>(_equipKey.size());
    for (int i=0;i<size;++i)
    {
        Equip* equip=Equip::create(_equipKey[i].first, _equipKey[i].second);
        equip->setKantai(kantai);
        kantai->equipGrid[i]=equip;
        equipData.push_back(equip);
    }
    return kantai;
}

void Player::deleteKantai(Kantai *kantai)
{
    if (kantai->getFleet())
    {
        Fleet* fleet=dynamic_cast<Fleet*>(kantai->getFleet());
        
        for (int i=0; i<6; ++i)
        {
            if (fleet->ship[i]) {
                if (fleet->ship[i]==kantai)
                {
                    fleet->ship[i]=NULL;
                    KantaiDB::getInstance()->deleteKantaiFleet(kantai->getKantaiKey());
                }
            }
        }
    }
    auto kantaiIt=kantaiData.begin();
    while (kantaiIt!=kantaiData.end())
    {
        if (*kantaiIt==kantai)
        {
            break;
        }
        ++kantaiIt;
    }
    if (kantaiIt==kantaiData.end())
    {
        CCASSERT(false, "have no kantai in deleteKantai");
    }
    
    for (auto it=kantai->equipGrid.begin(); it!=kantai->equipGrid.end(); ++it)
    {
        Equip* equipTemp=*it;
        if (equipTemp)
        {
            int _equipKey=equipTemp->getEquipKey();
            auto equipIt=find(equipData.begin(),equipData.end(),equipTemp);
            equipData.erase(equipIt);
            delete equipTemp;
            *it=NULL;
            EquipDB::getInstance()->deleteEquipKey(_equipKey, true);
        }
    }
    kantaiData.erase(kantaiIt);
    delete kantai;
    kantai=NULL;
    KantaiDB::getInstance()->deleteKantaiKey(kantai->getKantaiKey(), false);
}

void Player::deleteKantai(int _kantaiKey)
{
    Kantai* kantai=NULL;
    auto kantaiIt=kantaiData.begin();
    while (kantaiIt!=kantaiData.end())
    {
        if ((*kantaiIt)->getKantaiKey()==_kantaiKey)
        {
            kantai=*kantaiIt;
            break;
        }
        ++kantaiIt;
    }
    if (kantaiIt==kantaiData.end())
    {
        CCASSERT(false, "have no kantai in deleteKantai");
    }
    if (kantai->getFleet())
    {
        Fleet* fleet=dynamic_cast<Fleet*>(kantai->getFleet());
        
        for (int i=0; i<6; ++i)
        {
            if (fleet->ship[i]) {
                if (fleet->ship[i]==kantai)
                {
                    fleet->ship[i]=NULL;
                    KantaiDB::getInstance()->deleteKantaiFleet(kantai->getKantaiKey());
                }
            }
        }
    }
    for (auto it=kantai->equipGrid.begin(); it!=kantai->equipGrid.end(); ++it)
    {
        Equip* equipTemp=*it;
        if (equipTemp)
        {
            int _equipKey=equipTemp->getEquipKey();
            auto equipIt=find(equipData.begin(),equipData.end(),equipTemp);
            equipData.erase(equipIt);
            delete equipTemp;
            *it=NULL;
            EquipDB::getInstance()->deleteEquipKey(_equipKey, true);
        }
    }
    kantaiData.erase(kantaiIt);
    delete kantai;
    kantai=NULL;
    KantaiDB::getInstance()->deleteKantaiKey(kantai->getKantaiKey(), false);}

void Player::removeKantai(Fleet *_fleet, int _position)
{
    Kantai* kantaiTemp=_fleet->ship[_position-1];
    _fleet->ship[_position]=NULL;
    
    int _kantaiKey=kantaiTemp->getKantaiKey();
    KantaiDB::getInstance()->deleteKantaiFleet(_kantaiKey);
}


void Player::changeKantaiPosition(Kantai *kantai, Fleet *fleet, int position)
{
    auto _fleet=dynamic_cast<Fleet*>(kantai->getFleet());
    if (_fleet)
    {
        int prePosition=-1;
        for (int i=0; i<6; ++i)
        {
            if (_fleet->ship[i])
            {
                if (_fleet->ship[i]==kantai) {
                    prePosition=i+1;
                    break;
                }
            }
        }
        removeKantai(_fleet, prePosition);
    }
    _changeKantaiPosition(kantai,fleet,position);
}

void Player::changeKantaiPosition(int _kantaiKey, int _fleetNumber, int _position)
{
    auto _fleet=findFleetByFleetKey(_fleetNumber);
    auto _kantai=findKantaiByKantaiKey(_kantaiKey);
    changeKantaiPosition(_kantai,_fleet,_position);
}

void Player::_changeKantaiPosition(Kantai *kantai, Fleet *fleet, int position)
{
    fleet->ship[position-1]=kantai;
    kantai->setFleet(fleet);
    KantaiDB::getInstance()->changeKantaiPosition(kantai->getKantaiKey(),fleet->getFleetKey(),position);
}



Fleet* Player::buildNewFleet()
{
    for (int i=0; i<fleetData.size();++i) {
        if (!fleetData[i])
        {
            Fleet* fleet=Fleet::create(i+1, INIT_UNIT);
            fleetData[i]=fleet;
            FleetDB::getInstance()->getNewFleetByNumber(i+1,fleet->getFleetName(),fleet->getFleetState());
        }
    }
}


void Player::deleteFleet(int _fleetKey)
{
    Fleet* _fleet=fleetData[_fleetKey-1];
    
    for (auto it=_fleet->ship.begin(); it!=_fleet->ship.end(); ++it)
    {
        if (*it)
        {
            int _kantaiKey=(*it)->getKantaiKey();
            KantaiDB::getInstance()->deleteKantaiFleet(_kantaiKey);
        }
    }
    fleetData[_fleetKey-1]=NULL;
    delete _fleet;
    FleetDB::getInstance()->deleteFleetByKey(_fleetKey);
    
}

Fleet* Player::findFleetByFleetKey(int _fleetKey)
{
//    for (int i=0; i<fleetData.size(); ++i)
//    {
//        if (fleetData[i]->getFleetKey()==_fleetKey) {
//            return fleetData[i];
//        }
//    }
    return fleetData[_fleetKey-1];
    CCASSERT(false, "can not find the fleet");
}











