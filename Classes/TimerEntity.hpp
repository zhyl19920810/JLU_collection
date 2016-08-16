//
//  RepairTimeCounter.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#ifndef RepairTimeCounter_hpp
#define RepairTimeCounter_hpp

#include "cocos2d.h"
#include "HpBar.hpp"
#include "SystemHeader.h"

USING_NS_CC;


NS_KCL_BEGIN

class TimerEntity : public cocos2d::Node
{
    typedef std::function<void()> FinishCallback;
public:
    enum TimerState{FREE,CONUTDOWN,FINISH};
    
    static TimerEntity* create(FinishCallback callback);
    bool init(FinishCallback callback);
    virtual ~TimerEntity();
    void setTime(int64_t time);
    void update(float delta);
    void convertTimeToChar(int time,char *name);
    
    void setState(TimerState state);
    void updateTimer(int64_t time);
private:
    FinishCallback callback;
    int64_t completeTime;
    float remainTime;
    TimerState state;
    Label* label;
};


NS_KCL_END

#endif /* RepairTimeCounter_hpp */
