//
//  SoundBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "SoundBar.hpp"

NS_KCL_BEGIN

USING_NS_CC;

#define BGM_VOLUME     "bgm_volume"
#define SE_VOLUME      "se_volume"
#define VOICE_VOLUME   "voice_volume"


bool SoundBar::init(kancolle::SoundBarType _type)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        type=_type;
        
        
        listener=cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan=CC_CALLBACK_2(SoundBar::onTouchBegan, this);
        listener->onTouchMoved=CC_CALLBACK_2(SoundBar::onTouchMoved, this);
        listener->onTouchEnded=CC_CALLBACK_2(SoundBar::onTouchEnded, this);
        auto dispatcher=Director::getInstance()->getEventDispatcher();
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        switch (type)
        {
            case BGM_SOUNDBAR:
                soundPercent=UserDefault::getInstance()->getFloatForKey(BGM_VOLUME);
                break;
            case SE_SOUNDBAR:
                soundPercent=UserDefault::getInstance()->getFloatForKey(SE_VOLUME);
                break;
            case VOICE_SOUNDBAR:
                soundPercent=UserDefault::getInstance()->getFloatForKey(VOICE_VOLUME);
                break;
            default:
                break;
        }
        
        
        
        
        bRet=true;
    }while (0);
        
    
    return bRet;
}

bool SoundBar::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location=touch->getLocation();
    auto loc=adjustButton->convertToNodeSpace(location);
    auto rect=Rect(0,0,adjustButton->getContentSize().width,adjustButton->getContentSize().height);
    if (rect.containsPoint(loc))
    {
        return true;
    }
    return false;
}

void SoundBar::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void SoundBar::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}


SoundBar* SoundBar::create(kancolle::SoundBarType type)
{
    SoundBar* pRet=new SoundBar;
    if (pRet&&pRet->init(type))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


NS_KCL_END