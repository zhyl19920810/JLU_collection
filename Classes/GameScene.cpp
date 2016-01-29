//
//  GameScene.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 11/4/15.
//
//

#include "GameScene.h"


GameScene::GameScene(BattleModel *model)
{
    
    this->model = model;
    battleBar = new BattleBar(this);
    leftCornerLable = nullptr;
    nightFight = false;
    
    
    Sprite *bgImg;
    if (!nightFight)
        bgImg = Sprite::create("interface/BattleMain/BattleMain_86.jpg");
    else
        bgImg = Sprite::create("interface/BattleMain/BattleMain_87.jpg");
    
    bgImg->setPosition(400,240);
    this->addChild(bgImg);
    
    closeUpBorder = Sprite::create("interface/BattleMain/BattleMain_310.png");
    this->addChild(closeUpBorder);
    closeUpBorder->setZOrder(1);
    closeUpBorder->setOpacity(0);
    
    temptimer = Sprite::create("interface/BattleMain/BattleMain_515.png");
    this->addChild(temptimer);
    initLeftCornerBar();
    
    status = start;
    BattleStart();
    
}




void GameScene::nextStatus(float DelayTime)
{
    auto callFunc = CallFunc::create(CC_CALLBACK_0(GameScene::onStatusOverCallBack, this));
    auto *seq = Sequence::create(DelayTime::create(DelayTime), callFunc, NULL);
    temptimer->runAction(seq);
    
    
}


void GameScene::onStatusOverCallBack(){
    if (status == BattleStatus::start)
    {
        status = BattleStatus::character;
        initCharacters();
    }
    else if (status == BattleStatus::character)
    {
        status = BattleStatus::scouting;
        scoutStart();
    }
    else if (status == BattleStatus::scouting)
    {
        status = BattleStatus::enemy;
        initEnemy();
    }
    else if (status == BattleStatus::enemy)
    {
        status = BattleStatus::airbattle;
        airBattle();
    }
    else if (status == BattleStatus::airbattle)
    {
        status = BattleStatus::firebattle;
        fireBattle();
    }
    else if (status == BattleStatus::firebattle)
    {
        status = BattleStatus::dayEnd;
        dayEnd();
    }
    else {
        
        Director::getInstance()->popScene();
    }
    
}

void GameScene::dayEnd()
{
    showLeftCornerBar(lituopanding);
    startBorderUp->setZOrder(1);
    startBorderDown->setZOrder(1);
    startBorderUp->setTexture("interface/CommonAssets/image 473.png");
    startBorderDown->setTexture("interface/CommonAssets/image 471.png");
    startBorderUp->runAction(MoveTo::create(1, ccp(400,352)));
    startBorderDown->runAction(MoveTo::create(1, ccp(400,130)));
    startBorderDown->setScaleY(1.05);
    startBorderUp->setScaleY(1.05);
    
    
    auto escape=MenuItemImage::create("interface/BattleMain/BattleMain_32.png", "interface/BattleMain/BattleMain_39.png");
    auto nightBattle=MenuItemImage::create("interface/BattleMain/BattleMain_42.png", "interface/BattleMain/BattleMain_44.png");
    escape->setPosition(300,240);
    nightBattle->setPosition(500,240);
    
    escape->setOpacity(0);
    nightBattle->setOpacity(0);
    
    escape->runAction(Sequence::create(DelayTime::create(0.8),FadeIn::create(0.5), NULL));
    nightBattle->runAction(Sequence::create(DelayTime::create(0.8),FadeIn::create(0.5), NULL));
    
    auto menu=Menu::create(escape,nightBattle,NULL);
    addChild(menu);
    
    menu->setPosition(Point::ZERO);
    menu->setZOrder(2);
    
    nextStatus(5);
}





