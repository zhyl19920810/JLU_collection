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

NS_KCL_BEGIN

class SoundPanelButton:public cocos2d::Node
{
public:
    CREATE_FUNC(SoundPanelButton);
    
    void intoCallback(Ref*);
    bool init();
private:
    cocos2d::MenuItem* button;
};




NS_KCL_END

#endif /* SoundPanelButton_hpp */
