//
//  TimerMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/15/16.
//
//

#ifndef TimerMgr_hpp
#define TimerMgr_hpp

#include "SystemHeader.h"
#include "cocos2d.h"

NS_KCL_BEGIN

#define TIMER_MGR (TimerMgr::getInstance())


class TimerMgr
{
public:
    static TimerMgr* getInstance();
    void delInstance();
    
    void startTimer();
    void stopTimer();
    
    ~TimerMgr();
private:
    void scheduleFunc(float dt);
    static TimerMgr* m_instance;
    bool init();
};









NS_KCL_END


#endif /* TimerMgr_hpp */
