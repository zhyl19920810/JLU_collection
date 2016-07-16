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
    if (!Layer::init()) {
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
    organizeButton=NormalMainLayerButton::create(MainLayerButtonType::ORGANIZE_BUTTON, NULL);
    organizeButton->setPosition(Vec2(145+(300-145)/2, 340));
    addChild(organizeButton);

    supplyButton=NormalMainLayerButton::create(MainLayerButtonType::SUPPLY_BUTTON, NULL);
    supplyButton->setPosition(100, 260);
    addChild(supplyButton);

    remodeButton=NormalMainLayerButton::create(MainLayerButtonType::REMODE_BUTTON, NULL);
    remodeButton->setPosition(345, 260);
    addChild(remodeButton);
    
    repairButton=NormalMainLayerButton::create(MainLayerButtonType::REPAIR_BUTTON, NULL);
    repairButton->setPosition(145, 110);
    addChild(repairButton);
    
    factoryButton=NormalMainLayerButton::create(MainLayerButtonType::FACTORY_BUTTON, NULL);
    factoryButton->setPosition(300, 110);
    addChild(factoryButton);
    
    battleButton=BattleMainLayerButton::create(MainLayerButtonType::BATTLE_BUTTON, NULL);
    battleButton->setPosition((145+(300-145)/2), 210);
    addChild(battleButton);
}

PortMainLayer::~PortMainLayer()
{

}

NS_KCL_END


