//
//  portMainLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portMainLayer.h"
#include "Player.h"

NS_KCL_BEGIN


#define ANGLE_ROTATE 3


PortMainLayer::PortMainLayer():girl(NULL)
{
    girlflag=0;
}

void PortMainLayer::initLayer()
{
    //furniture
    floor = Sprite::create("furniture/floor/022.png");
    floor->setPosition(400, 100);
    floor->setZOrder(-2);
    this->addChild(floor);
    wall = Sprite::create("furniture/wall/012.png");
    wall->setPosition(400, 285);
    wall->setZOrder(-2);
    this->addChild(wall);
    object = Sprite::create("furniture/object/015.png");
    object->setPosition(80, 380);
    object->setZOrder(-2);
    this->addChild(object);
    desk = Sprite::create("furniture/desk/021.png");
    desk->setPosition(170, 200);
    desk->setZOrder(-2);
    this->addChild(desk);
    window = Sprite::create("furniture/window/017.png");
    window->setPosition(450, 300);
    window->setZOrder(-2);
    this->addChild(window);
    
    chest = Sprite::create("furniture/chest/003.png");
    chest->setPosition(700, 250);
    chest->setZOrder(-2);
    this->addChild(chest);
}



bool PortMainLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    initLayer();
    updateGirl();
    initMenu();
    
    return true;
}



void PortMainLayer::updateGirl()
{
    char resource[50];
    bzero(resource, sizeof(resource));
    auto fleet1=sPlayer.fleetData;
    int num=sPlayer.fleetData[0]->ship[0]->getKantaiNumber();
    sprintf(resource, "kantai/%d/image 17.png",num);
    //std::string resource="kantai/"+std::to_string(num)+"/image 17.png";
    
    if (girl==nullptr)
    {
        girl=Sprite::create(resource);
    }
    else
    {
        girl->setTexture(resource);
    }
    int height=girl->getContentSize().height;
    if (height>799)
    {
        girl->setAnchorPoint(Vec2(0.5, 0.45));
    }
    else if(height>699)
    {
        girl->setAnchorPoint(Vec2(0.5, 0.25));
    }
    if (!girl->getParent()) {
        addChild(girl);
    }
    
    girl->setPosition(600,0);
    girl->setZOrder(-1);
    girl->runAction(RepeatForever::create((ActionInterval*)Sequence::create(ScaleTo::create(4,1.02),ScaleTo::create(4, 1), NULL)));
    
}

void PortMainLayer::stopButtonAction()
{
    rotateButton->stopAction(rotate);
    rotateButton->setVisible(false);
    waveButton->stopAction(wave);
    waveButton->setScale(0.7);
    waveButton->setVisible(false);
}

void PortMainLayer::startButtonAction(const Vec2& point)
{
    stopEvent=true;
    rotate=RepeatForever::create(RotateBy::create(0.1, ANGLE_ROTATE));
    rotateButton->setPosition(point);
    rotateButton->setVisible(true);
    rotateButton->runAction(rotate);
    
    waveButton->setPosition(point);
    wave=RepeatForever::create(Sequence::create(ScaleTo::create(0.01,0.7),ScaleBy::create(3.0, 1.7), NULL));
    waveButton->setVisible(true);
    waveButton->runAction(wave);
}


bool PortMainLayer::organizeBegin(cocos2d::Touch *touch, cocos2d::Event *event)
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

void PortMainLayer::organizeMove(cocos2d::Touch *touch, cocos2d::Event *event)
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



void PortMainLayer::organizeEnd(cocos2d::Touch *touch, cocos2d::Event *event)
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


bool PortMainLayer::battleBegin(cocos2d::Touch *touch, cocos2d::Event *event)
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

void PortMainLayer::battleMove(Touch* touch,Event* event)
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

void PortMainLayer::battleEnd(Touch* touch,Event* event)
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

