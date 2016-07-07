//
//  KantaiDestroyEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/6/16.
//
//

#include "KantaiDestroyEntity.hpp"
#include "FactoryListEntity.hpp"
#include "portFactoryLayer.h"


NS_KCL_BEGIN

void KantaiDestroyEntity::initBg()
{
    bgImg=Sprite::create("RepairMain/repairSelectBg1.png");
    bgImg->setPosition(695,200);
    addChild(bgImg);
    auto tmp=bgImg->getContentSize()/2;
    
    auto destroyEntityBar=Sprite::create("RepairMain/repairBar.png");
    destroyEntityBar->setPosition(tmp.width+288,tmp.height+197);
    bgImg->addChild(destroyEntityBar);
    
    
    
    auto destroyEntityTitle=Sprite::create("ArsenalMain/image 435.png");
    destroyEntityTitle->setPosition(tmp.width-47,tmp.height+200);
    bgImg->addChild(destroyEntityTitle);
    
    
    auto fuelIcon=Sprite::create("ArsenalMain/image 456.png");
    fuelIcon->setPosition(tmp.width-100,tmp.height+123);
    fuelIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(fuelIcon);
    auto ammoIcon=Sprite::create("ArsenalMain/image 459.png");
    ammoIcon->setPosition(fuelIcon->getPosition()+Vec2(0, -37));
    ammoIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(ammoIcon);
    auto steelIcon=Sprite::create("ArsenalMain/image 461.png");
    steelIcon->setPosition(fuelIcon->getPosition()+Vec2(0, -74));
    steelIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(steelIcon);
    auto alIcon=Sprite::create("ArsenalMain/image 463.png");
    alIcon->setPosition(fuelIcon->getPosition()+Vec2(0, -111));
    alIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(alIcon);
}

void KantaiDestroyEntity::initKantai()
{
    auto tmp=bgImg->getContentSize()/2;
    fuel=Label::create("","fonts/DengXian.ttf",20);
    fuel->setPosition(tmp.width+80,tmp.height+123);
    fuel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fuel->setColor(Color3B::BLACK);
    bgImg->addChild(fuel);
    
    ammo=Label::create("","fonts/DengXian.ttf",20);
    ammo->setPosition(fuel->getPosition()+Vec2(0, -37));
    ammo->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    ammo->setColor(Color3B::BLACK);
    bgImg->addChild(ammo);
    
    steel=Label::create("","fonts/DengXian.ttf",20);
    steel->setPosition(fuel->getPosition()+Vec2(0, -74));
    steel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    steel->setColor(Color3B::BLACK);
    bgImg->addChild(steel);
    
    al=Label::create("","fonts/DengXian.ttf",20);
    al->setPosition(fuel->getPosition()+Vec2(0, -111));
    al->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    al->setColor(Color3B::BLACK);
    bgImg->addChild(al);
    
    kantaiCard=KantaiCard::create();
    kantaiCard->setPosition(tmp.width,tmp.height-60);
    bgImg->addChild(kantaiCard);
    
    destroyButton=MenuItemButton::create(Sprite::create("ArsenalMain/destroyButton1.png"), Sprite::create("ArsenalMain/destroyButton2.png"), Sprite::create("ArsenalMain/destroyButton3.png"), CC_CALLBACK_1(KantaiDestroyEntity::destroyCallback, this));
    bgImg->addChild(destroyButton);
    destroyButton->setPosition(tmp.width-5,tmp.height-160);
}

void KantaiDestroyEntity::update(Kantai *kantai)
{
    this->kantai=kantai;
    fuelVal=100;
    ammoVal=100;
    steelVal=150;
    alVal=50;
    fuel->setString(to_string(fuelVal));
    ammo->setString(to_string(ammoVal));
    steel->setString(to_string(steelVal));
    al->setString(to_string(alVal));
    
    kantaiCard->updateCard(kantai);
    destroyButton->setButtonVisible(canDestroyKantai(kantai));
}

bool KantaiDestroyEntity::canDestroyKantai(Kantai *kantai)
{
    bool canDestory=true;
    canDestory=canDestory&&(!kantai->getKantaiLock());
    canDestory=canDestory&&(!kantai->getFleet());
    return canDestory;
}


KantaiDestroyEntity::KantaiDestroyEntity()
{
    kantai=NULL;
    hidden=true;
}

void KantaiDestroyEntity::destroyCallback(cocos2d::Ref *pSender)
{
    auto factoryList=static_cast<FactoryListEntity*>(this->getParent());
    auto factoryLayer=static_cast<PortFactoryLayer*>(factoryList->getParent());
    CallFunc* f1=CallFunc::create([=]()
                                  {
                                      factoryLayer->destroyKantai(kantai, fuelVal, steelVal, ammoVal, alVal);
                                      factoryList->destoryKantai(kantai);
                                  });
    CallFunc* f2=CallFunc::create([=]()
                                  {
                                      factoryList->hideSelect(this);
                                  });
    CallFunc* f3=CallFunc::create([=]()
                                  {
                                      factoryList->updateRows();
                                  });
    CallFunc* f4=CallFunc::create([=]()
                                  {
                                      factoryLayer->hideDestroy(this);
                                  });
    this->runAction(Sequence::create(f1,f3,f2,DelayTime::create(0.5),f4,DelayTime::create(1.5), NULL));

    
    //这里加上layer中destroy的函数
    //organizeList->changeContainer( kantai);
}


void KantaiDestroyEntity::moveOut()
{
    if (!hidden)
    {
        kantai=NULL;
        this->runAction(MoveBy::create(0.15, Point(238, 0)));
        hidden = true;
    }
    
}
void KantaiDestroyEntity::moveIn()
{
    if (hidden)
    {
        this->runAction(MoveBy::create(0.15, Point(-238, 0)));
        hidden = false;
    }
}

bool KantaiDestroyEntity::init()
{
    bool bRet=false;
    do
    {
        if (!Layer::init())
        {
            break;
        }
        
        initBg();
        initKantai();
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}


NS_KCL_END

