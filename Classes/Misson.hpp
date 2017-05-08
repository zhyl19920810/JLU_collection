//
//  Misson.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#ifndef Misson_hpp
#define Misson_hpp

#include "SystemHeader.h"
#include "MissionNode.hpp"


NS_KCL_BEGIN

USING_NS_CC;


class Mission:public Ref
{
    friend class SallyInfo;
    
public:
    static Mission* create();
    bool init();
    virtual ~Mission();
    MissionNode* getNextNode();
    
    std::string id;
    int areaId;
    int index;
    std::string name;
    std::string missionName;
    std::string detail;
    std::vector<MissionNode*> nodes;
    
};


NS_KCL_END


#endif /* Misson_hpp */
