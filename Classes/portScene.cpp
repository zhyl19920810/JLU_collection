//
//  portScene.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portScene.h"
#include "Player.h"
#include "layerSelecter.h"
#include "portMainLayer.h"
#include "portSupplyLayer.h"
#include "portRemodeLayer.h"
#include "portRepairLayer.h"
#include "portOrganizeLayer.h"
#include "portFactoryLayer.h"
#include "portBattleLayer.h"
#include "portRepairLayer.h"
#include "portOrganizeLayer.h"
#include "Player.h"
#include "GameManger.hpp"
#include "Sound.hpp"




PortScene* PortScene::createScene()
{
    PortScene* scene=PortScene::create();
    sGameManger.setPortScene(scene);
    return scene;
}


PortUILayer::PortUILayer():
mainlayer(NULL),
supplylayer(NULL),
remodelayer(NULL),
factroylayer(NULL),
repairlayer(NULL),
battlelayer(NULL),
title(NULL),
organizelayer(NULL),
currentLayerType(LayerType::empty)
{
    
}

PortScene::PortScene():
layerSelecter(NULL),
portUIlayer(NULL),
portBgLayer(NULL)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PortMain/portmain.plist", "PortMain/portmain.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PortMain/layerSelect.plist", "PortMain/layerSelect.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PortMain/portMainLayer.plist", "PortMain/portMainLayer.pvr.ccz");
    SetCurrLayer(main);
}

