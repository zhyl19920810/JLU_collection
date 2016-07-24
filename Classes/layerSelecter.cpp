//
//  LayerSelecter.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "LayerSelecter.h"

NS_KCL_BEGIN

LayerSelecter::LayerSelecter()
{

}

void LayerSelecter::moveOut()
{
    runAction(MoveTo::create(0.3, initialPosition));
}

void LayerSelecter::moveIn()
{
    runAction(MoveTo::create(0.3, Vec2(initialPosition.x+100,initialPosition.y)));
}


void LayerSelecter::layerSelectCallback(cocos2d::Ref *pSender, PanelType type)
{
    parent->SetCurrPanel(type);
    
}

bool LayerSelecter::init()
{
    bool bRet=false;
    do
    {
        
        mainbody =Sprite::createWithSpriteFrameName("lsmb.png");
        mainbody->setPosition(-10, 0);
        backgroud = Sprite::createWithSpriteFrameName("lsbg.png");
        backgroud->setPosition(0, 0);
        
        this->addChild(backgroud);
        this->addChild(mainbody);
        
        portItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("portItem1.png"),Sprite::createWithSpriteFrameName("portItem2.png"),CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_MAINLAYER));
        portItem->setPosition(22, 0);
        organizeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("organizeItem1.png"),Sprite::createWithSpriteFrameName("organizeItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_ORGANIZE));
        organizeItem->setPosition(-30, 100);
        supplyItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("supplyItem1.png"),Sprite::createWithSpriteFrameName("supplyItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_SUPPLY));
        supplyItem->setPosition(-30, 50);
        remodeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("remodeItem1.png"),Sprite::createWithSpriteFrameName("remodeItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_REMODE));
        remodeItem->setPosition(-30, 0);
        repairItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("repairItem1.png"),Sprite::createWithSpriteFrameName("repairItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_REPAIR));
        repairItem->setPosition(-30, -50);
        factoryItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("factoryItem1.png"),Sprite::createWithSpriteFrameName("factoryItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_FACTORY));
        factoryItem->setPosition(-30, -100);
        
        menu = Menu::create(portItem,organizeItem, supplyItem, remodeItem, repairItem, factoryItem, NULL);
        menu->setPosition(0, 0);
        this->addChild(menu);
        
        
        
        bRet=true;
    }while(0);
    return bRet;
}


NS_KCL_END


