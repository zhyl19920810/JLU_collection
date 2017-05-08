//
//  SallyInfo.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "SallyInfo.hpp"


NS_KCL_BEGIN


SallyInfo* SallyInfo::create()
{
    SallyInfo* pRet=new SallyInfo;
    if(pRet&&pRet->init())
    {
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool SallyInfo::init()
{
    m_pMission=NULL;///这里需要改
    // this->currentMissionNode = mission->nodes[0];
    
    m_Status=SALLY_START;
    return true;
}

void SallyInfo::SetMission(int areaId, int index)
{
    
}

std::string SallyInfo::GetMissionName()
{//TODO 有可能有错误
    return std::to_string(m_pMission->areaId)+"-"+std::to_string(m_pMission->index);
}




NS_KCL_END
