//
//  FactoryListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/6/16.
//
//

#include "FactoryListEntity.hpp"
#include "portFactoryLayer.h"
#include "ViewMgr.hpp"

NS_KCL_BEGIN




FactoryListEntity* FactoryListEntity::create(cocos2d::Vec2 vec)
{
    FactoryListEntity* pRet=new FactoryListEntity;
    if (pRet&&pRet->FactoryListEntity::init(vec))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}


void FactoryListEntity::showSelect(Kantai* kantai)
{
    auto panel=dynamic_cast<PortFactoryLayer*>(VIEW_MGR->getPanel(PanelType::PORT_FACTORY));
    panel->showSelect(kantai);
}


bool FactoryListEntity::init(Vec2 vec)
{
    bool bRet=false;
    do
    {
        if (!ListEntity::init(vec))
        {
            break;
        }

        bRet=true;
    }while(0);
    
    return bRet;
}



NS_KCL_END
