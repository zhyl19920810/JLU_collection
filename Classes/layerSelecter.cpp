//
//  LayerSelecter.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#include "LayerSelecter.h"
#include "SelecterUnit.hpp"
#include "ViewMgr.hpp"
#include "EventPauseGuard.hpp"

NS_KCL_BEGIN


//const static float DropTime=0.07;
//const static float LiftTime=0.17;
//const static float OrbitMoveTime=0.3;


LayerSelecter::LayerSelecter()
{

}





void LayerSelecter::moveOut()
{
    std::string currPos=getPanelName(currType);
    auto currSelecter=getSelecterUnit(currType);
    currSelecter->setPosition(Vec2(xLoc["buttonFree"], yLoc[currPos]));
    currSelecter->setSelected(false);
    
    setPosition(lsPos["show"]);
    runAction(MoveTo::create(0.3, lsPos["hide"]));
}

void LayerSelecter::moveIn()
{
    setPosition(lsPos["hide"]);
    runAction(MoveTo::create(0.3, lsPos["show"]));
}


void LayerSelecter::loadLocData()
{
    xLoc["buttonFree"]=-30.0;
    xLoc["buttonSelected"]=-25.0;
    xLoc["hookMoved"]=7.0;
    xLoc["hookDown"]=-10.0;
    xLoc["hookSuspend"]=-3.0;
    
    yLoc["organize"]=100;
    yLoc["supply"]=50;
    yLoc["remode"]=0;
    yLoc["repair"]=-50;
    yLoc["factory"]=-100;
    
    lsPos["hide"]=Vec2(-50, 220);
    lsPos["show"]=Vec2(50, 220);
}

bool LayerSelecter::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        loadLocData();
        initBg();
        initButton();
        initHook();
        
        bRet=true;
    }while(0);
    return bRet;
}


void LayerSelecter::initHook()
{
    hook=Sprite::create("PortMain/image 245.png");
    hook->setPosition(xLoc["hookSuspend"], yLoc["organize"]);
    addChild(hook,-1);
}

void LayerSelecter::initBg()
{
    mainbody =Sprite::createWithSpriteFrameName("lsmb.png");
    mainbody->setPosition(-10, 0);
    addChild(mainbody);
    
    backgroud = Sprite::createWithSpriteFrameName("lsbg.png");
    backgroud->setPosition(0, 0);
    this->addChild(backgroud,-2);
}

void LayerSelecter::initButton()
{
    mainButton=SelecterUnit::create(PanelType::PORT_MAINLAYER);
    mainButton->setPosition(22, 0);
    addChild(mainButton);
    
    organizeButton=SelecterUnit::create(PanelType::PORT_ORGANIZE);
    organizeButton->setPosition(xLoc["buttonFree"], yLoc["organize"]);
    addChild(organizeButton);
    
    supplyButton=SelecterUnit::create(PanelType::PORT_SUPPLY);
    supplyButton->setPosition(xLoc["buttonFree"], yLoc["supply"]);
    addChild(supplyButton);
    
    remodeButton=SelecterUnit::create(PanelType::PORT_REMODE);
    remodeButton->setPosition(xLoc["buttonFree"], yLoc["remode"]);
    addChild(remodeButton);
    
    repairButton=SelecterUnit::create(PanelType::PORT_REPAIR);
    repairButton->setPosition(xLoc["buttonFree"], yLoc["repair"]);
    addChild(repairButton);
    
    factoryButton=SelecterUnit::create(PanelType::PORT_FACTORY);
    factoryButton->setPosition(xLoc["buttonFree"], yLoc["factory"]);
    addChild(factoryButton);
}

void LayerSelecter::setBattleState()
{
    
}

void LayerSelecter::setLayerType(PanelType type)
{
    if (type==PanelType::PORT_BATTLE)
    {
        setBattleState();
        return;
    }
    currType=type;
    if (isPortPanel(currType))
    {
        std::string modifyPos=getPanelName(type);
        hook->setPosition(xLoc["hookSuspend"], yLoc[modifyPos]);
        
        auto modifySelecter=getSelecterUnit(type);
        modifySelecter->setPosition(xLoc["buttonSelected"], yLoc[modifyPos]);
        modifySelecter->setSelected(true);
    }
}

bool LayerSelecter::isPortPanel(PanelType type) const
{
    if (type==PanelType::PORT_FACTORY||
        type==PanelType::PORT_ORGANIZE||
        type==PanelType::PORT_REMODE||
        type==PanelType::PORT_REPAIR||
        type==PanelType::PORT_SUPPLY)
    {
        return true;
    }
    return false;
}


