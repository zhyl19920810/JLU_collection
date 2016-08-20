//
//  RepairTimeCounter.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "TimerEntity.hpp"
#include "TimeUtil.hpp"


NS_KCL_BEGIN

TimerEntity::~TimerEntity()
{
    
}


TimerEntity* TimerEntity::create(FinishCallback callback)
{
    TimerEntity* pRet=new TimerEntity;
    if (pRet&&pRet->init(callback))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool TimerEntity::init(FinishCallback callback)
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!Node::create());
        remainTime=0;
        state=TimerState::FREE;
        this->callback=callback;
        
        label = Label::create("","fonts/DengXian.ttf",20);
        label->setPosition(0,0);
        label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        label->setColor(Color3B::BLACK);
        addChild(label);
        scheduleUpdate();
        
        Director::getInstance()->getEventDispatcher()->addCustomEventListener("updateTimestamp", [this](EventCustom* event)
        {
              if (state==TimerState::CONUTDOWN)
              {
                   remainTime=static_cast<float>(completeTime-TimeUtil::getTimestamp());
                  update(0.0);
               }
         });
        
        bRet=true;
    }while(0);
    return bRet;
}



void TimerEntity::setTime(int64_t completeTime)
{
    state=TimerState::CONUTDOWN;
    this->completeTime=completeTime;
    remainTime=static_cast<float>(completeTime-TimeUtil::getTimestamp());
    if (remainTime<=0)  remainTime=0;
}

void TimerEntity::update(float delta)
{
    if (state==TimerState::FREE||state==TimerState::FINISH) return;
    
    remainTime-=delta;
    if (remainTime<=0.0) remainTime=0.0;
    char l_time[30];
    bzero(l_time, sizeof(l_time));
    convertTimeToChar(remainTime, l_time);
    label->setString(l_time);
    
    if (remainTime==0.0)
    {
        state=TimerState::FINISH;
        if (callback) callback();
    }
}

void TimerEntity::convertTimeToChar(int time,char *name)
{
    char tmp[10];
    bzero(name, sizeof(name));
    int hour,minutes,second;
    hour=time/3600;
    if (!hour)
    {
        sprintf(name, "00:");
    }
    else if(hour<10)
    {
        sprintf(name, "0%d:",hour);
    }
    else
    {
        sprintf(name, "%d:",hour);
    }
    
    time=time%3600;
    minutes=time/60;
    if (!minutes)
    {
        strcat(name, "00:");
    }
    else if (minutes<10)
    {
        sprintf(tmp, "0%d:",minutes);
        strcat(name, tmp);
    }
    else
    {
        sprintf(tmp, "%d:",minutes);
        strcat(name, tmp);
    }
    
    time=time%60;
    second=time;
    if (!second)
    {
        strcat(name, "00");
    }
    else if (second<10)
    {
        sprintf(tmp, "0%d",second);
        strcat(name, tmp);
    }
    else
    {
        sprintf(tmp, "%d",second);
        strcat(name, tmp);
    }
}


void TimerEntity::setState(kancolle::TimerEntity::TimerState _state)
{
    if (_state==TimerState::FINISH||_state==TimerState::FREE)
    {
        remainTime=0.0;
        this->state=_state;
    }
}


NS_KCL_END
