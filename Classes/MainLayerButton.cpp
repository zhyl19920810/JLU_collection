//
//  MainLayerButton.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/11/16.
//
//

#include "MainLayerButton.hpp"
#include "ViewMgr.hpp"

NS_KCL_BEGIN



#define ANGLE_ROTATE 3.0
#define BUTTON_WAVE 1001
#define BUTTON_ROTATE 1002


#define BATTLE_BUTTON_WAVE         2001
#define BATTLE_BUTTON_ROTATE       2002
#define BATTLE_BUTTON_SHIPROTATE   2003
#define BATTLE_BUTTON_LEFTMOVE     2004
#define BATTLE_BUTTON_RIGHTMOVE    2004


USING_NS_CC;

bool MainLayerButton::init(MainLayerButtonType _buttonType,buttonCallBack _callback)
{
    bool b_ret=false;
    
    do
    {
        CC_BREAK_IF(!Node::init());
        eventListner=cocos2d::EventListenerTouchOneByOne::create();
        eventListner->onTouchBegan=CC_CALLBACK_2(MainLayerButton::touchBegin, this);
        eventListner->onTouchMoved=CC_CALLBACK_2(MainLayerButton::touchMoved, this);
        eventListner->onTouchEnded=CC_CALLBACK_2(MainLayerButton::touchEnded, this);
        auto eventDispatcher=Director::getInstance()->getEventDispatcher();
        eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);
        
        _enable=true;
        callback=_callback;
        buttonType=_buttonType;
        b_ret=true;
    }while(0);
    
    return b_ret;
}


bool MainLayerButton::touchBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return onTouchBegin(touch,event);
}

void MainLayerButton::touchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    onTouchMoved(touch,event);
}

void MainLayerButton::touchEnded(cocos2d::Touch* touch,cocos2d::Event* event)
{
    onTouchEnded(touch,event);
}


void MainLayerButton::setEnable()
{
    if (_enable) return;
    _enable=true;
    eventListner->setEnabled(true);
}

void MainLayerButton::setDisable()
{
    if (!_enable) return;
    _enable=false;
    eventListner->setEnabled(false);
}


////--------------------------------------------------------------------------------------------------------------------


NormalMainLayerButton* NormalMainLayerButton::create(kancolle::MainLayerButtonType buttonType, buttonCallBack _callback)
{
    NormalMainLayerButton* p_ret=new NormalMainLayerButton;
    if (p_ret&&p_ret->init(buttonType, _callback))
    {
        p_ret->autorelease();
        return p_ret;
    }
    delete p_ret;
    p_ret=NULL;
    return p_ret;
}




bool NormalMainLayerButton::init(kancolle::MainLayerButtonType buttonType, buttonCallBack _callback)
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!MainLayerButton::init(buttonType, _callback));
        
        rotateButton=Sprite::createWithSpriteFrameName("battleButton11.png");
        addChild(rotateButton);
        rotateButton->setVisible(false);
        waveButton=Sprite::createWithSpriteFrameName("battleButton12.png");
        addChild(waveButton,5);
        waveButton->setVisible(false);
        waveButton->setScale(0.7);
        waveButton->setOpacity(150);
        
        switch (buttonType)
        {
            case ORGANIZE_BUTTON:
                buttonImage=Sprite::createWithSpriteFrameName("organizeButton1.png");
                break;
            case SUPPLY_BUTTON:
                buttonImage=Sprite::createWithSpriteFrameName("supplyButton1.png");
                break;
            case REMODE_BUTTON:
                buttonImage=Sprite::createWithSpriteFrameName("remodeButton1.png");
                break;
            case REPAIR_BUTTON:
                buttonImage=Sprite::createWithSpriteFrameName("repairButton1.png");
                break;
            case FACTORY_BUTTON:
                buttonImage=Sprite::createWithSpriteFrameName("factoryButton1.png");
                break;
            default:
                break;
        }
        buttonImage->setPosition(Vec2::ZERO);
        addChild(buttonImage);
        
        bRet=true;
    }while(0);
    return bRet;
}




