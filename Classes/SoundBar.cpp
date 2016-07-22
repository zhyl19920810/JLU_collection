//
//  SoundBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "SoundBar.hpp"
#include "Sound.hpp"

NS_KCL_BEGIN

USING_NS_CC;




bool SoundBar::init(kancolle::SoundBarType _type)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        type=_type;
        
        displayBg=Sprite::create("PortMain/image 59.png");
        displayBg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        addChild(displayBg);
        Node::setContentSize(displayBg->getContentSize());
        
        displayBar=Sprite::create("PortMain/image 59.png");
        displayBar->setColor(Color3B::GREEN);
        displayBar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        addChild(displayBar);

        
        switch (_type)
        {
            case BGM_SOUNDBAR:
                soundPercent=UserDefault::getInstance()->getFloatForKey(BGM_VOLUME, 0.5);
                break;
            case SE_SOUNDBAR:
                soundPercent=UserDefault::getInstance()->getFloatForKey(SE_VOLUME, 0.5);
                break;
            case VOICE_SOUNDBAR:
                soundPercent=UserDefault::getInstance()->getFloatForKey(VOICE_VOLUME, 0.5);
                break;
            default:
                break;
        }
        
        adjustButton=Sprite::create("PortMain/image 71.png");
        adjustButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        Vec2 _adjustButtonVec=Vec2(displayBar->getContentSize().width*(soundPercent), displayBar->getContentSize().height*0.5);
        adjustButton->setPosition(_adjustButtonVec);
        addChild(adjustButton,2);
        
        
        listener=cocos2d::EventListenerTouchOneByOne::create();
        listener->onTouchBegan=CC_CALLBACK_2(SoundBar::onTouchBegan, this);
        listener->onTouchMoved=CC_CALLBACK_2(SoundBar::onTouchMoved, this);
        listener->onTouchEnded=CC_CALLBACK_2(SoundBar::onTouchEnded, this);
        auto dispatcher=Director::getInstance()->getEventDispatcher();
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        soundMuteIcon=SoundMuteIcon::create(soundPercent);
        soundMuteIcon->setPosition(Vec2(displayBar->getContentSize().width*(0)-10, displayBar->getContentSize().height/2));
        addChild(soundMuteIcon);
        updateVolume();
        
        
        
        bRet=true;
    }while (0);
        
    
    return bRet;
}

void SoundBar::updateVolume()
{
    switch (type)
    {
        case BGM_SOUNDBAR:
            SND->setBGVolume(soundPercent);
            UserDefault::getInstance()->setFloatForKey(BGM_VOLUME, soundPercent);
            break;
        case SE_SOUNDBAR:
            SND->setEffectVolume(soundPercent);
            UserDefault::getInstance()->setFloatForKey(SE_VOLUME, soundPercent);
            break;
        default:
            break;
    }
    displayBar->setScaleX(soundPercent);
    soundMuteIcon->updateVolume(soundPercent);
}





bool SoundBar::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location=touch->getLocation();
    auto loc=adjustButton->convertToNodeSpace(location);
    auto rect=Rect(-20,-20,adjustButton->getContentSize().width+20,adjustButton->getContentSize().height+20);
    isPress=false;
    if (rect.containsPoint(loc))
    {
        isPress=true;
        
        
        return true;
    }
    return false;
}

void SoundBar::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!isPress) return;
    auto location=touch->getLocation();
    auto loc=adjustButton->convertToNodeSpace(location);
    auto rect=Rect(-20,-20,adjustButton->getContentSize().width+20,adjustButton->getContentSize().height+20);
    
    if (rect.containsPoint(loc))
    {
        auto _displayBarLoc=displayBg->convertToNodeSpace(location);
        auto _displayBarWidth=displayBg->getContentSize().width;
        float modifyX=fmax(0,fmin(_displayBarLoc.x,_displayBarWidth));
        adjustButton->setPositionX(modifyX);
        float newSoundPercent=modifyX/_displayBarWidth;
        if (newSoundPercent-soundPercent<-0.001||newSoundPercent-soundPercent>0.001)
        {
            soundPercent=newSoundPercent;
            displayBar->setScaleX(soundPercent);
            soundMuteIcon->updateVolume(soundPercent);
        }
    }
    else
    {
        isPress=false;
    }
    
}

void SoundBar::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    updateVolume();
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

////------------------------------------------------------------------------------------------------------------

SoundMuteIcon* SoundMuteIcon::create(float soundPercent)
{
    SoundMuteIcon* pRet=new SoundMuteIcon;
    if (pRet&&pRet->init(soundPercent))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}


bool SoundMuteIcon::init(float volume)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        icon=Sprite::create("PortMain/image 68.png");
        icon->setPosition(Vec2(-14, 0));
        addChild(icon);
        
        updateVolume(volume);
        
        bRet=true;
    }while(0);
    return bRet;
}

void SoundMuteIcon::updateVolume(float volume)
{
    if (isVolumeZero(volume))
    {
        icon->setTexture("PortMain/image 68.png");
    }
    else
    {
        icon->setTexture("PortMain/image 66.png");
    }
}



NS_KCL_END