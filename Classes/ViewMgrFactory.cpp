//
//  ViewMgrFactory.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/6/16.
//
//

#include "ViewMgrFactory.hpp"
#include "portScene.h"
#include "portSupplyLayer.h"
#include "portFactoryLayer.h"
#include "portMainLayer.h"
#include "portRemodeLayer.h"
#include "portRepairLayer.h"
#include "portOrganizeLayer.h"
#include "portBattleLayer.h"
#include "SoundPanel.hpp"
#include "SallyPanel.hpp"
#include "BattlePanel.hpp"
#include "SallyScene.hpp"
#include "BattleScene.hpp"


NS_KCL_BEGIN

cocos2d::Scene* ViewMgrFactory::getScene(SceneType type,const cocos2d::Value& data)
{
    cocos2d::Scene* _scene=nullptr;
    switch (type)
    {
        case SceneType::HOME:
            _scene=PortScene::createScene();
            break;
        case SceneType::LOGIN:
            break;
        case SceneType::SALLY:
            _scene=SallyScene::create();
            break;
        case SceneType::BATTLE:
            _scene=BattleScene::create();
            break;
        default:
            break;
    }
    return _scene;
}


Panel* ViewMgrFactory::getPanel(PanelType type,const cocos2d::Value& data)
{
    Panel* _panel=nullptr;
    switch (type)
    {
        case PanelType::PORT_SUPPLY:
            _panel=PortSupplyLayer::create();
            break;
        case PanelType::PORT_FACTORY:
            _panel=PortFactoryLayer::create();
            break;
        case PanelType::PORT_ORGANIZE:
            _panel=PortOrganizeLayer::create();
            break;
        case PanelType::PORT_MAINLAYER:
            _panel=PortMainLayer::create();
            break;
        case PanelType::PORT_REMODE:
            _panel=PortRemodeLayer::create();
            break;
        case PanelType::PORT_BATTLE:
            _panel=PortBattleLayer::create();
            break;
        case PanelType::PORT_REPAIR:
            _panel=PortRepairLayer::create();
            break;
        case PanelType::SOUND:
            _panel=SoundPanel::create();
            break;
        case PanelType::SALLY_MAIN:
            _panel=SallyPanel::create();
            break;
        case PanelType::BATTLE_MAIN:
            _panel=BattlePanel::create();
        default:
            break;
    }
    return _panel;
}



NS_KCL_END
