//
//  EventPauseGuard.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/31/16.
//
//

#include "EventPauseGuard.hpp"
#include "cocos2d.h"


NS_KCL_BEGIN



int EventPauseGuard::_count=0;

void EventPauseGuard::resume()
{
    --_count;
    if (_count==0)
    {
        auto scene=cocos2d::Director::getInstance()->getRunningScene();
        cocos2d::Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(scene,true);  
    }
}



void EventPauseGuard::pause()
{
    if (_count==0)
    {
        auto scene=cocos2d::Director::getInstance()->getRunningScene();
        cocos2d::Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(scene,true);
    }
    ++_count;
}






NS_KCL_END