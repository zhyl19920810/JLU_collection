//
//  Equip.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//








#include "Equip.h"
//--------------------------------------------------------------------
//
// Equip
//
//--------------------------------------------------------------------


Equip::Equip():
equipImp(NULL),
parent(NULL)
{
    
}

Equip::~Equip()
{
    equipImp=NULL;
    parent=NULL;
}

Equip* Equip::create()
{
    Equip* equip=new Equip;
    if (!equip)
    {
        CCASSERT(false, "can not init the equip");
    }
    return equip;
}


Equip* Equip::create(int _equipKey, int _equipNumber, cocos2d::Ref* _parent)
{
    Equip* equip=new Equip;
    
    if (equip)
    {
        equip->init(_equipKey, _equipNumber,_parent);
    }
    else
    {
        CCASSERT(false, "can not init the equip");
    }
    return equip;
}


void Equip::init(int _equipKey, int _equipNumber, cocos2d::Ref* _parent)
{
    equipKey=_equipKey;
    equipNumber=_equipNumber;
    parent=_parent;
    equipImp=EquipMgr::getInstance().GetEquipMap(_equipNumber);
}

void Equip::setKantai(Ref* _parent)
{
    this->parent=_parent;
}



bool Equip::isSupKantaiType(KantaiType type)
{
    for (int i=0; i<MAX_SUPSHIP; ++i)
    {
        int kantaiType=equipImp->supKantaiType[i];
        if (!kantaiType) {
            return false;
        }
        if (type==kantaiType) {
            return true;
        }
    }
    return false;
}


