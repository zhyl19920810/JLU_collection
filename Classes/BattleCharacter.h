//
//  BattleCharacter.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#ifndef __kancolle_beta__BattleCharacter__
#define __kancolle_beta__BattleCharacter__

#include "cocos2d.h"
#include "kantai.h"
#include "CharacterCard.h"
#include "AnimationMaker.h"
#include "BattleBar.h"


USING_NS_CC;

NS_KCL_BEGIN

class BattleCharacter:public Node
{
public:
    BattleCharacter();
    
    Point getRealPosition();
    
    virtual void setCurrentHp(int hp);
    
    virtual void setMaxHp(int hp);
    
    virtual float showCloseUp(float delay){return 0;}
    
    virtual float showAttackingAnime(float delay){return 0;}
    
    virtual bool canAttack();
    
    float receiveDamage(float delay,bool miss,bool critical,int damage,int explodeTimes);
    
    virtual void stepOut(float delay){}
    
    virtual void stepBack(float delay){}
    
    
protected:
    Kantai* info;
    
    inline void setInfo(Kantai* info){this->info=info;}
    
    inline Kantai* getInfo(){return this->info;}
    
    CharacterCard* card;
    
    Sprite * border;
    Sprite * hpBar;
    Sprite * flagIcon;
    Sprite * closeUp;
    
    BattleBar * battleBar;
    Sprite* equipmentLabel;
    
    Sprite * informationBoard;
    Label *firePowerLabel;
    Label *torpedoLabel;
    Label *antiaircraftLabel;
    Label *nameLabel;
    Label *levelLabel;
    Label *armourLabel;
    Sprite *equipment1;
    Sprite *equipment2;
    Sprite* equipment3;
    Sprite* equipment4;
    
    virtual void ThreeDigitMode(){}
    
    virtual void setBroken(BrokenType type);
    
    void getDamage(int damage);
    
    void showAttackAnime(float delay);
    
    void showDamgeAnime(float delay,bool miss,bool critical,int damage);
    
    virtual void updateInformationBoard(){};
    
    Label *maxHpLabel;
    Label *currentHpLabel;
    int maxHp;
    int currentHp;
    int kantaiNumber;
    Node * parent;
    BrokenType type;

};


NS_KCL_END




#endif /* defined(__kancolle_beta__BattleCharacter__) */
