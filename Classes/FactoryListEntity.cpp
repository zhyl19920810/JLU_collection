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


void FactoryListEntity::hideSelect(cocos2d::Ref *pSender)
{
    //kantaiDestroyEntity->moveOut();
    //selectCover->setCoverEnable(false);
    
}

void FactoryListEntity::showSelect(Kantai* kantai)
{
    auto panel=dynamic_cast<PortFactoryLayer*>(VIEW_MGR->getPanel(PanelType::PORT_FACTORY));
    panel->showSelect(kantai);
}

void FactoryListEntity::removeCallback(cocos2d::Ref *ref)
{
    
}

bool FactoryListEntity::init()
{
    bool bRet=false;
    do
    {
        if (!ListEntity::init())
        {
            break;
        }

        bRet=true;
    }while(0);
    
    return bRet;
}


void FactoryListEntity::destoryKantai(Kantai *kantai)
{
    int p1=0,p2=0;
    while (p2<displayKantai.size())
    {
        if (displayKantai[p2]!=kantai)
        {
            displayKantai[p1++]=displayKantai[p2++];
        }else
        {
            ++p2;
        }
    }
    displayKantai.pop_back();
}

NS_KCL_END
