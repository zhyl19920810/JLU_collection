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

bool KantaiListEntity::init(Vec2 vec)
{
    bool bRet=false;
    do
    {
        if (!ListEntity::init(vec))
        {
            break;
        }
        
        Vec2 tmp=bgimg->getContentSize()/2;
        Sprite* line = Sprite::create("CommonAssets/Line.png");
        entity->addChild(line);
        //line->setPosition(540+35, 345-12);
        line->setPosition(tmp+Vec2(-29, 138));
        
        Label *removeLabel = Label::create("remove", "fonts/DengXian.ttf", 13);
        removeLabel->setPosition(Vec2::ZERO);
        removeLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        removeLabel->setColor(Color3B::BLACK);
        MenuItemLabel* removeButton=MenuItemLabel::create(removeLabel, CC_CALLBACK_1(ListEntity::removeCallback, this));
        //removeButton->setPosition(430,345);
        removeButton->setPosition(tmp+Vec2(-174,150));
        menu->addChild(removeButton);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}


KantaiListEntity* KantaiListEntity::create(Vec2 vec)
{
    KantaiListEntity* pRet=new KantaiListEntity;
    if (pRet&&pRet->init(vec))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}





NS_KCL_END
