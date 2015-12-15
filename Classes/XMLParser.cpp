//
//  XMLParser.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/23/15.
//
//

#include "XMLParser.h"
#include "kantai.h"


XMLParser* XMLParser::instance=0;


XMLParser::XMLParser()
{
    
}


XMLParser* XMLParser::getInstance()
{
    if (!instance)
    {
        instance=new XMLParser();
    }
    return instance;
}



Mission* XMLParser::readMissionXml(std::string name)
{
    auto mission=new Mission();
    
    std::string filePath="Mission.xml";
    
    XMLDocument *pDoc = new XMLDocument();
    XMLError errorId = pDoc->LoadFile(filePath.c_str());
    
    if (errorId!=0)
    {
        return mission;
    }
    
    XMLElement* root=pDoc->RootElement();
    XMLElement* node=root->FirstChildElement();
    
    while (node)
    {
        const char* tempName=node->FirstChildElement()->GetText();
        if (name==tempName)
        {
            break;
        }
        node=node->NextSiblingElement();
    }
    
    if (node)
    {
        mission->id=name;
        mission->areaId=atoi(node->FirstChildElement("area")->GetText());
        mission->index=atoi(node->FirstChildElement("index")->GetText());
        mission->name=node->FirstChildElement("name")->GetText();
        mission->missionName=node->FirstChildElement("missionName")->GetText();
        mission->detail=node->FirstChildElement("Detail")->GetText();
        
        
        XMLElement* missionNode=node->FirstChildElement("Node");
        while (missionNode)
        {
            auto newMissionNode=new MissionNode();
            newMissionNode->setType(missionNode->FirstChildElement("type")->GetText());
            newMissionNode->position=
            Point(atoi(missionNode->FirstChildElement("positionX")->GetText()),
                  atoi(missionNode->FirstChildElement("positionY")->GetText()));
            
            
            XMLElement* directionNode=missionNode->FirstChildElement("direction");
            if (directionNode)
            {
                newMissionNode->compassDirection=Compass::parseDirection(directionNode->GetText());
            }
            XMLElement* enemyFleetNode=missionNode->FirstChildElement("enemy");
            if (enemyFleetNode)
            {
                newMissionNode->parseEnemyFleet(enemyFleetNode->GetText());
            }
            int parentIndex=atoi(missionNode->FirstChildElement("parent")->GetText());
            if (parentIndex!=-1)
            {
                mission->nodes[parentIndex]->children.push_back(newMissionNode);
            }
            mission->nodes.push_back(newMissionNode);
            missionNode=missionNode->NextSiblingElement();
        }
        
    }
    delete pDoc;
    
    return mission;
}

