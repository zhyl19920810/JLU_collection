//
//  portFactoryLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portFactoryLayer.h"

PortFactoryLayer::PortFactoryLayer(Node* parent)
{
    this->parent = parent;
    initLayer();
}

void PortFactoryLayer::initLayer()
{
    auto bgimg = Sprite::create("interface/ArsenalMain/image 249.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto mainBody = Sprite::create("interface/ArsenalMain/image 3.png");
    this->addChild(mainBody);
    mainBody->setPosition(580, 200);
    
    auto buildButton = MenuItemImage::create("interface/ArsenalMain/image 180.png", "interface/ArsenalMain/image 178.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    buildButton->setPosition(230, 320);
    auto destroyButton = MenuItemImage::create("interface/ArsenalMain/image 184.png", "interface/ArsenalMain/image 186.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    destroyButton->setPosition(230, 245);
    auto developButton = MenuItemImage::create("interface/ArsenalMain/image 190.png", "interface/ArsenalMain/image 192.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    developButton->setPosition(230, 160);
    auto throwButton = MenuItemImage::create("interface/ArsenalMain/image 196.png", "interface/ArsenalMain/image 198.png", CC_CALLBACK_1(PortFactoryLayer::callBack, this));
    throwButton->setPosition(230, 80);
    
    auto menu = Menu::create(buildButton, destroyButton, developButton, throwButton, NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);
}

void PortFactoryLayer::callBack(Ref* pSender)
{}