PortScene::~PortScene()
{
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("PortMain/portmain.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("PortMain/portmain.pvr.ccz");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("PortMain/layerSelect.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("PortMain/layerSelect.pvr.ccz");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName("PortMain/portMainLayer.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("PortMain/portMainLayer.pvr.ccz");
    Director::getInstance()->getInstance()->getScheduler()->unscheduleUpdate(this);
}




void PortScene::pauseLayerSelecterButton()
{
    layerSelecter->pauseButton();
}

void PortScene::resumeLayerSelecterButton()
{
    layerSelecter->resumeButton();
}


void PortScene::SetCurrLayer(LayerType type)
{
//    switch (type) {
//        case main:
//        {
//            if (currentLayerType==LayerType::main)
//            {
//                return;
//            }
//            if(title!=nullptr)
//            {
//                title->setSpriteFrame("porttitle.png");
//            }
//            if (currentLayerType!=LayerType::empty)
//            {
//                removeChild(currentLayer);
//            }
//            currentLayerType=LayerType::main;
//            if (!mainlayer)
//            {
//                mainlayer=PortMainLayer::create();
//                this->addChild(mainlayer);
//            }else
//            {
//                mainlayer->setVisible(true);
//                mainlayer->resumeDispatcher();
//            }
//            layerSelecter->moveOut();
//            break;
//        }
//        case supply:
//        {
//            if (currentLayerType==LayerType::supply)
//            {
//                return;
//            }
//            title->setSpriteFrame("supplytitle.png");
//            bgImage->runAction(MoveTo::create(0.3, ccp(1600, 210)));
//            if (currentLayer)
//            {
//                removeChild(currentLayer);
//            }
//            mainlayer->setVisible(false);
//            currentLayer=PortSupplyLayer::create();
//            addChild(currentLayer,2);
//            layerSelecter->moveIn();
//            currentLayerType=type;
//            break;
//        }
//        case repair:
//        {
//            if (currentLayerType==LayerType::repair)
//            {
//                return;
//            }
//            title->setSpriteFrame("repairtitle.png");
//            bgImage->runAction(MoveTo::create(0.3, ccp(0,210)));
//            if (currentLayer)
//            {
//                removeChild(currentLayer);
//            }
//            mainlayer->setVisible(false);
//            currentLayer=PortRepairLayer::create();
//            addChild(currentLayer,2);
//            layerSelecter->moveIn();
//            currentLayerType=type;
//            break;
//        }
//        case factory:
//        {
//            if (currentLayerType==LayerType::factory)
//            {
//                return;
//            }
//            title->setSpriteFrame("factorytitle.png");
//            bgImage->runAction(MoveTo::create(0.3, ccp(-490,210)));
//            layerSelecter->moveIn();
//            if (currentLayer)
//            {
//                removeChild(currentLayer);
//            }
//            mainlayer->setVisible(false);
//            currentLayer=PortFactoryLayer::create();
//            addChild(currentLayer,2);
//            currentLayerType=type;
//            break;
//        }
//        case remode:
//        {
//            if (currentLayerType == LayerType::remode)
//                return;
//            title->setSpriteFrame("remodeltitle.png");
//            bgImage->runAction(MoveTo::create(0.3, ccp(-780, 210)));
//            layerSelecter->moveIn();
//            if (currentLayer)
//            {
//                removeChild(currentLayer);
//            }
//            mainlayer->setVisible(false);
//            currentLayer=PortRemodeLayer::create();
//            addChild(currentLayer,2);
//            currentLayerType=type;
//            break;
//        }
//        case battle:
//        {
//            if (currentLayerType == LayerType::battle)
//                return;
//            //layerSwithEffect();
//            title->setSpriteFrame("battletitle.png");
//            bgImage->runAction(MoveTo::create(0.3, ccp(800, 210)));
//            layerSelecter->moveIn();
//            if (currentLayer)
//            {
//                removeChild(currentLayer);
//            }
//            mainlayer->setVisible(false);
//            currentLayer=PortBattleLayer::create();
//            currentLayer->setZOrder(-1);
//            addChild(currentLayer);
//            currentLayerType=type;
//            break;
//        }
//        case organize:
//            if (currentLayerType == LayerType::organize)
//                return;
//            //layerSwithEffect();
//            title->setSpriteFrame("organizetitle.png");
//            bgImage->runAction(MoveTo::create(0.3,Point(800, 210)));
//            layerSelecter->moveIn();
//            if (currentLayer)
//            {
//                removeChild(currentLayer);
//            }
//            mainlayer->setVisible(false);
//            currentLayer=PortOrganizeLayer::create();
//            addChild(currentLayer,2);
//            currentLayerType=type;
//            break;
//            
//        default:
//            break;
//    }
//    
//    
    
}


//--------------------------------------------------------------------------------------------------------
bool PortUILayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        
        ///////////这个需要修改////////////////////
        startCircle();
        ///////////这个需要修改////////////////////
        
        auto borderTopLeft=Sprite::createWithSpriteFrameName("borderTopLeft.png");
        borderTopLeft->setPosition(48,439);
        RotateBy* circleAction=RotateBy::create(0.01, 6);
        Sequence* sequence=Sequence::create(circleAction, DelayTime::create(0.99),NULL);
        RepeatForever* repeat=RepeatForever::create((ActionInterval*)sequence);
        borderTopLeft->runAction(repeat);
        addChild(borderTopLeft);
        
        auto top_bar = Sprite::create("OrganizeMain/topBar.png");
        addChild(top_bar);
        top_bar->setPosition(Vec2(-370, 188));///可能需要改
        
        
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
        //clock
        auto *clockBg = Sprite::createWithSpriteFrameName("left_circle.png");
        clockBg->setPosition(52, 40);
        this->addChild(clockBg);
        
        
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
        
        
        Layer *layer = Layer::create();
        this->addChild(layer);
        
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
        layer->addChild(missionShader);
        missionShader->setZOrder(1);
        missionShader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(FadeOut::create(2), FadeIn::create(2), NULL)));
        
        auto buyHouseButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buyhhouse1.png"), Sprite::createWithSpriteFrameName("buyhouse2.png"), CC_CALLBACK_1(PortUILayer::menuHandlingCallback, this));
        buyHouseButton->setPosition(620, 432);
        
        
        
        auto menu = Menu::create(recordButton, allieButton, collectionButton, buyButton, furnitureButton, missionButton, buyHouseButton, NULL);
        menu->setPosition(0, 0);
        layer->addChild(menu);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
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

//--------------------------------------------------------------------------------------------------------
bool PortBgLayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        bgImage=Sprite::create("PortMain/image 345.jpg");
        bgImage->setPosition(800,210);
        bgImage->setGlobalZOrder(-3);
        addChild(bgImage);
        
        SND->playMusic("sound_bgm/sound 2.mp3");
        
        bRet=true;
    }while(0);
    
    return bRet;
}


bool PortScene::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        layerSelecter=LayerSelecter::create(this, Vec2(-50, 220));
        addChild(layerSelecter);
        portBgLayer=PortBgLayer::create();
        addChild(portBgLayer);
        portUIlayer=PortUILayer::create();
        addChild(portUIlayer);
        
        bRet=true;
    }while(0);
    
    return bRet;
    
}





///------------------------------
