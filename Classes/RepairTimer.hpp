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
USING_NS_CC;




class RepairTimer : public cocos2d::Node
{
public:
    static RepairTimer* create();
    bool init();
    virtual ~RepairTimer();
    void setTime(float time);
    void update(float delta);
    void convertTimeToChar(int time,char *name);
private:
    Label* label;
    float pTime;
};


#endif /* RepairTimeCounter_hpp */
