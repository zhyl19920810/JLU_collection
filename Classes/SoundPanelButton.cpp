//
//  SoundPanelButton.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/19/16.
//
//

#include "SoundPanelButton.hpp"


NS_KCL_BEGIN

USING_NS_CC;

bool SoundPanelButton::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        button=MenuItemSprite::create(Sprite::create(""), Sprite::create(""), CC_CALLBACK_1(SoundPanelButton::intoCallback, this));
        button->setPosition(Vec2::ZERO);
        addChild(button);
        
        bRet=true;
    }while(0);
    return bRet;
}

void SoundPanelButton::intoCallback(cocos2d::Ref *ref)
{
    
}





NS_KCL_END