//
//  PortUILayer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "PortUILayer.hpp"
#include "Player.h"


NS_KCL_BEGIN

bool PortUILayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        
        ///////////这个需要修改////////////////////
        startCircle();
        ///////////这个需要修改////////////////////
        
        
        initPortSceneBar();
        initClock();
        initTopLeftCircle();
        initPlayerAttr();
        initSelectButton();
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}

void PortUILayer::initPortSceneBar()
{
    Sprite* titleBar=Sprite::createWithSpriteFrameName("titleBar.png");
    titleBar->setPosition(400,447);
    titleBar->setOpacity(200);
    addChild(titleBar);
    
    //borders
    auto *border_bottom_1 = Sprite::createWithSpriteFrameName("border_bottom_1.png");
    border_bottom_1->setPosition(550, 5);
    this->addChild(border_bottom_1);
    
    auto *border_bottom_2 = Sprite::createWithSpriteFrameName("border_bottom_2.png");
    border_bottom_2->setPosition(150, -2);
    this->addChild(border_bottom_2);
    
    auto *border_left = Sprite::createWithSpriteFrameName("border_left.png");
    border_left->setPosition(8, 232);
    this->addChild(border_left);
    
    auto *border_top = Sprite::createWithSpriteFrameName("border_top.png");
    border_top->setPosition(550, 475);
    this->addChild(border_top);
}

void PortUILayer::initClock()
{
    //clock
    auto *clockBg = Sprite::createWithSpriteFrameName("left_circle.png");
    clockBg->setPosition(52, 40);
    this->addChild(clockBg);
}



void PortUILayer::initTopLeftCircle()
{
    auto borderTopLeft=Sprite::createWithSpriteFrameName("borderTopLeft.png");
    borderTopLeft->setPosition(48,439);
    RotateBy* circleAction=RotateBy::create(0.01, 6);
    Sequence* sequence=Sequence::create(circleAction, DelayTime::create(0.99),NULL);
    RepeatForever* repeat=RepeatForever::create((ActionInterval*)sequence);
    borderTopLeft->runAction(repeat);
    addChild(borderTopLeft);
    
    auto borderCircle=Sprite::createWithSpriteFrameName("borderCircle.png");
    borderCircle->setPosition(62,423);
    borderCircle->setZOrder(1);
    addChild(borderCircle);
    
    title=Sprite::createWithSpriteFrameName("porttitle.png");
    title->setPosition(49,438);
    RotateBy* circleAction2=RotateBy::create(1, 13);
    RepeatForever* repeat2=RepeatForever::create((ActionInterval*)circleAction2);
    title->runAction(repeat2);
    title->setZOrder(1);
    addChild(title);
    
    Sprite* shader=Sprite::createWithSpriteFrameName("shader.png");
    shader->setPosition(49,438);
    shader->setZOrder(1);
    shader->setOpacity(10);
    shader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(FadeTo::create(1.5, 170),FadeTo::create(1.5, 10), NULL)));
    addChild(shader);
}



void PortUILayer::initSelectButton()
{
    auto recordButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("record1.png"), Sprite::createWithSpriteFrameName("record2.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
    recordButton->setPosition(166, 432);
    
    auto allieButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("allie.png"), Sprite::createWithSpriteFrameName("allie.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
    allieButton->setPosition(240, 432);
    
    auto collectionButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("collection1.png"), Sprite::createWithSpriteFrameName("collection2.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
    collectionButton->setPosition(320, 432);
    
    auto buyButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buy1.png"), Sprite::createWithSpriteFrameName("buy2.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
    buyButton->setPosition(400, 432);
    
    auto furnitureButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("furniture1.png"), Sprite::createWithSpriteFrameName("furniture2.png"), CC_CALLBACK_1(PortUILayer::changeFurnitureCallback, this));
    furnitureButton->setPosition(480, 432);
    
    auto missionButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mission1.png"), Sprite::createWithSpriteFrameName("mission2.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
    missionButton->setPosition(560, 432);
    
    auto missionShader = Sprite::createWithSpriteFrameName("mission3.png");
    missionShader->setPosition(missionButton->getPosition());
    addChild(missionShader);
    missionShader->setZOrder(1);
    missionShader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(FadeOut::create(2), FadeIn::create(2), NULL)));
    
    auto buyHouseButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buyhhouse1.png"), Sprite::createWithSpriteFrameName("buyhouse2.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
    buyHouseButton->setPosition(620, 432);
    
    
    
    auto menu = Menu::create(recordButton, allieButton, collectionButton, buyButton, furnitureButton, missionButton, buyHouseButton, NULL);
    menu->setPosition(0, 0);
    addChild(menu);
}


