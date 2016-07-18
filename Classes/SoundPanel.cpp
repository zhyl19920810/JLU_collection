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
        
        bgmSoundBar=SoundBar::create();
        
        
        
        bRet=true;
    }while(0);
    
    
    return bRet;
    
    
}






NS_KCL_END