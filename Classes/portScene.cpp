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
#include "PortUILayer.hpp"
#include "GameManger.hpp"
#include "Sound.hpp"
#include "ViewMgr.hpp"
#include "PortBgLayer.hpp"
#include "SoundPanelButton.hpp"



NS_KCL_BEGIN

PortScene* PortScene::createScene()
{
    PortScene* scene=PortScene::create();
    return scene;
}


PortUILayer::PortUILayer():
title(NULL)
{
    
}

PortScene::PortScene():
portStateMachine(this),
layerSelecter(NULL),
portUIlayer(NULL),
portBgLayer(NULL),
currentPanelType(PanelType::NONE)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PortMain/portmain.plist", "PortMain/portmain.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PortMain/layerSelect.plist", "PortMain/layerSelect.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PortMain/portMainLayer.plist", "PortMain/portMainLayer.pvr.ccz");
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

PanelType PortScene::getCurrPanelType() const
{
    return currentPanelType;
}




void PortScene::SetCurrPanel(PanelType type)
{
    if (type==getCurrPanelType()) {
        return;
    }
    portStateMachine.changeState(type);
    currentPanelType=type;
}


bool PortScene::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        schedule([this](float dt){SetCurrPanel(PanelType::PORT_MAINLAYER);}, 0, 0, 0, "init_portScene");
        layerSelecter=LayerSelecter::create(this, Vec2(-50, 220));
        addChild(layerSelecter,3);
        portBgLayer=PortBgLayer::create();
        addChild(portBgLayer,-1);
        portUIlayer=PortUILayer::create();
        addChild(portUIlayer,2);
        SND->playMusic("sound_bgm/sound 2.mp3");
        initSoundButton();
        
        bRet=true;
    }while(0);
    
    return bRet;
    
}


void PortScene::updateUILayerAttr()
{
    portUIlayer->changeLabelAmmo(sPlayer.getAmmo());
    portUIlayer->changeLabelFuel(sPlayer.getFuel());
    portUIlayer->changeLabelSteel(sPlayer.getSteel());
    portUIlayer->changeLabelAluminium(sPlayer.getAluminium());
}

void PortScene::changeToSoundPanel()
{
    if (openSoundPanel)
    {
        SetCurrPanel(PanelType::PORT_MAINLAYER);
        openSoundPanel=!openSoundPanel;
    }
    else
    {
        SetCurrPanel(PanelType::SOUND);
        openSoundPanel=!openSoundPanel;
    }
}

void PortScene::initSoundButton()
{
    openSoundPanel=false;
    soundButton=SoundPanelButton::create(CC_CALLBACK_0(PortScene::changeToSoundPanel, this));
    Vec2 pos=Vec2(Director::getInstance()->getWinSize().width-26, 26);
    soundButton->setPosition(pos);
    addChild(soundButton,5);
}




///------------------------------

NS_KCL_END
