//
//  SallyScene.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#include "SallyScene.h"
#include "Player.h"
#include "portScene.h"
#include "GameScene.h"
SallyScene::SallyScene(Mission* mission)
{
   
    
    this->mission=mission;
    this->currentMissionNode=mission->nodes[0];
    
    showingBottomPanel=false;
    
    
    bgImg=Sprite::create("interface/SallyMain/SallyMain_1.jpg");
    bgImg->setPosition(400,240);
    bgImg->setOpacity(0);
    addChild(bgImg);
    
    
    sallyMap=Sprite::create("map/"+mission->id+"/image 1.png");
    addChild(sallyMap);
    sallyMap->setPosition(400,240);
    sallyMap->setOpacity(0);
    
    ship=Sprite::create("interface/SallyMain/SallyMain_889.png");
    this->addChild(ship);
    ship->setZOrder(1);
    ship->setVisible(false);
    
    std::string flagShipName="kantai/"+std::to_string(Player::getInstance()->fleetData[0]->ship[0]->getkantaiNumber())+"/image 17.png";
    flagShip=Sprite::create(flagShipName.c_str());
    addChild(flagShip);
    flagShip->setPosition(-300,250);
    flagShip->setZOrder(2);
    
    bottomBorder = Sprite::create("interface/SallyMain/SallyMain_801.png");
    bottomBorder->setPosition(400, -250);
    bottomBorder->setZOrder(3);
    this->addChild(bottomBorder);
    bottomCompass = new Compass();
    this->addChild(bottomCompass);
    bottomCompass->setZOrder(3);
    bottomCompass->setPosition(40, -260);
    bottomCompass->setRotation(45);
    bottomLabel=Label::create();
    bottomLabel->setZOrder(3);
    this->addChild(bottomLabel);
    temptimer = Sprite::create("interface/BattleMain/BattleMain_515.png");
    this->addChild(temptimer);
    
     initializeFormationPanel();
    
    status = sally_start;
    
    sallyStart();
    
}
void SallyScene::initializeFormationPanel()
{
    Formation * danzong = new Formation(DanZong, this);
    danzong->setPosition(450, 370);
    danzong->setVisible(false);
    this->addChild(danzong);
    Formation * fuzong = new Formation(FuZong, this);
    fuzong->setPosition(580, 370);
    fuzong->setVisible(false);
    this->addChild(fuzong);
    Formation * lunxing = new Formation(LunXing, this);
    lunxing->setPosition(710, 370);
    lunxing->setVisible(false);
    this->addChild(lunxing);
    Formation * tixing = new Formation(TiXing, this);
    tixing->setPosition(510, 210);
    tixing->setVisible(false);
    this->addChild(tixing);
    Formation * danheng = new Formation(DanHeng, this);
    danheng->setPosition(640, 210);
    danheng->setVisible(false);
    this->addChild(danheng);
    
    formations.push_back(danzong);
    formations.push_back(fuzong);
    formations.push_back(lunxing);
    formations.push_back(tixing);
    formations.push_back(danheng);
}

void SallyScene::sallyStart()
{
    auto slide=Sprite::create("interface/SallyMain/SallyMain_545.png");
    auto start=Sprite::create("interface/SallyMain/SallyMain_548.png");
    auto startShader=Sprite::create("interface/SallyMain/SallyMain_548.png");
    slide->setPosition(1200,240);
    start->setPosition(400,240);
    start->setOpacity(0);
    
    startShader->setOpacity(0);
    startShader->setScale(1.15);
    startShader->setPosition(400,240);
    
    addChild(slide);
    addChild(start);
    addChild(startShader);
    
    
    slide->runAction(Sequence::create(MoveTo::create(0.3, ccp(400,240)),DelayTime::create(1.3),FadeOut::create(0.3),NULL));
    start->runAction(Sequence::create(DelayTime::create(0.3),FadeIn::create(0.3),DelayTime::create(1),FadeOut::create(0.3),NULL));
    startShader->runAction(Sequence::create(DelayTime::create(0.3),FadeIn::create(0.3),ScaleTo::create(0.1, 1),DelayTime::create(1),FadeOut::create(0.3), NULL));
    bgImg->runAction(Sequence::create(DelayTime::create(1.6),FadeIn::create(0.3), NULL));
    sallyMap->runAction(Sequence::create(DelayTime::create(1.6),FadeIn::create(0.3), NULL));
    
    
    nextStatus(1.9);
}

void SallyScene::nextStatus(float DelayTime)
{
    auto callFunc=CallFunc::create(CC_CALLBACK_0(SallyScene::onStatusOverCallBack, this));
    auto seq=Sequence::create(DelayTime::create(DelayTime),callFunc, NULL);
    temptimer->runAction(seq);
}


