//
//  SallyInfo.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "SallyInfo.hpp"
#include "MissonLoader.hpp"
#include "Misson.hpp"


NS_KCL_BEGIN


SallyInfo* SallyInfo::create()
{
    SallyInfo* pRet=new SallyInfo;
    if(pRet&&pRet->init())
    {
        pRet->retain();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}

SallyInfo::~SallyInfo()
{
    delete m_pMission;
    release();
}


bool SallyInfo::init()
{
    m_Status=SALLY_START;
    return true;
}

void SallyInfo::SetMission(int areaId, int index)
{
    string strTmp=std::to_string(areaId)+"-"+std::to_string(index);
    m_pMission=MissonLoader::getInstance()->LoadMissionInfo(strTmp);
    m_CurMissonNode=m_pMission->nodes[0];
}

std::string SallyInfo::GetMissionName()
{//TODO 有可能有错误
    return std::to_string(m_pMission->areaId)+"-"+std::to_string(m_pMission->index+1);
}

MissionNode* SallyInfo::GetCurMissionNode()
{
    return m_CurMissonNode;
}


NS_KCL_END
