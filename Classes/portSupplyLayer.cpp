//
//  portSupplyLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portSupplyLayer.h"
#include "portScene.h"

PortSupplyLayer::PortSupplyLayer(PortScene* parent)
{
    this->parent = parent;
    initLayer();
}

void PortSupplyLayer::initLayer()
{
    auto bgimg = Sprite::create("interface/SupplyMain/image 87.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto bgimg2 = Sprite::create("interface/SupplyMain/image 1.png");
    this->addChild(bgimg2);
    bgimg2->setPosition(695, 200);
    
    auto label_top_right = Sprite::create("interface/SupplyMain/image 6.png");
    this->addChild(label_top_right);
    label_top_right->setPosition(700, 360);
    
    auto fuelBox = Sprite::create("interface/SupplyMain/image 5.png");
    this->addChild(fuelBox);
    fuelBox->setPosition(650, 295);
    
    auto ammoBox = Sprite::create("interface/SupplyMain/image 4.png");
    this->addChild(ammoBox);
    ammoBox->setPosition(750, 295);
    
    auto fuelBg = Sprite::create("interface/SupplyMain/image 15.png");
    this->addChild(fuelBg);
    fuelBg->setPosition(650, 190);
    
    auto ammoBg = Sprite::create("interface/SupplyMain/image 14.png");
    this->addChild(ammoBg);
    ammoBg->setPosition(750, 190);
    
    auto fuelButton = MenuItemImage::create("interface/SupplyMain/image 55.png", "interface/SupplyMain/image 57.png", CC_CALLBACK_1(PortSupplyLayer::callBack, this));
    fuelButton->setPosition(624, 50);
    auto midButton = MenuItemImage::create("interface/SupplyMain/image 71.png", "interface/SupplyMain/image 73.png", CC_CALLBACK_1(PortSupplyLayer::callBack, this));
    midButton->setPosition(700, 50);
    auto ammoButton = MenuItemImage::create("interface/SupplyMain/image 63.png", "interface/SupplyMain/image 65.png", CC_CALLBACK_1(PortSupplyLayer::callBack, this));
    ammoButton->setPosition(776, 50);
    
    auto menu = Menu::create(fuelButton, midButton, ammoButton, NULL);
    this->addChild(menu);
    menu->setPosition(0, 0);
    
}
void PortSupplyLayer::callBack(Ref* pSender)
{
    
}

