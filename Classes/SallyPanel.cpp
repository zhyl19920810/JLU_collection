//
//  SallyPanel.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "SallyPanel.hpp"
#include "ViewMgr.hpp"
#include "portScene.h"


NS_KCL_BEGIN



#define BG_ZORDER -1
#define _ZORDER 0



bool SallyPanel::init()
{
    bool bRet=false;
    do
    {
        m_SallyInfo=SallyInfo::create();
        InitBg();
        
        bRet=true;
    }while(0);
    
    return bRet;
}

SallyPanel::~SallyPanel()
{
    
}


void SallyPanel::InitBg()
{
    
    /*showingBottomPanel = false;*/
    bgImg = Sprite::create("SallyMain/image 1.jpg");
    bgImg->setPosition(400, 240);
    bgImg->setOpacity(0);
    addChild(bgImg);

    sallyMap=Sprite::create();
    addChild(sallyMap);
    sallyMap->setPosition(400, 240);
    sallyMap->setOpacity(0);
    
    m_pSallyShip=SallyShip::create();
    m_pSallyShip->setZOrder(1);
    m_pSallyShip->setVisible(false);
    addChild(m_pSallyShip);
    
    
    m_pFlagShip=FlagShip::create();
    addChild(m_pFlagShip);
    m_pFlagShip->setPosition(-300, 150);
    m_pFlagShip->setZOrder(2);
    
    
    m_pBottomBorder = Sprite::create("SallyMain/image 935.png");
    m_pBottomBorder->setPosition(400, -250);
    m_pBottomBorder->setZOrder(3);
    this->addChild(m_pBottomBorder);
    
    m_pCompass=Compass::create();
    addChild(m_pCompass);
    m_pCompass->setZOrder(3);
    m_pCompass->setPosition(40, -260);
    m_pCompass->setRotation(45);
    
    m_pBottomLabel=Label::create();
    m_pBottomLabel->setZOrder(3);
    addChild(m_pBottomLabel);
    temptimer = Sprite::create("BattleMain/image 478.png");
    addChild(temptimer);
    
    m_pNodePointShader = Sprite::create();
    addChild(m_pNodePointShader);
    
    m_pFormationSelecter=FormationSelecter::create();
    addChild(m_pFormationSelecter);
    
    SallyStart();
}

void SallyPanel::SallyFormation()
{
    m_pFlagShip->runAction(MoveTo::create(0.5, ccp(100, 150)));
    m_pFormationSelecter->ShowSelecter();
}



void SallyPanel::NextStatus(float DelayTime)
{
    auto callFunc = CallFunc::create(CC_CALLBACK_0(SallyPanel::OnStatusOverCallBack, this));
    auto *seq = Sequence::create(DelayTime::create(DelayTime), callFunc, NULL);
    temptimer->runAction(seq);
}


void SallyPanel::SallyStart()
{
    
    auto slide = Sprite::create("SallyMain/image 611.png");
    auto start = Sprite::create("SallyMain/image 614.png");
    auto startShader = Sprite::create("SallyMain/image 614.png");
    slide->setPosition(1200, 240);
    start->setPosition(400, 240);
    start->setOpacity(0);
    startShader->setOpacity(0);
    startShader->setScale(1.15);
    startShader->setPosition(400, 240);
    this->addChild(slide);
    this->addChild(start);
    this->addChild(startShader);
    
    
    
    //animation
    slide->runAction(Sequence::create(MoveTo::create(0.3, ccp(400, 240)), DelayTime::create(1.3), FadeOut::create(0.3),NULL));
    start->runAction(Sequence::create(DelayTime::create(0.3), FadeIn::create(0.3),DelayTime::create(1),FadeOut::create(0.3), NULL));
    startShader->runAction(Sequence::create(DelayTime::create(0.3), FadeIn::create(0.3), ScaleTo::create(0.1, 1), DelayTime::create(1), FadeOut::create(0.3), NULL));
    bgImg->runAction(Sequence::create(DelayTime::create(1.6), FadeIn::create(0.3),NULL));
    sallyMap->runAction(Sequence::create(DelayTime::create(1.6), FadeIn::create(0.3), NULL));
    
    NextStatus(1.9);
}