void PortUILayer::initPlayerAttr()
{
    playerName=Label::create();
    std::string _playerName=sPlayer.getPlayerName();
    playerName->setString(_playerName.c_str());
    playerName->setAlignment(TextHAlignment::LEFT);
    playerName->setPosition(170, 465);
    addChild(playerName);
    
    
    playerLevel = Label::create();
    int _playerLevel=sPlayer.getCurrLV();
    playerLevel->setString(std::to_string(_playerLevel));
    playerLevel->setPosition(420, 462);
    this->addChild(playerLevel);
    
    auto *fleetCountLabel = Sprite::createWithSpriteFrameName("fleetCountLabel.png");
    fleetCountLabel->setPosition(520, 462);
    this->addChild(fleetCountLabel);
    
    fleetCount = Label::create();
    int _maxFleetSize=sPlayer.getMaxFleetSize();
    fleetCount->setString(std::to_string(_maxFleetSize));
    fleetCount->setPosition(560, 462);
    this->addChild(fleetCount);
    
    auto *shipCountLabel = Sprite::createWithSpriteFrameName("shipCountLabel.png");
    shipCountLabel->setPosition(601, 462);
    this->addChild(shipCountLabel);
    
    shipCount = Label::create();
    int _maxKantaiSize=sPlayer.getMaxKantaiSize();
    shipCount->setString(std::to_string(_maxKantaiSize));
    shipCount->setPosition(640, 462);
    this->addChild(shipCount);
    
    //resources
    
    Sprite *iconfr = Sprite::createWithSpriteFrameName("iconfr.png");
    iconfr->setPosition(670,462);
    this->addChild(iconfr);
    
    quickRepairCount = Label::create();
    quickRepairCount->setString("2");
    quickRepairCount->setPosition(710, 462);
    this->addChild(quickRepairCount);
    
    Sprite *icondt = Sprite::createWithSpriteFrameName("icondt.png");
    icondt->setPosition(740, 462);
    this->addChild(icondt);
    
    devToolCount = Label::create();
    devToolCount->setString("10");
    devToolCount->setPosition(780, 462);
    this->addChild(devToolCount);
    
    int x = 660;
    int y = 441;
    Sprite *icon1 = Sprite::createWithSpriteFrameName("icon1.png");
    icon1->setPosition(x, y);
    this->addChild(icon1);
    Sprite *icon2 = Sprite::createWithSpriteFrameName("icon2.png");
    icon2->setPosition(x + 75, y);
    this->addChild(icon2);
    Sprite *icon3 = Sprite::createWithSpriteFrameName("icon3.png");
    icon3->setPosition(x, y - 19);
    this->addChild(icon3);
    Sprite *icon4 = Sprite::createWithSpriteFrameName("icon4.png");
    icon4->setPosition(x + 75, y - 19);
    this->addChild(icon4);
    
    x = x + 40;
    labelFuel = Label::create();
    labelSteel = Label::create();
    labelAmmo = Label::create();
    labelAluminium = Label::create();
    labelFuel->setString(std::to_string(sPlayer.getFuel()));
    labelSteel->setString(std::to_string(sPlayer.getSteel()));
    labelAmmo->setString(std::to_string(sPlayer.getAmmo()));
    labelAluminium->setString(std::to_string(sPlayer.getAluminium()));
    labelFuel->setAlignment(TextHAlignment::RIGHT);
    labelSteel->setAlignment(TextHAlignment::RIGHT);
    labelAmmo->setAlignment(TextHAlignment::RIGHT);
    labelAluminium->setAlignment(TextHAlignment::RIGHT);
    labelFuel->setColor(Color3B::WHITE);
    labelSteel->setColor(Color3B::WHITE);
    labelAmmo->setColor(Color3B::WHITE);
    labelAluminium->setColor(Color3B::WHITE);
    labelFuel->setPosition(x, y);
    labelSteel->setPosition(x + 75, y);
    labelAmmo->setPosition(x, y - 19);
    labelAluminium->setPosition(x + 75, y - 19);
    this->addChild(labelFuel);
    this->addChild(labelSteel);
    this->addChild(labelAmmo);
    this->addChild(labelAluminium);
    
}







void PortUILayer::menuHandlingCallback(Ref* pSender)
{
    
}

void PortUILayer::changeFurnitureCallback(Ref* psSender)
{
    
}

void PortUILayer::startCircle()
{
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
}

void PortUILayer::endCircle()
{
    Director::getInstance()->getInstance()->getScheduler()->unscheduleUpdate(this);
}



void PortUILayer::update(float dt)
{
    updatePlayerAttr(dt);
}

void PortUILayer::updatePlayerAttr(float dt)
{
    char number[20];
    bzero(number, sizeof(number));
    sprintf(number, "%d",sPlayer.getFuel());
    labelFuel->setString(number);
    sprintf(number, "%d",sPlayer.getSteel());
    labelSteel->setString(number);
    sprintf(number, "%d",sPlayer.getAmmo());
    labelAmmo->setString(number);
    sprintf(number, "%d",sPlayer.getAluminium());
    labelAluminium->setString(number);
}



void PortUILayer::changeTitlePic(kancolle::PanelType type)
{
    title->setVisible(true);
    std::string titleName;
    switch (type) {
        case PanelType::PORT_MAINLAYER:
            titleName="porttitle.png";
            break;
        case PanelType::PORT_SUPPLY:
            titleName="supplytitle.png";
            break;
        case PanelType::PORT_FACTORY:
            titleName="factorytitle.png";
            break;
        case PanelType::PORT_ORGANIZE:
            titleName="organizetitle.png";
            break;
        case PanelType::PORT_REMODE:
            titleName="remodeltitle.png";
            break;
        case PanelType::PORT_REPAIR:
            titleName="repairtitle.png";
            break;
        case PanelType::PORT_BATTLE:
            titleName="battletitle.png";
            break;
        default:
            title->setVisible(false);
            break;
    }
    title->setSpriteFrame(titleName);
}



NS_KCL_END
