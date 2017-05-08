//
//  ViewMgrMacro.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#ifndef ViewMgrMacro_hpp
#define ViewMgrMacro_hpp

#include "SystemHeader.h"

NS_KCL_BEGIN

enum class SceneType
{
    HOME=1001,
    LOGIN,
    SALLY,
    BATTLE,
    
    
    
    MAX
};


enum class PanelType
{
    NONE=0,
    PORT_SUPPLY=1001,
    PORT_REMODE,
    PORT_FACTORY,
    PORT_ORGANIZE,
    PORT_REPAIR,
    PORT_MAINLAYER,
    PORT_BATTLE,
    SALLY_MAIN,
    BATTLE_MAIN,
    
    SOUND=2001
};


NS_KCL_END


#endif /* ViewMgrMacro_hpp */
