//
//  SoundPanel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "SoundPanel.hpp"
#include "SoundBar.hpp"



NS_KCL_BEGIN

USING_NS_CC;

bool SoundPanel::init()
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!Panel::init());
        
        auto SoundBg=Sprite::create("PortMain/image 57.png");
        SoundBg->setPosition(Vec2::ZERO);//改
        addChild(SoundBg);
        
        bgmSoundBar=SoundBar::create(SoundBarType::BGM_SOUNDBAR);
        bgmSoundBar->setPosition(Vec2::ZERO);//改
        SoundBg->addChild(bgmSoundBar);
        
        SESoundBar=SoundBar::create(SoundBarType::SE_SOUNDBAR);
        SESoundBar->setPosition(Vec2::ZERO);//改
        SoundBg->addChild(SESoundBar);
        
        voiceSoundBar=SoundBar::create(SoundBarType::VOICE_SOUNDBAR);
        voiceSoundBar->setPosition(Vec2::ZERO);//改
        SoundBg->addChild(voiceSoundBar);
        
        sceneButton=MenuItemSprite::create(Sprite::create(), Sprite::create(), CC_CALLBACK_1(SoundPanel::sceneCallback, this));
        sceneButton->setPosition(Vec2::ZERO);
        addChild(sceneButton);
        
        bRet=true;
    }while(0);
    
    
    return bRet;
    
    
}


void SoundPanel::sceneCallback(cocos2d::Ref *ref)
{
    
}





NS_KCL_END