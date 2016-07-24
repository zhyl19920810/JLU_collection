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


NS_KCL_BEGIN

PortSupplyLayer::PortSupplyLayer()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SupplyMain/supplyLayer.plist", "SupplyMain/supplyLayer.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CommonAssets/commonAssets.plist", "CommonAssets/commonAssets.pvr.ccz");
    consumeAmmo=0;
    consumeFuel=0;
    fleetNumber=1;
    ammoST.clear();
    fuelST.clear();
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
}



void PortSupplyLayer::refreshLayer()
{
    consumeAmmo=0;
    consumeFuel=0;
    ammoST.clear();
    fuelST.clear();
    consumeAmmoLabel->setString("0");
    consumeFuelLabel->setString("0");
    setAmmoButtonVisible(false);
    setFuelButtonVisible(false);
    setMidButtonVisible(false);
}





bool PortSupplyLayer::init()
{
    if (!Panel::init()) {
        return false;
    }
    initLayer();
    initKantaiTable();
    
    
    fleetButton=FleetButton::create(std::bind(&PortSupplyLayer::refreshFleet,this, std::placeholders::_1));
    fleetButton->setPosition(47, bgimg->getContentSize().height-27);
    bgimg->addChild(fleetButton);
    

    return true;
}

void PortSupplyLayer::refreshFleet(int fleetNumber)
{
    this->fleetNumber=fleetNumber;
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    refreshLayer();
    refreshKantaiTable();
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
    midButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("AFButton2.png"),Sprite::createWithSpriteFrameName("AFButton3.png"), CC_CALLBACK_1(PortSupplyLayer::callMidButton, this));
    midButton->setPosition(700, 50);
    midButtonUp=Sprite::createWithSpriteFrameName("AFButton1.png");
    addChild(midButtonUp,3);
    midButtonUp->setPosition(midButton->getPosition());
    
    
    
    fuelButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("fuelButton2.png"),Sprite::createWithSpriteFrameName("fuelButton3.png"), CC_CALLBACK_1(PortSupplyLayer::callFuelButton, this));
    fuelButton->setPosition(midButton->getPosition().x-midButton->getContentSize().width/2-fuelButton->getContentSize().width/2, 50);
    fuelButtonUp=Sprite::createWithSpriteFrameName("fuelButton1.png");
    addChild(fuelButtonUp,3);
    fuelButtonUp->setPosition(fuelButton->getPosition());
    
    
    ammoButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ammoButton2.png"),Sprite::createWithSpriteFrameName("ammoButton3.png"), CC_CALLBACK_1(PortSupplyLayer::callAmmoButton, this));
    ammoButton->setPosition(midButton->getPosition().x+midButton->getContentSize().width/2+fuelButton->getContentSize().width/2, 50);
    ammoButtonUp=Sprite::createWithSpriteFrameName("ammoButton1.png");
    addChild(ammoButtonUp,3);
    ammoButtonUp->setPosition(ammoButton->getPosition());
    
    
    
    auto menu = Menu::create(fuelButton, midButton, ammoButton, NULL);
    this->addChild(menu,2);
    menu->setPosition(0, 0);
    
    ammoEntity=AmmoEntity::create();
    addChild(ammoEntity,2);
    ammoEntity->setPosition(Vec2(700, 190));
    
    fuelEntity=FuelEntity::create();
    addChild(fuelEntity,2);
    fuelEntity->setPosition(Vec2(700, 190));
    

    consumeAmmoLabel=Label::create();
    consumeAmmoLabel->setString(to_string(consumeAmmo));
    consumeAmmoLabel->setPosition(750,270);
    consumeAmmoLabel->setColor(Color3B::BLACK);
    consumeAmmoLabel->setSystemFontSize(30);
    addChild(consumeAmmoLabel, 3);
    
    consumeFuelLabel=Label::create();
    consumeFuelLabel->setString(to_string(consumeFuel));
    consumeFuelLabel->setPosition(650,270);
    consumeFuelLabel->setColor(Color3B::BLACK);
    consumeFuelLabel->setSystemFontSize(30);
    addChild(consumeFuelLabel, 3);
}

void PortSupplyLayer::addConsumeAmmo(int position,int ammo)
{
    if (ammoButtonUp->isVisible())
    {
        setAmmoButtonVisible(true);
    }
    if (midButtonUp->isVisible())
    {
        setMidButtonVisible(true);
    }
    consumeAmmo+=ammo;
    ammoEntity->addConsumeAmmo(ammo);
    ammoST.insert(std::pair<int, int>(position,ammo));
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeAmmo);
    consumeAmmoLabel->setString(tmp);
    
    ///Action
}

