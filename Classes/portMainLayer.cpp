//
//  portMainLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portMainLayer.h"
#include "Player.h"
#include "signBoardGirl.hpp"


NS_KCL_BEGIN


#define ANGLE_ROTATE 3


PortMainLayer::PortMainLayer():signBoardGirl(NULL)
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
    initSignBoardGirl();
    initMenu();
    
    return true;
}


void PortMainLayer::initSignBoardGirl()
{
    signBoardGirl=SignBoardGirl::create();
    signBoardGirl->setPosition(600,0);
    addChild(signBoardGirl);
}

void PortMainLayer::updateGirl()
{
    signBoardGirl->updateGirl();
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


