//
//  XMLParser.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/23/15.
//
//

#include "XMLParser.h"



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