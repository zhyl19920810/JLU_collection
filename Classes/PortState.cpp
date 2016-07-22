//
//  PortState.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/19/16.
//
//

#include "PortState.hpp"
#include "portScene.h"
#include "ViewMgr.hpp"
#include "portMainLayer.h"
#include "PortUILayer.hpp"
#include "layerSelecter.h"
#include "SoundPanelButton.hpp"

NS_KCL_BEGIN

PortStateMachine::PortStateMachine(PortScene* _owner):
owner(_owner),
m_pPreviousState(&nullState),
m_pCurrentState(&nullState)
{}

void PortStateMachine::changeState(PanelType newType)
{
    m_pPreviousState=m_pCurrentState;
    m_pCurrentState->Exit(newType,owner);
    m_pCurrentState=getState(newType);
    m_pCurrentState->Enter(newType,owner);
}


PortState* PortStateMachine::getState(kancolle::PanelType newType)
{
    PortState* state=NULL;
    switch (newType)
    {
        case kancolle::PanelType::PORT_MAINLAYER:
            state=&mainPanelState;
            break;
        case kancolle::PanelType::PORT_BATTLE:
        case kancolle::PanelType::PORT_FACTORY:
        case kancolle::PanelType::PORT_ORGANIZE:
        case kancolle::PanelType::PORT_REMODE:
        case kancolle::PanelType::PORT_REPAIR:
        case kancolle::PanelType::PORT_SUPPLY:
            state=&portPanelState;
            break;
        case kancolle::PanelType::NONE:
            state=&nullState;
        case kancolle::PanelType::SOUND:
            state=&soundPanelState;
            break;
        default:
            break;
    }
    return state;
}


void MainPanelState::Enter(PanelType newType,kancolle::PortScene *portScene)
{
    switch (portScene->getCurrPanelType()) {
        case kancolle::PanelType::PORT_MAINLAYER:
            break;
        case kancolle::PanelType::NONE:
            VIEW_MGR->showPanel(PanelType::PORT_MAINLAYER);
            portScene->portUIlayer->setVisible(true);
            portScene->layerSelecter->setVisible(true);
            portScene->portUIlayer->changeTitlePic(PanelType::PORT_MAINLAYER);
            break;
        case kancolle::PanelType::PORT_BATTLE:
        case kancolle::PanelType::PORT_FACTORY:
        case kancolle::PanelType::PORT_ORGANIZE:
        case kancolle::PanelType::PORT_REMODE:
        case kancolle::PanelType::PORT_REPAIR:
        case kancolle::PanelType::PORT_SUPPLY:
            VIEW_MGR->showPanel(PanelType::PORT_MAINLAYER);
            portScene->soundButton->setVisible(true);
            portScene->portUIlayer->changeTitlePic(PanelType::PORT_MAINLAYER);
            portScene->layerSelecter->moveOut();
            break;
        case kancolle::PanelType::SOUND:
            VIEW_MGR->showPanel(PanelType::PORT_MAINLAYER);
            break;
        default:
            break;
    }
}

void MainPanelState::Exit(PanelType newType,kancolle::PortScene *portScene)
{
    switch (newType)
    {
        case PanelType::PORT_MAINLAYER:
            break;
        case PanelType::SOUND:
            log("mainPanel exit(soundPanel will in");
            break;
        case kancolle::PanelType::PORT_BATTLE:
        case kancolle::PanelType::PORT_FACTORY:
        case kancolle::PanelType::PORT_ORGANIZE:
        case kancolle::PanelType::PORT_REMODE:
        case kancolle::PanelType::PORT_REPAIR:
        case kancolle::PanelType::PORT_SUPPLY:
            portScene->soundButton->setVisible(false);
            break;
        default:
            break;
    }
    
}

void PortPanelState::Enter(PanelType newType,kancolle::PortScene *portScene)
{
    auto currType=portScene->getCurrPanelType();
    if (newType==currType)
    {
        return;
    }
    switch (currType)
    {
        case kancolle::PanelType::PORT_MAINLAYER:
            VIEW_MGR->showPanel(newType,false);
            portScene->portUIlayer->changeTitlePic(newType);
            portScene->layerSelecter->moveIn();
            break;
        case kancolle::PanelType::PORT_BATTLE:
        case kancolle::PanelType::PORT_FACTORY:
        case kancolle::PanelType::PORT_ORGANIZE:
        case kancolle::PanelType::PORT_REMODE:
        case kancolle::PanelType::PORT_REPAIR:
        case kancolle::PanelType::PORT_SUPPLY:
            VIEW_MGR->showPanel(newType,true);
            portScene->portUIlayer->changeTitlePic(newType);
            portScene->layerSelecter->moveIn();
            break;
        case kancolle::PanelType::NONE:
            VIEW_MGR->showPanel(newType);
            portScene->portUIlayer->setVisible(true);
            portScene->layerSelecter->setVisible(true);
            portScene->portUIlayer->changeTitlePic(newType);
            break;
        case kancolle::PanelType::SOUND:
            
            break;
        default:
            break;
    }
}

void PortPanelState::Exit(PanelType newType,kancolle::PortScene *portScene)
{
    
}


void SoundPanelState::Enter(kancolle::PanelType newType, kancolle::PortScene * portScene)
{
    auto panel=VIEW_MGR->showPanel(PanelType::SOUND,false,true);
    panel->setZOrder(4);
}

void SoundPanelState::Exit(kancolle::PanelType newType, kancolle::PortScene *portScene)
{
    
}

NS_KCL_END

