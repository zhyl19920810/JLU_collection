//
//  SelecterUnit.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/24/16.
//
//

#include "SelecterUnit.hpp"
#include "ViewMgr.hpp"
#include "portScene.h"


NS_KCL_BEGIN

SelecterUnit* SelecterUnit::create(PanelType panelType)
{
    SelecterUnit* pRet=new SelecterUnit;
    if (pRet&&pRet->init(panelType))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

bool SelecterUnit::init(PanelType panelType)
{
    bool bRet=false;
    do
    {
        _panelType=panelType;
        {
            std::string freeStatePath=getFreeStatePath();
            std::string selectedStatePath=getSelectedStatePath();
            
            _button=MenuItemSprite::create(Sprite::createWithSpriteFrameName(freeStatePath.c_str()), Sprite::createWithSpriteFrameName(selectedStatePath.c_str()), Sprite::createWithSpriteFrameName(selectedStatePath.c_str()), CC_CALLBACK_1(SelecterUnit::layerSelectCallback, this, _panelType));
            _button->setPosition(Vec2::ZERO);
            
            auto menu=Menu::create();
            menu->setPosition(Vec2::ZERO);
            addChild(menu);
            menu->addChild(_button);
            
            setSelected(false);
        }
        bRet=true;
    }while(0);
    
    return bRet;
}


void SelecterUnit::setSelected(bool enable)
{
    if (enable==_enable) return;
    if (enable)
    {
        _selecterState=LayerSelecterState::SELECTED;
        _button->setEnabled(false);
        _enable=enable;
    }
    else
    {
        _selecterState=LayerSelecterState::FREE;
        _button->setEnabled(true);
        _enable=enable;
    }
}



std::string SelecterUnit::getFreeStatePath()
{
    std::string sRet;
    switch (_panelType)
    {
        case PanelType::PORT_MAINLAYER:
            sRet="portItem1.png";
            break;
        case PanelType::PORT_ORGANIZE:
            sRet="organizeItem1.png";
            break;
        case PanelType::PORT_SUPPLY:
            sRet="supplyItem1.png";
            break;
        case PanelType::PORT_REMODE:
            sRet="remodeItem1.png";
            break;
        case PanelType::PORT_REPAIR:
            sRet="repairItem1.png";
            break;
        case PanelType::PORT_FACTORY:
            sRet="factoryItem1.png";
            break;
        default:
            break;
    }
    return sRet;
}


std::string SelecterUnit::getSelectedStatePath()
{
    std::string sRet;
    switch (_panelType)
    {
        case PanelType::PORT_MAINLAYER:
            sRet="portItem2.png";
            break;
        case PanelType::PORT_ORGANIZE:
            sRet="organizeItem2.png";
            break;
        case PanelType::PORT_SUPPLY:
            sRet="supplyItem2.png";
            break;
        case PanelType::PORT_REMODE:
            sRet="remodeItem2.png";
            break;
        case PanelType::PORT_REPAIR:
            sRet="repairItem2.png";
            break;
        case PanelType::PORT_FACTORY:
            sRet="factoryItem2.png";
            break;
        default:
            break;
    }
    return sRet;
}



void SelecterUnit::layerSelectCallback(cocos2d::Ref *pSender, PanelType type)
{
    auto portScene=dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME));
    if (!portScene)
    {
        log("SceneType::HOME can not find in layerSelectCallback");
        return;
    }
    portScene->SetCurrPanel(type);
}

//portItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("portItem1.png"),Sprite::createWithSpriteFrameName("portItem2.png"),CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_MAINLAYER));
//portItem->setPosition(22, 0);
//organizeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("organizeItem1.png"),Sprite::createWithSpriteFrameName("organizeItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_ORGANIZE));
//organizeItem->setPosition(-30, 100);
//supplyItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("supplyItem1.png"),Sprite::createWithSpriteFrameName("supplyItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_SUPPLY));
//supplyItem->setPosition(-30, 50);
//remodeItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("remodeItem1.png"),Sprite::createWithSpriteFrameName("remodeItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_REMODE));
//remodeItem->setPosition(-30, 0);
//repairItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("repairItem1.png"),Sprite::createWithSpriteFrameName("repairItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_REPAIR));
//repairItem->setPosition(-30, -50);
//factoryItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("factoryItem1.png"),Sprite::createWithSpriteFrameName("factoryItem2.png"), CC_CALLBACK_1(LayerSelecter::layerSelectCallback, this, PanelType::PORT_FACTORY));
//factoryItem->setPosition(-30, -100);





NS_KCL_END