//
//  TimerMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/15/16.
//
//

#include "TimerMgr.hpp"
#include "arsenal.hpp"
#include "dock.hpp"
#include "Player.h"

NS_KCL_BEGIN


USING_NS_CC;

TimerMgr* TimerMgr::m_instance = nullptr;

#define TIMER_MGR_SCHEDULE "TimerMgrSchedule"


TimerMgr* TimerMgr::getInstance()
{
    if (!m_instance)
    {
        m_instance = new TimerMgr;
        if (!m_instance->init())
        {
            CC_SAFE_DELETE(m_instance);
        }
    }
    return m_instance;
}

bool TimerMgr::init()
{
    startTimer();
    return true;
}



TimerMgr::~TimerMgr()
{
    
}

void TimerMgr::delInstance()
{
    stopTimer();
    delete m_instance;
    m_instance=NULL;
}



void TimerMgr::startTimer()
{
    auto _scheduler = Director::getInstance()->getScheduler();
    _scheduler->unschedule(TIMER_MGR_SCHEDULE, this);
    _scheduler->schedule(CC_CALLBACK_1(TimerMgr::scheduleFunc, this), this, 1.f, false, TIMER_MGR_SCHEDULE);
}


void TimerMgr::stopTimer()
{
    Director::getInstance()->getScheduler()->unschedule(TIMER_MGR_SCHEDULE, this);
}

void TimerMgr::scheduleFunc(float dt)
{
    sArsenal.buildTimeCircle(dt);
    sDock.repairTimeCircle(dt);
}




NS_KCL_END