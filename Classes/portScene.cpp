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


PortScene* PortScene::createScene()
{
    PortScene* scene=new PortScene();
    return scene;
}

PortScene::PortScene()
{
    currentLayerType=LayerType::empty;
    mainlayer=nullptr;
    layerSelecter=nullptr;
    supplylayer=nullptr;
    remodelayer=nullptr;
    factroylayer=nullptr;
    repairlayer=nullptr;
    battlelayer=nullptr;
    title=nullptr;
    layerSelecter=new LayerSelecter(this,Vec2(-50,220));
    
    
    SetCurrLayer(main);
    init();
    
}

bool PortScene::init()
{
    
    
    
    bgImage=Sprite::create("interface/PortMain/image 345.jpg");
    bgImage->setPosition(800,210);
    bgImage->setZOrder(-3);
    addChild(bgImage);
    
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto borderTopLeft=Sprite::create("interface/PortMain/image 157.png");
    borderTopLeft->setPosition(48,439);
    RotateBy* circleAction=RotateBy::create(0.01, 6);
    Sequence* sequence=Sequence::create(circleAction, DelayTime::create(0.99),NULL);
    RepeatForever* repeat=RepeatForever::create((ActionInterval*)sequence);
    borderTopLeft->runAction(repeat);
    addChild(borderTopLeft);
    
    auto borderCircle=Sprite::create("interface/PortMain/image 281.png");
    borderCircle->setPosition(62,423);
    borderCircle->setZOrder(1);
    addChild(borderCircle);
    
    title=Sprite::create("interface/PortMain/image 283.png");
    title->setPosition(49,438);
    RotateBy* circleAction2=RotateBy::create(1, 13);
    RepeatForever* repeat2=RepeatForever::create((ActionInterval*)circleAction2);
    title->runAction(repeat2);
    title->setZOrder(1);
    addChild(title);
    
    Sprite* shader=Sprite::create("interface/PortMain/image 300.png");
    shader->setPosition(49,438);
    shader->setZOrder(1);
    shader->setOpacity(10);
    shader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(FadeTo::create(1.5, 170),FadeTo::create(1.5, 10), NULL)));
    addChild(shader);
    
    
    Sprite* titleBar=Sprite::create("interface/PortMain/image 160.png");
    titleBar->setPosition(400,447);
    titleBar->setOpacity(200);
    addChild(titleBar);
    
    auto _player=Player::getInstance();
    //borders
    auto *border_bottom_1 = Sprite::create("interface/PortMain/image 236.png");
    border_bottom_1->setPosition(550, 5);
    this->addChild(border_bottom_1);
    
    auto *border_bottom_2 = Sprite::create("interface/PortMain/image 235.png");
    border_bottom_2->setPosition(150, -2);
    this->addChild(border_bottom_2);
    
    auto *border_left = Sprite::create("interface/PortMain/image 232.png");
    border_left->setPosition(8, 232);
    this->addChild(border_left);
    
    auto *border_top = Sprite::create("interface/PortMain/image 168.png");
    border_top->setPosition(550, 475);
    this->addChild(border_top);
    //clock
    auto *clockBg = Sprite::create("interface/PortMain/image 233.png");
    clockBg->setPosition(52, 40);
    this->addChild(clockBg);
    
    
    playerName=Label::create();
    std::string _playerName=_player->getplayerName();
    playerName->setString(_playerName.c_str());
    playerName->setAlignment(TextHAlignment::LEFT);
    playerName->setPosition(170, 465);
    addChild(playerName);
    
    
    playerLevel = Label::create();
    int _playerLevel=_player->getcurrLV();
    playerLevel->setString(std::to_string(_playerLevel));
    playerLevel->setPosition(420, 462);
    this->addChild(playerLevel);
    
    auto *fleetCountLabel = Sprite::create("interface/PortMain/image 223.png");
    fleetCountLabel->setPosition(520, 462);
    this->addChild(fleetCountLabel);
    
    fleetCount = Label::create();
    int _maxFleetSize=_player->getmaxFleetSize();
    fleetCount->setString(std::to_string(_maxFleetSize));
    fleetCount->setPosition(560, 462);
    this->addChild(fleetCount);
    
    auto *shipCountLabel = Sprite::create("interface/PortMain/image 222.png");
    shipCountLabel->setPosition(601, 462);
    this->addChild(shipCountLabel);
    
    shipCount = Label::create();
    int _maxKantaiSize=_player->getmaxKantaiSize();
    shipCount->setString(std::to_string(_maxKantaiSize));
    shipCount->setPosition(640, 462);
    this->addChild(shipCount);
    
    //resources
    
    
    
    Sprite *iconfr = Sprite::create("interface/PortMain/image 161.png");
    iconfr->setPosition(670,462);
    this->addChild(iconfr);
    
    quickRepairCount = Label::create();
    quickRepairCount->setString("2");
    quickRepairCount->setPosition(710, 462);
    this->addChild(quickRepairCount);
    
    Sprite *icondt = Sprite::create("interface/PortMain/image 171.png");
    icondt->setPosition(740, 462);
    this->addChild(icondt);
    
    devToolCount = Label::create();
    devToolCount->setString("10");
    devToolCount->setPosition(780, 462);
    this->addChild(devToolCount);
    
    int x = 660;
    int y = 441;
    Sprite *icon1 = Sprite::create("interface/PortMain/image 141.png");
    icon1->setPosition(x, y);
    this->addChild(icon1);
    Sprite *icon2 = Sprite::create("interface/PortMain/image 139.png");
    icon2->setPosition(x + 75, y);
    this->addChild(icon2);
    Sprite *icon3 = Sprite::create("interface/PortMain/image 165.png");
    icon3->setPosition(x, y - 19);
    this->addChild(icon3);
    Sprite *icon4 = Sprite::create("interface/PortMain/image 138.png");
    icon4->setPosition(x + 75, y - 19);
    this->addChild(icon4);
                            
    x = x + 40;
    labelFuel = Label::create();
    labelSteel = Label::create();
    labelAmmo = Label::create();
    labelAluminium = Label::create();
    labelFuel->setString(std::to_string(_player->getfuel()));
    labelSteel->setString(std::to_string(_player->getsteel()));
    labelAmmo->setString(std::to_string(_player->getammo()));
    labelAluminium->setString(std::to_string(_player->getaluminium()));
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
    
    auto recordButton = MenuItemImage::create("interface/PortMain/image 180.png", "interface/PortMain/image 182.png", CC_CALLBACK_1(PortScene::menuHandlingCallback, this));
    recordButton->setPosition(166, 432);
    
    auto allieButton = MenuItemImage::create("interface/PortMain/image 186.png", "interface/PortMain/image 186.png", CC_CALLBACK_1(PortScene::menuHandlingCallback, this));
    allieButton->setPosition(240, 432);
    
    auto collectionButton = MenuItemImage::create("interface/PortMain/image 202.png", "interface/PortMain/image 204.png", CC_CALLBACK_1(PortScene::menuHandlingCallback, this));
    collectionButton->setPosition(320, 432);
    
    auto buyButton = MenuItemImage::create("interface/PortMain/image 207.png", "interface/PortMain/image 209.png", CC_CALLBACK_1(PortScene::menuHandlingCallback, this));
    buyButton->setPosition(400, 432);
    
    auto furnitureButton = MenuItemImage::create("interface/PortMain/image 212.png", "interface/PortMain/image 214.png", CC_CALLBACK_1(PortScene::changeFurnitureCallback, this));
    furnitureButton->setPosition(480, 432);
    
    auto missionButton = MenuItemImage::create("interface/PortMain/image 194.png", "interface/PortMain/image 199.png", CC_CALLBACK_1(PortScene::menuHandlingCallback, this));
    missionButton->setPosition(560, 432);
    
    auto missionShader = Sprite::create("interface/PortMain/image 196.png");
    missionShader->setPosition(missionButton->getPosition());
    layer->addChild(missionShader);
    missionShader->setZOrder(1);
    missionShader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(FadeOut::create(2), FadeIn::create(2), NULL)));
    
    auto buyHouseButton = MenuItemImage::create("interface/PortMain/image 217.png", "interface/PortMain/image 219.png", CC_CALLBACK_1(PortScene::menuHandlingCallback, this));
    buyHouseButton->setPosition(620, 432);
    
    
    
    auto menu = Menu::create(recordButton, allieButton, collectionButton, buyButton, furnitureButton, missionButton, buyHouseButton, NULL);
    menu->setPosition(0, 0);
    layer->addChild(menu);
    
    
    return true;
    
}


