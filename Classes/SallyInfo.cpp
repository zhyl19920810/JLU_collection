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





SallyMgr* SallyMgr::m_pInstance=NULL;


SallyMgr* SallyMgr::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance=new SallyMgr;
        m_pInstance->init();
        m_pInstance->retain();
    }
    return m_pInstance;
}


bool SallyMgr::init()
{
    m_Status=SALLY_START;
    m_pMission=NULL;
    m_CurMissonNode=NULL;
    return true;
}


SallyMgr::~SallyMgr()
{
}

void SallyMgr::SallyReset()
{
    if (m_pMission)
    {
        delete m_pMission;
    }
    m_CurMissonNode=NULL;
    m_Status=SALLY_START;
}



void SallyMgr::SetMission(int areaId, int index)
{
    SallyReset();
    string strTmp=std::to_string(areaId)+"-"+std::to_string(index);
    m_pMission=MissonLoader::getInstance()->LoadMissionInfo(strTmp);
    m_CurMissonNode=m_pMission->nodes[0];
}

std::string SallyMgr::GetMissionName()
{//TODO 有可能有错误
    return std::to_string(m_pMission->areaId)+"-"+std::to_string(m_pMission->index+1);
}

MissionNode* SallyMgr::GetCurMissionNode()
{
    return m_CurMissonNode;
}


NS_KCL_END
