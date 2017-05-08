//
//  SoundPanel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "SoundPanel.hpp"
#include "SoundBar.hpp"
#include "LayerCover.hpp"

NS_KCL_BEGIN


USING_NS_CC;

bool SoundPanel::init()
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!Panel::init());
        
        listCover=LayerCover::create(CC_CALLBACK_1(SoundPanel::sceneCallback, this));
        listCover->setPosition(0,0);
        addChild(listCover);
        listCover->setCoverEnable(true);
        
        auto SoundBg=Sprite::create("PortMain/image 57.png");
        auto winSize=Director::getInstance()->getWinSize();
        SoundBg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
        SoundBg->setPosition(Vec2(winSize.width-20, 25));//改
        addChild(SoundBg);
        
        bgmSoundBar=SoundBar::create(SoundBarType::BGM_SOUNDBAR);
        bgmSoundBar->setPosition(Vec2(50, 202));
        bgmSoundBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        SoundBg->addChild(bgmSoundBar);
        
        SESoundBar=SoundBar::create(SoundBarType::SE_SOUNDBAR);
        SESoundBar->setPosition(Vec2(50, 140));
        SESoundBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        SoundBg->addChild(SESoundBar);
        
        voiceSoundBar=SoundBar::create(SoundBarType::VOICE_SOUNDBAR);
        voiceSoundBar->setPosition(Vec2(50, 75));
        voiceSoundBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        SoundBg->addChild(voiceSoundBar);
        
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}


void SoundPanel::sceneCallback(cocos2d::Ref *ref)
{
    
}





NS_KCL_END
