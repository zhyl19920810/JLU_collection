//
//  ListRow.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/5/16.
//
//

#ifndef ListRow_hpp
#define ListRow_hpp

#include "cocos2d.h"
#include "Player.h"
#include "SystemHeader.h"


USING_NS_CC;
#define FONT_COLOR Color3B::BLACK

class ListRow:public Node
{
public:
    static ListRow* create(int position)
    {
        ListRow* tmp=new(std::nothrow) ListRow;
        if (tmp&&tmp->init(position))
        {
            tmp->autorelease();
            return tmp;
        }
        delete tmp;
        tmp=NULL;
        return NULL;
    }
    ListRow();
    void setEnable(bool bVisible);
    bool init(int position);
    
    void update(Kantai* kantai);
private:
    virtual void exchangeCallback(cocos2d::Ref *pSender);
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


#endif /* ListRow_hpp */
