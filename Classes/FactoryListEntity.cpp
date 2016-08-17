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

void FactoryListEntity::addKantai(Kantai* kantai)
{
    displayKantai.push_back(kantai);
    sortButtonCallback(this);
    updateRows();
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
