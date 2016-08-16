//
//  RepairSelectEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/30/16.
//
//

#include "RepairSelectEntity.hpp"
#include "dock.hpp"
#include "portRepairLayer.h"
#include "ViewMgr.hpp"


NS_KCL_BEGIN


RepairSelectEntity* RepairSelectEntity::create(Vec2 vec)
{
    RepairSelectEntity* pRet=new RepairSelectEntity;
    if (pRet&&pRet->init(vec))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


void RepairSelectEntity::initTitle()
{
    auto tmp=bgImg->getContentSize()/2;
    
    auto repairSelectTitle=Sprite::create("RepairMain/repairSelectTitle.png");
    repairSelectTitle->setPosition(tmp.width-47,tmp.height+200);
    bgImg->addChild(repairSelectTitle);
    
    
    Sprite* bgImg1=Sprite::create("RepairMain/repairSelectBg2.png");
    bgImg1->setPosition(tmp.width-5,tmp.height+105);
    bgImg->addChild(bgImg1);
    
    auto repairTime=Sprite::create("RepairMain/repairTime.png");
    repairTime->setPosition(tmp.width-78,tmp.height+29);
    bgImg->addChild(repairTime);
    
    auto fastRepairSprite=Sprite::create("RepairMain/fastRepairLabel.png");
    fastRepairSprite->setPosition(tmp.width-78,tmp.height-2);
    bgImg->addChild(fastRepairSprite);
    
    auto repairSteelSprite=Sprite::create("RepairMain/repairSteelLabel.png");
    repairSteelSprite->setPosition(tmp.width-45,tmp.height-44);
    bgImg->addChild(repairSteelSprite);
    
    
    auto repairFuelSprite=Sprite::create("RepairMain/repairFuelLabel.png");
    repairFuelSprite->setPosition(tmp.width-45,tmp.height-80);
    bgImg->addChild(repairFuelSprite);
    
    startRepair=MenuItemSprite::create(Sprite::create("RepairMain/startRepair1.png"), Sprite::create("RepairMain/startRepair2.png"),Sprite::create("RepairMain/startRepair3.png"), CC_CALLBACK_1(RepairSelectEntity::startRepairCallback, this));
    startRepair->setPosition(tmp.width-10,tmp.height-155);
    mn=Menu::create();
    mn->setPosition(Vec2::ZERO);
    mn->addChild(startRepair);
    bgImg->addChild(mn);
}




bool RepairSelectEntity::init(Vec2 vec)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!UnitEntity::init(vec));

        initTitle();
        initEntity();
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}


void RepairSelectEntity::initEntity()
{
    initKantai();
}


void RepairSelectEntity::startRepairCallback(cocos2d::Ref *pSender)
{
    auto panel=dynamic_cast<PortRepairLayer*>(VIEW_MGR->getPanel(PanelType::PORT_REPAIR));
    panel->startRepairKantai(kantai, repairSteel, repairFuel, repairTime);
//    int position=UserDefault::getInstance()->getIntegerForKey("repairPosition");
//    auto parent=dynamic_cast<PortRepairLayer*>(getParent());
//    sDock.repairKantai(kantai, position, repairSteel, repairFuel, repairTime);
//    moveOut();
//    parent->hideList(NULL);
//    parent->updateContainer();
}


void RepairSelectEntity::setStartRepairVisible(bool bVisible)
{
    startRepair->setEnabled(bVisible);
}


