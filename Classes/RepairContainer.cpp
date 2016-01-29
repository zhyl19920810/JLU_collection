//
//  RepairContainer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/29/16.
//
//

#include "RepairContainer.hpp"


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

void RepairContainer::update(Kantai* kantai)
{
    
}

void RepairContainer::fastRepairCallback(cocos2d::Ref *pSender)
{
    
}

void RepairContainer::setFastRepairVisible(bool bVisible)
{
    fastRepairUp->setVisible(!bVisible);
    fastRepair->setVisible(bVisible);
}


bool RepairContainer::init(int position)
{
    bool bRet=false;
    
    do
    {
        if (!Node::init())
        {
            break;
        }
        auto size=Director::getInstance()->getVisibleSize();
        this->position=position;
        kantaiBg=Sprite::create("RepairMain/repairKantaiBg.png");
        kantaiBg->setPosition(Vec2::ZERO);
        addChild(kantaiBg);
        
        kantaiName=Label::create("", "fonts/DengXian.ttf", 20);
        kantaiName->setPosition(Vec2(288, kantaiBg->getContentSize().height/2));
        kantaiName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        kantaiBg->addChild(kantaiName);
        hpBar=new HpBar(100, 100);
        hpBar->setPosition(288,kantaiBg->getContentSize().height/2-17);
        kantaiBg->addChild(hpBar);
        
        fastRepair=MenuItemSprite::create(Sprite::create("RepairMain/fastRepair1.png"), Sprite::create("RepairMain/fastRepair2.png"), CC_CALLBACK_1(RepairContainer::fastRepairCallback, this));
        fastRepair->setPosition(Vec2(625, kantaiBg->getContentSize().height/2));
        addChild(fastRepair);
        kantaiBg->addChild(fastRepair);
        fastRepairUp=Sprite::create("RepairMain/fastRepair3.png");
        fastRepairUp->setPosition(fastRepair->getPosition());
        kantaiBg->addChild(fastRepairUp);
        
        kantaiLv=Label::create("","fonts/DengXian.ttf",15);
        kantaiLv->setPosition(365,62);
        kantaiLv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        kantaiBg->addChild(kantaiLv);
        
        kantaiHp=Label::create();
        kantaiHp->setPosition(420,-37);
        kantaiHp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        kantaiBg->addChild(kantaiHp);
        
        stars=new Stars;
        stars->setPosition(395,57);
        kantaiBg->addChild(stars);
        
        kantaiCard=KantaiCard::create();
        kantaiCard->setPosition(125,37);
        kantaiBg->addChild(kantaiCard);
        
        selectDocks=Sprite::create();
        selectDocks->setPosition(125,37);
        kantaiBg->addChild(selectDocks);
        
        bRet=true;
    }while(0);

    return bRet;
}

