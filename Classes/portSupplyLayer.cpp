//
//  portSupplyLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portSupplyLayer.h"
#include "portScene.h"
#include "PortUILayer.hpp"
#include "ViewMgr.hpp"
#include "SupplyInfo.hpp"


NS_KCL_BEGIN

PortSupplyLayer::PortSupplyLayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SupplyMain/supplyLayer.plist", "SupplyMain/supplyLayer.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CommonAssets/commonAssets.plist", "CommonAssets/commonAssets.pvr.ccz");

    fleetNumber=1;
    shipUnit.resize(6);
    startCircle();
}

PortSupplyLayer::~PortSupplyLayer()
{
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("SupplyMain/supplyLayer.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("SupplyMain/supplyLayer.pvr.ccz");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("CommonAssets/commonAssets.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("CommonAssets/commonAssets.pvr.ccz");
    endCircle();
    delete supplyImp;
}



void PortSupplyLayer::resetAmmoFuel()
{
    consumeAmmoLabel->setString("0");
    consumeFuelLabel->setString("0");
    
    ammoButton->setEnabled(false);
    fuelButton->setEnabled(false);
    midButton->setEnabled(false);
}



bool PortSupplyLayer::init()
{
    if (!Panel::init()) {
        return false;
    }
    
    supplyImp=SupplyImp::create();
    
    initLayer();
    initKantai();
    initFleet();
    initButton();
    initAttrDisplay();
    initEntity();
    updateButton();
    
    return true;
}

void PortSupplyLayer::initFleet()
{
    fleetButton=FleetButton::create(std::bind(&PortSupplyLayer::fleetButtonCallback,this, std::placeholders::_1));
    fleetButton->setPosition(47, bgimg->getContentSize().height-27);
    bgimg->addChild(fleetButton);
}

void PortSupplyLayer::initButton()
{
    midButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("AFButton2.png"),Sprite::createWithSpriteFrameName("AFButton3.png"),Sprite::createWithSpriteFrameName("AFButton1.png"), CC_CALLBACK_1(PortSupplyLayer::callMidButton, this));
    midButton->setPosition(700, 50);
    
    
    fuelButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("fuelButton2.png"),Sprite::createWithSpriteFrameName("fuelButton3.png"),Sprite::createWithSpriteFrameName("fuelButton1.png"), CC_CALLBACK_1(PortSupplyLayer::callFuelButton, this));
    fuelButton->setPosition(midButton->getPosition().x-midButton->getContentSize().width/2-fuelButton->getContentSize().width/2, 50);
    
    ammoButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ammoButton2.png"),Sprite::createWithSpriteFrameName("ammoButton3.png"),Sprite::createWithSpriteFrameName("ammoButton1.png"), CC_CALLBACK_1(PortSupplyLayer::callAmmoButton, this));
    ammoButton->setPosition(midButton->getPosition().x+midButton->getContentSize().width/2+fuelButton->getContentSize().width/2, 50);
    
    
    auto menu = Menu::create(fuelButton, midButton, ammoButton, NULL);
    this->addChild(menu,2);
    menu->setPosition(0, 0);
}

void PortSupplyLayer::initAttrDisplay()
{
    auto fuelIcon=Sprite::create();
    fuelIcon->setSpriteFrame("supplyFuel.png");
    this->addChild(fuelIcon);
    fuelIcon->setPosition(417, 364);
    
    auto ammoIcon = Sprite::createWithSpriteFrameName("supplyAmmo.png");
    this->addChild(ammoIcon);
    ammoIcon->setPosition(525, 364);
    
    char tmp[30];
    bzero(tmp, sizeof(tmp));
    
    sprintf(tmp, "%d",sPlayer.getFuel());
    fuelNumber=Label::create();
    addChild(fuelNumber);
    fuelNumber->setPosition(fuelIcon->getPosition()+Vec2(45, 0));
    fuelNumber->setString(tmp);
    fuelNumber->setColor(Color3B::BLACK);
    
    sprintf(tmp, "%d",sPlayer.getAmmo());
    ammoNumber=Label::create();
    addChild(ammoNumber);
    ammoNumber->setPosition(ammoIcon->getPosition()+Vec2(45, 0));
    ammoNumber->setString(tmp);
    ammoNumber->setColor(Color3B::BLACK);
}



