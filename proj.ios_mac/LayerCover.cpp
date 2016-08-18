//
//  LayerCover.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/16/16.
//
//

#include "LayerCover.hpp"


NS_KCL_BEGIN

LayerCover* LayerCover::create(FUNC callback)
{
    LayerCover* pRet=new LayerCover;
    if (pRet&&pRet->init(callback))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}



bool LayerCover::init(FUNC callback)
{
    bool bRet=false;
    do
    {
        if (!Layer::init())
        {
            break;
        }
        this->callback=callback;
        bgCover=LayerColor::create(Color4B(0,0,0,150));
        bgCover->setPosition(0,0);
        addChild(bgCover,2);
        bgCover->setVisible(false);
        
//        auto listen_layer = Layer::create();
//        this->addChild(listen_layer,2);
        
        listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch *touch, Event *event)
        {
            if (callback)
                callback(this);
            
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
        listener->setEnabled(false);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
    
}


void LayerCover::setCoverEnable(bool bEnble)
{
    listener->setEnabled(bEnble);
    bgCover->setVisible(bEnble);
}

NS_KCL_END

