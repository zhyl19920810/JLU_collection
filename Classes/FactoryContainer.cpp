//
//  portFactoryContainer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#include "FactoryContainer.hpp"
#include "portFactoryLayer.h"

NS_KCL_BEGIN


FactoryContainer* FactoryContainer::create(int position)
{
    FactoryContainer* tmp=new FactoryContainer;
    if (tmp&&tmp->init(position))
    {
        tmp->autorelease();
        return tmp;
    }
    delete tmp;
    tmp=NULL;
    return tmp;
}


bool FactoryContainer::init(int position)
{
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        this->position=position;
        initBg();
        initButton();
        initArsenal();
        update();
        
        bRet=true;
    }while(0);
    
    return bRet;
}




void FactoryContainer::initBg()
{
    Sprite* remainTime=Sprite::create("ArsenalMain/image 26.png");
    remainTime->setPosition(50,40);
    addChild(remainTime);
    
    Sprite* slipway=Sprite::create("ArsenalMain/image 25.png");
    slipway->setPosition(225,0);
    addChild(slipway);
    
}

void FactoryContainer::initButton()
{

    buildButton=MenuItemSprite::create(Sprite::create("ArsenalMain/image 52.png"), Sprite::create("ArsenalMain/image 52.png"),CC_CALLBACK_1(FactoryContainer::buildCallback, this));
    buildButton->setPosition(225,30);
    getButton=MenuItemSprite::create(Sprite::create("ArsenalMain/image 56.png"), Sprite::create("ArsenalMain/image 56.png"),CC_CALLBACK_1(FactoryContainer::getCallback, this));
    getButton->setPosition(buildButton->getPosition());
    
    mn=Menu::create(buildButton,getButton, NULL);
    addChild(mn);
    mn->setPosition(Vec2::ZERO);
    
    fastBuild=MenuItemButton::create(Sprite::create("ArsenalMain/fastBuild1.png"), Sprite::create("ArsenalMain/fastBuild2.png"), Sprite::create("ArsenalMain/fastBuild3.png"), CC_CALLBACK_1(FactoryContainer::fastBuildCallback, this));
    fastBuild->setPosition(350,25);
    addChild(fastBuild);
    
}

void FactoryContainer::buildCallback(Ref* pSender)
{
    auto parent=static_cast<PortFactoryLayer*>(_parent);
    parent->showList(position);
    
}

void FactoryContainer::getCallback(cocos2d::Ref *pSender)
{
    sArsenal.finishBuildingKantai(position);
    update();
    //还有引出新的界面
}


void FactoryContainer::fastBuildCallback(cocos2d::Ref *pSender)
{
    
}


void FactoryContainer::initArsenal()
{
    shipFinish=Sprite::create("ArsenalMain/image 36.png");
    addChild(shipFinish);
    shipFinish->setPosition(225,30);
    
    title=Sprite::create();
    addChild(title);
    title->setPosition(50,65);
    
    timer=RepairTimer::create();
    timer->setPosition(10,15);
    addChild(timer);
    
}

void FactoryContainer::update()
{
    if (sArsenal.haveShip(position))
    {
        if (sArsenal.isBuildingFinished(position))
        {
            fastBuild->setButtonVisible(false);
            state=finish;
            title->setTexture("ArsenalMain/image 120.png");
            buildButton->setVisible(false);
            getButton->setVisible(true);
            shipFinish->setVisible(true);
        }
        else
        {
            auto data=sArsenal.getArsenal(position);
            buildButton->setVisible(false);
            getButton->setVisible(false);
            shipFinish->setVisible(false);
            fastBuild->setButtonVisible(true);
            state=building;
            title->setTexture("ArsenalMain/image 118.png");
            timer->setTime(data.remainTime);
        }
    }else
    {
        buildButton->setVisible(true);
        getButton->setVisible(false);
        shipFinish->setVisible(false);
        fastBuild->setButtonVisible(false);
        state=free;
        title->setTexture("ArsenalMain/image 116.png");
    }
    
    //时间加上
}


NS_KCL_END








