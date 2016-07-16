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

NS_KCL_BEGIN

PortScene* PortScene::createScene()
{
    PortScene* scene=PortScene::create();
    sGameManger.setPortScene(scene);
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
currentLayerType(LayerType::NONE)
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

LayerType PortScene::getCurrLayerType() const
{
    return currentLayerType;
}


void PortScene::pauseLayerSelecterButton()
{
    layerSelecter->pauseButton();
}

void PortScene::resumeLayerSelecterButton()
{
    layerSelecter->resumeButton();
}



PortStateMachine::PortStateMachine(PortScene* _owner):
owner(_owner),
m_pPreviousState(&nullState),
m_pCurrentState(&nullState)
{}

void PortStateMachine::changeState(LayerType newType)
{
    m_pPreviousState=m_pCurrentState;
    m_pCurrentState->Exit(newType,owner);
    m_pCurrentState=getState(newType);
    m_pCurrentState->Enter(newType,owner);
}


PortState* PortStateMachine::getState(kancolle::LayerType newType)
{
    PortState* state=NULL;
    switch (newType)
    {
        case kancolle::LayerType::PORT_MAINLAYER:
            state=&mainLayerState;
            break;
        case kancolle::LayerType::PORT_BATTLE:
        case kancolle::LayerType::PORT_FACTORY:
        case kancolle::LayerType::PORT_ORGANIZE:
        case kancolle::LayerType::PORT_REMODE:
        case kancolle::LayerType::PORT_REPAIR:
        case kancolle::LayerType::PORT_SUPPLY:
            state=&portLayerState;
            break;
        case kancolle::LayerType::NONE:
            state=&nullState;
            break;
        default:
            break;
    }
    return state;
}


void MainLayerState::Enter(LayerType newType,kancolle::PortScene *portScene)
{
    switch (portScene->getCurrLayerType()) {
        case kancolle::LayerType::PORT_MAINLAYER:
            break;
        case kancolle::LayerType::NONE:
            VIEW_MGR->showLayer(LayerType::PORT_MAINLAYER);
            portScene->portUIlayer->setVisible(true);
            portScene->layerSelecter->setVisible(true);
            portScene->portUIlayer->changeTitlePic(LayerType::PORT_MAINLAYER);
        case kancolle::LayerType::PORT_BATTLE:
        case kancolle::LayerType::PORT_FACTORY:
        case kancolle::LayerType::PORT_ORGANIZE:
        case kancolle::LayerType::PORT_REMODE:
        case kancolle::LayerType::PORT_REPAIR:
        case kancolle::LayerType::PORT_SUPPLY:
            VIEW_MGR->showLayer(LayerType::PORT_MAINLAYER);
            portScene->portUIlayer->changeTitlePic(LayerType::PORT_MAINLAYER);
            portScene->layerSelecter->moveOut();
            break;
        default:
            break;
    }
}

void MainLayerState::Exit(LayerType newType,kancolle::PortScene *portScene)
{
    switch (newType)
    {
        case LayerType::PORT_MAINLAYER:
            break;
        default:
            break;
    }

}

void PortLayerState::Enter(LayerType newType,kancolle::PortScene *portScene)
{
    auto currType=portScene->getCurrLayerType();
    if (newType==currType)
    {
        return;
    }
    switch (currType)
    {
        case kancolle::LayerType::PORT_MAINLAYER:
            VIEW_MGR->showLayer(newType,false);
            portScene->portUIlayer->changeTitlePic(newType);
            portScene->layerSelecter->moveIn();
            break;
        case kancolle::LayerType::PORT_BATTLE:
        case kancolle::LayerType::PORT_FACTORY:
        case kancolle::LayerType::PORT_ORGANIZE:
        case kancolle::LayerType::PORT_REMODE:
        case kancolle::LayerType::PORT_REPAIR:
        case kancolle::LayerType::PORT_SUPPLY:
            VIEW_MGR->showLayer(newType,true);
            portScene->portUIlayer->changeTitlePic(newType);
            portScene->layerSelecter->moveIn();
            break;
        case kancolle::LayerType::NONE:
            VIEW_MGR->showLayer(newType);
            portScene->portUIlayer->setVisible(true);
            portScene->layerSelecter->setVisible(true);
            portScene->portUIlayer->changeTitlePic(newType);
            break;
        default:
            break;
    }
}

void PortLayerState::Exit(LayerType newType,kancolle::PortScene *portScene)
{
    
}




void PortScene::SetCurrLayer(LayerType type)
{
    if (type==getCurrLayerType()) {
        return;
    }
    portStateMachine.changeState(type);
    currentLayerType=type;
}


bool PortScene::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        schedule([this](float dt){SetCurrLayer(LayerType::PORT_MAINLAYER);}, 0, 0, 0, "init_portScene");
        layerSelecter=LayerSelecter::create(this, Vec2(-50, 220));
        addChild(layerSelecter,3);
        portBgLayer=PortBgLayer::create();
        addChild(portBgLayer,-1);
        portUIlayer=PortUILayer::create();
        addChild(portUIlayer,2);
        SND->playMusic("sound_bgm/sound 2.mp3");
        
        bRet=true;
    }while(0);
    
    return bRet;
    
}



///------------------------------

NS_KCL_END
