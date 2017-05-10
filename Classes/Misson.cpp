//
//  Misson.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#include "Misson.hpp"

NS_KCL_BEGIN


Mission* Mission::create()
{
    Mission* pRet=new Mission;
    if (pRet&&pRet->init())
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool Mission::init()
{
    bool bRet=false;
    
    do
    {
        
        bRet=true;
    }while(0);
    
    return bRet;
}

Mission::~Mission()
{
    for (int i=0; i<nodes.size(); ++i)
    {
        delete nodes[i];
    }
    release();
}



NS_KCL_END
