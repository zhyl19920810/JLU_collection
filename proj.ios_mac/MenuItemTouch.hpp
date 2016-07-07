//
//  MenuItemTouch.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/3/16.
//
//

#ifndef MenuItemTouch_hpp
#define MenuItemTouch_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

USING_NS_CC;

class MenuItemButton:public Node
{
public:
    static MenuItemButton* create(Node* normalSprite, Node* selectedSprite,Node* coverSprite, const ccMenuCallback& callback);
    
    bool init(Node* normalSprite, Node* selectedSprite,Node* coverSprite, const ccMenuCallback& callback);
    void setButtonVisible(bool bVisible);
    
private:
    MenuItem* button;
    Node* buttonUp;
};



NS_KCL_END



#endif /* MenuItemTouch_hpp */