void NormalMainLayerButton::stopButtonAction()
{
    rotateButton->stopActionByTag(BUTTON_WAVE);
    rotateButton->setVisible(false);
    waveButton->stopActionByTag(BUTTON_WAVE);
    waveButton->setScale(0.7);
    waveButton->setVisible(false);
    switch (buttonType)
    {
        case ORGANIZE_BUTTON:
            buttonImage->setSpriteFrame("organizeButton1.png");
            break;
        case SUPPLY_BUTTON:
            buttonImage->setSpriteFrame("supplyButton1.png");
            break;
        case REMODE_BUTTON:
            buttonImage->setSpriteFrame("remodeButton1.png");
            break;
        case REPAIR_BUTTON:
            buttonImage->setSpriteFrame("repairButton1.png");
            break;
        case FACTORY_BUTTON:
            buttonImage->setSpriteFrame("factoryButton1.png");
            break;
        default:
            break;
    }
}

void NormalMainLayerButton::startButtonAction()
{
    switch (buttonType)
    {
        case ORGANIZE_BUTTON:
            buttonImage->setSpriteFrame("organizeButton3.png");
            break;
        case SUPPLY_BUTTON:
            buttonImage->setSpriteFrame("supplyButton3.png");
            break;
        case REMODE_BUTTON:
            buttonImage->setSpriteFrame("remodeButton3.png");
            break;
        case REPAIR_BUTTON:
            buttonImage->setSpriteFrame("repairButton3.png");
            break;
        case FACTORY_BUTTON:
            buttonImage->setSpriteFrame("factoryButton3.png");
            break;
        default:
            break;
    }
    stopEvent=true;
    auto rotate=RepeatForever::create(RotateBy::create(0.1, ANGLE_ROTATE));
    rotate->setTag(BUTTON_ROTATE);
    rotateButton->setVisible(true);
    rotateButton->runAction(rotate);
    
    auto wave=RepeatForever::create(Sequence::create(ScaleTo::create(0.01,0.7),ScaleBy::create(3.0, 1.7), NULL));
    wave->setTag(BUTTON_WAVE);
    waveButton->setVisible(true);
    waveButton->runAction(wave);
}




bool NormalMainLayerButton::onTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 location=buttonImage->convertToNodeSpace(touch->getLocation());
    Size s=buttonImage->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(location))
    {
        startButtonAction();
        return true;
    }
    return false;
}

void NormalMainLayerButton::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!stopEvent)
    {
        return;
    }
    Vec2 location=buttonImage->convertToNodeSpace(touch->getLocation());
    Size s=buttonImage->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (!rect.containsPoint(location))
    {
        stopButtonAction();
        stopEvent=false;
    }
}



void NormalMainLayerButton::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (stopEvent)
    {
        stopButtonAction();
        switch (buttonType)
        {
            case ORGANIZE_BUTTON:
                callback(PanelType::PORT_ORGANIZE);
                break;
            case SUPPLY_BUTTON:
                callback(PanelType::PORT_SUPPLY);
                break;
            case REMODE_BUTTON:
                callback(PanelType::PORT_REMODE);
                break;
            case REPAIR_BUTTON:
                callback(PanelType::PORT_REPAIR);
                break;
            case FACTORY_BUTTON:
                callback(PanelType::PORT_FACTORY);
                break;
            default:
                break;
        }
    }
}




/////-----------------------------------------------------------------------------------------------

BattleMainLayerButton* BattleMainLayerButton::create(kancolle::MainLayerButtonType buttonType, buttonCallBack _callback)
{
    BattleMainLayerButton* p_ret=new BattleMainLayerButton;
    if (p_ret&&p_ret->init(buttonType, _callback))
    {
        p_ret->autorelease();
        return p_ret;
    }
    delete p_ret;
    p_ret=NULL;
    return p_ret;
}



bool BattleMainLayerButton::init(MainLayerButtonType buttonType,buttonCallBack _callback)
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!MainLayerButton::init(buttonType, _callback));
        
        battleButton=Sprite::createWithSpriteFrameName("battleButton1.png");
        battleButton->setPosition(Vec2::ZERO);
        addChild(battleButton);
        
        
        battleButtonShip = Sprite::createWithSpriteFrameName("battleButtonShip.png");
        battleButtonGo = Sprite::createWithSpriteFrameName("battleButtonGo.png");
        battleButtonShip->setPosition(Vec2(0, 25));
        battleButtonGo->setPosition(Vec2(0, -25));
        addChild(battleButtonShip,3);
        addChild(battleButtonGo,4);
        
        
        battleLeft=Sprite::createWithSpriteFrameName("battleButton3.png");
        battleRight=Sprite::createWithSpriteFrameName("battleButton2.png");
        battleLeft->setPosition(Vec2(-30, -30));
        battleRight->setPosition(Vec2(30, -30));
        addChild(battleLeft);
        addChild(battleRight);
        
        
        rotateButton=Sprite::createWithSpriteFrameName("battleButton11.png");
        addChild(rotateButton);
        rotateButton->setVisible(false);
        
        
        waveButton=Sprite::createWithSpriteFrameName("battleButton12.png");
        addChild(waveButton,5);
        waveButton->setVisible(false);
        waveButton->setScale(0.7);
        waveButton->setOpacity(150);
        
        
        bRet=true;
    }while(0);
    return bRet;
}



