//
//  MissionSelectPage.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#include "MissionSelectPage.h"
#include "portBattleLayer.h"
#include "XMLParser.h"
#include "SallyScene.h"

NS_KCL_BEGIN


MissionSelectPage::MissionSelectPage(Node *parent)
{
    this->parent = parent;
    Hidden = true;
    
    auto bgimg = Sprite::create("interface/SallyMain/SallyMain_45.png");
    this->addChild(bgimg);
    bgimg->setOpacity(250);
    bgimg->setPosition(450, 197);
    
    auto top_bar = Sprite::create("interface/SallyMain/SallyMain_47.png");
    this->addChild(top_bar);
    top_bar->setPosition(450, 397);
    
    auto top_label = Sprite::create("interface/SallyMain/SallyMain_380.png");
    this->addChild(top_label);
    top_label->setPosition(160, 397);
    
    auto title_label = Sprite::create("interface/SallyMain/SallyMain_379.png");
    this->addChild(title_label);
    title_label->setPosition(280, 365);
    
    //containers
    currentArea = 1;
    container1 = new MissionContainer(currentArea, 0);
    container2 = new MissionContainer(currentArea, 1);
    container3 = new MissionContainer(currentArea, 2);
    container4 = new MissionContainer(currentArea, 3);
    container1->setPosition(290, 280);
    container2->setPosition(620, 280);
    container3->setPosition(290, 140);
    container4->setPosition(620, 140);
    this->addChild(container1);
    this->addChild(container2);
    this->addChild(container3);
    this->addChild(container4);
    //mission buttons
    auto mb1 = Sprite::create("interface/SallyMain/SallyMain_441.png");
    mb1->setOpacity(0);
    auto mb2 = Sprite::create("interface/SallyMain/SallyMain_441.png");
    mb2->setOpacity(0);
    auto mb3 = Sprite::create("interface/SallyMain/SallyMain_441.png");
    mb3->setOpacity(0);
    auto mb4 = Sprite::create("interface/SallyMain/SallyMain_441.png");
    mb4->setOpacity(0);
    auto missionButton1 = MenuItemSprite::create(mb1, Sprite::create("interface/SallyMain/SallyMain_441.png"),CC_CALLBACK_1(MissionSelectPage::startMission,this,0));
    missionButton1->setPosition(290, 280);
    
    auto missionButton2 = MenuItemSprite::create(mb2, Sprite::create("interface/SallyMain/SallyMain_441.png"), CC_CALLBACK_1(MissionSelectPage::startMission, this, 1));
    missionButton2->setPosition(620, 280);
    
    auto missionButton3 = MenuItemSprite::create(mb3, Sprite::create("interface/SallyMain/SallyMain_441.png"), CC_CALLBACK_1(MissionSelectPage::startMission, this, 2));
    missionButton3->setPosition(290, 140);
    
    auto missionButton4 = MenuItemSprite::create(mb4, Sprite::create("interface/SallyMain/SallyMain_441.png"), CC_CALLBACK_1(MissionSelectPage::startMission, this, 3));
    missionButton4->setPosition(620, 140);
    
    //top right buttons
    
//    auto strikeButton = MenuItemImage::create("Resources/interface/SallyMain/SallyMain_65.png", "Resources/interface/SallyMain/SallyMain_63.png", CC_CALLBACK_1(PortBattleLayer::ShowMissionSelectPage, parent));
//    strikeButton->setPosition(580, 365);
//    auto playactButton = MenuItemImage::create("Resources/interface/SallyMain/SallyMain_51.png", "Resources/interface/SallyMain/SallyMain_53.png", CC_CALLBACK_1(PortBattleLayer::callBack1, parent));
//    playactButton->setPosition(660, 365);
//    auto expeditionButton = MenuItemImage::create("Resources/interface/SallyMain/SallyMain_56.png", "Resources/interface/SallyMain/SallyMain_58.png", CC_CALLBACK_1(PortBattleLayer::callBack2, parent));
//    expeditionButton->setPosition(740, 365);

//    auto strikeButton=MenuItemImage::create("Resources/interface/SallyMain/SallyMain_65.png", "Resources/interface/SallyMain/SallyMain_63.png", CC_CALLBACK_1(PortBattleLayer::ShowMissionSelectPage, this,parent));
//    
//    
    //area buttons
    auto area1 = MenuItemImage::create("interface/SallyMain/SallyMain_69.png", "interface/SallyMain/SallyMain_71.png", CC_CALLBACK_1(MissionSelectPage::setCurrentArea, this,1));
    area1->setPosition(160, 50);
    auto area2 = MenuItemImage::create("interface/SallyMain/SallyMain_74.png", "interface/SallyMain/SallyMain_78.png", CC_CALLBACK_1(MissionSelectPage::setCurrentArea, this, 2));
    area2->setPosition(230, 50);
    auto area3 = MenuItemImage::create("interface/SallyMain/SallyMain_81.png", "interface/SallyMain/SallyMain_83.png", CC_CALLBACK_1(MissionSelectPage::setCurrentArea, this, 3));
    area3->setPosition(300, 50);
    auto area4 = MenuItemImage::create("interface/SallyMain/SallyMain_86.png", "interface/SallyMain/SallyMain_90.png", CC_CALLBACK_1(MissionSelectPage::setCurrentArea, this, 4));
    area4->setPosition(370, 50);
    auto area5 = MenuItemImage::create("interface/SallyMain/SallyMain_93.png", "interface/SallyMain/SallyMain_95.png", CC_CALLBACK_1(MissionSelectPage::setCurrentArea, this, 5));
    area5->setPosition(440, 50);
    auto area6 = MenuItemImage::create("interface/SallyMain/SallyMain_98.png", "interface/SallyMain/SallyMain_100.png", CC_CALLBACK_1(MissionSelectPage::setCurrentArea, this, 6));
    area6->setPosition(510, 50);
    //strikeButton, playactButton, expeditionButton,
    menu = Menu::create(missionButton1, missionButton2 ,missionButton3,missionButton4, area1, area2, area3, area4, area5, area6, NULL);
    this->addChild(menu);
    menu->setPosition(0, 0);
}

void  MissionSelectPage::setCurrentArea(Ref* pSender, int areaId)
{
    this->currentArea = areaId;
    container1->updateContainer(currentArea, 0);
    container2->updateContainer(currentArea, 1);
    container3->updateContainer(currentArea, 2);
    container4->updateContainer(currentArea, 3);
}
void MissionSelectPage::moveIn()
{
    if (Hidden)
    {
        runAction(MoveBy::create(0.2f, ccp(-800,0)));
        Hidden=false;
    }
}

void MissionSelectPage::moveOut()
{
    if (!Hidden)
    {
        runAction(MoveBy::create(0.2, ccp(800,0)));
        Hidden=true;
    }
}




void MissionSelectPage::startMission(cocos2d::Ref *pSender,int index)
{
    
//    Scene* scene=new SallyScene(XMLParser::getInstance()->readMissionXml("1-1"));
//    Director::getInstance()->replaceScene(scene);
    
}

NS_KCL_END

