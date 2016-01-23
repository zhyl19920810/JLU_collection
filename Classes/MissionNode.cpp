//
//  MissionNode.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#include "MissionNode.h"
#include "XMLBuilder.h"


void split(const std::string& src, const std::string& separator, std::vector<std::string>& dest)
{
    std::string str = src;
    std::string substring;
    std::string::size_type start = 0, index;
    
    do
    {
        index = str.find_first_of(separator, start);
        if (index != std::string::npos)
        {
            substring = str.substr(start, index - start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator, index);
            if (start == std::string::npos) return;
        }
    } while (index != std::string::npos);
    
    //the last token
    substring = str.substr(start);
    dest.push_back(substring);
}




MissionNode::MissionNode()
{
    enemyFleet=nullptr;
}



void MissionNode::setType(const std::string& type)
{
    if (type=="enemy")
    {
        this->type=node_enemy;
    }
    else if(type=="boss")
    {
        this->type=node_boss;
    }
    else if(type=="item")
    {
        this->type=node_item;
    }
    else if(type=="home")
    {
        this->type=node_home;
    }
    else
    {
        this->type=node_empty;
    }
}

Fleet* MissionNode::parseEnemyFleet(const std::string &name)
{
//    std::vector<std::string> strings;
//    split(name, "#", strings); //split text in script by "#"
//    enemyFleet = new Fleet(-1);
//    for (int i = 0; i < strings.size(); i++)
//    {
////        ValueVector temp=XMLBuilder::readKantaiXML(std::atoi(strings[i].c_str()));
////        Kantai* _kantai=new Kantai(temp);
////        enemyFleet->addShipNoDatabase(_kantai);
//    }
//    return enemyFleet;
}
