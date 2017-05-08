//
//  MissonSelectPage.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef MissonSelectPage_hpp
#define MissonSelectPage_hpp

#include "SystemHeader.h"
#include "MissonUnit.hpp"

NS_KCL_BEGIN


USING_NS_CC;

class MissionSelectPage :public Node
{
public:
    CREATE_FUNC(MissionSelectPage);
    virtual bool init() override;
    void MoveOut();
    void MoveIn();
    void SetCurrentArea(Ref* pSender, int areaId);
    void StartMission(Ref* pSender, int index);
private:
    void InitBg();
    
private:
    MissionContainer*     m_pContainer1;
    MissionContainer*     m_pContainer2;
    MissionContainer*     m_pContainer3;
    MissionContainer*     m_pContainer4;
    bool                  m_bHidden;
    int                   m_iCurrentArea;
    Menu*                 menu;
    
public:
    inline bool isHidden(){ return m_bHidden; }
private:
    
    
};




NS_KCL_END

#endif /* MissonSelectPage_hpp */
