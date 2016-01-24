//
//  portMainLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portMainLayer.h"
#include "Player.h"

PortMainLayer::PortMainLayer(PortScene* parent)
{
    this->parent=parent;
    girl=nullptr;
    
    initLayer();
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
    
    //girl
    updateGirl();
    
    //buttons
    initMenu();
    

    
    
    
}


void PortMainLayer::updateGirl()
{
    int num=sPlayer.fleetData[0]->ship[0]->getKantaiNumber();
    std::string resource="kantai/"+std::to_string(num)+"/image 17.png";
    
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

void PortMainLayer::initMenu()
{
    auto battleButton = MenuItemImage::create("interface/PortMain/image 407.png", "interface/PortMain/image 407.png", CC_CALLBACK_1(PortMainLayer::layerSelectCallback, this,LayerType::battle));
    battleButton->setPosition((145+(300-145)/2), 210);
    Sprite* battleButtonShip = Sprite::create("interface/PortMain/image 408.png");
    Sprite* battleButtonGo = Sprite::create("interface/PortMain/image 409.png");
    battleButtonShip->setPosition(67, 100);
    battleButtonGo->setPosition(67, 50);
    battleButton->addChild(battleButtonShip);
    battleButton->addChild(battleButtonGo);
    
    auto organizeButton = MenuItemImage::create("interface/PortMain/image 434.png", "interface/PortMain/image 441.png", CC_CALLBACK_1(PortMainLayer::layerSelectCallback, this,LayerType::organize));
    organizeButton->setPosition(battleButton->getPosition().x, 340);
    auto supplyButton = MenuItemImage::create("interface/PortMain/image 454.png", "interface/PortMain/image 461.png", CC_CALLBACK_1(PortMainLayer::layerSelectCallback, this, LayerType::supply));
    supplyButton->setPosition(100, 260);
    auto remodeButton = MenuItemImage::create("interface/PortMain/image 385.png", "interface/PortMain/image 392.png", CC_CALLBACK_1(PortMainLayer::layerSelectCallback, this, LayerType::remode));
    remodeButton->setPosition(345, 260);
    auto repairButton = MenuItemImage::create("interface/PortMain/image 444.png", "interface/PortMain/image 451.png", CC_CALLBACK_1(PortMainLayer::layerSelectCallback, this, LayerType::repair));
    repairButton->setPosition(145, 110);
    auto factoryButton = MenuItemImage::create("interface/PortMain/image 395.png", "interface/PortMain/image 402.png", CC_CALLBACK_1(PortMainLayer::layerSelectCallback, this, LayerType::factory));
    factoryButton->setPosition(300, 110);
    
    MenuItemSprite* settingButton = MenuItemImage::create("interface/PortMain/image 81.png", "interface/PortMain/image 81.png", CC_CALLBACK_1(PortScene::menuSettingCallback, parent));
    settingButton->setPosition(776, 28);
    
    
    auto menu = Menu::create(organizeButton, repairButton, factoryButton, battleButton, supplyButton, remodeButton,settingButton, NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);

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
    parent->SetCurrLayer(type);
}




