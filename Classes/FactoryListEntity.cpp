//
//  FactoryListEntity.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/6/16.
//
//

#include "FactoryListEntity.hpp"
#include "portFactoryLayer.h"





void FactoryListEntity::hideSelect(cocos2d::Ref *pSender)
{
    kantaiDestroyEntity->moveOut();
    hideListItem->setEnabled(false);
    
}

void FactoryListEntity::showSelect(Kantai* kantai)
{
    kantaiDestroyEntity->moveIn();
    kantaiDestroyEntity->update(kantai);
    hideListItem->setEnabled(true);
}

void FactoryListEntity::removeCallback(cocos2d::Ref *ref)
{
    //PortFactoryLayer* parent=static_cast<PortFactoryLayer*>(_parent);
    //parent->removeContainer();
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

        kantaiDestroyEntity=KantaiDestroyEntity::create();
        kantaiDestroyEntity->setPosition(238,0);
        addChild(kantaiDestroyEntity,2);
        
        
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
