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


class SallyInfo
{
    friend class SallyPanel;
public:
    static SallyInfo* create();
    
    SallyStatus GetStatus() const{return m_Status;}
    void SetStatus(SallyStatus _status) {m_Status=_status;}
    std::string GetMissionName();
    void SetMission(int areaId,int index);
private:
    bool init();
    
    
private:
    Mission*        m_pMission;
    SallyStatus     m_Status;
    MissionNode*    m_CurMissonNode;
    
};


NS_KCL_END


#endif /* SallyInfo_hpp */
