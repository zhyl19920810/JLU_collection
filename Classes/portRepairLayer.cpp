//
//  portRepairLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portRepairLayer.h"
#include "Player.h"

PortRepairLayer::PortRepairLayer()
{
    //this->setZOrder(-1);
    containerSize=sPlayer.getMaxDockSize();
    container.resize(4);
}


bool PortRepairLayer::init()
{
    bool bRet=false;
    do
    {
        if (!Layer::init()) {
            break;
        }
        initLayer();
        initContainer();
        
        bRet=true;
    }while(0);
    return bRet;
}


void PortRepairLayer::initContainer()
{
    int i=0;
    for (; i<containerSize; ++i)
    {
        container[i]=RepairContainer::create(i+1);
        addChild(container[i]);
        container[i]->setPosition(465,320-i*80);
    }
    for (; i<4; ++i)
    {
        container[i]=NoReapirContainer::create(i+1);
        addChild(container[i]);
        container[i]->setPosition(465,320-i*80);
    }
}


void PortRepairLayer::initLayer()
{
    auto bgimg = Sprite::create("RepairMain/repairBg.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto repairBar = Sprite::create("RepairMain/repairBar.png");
    addChild(repairBar);
    repairBar->setPosition(bgimg->getPosition()+Vec2(0, 197));
    
    auto repairTitle = Sprite::create("RepairMain/repairTitle.png");
    addChild(repairTitle);
    repairTitle->setPosition(repairBar->getPosition()+Vec2(-290, 4));
    
}

void PortRepairLayer::updateContainer()
{
    for (int i=0; i<containerSize; ++i)
    {
        container[i]->updateUnit();
    }
}