EquipImp* XMLParser::readEquipXml(int _equipNumber)
{
    EquipImp* equipImp=new EquipImp;
    
    std::string filePath="/Volumes/opengl/kancolle_beta/Resources/equipment/";
    filePath+=std::to_string(_equipNumber)+"/equipXML"+std::to_string(_equipNumber)+".xml";
    
    
    XMLDocument *pDoc = new XMLDocument();
    XMLError errorId = pDoc->LoadFile(filePath.c_str());
    if (errorId != 0)
    {
        char msg[256]={0};
        sprintf(msg, "can not open the XML: equip %5d", _equipNumber);
        CCASSERT(false,msg);
        return equipImp;
    }
    XMLElement *dataEle = pDoc->RootElement();
    //获取第一个节点属性
    //const XMLAttribute *attribute = dataEle->FirstAttribute();
    //打印节点属性名和值
    //equipData

    
    //equipBaseAtrr

    XMLElement *equipBaseAtrr=dataEle->FirstChildElement("equipBaseAtrribute");
    if(equipBaseAtrr)
    {
        
        const XMLAttribute* equipNumber=equipBaseAtrr->FirstAttribute();
        if (equipNumber)
        {
            equipImp->equipNumber=atoi(equipNumber->Value());
            
            equipNumber=equipNumber->Next();
            equipImp->equipName=equipNumber->Value();
            
            equipNumber=equipNumber->Next();
            equipImp->equipScope=static_cast<Shooting_Range>(atoi(equipNumber->Value()));
            
            equipNumber=equipNumber->Next();
            equipImp->equipType=static_cast<EquipType>(atoi(equipNumber->Value()));
            
            equipNumber=equipNumber->Next();
            equipImp->isPlane=static_cast<bool>(atoi(equipNumber->Value()));
        }
        else
        {
            char msg[256]={0};
            sprintf(msg, "can not open the XML: equip %5d", _equipNumber);
            CCASSERT(false,msg);
            return equipImp;
        }
    }
    else
    {
        char msg[256]={0};
        sprintf(msg, "can not open the XML: equip %5d", _equipNumber);
        CCASSERT(false,msg);
        return equipImp;
    }
    
    //equipAdvanceAtrr
    XMLElement *equipAdvanceAtrr=equipBaseAtrr->NextSiblingElement();
    if (equipAdvanceAtrr)
    {
        const XMLAttribute* advanceAtrr=equipAdvanceAtrr->FirstAttribute();
        if (advanceAtrr)
        {
            equipImp->firePower=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->AviTorpedo=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->AviBomb=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->antiAir=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->antiSubmarine=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->searchEnemy=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->hitRate=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->dodge=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->range=atoi(advanceAtrr->Value());
            
            advanceAtrr=advanceAtrr->Next();
            equipImp->armor=atoi(advanceAtrr->Value());
        }
    }
    
    auto& equipSet=equipImp->supKantaiType;
    //supKantaiType
    XMLElement *supKantaiType=equipAdvanceAtrr->NextSiblingElement();
    
    if (supKantaiType)
    {
        XMLElement *supKantaiEle=supKantaiType->FirstChildElement();
        if (supKantaiEle)
        {
            KantaiType temp1=static_cast<KantaiType>(atoi(supKantaiEle->GetText()));
            equipSet.insert(temp1);
            XMLElement *supKantaiNext=supKantaiEle->NextSiblingElement();
            while (supKantaiNext)
            {
               temp1=static_cast<KantaiType>(atoi(supKantaiNext->GetText()));
               equipSet.insert(temp1);
               supKantaiNext=supKantaiNext->NextSiblingElement();
            }
        }
        else
        {
            char msg[256]={0};
            sprintf(msg, "can not open the XML: equip %5d", _equipNumber);
            CCASSERT(false,msg);
            return equipImp;
            
        }
    }
    
    return equipImp;
}




