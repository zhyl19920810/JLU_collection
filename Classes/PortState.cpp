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
    auto preType=owner->getCurrPanelType();
    m_pPreviousState=m_pCurrentState;
    m_pCurrentState->Exit(newType,owner);
    m_pCurrentState=getState(newType);
    owner->currentPanelType=newType;
    m_pCurrentState->Enter(preType,owner);
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


void MainPanelState::Enter(PanelType preType,kancolle::PortScene *portScene)
{
    
    switch (preType) {
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
            dynamic_cast<PortMainLayer*>(VIEW_MGR->getPanel(PanelType::PORT_MAINLAYER))->buttonFlyIn();
            dynamic_cast<PortMainLayer*>(VIEW_MGR->getPanel(PanelType::PORT_MAINLAYER))->updateGirl();
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
            dynamic_cast<PortMainLayer*>(VIEW_MGR->getPanel(PanelType::PORT_MAINLAYER))->setButtonDisable();
            break;
        default:
            break;
    }
    
}

void PortPanelState::Enter(PanelType preType,kancolle::PortScene *portScene)
{
    auto newType=portScene->getCurrPanelType();
    if (newType==preType)
    {
        return;
    }
    switch (preType)
    {
        case kancolle::PanelType::PORT_MAINLAYER:
            VIEW_MGR->showPanel(newType,false);
            portScene->portUIlayer->changeTitlePic(newType);
            portScene->layerSelecter->setLayerType(newType);
            portScene->layerSelecter->moveIn();
            break;
        case kancolle::PanelType::PORT_BATTLE:
        case kancolle::PanelType::PORT_FACTORY:
        case kancolle::PanelType::PORT_ORGANIZE:
        case kancolle::PanelType::PORT_REMODE:
        case kancolle::PanelType::PORT_REPAIR:
        case kancolle::PanelType::PORT_SUPPLY:
            portScene->layerSelecter->changeHookPos(newType);
            portScene->changePortPanelAction(newType);
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
    switch (newType)
    {
        case kancolle::PanelType::PORT_MAINLAYER:
            
            break;
        default:
            break;
    }
}


void SoundPanelState::Enter(kancolle::PanelType preType, kancolle::PortScene * portScene)
{
    auto panel=VIEW_MGR->showPanel(PanelType::SOUND,false,true);
    panel->setZOrder(4);
}

void SoundPanelState::Exit(kancolle::PanelType newType, kancolle::PortScene *portScene)
{
    
}






NS_KCL_END

