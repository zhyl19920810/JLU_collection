//
//  RepairHpBar.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#ifndef RepairHpBar_hpp
#define RepairHpBar_hpp

#include "cocos2d.h"


USING_NS_CC;

class RepairHpBar:public Node
{
public:
    RepairHpBar(int maxHp,int currentHp);
    void setCurrHp(int currentHp);
    void setHp(int maxHp,int currentHp);
private:
    float maxHp;
    float currentHp;
    Sprite* bg;
    Sprite* bar;
    Sprite* barBg;
};

#endif /* RepairHpBar_hpp */
