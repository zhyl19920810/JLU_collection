//
//  SoundPanelButton.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/19/16.
//
//

#ifndef SoundPanelButton_hpp
#define SoundPanelButton_hpp

#include "cocos2d.h"
#include "SystemHeader.h"
#include "ViewMgrMacro.hpp"

NS_KCL_BEGIN


typedef std::function<void()> soundButtonCallBack;

class SoundPanelButton:public cocos2d::Node
{
public:
    static SoundPanelButton* create(soundButtonCallBack);
    
    void intoCallback(Ref*);
    bool init(soundButtonCallBack);
    ~SoundPanelButton();
private:
    bool SoundPanelOpen;
    cocos2d::MenuItem* button;
    soundButtonCallBack callback;
};




NS_KCL_END

#endif /* SoundPanelButton_hpp */
