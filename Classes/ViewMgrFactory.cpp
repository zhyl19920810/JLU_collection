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
            
        default:
            break;
    }
    return _scene;
}


cocos2d::Layer* ViewMgrFactory::getLayer(LayerType type,const cocos2d::Value& data)
{
    cocos2d::Layer* _layer=nullptr;
    switch (type)
    {
        case LayerType::PORT_SUPPLY:
            _layer=PortSupplyLayer::create();
            break;
        case LayerType::PORT_FACTORY:
            _layer=PortFactoryLayer::create();
            break;
        case LayerType::PORT_ORGANIZE:
            _layer=PortOrganizeLayer::create();
            break;
        case LayerType::PORT_MAINLAYER:
            _layer=PortMainLayer::create();
            break;
        case LayerType::PORT_REMODE:
            _layer=PortRemodeLayer::create();
            break;
        case LayerType::PORT_BATTLE:
            _layer=PortBattleLayer::create();
            break;
        case LayerType::PORT_REPAIR:
            _layer=PortRepairLayer::create();
            break;
            
            
        default:
            break;
    }
    return _layer;
}




NS_KCL_END