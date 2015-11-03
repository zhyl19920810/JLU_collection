//
//  BattleEnemy.h
//  kancolle_beta
//
//  Created by 岩林张 on 11/3/15.
//
//

#ifndef __kancolle_beta__BattleEnemy__
#define __kancolle_beta__BattleEnemy__

#include "BattleCharacter.h"
#include "cocos2d.h"


USING_NS_CC;



class BattleEnemy:public BattleCharacter
{
public:
    static BattleEnemy* create(Kantai* info,Node* parent,int row);
    
    bool init(int kantaiNumber,Node* parent,int row);
    
    virtual void setCurrentHp(int hp);
    
    virtual void setMaxHp(int hp);
    
    virtual void showCloseUp();
    
    virtual void stepOut(float delay);
    
    virtual void stepBack(float delay);
    
    void apearAnimation();
    
    virtual float showAttackingAnime(float delay);
    
    
private:
    
    virtual void ThreeDigitMode();
    
    virtual void updateInformationBoard();
};



#endif /* defined(__kancolle_beta__BattleEnemy__) */
