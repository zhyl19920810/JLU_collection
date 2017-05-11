//
//  BattleKantai.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/4/17.
//
//

#ifndef BattleKantai_hpp
#define BattleKantai_hpp

#include "SystemHeader.h"
#include "BattleCharacter.hpp"
#include "BattleCharacterInfo.hpp"

NS_KCL_BEGIN


USING_NS_CC;


class BattleKantai:public BattleCharacter
{
public:
    static BattleKantai* create(BattleCharacterInfo* info,int row);
    bool init(BattleCharacterInfo* info,int row);
    virtual void StepOut(float delay);
    virtual void StepBack(float delay);
    virtual float ShowCloseUp(float delay);
    virtual float ShowAttackingAnime(float delay);
    
protected:
    //virtual void UpdateInfo();
    
private:
    void InitInfo();
    BattleEquipInfo*    m_pMainCannon;
};


NS_KCL_END


#endif /* BattleKantai_hpp */
