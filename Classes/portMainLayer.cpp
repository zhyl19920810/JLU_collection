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
#include "ViewMgr.hpp"

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
    signBoardGirl->setPosition(600,100);
    addChild(signBoardGirl);
}

void PortMainLayer::updateGirl()
{
    signBoardGirl->updateGirl();
}


void PortMainLayer::changePanel(PanelType type)
{
    auto parent=dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME));
    if (!parent) {
        CC_ASSERT("can not find portScene");
    }
    parent->SetCurrPanel(type);
}

void PortMainLayer::buttonFlyIn()
{
    setButtonDisable();
    buttonParent->setPosition(0,210);
    {
        ActionInterval* buttonMoveIn=MoveTo::create(0.2, Vec2(217, 210));
        CallFunc* actionEndCall=CallFunc::create([=]()
                                                 {
                                                     setButtonEnable();
                                                 });
        buttonParent->runAction(Sequence::create(buttonMoveIn,actionEndCall, NULL));
    }
    
}


void PortMainLayer::setButtonEnable()
{
    organizeButton->setEnable();
    supplyButton->setEnable();
    remodeButton->setEnable();
    repairButton->setEnable();
    factoryButton->setEnable();
    battleButton->setEnable();
    signBoardGirl->setEnable();
}


void PortMainLayer::setButtonDisable()
{
    organizeButton->setDisable();
    supplyButton->setDisable();
    remodeButton->setDisable();
    repairButton->setDisable();
    factoryButton->setDisable();
    battleButton->setDisable();
    signBoardGirl->setDisable();
}




void PortMainLayer::initMenu()
{
    buttonParent=Node::create();
    buttonParent->setPosition(Vec2(217, 210));
    addChild(buttonParent);
    
    organizeButton=NormalMainLayerButton::create(MainLayerButtonType::ORGANIZE_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_ORGANIZE));
    organizeButton->setPosition(Vec2(0,130));
    buttonParent->addChild(organizeButton);

    supplyButton=NormalMainLayerButton::create(MainLayerButtonType::SUPPLY_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_SUPPLY));
    supplyButton->setPosition(-117, 50);
    buttonParent->addChild(supplyButton);

    remodeButton=NormalMainLayerButton::create(MainLayerButtonType::REMODE_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_REMODE));
    remodeButton->setPosition(128, 50);
    buttonParent->addChild(remodeButton);
    
    repairButton=NormalMainLayerButton::create(MainLayerButtonType::REPAIR_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_REPAIR));
    repairButton->setPosition(-72, -100);
    buttonParent->addChild(repairButton);
    
    factoryButton=NormalMainLayerButton::create(MainLayerButtonType::FACTORY_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_FACTORY));
    factoryButton->setPosition(83, -100);
    buttonParent->addChild(factoryButton);
    
    battleButton=BattleMainLayerButton::create(MainLayerButtonType::BATTLE_BUTTON, CC_CALLBACK_0(PortMainLayer::changePanel, this,PanelType::PORT_BATTLE));
    battleButton->setPosition(Vec2::ZERO);
    buttonParent->addChild(battleButton);
}



PortMainLayer::~PortMainLayer()
{
    
}

NS_KCL_END


