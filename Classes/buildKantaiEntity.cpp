//
//  buildKantaiEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#include "buildKantaiEntity.hpp"
#include "arsenal.hpp"
#include "portFactoryLayer.h"
#include "LayerCover.hpp"
#include "EventPauseGuard.hpp"


NS_KCL_BEGIN

#define HIDE_POS (Vec2(550,0))
#define SHOW_POS (Vec2(-550,0))
#define MOVE_TIME 0.25


BuildKantaiEntity* BuildKantaiEntity::create(factoryBM mode,Vec2 pos)
{
    BuildKantaiEntity* pRet=new BuildKantaiEntity;
    if (pRet&&pRet->init(mode,pos))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool BuildKantaiEntity::init(factoryBM mode,Vec2 pos)
{
    this->hidden=true;
    this->mode=mode;
    bool bRet=false;
    do
    {
        if (!Node::init())
        {
            break;
        }
        initBg(pos);
        updateButton();
        bRet=true;
    }while(0);
    
    return bRet;
}


void BuildKantaiEntity::initBg(Vec2 pos)
{
    cover=LayerCover::create(CC_CALLBACK_1(BuildKantaiEntity::moveOut, this));
    cover->setPosition(pos);
    addChild(cover,-1);

    entity=Node::create();
    addChild(entity);
    entity->setPosition(Vec2::ZERO);
    
    imgbg=Sprite::create("ArsenalMain/factoryBg.png");
    imgbg->setPosition(Vec2::ZERO);
    entity->addChild(imgbg);
    //log("%f  %f",imgbg->getContentSize().width,imgbg->getContentSize().height);
    
    Sprite* imgbg2=Sprite::create("ArsenalMain/imgbg2.png");
    imgbg2->setPosition(260,84);
    imgbg->addChild(imgbg2);
    
    mn=Menu::create();
    mn->setPosition(Vec2::ZERO);
    imgbg->addChild(mn);
    
    auto entityBar=Sprite::create("ArsenalMain/titleBar.png");
    entityBar->setPosition(390,395);
    imgbg->addChild(entityBar);
    
    auto entityTitle=Sprite::create("ArsenalMain/buildEntityTitle.png");
    entityTitle->setPosition(55,400);
    imgbg->addChild(entityTitle);
    

    fuelUnit=FuelBuildUnit::create(mode);
    fuelUnit->setPosition(145,303);
    imgbg->addChild(fuelUnit);
    
    steelUnit=SteelBuildUnit::create(mode);
    steelUnit->setPosition(373,303);
    imgbg->addChild(steelUnit);
    
    ammoUnit=AmmoBuildUnit::create(mode);
    ammoUnit->setPosition(145,172);
    imgbg->addChild(ammoUnit);
    
    AlUnit=AlBuildUnit::create(mode);
    AlUnit->setPosition(373,172);
    imgbg->addChild(AlUnit);
    
    startBuild=MenuItemSprite::create(Sprite::create("ArsenalMain/startBuild1.png"), Sprite::create("ArsenalMain/startBuild2.png"),CC_CALLBACK_1(BuildKantaiEntity::startBuildCallback, this));
    startBuild->setPosition(441,37);
    mn->addChild(startBuild);
    
    startBuildUp=Sprite::create("ArsenalMain/startBuild3.png");
    startBuildUp->setPosition(startBuild->getPosition());
    imgbg->addChild(startBuildUp);
    
    
    auto fastBuildLabel=Sprite::create("ArsenalMain/fastBuildLabel.png");
    fastBuildLabel->setPosition(93,83);
    imgbg->addChild(fastBuildLabel);
    
    auto developMaterialLabel=Sprite::create("ArsenalMain/developMaterialLabel.png");
    developMaterialLabel->setPosition(313,84);
    imgbg->addChild(developMaterialLabel);
    
    auto developMaterialIcon=Sprite::create("ArsenalMain/developMaterialIcon.png");
    developMaterialIcon->setPosition(272,84);
    imgbg->addChild(developMaterialIcon);
    
    auto icon2=Sprite::create("ArsenalMain/icon2.png");
    icon2->setPosition(405,83);
    imgbg->addChild(icon2);
    
    MenuItemSprite* shop=MenuItemSprite::create(Sprite::create("ArsenalMain/shopIcon1.png"), Sprite::create("ArsenalMain/shopIcon2.png"), CC_CALLBACK_1(BuildKantaiEntity::callback, this));
    shop->setPosition(335,37);
    imgbg->addChild(shop);
    
    eventListener=EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan=[=](Touch* touch,Event* event)->bool
    {
        auto rect=Rect(0,0,imgbg->getContentSize().width,imgbg->getContentSize().height);
        auto pos=imgbg->convertToNodeSpace(touch->getLocation());
        if (rect.containsPoint(pos))
        {
            return true;
        }
        return false;
    };
    eventListener->onTouchMoved=[=](Touch* touch,Event* event){};
    eventListener->onTouchEnded=[=](Touch* touch,Event* event){};
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
}



void BuildKantaiEntity::startBuildCallback(cocos2d::Ref *pSender)
{
    auto parent=static_cast<PortFactoryLayer*>(_parent);
    parent->startBuild(fuelUnit->getResouce(), steelUnit->getResouce(), ammoUnit->getResouce(), AlUnit->getResouce());
}

void BuildKantaiEntity::callback(cocos2d::Ref *pSender)
{
    
}

void BuildKantaiEntity::setStartBuildVisible(bool bVisible)
{
    startBuild->setVisible(bVisible);
    startBuild->setEnabled(bVisible);
    startBuildUp->setVisible(!bVisible);
}

bool BuildKantaiEntity::canStartBuild()
{
    bool bRet=fuelUnit->canBuildKantai()&&ammoUnit->canBuildKantai()&&steelUnit->canBuildKantai()&&AlUnit->canBuildKantai();
    return bRet;
}


void BuildKantaiEntity::updateButton()
{
    if (canStartBuild())
    {
        setStartBuildVisible(true);
    }
    else
    {
        setStartBuildVisible(false);
    }
}

void BuildKantaiEntity::moveIn()
{
    if (hidden)
    {
        CallFunc* moveByBefore=CallFunc::create([=]()
        {
           cover->setCoverEnable(true);
           EventPauseGuard::pause();
        });
        auto move=MoveBy::create(MOVE_TIME, SHOW_POS);
        CallFunc* moveByFinish=CallFunc::create([=]()
        {
            EventPauseGuard::resume();
        });
        entity->runAction(Sequence::create(moveByBefore,move,moveByFinish, NULL));
        hidden = false;
    }
}



void BuildKantaiEntity::moveOut(Ref* ref)
{
    if (!hidden)
    {
        CallFunc* moveByBefore=CallFunc::create([=]()
        {
           EventPauseGuard::pause();
        });
        auto move=MoveBy::create(MOVE_TIME, HIDE_POS);
        CallFunc* moveByFinish=CallFunc::create([=]()
        {
            EventPauseGuard::resume();
            cover->setCoverEnable(false);
        });
        entity->runAction(Sequence::create(moveByBefore,move,moveByFinish, NULL));
        hidden = true;
    }
}

void BuildKantaiEntity::updateRes()
{
    ammoUnit->updateRes();
    AlUnit->updateRes();
    steelUnit->updateRes();
    fuelUnit->updateRes();
    updateButton();
}

NS_KCL_END

