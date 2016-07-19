//
//  portMainLayer.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "portMainLayer.h"
#include "Player.h"
#include "signBoardGirl.hpp"
#include "MainLayerButton.hpp"
#include "furnitureBG.hpp"
#include "portScene.h"

NS_KCL_BEGIN





PortMainLayer::PortMainLayer():signBoardGirl(NULL)
{
}

void PortMainLayer::initLayer()
{
    furnitureBG=FurnitureBG::create();
    addChild(furnitureBG,-2);
    furnitureBG->setPosition(Vec2::ZERO);
}



bool PortMainLayer::init()
{
    if (!Panel::init()) {
        return false;
    }
    initLayer();
    initSignBoardGirl();
    initMenu();
    
    return true;
}


void PortMainLayer::initSignBoardGirl()
{
    signBoardGirl=SignBoardGirl::create();
    signBoardGirl->setPosition(600,0);
    addChild(signBoardGirl);
}

void PortMainLayer::updateGirl()
{
    signBoardGirl->updateGirl();
}


void PortMainLayer::changePanel(PanelType type)
{
    auto parent=static_cast<PortScene*>(_parent);
    parent->SetCurrPanel(type);
}


void PortMainLayer::resumeDispatcher()
{
//    EventDispatcher* eventDispatcher=Director::getInstance()->getEventDispatcher();
//    eventDispatcher->resumeEventListenersForTarget(organizeButton);
//    eventDispatcher->resumeEventListenersForTarget(supplyButton);
//    eventDispatcher->resumeEventListenersForTarget(remodeButton);
//    eventDispatcher->resumeEventListenersForTarget(repairButton);
//    eventDispatcher->resumeEventListenersForTarget(factoryButton);
//    eventDispatcher->resumeEventListenersForTarget(battleButton);
}

void PortMainLayer::initMenu()
{
    organizeButton=NormalMainLayerButton::create(MainLayerButtonType::ORGANIZE_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_ORGANIZE));
    organizeButton->setPosition(Vec2(145+(300-145)/2, 340));
    addChild(organizeButton);

    supplyButton=NormalMainLayerButton::create(MainLayerButtonType::SUPPLY_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_SUPPLY));
    supplyButton->setPosition(100, 260);
    addChild(supplyButton);

    remodeButton=NormalMainLayerButton::create(MainLayerButtonType::REMODE_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_REMODE));
    remodeButton->setPosition(345, 260);
    addChild(remodeButton);
    
    repairButton=NormalMainLayerButton::create(MainLayerButtonType::REPAIR_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_REPAIR));
    repairButton->setPosition(145, 110);
    addChild(repairButton);
    
    factoryButton=NormalMainLayerButton::create(MainLayerButtonType::FACTORY_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_FACTORY));
    factoryButton->setPosition(300, 110);
    addChild(factoryButton);
    
    battleButton=BattleMainLayerButton::create(MainLayerButtonType::BATTLE_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_BATTLE));
    battleButton->setPosition((145+(300-145)/2), 210);
    addChild(battleButton);
}

PortMainLayer::~PortMainLayer()
{

}

NS_KCL_END


