//
//  TitlePic.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/3/16.
//
//

#ifndef TitlePic_hpp
#define TitlePic_hpp

#include "SystemHeader.h"
#include "cocos2d.h"
#include "ViewMgrMacro.hpp"


NS_KCL_BEGIN

class TitlePic:public cocos2d::Node
{
public:
    static TitlePic* create();
    
    void changeTitlePic(kancolle::PanelType type,float delayTime);
    
    void changeAction(float delayTime);
    
    
private:
    bool init();
    
    cocos2d::Sprite* fadeCover;
    cocos2d::Sprite* preTitle;
    cocos2d::Sprite* title;
    PanelType currType;
};









NS_KCL_END

#endif /* TitlePic_hpp */
