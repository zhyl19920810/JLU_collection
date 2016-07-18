//
//  SoundBar.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef SoundBar_hpp
#define SoundBar_hpp

#include "cocos2d.h"
#include "SystemHeader.h"



NS_KCL_BEGIN


enum SoundBarType
{
    BGM_SOUNDBAR,
    SE_SOUNDBAR,
    VOICE_SOUNDBAR
};





class SoundBar:public cocos2d::Node
{
public:
    static SoundBar* create(SoundBarType type);
    
    
private:
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    bool isVolumeZero(){return soundPercent<0.001;}
    
    
private:
    bool init(kancolle::SoundBarType type);
    
    
    cocos2d::EventListenerTouchOneByOne* listener;
    SoundBarType type;
    cocos2d::Sprite* displayBar;
    float soundPercent;
    cocos2d::Sprite* adjustButton;
    
    
};

NS_KCL_END


#endif /* SoundBar_hpp */
