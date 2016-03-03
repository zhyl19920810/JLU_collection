//
//  ValueBar.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/3/16.
//
//

#ifndef ValueBar_hpp
#define ValueBar_hpp

#include "cocos2d.h"
USING_NS_CC;

class ValueBar:public Node
{
public:
    static ValueBar* create()
    {
        ValueBar* tmp=new(std::nothrow) ValueBar;
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
    void update(int value);
    
    ValueBar();
    void setVisible(bool visible);
private:
    Sprite* barPic;
    int value;
};



#endif /* ValueBar_hpp */
