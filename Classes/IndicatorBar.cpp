//
//  IndicatorBar.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "IndicatorBar.hpp"

NS_KCL_BEGIN

USING_NS_CC;

bool IndicatorBar::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        auto top_bar = Sprite::create("OrganizeMain/topBar.png");
        addChild(top_bar);
        top_bar->setPosition(Vec2(-370, 188));///可能需要改
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}





NS_KCL_END
