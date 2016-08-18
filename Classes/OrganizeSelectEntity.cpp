//
//  OrganizeSelectEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/2/16.
//
//

#include "OrganizeSelectEntity.hpp"
#include "portOrganizeLayer.h"
#include "KantaiListEntity.hpp"
#include "ViewMgr.hpp"
#include "EventPauseGuard.hpp"
#include "ValueBar.hpp"
#include "Star.hpp"
#include "LayerCover.hpp"
#include "HpBar.hpp"
#include "kantaiCard.hpp"
#include "MenuItemTouch.hpp"
#include "EquipmentContainer.hpp"
#include "ValueBar.hpp"


NS_KCL_BEGIN

OrganSelectEntity::OrganSelectEntity()
{
    equipContainer.resize(4);
    equipEmpty.resize(4);
}


OrganSelectEntity* OrganSelectEntity::create(Vec2 pos)
{
    OrganSelectEntity* pRet=new OrganSelectEntity;
    if (pRet&&pRet->init(pos))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}



bool OrganSelectEntity::init(Vec2 pos)
{
    bool bRet=false;
    do
    {
        if (!UnitEntity::init(pos))
        {
            break;
        }
        
        initTitle();
        initEntity();
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}

void OrganSelectEntity::initTitle()
{
    auto tmp=bgImg->getContentSize()/2;
    auto organSelectBar=Sprite::create("RepairMain/repairBar.png");
    organSelectBar->setPosition(tmp.width+288,tmp.height+197);
    bgImg->addChild(organSelectBar);
    
    auto organSelectTitle=Sprite::create("RepairMain/repairSelectTitle.png");
    organSelectTitle->setPosition(tmp.width-47,tmp.height+200);
    bgImg->addChild(organSelectTitle);
}



void OrganSelectEntity::initEntity()
{
    initButton();
    initKantai();
}

void OrganSelectEntity::initButton()
{
    auto tmp=bgImg->getContentSize()/2;
    changeShipButton=MenuItemButton::create(Sprite::create("OrganizeMain/changeShipButton2.png"), Sprite::create("OrganizeMain/changeShipButton3.png"), Sprite::create("OrganizeMain/changeShipButton1.png"), CC_CALLBACK_1(OrganSelectEntity::changeShipCallback, this));
    changeShipButton->setPosition(tmp.width-10,tmp.height-165);
    bgImg->addChild(changeShipButton);
}




void OrganSelectEntity::initKantai()
{
    auto tmp=bgImg->getContentSize()/2;
    kantaiName=Label::create("","fonts/DengXian.ttf",20);
    kantaiName->setPosition(tmp.width-85,tmp.height+160);
    kantaiName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kantaiName->setColor(Color3B::BLACK);
    bgImg->addChild(kantaiName);
    
    lvIcon=Sprite::create("CommonAssets/image 111.png");
    lvIcon->setPosition(tmp.width+30,tmp.height+160);
    bgImg->addChild(lvIcon);
    
    kantaiLv=Label::create("","fonts/DengXian.ttf",20);
    kantaiLv->setPosition(lvIcon->getPosition().x+lvIcon->getContentSize().width,tmp.height+160);
    kantaiLv->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kantaiLv->setColor(Color3B::BLACK);
    bgImg->addChild(kantaiLv);
    
    kantaiHp=Label::create("","fonts/DengXian.ttf",10);
    kantaiHp->setPosition(tmp.width-20,tmp.height+140);
    kantaiHp->setColor(Color3B::BLACK);
    kantaiHp->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(kantaiHp);
    
    hpBar=HpBar::create();
    hpBar->setPosition(tmp.width-55,tmp.height+140);
    hpBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(hpBar);
    
    stars=Stars::create();
    stars->setPosition(tmp.width+40,tmp.height+140);
    stars->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(stars);
    
    kantaiCard=KantaiCard::create();
    kantaiCard->setPosition(tmp.width-5,tmp.height+110);
    bgImg->addChild(kantaiCard);
    
    for (int i=0; i<4; ++i)
    {
        equipEmpty[i]=Sprite::create("CommonAssets/noEquipBg.png");
        equipEmpty[i]->setPosition(tmp.width-5,tmp.height+65-i*30);
        bgImg->addChild(equipEmpty[i]);
    }
    
    for (int i=0; i<4; ++i)
    {
        equipContainer[i]=EquipContainer::create();
        equipContainer[i]->setPosition(tmp.width-5,tmp.height+65-i*30);
        bgImg->addChild(equipContainer[i]);
    }
    
    firePower = Label::create("", "fonts/DengXian.ttf", 15);
    firePower->setColor(Color3B::BLACK);
    firePower->setPosition(tmp.width-35, tmp.height-60);
    firePower->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(firePower);
    
    armour = Label::create("", "fonts/DengXian.ttf", 15);
    armour->setColor(Color3B::BLACK);
    armour->setPosition(tmp.width-35, tmp.height-85);
    armour->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(armour);
    
    torpedo = Label::create("", "fonts/DengXian.ttf", 15);
    torpedo->setColor(Color3B::BLACK);
    torpedo->setPosition(tmp.width-35, tmp.height-110);
    torpedo->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(torpedo);
    
    antiAir = Label::create("", "fonts/DengXian.ttf", 15);
    antiAir->setColor(Color3B::BLACK);
    antiAir->setPosition(tmp.width-35, tmp.height-135);
    antiAir->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    bgImg->addChild(antiAir);
    
    
    firePowerIcon=Sprite::create("OrganizeMain/firePowerIcon.png");
    firePowerIcon->setPosition(tmp.width-70, tmp.height-60);
    bgImg->addChild(firePowerIcon);
    torpedoIcon=Sprite::create("OrganizeMain/torpedoIcon.png");
    torpedoIcon->setPosition(tmp.width-70, tmp.height-85);
    bgImg->addChild(torpedoIcon);
    antiAirIcon=Sprite::create("OrganizeMain/antiAirIcon.png");
    antiAirIcon->setPosition(tmp.width-70, tmp.height-110);
    bgImg->addChild(antiAirIcon);
    armourIcon=Sprite::create("OrganizeMain/armourIcon.png");
    armourIcon->setPosition(tmp.width-70, tmp.height-135);
    bgImg->addChild(armourIcon);
    
    ammoBar=ValueBar::create();
    ammoBar->setPosition(67+tmp.width,tmp.height-80);
    bgImg->addChild(ammoBar);
    
    fuelBar=ValueBar::create();
    fuelBar->setPosition(ammoBar->getPosition()-Vec2(0, 45));
    bgImg->addChild(fuelBar);
    
    auto fuelIcon=Sprite::create("OrganizeMain/image 323.png");
    bgImg->addChild(fuelIcon);
    fuelIcon->setPosition(tmp.width+47, tmp.height-70);
    
    auto ammoIcon =Sprite::create("OrganizeMain/image 324.png");
    bgImg->addChild(ammoIcon);
    ammoIcon->setPosition(fuelIcon->getPosition()-Vec2(0, 50));
}



void OrganSelectEntity::changeShipCallback(cocos2d::Ref *pSender)
{
    auto panel=dynamic_cast<PortOrganizeLayer*>(VIEW_MGR->getPanel(PanelType::PORT_ORGANIZE));
    panel->modifyContainer(CHANGE_CONTAINER,kantai);
}



void OrganSelectEntity::setEquipContainerVisible(int equipNumber, bool bVisible)
{
    CCASSERT(equipNumber>=1&&equipNumber<=4, "equipNumber is empty");
    if (bVisible)
    {
        equipContainer[equipNumber-1]->setVisible(true);
        equipEmpty[equipNumber-1]->setVisible(false);
    }
    else
    {
        equipContainer[equipNumber-1]->setVisible(false);
        equipEmpty[equipNumber-1]->setVisible(true);
    }
}

bool OrganSelectEntity::canChangeKantai(Kantai *kantai)
{
    auto panel=dynamic_cast<PortOrganizeLayer*>(VIEW_MGR->getPanel(PanelType::PORT_ORGANIZE));
    return panel->canChangeKantai(kantai);
}


void OrganSelectEntity::updateKantai(Kantai *kantai)
{
    this->kantai=kantai;
    if (canChangeKantai(kantai))
    {
        changeShipButton->setButtonVisible(true);
    }
    else
    {
        changeShipButton->setButtonVisible(false);
    }
    char name[30];
    bzero(name, sizeof(name));
    sprintf(name, "%s",kantai->getKantaiName());
    kantaiName->setString(name);
    
    sprintf(name, "%d",kantai->getCurrLV());
    kantaiLv->setString(name);
    
    kantaiCard->updateCard(kantai);
    
    sprintf(name, "%d//%d",kantai->getCurrHp(),kantai->getMaxHp());
    kantaiHp->setString(name);
    hpBar->setHp(kantai->getMaxHp(), kantai->getCurrHp());
    stars->setNumber(kantai->getStars());
    
    equipSize=kantai->getKantaiEquipSize();
    int i=0;
    for (; i<equipSize; ++i)
    {
        setEquipContainerVisible(i+1, true);
        equipContainer[i]->updateEquip(kantai->getEquip(i+1));
    }
    for (; i<4; ++i)
    {
        setEquipContainerVisible(i+1, false);
        equipContainer[i]->updateEquip(NULL);
    }
    
    sprintf(name, "%d",kantai->getFirePower());
    firePower->setString(name);
    sprintf(name, "%d",kantai->getTorpedo());
    torpedo->setString(name);
    sprintf(name, "%d",kantai->getAntiAir());
    antiAir->setString(name);
    sprintf(name, "%d",kantai->getArmor());
    armour->setString(name);
    
    ammoBar->update(kantai->getCurrAmmo(),kantai->getMaxAmmo());
    fuelBar->update(kantai->getCurrFuel(),kantai->getMaxFuel());
}

NS_KCL_END