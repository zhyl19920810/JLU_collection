//
//  BattleHero.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/25/15.
//
//

#ifndef __kancolle_beta__BattleHero__
#define __kancolle_beta__BattleHero__

#include "cocos2d.h"
#include "BattleCharacter.h"
USING_NS_CC;


class BattleHero:public BattleCharacter
{
public:
    static BattleHero* create(int kantaiNumber,Node* parent,int row);
    
    static BattleHero* create(Kantai* info,Node* parent,int row);
    
    bool init(int kantaiNumber, Node *parent, int row);
    
    virtual float showCloseUp(float delay);
    
    virtual void stepOut(float delay);
    
    virtual void stepBack(float delay);
    
    virtual float showAttackingAnime(float delay);
    
private:
    virtual void updateInformationBoard();
};


#endif /* defined(__kancolle_beta__BattleHero__) */
