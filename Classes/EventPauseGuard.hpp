//
//  EventPauseGuard.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/31/16.
//
//

#ifndef EventPauseGuard_hpp
#define EventPauseGuard_hpp

#include "SystemHeader.h"

NS_KCL_BEGIN

class EventPauseGuard
{
public:
    static void resume();
    static void pause();
    
private:
    static int _count;
    
};



NS_KCL_END

#endif /* EventPauseGuard_hpp */
