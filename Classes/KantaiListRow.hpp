//
//  KantaiListRow.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef KantaiListRow_hpp
#define KantaiListRow_hpp

#include "cocos2d.h"
#include "Player.h"
#include "SystemHeader.h"


USING_NS_CC;
#define FONT_COLOR Color3B::BLACK

class KantaiListRow:public Node
{
public:
    static KantaiListRow* create(int position)
    {
        KantaiListRow* tmp=new(std::nothrow) KantaiListRow;
        if (tmp&&tmp->init(position))
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    KantaiListRow();
    void setEnable(bool bVisible);
    bool init(int position);
    
    void update(Kantai* kantai);
private:
    void exchangeCallback(cocos2d::Ref *pSender);
    void lockCallback(Ref* pSender);
    int position;
    Sprite* line;
    Sprite* fleetIcon;
    Label* kantaiName;
    Label* level;
    Label* maxHP;
    Label* firePower;
    Label* torpedo;
    Label* antiAir;
    Sprite* speed;
    MenuItemSprite* menuItem;
    MenuItemToggle* lockIcon;
    Kantai* kantai;
};

#endif /* KantaiListRow_hpp */
