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
    
    mainbody = Sprite::create("interface/PortMain/image 243.png");
    mainbody->setPosition(-10, 0);
    backgroud = Sprite::create("interface/PortMain/image 242.png");
    backgroud->setPosition(0, 0);
    
    this->addChild(backgroud);
    this->addChild(mainbody);
    
    portItem = MenuItemImage::create("interface/PortMain/image 275.png", "interface/PortMain/image 277.png", CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::main));
    portItem->setPosition(22, 0);
    organizeItem = MenuItemImage::create("interface/PortMain/image 270.png", "interface/PortMain/image 272.png", CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::organize));
    organizeItem->setPosition(-30, 100);
    supplyItem = MenuItemImage::create("interface/PortMain/image 250.png", "interface/PortMain/image 252.png", CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::supply));
    supplyItem->setPosition(-30, 50);
    remodeItem = MenuItemImage::create("interface/PortMain/image 255.png", "interface/PortMain/image 257.png", CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::remode));
    remodeItem->setPosition(-30, 0);
    repairItem = MenuItemImage::create("interface/PortMain/image 260.png", "interface/PortMain/image 262.png", CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::repair));
    repairItem->setPosition(-30, -50);
    factoryItem = MenuItemImage::create("interface/PortMain/image 265.png", "interface/PortMain/image 267.png", CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, LayerType::factory));
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
    runAction(MoveTo::create(0.3, ccp(initialPosition.x+100,initialPosition.y)));
}


void LayerSelecter::layerSelectCallback(cocos2d::Ref *pSender, LayerType type)
{
    parent->SetCurrLayer(type);
    
}







