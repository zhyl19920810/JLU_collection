//
//  MissonSelectPage.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "MissonSelectPage.hpp"
#include "ViewMgr.hpp"
#include "SallyPanel.hpp"


NS_KCL_BEGIN

bool MissionSelectPage::init()
{
    bool bRet=false;
    do
    {
        InitBg();
        
        m_bHidden = true;
        
        //containers
        m_iCurrentArea = 1;
        m_pContainer1 =MissionContainer::create();
        m_pContainer2 =MissionContainer::create();
        m_pContainer3 =MissionContainer::create();
        m_pContainer4 =MissionContainer::create();
        m_pContainer1->setPosition(290, 280);
        m_pContainer2->setPosition(620, 280);
        m_pContainer3->setPosition(290, 140);
        m_pContainer4->setPosition(620, 140);
        this->addChild(m_pContainer1);
        this->addChild(m_pContainer2);
        this->addChild(m_pContainer3);
        this->addChild(m_pContainer4);
        m_pContainer1->updateContainer(m_iCurrentArea, 0);
        m_pContainer2->updateContainer(m_iCurrentArea, 1);
        m_pContainer3->updateContainer(m_iCurrentArea, 2);
        m_pContainer4->updateContainer(m_iCurrentArea, 3);
        

        MenuItem*  missionButton1 = MenuItemSprite::create(Sprite::create("SallyMain/image 481.png"), Sprite::create("SallyMain/image 481.png"),CC_CALLBACK_1(MissionSelectPage::StartMission,this,1));
        missionButton1->setPosition(290, 280);
        
        MenuItem*  missionButton2 = MenuItemSprite::create(Sprite::create("SallyMain/image 481.png"), Sprite::create("SallyMain/image 481.png"), CC_CALLBACK_1(MissionSelectPage::StartMission, this, 2));
        missionButton2->setPosition(620, 280);
        
        MenuItem*  missionButton3 = MenuItemSprite::create(Sprite::create("SallyMain/image 481.png"), Sprite::create("SallyMain/image 481.png"), CC_CALLBACK_1(MissionSelectPage::StartMission, this, 3));
        missionButton3->setPosition(290, 140);
        
        MenuItem*  missionButton4 = MenuItemSprite::create(Sprite::create("SallyMain/image 481.png"), Sprite::create("SallyMain/image 481.png"), CC_CALLBACK_1(MissionSelectPage::StartMission, this, 4));
        missionButton4->setPosition(620, 140);
        
        
        //area buttons
        MenuItem*  area1 = MenuItemImage::create("SallyMain/image 91.png", "SallyMain/image 93.png", CC_CALLBACK_1(MissionSelectPage::SetCurrentArea, this,1));
        area1->setPosition(160, 50);
        MenuItem*  area2 = MenuItemImage::create("SallyMain/image 96.png", "SallyMain/image 100.png", CC_CALLBACK_1(MissionSelectPage::SetCurrentArea, this, 2));
        area2->setPosition(230, 50);
        MenuItem*  area3 = MenuItemImage::create("SallyMain/image 103.png", "SallyMain/image 105.png", CC_CALLBACK_1(MissionSelectPage::SetCurrentArea, this, 3));
        area3->setPosition(300, 50);
        MenuItem*  area4 = MenuItemImage::create("SallyMain/image 108.png", "SallyMain/image 112.png", CC_CALLBACK_1(MissionSelectPage::SetCurrentArea, this, 4));
        area4->setPosition(370, 50);
        MenuItem*  area5 = MenuItemImage::create("SallyMain/image 115.png", "SallyMain/image 117.png", CC_CALLBACK_1(MissionSelectPage::SetCurrentArea, this, 5));
        area5->setPosition(440, 50);
        MenuItem*  area6 = MenuItemImage::create("SallyMain/image 120.png", "SallyMain/image 122.png", CC_CALLBACK_1(MissionSelectPage::SetCurrentArea, this, 6));
        area6->setPosition(510, 50);
        
        menu = Menu::create(missionButton1, missionButton2 ,missionButton3,missionButton4, area1, area2, area3, area4, area5, area6, NULL);
        this->addChild(menu);
        menu->setPosition(0, 0);
        
        
        bRet=true;
    }while(0);
    
    return bRet;
    
}


void MissionSelectPage::InitBg()
{
    auto bgimg = Sprite::create("SallyMain/image 67.png");
    this->addChild(bgimg);
    bgimg->setOpacity(250);
    bgimg->setPosition(450, 197);
    
    auto top_bar = Sprite::create("SallyMain/image 69.png");
    this->addChild(top_bar);
    top_bar->setPosition(450, 397);
    
    auto top_label = Sprite::create("SallyMain/image 410.png");
    this->addChild(top_label);
    top_label->setPosition(160, 397);
    
    auto title_label = Sprite::create("SallyMain/image 409.png");
    this->addChild(title_label);
    title_label->setPosition(280, 365);
}


void MissionSelectPage::MoveOut()
{
    if (!m_bHidden)
    {
        this->runAction(MoveBy::create(0.2, ccp(800, 0)));
        m_bHidden = true;
    }
    
}
void MissionSelectPage::MoveIn()
{
    if (m_bHidden)
    {
        this->runAction(MoveBy::create(0.2, ccp(-800, 0)));
        m_bHidden = false;
    }
}


void  MissionSelectPage::SetCurrentArea(Ref* pSender, int areaId)
{
    m_iCurrentArea = areaId;
    m_pContainer1->updateContainer(m_iCurrentArea, 0);
    m_pContainer2->updateContainer(m_iCurrentArea, 1);
    m_pContainer3->updateContainer(m_iCurrentArea, 2);
    m_pContainer4->updateContainer(m_iCurrentArea, 3);
}
void MissionSelectPage::StartMission(Ref* pSender, int index)
{
    VIEW_MGR->showScene(SceneType::SALLY);
    SallyPanel* sallyPanel=dynamic_cast<SallyPanel*>(VIEW_MGR->showPanel(PanelType::SALLY_MAIN));
    sallyPanel->SetMission(m_iCurrentArea, index);
    //auto model = new BattleModel(GameModel::getInstance()->getFleet(0), new Fleet(5), DanZong, LunXing);
    //auto scene = new GameScene(model);
    //auto scene = new SallyScene(XMLParser::getInstance()->loadMissionInfo(Helper::getMissionId(currentArea, index)));
    //Director::getInstance()->replaceScene(scene);
    
}


NS_KCL_END
