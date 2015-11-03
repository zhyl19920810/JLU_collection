//
//  Mission.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#ifndef __kancolle_alpha__Mission__
#define __kancolle_alpha__Mission__

#include "cocos2d.h"
#include "MissionNode.h"

class Mission
{
public:
    Mission(){}
    
    std::string id;
    
    int areaId;
    
    int index;
    
    std::string name;
    
    std::string missionName;
    
    std::string detail;
    
    std::vector<MissionNode*> nodes;
};

#endif /* defined(__kancolle_alpha__Mission__) */
