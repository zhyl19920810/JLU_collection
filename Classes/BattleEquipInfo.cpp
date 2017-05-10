//
//  BattleEquipInfo.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/6/17.
//
//

#include "BattleEquipInfo.hpp"


NS_KCL_BEGIN




BattleEquipInfo::~BattleEquipInfo()
{
    release();
}

BattleEquipInfo* BattleEquipInfo::create(int equipNumber)
{
    BattleEquipInfo* equip=new BattleEquipInfo;
    if (equip&&equip->init(equipNumber))
    {
        equip->retain();
        return equip;
    }
    delete equip;
    equip=NULL;
    return equip;
}


BattleEquipInfo::BattleEquipInfo()
{
    
}


bool BattleEquipInfo::init(int equipNumber)
{
    equipNumber=equipNumber;
    equipImp=EquipMgr::getInstance().GetEquipMap(equipNumber);
    return true;
}

std::string BattleEquipInfo::getIcon()
{
    
    switch (getEquipType())
    {
        case EquipType::Small_Caliber:
            return "icons/image 3.png";
            break;
        case EquipType::Medium_Caliber:
            return "icons/image 5.png";
            break;
        case EquipType::Large_Caliber:
            return "icons/image 7.png";
            break;
        case EquipType::Vice_Gun:
            return "icons/image 9.png";
            break;
        case EquipType::AntiAir_MachineGun:
            return "icons/image 31.png";
            break;
        case EquipType::Shell:
            return "icons/image 25.png";
            break;
        case EquipType::Torpedo:
            return "icons/image 11.png";
            break;
        case EquipType::Fighter:
            return "icons/image 13.png";
            break;
        case EquipType::Attacker:
            return "icons/image 17.png";
            break;
        case EquipType::Bomber:
            return "icons/image 15.png";
            break;
        case EquipType::Surv_Aircraft:
            return "icons/image 19.png";
            break;
        case EquipType::Mari_Bomber:
            return "icons/image 21.png";
            break;
        case EquipType::Radar:
            return "icons/image 23.png";
            break;
        case EquipType::Sonar:
            return "icons/image 37.png";
            break;
        case EquipType::Deep_Sea_Type:
            return "icons/image 35.png";
            break;
        case EquipType::OthersType:
            return "icons/image 1.png";
            break;
        default:
            return "icons/image 1.png";
            break;
    }
    
}

std::string BattleEquipInfo::getLabel() const
{
    string tempS=std::to_string(getEquipNumber());
    while (tempS.size()!=3)
    {
        tempS="0"+tempS;
    }
    return "Equipment/btxt_flat/"+tempS+".png";
}


//bool Equip::isSupKantaiType(KantaiType type)
//{
//    for (int i=0; i<MAX_SUPSHIP; ++i)
//    {
//        int kantaiType=equipImp->supKantaiType[i];
//        if (!kantaiType) {
//            return false;
//        }
//        if (type==kantaiType) {
//            return true;
//        }
//    }
//    return false;
//}





NS_KCL_END

