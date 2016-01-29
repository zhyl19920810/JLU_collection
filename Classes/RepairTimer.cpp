//
//  RepairTimeCounter.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "RepairTimer.hpp"


ReapirTimer::~ReapirTimer()
{

}

ReapirTimer* ReapirTimer::create(float time)
{
    ReapirTimer* pRet=new ReapirTimer;
    if (pRet&&pRet->init(time))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool ReapirTimer::init(float time)
{
    pTime = time;
    
    label = Label::create();
    label->setPosition(0,0);
    addChild(label);
    
    schedule(schedule_selector(ReapirTimer::update));
    
    return true;
}
void ReapirTimer::update(float delta)
{
    pTime -= delta;
    char* mtime = new char[10];
    //此处只是显示分钟数和秒数  自己可以定义输出时间格式
    sprintf(mtime,"%d : %d",(int)pTime/60,(int)pTime%60);
    label->setString(mtime);
}