bool BattleMainLayerButton::onTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 location=battleButton->convertToNodeSpace(touch->getLocation());
    Size s=battleButton->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(location))
    {
        battleButton->setSpriteFrame("battleButton8.png");
        battleButtonGo->setSpriteFrame("battleButton10.png");
        battleButtonShip->setSpriteFrame("battleButton9.png");
        ActionInterval* tmp1=RotateBy::create(2.5, -6);
        ActionInterval* tmp2=RotateBy::create(4.0, 15);
        ActionInterval* tmp3=Sequence::create(tmp1,tmp2, NULL);
        auto battleShipRotate=RepeatForever::create(Sequence::create(tmp3,tmp3->reverse(),NULL));
        battleShipRotate->setTag(BATTLE_BUTTON_SHIPROTATE);
        battleButtonShip->runAction(battleShipRotate);
        battleLeft->setSpriteFrame("battleButton7.png");
        battleRight->setSpriteFrame("battleButton6.png");
        
        
        auto rotate=RepeatForever::create(RotateBy::create(0.1, ANGLE_ROTATE));
        rotate->setTag(BATTLE_BUTTON_ROTATE);
        rotateButton->setSpriteFrame("battleButton1.png");
        rotateButton->setPosition(battleButton->getPosition());
        rotateButton->setVisible(true);
        rotateButton->runAction(rotate);
        
        waveButton->setPosition(battleButton->getPosition());
        auto wave=RepeatForever::create(Sequence::create(ScaleTo::create(0.01,1.0),ScaleBy::create(3.0, 2.0), NULL));
        wave->setTag(BATTLE_BUTTON_WAVE);
        waveButton->setVisible(true);
        waveButton->runAction(wave);
        stopEvent=true;
        
        return true;
    }
    return false;
}

void BattleMainLayerButton::onTouchMoved(Touch* touch,Event* event)
{
    if (!stopEvent)
    {
        return;
    }
    Vec2 location=battleButton->convertToNodeSpace(touch->getLocation());
    Size s=battleButton->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (!rect.containsPoint(location))
    {
        battleButton->setSpriteFrame("battleButton1.png");
        battleButtonGo->setSpriteFrame("battleButtonGo.png");
        battleButtonShip->setSpriteFrame("battleButtonShip.png");
        battleButtonShip->setRotation(0);
        battleButtonShip->stopActionByTag(BATTLE_BUTTON_SHIPROTATE);
        battleLeft->setSpriteFrame("battleButton3.png");
        battleRight->setSpriteFrame("battleButton2.png");
        
        rotateButton->setSpriteFrame("battleButton11.png");
        battleButton->stopActionByTag(BATTLE_BUTTON_ROTATE);
        rotateButton->setVisible(false);
        battleButton->stopActionByTag(BATTLE_BUTTON_WAVE);
        waveButton->setScale(0.7);
        waveButton->setVisible(false);
        
        stopEvent=false;
    }
}

void BattleMainLayerButton::onTouchEnded(Touch* touch,Event* event)
{
    
    if (stopEvent)
    {
        battleButton->setSpriteFrame("battleButton1.png");
        battleButtonGo->setSpriteFrame("battleButtonGo.png");
        battleButtonShip->setSpriteFrame("battleButtonShip.png");
        battleButtonShip->setRotation(0);
        battleButtonShip->stopActionByTag(BATTLE_BUTTON_SHIPROTATE);
        battleLeft->setSpriteFrame("battleButton3.png");
        battleRight->setSpriteFrame("battleButton2.png");
        
        rotateButton->setSpriteFrame("battleButton11.png");
        battleButton->stopActionByTag(BATTLE_BUTTON_ROTATE);
        rotateButton->setVisible(false);
        battleButton->stopActionByTag(BATTLE_BUTTON_WAVE);
        waveButton->setScale(0.7);
        waveButton->setVisible(false);
        stopEvent=false;
        
        callback(PanelType::PORT_BATTLE);
    }
}









NS_KCL_END