Kantai* XMLParser::readKantaiXml(int _kantaiNumber)
{
//    std::string filePath="/Volumes/opengl/kancolle_beta/Resources/kantai/";
//    if (_kantaiNumber<0)
//    {
//        filePath+=std::to_string(_kantaiNumber)+"/kantaiXML.xml";
//    }
//    else
//        filePath+=std::to_string(_kantaiNumber)+"/kantaiXML"+std::to_string(_kantaiNumber)+".xml";
//    
//    XMLDocument *pDoc = new XMLDocument();
//    XMLError errorId = pDoc->LoadFile(filePath.c_str());
//    if (errorId != 0)
//    {
//        CCASSERT(false, "can not open the file");
//    }
//    
//    XMLElement *dataEle = pDoc->RootElement();
//    //获取第一个节点属性
//    //const XMLAttribute *attribute = dataEle->FirstAttribute();
//    
//    Kantai* kantai=new Kantai();
//    
//    //name
//    XMLElement *nameEle=dataEle->FirstChildElement("name");
//    if(nameEle)
//    {
//        
//        const XMLAttribute* kantaiName=nameEle->FirstAttribute();
//        if (kantaiName)
//        {
//            kantai->kantaiName=kantaiName->Value();
//            const XMLAttribute* kantaiFullName=kantaiName->Next();
//            if (kantaiFullName)
//            {
//                kantai->kantaiFullName=kantaiFullName->Value();
//            }
//            else
//            {
//                CCASSERT(false, "read _name fail");
//                return kantai;
//            }
//        }
//        else
//        {
//            CCASSERT(false, "read _name fail");
//            return kantai;
//        }
//    }
//    else
//    {
//        CCASSERT(false, "read _name fail");
//        return kantai;
//    }
//    
//    
//    //kantaiBaseAtrr
//    XMLElement *kantaiBaseAtrr=nameEle->NextSiblingElement();
//    if (kantaiBaseAtrr)
//    {
//        const XMLAttribute* baseAtrr=kantaiBaseAtrr->FirstAttribute();
//        if (baseAtrr)
//        {
//            kantai->kantaiNumber=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->kantaiType=static_cast<KantaiType>(atoi(baseAtrr->Value()));
//            baseAtrr=baseAtrr->Next();
//            
//            //kantai->buildTime=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->updateLv=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->maxFuel=kantai->currFuel=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->maxAmmo=kantai->currAmmo=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->speed=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->range=atoi(baseAtrr->Value());
//            baseAtrr=baseAtrr->Next();
//            
//            kantai->currHp=kantai->maxHp=atoi(baseAtrr->Value());
//            //baseAtrr=baseAtrr->Next();
//        }
//    }
//    
//    XMLElement* kantaiMaxAtrr=kantaiBaseAtrr->NextSiblingElement();
//    if (kantaiMaxAtrr)
//    {
//        const XMLAttribute* maxAtrr=kantaiMaxAtrr->FirstAttribute();
//        if (maxAtrr)
//        {
//            kantai->maxLuck=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxAntiSubmarine=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxDodge=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxAntiAir=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxTorpedo=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxSearchEnemy=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxFirePower=atoi(maxAtrr->Value());
//            maxAtrr=maxAtrr->Next();
//            
//            kantai->maxArmor=atoi(maxAtrr->Value());
//        }
//    }
//    
//    
//    
//    //kantaiInitAtrr
//    XMLElement *kantaiInitAtrr=kantaiMaxAtrr->NextSiblingElement();
//    if (kantaiInitAtrr)
//    {
//        const XMLAttribute* initAtrr=kantaiInitAtrr->FirstAttribute();
//        if (initAtrr)
//        {
//            kantai->searchEnemy=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->armor=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->luck=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->AntiSubMarine=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->dodge=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->torpedo=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->firePower=atoi(initAtrr->Value());
//            initAtrr=initAtrr->Next();
//            
//            kantai->antiAir=atoi(initAtrr->Value());
//        }
//    }
//    
//    //kantaiEquipSize
//    int _kantaiEquipSize;
//    XMLElement *equipData=kantaiInitAtrr->NextSiblingElement();
//    if (equipData)
//    {
//        const XMLAttribute* kantaiEquipSize=equipData->FirstAttribute();
//        _kantaiEquipSize=std::atoi(kantaiEquipSize->Value());
//    }
//    
//    kantai->equipGrid.resize(_kantaiEquipSize);
//    kantai->planeLoad.resize(_kantaiEquipSize);
//    
//    if (_kantaiEquipSize)
//    {
//        //kantaiEquipInit
//        XMLElement *kantaiEquipInit=equipData->FirstChildElement();
//        if (kantaiEquipInit)
//        {
//            XMLElement *equipInit=kantaiEquipInit->FirstChildElement();
//            for (int i=0; i<_kantaiEquipSize; ++i)
//            {
//                int equipNumber=std::atoi(equipInit->GetText());
//                kantai->equipGrid[i]=Equip::create(1,equipNumber,kantai);///少一个equipkey
//                equipInit->NextSiblingElement();
//            }
//        }
//        
//        //planeLoad
//        XMLElement *planeLoad=kantaiEquipInit->NextSiblingElement();
//        if (planeLoad)
//        {
//            XMLElement *planeLoadUnit=planeLoad->FirstChildElement();
//            for (int i=0; i<_kantaiEquipSize; ++i)
//            {
//                kantai->planeLoad[i]=std::atoi(planeLoadUnit->GetText());
//                planeLoadUnit=planeLoadUnit->NextSiblingElement();
//            }
//        }
//    }
//    
//    
//    kantai->kantaiKey=1;//////少一个kantaiKey
//    
//    kantai->fatigueValue=50;
//    
//    kantai->kantaiLock=false;
//    
//    kantai->kantaiStar=1;///这里引用固定的star函数
//    
//    kantai->kantaiState=Free;
//    
//    kantai->brokenType=normal;
//    
//    return kantai;
//    
    
}
