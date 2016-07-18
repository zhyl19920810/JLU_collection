//
//  Panel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#include "Panel.hpp"


NS_KCL_BEGIN

bool Panel::init()
{
    bool bRet=false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}




NS_KCL_END