//
//  LayerSelecter.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "LayerSelecter.h"


LayerSelecter::LayerSelecter(PortScene *parent,Point position)
{
    initialPosition=position;
    this->parent=parent;
    this->setPosition(initialPosition);
    parent->addChild(this);
    this->setZOrder(2);
    
    mainbody =Sprite::createWithSpriteFrameName("lsmb.png");
    mainbody->setPosition(-10, 0);
    backgroud = Sprite::createWithSpriteFrameName("lsbg.png");
    backgroud->setPosition(0, 0);
    
    this->addChild(backgroud);
    this->addChild(mainbody);
    
    portItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("portItem1.png"),Sprite::createWithSpriteFrameName("portItem2.png"),CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::main));
    portItem->setPosition(22, 0);
    organizeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("organizeItem1.png"),Sprite::createWithSpriteFrameName("organizeItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::organize));
    organizeItem->setPosition(-30, 100);
    supplyItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("supplyItem1.png"),Sprite::createWithSpriteFrameName("supplyItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::supply));
    supplyItem->setPosition(-30, 50);
    remodeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("remodeItem1.png"),Sprite::createWithSpriteFrameName("remodeItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::remode));
    remodeItem->setPosition(-30, 0);
    repairItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("repairItem1.png"),Sprite::createWithSpriteFrameName("repairItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::repair));
    repairItem->setPosition(-30, -50);
    factoryItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("factoryItem1.png"),Sprite::createWithSpriteFrameName("factoryItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::factory));
    factoryItem->setPosition(-30, -100);
    
    menu = Menu::create(portItem,organizeItem, supplyItem, remodeItem, repairItem, factoryItem, NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);
    
}

void LayerSelecter::moveOut()
{
    runAction(MoveTo::create(0.3, initialPosition));
}

void LayerSelecter::moveIn()
{
    runAction(MoveTo::create(0.3, Vec2(initialPosition.x+100,initialPosition.y)));
}


void LayerSelecter::layerSelectCallback(cocos2d::Ref *pSender, LayerType type)
{
    parent->SetCurrLayer(type);
    
}







