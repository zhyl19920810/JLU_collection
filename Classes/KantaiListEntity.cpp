//
//  KantaiListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//


#include "KantaiListEntity.hpp"
#include "portOrganizeLayer.h"
#include "ViewMgr.hpp"


NS_KCL_BEGIN

void KantaiListEntity::hideSelect(cocos2d::Ref *pSender)
{

}

void KantaiListEntity::showSelect(Kantai* kantai)
{
    PortOrganizeLayer* panel=dynamic_cast<PortOrganizeLayer*>(VIEW_MGR->getPanel(PanelType::PORT_ORGANIZE));
    panel->showSelect(kantai);
}

void KantaiListEntity::removeCallback(cocos2d::Ref *ref)
{
    PortOrganizeLayer* panel=dynamic_cast<PortOrganizeLayer*>(VIEW_MGR->getPanel(PanelType::PORT_ORGANIZE));
    panel->modifyContainer(REMOVE_CONTAINER);
}

bool KantaiListEntity::init()
{
    bool bRet=false;
    do
    {
        if (!ListEntity::init())
        {
            break;
        }
        
        Sprite* line = Sprite::create("CommonAssets/Line.png");
        addChild(line);
        line->setPosition(540+35, 345-12);
        
        Label *removeLabel = Label::create("remove", "fonts/DengXian.ttf", 13);
        removeLabel->setPosition(Vec2::ZERO);
        removeLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        removeLabel->setColor(Color3B::BLACK);
        MenuItemLabel* removeButton=MenuItemLabel::create(removeLabel, CC_CALLBACK_1(ListEntity::removeCallback, this));
        removeButton->setPosition(430,345);
        menu->addChild(removeButton);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}


NS_KCL_END