void GameScene::fireBattle()
{
    
    showLeftCornerBar(paojizhan);
    
    float timePassed=1;
    
    float delay1=0.5,delay2=1,delay3=1;
    
    bool doubleHit=false,ci=false,special=false,miss=false,critical=false;
    int damage=10;
    
    model->resetFireBattle();
    bool fire=false,allieAttack=false;
    int index;
    
    fire=model->getNextIndexToFire(allieAttack, index);
    
    while (fire)
    {
        if (allieAttack&&model->allies[index]->canAttack())
        {
            int targetIndex=model->getTargetIndex(allieAttack);
            if (targetIndex==-1)
            {
                nextStatus(timePassed+2);
                return;
            }
            battleHeros[index]->stepOut(timePassed);
            delay1=battleHeros[index]->showAttackingAnime(timePassed-0.35);
            delay2=delay1+0.5;
            delay3=delay1+1.5;
            
            
            battleEnemies[targetIndex]->stepOut(timePassed);
            model->getFireDamage(allieAttack, index, targetIndex, doubleHit, special, ci, damage, critical, miss);
            if (!miss)
            {
                model->enemy[targetIndex]->getDamage(damage);
            }
            battleEnemies[targetIndex]->receiveDamage(timePassed+delay1, miss, critical, damage, 1);
            battleEnemies[targetIndex]->stepBack(timePassed+delay1);
            battleHeros[index]->stepBack(timePassed+delay2);
            timePassed+=delay3;
        }
        else if(!allieAttack&&model->enemy[index]->canAttack())
        {
            int targetIndex=model->getTargetIndex(allieAttack);
            if (targetIndex==-1)
            {
                nextStatus(timePassed+2);
                return;
            }
            battleEnemies[index]->stepOut(timePassed);
            delay1=battleEnemies[index]->showAttackingAnime(timePassed)-0.35;
            delay2=delay1+0.5;
            delay3=delay1+1.5;
            
            battleHeros[targetIndex]->stepOut(timePassed);
            model->getFireDamage(allieAttack, targetIndex, index, doubleHit, special, ci, damage, critical, miss);
            
            if (!miss)
            {
                model->allies[targetIndex]->getDamage(damage);
            }
            battleHeros[targetIndex]->receiveDamage(timePassed+delay1, miss, critical, damage, 1);
            battleHeros[targetIndex]->stepBack(timePassed+delay1);
            battleEnemies[index]->stepBack(timePassed+delay2);
            timePassed+=delay3;
        }
        
        fire=model->getNextIndexToFire(allieAttack, index);
    }
    
    timePassed+=2.3;
    
    nextStatus(timePassed);
    
    
    
}




void GameScene::airBattle()
{
    
    bool airBattleHappens=false;

    int fireCvIndex;
    
    for (int i=model->allies.size()-1; i>=0; --i)
    {
        if (model->allies[i]->canAirBattle())
        {
            airBattleHappens=true;
            fireCvIndex=i;
        }
    }
    
    if (!airBattleHappens)
    {
        nextStatus(0);
        return;
    }
    
    showLeftCornerBar(hangkongzhan);
    battleHeros[fireCvIndex]->showCloseUp(1.2);
    showCloseUpBorder();
    
    
    AnimationMaker::playPlaneAnimation(this, 1.7);
    AnimationMaker::playAirBattleAnimation(this, 3.5);
    
    bool doubleHit=false,ci=false,special=false,miss=false,critical=false;
    int damage;
    
    model->getFireDamage(true, 1, 0, doubleHit, special, ci, damage, critical, miss);
    model->enemy[0]->getDamage(damage);
    battleEnemies[0]->receiveDamage(6.2, miss, critical, damage*3, 2);
    
    if (battleEnemies.size()>3)
    {
        model->getFireDamage(true, 1, 3, doubleHit, special, ci, damage, critical, miss);
        model->enemy[3]->getDamage(damage);
        battleEnemies[3]->receiveDamage(6.2, miss, critical, damage*2, 1);
    }
    
    if (battleEnemies.size()>5)
    {
        model->getFireDamage(true, 1, 5, doubleHit, special, ci, damage, critical, miss);
        model->enemy[5]->getDamage(damage);
        battleEnemies[3]->receiveDamage(6.2, miss, critical, damage*3, 2);
    }
    
    nextStatus(3.5+3);
    
    
}

void GameScene::showCloseUpBorder()
{
    closeUpBorder->setPosition(1200, -240);
    auto *fadeIn = FadeIn::create(0.1);
    auto *moveToCenter = MoveTo::create(0.2, Point(400, 190));
    auto *fadeOut = FadeOut::create(0.5);
    auto *seq = Sequence::create(DelayTime::create(1), fadeIn, moveToCenter, DelayTime::create(2), fadeOut, NULL);
    closeUpBorder->runAction(seq);
}


