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

bool SoundPanelButton::init(soundButtonCallBack _callback)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        callback=_callback;
        button=MenuItemSprite::create(Sprite::create("PortMain/image 81.png"), Sprite::create("PortMain/image 81.png"), CC_CALLBACK_1(SoundPanelButton::intoCallback, this));
        button->setPosition(Vec2::ZERO);
        Menu* mn=Menu::create();
        mn->setPosition(Vec2::ZERO);
        mn->addChild(button);
        addChild(mn);
        
        
        bRet=true;
    }while(0);
    return bRet;
}

void SoundPanelButton::intoCallback(cocos2d::Ref *ref)
{
    callback();
}


SoundPanelButton* SoundPanelButton::create(soundButtonCallBack _callback)
{
    static SoundPanelButton* pRet=new SoundPanelButton;
    if (pRet&&pRet->init(_callback))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}



NS_KCL_END