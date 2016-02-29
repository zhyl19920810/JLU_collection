//
//  portSupplyLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portSupplyLayer.h"
#include "portScene.h"
#include "GameManger.hpp"


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
    fleetToggle.resize(4);
    fleetSprite.resize(4);
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

void PortSupplyLayer::initFleetButton()
{
    fleetSprite[0]=Sprite::createWithSpriteFrameName("one1.png");
    bgimg->addChild(fleetSprite[0]);
    fleetSprite[0]->setPosition(Vec2(47, bgimg->getContentSize().height-27));
    
    fleetToggle[0]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortSupplyLayer::fleetCallback, this,1), MenuItemSprite::create(Sprite::createWithSpriteFrameName("one2.png"), Sprite::createWithSpriteFrameName("one2.png")),
    MenuItemSprite::create(Sprite::createWithSpriteFrameName("one3.png"), Sprite::createWithSpriteFrameName("one3.png")), NULL);
    fleetToggle[0]->setPosition(fleetSprite[0]->getPosition());
    
    
    fleetSprite[1]=Sprite::createWithSpriteFrameName("two1.png");
    bgimg->addChild(fleetSprite[1]);
    fleetSprite[1]->setPosition(fleetSprite[0]->getPosition()+Vec2(30, 0));
    
    fleetToggle[1]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortSupplyLayer::fleetCallback, this,2), MenuItemSprite::create(Sprite::createWithSpriteFrameName("two2.png"), Sprite::createWithSpriteFrameName("two2.png")),
        MenuItemSprite::create(Sprite::createWithSpriteFrameName("two3.png"), Sprite::createWithSpriteFrameName("two3.png")), NULL);
    fleetToggle[1]->setPosition(fleetSprite[1]->getPosition());
    
    

    fleetSprite[2]=Sprite::createWithSpriteFrameName("three1.png");
    bgimg->addChild(fleetSprite[2]);
    fleetSprite[2]->setPosition(fleetSprite[1]->getPosition()+Vec2(30, 0));
    
    fleetToggle[2]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortSupplyLayer::fleetCallback, this,3), MenuItemSprite::create(Sprite::createWithSpriteFrameName("three2.png"), Sprite::createWithSpriteFrameName("three2.png")),
    MenuItemSprite::create(Sprite::createWithSpriteFrameName("three3.png"), Sprite::createWithSpriteFrameName("three3.png")), NULL);
    fleetToggle[2]->setPosition(fleetSprite[2]->getPosition());
    
    
    
    fleetSprite[3]=Sprite::createWithSpriteFrameName("four1.png");
    bgimg->addChild(fleetSprite[3]);
    fleetSprite[3]->setPosition(fleetSprite[2]->getPosition()+Vec2(30, 0));
    
    fleetToggle[3]=MenuItemToggle::createWithCallback(CC_CALLBACK_1(PortSupplyLayer::fleetCallback, this,4), MenuItemSprite::create(Sprite::createWithSpriteFrameName("four2.png"), Sprite::createWithSpriteFrameName("four2.png")),
    MenuItemSprite::create(Sprite::createWithSpriteFrameName("four3.png"), Sprite::createWithSpriteFrameName("four3.png")), NULL);
    fleetToggle[3]->setPosition(fleetSprite[3]->getPosition());
    
    auto mn=Menu::create(fleetToggle[0],fleetToggle[1],fleetToggle[2],fleetToggle[3], NULL);
    mn->setPosition(Vec2::ZERO);
    bgimg->addChild(mn);
    
    fleetToggle[0]->setSelectedIndex(1);
    for (int i=1; i<=4; ++i)
    {
        SetFleetButtonVisible(i, sPlayer.getFleetByFleetKey(i));
    }
}

void PortSupplyLayer::fleetCallback(cocos2d::Ref *pSender, int layNumber)
{
    auto toggle=dynamic_cast<MenuItemToggle*>(pSender);
    if (toggle->getSelectedIndex())  //关到开
    {
        if (layNumber==fleetNumber)
        {
            toggle->setSelectedIndex(0);
            return;
        }
        fleetToggle[fleetNumber-1]->setSelectedIndex(0);
        
        changeFleet(layNumber);
    }
    else  //开到关
    {
        toggle->setSelectedIndex(1);
    }
}

