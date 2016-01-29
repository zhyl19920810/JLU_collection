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




class ReapirTimer : public cocos2d::Node
{
public:
    static ReapirTimer* create(float time);
    bool init(float time);
    virtual ~ReapirTimer();
    void update(float delta);
    
private:
    Label* label;
    double pTime;
};


#endif /* RepairTimeCounter_hpp */
