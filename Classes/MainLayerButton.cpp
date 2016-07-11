//
//  MainLayerButton.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/11/16.
//
//

#include "MainLayerButton.hpp"

NS_KCL_BEGIN


USING_NS_CC;

MainLayerButton* MainLayerButton::create(kancolle::MainLayerButtonType buttonType, buttonCallBack _callback)
{
    static MainLayerButton* p_ret=new MainLayerButton;
    if (p_ret&&p_ret->init(buttonType, _callback))
    {
        p_ret->autorelease();
        return p_ret;
    }
    delete p_ret;
    p_ret=NULL;
    return p_ret;
}


bool MainLayerButton::init(kancolle::MainLayerButtonType buttonType, buttonCallBack _callback)
{
    bool b_ret=false;
    
    do
    {
        CC_BREAK_IF(!Node::init());
        eventListner=cocos2d::EventListenerTouchOneByOne::create();
//        eventListner->onTouchBegan=
//        eventListner->onTouchMoved=
//        eventListner->onTouchEnded=
        auto eventDispatcher=Director::getInstance()->getEventDispatcher();
        eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);
        
        b_ret=true;
    }while(0);
    
    return b_ret;
}





bool MainLayerButton::organizeBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto target=static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 location=target->convertToNodeSpace(touch->getLocation());
    Size s=target->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(location))
    {
        int type=target->getTag();
        switch (type)
        {
            case organizeBu:
                target->setSpriteFrame("organizeButton3.png");
                break;
            case supplyBu:
                target->setSpriteFrame("supplyButton3.png");
                break;
            case remodeBu:
                target->setSpriteFrame("remodeButton3.png");
                break;
            case repairBu:
                target->setSpriteFrame("repairButton3.png");
                break;
            case factoryBu:
                target->setSpriteFrame("factoryButton3.png");
                break;
            default:
                break;
        }
        startButtonAction(target->getPosition());
        return true;
    }
    return false;
}

void MainLayerButton::organizeMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!stopEvent)
    {
        return;
    }
    auto target=static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 location=target->convertToNodeSpace(touch->getLocation());
    Size s=target->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (!rect.containsPoint(location))
    {
        int type=target->getTag();
        switch (type)
        {
            case organizeBu:
                target->setSpriteFrame("organizeButton1.png");
                break;
            case supplyBu:
                target->setSpriteFrame("supplyButton1.png");
                break;
            case remodeBu:
                target->setSpriteFrame("remodeButton1.png");
                break;
            case repairBu:
                target->setSpriteFrame("repairButton1.png");
                break;
            case factoryBu:
                target->setSpriteFrame("factoryButton1.png");
                break;
            default:
                break;
        }
        stopButtonAction();
        stopEvent=false;
    }
}



void MainLayerButton::organizeEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (stopEvent)
    {
        auto target=static_cast<Sprite*>(event->getCurrentTarget());
        int type=target->getTag();
        stopButtonAction();
        auto scene=dynamic_cast<PortScene*>(getParent());
        EventDispatcher* eventDispatcher=Director::getInstance()->getEventDispatcher();
        eventDispatcher->pauseEventListenersForTarget(organizeButton);
        eventDispatcher->pauseEventListenersForTarget(supplyButton);
        eventDispatcher->pauseEventListenersForTarget(remodeButton);
        eventDispatcher->pauseEventListenersForTarget(repairButton);
        eventDispatcher->pauseEventListenersForTarget(factoryButton);
        eventDispatcher->pauseEventListenersForTarget(battleButton);
        switch (type)
        {
                
            case organizeBu:
                target->setSpriteFrame("organizeButton1.png");
                scene->SetCurrLayer(LayerType::PORT_ORGANIZE);
                break;
            case supplyBu:
                target->setSpriteFrame("supplyButton1.png");
                scene->SetCurrLayer(LayerType::PORT_SUPPLY);
                break;
            case remodeBu:
                target->setSpriteFrame("remodeButton1.png");
                scene->SetCurrLayer(LayerType::PORT_REMODE);
                break;
            case repairBu:
                target->setSpriteFrame("repairButton1.png");
                scene->SetCurrLayer(LayerType::PORT_REPAIR);
                break;
            case factoryBu:
                target->setSpriteFrame("factoryButton1.png");
                scene->SetCurrLayer(LayerType::PORT_FACTORY);
                break;
            default:
                break;
        }
        
        
        
    }
}


