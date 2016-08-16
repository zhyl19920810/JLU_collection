//
//  RepairContainer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "RepairContainer.hpp"
#include "dock.hpp"
#include "portRepairLayer.h"
#include "TimeUtil.hpp"


NS_KCL_BEGIN

RepairContainer::RepairContainer()
{
}


RepairContainer* RepairContainer::create(int position)
{
    RepairContainer* pRet=new RepairContainer();
    if (pRet&&pRet->init(position)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}

void RepairContainer::updateUnit()
{
    auto data=sDock.getDockData(position);
    auto kantai=data.kantai;
    if (kantai)
    {
        char name[30];
        bzero(name, sizeof(name));
        haveKantaiInReparing(true);
        kantaiName->setString(kantai->getKantaiName());
        sprintf(name, "%d//%d",kantai->getCurrHp(),kantai->getMaxHp());
        kantaiHp->setString(name);
        sprintf(name, "%d",kantai->getCurrLV());
        kantaiLv->setString(name);
        stars->setNumber(kantai->getStars());
        repairHpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
        kantaiCard->updateCard(kantai);
        timer->setTime(data.complateTime);
    }
    else
    {
        haveKantaiInReparing(false);
    }
}



void RepairContainer::fastRepairCallback(cocos2d::Ref *pSender)
{
    
}

void RepairContainer::setFastRepairVisible(bool bVisible)
{
    if (haveKantai)
    {
        fastRepairUp->setVisible(!bVisible);
        fastRepair->setVisible(bVisible);
        fastRepair->setEnabled(bVisible);
    }
    else
    {
        fastRepairUp->setVisible(false);
        fastRepair->setVisible(false);
        fastRepair->setEnabled(false);
    }
}



void RepairContainer::initBg()
{
    this->position=position;
    kantaiBg=Sprite::create("RepairMain/repairKantaiBg.png");
    kantaiBg->setPosition(Vec2::ZERO);
    addChild(kantaiBg);
    
    Sprite* selectPic=Sprite::create("RepairMain/selectDock.png");
    selectPic->setOpacity(0);
    selectDocks=MenuItemSprite::create(selectPic, Sprite::create("RepairMain/selectDock.png"), CC_CALLBACK_1(RepairContainer::selectKantai, this));
    selectDocks->setPosition(125,37);
    mn=Menu::create();
    mn->setPosition(Vec2::ZERO);
    mn->addChild(selectDocks);
    kantaiBg->addChild(mn);
    LVIcon=Sprite::create("CommonAssets/LVIcon.png");
    LVIcon->setPosition(355,60);
    kantaiBg->addChild(LVIcon);
}

void RepairContainer::selectKantai(cocos2d::Ref *pSender)
{
    UserDefault::getInstance()->setIntegerForKey("repairPosition", position);
    auto parent=dynamic_cast<PortRepairLayer*>(this->getParent());
    parent->showList(position);
}


void RepairContainer::haveKantaiInReparing(bool visible)
{
    haveKantai=visible;
    selectDocks->setVisible(!visible);
    selectDocks->setEnabled(!visible);
    kantaiName->setVisible(visible);
    repairHpBar->setVisible(visible);
    setFastRepairVisible(visible);
    kantaiLv->setVisible(visible);
    kantaiHp->setVisible(visible);
    kantaiCard->setVisible(visible);
    stars->setVisible(visible);
    LVIcon->setVisible(visible);
    timer->setVisible(visible);
}


void RepairContainer::initKantai()
{
    kantaiName=Label::create("", "fonts/DengXian.ttf", 20);
    kantaiName->setPosition(Vec2(288, kantaiBg->getContentSize().height/2));
    kantaiName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    kantaiBg->addChild(kantaiName);
    repairHpBar=new RepairHpBar(0, 0);
    repairHpBar->setPosition(368,kantaiBg->getContentSize().height/2-17);
    kantaiBg->addChild(repairHpBar);
    
    fastRepair=MenuItemSprite::create(Sprite::create("RepairMain/fastRepair1.png"), Sprite::create("RepairMain/fastRepair2.png"), CC_CALLBACK_1(RepairContainer::fastRepairCallback, this));
    fastRepair->setPosition(Vec2(625, kantaiBg->getContentSize().height/2));
    mn->addChild(fastRepair);
    
    fastRepairUp=Sprite::create("RepairMain/fastRepair3.png");
    fastRepairUp->setPosition(fastRepair->getPosition());
    kantaiBg->addChild(fastRepairUp);
    
    kantaiLv=Label::create("","fonts/DengXian.ttf",17);
    kantaiLv->setPosition(365,57);
    kantaiLv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    kantaiBg->addChild(kantaiLv);
    
    kantaiHp=Label::create("","fonts/DengXian.ttf",10);
    kantaiHp->setPosition(420,kantaiBg->getContentSize().height/2-3);
    kantaiHp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    kantaiBg->addChild(kantaiHp);
    
    stars=Stars::create();
    stars->setPosition(395,57);
    kantaiBg->addChild(stars);
    
    kantaiCard=KantaiCard::create();
    kantaiCard->setPosition(125,37);
    kantaiBg->addChild(kantaiCard,0);
    
    timer=TimerEntity::create(CC_CALLBACK_0(RepairContainer::updateUnit, this));
    timer->setPosition(480,kantaiBg->getContentSize().height/2-10);
    kantaiBg->addChild(timer);
}

bool RepairContainer::init(int position)
{
    bool bRet=false;
    this->position=position;
    do
    {
        if (!Node::init())
        {
            break;
        }
        initBg();
        initKantai();
        updateUnit();
        
        bRet=true;
    }while(0);

    return bRet;
}




///NoReapirContainer
NoReapirContainer* NoReapirContainer::create(int position)
{
    NoReapirContainer* pRet=new NoReapirContainer();
    if (pRet&&pRet->init(position)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool NoReapirContainer::init(int position)
{
    bool bRet=false;
    this->position=position;
    do
    {
        if (Node::init())
        {
            break;
        }
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}

NS_KCL_END






