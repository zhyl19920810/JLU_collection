//
//  SallyInfo.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef SallyInfo_hpp
#define SallyInfo_hpp


#include "SystemHeader.h"
#include "Misson.hpp"
#include "MissionNode.hpp"

NS_KCL_BEGIN

USING_NS_CC;


enum SallyStatus{
    SALLY_START,
    SALLY_MOVE,
    SALLY_FORMATION,
    SALLY_BATTLE,
};


#define  SALLY_MGR SallyMgr::GetInstance()


class SallyMgr:public Ref
{
    friend class SallyPanel;
public:
    static SallyMgr* GetInstance();
    void DelInstance();
    ~SallyMgr();
    
    void SallyReset();
    SallyStatus GetStatus() const{return m_Status;}
    void SetStatus(SallyStatus _status) {m_Status=_status;}
    std::string GetMissionName();
    void SetMission(int areaId,int index);
    MissionNode* GetCurMissionNode();
    bool IfEndSally();

private:
    bool init();
    
    
private:
    Mission*        m_pMission;
    SallyStatus     m_Status;
    MissionNode*    m_CurMissonNode;
    static SallyMgr*  m_pInstance;
    
};


NS_KCL_END


#endif /* SallyInfo_hpp */
