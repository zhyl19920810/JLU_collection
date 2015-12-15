//
//  Equip.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//








#include "Equip.h"
#include "XMLParser.h"
#include <algorithm>


//--------------------------------------------------------------------
//
// Equip
//
//--------------------------------------------------------------------




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


Equip::Equip()
{
    equipImp=NULL;
    
    parent=NULL;
}


void Equip::init(int _equipKey, int _equipNumber, cocos2d::Ref* _parent)
{
    equipKey=_equipKey;
    
    equipNumber=_equipNumber;
    
    parent=_parent;
    
    equipImp=EquipPoolManager::getInstance()->insertEquip(_equipNumber);
}

void Equip::setKantai(Ref* _parent)
{
    this->parent=_parent;
}

Ref* Equip::getKantai() const
{
    return parent;
}


Equip::~Equip()
{
    EquipPoolManager::getInstance()->deleteEquip(equipNumber);
}

std::set<KantaiType>& Equip::getSupKantaiType() const
{
    return equipImp->getSupKantaiType();
}



//--------------------------------------------------------------------
//
// EquipPoolManager
//
//--------------------------------------------------------------------

EquipPoolManager* EquipPoolManager::equipDecData=NULL;

EquipPoolManager* EquipPoolManager::getInstance()
{
    if (equipDecData==NULL)
    {
        equipDecData=new (std::nothrow) EquipPoolManager();
    }
    return equipDecData;
}


void EquipPoolManager::deleteEquip(int equipNumber)
{
    auto it=impData.find(equipNumber);
    if (it!=impData.end())
    {
        auto temp=it->second;
        --temp->count;
        if (temp->count==0)
        {
            impData.erase(it);
            delete temp;
        }
    }
    else
    {
        log("there is not the equip in the data");
    }
}

EquipImp* EquipPoolManager::insertEquip(int equipNumber)
{
    EquipDec* temp;
    auto it=impData.find(equipNumber);
    if (it!=impData.end())
    {
        temp=it->second;
        ++temp->count;
    }
    else
    {
        auto equipImp=XMLParser::getInstance()->readEquipXml(equipNumber);
        temp=new EquipDec(equipImp);
        impData.insert(std::pair<int,EquipDec*>(equipNumber,temp));
    }
    return temp->getEquipImp();
}


void EquipPoolManager::clear()
{
    for (auto it=impData.begin(); it!=impData.end(); ++it)
    {
        (*it).second->clear();
    }
}

void EquipPoolManager::print()
{
    for (auto it=impData.begin(); it!=impData.end(); ++it)
    {
        log("the number:%4d",it->first);
        
        auto equipDec=it->second;
        log("the quote sum:%4d",equipDec->count);
        
        auto _equip=equipDec->equipImp;
        log("===>equipNumber:  %d",_equip->getequipNumber());
        log("===>equipName:  %s",_equip->getequipName().c_str());
        log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip->getequipScope()).c_str());
        log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip->getequipType()).c_str());
        log("===>isPlane: %s",_equip->getisPlane()?"true":"false");
        
        log("===>equipAdvanceAtrr");
        log("=====>firePower :%d ",_equip->getfirePower());
        log("=====>AviTorpedo :%d ",_equip->getAviTorpedo());
        log("=====>AviBomb :%d ",_equip->getAviBomb());
        log("=====>antiAir :%d ",_equip->getantiAir());
        log("=====>antiSubmarine :%d ",_equip->getantiSubmarine());
        log("=====>searchEnemy :%d ",_equip->getsearchEnemy());
        log("=====>hitRate :%d ",_equip->gethitRate());
        log("=====>dodge :%d ",_equip->getdodge());
        log("=====>range :%d ",_equip->getrange());
        log("=====>armor :%d ",_equip->getarmor());
        
        for (auto it=_equip->getSupKantaiType().begin(); it!=_equip->getSupKantaiType().end(); ++it)
        {
            log("=====>supKantaiType :%s ",NameResolution::KantaiTypeReso(*it).c_str());
        }
    }
}



