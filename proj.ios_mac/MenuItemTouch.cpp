//
//  MenuItemTouch.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/3/16.
//
//

#include "MenuItemTouch.hpp"


MenuItemButton* MenuItemButton::create(cocos2d::Node *normalSprite, cocos2d::Node *selectedSprite, cocos2d::Node *coverSprite, const ccMenuCallback &callback)
{
    MenuItemButton* tmp=new(std::nothrow) MenuItemButton;
    if (tmp&&tmp->init(normalSprite,selectedSprite,coverSprite,callback))
    {
        tmp->autorelease();
        return tmp;
    }
    delete tmp;
    tmp=NULL;
    return NULL;
}

bool MenuItemButton::init(cocos2d::Node *normalSprite, cocos2d::Node *selectedSprite, cocos2d::Node *coverSprite, const ccMenuCallback &callback)
{
    if (!Node::init())
    {
        return false;
    }
    button=MenuItemSprite::create(normalSprite, selectedSprite, callback);
    button->setPosition(Vec2::ZERO);
    Menu* mn=Menu::create();
    mn->addChild(button);
    mn->setPosition(Vec2::ZERO);
    addChild(mn);
    
    buttonUp=coverSprite;
    buttonUp->setPosition(Vec2::ZERO);
    addChild(buttonUp);
    return true;
}

void MenuItemButton::setButtonVisible(bool bVisible)
{
    button->setVisible(bVisible);
    buttonUp->setVisible(!bVisible);
}