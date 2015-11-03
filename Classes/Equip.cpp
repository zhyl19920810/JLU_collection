//
//  Equip.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//








#include "Equip.h"
#include <algorithm>
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
//
//Equip::Equip(int _equipNumber)
//{
//    
//    XMLControl* xmlCont=new XMLBaseControl;
//    ValueVector _equipData=xmlCont->ReadEquipXml(_equipNumber);
//    
//    ///添加进数据库，返回一个int值，为数据库的主键
//    equipKey=1;
//    
//    ValueMap equipBaseAtrr=_equipData[0].asValueMap();
//    
//    equipNumber=equipBaseAtrr["equipNumber"].asInt();
//    equipName=equipBaseAtrr["equipName"].asString();
//    equipScope=equipBaseAtrr["equipScope"].asInt();
//    equipType=equipBaseAtrr["equipType"].asInt();
//    isPlane=equipBaseAtrr["isPlane"].asBool();
//    
//    equipAdvanceAtrr=_equipData[1].asValueMap();
//    
//    supKantaiType=_equipData[2].asValueVector();
//    
//    delete xmlCont;
//    
//}
//
//int Equip::GetEquipKey() const
//{
//    return equipKey;
//}
//
//int Equip::GetEquipNumber() const
//{
//    return equipNumber;
//}
//
//int Equip::GetEquipScope() const
//{
//    return equipScope;
//}
//
//std::string Equip::GetEquipName() const
//{
//    return equipName;
//}
//
//int Equip::GetEquipType() const
//{
//    return equipType;
//}
//
//bool Equip::GetIsPlane() const
//{
//    return isPlane;
//}
//
//
//ValueMap Equip::GetEquipAdvanceAtrr() const
//{
//    return equipAdvanceAtrr;
//}
//
//ValueVector Equip::GetSupKantaiType() const
//{
//    return supKantaiType;
//}
//

std::map<int,EquipDec*> EquipDecData::impData=std::map<int,EquipDec*>();

void EquipPrint::PrintEquipInfo(const Equip &_equip)
{
    log("===>equipKey:   %d",_equip.getequipKey());
    log("===>equipNumber:  %d",_equip.getequipNumber());
    log("===>equipName:  %s",_equip.getequipName().c_str());
    log("===>equipScope: %s",NameResolution::EquipScopeReso(_equip.getequipScope()).c_str());
    log("===>equipScope:  %s",NameResolution::EquipTypeReso(_equip.getequipScope()).c_str());
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
//
//    ValueVector _supKantaiType=_equip.GetSupKantaiType();
//    log("===>supKantaiType");
//    for (auto it=_supKantaiType.begin(); it!=_supKantaiType.end(); ++it)
//    {
//        log("support the kantai type: %d",it->asInt());
//    }
//    
    
    
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
}



////////////////equip implement///////////////////

void EquipImp::_equipImp(ValueVector &_equipData)
{

    ValueMap equipBaseAtrr=_equipData[0].asValueMap();
    
    equipNumber=equipBaseAtrr["equipNumber"].asInt();
    equipName=equipBaseAtrr["equipName"].asString();
    equipScope=equipBaseAtrr["equipScope"].asInt();
    equipType=equipBaseAtrr["equipType"].asInt();
    isPlane=equipBaseAtrr["isPlane"].asBool();
    
    
    
    ValueMap equipAdvanceAtrr=_equipData[1].asValueMap();
    
    firePower=equipAdvanceAtrr["firePower"].asInt();
    AviTorpedo=equipAdvanceAtrr["AviTorpedo"].asInt();
    AviBomb=equipAdvanceAtrr["AviBomb"].asInt();
    antiAir=equipAdvanceAtrr["antiAir"].asInt();
    antiSubmarine=equipAdvanceAtrr["antiSubmarine"].asInt();
    searchEnemy=equipAdvanceAtrr["searchEnemy"].asInt();
    hitRate=equipAdvanceAtrr["hitRate"].asInt();
    dodge=equipAdvanceAtrr["dodge"].asInt();
    range=equipAdvanceAtrr["range"].asInt();
    armor=equipAdvanceAtrr["armor"].asInt();


    supKantaiType=_equipData[2].asValueVector();
}



EquipImp::EquipImp(ValueVector& equip)
{
    _equipImp(equip);
}


EquipImp::EquipImp(int _equipNumber)
{
    XMLControl* xmlCont=new XMLBaseControl;
    ValueVector _equipData=xmlCont->ReadEquipXml(_equipNumber);
    
    _equipImp(_equipData);
    
    delete xmlCont;
}

ValueVector EquipImp::getSupKantaiType()
{
    return supKantaiType;
}


Equip::Equip(int _equipKey,int _equipNumber)
{

    equipKey=_equipKey;
    
    equipNumber=_equipNumber;
    
    equipImp=EquipDecData::insertEquip(_equipNumber);
}

EquipDec::~EquipDec()
{
    delete equipImp;
}


EquipImp* EquipDecData::insertEquip(ValueVector& _equipData)
{
    EquipDec* temp;
    ValueMap equipBaseAtrr=_equipData[0].asValueMap();
    int equipNumber=equipBaseAtrr["equipNumber"].asInt();
    
    auto it=EquipDecData::impData.find(equipNumber);
    if (it!=EquipDecData::impData.end())
    {
        (*it).second->addCount();
        temp=it->second;
    }
    else
    {
        temp=new EquipDec(_equipData);
        impData.insert(std::pair<int,EquipDec*>(equipNumber,temp));
    }
    return temp->getEquipImp();
}

EquipImp* EquipDecData::insertEquip(int equipNumber)
{
    EquipDec* temp;
    auto it=EquipDecData::impData.find(equipNumber);
    if (it!=EquipDecData::impData.end())
    {
        (*it).second->addCount();
        temp=it->second;
    }
    else
    {
        ///这里还得改
        XMLControl* xmlControl=new XMLBaseControl;
        auto equipData=xmlControl->ReadEquipXml(equipNumber);
        temp=new EquipDec(equipData);
        EquipDecData::impData.insert(std::pair<int,EquipDec*>(equipNumber,temp));
        delete xmlControl;
    }
    return temp->getEquipImp();
}



void EquipDecData::deleteEquip(int equipNumber)
{
    auto it=EquipDecData::impData.find(equipNumber);
    if (it!=EquipDecData::impData.end())
    {
        auto temp=it->second;
        temp->minusCount();
        if (temp->getCount()==0)
        {
            EquipDecData::impData.erase(it);
            delete temp;
        }
    }
    else
    {
        
    }
}