//--------------------------------------------------------------------
//
// EquipDec
//
//--------------------------------------------------------------------




void EquipDec::clear()
{
    delete equipImp;
}

EquipDec::EquipDec(EquipImp* _equipimp):equipImp(_equipimp),count(1)
{
    
}




//--------------------------------------------------------------------
//
// EquipImp
//
//--------------------------------------------------------------------




EquipImp* EquipImp::create(int _equipNumber)
{
    EquipImp* equipImp;
    equipImp=XMLParser::getInstance()->readEquipXml(_equipNumber);
    
    return equipImp;
}


EquipImp::EquipImp()
{
    supKantaiType=std::set<KantaiType>();
}


std::set<KantaiType>& EquipImp::getSupKantaiType()
{
    return supKantaiType;
}


EquipImp::~EquipImp()
{
    
}







/////存储equip本体的xml构造方法vol.1/////

//valueVector equipData
//===>valueMap equipBaseAtrr
//装备的基本属性
//=====>std::pair<std::string ,Value(int)> equipNumber    装备编号
//=====>std::pair<std::string ,Value(std::string)> equipName   装备名称
//=====>std::pair<std::string ,Value(int)> equipScope   装备分类
//=====>std::pair<std::string ,Value(int)> equipType  装备种类
//=====>std::pair<std::string ,Value(bool)> isPlane  是否是飞机

//===>valueMap equipAdvanceAtrr
//装备能提高舰娘的某项属性，提高的属性的名字和具体数值存在于该valueMap中
//有可能某项数据不存在，存在的话，添加，不存在的话不添加
//=====>std::pair<std::string ,Value(int)> firePower
//=====>std::pair<std::string ,Value(int)> AviTorpedo
//=====>std::pair<std::string ,Value(int)> AviBomb
//=====>std::pair<std::string ,Value(int)> antiAir
//=====>std::pair<std::string ,Value(int)> antiSubmarine
//=====>std::pair<std::string ,Value(int)> searchEnemy
//=====>std::pair<std::string ,Value(int)> hitRate
//=====>std::pair<std::string ,Value(int)> dodge
//=====>std::pair<std::string ,Value(int)> range
//=====>std::pair<std::string ,Value(int)> armor

//===>valueVector<value<KantaiType>> supKantaiType;
//







////////////////equip implement///////////////////
//
//void EquipImp::_equipImp(ValueVector &_equipData)
//{
//
//    ValueMap equipBaseAtrr=_equipData[0].asValueMap();
//    
//    equipNumber=equipBaseAtrr["equipNumber"].asInt();
//    equipName=equipBaseAtrr["equipName"].asString();
//    equipScope=equipBaseAtrr["equipScope"].asInt();
//    equipType=equipBaseAtrr["equipType"].asInt();
//    isPlane=equipBaseAtrr["isPlane"].asBool();
//    
//    
//    
//    ValueMap equipAdvanceAtrr=_equipData[1].asValueMap();
//    
//    firePower=equipAdvanceAtrr["firePower"].asInt();
//    AviTorpedo=equipAdvanceAtrr["AviTorpedo"].asInt();
//    AviBomb=equipAdvanceAtrr["AviBomb"].asInt();
//    antiAir=equipAdvanceAtrr["antiAir"].asInt();
//    antiSubmarine=equipAdvanceAtrr["antiSubmarine"].asInt();
//    searchEnemy=equipAdvanceAtrr["searchEnemy"].asInt();
//    hitRate=equipAdvanceAtrr["hitRate"].asInt();
//    dodge=equipAdvanceAtrr["dodge"].asInt();
//    range=equipAdvanceAtrr["range"].asInt();
//    armor=equipAdvanceAtrr["armor"].asInt();
//
//    
//    ValueVector typeTemp=_equipData[2].asValueVector();
//    
//    for (auto it=typeTemp.begin(); it!=typeTemp.end(); ++it)
//    {
//        supKantaiType.push_back(static_cast<KantaiType>((*it).asInt()));
//    }
//    
//}