void PortSupplyLayer::fleetButtonCallback(int fleetNumber)
{
    this->fleetNumber=fleetNumber;
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    resetAmmoFuel();
    updateKantai();
}

void PortSupplyLayer::initEntity()
{
    ammoEntity=AmmoEntity::create();
    addChild(ammoEntity,2);
    ammoEntity->setPosition(Vec2(700, 190));
    
    fuelEntity=FuelEntity::create();
    addChild(fuelEntity,2);
    fuelEntity->setPosition(Vec2(700, 190));
}

void PortSupplyLayer::initLayer()
{
    Size size=Director::getInstance()->getVisibleSize();
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    
    
    bgimg = Sprite::createWithSpriteFrameName("supplyBg1.png");
    this->addChild(bgimg);
    //bgimg->setOpacity(200);
    bgimg->setPosition(450, 200);
    
    auto bgimg2 = Sprite::createWithSpriteFrameName("supplyBg2.png");
    this->addChild(bgimg2,2);
    bgimg2->setPosition(695, 200);
    
    
    auto bgimg3 = Sprite::createWithSpriteFrameName("supplyBg3.png");
    this->addChild(bgimg3);
    bgimg3->setAnchorPoint(Vec2(1, 0.5));
    bgimg3->setPosition(size.width, size.height*5/6);
    bgimg3->setGlobalZOrder(-1);
    bgimg3->setOpacity(150);
    
    auto supplyTitle =Sprite::createWithSpriteFrameName("suppyTitle.png");
    this->addChild(supplyTitle,2);
    supplyTitle->setPosition(size.width-supplyTitle->getContentSize().width/2, size.height*3/4);
    
    auto leftTitle=Sprite::createWithSpriteFrameName("leftTitle.png");
    this->addChild(leftTitle);
    leftTitle->setPosition(Vec2(156, size.height*5/6));
    
    auto rightTitle=Sprite::createWithSpriteFrameName("rightTitle.png");
    addChild(rightTitle);
    rightTitle->setPosition(Vec2(size.width-130, size.height*5/6));
    
    
    consumeAmmoLabel=Label::create();
    consumeAmmoLabel->setString(to_string(supplyImp->getConsumeAmmo()));
    consumeAmmoLabel->setPosition(750,270);
    consumeAmmoLabel->setColor(Color3B::BLACK);
    consumeAmmoLabel->setSystemFontSize(30);
    addChild(consumeAmmoLabel, 3);
    
    consumeFuelLabel=Label::create();
    consumeFuelLabel->setString(to_string(supplyImp->getConsumeFuel()));
    consumeFuelLabel->setPosition(650,270);
    consumeFuelLabel->setColor(Color3B::BLACK);
    consumeFuelLabel->setSystemFontSize(30);
    addChild(consumeFuelLabel, 3);
}


void PortSupplyLayer::addConsumeAmmo(int position,int ammo)
{
    
    supplyImp->addConsumeAmmo(position, ammo);
    ammoEntity->addConsumeAmmo(ammo);
    updateButton();
    
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",supplyImp->getConsumeAmmo());
    consumeAmmoLabel->setString(tmp);
}


void PortSupplyLayer::addConsumeFuel(int position, int fuel)
{
    supplyImp->addConsumeFuel(position, fuel);
    fuelEntity->addConsumeFuel(fuel);
    updateButton();
    
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",supplyImp->getConsumeFuel());
    consumeFuelLabel->setString(tmp);
}

int PortSupplyLayer::minusConsumeAmmo(int position)
{
    int minusAmmo=supplyImp->minusConsumeAmmo(position);
    int consumeAmmo=supplyImp->consumeAmmo;
    ammoEntity->minusConsumeAmmo(minusAmmo);
    
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeAmmo);
    consumeAmmoLabel->setString(tmp);
    updateButton();
    
    return minusAmmo;
}


