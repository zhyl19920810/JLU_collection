//
//  MainLayerButton.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/11/16.
//
//

#ifndef MainLayerButton_hpp
#define MainLayerButton_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN

enum MainLayerButtonType
{
    BATTLE_BUTTON,
    ORGANIZE_BUTTON,
    SUPPLY_BUTTON,
    REMODE_BUTTON,
    REPAIR_BUTTON,
    FACTORY_BUTTON
};


typedef std::function<void(cocos2d::Ref*)> buttonCallBack;



class MainLayerButton:public cocos2d::Node
{
public:
    static MainLayerButton* create(MainLayerButtonType buttonType,buttonCallBack);
    
private:
    
    bool init(MainLayerButtonType buttonType,buttonCallBack);
    buttonCallBack callback;
    cocos2d::EventListenerTouchOneByOne* eventListner;
    
    
    
    
    
private:
    bool organizeBegin(Touch* touch,Event* event);
    void organizeMove(Touch* touch,Event* event);
    void organizeEnd(Touch* touch,Event* event);
    
    bool battleBegin(Touch* touch,Event* event);
    void battleMove(Touch* touch,Event* event);
    void battleEnd(Touch* touch,Event* event);
    
    
    
    
};





NS_KCL_END



#endif /* MainLayerButton_hpp */
