//
//  RepairTimeCounter.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "RepairTimer.hpp"


RepairTimer::~RepairTimer()
{

}

RepairTimer* RepairTimer::create()
{
    RepairTimer* pRet=new RepairTimer;
    if (pRet&&pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool RepairTimer::init()
{
    pTime=0;
    label = Label::create("","fonts/DengXian.ttf",20);
    label->setPosition(0,0);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label->setColor(Color3B::BLACK);
    addChild(label);    
    return true;
}


void RepairTimer::setTime(float time)
{
    if (pTime)
    {
        return;
    }
    pTime = time;
    schedule(schedule_selector(RepairTimer::update));
}

void RepairTimer::update(float delta)
{
    pTime -= delta;
    char l_time[30];
    bzero(l_time, sizeof(l_time));
    convertTimeToChar(pTime, l_time);
    label->setString(l_time);
}

void RepairTimer::convertTimeToChar(int time,char *name)
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