//
//EquipImp::EquipImp(ValueVector& equip)
//{
//    _equipImp(equip);
//}
//
//
//EquipImp::EquipImp(int _equipNumber)
//{
//
//}



//
//
//EquipImp* EquipDecData::insertEquip(int _equipNumber)
//{
//    EquipDec* temp;
//    //ValueMap equipBaseAtrr=_equipData[0].asValueMap();
//    //int equipNumber=equipBaseAtrr["equipNumber"].asInt();
//    
//    auto it=EquipDecData::impData.find(_equipNumber);
//    if (it!=EquipDecData::impData.end())
//    {
//        (*it).second->addCount();
//        temp=it->second;
//    }
//    else
//    {
//        temp=new EquipDec(_equipData);
//        impData.insert(std::pair<int,EquipDec*>(equipNumber,temp));
//    }
//    return temp->getEquipImp();
//}








void EquipPrint::PrintEquipInfo(const Equip &_equip)
{
    log("===>equipKey:   %d",_equip.getequipKey());
    log("===>equipNumber:  %d",_equip.getequipNumber());
    log("===>equipName:  %s",_equip.getequipName().c_str());
    log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip.getequipScope()).c_str());
    log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip.getequipType()).c_str());
    log("===>isPlane: %s",_equip.getisPlane()?"true":"false");
    
    log("===>equipAdvanceAtrr");
    log("=====>firePower :%d ",_equip.getfirePower());
    log("=====>AviTorpedo :%d ",_equip.getAviTorpedo());
    log("=====>AviBomb :%d ",_equip.getAviBomb());
    log("=====>antiAir :%d ",_equip.getantiAir());
    log("=====>antiSubmarine :%d ",_equip.getantiSubmarine());
    log("=====>searchEnemy :%d ",_equip.getsearchEnemy());
    log("=====>hitRate :%d ",_equip.gethitRate());
    log("=====>dodge :%d ",_equip.getdodge());
    log("=====>range :%d ",_equip.getrange());
    log("=====>armor :%d ",_equip.getarmor());

    for (auto it=_equip.getSupKantaiType().begin(); it!=_equip.getSupKantaiType().end(); ++it)
    {
        log("=====>supKantaiType :%s ",NameResolution::KantaiTypeReso(*it).c_str());
    }
    
    
    
}

void EquipPrint::PrintEquipInfo(Equip *_equip)
{
    log("===>equipKey:   %d",_equip->getequipKey());
    log("===>equipNumber:  %d",_equip->getequipNumber());
    log("===>equipName:  %s",_equip->getequipName().c_str());
    log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip->getequipScope()).c_str());
    log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip->getequipType()).c_str());
    log("===>isPlane: %s",_equip->getisPlane()?"true":"false");
    
    log("===>equipAdvanceAtrr");
    log("=====>firePower :%d ",_equip->getfirePower());
    log("=====>AviTorpedo :%d ",_equip->getAviTorpedo());
    log("=====>AviBomb :%d ",_equip->getAviBomb());
    log("=====>antiAir :%d ",_equip->getantiAir());
    log("=====>antiSubmarine :%d ",_equip->getantiSubmarine());
    log("=====>searchEnemy :%d ",_equip->getsearchEnemy());
    log("=====>hitRate :%d ",_equip->gethitRate());
    log("=====>dodge :%d ",_equip->getdodge());
    log("=====>range :%d ",_equip->getrange());
    log("=====>armor :%d ",_equip->getarmor());
    
    for (auto it=_equip->getSupKantaiType().begin(); it!=_equip->getSupKantaiType().end(); ++it)
    {
        log("=====>supKantaiType :%s ",NameResolution::KantaiTypeReso(*it).c_str());
    }
    
}





