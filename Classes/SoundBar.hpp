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


class SoundMuteIcon;


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
    
    void updateVolume();
    
    cocos2d::EventListenerTouchOneByOne* listener;
    SoundBarType type;
    cocos2d::Sprite* displayBar;
    cocos2d::Sprite* displayBg;
    float soundPercent;
    cocos2d::Sprite* adjustButton;
    
    bool isPress;
    
private:
    SoundMuteIcon* soundMuteIcon;
};


class SoundMuteIcon:public cocos2d::Node
{
public:
    static SoundMuteIcon* create(float volume);
    
    void updateVolume(float volume);
private:
    bool isVolumeZero(float volume){return volume<0.001;}
    bool init(float soundPercent);
    
private:
    cocos2d::Sprite* icon;
};

NS_KCL_END


#endif /* SoundBar_hpp */
