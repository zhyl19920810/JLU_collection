//
//  GameScene.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#ifndef __kancolle_beta__GameScene__
#define __kancolle_beta__GameScene__


#include "cocos2d.h"
#include "Player.h"
#include "BattleModel.h"
#include "Formation.h"
#include "BattleBar.h"
#include "BattleHero.h"
#include "BattleEnemy.h"

NS_KCL_BEGIN

using namespace cocos2d;

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




class GameScene:public Scene
{
public:
    GameScene(BattleModel* model);
    
    void resetFireBattle();
    
    
    
private:
    BattleModel* model;
    
    
    
    
    
private:
    void onStatusOverCallBack();
    void initCharacters();
    void initEnemy();
    void BattleStart();
    void initFormation();
    void scoutStart();
    void doScout();
    void scoutResult();
    void airBattle();
    void fireBattle();
    void dayEnd();
    
    void nextStatus(float DelayTime);
    
    
private:
    enum LeftCornerType
    {
        suodi,
        paojizhan,
        yezhan,
        hangkongzhan,
        lituopanding
    };
    
    void initLeftCornerBar();
    
    void hideLeftCornerBar();
    
    void showLeftCornerBar(LeftCornerType type);
    
    Sprite *leftCornerBar;
    Sprite *leftCornerCircle;
    Sprite *leftCornerLable;
    
private:
    Sprite* startBorderUp;
    Sprite* startBorderDown;
    BattleBar* battleBar;
    BattleStatus status;
    Formation *myFormation;
    Formation *enemyFormation;
    Sprite * temptimer;
    Sprite * closeUpBorder;
    void showCloseUpBorder();
    bool nightFight;
    
private:
    std::vector<BattleHero*> battleHeros;
    std::vector<BattleEnemy*> battleEnemies;
};

NS_KCL_END

#endif /* defined(__kancolle_beta__GameScene__) */
