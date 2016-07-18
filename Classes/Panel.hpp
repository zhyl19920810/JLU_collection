//
//  Panel.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef Panel_hpp
#define Panel_hpp

#include "cocos2d.h"
#include "SystemHeader.h"


NS_KCL_BEGIN


class SoundBar;



class Panel:public cocos2d::Layer
{
public:
    CREATE_FUNC(Panel);
    
    virtual bool init() override;
    
    
private:
    SoundBar* bgmSoundBar;
    SoundBar* SESoundBar;
    SoundBar* VocSoundBar;
};


NS_KCL_END





#endif /* Panel_hpp */