void PortSupplyLayer::addConsumeFuel(int position, int fuel)
{
    if (fuelButtonUp->isVisible())
    {
        setFuelButtonVisible(true);
    }
    if (midButtonUp->isVisible()) {
        setMidButtonVisible(true);
    }
    consumeFuel+=fuel;
    fuelEntity->addConsumeFuel(fuel);
    fuelST.insert(std::pair<int, int>(position,fuel));
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeFuel);
    consumeFuelLabel->setString(tmp);
    //action
}

int PortSupplyLayer::minusConsumeAmmo(int position)
{
    auto it=ammoST.find(position);
    CCASSERT(it!=ammoST.end(), "the position do not exist in \"function minusConsumeAmmo\"");
    int minusAmmo=it->second;
    consumeAmmo-=minusAmmo;
    ammoEntity->minusConsumeAmmo(minusAmmo);
    
    ammoST.erase(it);
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeAmmo);
    consumeAmmoLabel->setString(tmp);
    
    if (!consumeAmmo) {
        setAmmoButtonVisible(false);
        if (!consumeFuel) {
            setMidButtonVisible(false);
        }
    }
    return minusAmmo;
}


int PortSupplyLayer::minusConsumeFuel(int position)
{
    auto it=fuelST.find(position);
    CCASSERT(it!=fuelST.end(), "the position do not exist in \"function minusConsumeFuel\"");
    int minusFuel=it->second;
    consumeFuel-=minusFuel;
    fuelEntity->minusConsumeFuel(minusFuel);
    
    fuelST.erase(it);
    char tmp[20];
    bzero(tmp, sizeof(tmp));
    sprintf(tmp, "%d",consumeFuel);
    consumeFuelLabel->setString(tmp);
    
    if (!consumeFuel) {
        setFuelButtonVisible(false);
        if (!consumeAmmo) {
            setMidButtonVisible(false);
        }
    }
    return minusFuel;
}



void PortSupplyLayer::initKantaiTable()
{
    for (int i=0; i<6; ++i)
    {
        shipUnit[i]=ShipUnit::create(i+1);
        addChild(shipUnit[i]);
        if (!fleet||!fleet->getShip(i+1))
        {
            shipUnit[i]->update(NULL);
        }
        else shipUnit[i]->update(fleet->getShip(i+1));
        shipUnit[i]->setPosition(371,366-52*(i+1));
    }
}

void PortSupplyLayer::refreshKantaiTable()
{
    for (int i=0; i<6; ++i)
    {
        if (!fleet||!fleet->getShip(i+1))
        {
            shipUnit[i]->update(NULL);
        }
        else shipUnit[i]->update(fleet->getShip(i+1));
    }
}



bool PortSupplyLayer::canFillUpAmmo(int position,Kantai* kantai)
{
    int ammo=kantai->getMaxAmmo()-kantai->getCurrAmmo();
    if (!ammo) {
        return false;
    }
    int haveAmmo=sPlayer.getAmmo();
    if (haveAmmo<(consumeAmmo+ammo))
    {
        return false;
    }
    return true;
}

bool PortSupplyLayer::canFillUpFuel(int position,Kantai* kantai)
{
    int fuel=kantai->getMaxFuel()-kantai->getCurrFuel();
    if (!fuel) {
        return false;
    }
    int haveFuel=sPlayer.getFuel();
    if (haveFuel<(consumeFuel+fuel))
    {
        return false;
    }
    return true;
}


void PortSupplyLayer::setAmmoButtonVisible(bool bVisible)
{
    if (bVisible) {
        ammoButtonUp->setVisible(false);
        ammoButton->setVisible(true);
    }
    else
    {
        ammoButtonUp->setVisible(true);
        ammoButton->setVisible(false);
    }
}

void PortSupplyLayer::setFuelButtonVisible(bool bVisible)
{
    if (bVisible) {
        fuelButtonUp->setVisible(false);
        fuelButton->setVisible(true);
    }
    else
    {
        fuelButtonUp->setVisible(true);
        fuelButton->setVisible(false);
    }
}

void PortSupplyLayer::setMidButtonVisible(bool bVisible)
{
    if (bVisible) {
        midButtonUp->setVisible(false);
        midButton->setVisible(true);
    }
    else
    {
        midButtonUp->setVisible(true);
        midButton->setVisible(false);
    }
}


