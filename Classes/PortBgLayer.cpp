//
//  PortBgLayer.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "PortBgLayer.hpp"

NS_KCL_BEGIN

USING_NS_CC;

bool PortBgLayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        bgImage=cocos2d::Sprite::create("PortMain/image 345.jpg");
        bgImage->setPosition(800,210);
        addChild(bgImage);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
}




NS_KCL_END