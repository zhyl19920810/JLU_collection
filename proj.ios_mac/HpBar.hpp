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
#include "SystemHeader.h"

using namespace cocos2d;

NS_KCL_BEGIN

class HpBar :public Node{
public:
    static HpBar* create()
    {
        HpBar* tmp=new(std::nothrow) HpBar;
        if (tmp&&tmp->init())
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    bool init();
    HpBar();
    void setCurrentHp(int currentHp);
    void setHp(int maxHp, int currentHp);
private:
    int maxHp;
    int currentHp;
    Sprite * bar;
};

NS_KCL_END

#endif /* HpBar_hpp */