void GameScene::BattleStart()
{
    hideLeftCornerBar();
    startBorderUp = Sprite::create("interface/CommonAssets/image 472.png");
    startBorderDown = Sprite::create("interface/CommonAssets/image 470.png");
    startBorderDown->setPosition(400, 130);
    startBorderUp->setPosition(400, 330);
    this->addChild(startBorderDown);
    this->addChild(startBorderUp);
    auto *battleStart = Sprite::create("interface/BattleMain/BattleMain_51.png");
    battleStart->setPosition(400, 240);
    this->addChild(battleStart);
    
    //animation
    
    
    startBorderDown->runAction(CCMoveTo::create(1, Point(400, -100)));
    startBorderUp->runAction(CCMoveTo::create(1, Point(400, 580)));
    battleStart->runAction(CCFadeOut::create(0.6));
    battleStart->runAction(CCMoveTo::create(0.6, Point(360, 240)));
    
    nextStatus(1);
}
void GameScene::initFormation()
{
    myFormation= new Formation(model->allies.size(), model->alliesFormation);
    enemyFormation= new Formation(model->enemy.size(), model->enemyFormation, true);
    myFormation->addBattleBorder();
    enemyFormation->addBattleBorder();
    this->addChild(myFormation);
    this->addChild(enemyFormation);
    myFormation->setPosition(75, 90);
    enemyFormation->setPosition(715, 400);
    myFormation->setVisible(false);
    enemyFormation->setVisible(false);
    
}
void GameScene::initCharacters()
{
    if (nullptr != this->model)
    {
        std::vector<Kantai*> heros = model->allies;
        
        for (int i = 0; i < heros.size(); i++)
        {
            BattleHero *hero = BattleHero::create(heros[i], this, (i + 1));
            hero->setMaxHp(heros[i]->getMaxHp());
            battleHeros.push_back(hero);
            hero->setPosition(-160, 0);
            FiniteTimeAction *actionMoveOut = CCMoveTo::create(0.3, Point(0, 0));
            auto action = Sequence::create(CCDelayTime::create(0.1 * i), actionMoveOut, NULL);
            hero->runAction(action);
        }
        nextStatus(0.1 * heros.size() + 0.3 + 0.3);
        return;
    }
    //default
    
}
void GameScene::initEnemy()
{
    //enemy seen
    battleBar->openAndCloseAnimation(center, enemy_seen);
    enemyFormation->showPoints();
    if (nullptr != this->model)
    {
        std::vector<Kantai*> enemies = model->enemy;
        int fleetSize=model->enemy.size();
        for (int i = 0; i <fleetSize; i++)
        {
            BattleEnemy *enemy = BattleEnemy::create(enemies[i], this, (i + 1));
            enemy->setMaxHp(enemies[i]->getMaxHp());
            battleEnemies.push_back(enemy);
            enemy->apearAnimation();
        }
        nextStatus(0.1 * enemies.size() + 0.3 + 0.3);
        return;
    }
    
    
    nextStatus(1.5);
    
}

void GameScene::initLeftCornerBar()
{
    
    
    leftCornerBar = Sprite::create("interface/BattleMain/BattleMain_164.png");
    leftCornerBar->setPosition(128, 427);
    leftCornerBar->setZOrder(1);
    //leftCornerBar->setVisible(false);
    this->addChild(leftCornerBar);
    if (nightFight)
        leftCornerCircle = Sprite::create("interface/BattleMain/BattleMain_161.png");
    else
        leftCornerCircle = Sprite::create("interface/BattleMain/BattleMain_159.png");
    leftCornerCircle->setPosition(18, 427);
    leftCornerCircle->setZOrder(1);
    auto *circleAction = RotateBy::create(1, 90);
    auto *sequence = Sequence::create(circleAction, NULL);
    auto *repeat = RepeatForever::create((ActionInterval*)sequence);
    leftCornerCircle->runAction(repeat);
    this->addChild(leftCornerCircle);
}
void GameScene::hideLeftCornerBar()
{
    if (nullptr != leftCornerBar)
    {
        auto *fadeOut1 = FadeOut::create(0.3);
        leftCornerBar->runAction(fadeOut1);
    }
    if (nullptr != leftCornerCircle)
    {
        auto *fadeOut2 = FadeOut::create(0.3);
        leftCornerCircle->runAction(fadeOut2);
    }
    if (nullptr != leftCornerLable)
    {
        auto *fadeOut3 = FadeOut::create(0.3);
        leftCornerLable->runAction(fadeOut3);
    }
    
}

