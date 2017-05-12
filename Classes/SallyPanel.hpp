//
//  SallyPanel.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef SallyPanel_hpp
#define SallyPanel_hpp

#include "SystemHeader.h"
#include "Panel.hpp"
#include "Compass.hpp"
#include "FormationSelecter.hpp"
#include "SallyShip.hpp"
#include "SallyInfo.hpp"
#include "FlagShip.hpp"

NS_KCL_BEGIN

USING_NS_CC;


class SallyPanel:public Panel
{
public:
    CREATE_FUNC(SallyPanel);
    
    virtual bool init();
    virtual ~SallyPanel();
    void SetFormationCallback(Ref* pSender, FormationType formation);
    void SetMission(int areaId,int index);
    void SetMission();
    
private:
    
    void InitBg();
    
    
    
private:
    
    Compass*               m_pCompass;
    FormationSelecter*     m_pFormationSelecter;
    SallyShip*             m_pSallyShip;
    FlagShip*              m_pFlagShip;
    
    
    
private:
    Sprite*        bgImg;
    Sprite*        sallyMap;
    Sprite*        m_pBottomBorder;
    Label*         m_pBottomLabel;
    Sprite*        temptimer;
    bool           m_bShowingBottomPanel;
    Sprite*        m_pNodePointShader;
    
private:
    void SallyStart();
    void SallyMove();
    void SallyBattle();
    void SallyFormation();
    void SallyFinish();
    void OnStatusOverCallBack();
    void NextStatus(float delayTime);
    void HideBottomPanel();
    void ShowBottomPanel();
};




NS_KCL_END

#endif /* SallyPanel_hpp */