void PortScene::menuSettingCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void PortScene::menuHandlingCallback(Ref* pSender)
{
    
}

void PortScene::changeFurnitureCallback(Ref* psSender)
{
    
}


void PortScene::SetCurrLayer(LayerType type)
{
    switch (type) {
        case main:
        {
            if (currentLayerType==LayerType::main)
            {
                return;
            }
            if(title!=nullptr)
                title->setTexture("interface/PortMain/image 283.png");
            if (!mainlayer)
            {
                mainlayer=new PortMainLayer(this);
                this->addChild(mainlayer);
            }
            layerSelecter->moveOut();
            if (currentLayerType!=LayerType::empty)
            {
                currentLayer->setVisible(false);
            }
            currentLayer=mainlayer;
            mainlayer->setVisible(true);

            currentLayerType=type;
            break;
        }
        case supply:
        {
            if (currentLayerType==LayerType::supply)
            {
                return;
            }
            title->setTexture("interface/PortMain/image 285.png");
            bgImage->runAction(MoveTo::create(0.3, ccp(1600, 210)));
            if (!supplylayer)
            {
                supplylayer=new PortSupplyLayer(this);
                addChild(supplylayer);
            }
            layerSelecter->moveIn();
            if (currentLayerType!=LayerType::empty)
            {
                currentLayer->setVisible(false);
            }
            currentLayer=supplylayer;
            supplylayer->setVisible(true);
            currentLayerType=type;
            break;
        }
        case repair:
        {
            if (currentLayerType==LayerType::repair)
            {
                return;
            }
            title->setTexture("interface/PortMain/image 291.png");
            bgImage->runAction(MoveTo::create(0.3, ccp(0,210)));
            layerSelecter->moveIn();
            if (!repairlayer) {
                repairlayer=new PortRepairLayer(this);
                addChild(repairlayer);
            }
            if (currentLayerType!=LayerType::empty) {
                currentLayer->setVisible(false);
            }
            currentLayer=repairlayer;
            currentLayerType=LayerType::repair;
            repairlayer->setVisible(true);
            
            break;
        }
        case factory:
        {
            if (currentLayerType==LayerType::factory)
            {
                return;
            }
            title->setTexture("interface/PortMain/image 293.png");
            bgImage->runAction(MoveTo::create(0.3, ccp(-490,210)));
            layerSelecter->moveIn();
            if (!factroylayer)
            {
                factroylayer=new PortFactoryLayer(this);
                addChild(factroylayer);
            }
            if (currentLayerType!=LayerType::empty)
            {
                currentLayer->setVisible(false);
            }
            currentLayer=factroylayer;
            factroylayer->setVisible(true);
            currentLayerType=LayerType::factory;
            break;
        }
        case remode:
        {
            if (currentLayerType == LayerType::remode)
                return;
            //layerSwithEffect();
            title->setTexture("interface/PortMain/image 287.png");
            bgImage->runAction(MoveTo::create(0.3, ccp(-780, 210)));
            layerSelecter->moveIn();
            if (remodelayer == nullptr)
            {
                remodelayer = new PortRemodeLayer(this);
                this->addChild(remodelayer);
            }
            if (currentLayerType != LayerType::empty)
                currentLayer->setVisible(false);
            currentLayer = remodelayer;
            remodelayer->setVisible(true);
            currentLayerType = LayerType::remode;
            break;
        }
        case battle:
        {
            if (currentLayerType == LayerType::battle)
                return;
            //layerSwithEffect();
            title->setTexture("interface/PortMain/image 295.png");
            bgImage->runAction(MoveTo::create(0.3, ccp(800, 210)));
            layerSelecter->moveIn();
            if (battlelayer == nullptr)
            {
                battlelayer = new PortBattleLayer(this);
                this->addChild(battlelayer);
            }
            if (currentLayerType != LayerType::empty)
                currentLayer->setVisible(false);
            currentLayer = battlelayer;
            battlelayer->setZOrder(-1);
            battlelayer->setVisible(true);
            currentLayerType = LayerType::battle;
            break;
        }

//        case organize:
//            if (currentLayerType == LayerType::organize)
//                return;
//            //layerSwithEffect();
//            title->setTexture("PortMain/image 289.png");
//            bgImage->runAction(MoveTo::create(0.3,ccp(800, 210)));
//            layerSelecter->moveIn();
//            if (organizelayer == nullptr)
//            {
//                organizelayer = new PortOrganizeLayer(this);
//                this->addChild(organizelayer);
//            }
//            if (currentLayerType != LayerType::empty)
//                currentLayer->setVisible(false);
//            currentLayer = organizelayer;
//            organizelayer->setVisible(true);
//            currentLayerType = LayerType::organize;
//            break;

        default:
            break;
    }
    
    
    
}