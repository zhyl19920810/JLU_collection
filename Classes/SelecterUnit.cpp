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
#include "Sound.hpp"
#include "layerSelecter.h"

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
        CC_BREAK_IF(!Node::init());
        
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

std::string SelecterUnit::getPanelName(PanelType type) const
{
    std::string str;
    switch (type)
    {
        case PanelType::PORT_MAINLAYER:
            str="main";
            break;
        case PanelType::PORT_ORGANIZE:
            str="organize";
            break;
        case PanelType::PORT_SUPPLY:
            str="supply";
            break;
        case PanelType::PORT_REMODE:
            str="remode";
            break;
        case PanelType::PORT_REPAIR:
            str="repair";
            break;
        case PanelType::PORT_FACTORY:
            str="factory";
            break;
        default:
            break;
    }
    return str;
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
    if (type==PanelType::PORT_MAINLAYER)
    SND->playEffect("soundSE/mainButton.mp3");
    else
    SND->playEffect("soundSE/portButton.mp3");
    
    auto portScene=dynamic_cast<PortScene*>(VIEW_MGR->getScene(SceneType::HOME));
    if (!portScene)
    {
        log("SceneType::HOME can not find in layerSelectCallback");
        return;
    }
    portScene->SetCurrPanel(type);
}





NS_KCL_END