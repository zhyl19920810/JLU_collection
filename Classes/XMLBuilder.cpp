////
////  XMLBuilder.cpp
////  kancolle_alpha
////
////  Created by 岩林张 on 7/31/15.
////
////
//
//#include "XMLBuilder.h"
//#include "Equip.h"
//#include "Compass.h"
//
//
//Scene* XMLBuilder::createScene()
//{
//    auto scene=Scene::create();
//    
//    auto layer=XMLBuilder::create();
//    
//    scene->addChild(layer);
//    
//    return scene;
//}
//
//
//bool XMLBuilder::init()
//{
//    
//    if (!Layer::init()) {
//        return false;
//    }
//    
//    XMLBuilder::setButton();
//    
//    
//    return true;
//}
//
//
//
//void XMLBuilder::setButton()
//{
//    
//    Label* label1=Label::createWithTTF("insert database", FONT_ADDRESS, 30);
//    MenuItemLabel* menuItem1=MenuItemLabel::create(label1, CC_CALLBACK_1(XMLBuilder::readXMLCallback, this));
//    
//    
//    Label* label2=Label::createWithTTF("read database", FONT_ADDRESS, 30);
//    MenuItemLabel* menuItem2=MenuItemLabel::create(label2, CC_CALLBACK_1(XMLBuilder::writeXMLCallback, this));
//    
//
//    
//    Menu* mn=Menu::create(menuItem1,menuItem2, NULL);
//    mn->alignItemsVertically();
//    addChild(mn);
//    
//    
//}
//
//void XMLBuilder::readXML(int _kantaiNumber)
//{
//    
//    std::string filePath="kantai/";
//    filePath+=std::to_string(_kantaiNumber)+"/"+std::to_string(_kantaiNumber)+".xml";
//    //std::string filePath="/Volumes/opengl/kancolle_alpha/Resources/21.xml";
//    XMLDocument *pDoc = new XMLDocument();
//    XMLError errorId = pDoc->LoadFile(filePath.c_str());
//    if (errorId != 0) {
//        //xml格式错误
//        return;
//    }
//    XMLElement *plistEle = pDoc->RootElement();
//    //获取第一个节点属性
//    const XMLAttribute *attribute = plistEle->FirstAttribute();
//    //打印节点属性名和值
//    log("attribute<em>name = %s,attribute</em>value = %s", attribute->Name(), attribute->Value());
//    
//    
//    XMLElement *kantaiNumber = plistEle->FirstChildElement("kantaiNumber");
//    if (kantaiNumber)
//    {
//        log("kantaiNumber = %s",kantaiNumber->GetText());
//    }
//    
//    XMLElement *kantaiType=kantaiNumber->NextSiblingElement();
//    if (kantaiType) {
//        log("kantaiType = %s",kantaiType->GetText());
//    }
//    
//    XMLElement *kantaiName=kantaiType->NextSiblingElement();
//    if (kantaiName) {
//        log("kantaiName = %s",kantaiName->GetText());
//    }
//    
//    
//    ///max
//    XMLElement *maxEle=kantaiName->NextSiblingElement();
//    
//    //maxInThePanel
//    XMLElement *maxInThePanel=maxEle->FirstChildElement();
//    
//    const XMLAttribute *maxPower=maxInThePanel->FirstAttribute();
//    log("%s   =   %s",maxPower->Name(),maxPower->Value());
//    
//    const XMLAttribute *maxArmor=maxPower->Next();
//    log("%s   =   %s",maxArmor->Name(),maxArmor->Value());
//    
//    const XMLAttribute *maxTorpedo=maxArmor->Next();
//    log("%s   =   %s",maxTorpedo->Name(),maxTorpedo->Value());
//    
//    const XMLAttribute *maxAntiAir=maxTorpedo->Next();
//    log("%s   =   %s",maxAntiAir->Name(),maxAntiAir->Value());
//    
//    const XMLAttribute *maxDodge=maxAntiAir->Next();
//    log("%s   =   %s",maxDodge->Name(),maxDodge->Value());
//    
//    XMLElement *maxMinorInThePanel=maxInThePanel->NextSiblingElement();
//    
//    const XMLAttribute *maxSearchEnemy=maxMinorInThePanel->FirstAttribute();
//    log("%s   =   %s",maxSearchEnemy->Name(),maxSearchEnemy->Value());
//    
//    const XMLAttribute *maxLuck=maxSearchEnemy->Next();
//    log("%s   =   %s",maxLuck->Name(),maxLuck->Value());
//    
//    const XMLAttribute *maxAntiSubMarine=maxLuck->Next();
//    log("%s   =   %s",maxAntiSubMarine->Name(),maxAntiSubMarine->Value());
//    
//    
//    delete pDoc;
//
//    
//    
//    
//}
//
//ValueVector XMLBuilder::readXML1(int _kantaiNumber)
//{
//    
//    std::string filePath="kantai/";
//    filePath+=std::to_string(_kantaiNumber)+"/"+std::to_string(_kantaiNumber)+".xml";
//    //std::string filePath="/Volumes/opengl/kancolle_alpha/Resources/21.xml";
//    XMLDocument *pDoc = new XMLDocument();
//    XMLError errorId = pDoc->LoadFile(filePath.c_str());
//    if (errorId != 0) {
//        //xml格式错误
//        return ValueVector();
//    }
//    XMLElement *plistEle = pDoc->RootElement();
//    //获取第一个节点属性
//    const XMLAttribute *attribute = plistEle->FirstAttribute();
//    //打印节点属性名和值
//    log("attribute<em>name = %s,attribute</em>value = %s", attribute->Name(), attribute->Value());
//    
//    ValueVector kantaiReturn=ValueVector();
//    ValueMap kantaiData=ValueMap();
//    XMLElement * kantaiNumber = plistEle->FirstChildElement("kantaiNumber");
//    if (kantaiNumber)
//    {
//        kantaiData["kantaiNumber"]=Value(atoi(kantaiNumber->GetText()));
//        log("kantaiNumber = %s",kantaiNumber->GetText());
//    }
//    
//    XMLElement *kantaiType=kantaiNumber->NextSiblingElement();
//    if (kantaiType)
//    {
//        kantaiData["kantaiType"]=Value(atoi(kantaiNumber->GetText()));
//        log("kantaiType = %s",kantaiType->GetText());
//    }
//    
//    XMLElement *kantaiName=kantaiType->NextSiblingElement();
//    if (kantaiName)
//    {
//        kantaiReturn.push_back(Value(kantaiName->GetText()));
//        log("kantaiName = %s",kantaiName->GetText());
//    }
//    
//    ///max
//    XMLElement *maxEle=kantaiName->NextSiblingElement();
//    
//    //maxInThePanel
//    XMLElement *maxInThePanel=maxEle->FirstChildElement();
//    
//    
//    const XMLAttribute *maxPower=maxInThePanel->FirstAttribute();
//    if (maxPower)
//    {
//        kantaiData[maxPower->Name()]=Value(maxPower->Value());
//        log("%s   =   %s",maxPower->Name(),maxPower->Value());
//    }
//    
//    
//    const XMLAttribute *maxArmor=maxPower->Next();
//    if (maxArmor)
//    {
//        kantaiData[maxArmor->Name()]=Value(maxArmor->Value());
//        log("%s   =   %s",maxArmor->Name(),maxArmor->Value());
//    }
//    
//    const XMLAttribute *maxTorpedo=maxArmor->Next();
//    if (maxTorpedo)
//    {
//        kantaiData[maxTorpedo->Name()]=Value(maxTorpedo->Value());
//        log("%s   =   %s",maxTorpedo->Name(),maxTorpedo->Value());
//    }
//    
//    
//    const XMLAttribute *maxAntiAir=maxTorpedo->Next();
//    if (maxAntiAir)
//    {
//        kantaiData[maxTorpedo->Name()]=Value(maxTorpedo->Value());
//        log("%s   =   %s",maxAntiAir->Name(),maxAntiAir->Value());
//    }
//    
//    
//    const XMLAttribute *maxDodge=maxAntiAir->Next();
//    if (maxDodge)
//    {
//        kantaiData[maxDodge->Name()]=Value(maxDodge->Value());
//        log("%s   =   %s",maxDodge->Name(),maxDodge->Value());
//    }
//    
//    
//    
//    XMLElement *maxMinorInThePanel=maxInThePanel->NextSiblingElement();
//    
//    const XMLAttribute *maxSearchEnemy=maxMinorInThePanel->FirstAttribute();
//    if (maxSearchEnemy)
//    {
//        kantaiData[maxSearchEnemy->Name()]=Value(maxSearchEnemy->Value());
//        log("%s   =   %s",maxSearchEnemy->Name(),maxSearchEnemy->Value());
//    }
//    
//    const XMLAttribute *maxLuck=maxSearchEnemy->Next();
//    if (maxLuck)
//    {
//        kantaiData[maxLuck->Name()]=Value(maxLuck->Value());
//        log("%s   =   %s",maxLuck->Name(),maxLuck->Value());
//    }
//    
//    
//    const XMLAttribute *maxAntiSubMarine=maxLuck->Next();
//    if (maxAntiSubMarine)
//    {
//        kantaiData[maxAntiSubMarine->Name()]=Value(maxAntiSubMarine->Value());
//        log("%s   =   %s",maxAntiSubMarine->Name(),maxAntiSubMarine->Value());
//    }
//    
//    
//    kantaiReturn.push_back(Value(kantaiData));
//    
//    delete pDoc;
//    
//    return kantaiReturn;
//    
//    
//}
//
//
//void XMLBuilder::writeXML(int _kantaiNumber)
//{
//    
//    std::string filePath="kantai/";
//    filePath+=std::to_string(_kantaiNumber)+"/"+std::to_string(_kantaiNumber)+".xml";
//    XMLDocument *pDoc=new XMLDocument();
//    
//    XMLDeclaration *pDec=pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
//    pDoc->LinkEndChild(pDec);
//
//
//    //<plist version=?>
//    XMLElement *plistElement=pDoc->NewElement("plist");
//    plistElement->SetAttribute("version", "1.0");
//    pDoc->LinkEndChild(plistElement);
//    
//    //<"the number of the kantai:  i">
//    XMLComment *commentElement=pDoc->NewComment(StringUtils::format("the number of the kantai:  %d",_kantaiNumber).c_str());
//    plistElement->LinkEndChild(commentElement);
//    
//    //kantai number
//    XMLElement *kantaiNumber=pDoc->NewElement("kantaiNumber");
//    kantaiNumber->LinkEndChild(pDoc->NewText(std::to_string(_kantaiNumber).c_str()));
//    plistElement->LinkEndChild(kantaiNumber);
//    
//    //kantai type
//    XMLElement *kantaiType=pDoc->NewElement("kantaiType");
//    kantaiType->LinkEndChild(pDoc->NewText(std::to_string(Battleship).c_str()));
//    plistElement->LinkEndChild(kantaiType);
//    
//    //kantai name
//    XMLElement *kantaiName=pDoc->NewElement("kantaiName");
//    kantaiName->LinkEndChild(pDoc->NewText("kongo"));
//    plistElement->LinkEndChild(kantaiName);
//    
//    //max
//    XMLElement *maxEle=pDoc->NewElement("max");
//    plistElement->LinkEndChild(maxEle);
//    
//    //kantai Max Attribute in the panel
//    XMLElement *maxInThePanel=pDoc->NewElement("maxInThePanel");
//    maxInThePanel->SetAttribute("maxPower", 98);
//    maxInThePanel->SetAttribute("maxArmor", 94);
//    maxInThePanel->SetAttribute("maxTorpedo", 0);
//    maxInThePanel->SetAttribute("maxAntiAir", 84);
//    maxInThePanel->SetAttribute("maxDodge", 72);
//    maxEle->LinkEndChild(maxInThePanel);
//    
//    //kantai Max minor attribute in the panel poi
//    XMLElement *maxMinorInThePanel=pDoc->NewElement("maxMinorInThePanel");
//    maxMinorInThePanel->SetAttribute("maxSearchEnemy", 49);
//    maxMinorInThePanel->SetAttribute("maxLuck", 1);
//    maxMinorInThePanel->SetAttribute("maxAntiSubMarine", 1);
//    maxEle->LinkEndChild(maxMinorInThePanel);
//    
//    //kantai init poi
//    XMLElement* initEle=pDoc->NewElement("init");
//    plistElement->LinkEndChild(initEle);
//    
//    //HP poi
//    XMLElement* HPEle=pDoc->NewElement("HP");
//    HPEle->LinkEndChild(pDoc->NewText(std::to_string(63).c_str()));
//    initEle->LinkEndChild(HPEle);
//    
//    
//    //kantai Init Attribute poi
//    XMLElement *initInThePanel=pDoc->NewElement("initInthePanel");
//    initInThePanel->SetAttribute("initPowerFire", 0);
//    initInThePanel->SetAttribute("initAromor", 0);
//    initInThePanel->SetAttribute("initTorpedo", 0);
//    initInThePanel->SetAttribute("initAntiAir", 0);
//    initInThePanel->SetAttribute("initDodge", 0);
//    initInThePanel->SetAttribute("initSearchEnemy", 0);
//    initInThePanel->SetAttribute("initLuck", 0);
//    initInThePanel->SetAttribute("initAntiSubMarine", 0);
//    initInThePanel->SetAttribute("initSpeed", 0);
//    initInThePanel->SetAttribute("initRange", 0);
//    initEle->LinkEndChild(initInThePanel);
//    
//    //fuel poi
//    XMLElement* fuelEle=pDoc->NewElement("fuel");
//    fuelEle->LinkEndChild(pDoc->NewText(std::to_string(80).c_str()));
//    initEle->LinkEndChild(fuelEle);
//    
//    //ammo poi
//    XMLElement* ammoEle=pDoc->NewElement("ammo");
//    ammoEle->LinkEndChild(pDoc->NewText(std::to_string(80).c_str()));
//    initEle->LinkEndChild(ammoEle);
//    
//    //build time poi
//    //for example 04:30:00 =4*3600+30*60+0
//    XMLElement* buildTime=pDoc->NewElement("buildTime");
//    buildTime->LinkEndChild(pDoc->NewText(std::to_string(4*3600).c_str()));
//    initEle->LinkEndChild(buildTime);
//    
//    XMLElement* equip=pDoc->NewElement("equip");
//    initEle->LinkEndChild(equip);
//    
//    XMLElement* equipSize=pDoc->NewElement("equipSize");
//    equipSize->LinkEndChild(pDoc->NewText(std::to_string(3).c_str()));
//    equip->LinkEndChild(equipSize);
//    
//    
////    XMLElement* equipInit=pDoc->NewElement("equipInit");
////    for (int i=1; i<4; ++i) {
////        equip->SetAttribute(std::to_string(i).c_str(), 3);
////    }
////    equip->LinkEndChild(equipInit);
////    
//    pDoc->SaveFile(filePath.c_str());
//     pDoc->Print();
//    delete pDoc;
//
//    
//}
//
////用于保存舰娘初始的数据
////其中valuevector中第一个元素
////kantaiData[0]存储的为名字(string类型)
////kantaiData[1]为valueMap类型变量，保存着基础信息
////先不考虑装备的问题
//
//
//
//
//
//
//
//ValueVector XMLBuilder::buildTheEquipXML()
//{
//    ValueVector _equipData;
//    ValueMap _equipBaseAtrr;
//    _equipData.reserve(3);
//    
//    //equipBaseAtrr
//    _equipBaseAtrr["equipNumber"]=1;
//    _equipBaseAtrr["equipName"]="12cm单装炮";
//    _equipBaseAtrr["equipScope"]=AttackEquip_Radio;
//    _equipBaseAtrr["equipType"]=Small_Caliber;
//    _equipBaseAtrr["isPlane"]=false;
//    _equipData.push_back(Value(_equipBaseAtrr));
//    
//    //equipAdvanceAtrr
//    ValueMap _equipAdvanceAtrr;
//    _equipAdvanceAtrr["firePower"]=1;
//    _equipAdvanceAtrr["antiAir"]=1;
//    _equipData.push_back(Value(_equipAdvanceAtrr));
//    
//    
//    //supKantaiType
//    ValueVector _supKantaiType;
//    _supKantaiType.reserve(7);
//    _supKantaiType.push_back(Value(Destroyer));
//    _supKantaiType.push_back(Value(Light_Cruiser));
//    _supKantaiType.push_back(Value(Torpedo_Cruiser));
//    _supKantaiType.push_back(Value(Seaplane_Carrier));
//    _supKantaiType.push_back(Value(Landing_craft));
//    _supKantaiType.push_back(Value(Diving_Mothership));
//    _supKantaiType.push_back(Value(Workboat));
//    _equipData.push_back(Value(_supKantaiType));
//    
//    return _equipData;
//    
//}
///////存储equip本体的xml构造方法vol.1/////
//
////valueVector equipData
////===>valueMap equipBaseAtrr
////装备的基本属性
////=====>std::pair<std::string ,Value(int)> equipNumber    装备编号
////=====>std::pair<std::string ,Value(std::string)> equipName   装备名称
////=====>std::pair<std::string ,Value(int)> equipScope   装备分类
////=====>std::pair<std::string ,Value(int)> equipType  装备种类
////=====>std::pair<std::string ,Value(bool)> isPlane  是否是飞机
//
////===>valueMap equipAdvanceAtrr
////装备能提高舰娘的某项属性，提高的属性的名字和具体数值存在于该valueMap中
////有可能某项数据不存在，存在的话，添加，不存在的话不添加
////=====>std::pair<std::string ,Value(int)> firePower
////=====>std::pair<std::string ,Value(int)> AviTorpedo
////=====>std::pair<std::string ,Value(int)> AviBomb
////=====>std::pair<std::string ,Value(int)> antiAir
////=====>std::pair<std::string ,Value(int)> antiSubmarine
////=====>std::pair<std::string ,Value(int)> searchEnemy
////=====>std::pair<std::string ,Value(int)> hitRate
////=====>std::pair<std::string ,Value(int)> dodge
////=====>std::pair<std::string ,Value(int)> range
////=====>std::pair<std::string ,Value(int)> armor
//
////===>valueVector<value<KantaiType>> supKantaiType;
//
//
//
//
//
//void XMLBuilder::writeEquipXml(ValueVector _equipData)
//{
//    
//    ValueMap _equipBaseAtrr=_equipData[0].asValueMap();
//    
//    int _equipNumber=_equipBaseAtrr.at("equipNumber").asInt();
//    std::string _equipName=_equipBaseAtrr.at("equipName").asString();
//    int _equipScope=_equipBaseAtrr.at("equipScope").asInt();
//    int _equipType=_equipBaseAtrr.at("equipType").asInt();
//    bool _isPlane=_equipBaseAtrr.at("isPlane").asBool();
//    
//
//    
//    std::string filePath="equipment/";
//    filePath+=std::to_string(_equipNumber)+"/equipXML"+std::to_string(_equipNumber)+".xml";
//    XMLDocument *pDoc=new XMLDocument();
//    
//    XMLDeclaration *pDec=pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
//    pDoc->LinkEndChild(pDec);
//    
//    
//    //<plist version=?>
//    XMLElement *dataElement=pDoc->NewElement("data");
//    dataElement->SetAttribute("version", "1.0");
//    pDoc->LinkEndChild(dataElement);
//    
//    //<"the number of the kantai:  i">
//    XMLComment *commentElement=pDoc->NewComment(StringUtils::format("the number of the equip:  %d",_equipNumber).c_str());
//    dataElement->LinkEndChild(commentElement);
//    
//    //xml add equipBaseAtrr
//    XMLElement *equipBaseAtrr=pDoc->NewElement("equipBaseAtrribute");
//    equipBaseAtrr->SetAttribute("equipNumber", _equipNumber);
//    equipBaseAtrr->SetAttribute("equipName", _equipName.c_str());
//    equipBaseAtrr->SetAttribute("equipScope", _equipScope);
//    equipBaseAtrr->SetAttribute("equipType", _equipType);
//    equipBaseAtrr->SetAttribute("isPlane", _isPlane);
//    dataElement->LinkEndChild(equipBaseAtrr);
//    
//    
//    //xml add equipAdvanceAtrr
//    ValueMap _equipAdvanceAtrr=_equipData[1].asValueMap();
//    XMLElement *equipAdvanceAtrr=pDoc->NewElement("equipAdvanceAtrr");
//    for(auto it=_equipAdvanceAtrr.begin();it!=_equipAdvanceAtrr.end();++it)
//    {
//       equipAdvanceAtrr->SetAttribute(it->first.c_str(), it->second.asInt());
//    }
//    dataElement->LinkEndChild(equipAdvanceAtrr);
//    
//    
//    //xml add supKantaiType
//    ValueVector _supKantaiType=_equipData[2].asValueVector();
//    XMLElement *supKantaiType=pDoc->NewElement("supKantaiType");
//    dataElement->LinkEndChild(supKantaiType);
//    
//    for (auto it=_supKantaiType.begin(); it!=_supKantaiType.end(); ++it)
//    {
//        XMLElement* supType=pDoc->NewElement("supKantaiType");
//        supType->LinkEndChild(pDoc->NewText(std::to_string(it->asInt()).c_str()));
//        supKantaiType->LinkEndChild(supType);
//    }
//    
//    pDoc->SaveFile(filePath.c_str());
//    pDoc->Print();
//    delete pDoc;
//    
//    
//}
//
//
//
///////存储equip本体的xml构造方法vol.1/////
//
////valueVector equipData
////===>valueMap equipBaseAtrr
////装备的基本属性
////=====>std::pair<std::string ,Value(int)> equipNumber    装备编号
////=====>std::pair<std::string ,Value(std::string)> equipName   装备名称
////=====>std::pair<std::string ,Value(int)> equipScope   装备分类
////=====>std::pair<std::string ,Value(int)> equipType  装备种类
////=====>std::pair<std::string ,Value(bool)> isPlane  是否是飞机
//
////===>valueMap equipAdvanceAtrr
////装备能提高舰娘的某项属性，提高的属性的名字和具体数值存在于该valueMap中
////有可能某项数据不存在，存在的话，添加，不存在的话不添加
////=====>std::pair<std::string ,Value(int)> firePower
////=====>std::pair<std::string ,Value(int)> AviTorpedo
////=====>std::pair<std::string ,Value(int)> AviBomb
////=====>std::pair<std::string ,Value(int)> antiAir
////=====>std::pair<std::string ,Value(int)> antiSubmarine
////=====>std::pair<std::string ,Value(int)> searchEnemy
////=====>std::pair<std::string ,Value(int)> hitRate
////=====>std::pair<std::string ,Value(int)> dodge
////=====>std::pair<std::string ,Value(int)> range
////=====>std::pair<std::string ,Value(int)> armor
//
////===>valueVector<value<KantaiType>> supKantaiType;
//
//ValueVector XMLBuilder::readEquipXml(int _equipNumber)
//{
//
//    std::string filePath="equipment/";
//    filePath+=std::to_string(_equipNumber)+"/equipXML"+std::to_string(_equipNumber)+".xml";
//    filePath=FileUtils::getInstance()->fullPathForFilename(filePath);
//    XMLDocument *pDoc = new XMLDocument();
//    XMLError errorId = pDoc->LoadFile(filePath.c_str());
//    if (errorId != 0) {
//        //xml格式错误
//        return ValueVector();
//    }
//    XMLElement *dataEle = pDoc->RootElement();
//    //获取第一个节点属性
//    const XMLAttribute *attribute = dataEle->FirstAttribute();
//    //打印节点属性名和值
//    log("attribute<em>name = %s,attribute</em>value = %s", attribute->Name(), attribute->Value());
//    
//    //equipData
//    ValueVector _equipData;
//    
//    
//    
//    //equipBaseAtrr
//    ValueMap _equipBaseAtrr;
//    XMLElement *equipBaseAtrr=dataEle->FirstChildElement("equipBaseAtrribute");
//    if(equipBaseAtrr)
//    {
//
//        const XMLAttribute* equipNumber=equipBaseAtrr->FirstAttribute();
//        if (equipNumber)
//        {
//            _equipBaseAtrr[equipNumber->Name()]=equipNumber->Value();
//            
//            while (equipNumber->Next())
//            {
//                equipNumber=equipNumber->Next();
//                _equipBaseAtrr[equipNumber->Name()]=equipNumber->Value();
//            }
//
//        }
//        else
//        {
//            CCASSERT(false, "read equipBaseAtrr fail");
//            return ValueVector();
//        }
//    }
//    else
//    {
//        CCASSERT(false, "read equipBaseAtrr fail");
//        return ValueVector();
//    }
//    _equipData.push_back(Value(_equipBaseAtrr));
//    
//    
//    
//    //equipAdvanceAtrr
//    ValueMap _equipAdvanceAtrr;
//    XMLElement *equipAdvanceAtrr=equipBaseAtrr->NextSiblingElement();
//    if (equipAdvanceAtrr)
//    {
//        const XMLAttribute* advanceAtrr=equipAdvanceAtrr->FirstAttribute();
//        if (advanceAtrr)
//        {
//            _equipAdvanceAtrr[advanceAtrr->Name()]=advanceAtrr->Value();
//            
//            while (advanceAtrr->Next())
//            {
//                advanceAtrr=advanceAtrr->Next();
//                _equipAdvanceAtrr[advanceAtrr->Name()]=advanceAtrr->Value();
//            }
//        }
//    }
//    _equipData.push_back(Value(_equipAdvanceAtrr));
//    
//    //supKantaiType
//    ValueVector _supKantaiType;
//    XMLElement *supKantaiType=equipAdvanceAtrr->NextSiblingElement();
//    
//    if (supKantaiType)
//    {
//        XMLElement *supKantaiEle=supKantaiType->FirstChildElement();
//        if (supKantaiEle)
//        {
//            _supKantaiType.push_back(Value(supKantaiEle->GetText()));
//            XMLElement *supKantaiNext=supKantaiEle->NextSiblingElement();
//            while (supKantaiNext)
//            {
//                 _supKantaiType.push_back(Value(supKantaiNext->GetText()));
//                supKantaiNext=supKantaiNext->NextSiblingElement();
//            }
//        }
//        else
//        {
//            CCASSERT(false, "read supKantaiType fail");
//            return ValueVector();
//            
//        }
//    }
//    _equipData.push_back(Value(_supKantaiType));
//    
//    
//    
//    return _equipData;
//}
//
///////存储equip本体的xml构造方法vol.1/////
//
////valueVector equipData
////===>valueMap equipBaseAtrr
////装备的基本属性
////=====>std::pair<std::string ,Value(int)> equipNumber    装备编号
////=====>std::pair<std::string ,Value(std::string)> equipName   装备名称
////=====>std::pair<std::string ,Value(int)> equipScope   装备分类
////=====>std::pair<std::string ,Value(int)> equipType  装备种类
////=====>std::pair<std::string ,Value(bool)> isPlane  是否是飞机
//
////===>valueMap equipAdvanceAtrr
////装备能提高舰娘的某项属性，提高的属性的名字和具体数值存在于该valueMap中
////有可能某项数据不存在，存在的话，添加，不存在的话不添加
////=====>std::pair<std::string ,Value(int)> firePower
////=====>std::pair<std::string ,Value(int)> AviTorpedo
////=====>std::pair<std::string ,Value(int)> AviBomb
////=====>std::pair<std::string ,Value(int)> antiAir
////=====>std::pair<std::string ,Value(int)> antiSubmarine
////=====>std::pair<std::string ,Value(int)> searchEnemy
////=====>std::pair<std::string ,Value(int)> hitRate
////=====>std::pair<std::string ,Value(int)> dodge
////=====>std::pair<std::string ,Value(int)> range
////=====>std::pair<std::string ,Value(int)> armor
//
////===>valueVector<value<KantaiType>> supKantaiType;
//
//
//
//
//
//void XMLBuilder::printEquipXML(ValueVector _equipData)
//{
//    ValueMap _equipBaseAtrr=_equipData[0].asValueMap();
//    
//    
//    int _equipNumber=_equipBaseAtrr.at("equipNumber").asInt();
//    std::string _equipName=_equipBaseAtrr.at("equipName").asString();
//    int _equipScope=_equipBaseAtrr.at("equipScope").asInt();
//    int _equipType=_equipBaseAtrr.at("equipType").asInt();
//    bool _isPlane=_equipBaseAtrr.at("isPlane").asBool();
//    
//    log("===>equipBaseAtrr");
//    log("=====>equipNumber:  %d",_equipNumber);
//    log("=====>equipName:    %s",_equipName.c_str());
//    log("=====>equipScope:   %d",_equipScope);
//    log("=====>equipType:    %d",_equipType);
//    log("=====>equipType:    %d",_isPlane);
//    
//    
//    ValueMap _equipAdvanceAtrr=_equipData[1].asValueMap();
//    log("===>equipAdvanceAtrr");
//    for (auto it=_equipAdvanceAtrr.begin(); it!=_equipAdvanceAtrr.end(); ++it)
//    {
//        log("=====>%s :%d ",it->first.c_str(),it->second.asInt());
//    }
//    
//    
//    ValueVector _supKantaiType=_equipData[2].asValueVector();
//    log("===>supKantaiType");
//    for (auto it=_supKantaiType.begin(); it!=_supKantaiType.end(); ++it)
//    {
//        log("support the kantai type: %d",it->asInt());
//    }
//    
//}
//
//////存储kantai本体的xml构造方法
//
////vol.1
//
////valueVector kantaiData
////===>valueMap name
////舰娘的各项名字(每项名字必须存在）
////=====>std::pair<std::string,Value(std::string)> kantaiName       //舰娘名字
////=====>std::pair<std::string,Value(std::string)> kantaiFullName   //舰娘全称
//
//
////===>valueMap kantaiBaseAtrr
////舰娘的基本属性(每项基本属性必须存在）
////=====>std::pair<std::string,Value(int)> kantaiNumber
////=====>std::pair<std::string,Value(int)> kantaiType
////=====>std::pair<std::string,Value(int)> buildTime
////=====>std::pair<std::string,Value(int)> updateLv
////=====>std::pair<std::string,Value(int)> fuel
////=====>std::pair<std::string,Value(int)> ammo
////=====>std::pair<std::string,Value(int)> speed
////=====>std::pair<std::string,Value(int)> range
////=====>std::pair<std::string,Value(int)> maxHp       //耐久值
////=====>std::pair<std::string,Value(int)> transformTimes       //改造次数
//
//
////===>valueMap kantaiMaxAtrr
////舰娘相关属性初始时候的最大值（可以有最大属性不存在，不存在的话，最大属性设为0）
////=====>std::pair<std::string,Value(int)> maxFirePower
////=====>std::pair<std::string,Value(int)> maxArmor
////=====>std::pair<std::string,Value(int)> maxTorpedo
////=====>std::pair<std::string,Value(int)> maxDodge
////=====>std::pair<std::string,Value(int)> maxAntiAir
////=====>std::pair<std::string,Value(int)> maxAntiSubmarine
////=====>std::pair<std::string,Value(int)> maxSearchEnemy
////=====>std::pair<std::string,Value(int)> maxLuck
//
//
////===>valueMap kantaiInitAtrr
////舰娘相关有最大属性的值的初始值（可以没有初始值，不存在的话，初始值设为0）
////=====>std::pair<std::string,Value(int)> initFirePower
////=====>std::pair<std::string,Value(int)> initArmor
////=====>std::pair<std::string,Value(int)> initTorpedo
////=====>std::pair<std::string,Value(int)> initDodge
////=====>std::pair<std::string,Value(int)> initAntiAir
////=====>std::pair<std::string,Value(int)> initAntiSubmarine
////=====>std::pair<std::string,Value(int)> initSearchEnemy
////=====>std::pair<std::string,Value(int)> initLuck
//
//
////<equipData>
////舰娘所初始化时候所装装载的装备
////=====>Value(int kantaiEquipSize )单个舰娘所装备格子数量最大值
////=====>Value(ValueMapIntKey kantaiEquipInit) 初始的装备 map(int,value(int)) 保存的是装备的主键值
////=====>Value(ValueVector planeLoad) 每个格子能搭载的飞机数量
//
//
//
//
////vol.2
//
////valueVector kantaiData
////===>valueMap name
////舰娘的各项名字(每项名字必须存在）
////=====>std::pair<std::string,Value(std::string)> kantaiName       //舰娘名字
////=====>std::pair<std::string,Value(std::string)> kantaiFullName   //舰娘全称
//
//
////===>valueMap kantaiBaseAtrr
////舰娘的基本属性(每项基本属性必须存在）
////=====>std::pair<std::string,Value(int)> kantaiNumber
////=====>std::pair<std::string,Value(int)> kantaiType
////=====>std::pair<std::string,Value(int)> buildTime
////=====>std::pair<std::string,Value(int)> updateLv
////=====>std::pair<std::string,Value(int)> fuel
////=====>std::pair<std::string,Value(int)> ammo
////=====>std::pair<std::string,Value(int)> speed
///////////////=====>std::pair<std::string,Value(int)> range
////=====>std::pair<std::string,Value(int)> maxHp       //耐久值
////=====>std::pair<std::string,Value(int)> transformTimes       //改造次数
//
//
////===>valueMap kantaiMaxAtrr
////舰娘相关属性初始时候的最大值（可以有最大属性不存在，不存在的话，最大属性设为0）
////=====>std::pair<std::string,Value(int)> maxFirePower
////=====>std::pair<std::string,Value(int)> maxArmor
////=====>std::pair<std::string,Value(int)> maxTorpedo
////=====>std::pair<std::string,Value(int)> maxDodge
////=====>std::pair<std::string,Value(int)> maxAntiAir
////=====>std::pair<std::string,Value(int)> maxAntiSubmarine
////=====>std::pair<std::string,Value(int)> maxSearchEnemy
////=====>std::pair<std::string,Value(int)> maxLuck
//
//
////===>valueMap kantaiInitAtrr
////舰娘相关有最大属性的值的初始值（可以没有初始值，不存在的话，初始值设为0）
////=====>std::pair<std::string,Value(int)> initFirePower
////=====>std::pair<std::string,Value(int)> initArmor
////=====>std::pair<std::string,Value(int)> initTorpedo
////=====>std::pair<std::string,Value(int)> initDodge
////=====>std::pair<std::string,Value(int)> initAntiAir
////=====>std::pair<std::string,Value(int)> initAntiSubmarine
////=====>std::pair<std::string,Value(int)> initSearchEnemy
////=====>std::pair<std::string,Value(int)> initLuck
//
////<equipData>
////舰娘所初始化时候所装装载的装备
////=====>Value(int kantaiEquipSize )单个舰娘所装备格子数量最大值
////=====>Value(ValueMapIntKey kantaiEquipInit) 初始的装备 map(int,value(int)) 保存的是装备的编号
////=====>Value(ValueVector planeLoad) 每个格子能搭载的飞机数量
//
//
//
//
//
//void XMLBuilder::writeKantaiXml(ValueVector _kantaiData)
//{
//    //base
//    ValueMap _kantaiBaseAtrr=_kantaiData[1].asValueMap();
//    int _kantaiNumber=_kantaiBaseAtrr.at("kantaiNumber").asInt();
//    int _kantaiType=_kantaiBaseAtrr.at("kantaiType").asInt();
//    int _buildTime=_kantaiBaseAtrr.at("buildTime").asInt();
//    int _updateLv=_kantaiBaseAtrr.at("updateLv").asInt();
//    int _fuel=_kantaiBaseAtrr.at("fuel").asInt();
//    int _ammo=_kantaiBaseAtrr.at("ammo").asInt();
//    int _speed=_kantaiBaseAtrr.at("speed").asInt();
//    int _range=_kantaiBaseAtrr.at("range").asInt();
//    int _maxHp=_kantaiBaseAtrr.at("maxHp").asInt();
//    int _transformTimes=_kantaiBaseAtrr.at("transformTimes").asInt();
//    
//    
//
//    std::string filePath="kantai/";
//    filePath+=std::to_string(_kantaiNumber)+"/kantaiXML"+std::to_string(_kantaiNumber)+".xml";
//    XMLDocument *pDoc=new XMLDocument();
//    
//    XMLDeclaration *pDec=pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
//    pDoc->LinkEndChild(pDec);
//    
//    
//    //<plist version=?>
//    XMLElement *dataElement=pDoc->NewElement("data");
//    dataElement->SetAttribute("version", "2.0");
//    pDoc->LinkEndChild(dataElement);
//    
//    //<"the number of the kantai:  i">
//    XMLComment *commentElement=pDoc->NewComment(StringUtils::format("the number of the equip:  %d",_kantaiNumber).c_str());
//    dataElement->LinkEndChild(commentElement);
//    
//    //xml add name
//    ValueMap _name=_kantaiData[0].asValueMap();
//    std::string _kantaiName=_name.at("kantaiName").asString();
//    std::string _kantaiFullName=_name.at("kantaiFullName").asString();
//    
//    
//    XMLElement *nameEle=pDoc->NewElement("name");
//    nameEle->SetAttribute("kantaiName", _kantaiName.c_str());
//    nameEle->SetAttribute("kantaiFullName", _kantaiFullName.c_str());
//    dataElement->LinkEndChild(nameEle);
//    
//
//    //xml add equipBaseAtrr
//    XMLElement *kantaiBaseAtrr=pDoc->NewElement("kantaiBaseAtrr");
//    kantaiBaseAtrr->SetAttribute("kantaiNumber", _kantaiNumber);
//    kantaiBaseAtrr->SetAttribute("kantaiType", _kantaiType);
//    kantaiBaseAtrr->SetAttribute("buildTime", _buildTime);
//    kantaiBaseAtrr->SetAttribute("updateLv", _updateLv);
//    kantaiBaseAtrr->SetAttribute("fuel", _fuel);
//    kantaiBaseAtrr->SetAttribute("ammo", _ammo);
//    kantaiBaseAtrr->SetAttribute("speed", _speed);
//    kantaiBaseAtrr->SetAttribute("range", _range);
//    kantaiBaseAtrr->SetAttribute("maxHp", _maxHp);
//    kantaiBaseAtrr->SetAttribute("transformTimes", _transformTimes);
//    
//    dataElement->LinkEndChild(kantaiBaseAtrr);
//    
//    
//    //xml add kantaiMaxAtrr
//    ValueMap _kantaiMaxAtrr=_kantaiData[2].asValueMap();
//    XMLElement *kantaiMaxAtrr=pDoc->NewElement("kantaiMaxAtrr");
//    for(auto it=_kantaiMaxAtrr.begin();it!=_kantaiMaxAtrr.end();++it)
//    {
//        kantaiMaxAtrr->SetAttribute(it->first.c_str(), it->second.asInt());
//    }
//    dataElement->LinkEndChild(kantaiMaxAtrr);
//    
//    
//    //xml add kantaiInitAtrr
//    ValueMap _kantaiInitAtrr=_kantaiData[3].asValueMap();
//    XMLElement *kantaiInitAtrr=pDoc->NewElement("kantaiInitAtrr");
//    for(auto it=_kantaiInitAtrr.begin();it!=_kantaiInitAtrr.end();++it)
//    {
//        kantaiInitAtrr->SetAttribute(it->first.c_str(), it->second.asInt());
//    }
//    dataElement->LinkEndChild(kantaiInitAtrr);
//    
//    //equipData
//    int _kantaiEquipSize=_kantaiData[4].asInt();
//    XMLElement *equipData=pDoc->NewElement("equipData");
//    equipData->SetAttribute("kantaiEquipSize", _kantaiEquipSize);
//    dataElement->LinkEndChild(equipData);
//    
//
////    ValueMapIntKey _kantaiEquipInit=_kantaiData[5].asIntKeyMap();
////    XMLElement* equipInit=pDoc->NewElement("kantaiEquipInit");
////    
////    for (auto it=_kantaiEquipInit.begin(); it!=_kantaiEquipInit.end(); ++it)
////    {
////
////        equipInit->SetAttribute(std::to_string(it->first).c_str(), it->second.asInt());
////    }
////    equipData->LinkEndChild(equipInit);
//
//    
//    ValueMapIntKey _kantaiEquipInit=_kantaiData[5].asIntKeyMap();
//    XMLElement* kantaiEquipInit=pDoc->NewElement("kantaiEquipInit");
//    equipData->LinkEndChild(kantaiEquipInit);
//    
//    
//    XMLElement* equipInit=pDoc->NewElement("array");
//    auto it=_kantaiEquipInit.begin();
//    equipInit->LinkEndChild(pDoc->NewText(std::to_string(it->second.asInt()).c_str()));
//    kantaiEquipInit->LinkEndChild(equipInit);
//    ++it;
//    while (it!=_kantaiEquipInit.end())
//    {
//        equipInit=pDoc->NewElement("array");
//        equipInit->LinkEndChild(pDoc->NewText(std::to_string(it->second.asInt()).c_str()));
//        kantaiEquipInit->LinkEndChild(equipInit);
//        ++it;
//    }
//    
//    
//    //////
//    ValueVector _planeLoad=_kantaiData[6].asValueVector();
//    XMLElement* planeLoad=pDoc->NewElement("planeLoad");
//    equipData->LinkEndChild(planeLoad);
//    
//
//    for (auto it=_planeLoad.begin(); it!=_planeLoad.end(); ++it)
//    {
//        XMLElement* planeLoadInit=pDoc->NewElement("array");
//        planeLoadInit->LinkEndChild(pDoc->NewText(std::to_string(it->asInt()).c_str()));
//        planeLoad->LinkEndChild(planeLoadInit);
//    }
//    
//    
//    pDoc->SaveFile(filePath.c_str());
//    pDoc->Print();
//    delete pDoc;
//    
//}
//
//
//ValueVector XMLBuilder::buildTheKantaiXML()
//{
//    ValueVector _kantaiData;
//    
//    ValueMap _name;
//    _name["kantaiName"]="金刚";
//    _name["kantaiFullName"]="金刚型一番舰";
//    _kantaiData.push_back(Value(_name));
//    
//    
//    ValueMap _kantaiBaseAtrr;
//    _kantaiBaseAtrr["kantaiNumber"]=21;
//    _kantaiBaseAtrr["kantaiType"]=Battleship;
//    _kantaiBaseAtrr["buildTime"]=4*3600;
//    _kantaiBaseAtrr["updateLv"]=25;
//    _kantaiBaseAtrr["fuel"]=100;
//    _kantaiBaseAtrr["ammo"]=110;
//    _kantaiBaseAtrr["speed"]=4;
//    _kantaiBaseAtrr["range"]=4;
//    _kantaiBaseAtrr["maxHp"]=63;
//    _kantaiBaseAtrr["transformTimes"]=0;
//    _kantaiData.push_back(Value(_kantaiBaseAtrr));
//    
//    
//    ValueMap _kantaiMaxAtrr;
//    _kantaiMaxAtrr["maxFirePower"]=98;
//    _kantaiMaxAtrr["maxArmor"]=94;
//    _kantaiMaxAtrr["maxTorpedo"]=0;
//    _kantaiMaxAtrr["maxDodge"]=72;
//    _kantaiMaxAtrr["maxAntiAir"]=84;
//    _kantaiMaxAtrr["maxAntiSubmarine"]=0;
//    _kantaiMaxAtrr["maxSearchEnemy"]=49;
//    _kantaiMaxAtrr["maxLuck"]=79;
//    _kantaiData.push_back(Value(_kantaiMaxAtrr));
//    
//    ValueMap _kantaiInitAtrr;
//    _kantaiInitAtrr["initFirePower"]=63;
//    _kantaiInitAtrr["initArmor"]=52;
//    _kantaiInitAtrr["initTorpedo"]=0;
//    _kantaiInitAtrr["initDodge"]=30;
//    _kantaiInitAtrr["initAntiAir"]=24;
//    _kantaiInitAtrr["initAntiSubmarine"]=0;
//    _kantaiInitAtrr["initSearchEnemy"]=13;
//    _kantaiInitAtrr["initLuck"]=12;
//    _kantaiData.push_back(Value(_kantaiInitAtrr));
//    
//    int _kantaiEquipSize=3;
//    _kantaiData.push_back(Value(_kantaiEquipSize));
//    
//    ValueMapIntKey _kantaiEquipInit;
//    _kantaiEquipInit[0]=2;
//    _kantaiEquipInit[1]=4;
//    _kantaiEquipInit[2]=12;
//    _kantaiData.push_back(Value(_kantaiEquipInit));
//    
//    ValueVector _planeLoad;
//    _planeLoad.push_back(Value(11));
//    _planeLoad.push_back(Value(11));
//    _planeLoad.push_back(Value(11));
//    _kantaiData.push_back(Value(_planeLoad));
//    
//    
//    return _kantaiData;
//}
//
//
//ValueVector XMLBuilder::readKantaiXML(int _kantaiNumber)
//{
//    std::string filePath="kantai/";
//    
//    if (_kantaiNumber<0)
//    {
//        filePath+=std::to_string(_kantaiNumber)+"/kantaiXML.xml";
//    }
//    else
//    filePath+=std::to_string(_kantaiNumber)+"/kantaiXML"+std::to_string(_kantaiNumber)+".xml";
//    filePath=FileUtils::getInstance()->fullPathForFilename(filePath);
//    XMLDocument *pDoc = new XMLDocument();
//    XMLError errorId = pDoc->LoadFile(filePath.c_str());
//    if (errorId != 0) {
//        //xml格式错误
//        return ValueVector();
//    }
//    XMLElement *dataEle = pDoc->RootElement();
//    //获取第一个节点属性
//    const XMLAttribute *attribute = dataEle->FirstAttribute();
//    //打印节点属性名和值
//    log("attribute<em>name = %s,attribute</em>value = %s", attribute->Name(), attribute->Value());
//    
//    //kantaiData
//    ValueVector _kantaiData;
//    
//
//    //name
//    ValueMap _name;
//    XMLElement *nameEle=dataEle->FirstChildElement("name");
//    if(nameEle)
//    {
//        
//        const XMLAttribute* kantaiName=nameEle->FirstAttribute();
//        if (kantaiName)
//        {
//            _name[kantaiName->Name()]=kantaiName->Value();
//            const XMLAttribute* kantaiFullName=kantaiName->Next();
//            if (kantaiFullName)
//            {
//                _name[kantaiFullName->Name()]=kantaiFullName->Value();
//            }
//            else
//            {
//                CCASSERT(false, "read _name fail");
//                return ValueVector();
//            }
//        }
//        else
//        {
//            CCASSERT(false, "read _name fail");
//            return ValueVector();
//        }
//    }
//    else
//    {
//        CCASSERT(false, "read _name fail");
//        return ValueVector();
//    }
//    _kantaiData.push_back(Value(_name));
//    
//    
//    
//    //kantaiBaseAtrr
//    ValueMap _kantaiBaseAtrr;
//    XMLElement *kantaiBaseAtrr=nameEle->NextSiblingElement();
//    if (kantaiBaseAtrr)
//    {
//        const XMLAttribute* baseAtrr=kantaiBaseAtrr->FirstAttribute();
//        if (baseAtrr)
//        {
//            _kantaiBaseAtrr[baseAtrr->Name()]=baseAtrr->Value();
//            
//            while (baseAtrr->Next())
//            {
//                baseAtrr=baseAtrr->Next();
//                _kantaiBaseAtrr[baseAtrr->Name()]=baseAtrr->Value();
//            }
//        }
//    }
//    _kantaiData.push_back(Value(_kantaiBaseAtrr));
//    
//    
//  
//    //kantaiMaxAtrr
//    ValueMap _kantaiMaxAtrr;
//    XMLElement *kantaiMaxAtrr=kantaiBaseAtrr->NextSiblingElement();
//    if (kantaiMaxAtrr)
//    {
//        const XMLAttribute* maxAtrr=kantaiMaxAtrr->FirstAttribute();
//        if (maxAtrr)
//        {
//            _kantaiMaxAtrr[maxAtrr->Name()]=maxAtrr->Value();
//            
//            while (maxAtrr->Next())
//            {
//                maxAtrr=maxAtrr->Next();
//                _kantaiMaxAtrr[maxAtrr->Name()]=maxAtrr->Value();
//            }
//        }
//    }
//    _kantaiData.push_back(Value(_kantaiMaxAtrr));
//    
//    
//    
//    //kantaiInitAtrr
//    ValueMap _kantaiInitAtrr;
//    XMLElement *kantaiInitAtrr=kantaiMaxAtrr->NextSiblingElement();
//    if (kantaiInitAtrr)
//    {
//        const XMLAttribute* initAtrr=kantaiInitAtrr->FirstAttribute();
//        if (initAtrr)
//        {
//            _kantaiInitAtrr[initAtrr->Name()]=initAtrr->Value();
//            
//            while (initAtrr->Next())
//            {
//                initAtrr=initAtrr->Next();
//                _kantaiInitAtrr[initAtrr->Name()]=initAtrr->Value();
//            }
//        }
//    }
//    _kantaiData.push_back(Value(_kantaiInitAtrr));
//    
//    
//    //kantaiEquipSize
//    int _kantaiEquipSize;
//    XMLElement *equipData=kantaiInitAtrr->NextSiblingElement();
//    if (equipData)
//    {
//        const XMLAttribute* kantaiEquipSize=equipData->FirstAttribute();
//        _kantaiEquipSize=std::atoi(kantaiEquipSize->Value());
//    }
//    _kantaiData.push_back(Value(_kantaiEquipSize));
//    
//    
//    if (_kantaiEquipSize)
//    {
//        //kantaiEquipInit
//        ValueMapIntKey _kantaiEquipInit;
//        int count=0;
//        XMLElement *kantaiEquipInit=equipData->FirstChildElement();
//        if (kantaiEquipInit)
//        {
//            XMLElement *equipInit=kantaiEquipInit->FirstChildElement();
//            _kantaiEquipInit[count++]=std::atoi(equipInit->GetText());
//            while (equipInit->NextSiblingElement())
//            {
//                equipInit=equipInit->NextSiblingElement();
//                log("%s",equipInit->Value());
//                _kantaiEquipInit[count++]=std::atoi(equipInit->GetText());
//            }
//            
//        }
//        _kantaiData.push_back(Value(_kantaiEquipInit));
//        
//        
//        //planeLoad
//        ValueVector _planeLoad;
//        XMLElement *planeLoad=kantaiEquipInit->NextSiblingElement();
//        if (planeLoad)
//        {
//            XMLElement *planeLoadEle=planeLoad->FirstChildElement();
//            _planeLoad.push_back(Value(std::atoi(planeLoadEle->GetText())));
//            while (planeLoadEle->NextSiblingElement())
//            {
//                planeLoadEle=planeLoadEle->NextSiblingElement();
//                _planeLoad.push_back(Value(std::atoi(planeLoadEle->GetText())));
//            }
//            
//        }
//        _kantaiData.push_back(Value(_planeLoad));
//
//    }
//    
//    return _kantaiData;
//
//    
//}
//
//
//void XMLBuilder::printKantaiXML(ValueVector _kantaiData)
//{
//    
//    ValueMap _name=_kantaiData[0].asValueMap();
//    std::string _kantaiName=_name.at("kantaiName").asString();
//    std::string _kantaiFullName=_name.at("kantaiFullName").asString();
//    
//    log("===>name");
//    log("=====>kantaiName:      %s",_kantaiName.c_str());
//    log("=====>kantaiFullName:  %s",_kantaiFullName.c_str());
//    
//    
//    
//    
//    ValueMap _kantaiBaseAtrr=_kantaiData[1].asValueMap();
//    int _kantaiNumber=_kantaiBaseAtrr.at("kantaiNumber").asInt();
//    int _kantaiType=_kantaiBaseAtrr.at("kantaiType").asInt();
//    int _buildTime=_kantaiBaseAtrr.at("buildTime").asInt();
//    int _updateLv=_kantaiBaseAtrr.at("updateLv").asInt();
//    int _fuel=_kantaiBaseAtrr.at("fuel").asInt();
//    int _ammo=_kantaiBaseAtrr.at("ammo").asInt();
//    int _speed=_kantaiBaseAtrr.at("speed").asInt();
//    int _range=_kantaiBaseAtrr.at("range").asInt();
//    int _maxHp=_kantaiBaseAtrr.at("maxHp").asInt();
//    int _transformTimes=_kantaiBaseAtrr.at("transformTimes").asInt();
//    
//    
//    log("===>kantaiBaseAtrr");
//    log("=====>kantaiNumber:  %d",_kantaiNumber);
//    log("=====>kantaiType:    %d",_kantaiType);
//    log("=====>buildTime:     %d",_buildTime);
//    log("=====>updateLv:      %d",_updateLv);
//    log("=====>fuel:          %d",_fuel);
//    log("=====>ammo:          %d",_ammo);
//    log("=====>speed:         %d",_speed);
//    log("=====>range:         %d",_range);
//    log("=====>maxHp:         %d",_maxHp);
//    log("=====>transformTimes:         %d",_transformTimes);
//    
//    
//    ValueMap _kantaiMaxAtrr=_kantaiData[2].asValueMap();
//    log("===>kantaiMaxAtrr");
//    for (auto it=_kantaiMaxAtrr.begin(); it!=_kantaiMaxAtrr.end(); ++it)
//    {
//        log("=====>%s :%d ",it->first.c_str(),it->second.asInt());
//    }
//    
//    
//    ValueMap _kantaiInitAtrr=_kantaiData[3].asValueMap();
//    log("===>kantaiInitAtrr");
//    for (auto it=_kantaiInitAtrr.begin(); it!=_kantaiInitAtrr.end(); ++it)
//    {
//        log("=====>%s :%d ",it->first.c_str(),it->second.asInt());
//    }
//    
//    int _kantaiEquipSize=_kantaiData[4].asInt();
//    log("===>equip");
//    log("=====>kantaiEquipSize:    %d",_kantaiEquipSize);
//    
//    
//    ValueMapIntKey _kantaiEquipInit=_kantaiData[5].asIntKeyMap();
//    log("=====>kantaiEquipInit");
//    for (auto it=_kantaiEquipInit.begin(); it!=_kantaiEquipInit.end(); ++it)
//    {
//        log("=======>  %d ",it->second.asInt());
//    }
//    
//    ValueVector _planeLoad=_kantaiData[6].asValueVector();
//    log("=====>planeLoad:");
//    for (auto it=_planeLoad.begin(); it!=_planeLoad.end(); ++it)
//    {
//        log("=======>  %d ",it->asInt());
//    }
//    
//}
//
//
//
//
//
//
//void XMLBuilder::readXMLCallback(Ref* pSender)
//{
//    
//    ValueVector zhang=XMLBuilder::buildTheEquipXML();
//     XMLBuilder::writeEquipXml(zhang);
//}
//
//void XMLBuilder::writeXMLCallback(Ref* pSender)
//{
//    Equip* zhang;
//    for (int i=0; i<10; ++i)
//    {
//        zhang=Equip::create(i, 1);
//    }
//    
//    //EquipPrint printEquip;
//    //printEquip.PrintEquipInfo(zhang);
//    //ValueVector zhang=XMLBuilder::readEquipXml(1);
//    //XMLBuilder::printEquipXML(zhang);
//}
//
