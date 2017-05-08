//
//  BattleCharacterInfo.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#include "BattleCharacterInfo.hpp"
#include "KantaiMgr.hpp"

NS_KCL_BEGIN

BattleCharacterInfo* BattleCharacterInfo::create(kancolle::Kantai *kantai)
{
    BattleCharacterInfo* pRet=new BattleCharacterInfo;
    if (pRet&&pRet->init(kantai))
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

BattleCharacterInfo* BattleCharacterInfo::create(int kantaiNumber)
{
    BattleCharacterInfo* pRet=new BattleCharacterInfo;
    if (pRet&&pRet->init(kantaiNumber))
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}


bool BattleCharacterInfo::init(kancolle::Kantai *kantai)
{
    bool bRet=false;
    do
    {
        m_Kantai=kantai;
        kantaiNumber=m_Kantai->getKantaiNumber();
        m_bIsEnemy=false;
        m_KantaiImp=sKantaiMgr.GetKantaiMap(kantaiNumber);
        
        currLV=kantai->getCurrLV();
        currFuel=kantai->getCurrFuel();
        currAmmo=kantai->getCurrAmmo();
        currHp=kantai->getCurrHp();
        searchEnemy=kantai->getSearchEnemy();
        armor=kantai->getArmor();
        luck=kantai->getLuck();
        AntiSubMarine=kantai->getAntiSubMarine();
        dodge=kantai->getDodge();
        torpedo=kantai->getTorpedo();
        firePower=kantai->getFirePower();
        antiAir=kantai->getAntiAir();
        fatigueValue=kantai->getFatigueValue();
        kantaiLock=kantai->getKantaiLock();
        kantaiStar=kantai->getKantaiStar();
        setBrokenType();
        
        m_vEquipInfo.resize(kantai->getKantaiEquipSize());
        for (int i=1; i<=m_vEquipInfo.size(); ++i)
        {
            m_vEquipInfo[i]=NULL;
            if (kantai->getEquip(i))
            {
                m_vEquipInfo[i]=BattleEquipInfo::create(kantai->getEquip(i)->getEquipNumber());
            }
        }
        m_vCurrPlaneLoad=kantai->currPlaneLoad;
        
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}


bool BattleCharacterInfo::init(int kantaiNumber)
{
    bool bRet=false;
    do
    {
        m_Kantai=NULL;
        kantaiNumber=kantaiNumber;
        m_bIsEnemy=true;
        m_KantaiImp=sKantaiMgr.GetKantaiMap(kantaiNumber);
        
        currLV=1;
        currFuel=sKantaiMgr.GetKantaiMap(kantaiNumber)->fuel;
        currAmmo=sKantaiMgr.GetKantaiMap(kantaiNumber)->ammo;
        currHp=sKantaiMgr.GetKantaiMap(kantaiNumber)->maxHp;
        searchEnemy=sKantaiMgr.GetKantaiMap(kantaiNumber)->initSearchEnemy;
        armor=sKantaiMgr.GetKantaiMap(kantaiNumber)->initArmor;
        luck=sKantaiMgr.GetKantaiMap(kantaiNumber)->initLuck;
        AntiSubMarine=sKantaiMgr.GetKantaiMap(kantaiNumber)->initAntiSubmarine;
        dodge=sKantaiMgr.GetKantaiMap(kantaiNumber)->initDodge;
        torpedo=sKantaiMgr.GetKantaiMap(kantaiNumber)->initTorpedo;
        firePower=sKantaiMgr.GetKantaiMap(kantaiNumber)->initFirePower;
        antiAir=sKantaiMgr.GetKantaiMap(kantaiNumber)->initAntiAir;
        //TODO
        fatigueValue=1;
        kantaiLock=false;
        //TODO
        kantaiStar=1;
        setBrokenType();
        
        m_vEquipInfo.resize(sKantaiMgr.GetKantaiMap(kantaiNumber)->kantaiEquipSize);
        m_vCurrPlaneLoad.resize(sKantaiMgr.GetKantaiMap(kantaiNumber)->kantaiEquipSize);
        for (int i=0; i<m_vEquipInfo.size(); ++i)
        {
            m_vEquipInfo[i]=NULL;
            if (sKantaiMgr.GetKantaiMap(kantaiNumber)->kantaiEquipInit)
            {
                m_vEquipInfo[i]=BattleEquipInfo::create(sKantaiMgr.GetKantaiMap(kantaiNumber)->kantaiEquipInit[i]);
            }
        }
        for (int i=0; i<m_vEquipInfo.size(); ++i)
        {
            m_vCurrPlaneLoad[i]=sKantaiMgr.GetKantaiMap(kantaiNumber)->planeLoad[i];
        }
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}


void BattleCharacterInfo::setBrokenType()
{
    
}


BattleCharacterInfo::~BattleCharacterInfo()
{
    for (int i=0; i<m_vEquipInfo.size(); ++i)
    {
        if (m_vEquipInfo[i])
        {
            delete m_vEquipInfo[i];
        }
    }
    release();
}



BattleEquipInfo*  BattleCharacterInfo::GetMainCannon()
{
    for (int i = 1; i <=MAX_EQUIPMENT_NUMBER; i++)
    {
        BattleEquipInfo* equipInfo=GetEquipInfo(i);
        if (equipInfo)
        {
            if (equipInfo->getEquipType()==EquipType::Small_Caliber||
                equipInfo->getEquipType()==EquipType::Medium_Caliber||
                equipInfo->getEquipType()==EquipType::Large_Caliber)
                return equipInfo;
        }
    }
    return NULL;
}

bool BattleCharacterInfo::CanAirBattle()
{
    if (getKantaiType()!=KantaiType::Seaplane_Carrier&&
        getKantaiType()!=KantaiType::Armor_Carrier&&
        getKantaiType()!=KantaiType::Light_Carrier&&
        getKantaiType()!=KantaiType::Battle_Carrier&&
        getKantaiType()!=KantaiType::Diving_Carrier)
        return false;
    for (int i = 1; i <=MAX_EQUIPMENT_NUMBER; i++)
    {
        BattleEquipInfo* equipInfo=GetEquipInfo(i);
        if (equipInfo)
        {
            if (equipInfo->getEquipType()==EquipType::Fighter||
                equipInfo->getEquipType()==EquipType::Bomber||
                equipInfo->getEquipType()==EquipType::Attacker||
                equipInfo->getEquipType()==EquipType::Mari_Bomber)
                return true;
        }
    }
    return false;
}

int BattleCharacterInfo::getTorpedo() const
{
    int totalTorpedo=0;
    for (int i=0; i<m_vEquipInfo.size(); ++i)
    {
        if (m_vEquipInfo[i])
        {
            totalTorpedo=m_vEquipInfo[i]->getAviTorpedo();
        }
    }
    return totalTorpedo+torpedo;
}

int BattleCharacterInfo::getBomb() const
{
    int totalBomb=0;
    for (int i=0; i<m_vEquipInfo.size(); ++i)
    {
        if (m_vEquipInfo[i])
        {
            totalBomb=m_vEquipInfo[i]->getAviBomb();
        }
    }
    return totalBomb;
}


int BattleCharacterInfo::getHitRate() const
{
    int totalHitRate=0;
    for (int i=0; i<m_vEquipInfo.size(); ++i)
    {
        if (m_vEquipInfo[i])
        {
            totalHitRate=m_vEquipInfo[i]->getHitRate();
        }
    }
    return totalHitRate;
}


bool BattleCharacterInfo::GetAirCraftId(std::string &plane1, std::string &plane2, std::string plane3)
{
    return false;
}

void BattleCharacterInfo::GetDamage(int damage)
{
    if (damage > 0)
    {
        setCurrHp(getCurrHp()-damage);
        float persentage = (float)getCurrHp()/(float)getMaxHp();
        if (persentage>0.75)
        {
            brokenType = BrokenType::normal;
        }
        else if (persentage>0.50) //–°∆∆
        {
            brokenType = BrokenType::tiny;
        }
        else if (persentage>0.25)//÷–∆∆
        {
            brokenType = BrokenType::mid;
        }
        else if (persentage>0)//¥Û∆∆
        {
            brokenType = BrokenType::large;
        }
        else
        {
            brokenType = BrokenType::drown;
        }
    }
}
bool BattleCharacterInfo::CanAttack()
{
    if (getKantaiType()==KantaiType::Light_Carrier||
        getKantaiType()==KantaiType::Armor_Carrier||
        getKantaiType()==KantaiType::Carrier)
    {
        float persentage = getCurrHp() / getMaxHp();
        if (persentage <= 0.5)
            return false;
    }
    
    if (getCurrHp() == 0)
        return false;
    
    return true;
}
//void CharacterInfo::addEquipment(Equipment* equipment,int index)
//{
//    if (equipment != nullptr)
//    {
//        this->firePower += equipment->firePower;
//        this->torpedo += equipment->torpedo;
//        this->bomb += equipment->bomb;
//        this->antiaircraft += equipment->antiaircraft;
//        this->antisubmarine += equipment->antisubmarine;
//        this->scout += equipment->scout;
//        this->hitRate += equipment->hitRate;
//        this->agility += equipment->agility;
//        
//        equipments[index] = equipment;
//    }
//    
//}


NS_KCL_END


