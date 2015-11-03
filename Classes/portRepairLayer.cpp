//
//  portRepairLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portRepairLayer.h"

PortRepairLayer::PortRepairLayer(Node* parent)
{
    this->parent = parent;
    this->setZOrder(-1);
    initLayer();
}

void PortRepairLayer::initLayer()
{
    auto bgimg = Sprite::create("interface/RepairMain/image 5.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto p1 = Sprite::create("interface/RepairMain/image 70.png");
    auto p2 = Sprite::create("interface/RepairMain/image 70.png");
    auto p3 = Sprite::create("interface/RepairMain/image 70.png");
    auto p4 = Sprite::create("interface/RepairMain/image 70.png");
    
    p1->setPosition(480, 320);
    p2-> setPosition(480, 240);
    p3->setPosition(480,160);
    p4->setPosition(480, 80);
    
    this->addChild(p1);
    this->addChild(p2);
    this->addChild(p3);
    this->addChild(p4);
}