void RepairSelectEntity::initKantai()
{
    auto tmp=bgImg->getContentSize()/2;
    kantaiName=Label::create("","fonts/DengXian.ttf",20);
    kantaiName->setPosition(tmp.width-85,tmp.height+145);
    kantaiName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kantaiName->setColor(Color3B::BLACK);
    bgImg->addChild(kantaiName);
    
    lvIcon=Sprite::create("CommonAssets/image 111.png");
    lvIcon->setPosition(tmp.width+30,tmp.height+145);
    bgImg->addChild(lvIcon);
    
    kantaiLv=Label::create("","fonts/DengXian.ttf",15);
    kantaiLv->setPosition(lvIcon->getPosition().x+lvIcon->getContentSize().width,tmp.height+145);
    kantaiLv->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kantaiLv->setColor(Color3B::BLACK);
    bgImg->addChild(kantaiLv);
    
    kancaiCard=KantaiCard::create();
    kancaiCard->setPosition(tmp.width-5,tmp.height+110);
    bgImg->addChild(kancaiCard);
    
    kantaiHp=Label::create("","fonts/DengXian.ttf",10);
    kantaiHp->setPosition(tmp.width+40,tmp.height+75);
    kantaiHp->setColor(Color3B::BLACK);
    kantaiHp->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(kantaiHp);
    
    hpBar=new RepairHpBar(0,1);
    hpBar->setPosition(tmp.width-5,65+tmp.height);
    hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
    bgImg->addChild(hpBar);
    
    repairTimeLabel=Label::create("","fonts/DengXian.ttf",15);
    repairTimeLabel->setPosition(tmp.width+20,tmp.height+25);
    repairTimeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    repairTimeLabel->setColor(Color3B::BLACK);
    bgImg->addChild(repairTimeLabel);
    
    fastRepairToggle=MenuItemToggle::createWithCallback(CC_CALLBACK_1(RepairSelectEntity::fastRepairCallback, this), MenuItemSprite::create(Sprite::create("RepairMain/image 163.png"),Sprite::create("RepairMain/image 163.png")),MenuItemSprite::create(Sprite::create("RepairMain/image 167.png"), Sprite::create("RepairMain/image 167.png")), NULL);
    fastRepairToggle->setPosition(tmp.width+50,tmp.height-5);
    mn->addChild(fastRepairToggle);
    
    repairSteelLabel=Label::create("","fonts/DengXian.ttf",10);
    repairSteelLabel->setPosition(tmp.width+80,tmp.height-45);
    repairSteelLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    repairSteelLabel->setColor(Color3B::BLACK);
    bgImg->addChild(repairSteelLabel);
    
    repairFuelLabel=Label::create("", "fonts/DengXian.ttf", 10);
    repairFuelLabel->setPosition(tmp.width+80,tmp.height-80);
    repairFuelLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    repairFuelLabel->setColor(Color3B::BLACK);
    bgImg->addChild(repairFuelLabel);
    
    
}


void RepairSelectEntity::fastRepairCallback(cocos2d::Ref *pSender)
{

}

void RepairSelectEntity::convertTimeToChar(int time,char *name)
{
    char tmp[10];
    bzero(name, sizeof(name));
    int hour,minutes,second;
    hour=time/3600;
    if (!hour)
    {
        sprintf(name, "00:");
    }
    else if(hour<10)
    {
        sprintf(name, "0%d:",hour);
    }
    else
    {
        sprintf(name, "%d:",hour);
    }
    
    time=time%3600;
    minutes=time/60;
    if (!minutes)
    {
        strcat(name, "00:");
    }
    else if (minutes<10)
    {
        sprintf(tmp, "0%d:",minutes);
        strcat(name, tmp);
    }
    else
    {
        sprintf(tmp, "%d:",minutes);
        strcat(name, tmp);
    }
    
    time=time%60;
    second=time;
    if (!second)
    {
        strcat(name, "00");
    }
    else if (second<10)
    {
        sprintf(tmp, "0%d",second);
        strcat(name, tmp);
    }
    else
    {
        sprintf(tmp, "%d",second);
        strcat(name, tmp);
    }
}



void RepairSelectEntity::updateKantai(Kantai *kantai)
{
    this->kantai=kantai;
    if (sDock.canRepairKantai(kantai, repairSteel, repairFuel, repairTime))
    {
        setStartRepairVisible(true);
    }
    else
    {
        setStartRepairVisible(false);
    }
    char name[30];
    bzero(name, sizeof(name));
    sprintf(name, "%s",kantai->getKantaiName());
    kantaiName->setString(name);
    
    sprintf(name, "%d",kantai->getCurrLV());
    kantaiLv->setString(name);
    
    kancaiCard->updateCard(kantai);
    
    sprintf(name, "%d//%d",kantai->getCurrHp(),kantai->getMaxHp());
    kantaiHp->setString(name);
    
    hpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
    
    convertTimeToChar(repairTime,name);
    repairTimeLabel->setString(name);
    
    
    sprintf(name, "%d",repairSteel);
    repairSteelLabel->setString(name);
    
    sprintf(name, "%d",repairFuel);
    repairFuelLabel->setString(name);
}


NS_KCL_END


