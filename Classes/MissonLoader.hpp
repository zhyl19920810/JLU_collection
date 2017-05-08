//
//  MissonLoader.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/7/17.
//
//

#ifndef MissonLoader_hpp
#define MissonLoader_hpp

#include "SystemHeader.h"
#include "Misson.hpp"
#include "tinyxml2/tinyxml2.h"
#include "BattleCharacterInfo.hpp"


NS_KCL_BEGIN

enum ScriptType
{
    characterInfo,
    strings,
    equipment,
    mission
};


USING_NS_CC;

class MissonLoader
{
public :
    static MissonLoader* getInstance()
    {
        if (instance == NULL)
            instance = new MissonLoader();
        return instance;
    }
    Mission*               LoadMissionInfo(std::string id);
    BattleCharacterInfo*   LoadCharacterInfo(std::string id);
    std::string GetStringByName(std::string name);
    
    
private:
    MissonLoader();
    static MissonLoader *instance;
    //tinyxml2::XMLDocument missionDoc;
    tinyxml2::XMLDocument missionDoc;
    tinyxml2::XMLElement* FindNodeByName(std::string name, ScriptType type);
};


NS_KCL_END


#endif /* MissonLoader_hpp */
