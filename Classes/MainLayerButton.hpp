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
#include "ViewMgrMacro.hpp"

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




typedef std::function<void(PanelType)> buttonCallBack;


class MainLayerButton:public cocos2d::Node
{
public:
    virtual bool onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event)=0;
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event)=0;
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event)=0;
    
    bool touchBegin(cocos2d::Touch* touch,cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    void touchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void setEndCallBack(buttonCallBack _callback){callback=_callback;}
private:
    cocos2d::EventListenerTouchOneByOne* eventListner;
protected:
    bool init(MainLayerButtonType buttonType,buttonCallBack _callback);
    MainLayerButtonType buttonType;
    buttonCallBack callback;
    
};




class NormalMainLayerButton:public MainLayerButton
{
public:
    static NormalMainLayerButton* create(MainLayerButtonType buttonType,buttonCallBack _callback);
    
    
    virtual bool onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
private:
    bool init(MainLayerButtonType buttonType,buttonCallBack _callback);
    
private:
    
    void stopButtonAction();
    void startButtonAction();
    
    bool stopEvent;
    cocos2d::Sprite* rotateButton;
    cocos2d::Sprite* waveButton;
    cocos2d::Sprite* buttonImage;
};






class BattleMainLayerButton:public MainLayerButton
{
public:
    static BattleMainLayerButton* create(MainLayerButtonType buttonType,buttonCallBack _callback);
    
    
    virtual bool onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
private:
    bool init(MainLayerButtonType buttonType,buttonCallBack _callback);
    
    cocos2d::Sprite* battleButtonShip;
    cocos2d::Sprite* battleButtonGo;
    cocos2d::Sprite* battleButton;
    cocos2d::Sprite* battleLeft;
    cocos2d::Sprite* battleRight;
    cocos2d::Sprite* rotateButton;
    cocos2d::Sprite* waveButton;
    
    
    bool stopEvent=true;
};






NS_KCL_END



#endif /* MainLayerButton_hpp */
