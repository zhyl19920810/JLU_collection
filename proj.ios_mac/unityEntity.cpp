//
//  unityEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/9/16.
//
//

#include "unityEntity.hpp"
#include "LayerCover.hpp"
#include "EventPauseGuard.hpp"
#include "LayerCover.hpp"

NS_KCL_BEGIN


#define HIDE_POS (Vec2(238,0))
#define SHOW_POS (Vec2(-238,0))
#define MOVE_TIME 0.15

bool UnitEntity::init(Vec2 pos)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        hidden=false;
        
        initEntityBg(pos);
        setHide(true);
        
        bRet=true;
    }while(0);
    
    return bRet;
}


void UnitEntity::initEntityBg(Vec2 pos)
{
    layerCover=LayerCover::create(CC_CALLBACK_0(UnitEntity::moveOut, this));
    addChild(layerCover);
    layerCover->setPosition(-pos);
    
    entity=Node::create();
    entity->setPosition(Vec2::ZERO);
    addChild(entity);
    
    bgImg=Sprite::create("RepairMain/repairSelectBg1.png");
    bgImg->setPosition(Vec2::ZERO);
    entity->addChild(bgImg);
    auto tmp=bgImg->getContentSize()/2;
    
    auto entityBar=Sprite::create("RepairMain/repairBar.png");
    entityBar->setPosition(tmp.width+288,tmp.height+197);
    bgImg->addChild(entityBar);
}

void UnitEntity::setHide(bool _hide)
{
    if (hidden!=_hide)
    {
        if (_hide)
        {
            entity->setPosition(HIDE_POS);
            hidden=true;
        }
        else
        {
            entity->setPosition(Vec2::ZERO);
            hidden=false;
        }
    }
}


void UnitEntity::moveOut()
{
    if (!hidden)
    {
        CallFunc* moveByBefore=CallFunc::create([=]()
                                                {
                                                    EventPauseGuard::pause();
                                                });
        auto move=MoveBy::create(MOVE_TIME, HIDE_POS);
        CallFunc* moveByFinish=CallFunc::create([=]()
                                                {
                                                    EventPauseGuard::resume();
                                                    layerCover->setCoverEnable(false);
                                                });
        entity->runAction(Sequence::create(moveByBefore,move,moveByFinish, NULL));
        kantai=NULL;
        hidden = true;
    }
    
}
void UnitEntity::moveIn()
{
    if (hidden)
    {
        CallFunc* moveByBefore=CallFunc::create([=]()
                                                {
                                                    layerCover->setCoverEnable(true);
                                                    EventPauseGuard::pause();
                                                });
        auto move=MoveBy::create(MOVE_TIME, SHOW_POS);
        CallFunc* moveByFinish=CallFunc::create([=]()
                                                {
                                                    EventPauseGuard::resume();
                                                });
        entity->runAction(Sequence::create(moveByBefore,move,moveByFinish, NULL));
        hidden = false;
    }
}




NS_KCL_END