void GameScene::showLeftCornerBar(LeftCornerType type)
{
    if (nullptr != leftCornerBar)
    {
        auto *fadeIn1 = FadeIn::create(0.3);
        leftCornerBar->runAction(fadeIn1);
    }
    if (nullptr != leftCornerCircle)
    {
        auto *fadeIn2 = FadeIn::create(0.3);
        leftCornerCircle->runAction(fadeIn2);
    }
    if (nullptr != leftCornerLable)
    {
        this->cocos2d::Node::removeChild(leftCornerLable);
    }
    switch (type)
    {
        case GameScene::suodi:
            leftCornerLable = Sprite::create("interface/BattleMain/BattleMain_166.png");
            break;
        case GameScene::paojizhan:
            leftCornerLable = Sprite::create("interface/BattleMain/BattleMain_170.png");
            break;
        case GameScene::yezhan:
            leftCornerLable = Sprite::create("interface/BattleMain/BattleMain_188.png");
            break;
        case GameScene::hangkongzhan:
            leftCornerLable = Sprite::create("interface/BattleMain/BattleMain_168.png");
            break;
        case GameScene::lituopanding:
            leftCornerLable = Sprite::create("interface/BattleMain/BattleMain_174.png");
            break;
        default:
            break;
    }
    leftCornerLable->setZOrder(1);
    leftCornerLable->setPosition(40, 427);
    leftCornerLable->setAnchorPoint(ccp(0, 0.5));
    this->addChild(leftCornerLable);
    auto *fadeIn3 = FadeIn::create(0.3);
    leftCornerLable->runAction(fadeIn3);
    
    
    
}





void GameScene::scoutStart()
{
    //show formation
    initFormation();
    myFormation->setScale(0.001);
    myFormation->setVisible(true);
    myFormation->showPoints();
    
    enemyFormation->setScale(0.001);
    enemyFormation->setVisible(true);
    
    auto *myscaleUp = ScaleBy::create(0.5, 1000);
    auto *enemyscaleUp = ScaleBy::create(0.5, 1000);
    myFormation->runAction(myscaleUp);
    enemyFormation->runAction(enemyscaleUp);
    
    //scout start
    showLeftCornerBar(suodi);
    
    battleBar->openAndCloseAnimation(center, scout_start);
    auto action = Sequence::create(CCDelayTime::create(1), CallFunc::create(CC_CALLBACK_0(GameScene::doScout, this)), NULL);
    battleBar->runAction(action, center);
}



void GameScene::doScout()
{
    //slide
    auto *slide = Sprite::create("interface/BattleMain/BattleMain_66.png");
    slide->setPosition(400, 240);
    slide->setRotation(120);
    slide->setScaleY(0.5);
    FiniteTimeAction *scale = ScaleBy::create(0.8, 40, 1);
    FiniteTimeAction *fadeOut = FadeOut::create(0.5);
    auto actionSlide = Sequence::create(scale, CCDelayTime::create(2.5), fadeOut, NULL);
    this->addChild(slide);
    slide->runAction(actionSlide);
    
    //plane
    auto *plane = Sprite::create("interface/BattleMain/BattleMain_114.png");
    plane->setPosition(20, -20);
    this->addChild(plane);
    FiniteTimeAction *move = MoveTo::create(1.5, Point(880, 520));
    Sequence *planeAction = Sequence::create(CCDelayTime::create(0.75), move, CallFunc::create(CC_CALLBACK_0(GameScene::scoutResult, this)),NULL);
    plane->runAction(planeAction);
    
}
void GameScene::scoutResult()
{
    bool enemyFound = true;
    
    hideLeftCornerBar();
    
    if (enemyFound)
    {
        
        battleBar->openAndCloseAnimation(topleft, enemy_scouted);
        nextStatus(1.5);
        
        auto *statusUp = Sprite::create("interface/BattleMain/BattleMain_553.png");
        statusUp->setPosition(400, 330);
        statusUp->setZOrder(1);
        auto *moveLeft = MoveTo::create(0.2, Point(-400, 330));
        auto actionStatusUp = Sequence::create(CCDelayTime::create(1), moveLeft, NULL);
        
        this->addChild(statusUp);
        statusUp->runAction(actionStatusUp);
    }
    
    
}