int PortSupplyLayer::minusConsumeFuel(int position)
{
    int minusFuel=supplyImp->minusConsumeFuel(position);
    int consumeFuel=supplyImp->consumeFuel;
    fuelEntity->minusConsumeFuel(minusFuel);
    
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeFuel);
    consumeFuelLabel->setString(tmp);
    updateButton();
    
    return minusFuel;
}


void PortSupplyLayer::initKantai()
{
    for (int i=0; i<6; ++i)
    {
        shipUnit[i]=ShipUnit::create(i+1);
        addChild(shipUnit[i]);
        if (!fleet||!fleet->getShip(i+1))
            shipUnit[i]->update(NULL);
        else
            shipUnit[i]->update(fleet->getShip(i+1));
        shipUnit[i]->setPosition(371,366-52*(i+1));
    }
}



void PortSupplyLayer::updateKantai()
{
    for (int i=0; i<6; ++i)
    {
        if (!fleet||!fleet->getShip(i+1))
            shipUnit[i]->update(NULL);
        else
            shipUnit[i]->update(fleet->getShip(i+1));
    }
}


void PortSupplyLayer::updateButton()
{
    int consumeAmmo=supplyImp->consumeAmmo;
    int consumeFuel=supplyImp->consumeFuel;
    
    midButton->setEnabled(true);
    ammoButton->setEnabled(true);
    fuelButton->setEnabled(true);
    
    if (!consumeAmmo&&!consumeFuel) midButton->setEnabled(false);
    if (!consumeAmmo)              ammoButton->setEnabled(false);
    if (!consumeFuel)              fuelButton->setEnabled(false);
}


void PortSupplyLayer::callFuelButton(Ref* pSender)
{
    supplyImp->callFuelButton(fleet);
    updatehipAllState();
    updateAllBar();
//    fuelNumber->setString(to_string(sPlayer.getFuel()));
    dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME))->updateUILayerAttr();
    consumeFuelLabel->setString(to_string(0));
    
    fuelEntity->supplyAll();
    updateButton();
}

void PortSupplyLayer::callAmmoButton(cocos2d::Ref *pSender)
{
    supplyImp->callAmmoButton(fleet);
    updatehipAllState();
    updateAllBar();
//    ammoNumber->setString(to_string(sPlayer.getAmmo()));
    dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME))->updateUILayerAttr();
    consumeAmmoLabel->setString(to_string(0));
    
    ammoEntity->supplyAll();
    updateButton();
}

void PortSupplyLayer::callMidButton(cocos2d::Ref *pSender)
{
    supplyImp->callMidButton(fleet);
    updatehipAllState();
    updateAllBar();
//    ammoNumber->setString(to_string(sPlayer.getAmmo()));
//    fuelNumber->setString(to_string(sPlayer.getFuel()));
    dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME))->updateUILayerAttr();
    consumeAmmoLabel->setString(to_string(0));
    consumeFuelLabel->setString(to_string(0));
    
    ammoEntity->supplyAll();
    fuelEntity->supplyAll();
    updateButton();
}



void PortSupplyLayer::updatehipAllState()
{
    if (!fleet) return;
    
    for (int i=0; i<6; ++i)
    {
        auto kantai=fleet->getShip(i+1);
        if (kantai)
        {
            shipUnit[i]->updateShipState();
        }
    }
}

void PortSupplyLayer::updateAllBar()
{
    if (!fleet) return;
        
    for (int i=0; i<6; ++i)
    {
        auto kantai=fleet->getShip(i+1);
        if (kantai)
        {
            shipUnit[i]->updateBar();
        }
    }
}


void PortSupplyLayer::startCircle()
{
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
}

void PortSupplyLayer::endCircle()
{
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void PortSupplyLayer::update(float dt)
{
    char name[50];
    sprintf(name, "%d",sPlayer.getFuel());
    fuelNumber->setString(name);
    sprintf(name, "%d",sPlayer.getAmmo());
    ammoNumber->setString(name);
}

void PortSupplyLayer::setUnitReset(int position)
{
    auto tmp=shipUnit[position-1]->select;
    tmp->setSelectedIndex(0);
}



NS_KCL_END




