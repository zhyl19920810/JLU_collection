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
#include "TimeUtil.hpp"


NS_KCL_BEGIN


USING_NS_CC;

TimerMgr* TimerMgr::m_instance = nullptr;

#define TIMER_MGR_SCHEDULE "TimerMgrSchedule"
#define ATTR_COUNTDOWN 20.0

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
    _lastSaveAttrTimestamp=UserDefault::getInstance()->getIntegerForKey("lastSaveAttrTimestamp");
    auto ts=TimeUtil::getTimestamp();
    uint64_t timeDiff=ts-_lastSaveAttrTimestamp;
    int numAttrAdd=timeDiff/ATTR_COUNTDOWN;
    totalSecond=timeDiff-numAttrAdd*ATTR_COUNTDOWN;
    sPlayer.addAttr(0.0, numAttrAdd);
    
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
    _scheduler->schedule(CC_CALLBACK_1(TimerMgr::scheduleFunc, this), this, 0.f, false, TIMER_MGR_SCHEDULE);
}


void TimerMgr::stopTimer()
{
    Director::getInstance()->getScheduler()->unschedule(TIMER_MGR_SCHEDULE, this);
}

void TimerMgr::scheduleFunc(float dt)
{
    sArsenal.buildTimeCircle(dt);
    sDock.repairTimeCircle(dt);
    addAttr(dt);
}

void TimerMgr::addAttr(float dt)
{
    totalSecond+=dt;
    if (totalSecond>=ATTR_COUNTDOWN)
    {
        totalSecond-=ATTR_COUNTDOWN;
        sPlayer.addAttr(dt,1);
        _lastSaveAttrTimestamp=TimeUtil::getTimestamp();
        UserDefault::getInstance()->setIntegerForKey("lastSaveAttrTimestamp", _lastSaveAttrTimestamp);
    }
}


void TimerMgr::enterForeGround()
{
    _lastSaveAttrTimestamp=UserDefault::getInstance()->getIntegerForKey("lastSaveAttrTimestamp");
    uint64_t timeDiff=TimeUtil::getTimestamp()-_lastSaveAttrTimestamp;
    int numAttrAdd=timeDiff/ATTR_COUNTDOWN;
    totalSecond=timeDiff-numAttrAdd*ATTR_COUNTDOWN;
    
    sPlayer.addAttr(0.0, numAttrAdd);
}


NS_KCL_END