bool MainLayerButton::battleBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto target=static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 location=target->convertToNodeSpace(touch->getLocation());
    Size s=target->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(location))
    {
        target->setSpriteFrame("battleButton8.png");
        battleButtonGo->setSpriteFrame("battleButton10.png");
        battleButtonShip->setSpriteFrame("battleButton9.png");
        ActionInterval* tmp1=RotateBy::create(2.5, -6);
        ActionInterval* tmp2=RotateBy::create(4.0, 15);
        ActionInterval* tmp3=Sequence::create(tmp1,tmp2, NULL);
        battleShipRotate=RepeatForever::create(Sequence::create(tmp3,tmp3->reverse(),NULL));
        battleButtonShip->runAction(battleShipRotate);
        
        battleLeft->setSpriteFrame("battleButton7.png");
        
        
        battleRight->setSpriteFrame("battleButton6.png");
        
        stopEvent=true;
        rotate=RepeatForever::create(RotateBy::create(0.1, ANGLE_ROTATE));
        rotateButton->setSpriteFrame("battleButton1.png");
        rotateButton->setPosition(target->getPosition());
        rotateButton->setVisible(true);
        rotateButton->runAction(rotate);
        
        waveButton->setPosition(target->getPosition());
        wave=RepeatForever::create(Sequence::create(ScaleTo::create(0.01,1.0),ScaleBy::create(3.0, 2.0), NULL));
        waveButton->setVisible(true);
        waveButton->runAction(wave);
        return true;
    }
    return false;
}

void MainLayerButton::battleMove(Touch* touch,Event* event)
{
    if (!stopEvent)
    {
        return;
    }
    auto target=static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 location=target->convertToNodeSpace(touch->getLocation());
    Size s=target->getContentSize();
    Rect rect=Rect(0, 0, s.width, s.height);
    if (!rect.containsPoint(location))
    {
        target->setSpriteFrame("battleButton1.png");
        battleButtonGo->setSpriteFrame("battleButtonGo.png");
        battleButtonShip->setSpriteFrame("battleButtonShip.png");
        battleButtonShip->setRotation(0);
        battleButtonShip->stopAction(battleShipRotate);
        battleLeft->setSpriteFrame("battleButton3.png");
        battleRight->setSpriteFrame("battleButton2.png");
        
        rotateButton->setSpriteFrame("battleButton11.png");
        rotateButton->stopAction(rotate);
        rotateButton->setVisible(false);
        waveButton->stopAction(wave);
        waveButton->setScale(0.7);
        waveButton->setVisible(false);
        
        stopEvent=false;
    }
}

void MainLayerButton::battleEnd(Touch* touch,Event* event)
{
    
    if (stopEvent)
    {
        auto target=static_cast<Sprite*>(event->getCurrentTarget());
        target->setSpriteFrame("battleButton1.png");
        battleButtonGo->setSpriteFrame("battleButtonGo.png");
        battleButtonShip->setSpriteFrame("battleButtonShip.png");
        battleButtonShip->setRotation(0);
        battleButtonShip->stopAction(battleShipRotate);
        battleLeft->setSpriteFrame("battleButton3.png");
        battleRight->setSpriteFrame("battleButton2.png");
        
        rotateButton->setSpriteFrame("battleButton11.png");
        rotateButton->stopAction(rotate);
        rotateButton->setVisible(false);
        waveButton->stopAction(wave);
        waveButton->setScale(0.7);
        waveButton->setVisible(false);
        stopEvent=false;
        
        EventDispatcher* eventDispatcher=Director::getInstance()->getEventDispatcher();
        eventDispatcher->pauseEventListenersForTarget(organizeButton);
        eventDispatcher->pauseEventListenersForTarget(supplyButton);
        eventDispatcher->pauseEventListenersForTarget(remodeButton);
        eventDispatcher->pauseEventListenersForTarget(repairButton);
        eventDispatcher->pauseEventListenersForTarget(factoryButton);
        eventDispatcher->pauseEventListenersForTarget(battleButton);
        
        auto scene=dynamic_cast<PortScene*>(target->getParent()->getParent());
        scene->SetCurrLayer(LayerType::PORT_BATTLE);
    }
}









NS_KCL_END