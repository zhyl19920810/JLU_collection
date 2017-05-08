//
//  BattleScene.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include "SystemHeader.h"


NS_KCL_BEGIN

USING_NS_CC;

class BattleScene:public Scene
{
public:
    static BattleScene* create();
    
    
    
private:
    virtual bool init() override;
    
    
    
};




NS_KCL_END



//#include "cocos2d.h"
//#include "BattleInfo.hpp"
//#include "BattleBar.h"
//#include "BattleHero.h"
//#include "BattleEnemy.h"
//#include "formation.h"
//using namespace cocos2d;
//
//enum BattleStatus{
//    start,
//    character,
//    scouting,
//    formation,
//    enemy,
//    airbattle,
//    firebattle,
//    dayEnd
//};

//class GameScene : public Scene{
//public:
//    GameScene(BattleModel *model);
//    
//private:
//    BattleModel* model;
//    
//private:
//    void onStatusOverCallBack();
//    void initCharacters();
//    void initEnemy();
//    void BattleStart();
//    void initFormation();
//    void scoutStart();
//    void doScout();
//    void scoutResult();
//    void airBattle();
//    void fireBattle();
//    void dayEnd();
//    
//    
//    void nextStatus(float DelayTime);
//    
//private:	//Left Corner Bar
//    enum LeftCornerType
//    {
//        suodi,
//        paojizhan,
//        yezhan,
//        hangkongzhan,
//        lituopanding
//    };
//    void initLeftCornerBar();
//    void hideLeftCornerBar();
//    void showLeftCornerBar(LeftCornerType type);
//    Sprite *leftCornerBar;
//    Sprite *leftCornerCircle;
//    Sprite *leftCornerLable;
//    
//    
//private:
//    Sprite* startBorderUp;
//    Sprite* startBorderDown;
//    BattleBar* battleBar;
//    BattleStatus status;
//    Formation *myFormation;
//    Formation *enemyFormation;
//    Sprite * temptimer;
//    Sprite * closeUpBorder;
//    void showCloseUpBorder();
//    bool nightFight;
//    
//private:
//    std::vector<BattleHero*> battleHeros;
//    std::vector<BattleEnemy*> battleEnemies;
//    
//};


#endif /* BattleScene_hpp */