void PortMainLayer::resumeDispatcher()
{
    EventDispatcher* eventDispatcher=Director::getInstance()->getEventDispatcher();
    eventDispatcher->resumeEventListenersForTarget(organizeButton);
    eventDispatcher->resumeEventListenersForTarget(supplyButton);
    eventDispatcher->resumeEventListenersForTarget(remodeButton);
    eventDispatcher->resumeEventListenersForTarget(repairButton);
    eventDispatcher->resumeEventListenersForTarget(factoryButton);
    eventDispatcher->resumeEventListenersForTarget(battleButton);
}

void PortMainLayer::initMenu()
{

    
    rotateButton=Sprite::createWithSpriteFrameName("battleButton11.png");
    addChild(rotateButton);
    rotateButton->setVisible(false);
    
    
    waveButton=Sprite::createWithSpriteFrameName("battleButton12.png");
    addChild(waveButton,5);
    waveButton->setVisible(false);
    waveButton->setScale(0.7);
    waveButton->setOpacity(150);
    

    organizeButton=Sprite::createWithSpriteFrameName("organizeButton1.png");
    organizeButton->setPosition(Vec2(145+(300-145)/2, 340));
    addChild(organizeButton,1,organizeBu);
    
    supplyButton=Sprite::createWithSpriteFrameName("supplyButton1.png");
    supplyButton->setPosition(100, 260);
    addChild(supplyButton,1,supplyBu);
    
    remodeButton=Sprite::createWithSpriteFrameName("remodeButton1.png");
    remodeButton->setPosition(345, 260);
    addChild(remodeButton,1,remodeBu);
    
    repairButton=Sprite::createWithSpriteFrameName("repairButton1.png");
    repairButton->setPosition(145, 110);
    addChild(repairButton,1,repairBu);
    
    factoryButton=Sprite::createWithSpriteFrameName("factoryButton1.png");
    factoryButton->setPosition(300, 110);
    addChild(factoryButton,1,factoryBu);
    
    
    EventListenerTouchOneByOne* listener1=EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan=CC_CALLBACK_2(PortMainLayer::organizeBegin, this);
    listener1->onTouchMoved=CC_CALLBACK_2(PortMainLayer::organizeMove, this);
    listener1->onTouchEnded=CC_CALLBACK_2(PortMainLayer::organizeEnd, this);
    EventDispatcher* eventDispatcher=Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,organizeButton);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), supplyButton);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), remodeButton);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), repairButton);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), factoryButton);
    
    
    
    battleButton=Sprite::createWithSpriteFrameName("battleButton1.png");
    battleButton->setPosition((145+(300-145)/2), 210);
    Vec2 size=battleButton->getPosition();
    addChild(battleButton,2);
    battleButtonShip = Sprite::createWithSpriteFrameName("battleButtonShip.png");
    battleButtonGo = Sprite::createWithSpriteFrameName("battleButtonGo.png");
    
    battleButtonShip->setPosition(size+Vec2(0, 25));
    battleButtonGo->setPosition(size+Vec2(0, -25));
    addChild(battleButtonShip,3);
    addChild(battleButtonGo,4);
    battleLeft=Sprite::createWithSpriteFrameName("battleButton3.png");
    battleRight=Sprite::createWithSpriteFrameName("battleButton2.png");
    
    battleLeft->setPosition(Vec2(-30, -30)+size);
    battleRight->setPosition(Vec2(30, -30)+size);
    addChild(battleLeft,0);
    addChild(battleRight,0);
    

    EventListenerTouchOneByOne* listener2=EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);
    listener2->onTouchBegan=CC_CALLBACK_2(PortMainLayer::battleBegin, this);
    listener2->onTouchMoved=CC_CALLBACK_2(PortMainLayer::battleMove, this);
    listener2->onTouchEnded=CC_CALLBACK_2(PortMainLayer::battleEnd, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,battleButton);

   


}

PortMainLayer::~PortMainLayer()
{

}

void PortMainLayer::menuCallback(cocos2d::Ref *pSender)
{
    
}

void PortMainLayer::battleCallback(cocos2d::Ref *pSender)
{
    
}

void PortMainLayer::layerSelectCallback(cocos2d::Ref *pSender, LayerType type)
{
    auto scene=dynamic_cast<PortScene*>(getParent());
    scene->SetCurrLayer(type);
}

NS_KCL_END


