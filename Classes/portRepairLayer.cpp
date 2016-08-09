//
//  portRepairLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portRepairLayer.h"
#include "Player.h"

NS_KCL_BEGIN

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
        if (!Panel::init()) {
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
    auto size=Director::getInstance()->getVisibleSize();
    auto bgimg = Sprite::create("RepairMain/repairBg.png");
    this->addChild(bgimg);
    bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto repairTitle = Sprite::create("RepairMain/repairTitle.png");
    addChild(repairTitle);
    repairTitle->setPosition(bgimg->getPosition()+Vec2(0, 197)+Vec2(-290, 4));
    
    listCover=LayerCover::create(CC_CALLBACK_1(PortRepairLayer::hideList, this));
    listCover->setPosition(0,0);
    addChild(listCover,2);
    
    listEntity=RepairListEntity::create();
    addChild(listEntity,3);
    listEntity->setPosition(size.width,0);
    addChild(listEntity->selectEntity,4);
}

void PortRepairLayer::updateContainer()
{
    for (int i=0; i<containerSize; ++i)
    {
        container[i]->updateUnit();
    }
}

void PortRepairLayer::showList(int index)
{
    if (listEntity->isHidden()) {
        listEntity->moveIn();
    }
    listCover->setCoverEnable(true);
    listEntity->updateRows();
    
}

void PortRepairLayer::hideList(cocos2d::Ref *pSender)
{
    listEntity->moveOut();
    listCover->setCoverEnable(false);
}

NS_KCL_END