void SallyPanel::SallyMove()
{
    ShowBottomPanel();
    
    MissionNode* curMissionNode=m_SallyInfo->m_CurMissonNode;
    bool needRollCompass=false;
    float timepassed = 0;
    m_pSallyShip->setVisible(true);
    m_pSallyShip->setPosition(curMissionNode->position);
    
    MissionNode* nextNode;
    if (curMissionNode->m_vChildren.size() == 0)
    {
        SallyFinish();
        return;
    }
    else if (curMissionNode->m_vChildren.size() == 1)
    {
        nextNode = curMissionNode->m_vChildren[0];
    }
    else //currentMissionNode->children.size() > 1
    {
        needRollCompass = true;
        nextNode = curMissionNode->m_vChildren[1];
    }
    
    
    timepassed += 2;
    m_pSallyShip->runAction(Sequence::create(DelayTime::create(timepassed),MoveTo::create(1, nextNode->position),NULL));
    timepassed += 1;
    
    
    //point animation
    auto nodePoint = Sprite::create();
    nodePoint->setPosition(nextNode->position);
    nodePoint->setOpacity(0);
    nodePoint->runAction(Sequence::create(DelayTime::create(timepassed),FadeIn::create(0.5),NULL));
    this->addChild(nodePoint);
    
    
    
    m_pNodePointShader->setPosition(nextNode->position);
    m_pNodePointShader->setOpacity(0);
    m_pNodePointShader->runAction(Sequence::create(DelayTime::create(timepassed), FadeIn::create(0.5), NULL));
    m_pNodePointShader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(ScaleTo::create(1.2, 2), ScaleTo::create(0.01, 1), ScaleTo::create(1.2, 2), ScaleTo::create(0.01, 1)
                                                                                       , NULL)));
    timepassed += 2.4;
    
    
    
    switch (nextNode->m_type)
    {
        case NODE_BOSS:
            nodePoint->setTexture("SallyMain/image 867.png");
            m_pNodePointShader->setTexture("SallyMain/image 867.png");
            break;
        case NODE_ENEMY:
            nodePoint->setTexture("SallyMain/image 861.png");
            m_pNodePointShader->setTexture("RemodelMain/image 1.png");
            break;
        case NODE_ITEM:
            nodePoint->setTexture("SallyMain/image 857.png");
            break;
        case NODE_EMPTY:
            nodePoint->setTexture("SallyMain/image 855.png");
            break;
        case NODE_DISASTER:
            nodePoint->setTexture("SallyMain/image 859.png");
            break;
        default:
            break;
    }
    if (nextNode->m_type == NODE_BOSS || nextNode->m_type == NODE_ENEMY)
    {
        m_SallyInfo->m_Status = SALLY_FORMATION;
        m_SallyInfo->m_CurMissonNode = nextNode;
        NextStatus(timepassed);
    }
    
}

void SallyPanel::SallyBattle()
{
    
}
void SallyPanel::SallyFinish()
{
    auto scene=dynamic_cast<PortScene*>(VIEW_MGR->showScene(SceneType::HOME));
    scene->SetCurrPanel(PanelType::PORT_MAINLAYER);
    
    //Director::getInstance()->replaceScene(PortScene::createScene());
}


void SallyPanel::OnStatusOverCallBack()
{
    if (m_SallyInfo->m_Status == SallyStatus::SALLY_START)
    {
        m_SallyInfo->m_Status = SALLY_MOVE;
        SallyMove();
    }
    else if (m_SallyInfo->m_Status == SallyStatus::SALLY_BATTLE)
    {
        SallyBattle();
    }
    else if (m_SallyInfo->m_Status == SallyStatus::SALLY_FORMATION)
    {
        SallyFormation();
    }
}




void SallyPanel::HideBottomPanel()
{
    if (!m_bShowingBottomPanel)
        return;
    m_pBottomBorder->runAction(MoveBy::create(1, ccp(0, -300)));
    m_pCompass->runAction(MoveBy::create(1, ccp(0, -300)));
    m_pBottomLabel->runAction(MoveBy::create(1, ccp(0, -300)));
    m_bShowingBottomPanel = false;
}



void SallyPanel::ShowBottomPanel()
{
    if (m_bShowingBottomPanel)
        return;
    m_pBottomBorder->runAction(MoveBy::create(1, ccp(0, 300)));
    m_pCompass->runAction(MoveBy::create(1, ccp(0, 300)));
    m_pBottomLabel->runAction(MoveBy::create(1, ccp(0, 300)));
    m_bShowingBottomPanel = true;
}


void SallyPanel::SetFormationCallback(Ref* pSender, FormationType formation)
{
    
    m_pFlagShip->runAction(MoveBy::create(0.5, ccp(-400, 0)));
    m_SallyInfo->m_Status = SALLY_START;
    m_pNodePointShader->setVisible(false);
    m_pFormationSelecter->HideSelecter();
    
    NextStatus(1);
    //TODO
//    Fleet* allies = GameModel::getInstance()->getFleet(0);
//    Fleet* enemy = currentMissionNode->enemyFleet;
//    auto scene = new GameScene(new BattleModel(allies, enemy, formation, DanZong));
//    
//    Director::getInstance()->pushScene(scene);
}

void SallyPanel::SetMission(int areaId, int index)
{
    m_SallyInfo->SetMission(areaId, index);
    sallyMap->setTexture("Map/" +m_SallyInfo->GetMissionName()+ "/image 1.png");
}


NS_KCL_END
