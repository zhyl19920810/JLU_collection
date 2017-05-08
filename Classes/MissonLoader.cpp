//
//  MissonLoader.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/7/17.
//
//

#include "MissonLoader.hpp"
#include "BattleCharacterInfo.hpp"
#include "Compass.hpp"
#include <string>


NS_KCL_BEGIN


MissonLoader* MissonLoader::instance=NULL;

void MissonLoader::parse()
{
    ssize_t bufferSize = 0;
    
    std::string xmlFile4 = FileUtils::getInstance()->fullPathForFilename("Data/Mission.xml").c_str();
    unsigned char* pBuffer4 = FileUtils::sharedFileUtils()->getFileData(xmlFile4.c_str(), "rb", &bufferSize);
    missionDoc.Parse((const char*)pBuffer4);
}

void MissonLoader::delInstance()
{
    delete instance;
}

MissonLoader::MissonLoader()
{
    
}

bool MissonLoader::init()
{
    bool bRet=false;
    do
    {
        parse();
        bRet=true;
    }while(0);
    
    return bRet;
}








Mission* MissonLoader::LoadMissionInfo(std::string id)
{
    auto mission =Mission::create();
    
    tinyxml2::XMLElement *node = FindNodeByName(id, ScriptType::mission);
    if (node != NULL)
    {
        mission->id = id;
        mission->areaId = atoi( node->FirstChildElement("area")->GetText());
        mission->index = atoi(node->FirstChildElement("index")->GetText());
        mission->name = node->FirstChildElement("name")->GetText();
        mission->missionName = node->FirstChildElement("missionName")->GetText();
        mission->detail = node->FirstChildElement("Detail")->GetText();
        
        //MissionNode
        tinyxml2::XMLElement *missionnode = node->FirstChildElement("Node");
        while (missionnode != NULL)
        {
            auto newMissionNode =MissionNode::create();
            newMissionNode->SetType(missionnode->FirstChildElement("type")->GetText());
            newMissionNode->position =
            Point(atoi(missionnode->FirstChildElement("positionX")->GetText()),
                  atoi(missionnode->FirstChildElement("positionY")->GetText()));
            tinyxml2::XMLElement *directionNode = missionnode->FirstChildElement("direction");
            if (directionNode != NULL)
                newMissionNode->compassDirection = Compass::parseDirection(directionNode->GetText());
            tinyxml2::XMLElement *enemyFleetNode= missionnode->FirstChildElement("enemy");
            if (enemyFleetNode != NULL)
                newMissionNode->ParseEnemyFleet(enemyFleetNode->GetText());
            int parentIndex = atoi(missionnode->FirstChildElement("parent")->GetText());
            if (parentIndex != -1)
                mission->nodes[parentIndex]->m_vChildren.push_back(newMissionNode);
            mission->nodes.push_back(newMissionNode);
            missionnode = missionnode->NextSiblingElement();
            
        }
        
    }
    return mission;
}
tinyxml2::XMLElement* MissonLoader::FindNodeByName(std::string name, ScriptType type)
{
    const char* nodeName;
    tinyxml2::XMLDocument* doc;
    std::string nameOrId = "name";
    switch (type)
    {
//        case ScriptType::characterInfo:
//            nodeName = "Character";
//            doc = &this->characterDoc;
//            break;
//        case ScriptType::strings:
//            nodeName = "String";
//            doc = &this->stringsDoc;
//            break;
//        case ScriptType::equipment:
//            nodeName = "Equipment";
//            doc = &this->equipmentDoc;
//            nameOrId = "id";
//            break;
        case ScriptType::mission:
            nodeName = "Mission";
            doc = &this->missionDoc;
            nameOrId = "id";
        default:
            break;
    }
    tinyxml2::XMLElement *root = doc->RootElement();
    tinyxml2::XMLElement *node = root->FirstChildElement(nodeName);
    while (node)
    {
        const char* tempName = node->FirstChildElement(nameOrId.c_str())->GetText();
        if (name == tempName)
            return node;
        node = node->NextSiblingElement();
    }
    return NULL;
}

std::string MissonLoader::GetStringByName(std::string name)
{
    std::string string="";
    tinyxml2::XMLElement *node = FindNodeByName(name, strings);
    if (node != NULL)
    {
        string = node->FirstChildElement("context")->GetText();
    }
    return string;
}


BattleCharacterInfo* MissonLoader::LoadCharacterInfo(std::string id)
{
    BattleCharacterInfo* info=BattleCharacterInfo::create(atoi(id.c_str()));
    return info;
}


NS_KCL_END