void PortSupplyLayer::changeFleet(int fleetNumber)
{
    this->fleetNumber=fleetNumber;
    fleet=sPlayer.getFleetByFleetKey(fleetNumber);
    refreshLayer();
    refreshKantaiTable();
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


void PortSupplyLayer::SetFleetButtonVisible(int fleetNumber, bool bVisible)
{
    if (bVisible)
    {
        fleetToggle[fleetNumber-1]->setVisible(true);
        fleetSprite[fleetNumber-1]->setVisible(false);
    }
    else
    {
        fleetToggle[fleetNumber-1]->setVisible(false);
        fleetSprite[fleetNumber-1]->setVisible(true);
    }
}




bool PortSupplyLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    initLayer();
    initKantaiTable();
    initFleetButton();
    
    return true;
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
    
    
    auto fuelBox =Sprite::createWithSpriteFrameName("fuelBox.png");
    this->addChild(fuelBox,2);
    fuelBox->setPosition(650, 295);
    
    auto ammoBox =Sprite::createWithSpriteFrameName("ammoBox.png");
    this->addChild(ammoBox,2);
    ammoBox->setPosition(750, 295);
    
    auto fuelBg =Sprite::createWithSpriteFrameName("fuelBg.png");
    this->addChild(fuelBg,2);
    fuelBg->setPosition(650, 190);
    
    auto ammoBg =Sprite::createWithSpriteFrameName("ammoBg.png");
    this->addChild(ammoBg,2);
    ammoBg->setPosition(750, 190);
    
    
    auto lSupplyLight=Sprite::createWithSpriteFrameName("supplyLight.png");
    addChild(lSupplyLight,3);
    lSupplyLight->setPosition(fuelBg->getPosition()-Vec2(0,15));
    
    auto rSupplyLight=Sprite::createWithSpriteFrameName("supplyLight.png");
    addChild(rSupplyLight,3);
    rSupplyLight->setPosition(ammoBg->getPosition()-Vec2(0,15));
    
    consumeAmmoLabel=Label::create();
    consumeAmmoLabel->setString(to_string(consumeAmmo));
    consumeAmmoLabel->setPosition(ammoBox->getPosition()-Vec2(0, ammoBox->getContentSize().height/4));
    consumeAmmoLabel->setColor(Color3B::BLACK);
    consumeAmmoLabel->setSystemFontSize(30);
    addChild(consumeAmmoLabel, 3);
    
    consumeFuelLabel=Label::create();
    consumeFuelLabel->setString(to_string(consumeFuel));
    consumeFuelLabel->setPosition(fuelBox->getPosition()-Vec2(0, fuelBox->getContentSize().height/4));
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
    sGameManger.getPortScene()->changeLabelFuel(sPlayer.getFuel());
    consumeFuel=0;
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
    sGameManger.getPortScene()->changeLabelAmmo(sPlayer.getAmmo());
    fuelNumber->setString(to_string(sPlayer.getFuel()));
    sGameManger.getPortScene()->changeLabelFuel(sPlayer.getFuel());
    consumeAmmo=0;
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
    sGameManger.getPortScene()->changeLabelAmmo(sPlayer.getAmmo());
    consumeAmmo=0;
    consumeAmmoLabel->setString(to_string(0));
    consumeFuel=0;
    consumeFuelLabel->setString(to_string(0));
    
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
    updateLabel=schedule_selector(PortSupplyLayer::changeLabel);
    schedule(updateLabel,1);
}

void PortSupplyLayer::endCircle()
{
    unschedule(updateLabel);
}

void PortSupplyLayer::changeLabel(float dt)
{
    char name[50];
    sprintf(name, "%d",sPlayer.getFuel());
    fuelNumber->setString(name);
    sprintf(name, "%d",sPlayer.getAmmo());
    ammoNumber->setString(name);
}


