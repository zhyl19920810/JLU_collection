//
//  KantaiListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//


#include "KantaiListEntity.hpp"
#include "portOrganizeLayer.h"

void KantaiListEntity::hideSelect(cocos2d::Ref *pSender)
{
    organSelectEntity->moveOut();
    hideListItem->setEnabled(false);
    
}

void KantaiListEntity::showSelect(Kantai* kantai)
{
    organSelectEntity->moveIn();
    organSelectEntity->updateKantai(kantai);
    hideListItem->setEnabled(true);
}

void KantaiListEntity::removeCallback(cocos2d::Ref *ref)
{
    PortOrganizeLayer* parent=static_cast<PortOrganizeLayer*>(_parent);
    parent->removeContainer();
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
        
        
        organSelectEntity=OrganSelectEntity::create();
        organSelectEntity->setPosition(238,0);
        addChild(organSelectEntity,2);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}



