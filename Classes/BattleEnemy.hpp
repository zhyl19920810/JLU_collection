//
//  BattleEnemy.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleEnemy_hpp
#define BattleEnemy_hpp

#include "SystemHeader.h"
#include "BattleCharacter.hpp"


NS_KCL_BEGIN

USING_NS_CC;


class BattleEnemy :public BattleCharacter
{
public:
    static BattleEnemy* create(BattleCharacterInfo *info,int row);
    bool init(BattleCharacterInfo *info,int row);
    virtual void SetCurrentHp(int hp);
    virtual void SetMaxHp(int hp);
    virtual void ShowCloseUp();
    virtual void StepOut(float delay);
    virtual void StepBack(float delay);
    void ApearAnimation();
    virtual float ShowAttackingAnime(float delay);
    
    ~BattleEnemy();
private:
    virtual void ThreeDigitMode();
   // virtual void UpdateInfo();
    
};

NS_KCL_END

#endif /* BattleEnemy_hpp */