void LayerSelecter::changeHookPos(kancolle::PanelType type)
{
    if (type==currType) return;
    if (!isPortPanel(type)) return;
    
    std::string currPos=getPanelName(currType);
    std::string modifyPos=getPanelName(type);
    auto currSelecter=getSelecterUnit(currType);
    auto modifySelecter=getSelecterUnit(type);
    
    
    CallFunc* callPre=CallFunc::create([=]()
    {
        EVENT_PAUSE
    });
    
    ActionInterval* p1;
    {

        CallFunc* callfunc=CallFunc::create([=]()
        {
            auto hookMove=MoveTo::create(DropTime, Vec2(xLoc["hookDown"], yLoc[currPos]));
            hook->runAction(hookMove);
            auto buttonMove=MoveTo::create(DropTime, Vec2(xLoc["buttonFree"], yLoc[currPos]));
            currSelecter->runAction(buttonMove);
        });
        
        CallFunc* callAfter=CallFunc::create([=]()
        {
            currSelecter->setSelected(false);
            currSelecter->setPosition(xLoc["buttonFree"], yLoc[currPos]);
        });
        p1=Sequence::create(callfunc,DelayTime::create(DropTime+StopTime),callAfter, NULL);
    }
    
    ActionInterval* p2;
    {
        CallFunc* callfunc=CallFunc::create([=]()
        {
            auto hookMove=MoveTo::create(LiftTime, Vec2(xLoc["hookMoved"], yLoc[currPos]));
            hook->runAction(hookMove);
        });
        p2=Sequence::create(callfunc,DelayTime::create(LiftTime+StopTime), NULL);
    }
    
    ActionInterval* p3;
    {
        CallFunc* callfunc=CallFunc::create([=]()
        {
            auto hookMove=MoveTo::create(OrbitMoveTime, Vec2(xLoc["hookMoved"], yLoc[modifyPos]));
            hook->runAction(hookMove);
        });
        p3=Sequence::create(callfunc,DelayTime::create(OrbitMoveTime+StopTime), NULL);
    }
    
    ActionInterval* p4;
    {   CallFunc* callfunc=CallFunc::create([=]()
        {
            auto hookMove=MoveTo::create(LiftTime, Vec2(xLoc["hookDown"], yLoc[modifyPos]));
            hook->runAction(hookMove);
        });
        CallFunc* callAfter=CallFunc::create([=]()
        {
            modifySelecter->setSelected(true);
            modifySelecter->setPosition(xLoc["buttonFree"], yLoc[modifyPos]);
        });
        p4=Sequence::create(callfunc,DelayTime::create(LiftTime+StopTime),callAfter, NULL);
    }
    
    ActionInterval* p5;
    {
        CallFunc* callfunc=CallFunc::create([=]()
        {
            auto hookMove=MoveTo::create(DropTime, Vec2(xLoc["hookSuspend"], yLoc[modifyPos]));
            hook->runAction(hookMove);
            auto buttonMove=MoveTo::create(DropTime, Vec2(xLoc["buttonSelected"], yLoc[modifyPos]));
            modifySelecter->runAction(buttonMove);
        });
        CallFunc* callAfter=CallFunc::create([=]()
        {
            currType=type;
        });
        p5=Sequence::create(callfunc,DelayTime::create(DropTime),callAfter, NULL);
    }
    CallFunc* callPost=CallFunc::create([=]()
    {
         EVENT_RESUME
    });
    
    auto seqAction=Sequence::create(callPre,p1,p2,p3,p4,p5,callPost,NULL);
    runAction(seqAction);
    
}

SelecterUnit* LayerSelecter::getSelecterUnit(PanelType type) const
{
    SelecterUnit* pRet=NULL;
    switch (type)
    {
        case PanelType::PORT_MAINLAYER:
            pRet=mainButton;
            break;
        case PanelType::PORT_ORGANIZE:
            pRet=organizeButton;
            break;
        case PanelType::PORT_SUPPLY:
            pRet=supplyButton;
            break;
        case PanelType::PORT_REMODE:
            pRet=remodeButton;
            break;
        case PanelType::PORT_REPAIR:
            pRet=repairButton;
            break;
        case PanelType::PORT_FACTORY:
            pRet=factoryButton;
            break;
        default:
            break;
    }
    return pRet;
}

std::string LayerSelecter::getPanelName(PanelType type) const
{
    std::string str;
    switch (type)
    {
        case PanelType::PORT_MAINLAYER:
            str="main";
            break;
        case PanelType::PORT_ORGANIZE:
            str="organize";
            break;
        case PanelType::PORT_SUPPLY:
            str="supply";
            break;
        case PanelType::PORT_REMODE:
            str="remode";
            break;
        case PanelType::PORT_REPAIR:
            str="repair";
            break;
        case PanelType::PORT_FACTORY:
            str="factory";
            break;
        default:
            break;
    }
    return str;
}



NS_KCL_END


