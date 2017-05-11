//
//  BattleCharacter.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleCharacter_hpp
#define BattleCharacter_hpp


#include "SystemHeader.h"
#include "BattleCharacterInfo.hpp"
#include "BattleBar.hpp"
#include "BattleAvatarCard.hpp"
#include "BattleInfoBoard.hpp"

//#include "AnimationMaker.h"
//#include "CharacterCard.h"



NS_KCL_BEGIN


USING_NS_CC;

class BattleCharacter :public cocos2d::Node
{
public:
    static BattleCharacter* create();
    virtual bool init() override;
    BattleCharacter();
 
    virtual void SetCurrentHp(int hp);
    virtual void SetMaxHp(int hp);
    virtual float ShowCloseUp(float delay){ return 0; };
    virtual float ShowAttackingAnime(float delay){ return 0; };
    virtual void StepOut(float delay){};
    virtual void StepBack(float delay){};
    
    inline void SetInfo(BattleCharacterInfo *info){ m_pBattleCharacterInfo=info; }
    inline BattleCharacterInfo* GetInfo(){ return m_pBattleCharacterInfo; }
    virtual void ThreeDigitMode(){};
    
protected:
    Sprite * border;
    Sprite * hpBar;
    Sprite * flagIcon;
    Sprite * closeUp;
    BattleBar * battleBar;
    Sprite* equipmentLabel;

    Label *maxHpLabel;
    Label *currentHpLabel;
    int maxHp;
    int currentHp;
    BattleCharacterInfo* m_pBattleCharacterInfo;
    BattleAvatarCard*    m_pBattleAvatarCard;
    BattleInfoBorard*    m_pBattleInfoBorard;
    
public:
    
    Point GetRealPosition();
    virtual bool CanAttack();
    float ReceiveDamage(float delay, bool miss, bool critical, int damage,int explodeTimes);
    

protected:
    
    virtual void SetBroken(BrokenType type);
    void GetDamage(int damage);
    void ShowAttackedAnime(float delay);
    void ShowDamageAnime(float delay, bool miss, bool critical, int damage);
   // virtual void UpdateInformationBoard(){};
    

    
public:
    std::string int2str(int &i);
};

NS_KCL_END



#endif /* BattleCharacter_hpp */