void PortSupplyLayer::callFuelButton(Ref* pSender)
{
    vector<int> positionST(6);
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    
    int sum=0;
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        int postion=it->first;
        auto kantai=fleet->getShip(postion);
        int fuelValue=it->second;
        --positionST[postion-1];
        if (!positionST[postion-1])
        {
            auto tmp=shipUnit[postion-1]->select;
            tmp->setSelectedIndex(0);
        }
        kantai->setCurrFuel(kantai->getMaxFuel());
        sum+=fuelValue;
    }
    fuelST.clear();
    sPlayer.minusFuel(sum);
    freshShipAllCondition();
    freshShipAllAttr();
    
    fuelNumber->setString(to_string(sPlayer.getFuel()));
    dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME))->updateUILayerAttr();
    consumeFuel=0;
    
    fuelEntity->supplyAll();
    consumeFuelLabel->setString(to_string(0));
    
    setFuelButtonVisible(false);
    if (!consumeAmmo)
    {
        setMidButtonVisible(false);
    }

}

void PortSupplyLayer::callAmmoButton(cocos2d::Ref *pSender)
{
    vector<int> positionST(6);
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        ++positionST[it->first-1];
    }
    
    int sum=0;
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        int postion=it->first;
        auto kantai=fleet->getShip(postion);
        int ammoValue=it->second;
        --positionST[postion-1];
        if (!positionST[postion-1])
        {
            auto tmp=shipUnit[postion-1]->select;
            tmp->setSelectedIndex(0);
        }
        kantai->setCurrAmmo(kantai->getMaxAmmo());
        sum+=ammoValue;
    }
    ammoST.clear();
    sPlayer.minusAmmo(sum);
    freshShipAllCondition();
    freshShipAllAttr();

    ammoNumber->setString(to_string(sPlayer.getAmmo()));
    dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME))->updateUILayerAttr();
    consumeAmmo=0;
    ammoEntity->supplyAll();
    consumeAmmoLabel->setString(to_string(0));
    
    setAmmoButtonVisible(false);
    if (!consumeFuel) {
        setMidButtonVisible(false);
    }
}

void PortSupplyLayer::callMidButton(cocos2d::Ref *pSender)
{
    int fuelSum=0;
    for (auto it=fuelST.begin(); it!=fuelST.end(); ++it)
    {
        int postion=it->first;
        auto kantai=fleet->getShip(postion);
        int fuelValue=it->second;
        auto tmp=shipUnit[postion-1]->select;
        tmp->setSelectedIndex(0);
        kantai->setCurrFuel(kantai->getMaxFuel());
        fuelSum+=fuelValue;
    }
    fuelST.clear();
    
    int ammoSum=0;
    for (auto it=ammoST.begin(); it!=ammoST.end(); ++it)
    {
        int postion=it->first;
        auto kantai=fleet->getShip(postion);
        int ammoValue=it->second;
        auto tmp=dynamic_cast<MenuItemToggle*>(shipUnit[postion-1]->select);
        tmp->setSelectedIndex(0);
        kantai->setCurrAmmo(kantai->getMaxAmmo());
        ammoSum+=ammoValue;
    }
    ammoST.clear();
    
    sPlayer.minusFuel(fuelSum);
    sPlayer.minusAmmo(ammoSum);
    freshShipAllCondition();
    freshShipAllAttr();
    
    ammoNumber->setString(to_string(sPlayer.getAmmo()));
    dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME))->updateUILayerAttr();
    consumeAmmo=0;
    consumeAmmoLabel->setString(to_string(0));
    consumeFuel=0;
    consumeFuelLabel->setString(to_string(0));
    
    ammoEntity->supplyAll();
    fuelEntity->supplyAll();
    setAmmoButtonVisible(false);
    setFuelButtonVisible(false);
    setMidButtonVisible(false);
}



void PortSupplyLayer::freshShipAllCondition()
{
    if (!fleet)
    {
        return;
    }
    for (int i=0; i<6; ++i)
    {
        auto kantai=fleet->getShip(i+1);
        if (kantai)
        {
            shipUnit[i]->freshShipCondition();
        }
    }
}

void PortSupplyLayer::freshShipAllAttr()
{
    if (!fleet) {
        return;
    }
    for (int i=0; i<6; ++i)
    {
        auto kantai=fleet->getShip(i+1);
        if (kantai)
        {
            shipUnit[i]->freshShipAttr();
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

NS_KCL_END




