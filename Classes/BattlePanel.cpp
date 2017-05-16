//
//  BattlePanel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#include "BattlePanel.hpp"
#include "AnimationMaker.hpp"
#include "ViewMgr.hpp"
#include "SallyPanel.hpp"
#include "portScene.h"
#include "Sound.hpp"

#define DEBUG false

NS_KCL_BEGIN


#define BG_ZORDER        -1
#define FORMATION_ZORDER  3
#define SHELL_ZORDER      6
#define AVATAR_ZORDER     8
#define INTERFACE_ZORDER  10
#define BUTTON_ZORDER     12

BattlePanel* BattlePanel::create(BattleFleet* kantaiFleet,BattleFleet* enemyFleet,FormationType kantaiFormation,FormationType enemyFormation)
{
    BattlePanel* pRet=new BattlePanel;
    if (pRet&&pRet->init(kantaiFleet, enemyFleet, kantaiFormation, enemyFormation))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool BattlePanel::init(kancolle::BattleFleet *kantaiFleet, kancolle::BattleFleet *enemyFleet, kancolle::FormationType kantaiFormation, kancolle::FormationType enemyFormation)
{
    bool bRet=false;
    do
    {
        if (!Panel::init())  break;
        
        m_pBattleInfo=BattleInfo::create(kantaiFleet,enemyFleet,kantaiFormation,enemyFormation);
        
        m_pBattleBar=BattleBar::create();
        addChild(m_pBattleBar);
        m_bNightFight=false;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        
        Sprite *bgImg;
        if (!m_bNightFight)
            bgImg = Sprite::create("BattleMain/image 86.jpg");
        else
            bgImg = Sprite::create("BattleMain/image 87.jpg");
        bgImg->setPosition(400,240);
        addChild(bgImg,BG_ZORDER);
        
        closeUpBorder = Sprite::create("BattleMain/image 303.png");
        this->addChild(closeUpBorder,INTERFACE_ZORDER);
        closeUpBorder->setZOrder(1);
        closeUpBorder->setOpacity(0);
        
        temptimer = Sprite::create("BattleMain/image 478.png");
        this->addChild(temptimer);
        InitLeftCornerBar();
        
        if (DEBUG)
        {
//            std::vector<CharacterInfo*> heros = model->getAllies();
//            for (int i = 0; i < heros.size(); i++)
//            {
//                BattleHero *hero = BattleHero::create(heros[i], this, (i + 1));
//                hero->setMaxHp(heros[i]->maxHP);
//                battleHeros.push_back(hero);
//            }
//            std::vector<CharacterInfo*> enemies = model->getEnemies();
//            for (int i = 0; i < enemies.size(); i++)
//            {
//                BattleEnemy *enemy = BattleEnemy::create(enemies[i], this, (i + 1));
//                enemy->setMaxHp(enemies[i]->maxHP);
//                battleEnemies.push_back(enemy);
//            }
//            //status = BattleStatus::firebattle;
//            fireBattle();
//            //BattleStart();
        }
        else
        {
            status = start;
            BattleStart();
        }
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}



BattlePanel* BattlePanel::create()
{
    BattlePanel* pRet=new BattlePanel;
    if (pRet&&pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return NULL;
}


bool BattlePanel::init()
{
    bool bRet=false;
    do
    {
        if (!Panel::init())  break;
        
        leftCornerLable=NULL;
        m_pBattleInfo=NULL;
        m_pBattleBar=BattleBar::create();
        addChild(m_pBattleBar);
        m_bNightFight=false;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        
        Sprite *bgImg;
        if (!m_bNightFight)
            bgImg = Sprite::create("BattleMain/image 86.jpg");
        else
            bgImg = Sprite::create("BattleMain/image 87.jpg");
        bgImg->setPosition(400,240);
        addChild(bgImg);
        
        closeUpBorder = Sprite::create("BattleMain/image 303.png");
        this->addChild(closeUpBorder);
        closeUpBorder->setZOrder(1);
        closeUpBorder->setOpacity(0);
        
        temptimer = Sprite::create("BattleMain/image 478.png");
        this->addChild(temptimer);
        InitLeftCornerBar();
        
        if (DEBUG)
        {
            //            std::vector<CharacterInfo*> heros = model->getAllies();
            //            for (int i = 0; i < heros.size(); i++)
            //            {
            //                BattleHero *hero = BattleHero::create(heros[i], this, (i + 1));
            //                hero->setMaxHp(heros[i]->maxHP);
            //                battleHeros.push_back(hero);
            //            }
            //            std::vector<CharacterInfo*> enemies = model->getEnemies();
            //            for (int i = 0; i < enemies.size(); i++)
            //            {
            //                BattleEnemy *enemy = BattleEnemy::create(enemies[i], this, (i + 1));
            //                enemy->setMaxHp(enemies[i]->maxHP);
            //                battleEnemies.push_back(enemy);
            //            }
            //            //status = BattleStatus::firebattle;
            //            fireBattle();
            //            //BattleStart();
        }
        else
        {
            status = start;
            BattleStart();
        }
        
        bRet=true;
    }while(0);
    
    
    return bRet;
}





void BattlePanel::InitLeftCornerBar()
{
    leftCornerBar=Sprite::create("BattleMain/image 164.png");
    leftCornerBar->setPosition(128, 427);
    //leftCornerBar->setVisible(false);
    this->addChild(leftCornerBar,FORMATION_ZORDER);
    if (m_bNightFight)
        leftCornerCircle = Sprite::create("BattleMain/image 161.png");
    else
        leftCornerCircle = Sprite::create("BattleMain/image 159.png");
    leftCornerCircle->setPosition(18, 427);
    //leftCornerCircle->setZOrder(1);
    auto *circleAction = RotateBy::create(1, 90);
    auto *sequence = Sequence::create(circleAction, NULL);
    auto *repeat = RepeatForever::create((ActionInterval*)sequence);
    leftCornerCircle->runAction(repeat);
    this->addChild(leftCornerCircle,FORMATION_ZORDER);
    
    
}


void BattlePanel::InitFormation()
{
    
    m_pKantaiFormation=Formation::create(m_pBattleInfo->GetKantaiFormation(),false);
    m_pKantaiFormation->AddBattleBorder();
    addChild(m_pKantaiFormation,FORMATION_ZORDER);
    m_pKantaiFormation->setPosition(75, 90);
    m_pKantaiFormation->setVisible(false);
    
    m_pEnemyFormation=Formation::create(m_pBattleInfo->GetEnemyFormation(),false);
    m_pEnemyFormation->AddBattleBorder();
    addChild(m_pEnemyFormation,FORMATION_ZORDER);
    m_pEnemyFormation->setPosition(715, 400);
    m_pEnemyFormation->setVisible(false);
    
}


//
//BattlePanel::BattlePanel(BattleModel *model)
//{
//    
//    this->model = model;
//    battleBar = new BattleBar(this);
//    leftCornerLable = nullptr;
//    nightFight = false;
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Sprite *bgImg;
//    if (!nightFight)
//        bgImg = Sprite::create("BattleMain/image 86.jpg");
//    else
//        bgImg = Sprite::create("BattleMain/image 87.jpg");
//    
//    bgImg->setPosition(400,240);
//    this->addChild(bgImg);
//    
//    closeUpBorder = Sprite::create("BattleMain/image 303.png");
//    this->addChild(closeUpBorder);
//    closeUpBorder->setZOrder(1);
//    closeUpBorder->setOpacity(0);
//    
//    temptimer = Sprite::create("BattleMain/image 478.png");
//    this->addChild(temptimer);
//    initLeftCornerBar();
//    
//    
//    
//    //debug
//    if (DEBUG)
//    {
//        std::vector<CharacterInfo*> heros = model->getAllies();
//        for (int i = 0; i < heros.size(); i++)
//        {
//            BattleHero *hero = BattleHero::create(heros[i], this, (i + 1));
//            hero->setMaxHp(heros[i]->maxHP);
//            battleHeros.push_back(hero);
//        }
//        std::vector<CharacterInfo*> enemies = model->getEnemies();
//        for (int i = 0; i < enemies.size(); i++)
//        {
//            BattleEnemy *enemy = BattleEnemy::create(enemies[i], this, (i + 1));
//            enemy->setMaxHp(enemies[i]->maxHP);
//            battleEnemies.push_back(enemy);
//        }
//        //status = BattleStatus::firebattle;
//        fireBattle();
//        //BattleStart();
//        
//    }
//    else
//    {
//        status = start;
//        BattleStart();
//    }
//    
//}
void BattlePanel::NextStatus(float DelayTime)
{
    auto callFunc = CallFunc::create(CC_CALLBACK_0(BattlePanel::onStatusOverCallBack, this));
    auto *seq = Sequence::create(DelayTime::create(DelayTime), callFunc, NULL);
    temptimer->runAction(seq);
    
    
}
void BattlePanel::onStatusOverCallBack(){
    if (status == BattleStatus::start)
    {
        status = BattleStatus::character;
        InitCharacters();
    }
    else if (status == BattleStatus::character)
    {
        status = BattleStatus::scouting;
        ScoutStart();
    }
    else if (status == BattleStatus::scouting)
    {
        status = BattleStatus::enemy;
        InitEnemy();
    }
    else if (status == BattleStatus::enemy)
    {
        status = BattleStatus::airbattle;
        AirBattle();
    }
    else if (status == BattleStatus::airbattle)
    {
        status = BattleStatus::firebattle;
        fireBattle();
    }
    else if (status == BattleStatus::firebattle)
    {
        status = BattleStatus::dayEnd;
        DayEnd();
    }
    else
    {
        EndBattle();
    }
    
}




void BattlePanel::BattleStart()
{
    HideLeftCornerBar();
    startBorderUp = Sprite::create("CommonAssets/image 472.png");
    startBorderDown = Sprite::create("CommonAssets/image 470.png");
    startBorderDown->setPosition(400, 130);
    startBorderUp->setPosition(400, 330);
    this->addChild(startBorderDown,INTERFACE_ZORDER);
    this->addChild(startBorderUp,INTERFACE_ZORDER);
    
    auto *battleStart = Sprite::create("BattleMain/image 51.png");
    battleStart->setPosition(400, 240);
    this->addChild(battleStart,INTERFACE_ZORDER);
    
    //animation
    startBorderDown->runAction(MoveTo::create(1, Point(400, -100)));
    startBorderUp->runAction(MoveTo::create(1, Point(400, 580)));
    battleStart->runAction(FadeOut::create(0.6));
    battleStart->runAction(MoveTo::create(0.6, Point(360, 240)));
    
    NextStatus(1);
}

void BattlePanel::InitCharacters()
{
    if (m_pBattleInfo)
    {
        BattleFleet* kantaiFleet= m_pBattleInfo->GetKantais();
        std::vector<BattleCharacterInfo*> vBattleKantai=kantaiFleet->m_vBattleShip;
        
        int countKantai=0;
        for (int i = 0; i < vBattleKantai.size(); i++)
        {
            BattleCharacterInfo* kantaiInfo=vBattleKantai[i];
            if (kantaiInfo)
            {
                BattleKantai *kantai = BattleKantai::create(kantaiInfo,(i + 1));
                kantai->SetMaxHp(kantaiInfo->getMaxHp());
                m_vBattleKantais.push_back(kantai);
                kantai->setPosition(-160, 0);
                CCFiniteTimeAction *actionMoveOut = MoveTo::create(0.3, Point(0, 0));
                auto action = Sequence::create(DelayTime::create(0.1 * i), actionMoveOut, NULL);
                kantai->runAction(action);
                ++countKantai;
                addChild(kantai,AVATAR_ZORDER);
            }

        }
        NextStatus(0.1 * countKantai + 0.3 + 0.3);
        return;
    }
    //default
    
}
void BattlePanel::InitEnemy()
{
    //enemy seen
    m_pBattleBar->openAndCloseAnimation(center, enemy_seen);
    m_pEnemyFormation->ShowPoints();
    if (m_pBattleInfo)
    {
        BattleFleet* enemyFleet= m_pBattleInfo->getEnemies();
        std::vector<BattleCharacterInfo*> vBattleEnemy=enemyFleet->m_vBattleShip;
        m_vBattleEnemies.resize(vBattleEnemy.size());
        for (int i=0; i<m_vBattleEnemies.size(); ++i)
        {
            m_vBattleEnemies[i]=NULL;
        }
        
        int countEnemy=0;
        for (int i = 0; i < vBattleEnemy.size(); i++)
        {
            BattleCharacterInfo* enemyInfo=vBattleEnemy[i];
            if (enemyInfo)
            {
                //TODO
                BattleEnemy *enemy = BattleEnemy::create(enemyInfo,(i + 1));
//                enemy->SetMaxHp(enemyInfo->getMaxHp());
//                enemy->SetCurrentHp(enemyInfo->getCurrHp());
                m_vBattleEnemies[i]=enemy;
                addChild(enemy,AVATAR_ZORDER);
                //enemy->ApearAnimation();
                
            }

            ++countEnemy;
        }
        NextStatus(0.1 * countEnemy + 0.3 + 0.3);
        return;
    }
    
    
    NextStatus(1.5);
    
}


void BattlePanel::HideLeftCornerBar()
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
void BattlePanel::ShowLeftCornerBar(LeftCornerType type)
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
        // delete leftCornerLable;
    }
    switch (type)
    {
        case BattlePanel::suodi:
            leftCornerLable = Sprite::create("BattleMain/image 166.png");
            break;
        case BattlePanel::paojizhan:
            leftCornerLable = Sprite::create("BattleMain/image 170.png");
            break;
        case BattlePanel::yezhan:
            leftCornerLable = Sprite::create("BattleMain/image 188.png");
            break;
        case BattlePanel::hangkongzhan:
            leftCornerLable = Sprite::create("BattleMain/image 168.png");
            break;
        case BattlePanel::lituopanding:
            leftCornerLable = Sprite::create("BattleMain/image 174.png");
            break;
        default:
            break;
    }
    leftCornerLable->setPosition(40, 427);
    leftCornerLable->setAnchorPoint(ccp(0, 0.5));
    this->addChild(leftCornerLable,FORMATION_ZORDER);
    auto *fadeIn3 = FadeIn::create(0.3);
    leftCornerLable->runAction(fadeIn3);
    
    
    
}

void BattlePanel::ShowCloseUpBorder()
{
    closeUpBorder->setPosition(1200, -240);
    auto *fadeIn = FadeIn::create(0.1);
    auto *moveToCenter = MoveTo::create(0.2, Point(400, 190));
    auto *fadeOut = FadeOut::create(0.5);
    auto *seq = Sequence::create(DelayTime::create(1), fadeIn, moveToCenter, DelayTime::create(2), fadeOut, NULL);
    closeUpBorder->runAction(seq);
}
void BattlePanel::ScoutStart()
{
    //show formation
    InitFormation();
    m_pKantaiFormation->setScale(0.001);
    m_pKantaiFormation->setVisible(true);
    m_pKantaiFormation->ShowPoints();
    
    m_pEnemyFormation->setScale(0.001);
    m_pEnemyFormation->setVisible(true);
    
    auto *myscaleUp = ScaleBy::create(0.5, 1000);
    auto *enemyscaleUp = ScaleBy::create(0.5, 1000);
    m_pKantaiFormation->runAction(myscaleUp);
    m_pEnemyFormation->runAction(enemyscaleUp);
    
    
    //scout start
    ShowLeftCornerBar(suodi);
    
    m_pBattleBar->openAndCloseAnimation(center, scout_start);
    auto action = Sequence::create(CCDelayTime::create(1), CallFunc::create(CC_CALLBACK_0(BattlePanel::DoScout, this)), NULL);
    m_pBattleBar->runAction(action, center);
}



void BattlePanel::DoScout()
{
    //slide
    auto *slide = Sprite::create("BattleMain/image 66.png");
    slide->setPosition(400, 240);
    slide->setRotation(120);
    slide->setScaleY(0.5);
    FiniteTimeAction *scale = ScaleBy::create(0.8, 40, 1);
    FiniteTimeAction *fadeOut = FadeOut::create(0.5);
    auto actionSlide = Sequence::create(scale, CCDelayTime::create(2.5), fadeOut, NULL);
    this->addChild(slide,SHELL_ZORDER);
    slide->runAction(actionSlide);
    
    //plane
    auto *plane = Sprite::create("BattleMain/image 114.png");
    plane->setPosition(20, -20);
    this->addChild(plane,SHELL_ZORDER);
    function<void()> soundOpen=[](){SND->playEffect("sound_se/sound 37.mp3");};
    CallFunc* soundCallfunc=CallFunc::create(soundOpen);
    FiniteTimeAction *move = MoveTo::create(1.5, Point(880, 520));
    Sequence *planeAction = Sequence::create(CCDelayTime::create(0.75),soundCallfunc, move, CallFunc::create(CC_CALLBACK_0(BattlePanel::ScoutResult, this)),NULL);
    plane->runAction(planeAction);
    
}
void BattlePanel::ScoutResult()
{
    bool enemyFound = true;
    
    HideLeftCornerBar();
    
    if (enemyFound)
    {
        
        m_pBattleBar->openAndCloseAnimation(topleft, enemy_scouted);
        NextStatus(1.5);
        
        auto *statusUp = Sprite::create("BattleMain/image 515.png");
        statusUp->setPosition(400, 330);
        this->addChild(statusUp,INTERFACE_ZORDER);
        
        auto *moveLeft = MoveTo::create(0.2, Point(-400, 330));
        function<void()> soundOpen=[](){SND->playEffect("sound_se/sound 38.mp3");};
        CallFunc* soundCallfunc=CallFunc::create(soundOpen);
        auto actionStatusUp = Sequence::create(CCDelayTime::create(1),soundCallfunc, moveLeft, NULL);
        statusUp->runAction(actionStatusUp);
    }
    
    
}
void BattlePanel::AirBattle()
{
    
    //judge if air battle happens
    
    bool airBattleHappens = false;
    int firstCVindex;
    
    BattleFleet*   kantaiFleet=m_pBattleInfo->GetKantais();
    std::vector<BattleCharacterInfo*> vKantai=kantaiFleet->m_vBattleShip;
    
    for (int i = vKantai.size()-1; i >=0; i--)
    {
        if (vKantai[i]&&vKantai[i]->CanAirBattle())
        {
            firstCVindex = i;
            airBattleHappens = true;
        }
        
    }
    
    if (airBattleHappens == false)
    {
        NextStatus(0);
        return;
    }
    
    
    //do air battle
    ShowLeftCornerBar(hangkongzhan);
    m_vBattleKantais[firstCVindex]->ShowCloseUp(1.2);
    ShowCloseUpBorder();
    //plane anime
    AnimationMaker::playPlaneAnimation(1.7);
    AnimationMaker::playAirBattleAnimation(3.5);
    
    //TODO damage
    bool doubleHit = false, ci = false, special = false, miss = false, critical = false;
    int damage;
    m_pBattleInfo->GetFireDamage(true, 1, 0, doubleHit, special, ci, damage, critical, miss);
    BattleCharacterInfo* enemyDamgae=m_pBattleInfo->getEnemies()->m_vBattleShip[0];
    enemyDamgae->GetDamage(damage);
    m_vBattleEnemies[0]->ReceiveDamage(6.2, miss, critical, damage*3, 2);
    
    if (BattleEnemiesSize() > 3){
        m_pBattleInfo->GetFireDamage(true, 1, 3, doubleHit, special, ci, damage, critical, miss);
        BattleCharacterInfo* enemyDamgae=m_pBattleInfo->getEnemies()->m_vBattleShip[3];
        enemyDamgae->GetDamage(damage);
        m_vBattleEnemies[3]->ReceiveDamage(6.2, miss, critical, damage * 2, 1);
    }
    
    if (BattleEnemiesSize() > 5){
        m_pBattleInfo->GetFireDamage(true, 1, 5, doubleHit, special, ci, damage, critical, miss);
        BattleCharacterInfo* enemyDamgae=m_pBattleInfo->getEnemies()->m_vBattleShip[5];
        enemyDamgae->GetDamage(damage);
        m_vBattleEnemies[5]->ReceiveDamage(6.2, miss, critical, damage * 3, 2);
    }
    
    NextStatus(3.5 + 3);
    
}

void BattlePanel::EndBattle()
{
    if (SALLY_MGR->IfEndSally())
    {
        auto scene=dynamic_cast<PortScene*>(VIEW_MGR->showScene(SceneType::HOME));
        scene->SetCurrPanel(PanelType::PORT_MAINLAYER);
    }
    else
    {
        VIEW_MGR->showScene(SceneType::SALLY);
        SallyPanel* sallyPanel=dynamic_cast<SallyPanel*>(VIEW_MGR->showPanel(PanelType::SALLY_MAIN));
        sallyPanel->SetMission();
    }
}



int BattlePanel::BattleKantaiSize()
{
    int total=0;
    for (int i=0; i<m_vBattleKantais.size(); ++i)
    {
        if (m_vBattleKantais[i])
        {
            ++total;
        }
    }
    return total;
}

int BattlePanel::BattleEnemiesSize()
{
    int total=0;
    for (int i=0; i<m_vBattleEnemies.size(); ++i)
    {
        if (m_vBattleEnemies[i])
        {
            ++total;
        }
    }
    return total;
}




void BattlePanel::fireBattle()
{
    ShowLeftCornerBar(paojizhan);
    
    //First Round
    float timePassed = 1;
    
    
    float delay1 = 0.5, delay2 = 1, delay3 = 1;
    
    bool doubleHit = false, ci = false, special = false, miss = false, critical = false;
    int damage = 10;
    
    m_pBattleInfo->ResetFireBattle();
    bool fire=false, allieAttack=false;int index;
    
    fire = m_pBattleInfo->GetNextIndexToFire(allieAttack, index);
    while (fire)
    {
        
        if (allieAttack &&(m_pBattleInfo->GetKantais()->m_vBattleShip)[index]->CanAttack())
        {
            int targetIndex=m_pBattleInfo->GetTargetIndex(allieAttack);
            if (targetIndex == -1){
                NextStatus(timePassed + 2);
                return;//WIN
            }
            m_vBattleKantais[index]->StepOut(timePassed);
            delay1 = m_vBattleKantais[index]->ShowAttackingAnime(timePassed) - 0.35;
            delay2 = delay1 + 0.5;
            delay3 = delay1 + 1.5;
            
            
            BattleEnemy* _enemy=m_vBattleEnemies[targetIndex];
            _enemy->StepOut(timePassed);
            m_pBattleInfo->GetFireDamage(allieAttack, index, targetIndex, doubleHit, special, ci, damage, critical, miss);
            if (!miss)
                m_pBattleInfo->getEnemies()->m_vBattleShip[targetIndex]->GetDamage(damage);
            m_vBattleEnemies[targetIndex]->ReceiveDamage(timePassed + delay1, miss, critical, damage, 1);
            m_vBattleEnemies[targetIndex]->StepBack(timePassed + delay1);
            m_vBattleKantais[index]->StepBack(timePassed + delay2);
            timePassed += delay3;
        }
        else if (!allieAttack&&m_pBattleInfo->getEnemies()->m_vBattleShip[index]->CanAttack())
        {
            int targetIndex = m_pBattleInfo->GetTargetIndex(allieAttack);
            if (targetIndex == -1){
                NextStatus(timePassed + 2);
                return; //GAMEOVER
            }
            m_vBattleEnemies[index]->StepOut(timePassed);
            delay1 = m_vBattleEnemies[index]->ShowAttackingAnime(timePassed) - 0.35;
            delay2 = delay1 + 0.5;
            delay3 = delay1 + 1.5;
            
            m_vBattleKantais[targetIndex]->StepOut(timePassed);
            m_pBattleInfo->GetFireDamage(allieAttack, targetIndex, index, doubleHit, special, ci, damage, critical, miss);
            if (!miss)
                m_pBattleInfo->GetKantais()->m_vBattleShip[targetIndex]->GetDamage(damage);
            m_vBattleKantais[targetIndex]->ReceiveDamage(timePassed + delay1, miss, critical, damage, 1);
            m_vBattleKantais[targetIndex]->StepBack(timePassed + delay1);
            m_vBattleEnemies[index]->StepBack(timePassed + delay2);
            timePassed += delay3;
        }
        fire = m_pBattleInfo->GetNextIndexToFire(allieAttack, index);
        
    }
    
    timePassed += 2.3;
    //Second Round
    
    //if BB exists, do second round
    bool doSecondRound = false;
    for (int i = 0; i < m_pBattleInfo->GetKantais()->m_vBattleShip.size(); i++)
    {
        BattleCharacterInfo* info=m_pBattleInfo->GetKantais()->m_vBattleShip[i];
        if (info&&
            (info->getKantaiType()==KantaiType::Battleship||
             info->getKantaiType()==KantaiType::Battle_Carrier))
             doSecondRound = true;
    }
    
    for (int i = 0; i < m_pBattleInfo->getEnemies()->m_vBattleShip.size(); i++)
    {
        BattleCharacterInfo* info=m_pBattleInfo->getEnemies()->m_vBattleShip[i];
        if (info&&
            (info->getKantaiType()==KantaiType::Battleship||
             info->getKantaiType()==KantaiType::Battle_Carrier))
            doSecondRound = true;
    }
    
    
    if (false)
    {
        
        for (int i = 0; i < MAX_SHIPS_PER_FLEET; i++)
        {
            index = i;
            for (int j=index;j<MAX_SHIPS_PER_FLEET; ++j)
            {
                index=j;
                if (m_pBattleInfo->GetKantais()->m_vBattleShip[i]&&
                    m_pBattleInfo->GetKantais()->m_vBattleShip[i]->CanAttack())
                {
                    break;
                }
            }
//            while (!m_pBattleInfo->getAllies()
//                   [index]->canAttack() && index < (model->getAllies().size()-1))
//                index++;
            if (m_pBattleInfo->GetKantais()->m_vBattleShip[index]->CanAttack())
            {
                m_vBattleKantais[index]->StepOut(timePassed);
                delay1 = m_vBattleKantais[index]->ShowAttackingAnime(timePassed) - 0.35;
                delay2 = delay1 + 0.5;
                delay3 = delay1 + 1.5;
                int targetIndex = m_pBattleInfo->GetTargetIndex(allieAttack);
                m_vBattleEnemies[targetIndex]->StepOut(timePassed);
                m_pBattleInfo->GetFireDamage(allieAttack, index, targetIndex, doubleHit, special, ci, damage, critical, miss);
                if (!miss)
                    m_pBattleInfo->getEnemies()->m_vBattleShip[targetIndex]->GetDamage(damage);
                m_vBattleEnemies[targetIndex]->ReceiveDamage(timePassed + delay1, miss, critical, damage, 1);
                m_vBattleEnemies[targetIndex]->StepBack(timePassed + delay1);
                m_vBattleKantais[index]->StepBack(timePassed + delay2);
                timePassed += delay3;
            }
            index = i;
            for (int j=index;j<MAX_SHIPS_PER_FLEET; ++j)
            {
                index=j;
                if (m_pBattleInfo->getEnemies()->m_vBattleShip[i]&&
                    m_pBattleInfo->getEnemies()->m_vBattleShip[i]->CanAttack())
                {
                    break;
                }
            }
//            while (!model->getEnemies()[index]->canAttack() && index < (model->getEnemies().size() - 1))
//                index++;
            if (m_pBattleInfo->getEnemies()->m_vBattleShip[index]->CanAttack())
            {
                m_vBattleEnemies[index]->StepOut(timePassed);
                delay1 = m_vBattleEnemies[index]->ShowAttackingAnime(timePassed) - 0.35;
                delay2 = delay1 + 0.5;
                delay3 = delay1 + 1.5;
                int targetIndex = m_pBattleInfo->GetTargetIndex(allieAttack);
                m_vBattleKantais[targetIndex]->StepOut(timePassed);
                m_pBattleInfo->GetFireDamage(allieAttack, targetIndex, index, doubleHit, special, ci, damage, critical, miss);
                if (!miss)
                    m_pBattleInfo->GetKantais()->m_vBattleShip[targetIndex]->GetDamage(damage);
                m_vBattleKantais[targetIndex]->ReceiveDamage(timePassed + delay1, miss, critical, damage, 1);
                m_vBattleKantais[targetIndex]->StepBack(timePassed + delay1);
                m_vBattleEnemies[index]->StepBack(timePassed + delay2);
                timePassed += delay3;
            }
        }
    }
    
    NextStatus(timePassed);
    
}

void BattlePanel::DayEnd()
{
    ShowLeftCornerBar(lituopanding);
    SND->playEffect("sound_se/sound 38.mp3");
    startBorderUp->setTexture("CommonAssets/image 473.png");
    startBorderDown->setTexture("CommonAssets/image 471.png");
    startBorderUp->runAction(MoveTo::create(1, ccp(400, 352)));
    startBorderDown->runAction(MoveTo::create(1, ccp(400, 130)));
    startBorderDown->setScaleY(1.05);
    startBorderUp->setScaleY(1.05);
    
//    auto escape = MenuItemImage::create("BattleMain/image 2.png","BattleMain/image 9.png");
//    auto nightBattle = MenuItemImage::create("BattleMain/image 12.png", "BattleMain/image 14.png");
//    escape->setPosition(300, 240);
//    nightBattle->setPosition(500, 240);
//    escape->setOpacity(0);
//    nightBattle->setOpacity(0);
//    escape->runAction(Sequence::create(DelayTime::create(0.8), FadeIn::create(0.5), NULL));
//    nightBattle->runAction(Sequence::create(DelayTime::create(0.8), FadeIn::create(0.5), NULL));
//    auto menu = Menu::create(escape, nightBattle,NULL);
//    this->addChild(menu,BUTTON_ZORDER);
//    menu->setPosition(Point::ZERO);
    
    NextStatus(5);
}

void BattlePanel::SetInfo(kancolle::BattleFleet *kantaiFleet, kancolle::BattleFleet *enemyFleet, kancolle::FormationType kantaiFormation, kancolle::FormationType enemyFormation)
{
    m_pBattleInfo=BattleInfo::create(kantaiFleet, enemyFleet, kantaiFormation, enemyFormation);
}




NS_KCL_END