void SallyScene::onStatusOverCallBack()
{
    if (status==SallyStatus::sally_start)
    {
        status=sally_move;
        sallyMove();
    }
    else if(status==SallyStatus::sally_battle)
    {
        sallyBattle();
    }
    else if(status==SallyStatus::sally_formation)
    {
        sallyFormation();
    }
}

void SallyScene::sallyFormation()
{
    flagShip->runAction(MoveTo::create(0.5, ccp(100,150)));
    
    for (Formation* formation : formations)
    {
        formation->setVisible(true);
    }
}


void SallyScene::sallyMove()
{
    showBottomPanel();
    bool needRollCompass=false;
    float timepassed=0;
    ship->setVisible(true);
    ship->setPosition(currentMissionNode->position);
    
    MissionNode* nextNode;
    if (currentMissionNode->children.size()==0)
    {
        sallyFinish();
    }
    else if(currentMissionNode->children.size()==1)
    {
        nextNode=currentMissionNode->children[0];
    }
    else
    {
        needRollCompass=true;
        nextNode=currentMissionNode->children[1];
    }
    
    timepassed+=2;
    ship->runAction(Sequence::create(DelayTime::create(timepassed),MoveTo::create(1, nextNode->position), NULL));
    timepassed+=1;
    
    auto nodePoint=Sprite::create();
    nodePoint->setPosition(nextNode->position);
    nodePoint->setOpacity(0);
    nodePoint->runAction(Sequence::create(DelayTime::create(timepassed),FadeIn::create(0.5), NULL));
    addChild(nodePoint);
    
    nodePointShader=Sprite::create();
    nodePointShader->setPosition(nextNode->position);
    nodePointShader->setOpacity(0);
    nodePointShader->runAction(Sequence::create(DelayTime::create(timepassed),FadeIn::create(0.5), NULL));
    nodePointShader->runAction(RepeatForever::create((ActionInterval*)Sequence::create(ScaleTo::create(1.2, 2),ScaleTo::create(0.01, 1), NULL)));
    timepassed+=2.4;
    addChild(nodePointShader);
    
    switch (nextNode->type)
    {
        case node_boss:
        {
            nodePoint->setTexture("interface/SallyMain/SallyMain_796.png");
            nodePointShader->setTexture("interface/SallyMain/SallyMain_796.png");
            break;
        }
        case node_enemy:
        {
            nodePoint->setTexture("interface/SallyMain/SallyMain_790.png");
            nodePointShader->setTexture("interface/RemodelMain/RemodelMain_1.png");
            break;
        }
        case node_item:
        {
            nodePoint->setTexture("interface/interface/SallyMain/SallyMain_786.png");
            break;
        }
        case node_empty:
        {
            nodePoint->setTexture("interface/SallyMain/SallyMain_784.png");
            break;
        }
        case node_disaster:
        {
            nodePoint->setTexture("interface/SallyMain/SallyMain_788.png");
            break;
        }
        default:
            break;
    }
    
    
    if (nextNode->type==node_boss||nextNode->type==node_enemy)
    {
        this->status=sally_formation;
        currentMissionNode=nextNode;
        nextStatus(timepassed);
    }
    
}

void SallyScene::hideBottomPanel()
{
    if (!showingBottomPanel)
    {
        return;
    }
    bottomBorder->runAction(MoveBy::create(1, ccp(0,-300)));
    bottomCompass->runAction(MoveBy::create(1, ccp(0,-300)));
    bottomLabel->runAction(MoveBy::create(1, ccp(0,-300)));
    showingBottomPanel=false;
}

void SallyScene::showBottomPanel()
{
    if (showingBottomPanel)
    {
        return;
    }
    bottomBorder->runAction(MoveBy::create(1, ccp(0,300)));
    bottomCompass->runAction(MoveBy::create(1, ccp(0,300)));
    bottomLabel->runAction(MoveBy::create(1, ccp(0,300)));
    showingBottomPanel=true;
}


void SallyScene::sallyFinish()
{
    Director::getInstance()->replaceScene(PortScene::createScene());
}



void SallyScene::sallyBattle()
{
    
    
    
    
}



void SallyScene::setFormationCallback(Ref* ref, FormationType formation)
{
    flagShip->runAction(MoveBy::create(0.5f, ccp(-300,0)));
    this->status=sally_start;
    nodePointShader->removeFromParent();
    
    for(auto formation:formations)
    {
        formation->setVisible(false);
    }
    nextStatus(1);
    Fleet* allies=Player::getInstance()->fleetData[0];
    Fleet* enemy=currentMissionNode->enemyFleet;
    
    auto battleModel=new BattleModel(allies,enemy,formation,DanZong);
    GameScene* scene=new GameScene(battleModel);
    Director::getInstance()->replaceScene(scene);
    
    
}