//
//
////--------------------------------------------------------------------
////
//// Equip
////
////--------------------------------------------------------------------
//
//
//
//
//Equip* Equip::create()
//{
//    Equip* equip=new Equip;
//    if (!equip)
//    {
//        CCASSERT(false, "can not init the equip");
//    }
//    return equip;
//}
//
//
//Equip* Equip::create(int _equipKey, int _equipNumber, cocos2d::Ref* _parent)
//{
//    Equip* equip=new Equip;
//    
//    if (equip)
//    {
//        equip->init(_equipKey, _equipNumber,_parent);
//    }
//    else
//    {
//        CCASSERT(false, "can not init the equip");
//    }
//    return equip;
//}
//
//
//Equip::Equip()
//{
//    equipImp=NULL;
//    
//    parent=NULL;
//}
//
//
//void Equip::init(int _equipKey, int _equipNumber, cocos2d::Ref* _parent)
//{
//    equipKey=_equipKey;
//    
//    equipNumber=_equipNumber;
//    
//    parent=_parent;
//    
//    equipImp=EquipPoolManager::getInstance()->insertEquip(_equipNumber);
//}
//
//void Equip::setKantai(Ref* _parent)
//{
//    this->parent=_parent;
//}
//
//Ref* Equip::getKantai() const
//{
//    return parent;
//}
//
//
//Equip::~Equip()
//{
//    EquipPoolManager::getInstance()->deleteEquip(equipNumber);
//}
//
//std::set<KantaiType>& Equip::getSupKantaiType() const
//{
//    return equipImp->getSupKantaiType();
//}
//
//
//
////--------------------------------------------------------------------
////
//// EquipPoolManager
////
////--------------------------------------------------------------------
//
//EquipPoolManager* EquipPoolManager::equipDecData=NULL;
//
//EquipPoolManager* EquipPoolManager::getInstance()
//{
//    if (equipDecData==NULL)
//    {
//        equipDecData=new (std::nothrow) EquipPoolManager();
//    }
//    return equipDecData;
//}
//
//
//void EquipPoolManager::deleteEquip(int equipNumber)
//{
//    auto it=impData.find(equipNumber);
//    if (it!=impData.end())
//    {
//        auto temp=it->second;
//        --temp->count;
//        if (temp->count==0)
//        {
//            impData.erase(it);
//            delete temp;
//        }
//    }
//    else
//    {
//        log("there is not the equip in the data");
//    }
//}
//
//EquipImp* EquipPoolManager::insertEquip(int equipNumber)
//{
//    EquipDec* temp;
//    auto it=impData.find(equipNumber);
//    if (it!=impData.end())
//    {
//        temp=it->second;
//        ++temp->count;
//    }
//    else
//    {
//        auto equipImp=XMLParser::getInstance()->readEquipXml(equipNumber);
//        temp=new EquipDec(equipImp);
//        impData.insert(std::pair<int,EquipDec*>(equipNumber,temp));
//    }
//    return temp->getEquipImp();
//}
//
//
//void EquipPoolManager::clear()
//{
//    for (auto it=impData.begin(); it!=impData.end(); ++it)
//    {
//        (*it).second->clear();
//    }
//}
//
//void EquipPoolManager::print()
//{
//    for (auto it=impData.begin(); it!=impData.end(); ++it)
//    {
//        log("the number:%4d",it->first);
//        
//        auto equipDec=it->second;
//        log("the quote sum:%4d",equipDec->count);
//        
//        auto _equip=equipDec->equipImp;
//        log("===>equipNumber:  %d",_equip->getequipNumber());
//        log("===>equipName:  %s",_equip->getequipName().c_str());
//        log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip->getequipScope()).c_str());
//        log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip->getequipType()).c_str());
//        log("===>isPlane: %s",_equip->getisPlane()?"true":"false");
//        
//        log("===>equipAdvanceAtrr");
//        log("=====>firePower :%d ",_equip->getfirePower());
//        log("=====>AviTorpedo :%d ",_equip->getAviTorpedo());
//        log("=====>AviBomb :%d ",_equip->getAviBomb());
//        log("=====>antiAir :%d ",_equip->getantiAir());
//        log("=====>antiSubmarine :%d ",_equip->getantiSubmarine());
//        log("=====>searchEnemy :%d ",_equip->getsearchEnemy());
//        log("=====>hitRate :%d ",_equip->gethitRate());
//        log("=====>dodge :%d ",_equip->getdodge());
//        log("=====>range :%d ",_equip->getrange());
//        log("=====>armor :%d ",_equip->getarmor());
//        
//        for (auto it=_equip->getSupKantaiType().begin(); it!=_equip->getSupKantaiType().end(); ++it)
//        {
//            log("=====>supKantaiType :%s ",NameResolution::KantaiTypeReso(*it).c_str());
//        }
//    }
//}
//
//
//
////--------------------------------------------------------------------
////
//// EquipDec
////
////--------------------------------------------------------------------
//
//
//
//
//void EquipDec::clear()
//{
//    delete equipImp;
//}
//
//EquipDec::EquipDec(EquipImp* _equipimp):equipImp(_equipimp),count(1)
//{
//    
//}
//
//
//
//
////--------------------------------------------------------------------
////
//// EquipImp
////
////--------------------------------------------------------------------
//
//
//
//
//EquipImp* EquipImp::create(int _equipNumber)
//{
//    EquipImp* equipImp;
//    equipImp=XMLParser::getInstance()->readEquipXml(_equipNumber);
//    
//    return equipImp;
//}
//
//
//EquipImp::EquipImp()
//{
//    supKantaiType=std::set<KantaiType>();
//}
//
//
//std::set<KantaiType>& EquipImp::getSupKantaiType()
//{
//    return supKantaiType;
//}
//
//
//EquipImp::~EquipImp()
//{
//    
//}
//
//
//
//void EquipPrint::PrintEquipInfo(const Equip &_equip)
//{
//    log("===>equipKey:   %d",_equip.getequipKey());
//    log("===>equipNumber:  %d",_equip.getequipNumber());
//    log("===>equipName:  %s",_equip.getequipName().c_str());
//    log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip.getequipScope()).c_str());
//    log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip.getequipType()).c_str());
//    log("===>isPlane: %s",_equip.getisPlane()?"true":"false");
//    
//    log("===>equipAdvanceAtrr");
//    log("=====>firePower :%d ",_equip.getfirePower());
//    log("=====>AviTorpedo :%d ",_equip.getAviTorpedo());
//    log("=====>AviBomb :%d ",_equip.getAviBomb());
//    log("=====>antiAir :%d ",_equip.getantiAir());
//    log("=====>antiSubmarine :%d ",_equip.getantiSubmarine());
//    log("=====>searchEnemy :%d ",_equip.getsearchEnemy());
//    log("=====>hitRate :%d ",_equip.gethitRate());
//    log("=====>dodge :%d ",_equip.getdodge());
//    log("=====>range :%d ",_equip.getrange());
//    log("=====>armor :%d ",_equip.getarmor());
//
//    for (auto it=_equip.getSupKantaiType().begin(); it!=_equip.getSupKantaiType().end(); ++it)
//    {
//        log("=====>supKantaiType :%s ",NameResolution::KantaiTypeReso(*it).c_str());
//    }
//    
//    
//    
//}
//
//void EquipPrint::PrintEquipInfo(Equip *_equip)
//{
//    log("===>equipKey:   %d",_equip->getequipKey());
//    log("===>equipNumber:  %d",_equip->getequipNumber());
//    log("===>equipName:  %s",_equip->getequipName().c_str());
//    log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip->getequipScope()).c_str());
//    log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip->getequipType()).c_str());
//    log("===>isPlane: %s",_equip->getisPlane()?"true":"false");
//    
//    log("===>equipAdvanceAtrr");
//    log("=====>firePower :%d ",_equip->getfirePower());
//    log("=====>AviTorpedo :%d ",_equip->getAviTorpedo());
//    log("=====>AviBomb :%d ",_equip->getAviBomb());
//    log("=====>antiAir :%d ",_equip->getantiAir());
//    log("=====>antiSubmarine :%d ",_equip->getantiSubmarine());
//    log("=====>searchEnemy :%d ",_equip->getsearchEnemy());
//    log("=====>hitRate :%d ",_equip->gethitRate());
//    log("=====>dodge :%d ",_equip->getdodge());
//    log("=====>range :%d ",_equip->getrange());
//    log("=====>armor :%d ",_equip->getarmor());
//    
//    for (auto it=_equip->getSupKantaiType().begin(); it!=_equip->getSupKantaiType().end(); ++it)
//    {
//        log("=====>supKantaiType :%s ",NameResolution::KantaiTypeReso(*it).c_str());
//    }
//    
//}
//
//
//


