//
//  HpBar.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef HpBar_hpp
#define HpBar_hpp

#include "cocos2d.h"
using namespace cocos2d;

class HpBar :public Node{
public:
    HpBar(int maxHp, int currentHp);
    void setCurrentHp(int currentHp);
    void setHp(int maxHp, int currentHp);
private:
    int maxHp;
    int currentHp;
    Sprite * bar;
};

#endif /* HpBar_hpp */
