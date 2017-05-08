//
//  BattlePanel.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattlePanel_hpp
#define BattlePanel_hpp

#include "SystemHeader.h"
#include "BattleInfo.hpp"
#include "BattleBar.hpp"
#include "BattleEnemy.hpp"
#include "BattleKantai.hpp"
#include "Formation.hpp"
#include "Panel.hpp"
#include "BattleFleetInfo.hpp"



NS_KCL_BEGIN


USING_NS_CC;

enum BattleStatus{
    start,
    character,
    scouting,
    formation,
    enemy,
    airbattle,
    firebattle,
    dayEnd
};


class BattlePanel:public kancolle::Panel
{
    
    enum LeftCornerType
    {
        suodi,
        paojizhan,
        yezhan,
        hangkongzhan,
        lituopanding
    };
    
public:
    static BattlePanel* create(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation);
    
    bool init(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation);
    
    int BattleEnemiesSize();
    int BattleKantaiSize();
private:
    void onStatusOverCallBack();

    void BattleStart();
    
    void ScoutStart();
    void DoScout();
    void ScoutResult();
    void AirBattle();
    void fireBattle();
    void DayEnd();
    void NextStatus(float DelayTime);
    //void initLeftCornerBar();
    void HideLeftCornerBar();
    void ShowLeftCornerBar(LeftCornerType type);
    void ShowCloseUpBorder();
    
    
private:
    bool                          m_bNightFight;
    BattleInfo*                   m_pBattleInfo;
    BattleBar*                    m_pBattleBar;
    Formation*                    m_pKantaiFormation;
    Formation*                    m_pEnemyFormation;
    Sprite*                       leftCornerBar;
    Sprite*                       leftCornerCircle;
    Sprite*                       leftCornerLable;
    Sprite*                       startBorderUp;
    Sprite*                       startBorderDown;
    BattleStatus                  status;
    Sprite*                       temptimer;
    Sprite*                       closeUpBorder;
    
    std::vector<BattleKantai*>    m_vBattleKantais;
    std::vector<BattleEnemy*>     m_vBattleEnemies;
    
private:
    void InitLeftCornerBar();
    void InitFormation();
    void InitCharacters();
    void InitEnemy();
    
};




NS_KCL_END


#endif /* BattlePanel_hpp */
