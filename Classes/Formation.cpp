//
//  Formation.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#include "Formation.hpp"
#include "Player.h"
#include "Fleet.h"
#include "SallyPanel.hpp"
#include "ViewMgr.hpp"

NS_KCL_BEGIN


Formation* Formation::create(kancolle::FormationType _type)
{
    Formation* pRet=new Formation;
    if(pRet&&pRet->init(_type))
    {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet=NULL;
    return pRet;
}

bool Formation::init(kancolle::FormationType _type)
{
    bool bRet=false;
    
    do
    {
        m_FormationType=_type;
        
        InitBg();
        for(int i=0;i<6;++i)
        {
            Sprite *temp = Sprite::create("BattleMain/image 686.png");
            temp->setVisible(false);
            m_vPoints.push_back(temp);
            addChild(temp);
        }
        OrganizePoints();

        bRet=true;
    }while(0);
    
    
    return bRet;
}


void Formation::InitBg()
{
    m_pSallyPanel=dynamic_cast<SallyPanel*>(VIEW_MGR->getPanel(PanelType::SALLY_MAIN));
    m_pFormationBg = Sprite::create("SallyMain/image 684.png");
    m_pFormationBg->setZOrder(-1);
    this->addChild(m_pFormationBg);
    m_pFormationBg->setPosition(0, -18);
    switch (m_FormationType)
    {
        case DanZong:
            m_pFormationButton = MenuItemImage::create("SallyMain/image 692.png",
                                           "SallyMain/image 694.png", CC_CALLBACK_1(SallyPanel::SetFormationCallback, m_pSallyPanel,DanZong));
            break;
        case FuZong:
            m_pFormationButton = MenuItemImage::create("SallyMain/image 697.png",
                                           "SallyMain/image 699.png", CC_CALLBACK_1(SallyPanel::SetFormationCallback, m_pSallyPanel,FuZong));
            break;
        case LunXing:
            m_pFormationButton = MenuItemImage::create("SallyMain/image 702.png",
                                           "SallyMain/image 704.png", CC_CALLBACK_1(SallyPanel::SetFormationCallback, m_pSallyPanel,LunXing));
            break;
        case TiXing:
            m_pFormationButton = MenuItemImage::create("SallyMain/image 707.png",
                                           "SallyMain/image 709.png", CC_CALLBACK_1(SallyPanel::SetFormationCallback, m_pSallyPanel,TiXing));
            break;
        case DanHeng:
            m_pFormationButton = MenuItemImage::create("SallyMain/image 712.png",
                                           "SallyMain/image 714.png", CC_CALLBACK_1(SallyPanel::SetFormationCallback, m_pSallyPanel,DanHeng));
            break;
        default:
            break;
    }
    m_pFormationButton->setPosition(0, -67);
    
    auto menu = Menu::create(m_pFormationButton, NULL);
    this->addChild(menu);
    menu->setZOrder(1);
    menu->setPosition(Point::ZERO);
    
}

void Formation::OrganizePoints()
{
    m_iShipCount=sPlayer.getFleetByFleetKey(1)->KantaiSize();
    
    if (m_iShipCount == 1)
        return;
    
    switch (m_FormationType)
    {
        case DanZong:
            Danzong();
            break;
        case FuZong:
            Fuzong();
            break;
        case LunXing:
            Lunxing();
            break;
        case TiXing:
            Tixing();
            break;
        case DanHeng:
            Danheng();
            break;
        default:
            break;
    }
}



void Formation::Danzong()
{
    if (0 == (m_iShipCount & 1)) //≈º ˝
    {
        for (int i = 0, j = 0; i < m_vPoints.size(); i++)
        {
            int x;
            
            if ((i & 1) == 0)
                x = -8 - 16 * j;
            else
            {
                x = 8 + 16 * j;
                j++;
            }
            
            m_vPoints[i]->setPosition(x, 0);
        }
    }
    else //∆Ê ˝
    {
        for (int i = 1, j = 1; i < m_vPoints.size(); i++)
        {
            int x;
            
            if ((i & 1) != 0)
                x = -18 * j;
            else
            {
                x = 18 * j;
                j++;
            }
            
            m_vPoints[i]->setPosition(x, 0);
        }
    }
}
void Formation::Fuzong(){
    if (m_iShipCount < 4)
        return;
    float x = 0;
    if (m_iShipCount > 4)
    {
        x = -10;
        m_vPoints[4]->setPosition(x + 30, 10);
    }
    if (m_iShipCount == 6)
        m_vPoints[5]->setPosition(x + 30, -10);
    
    m_vPoints[0]->setPosition(x+10, 10);
    m_vPoints[1]->setPosition(x+10, -10);
    m_vPoints[2]->setPosition(x - 10, 10);
    m_vPoints[3]->setPosition(x - 10, -10);
    
}
void Formation::Tixing()
{
    if (m_iShipCount < 4)
        return;
    int x = 0, y = 0;
    if (m_iShipCount == 5)
    {
        x = 5;
        m_vPoints[4]->setPosition(x - 25, y - 25);
    }
    if (m_iShipCount == 6)
    {
        m_vPoints[4]->setPosition(x + 25, y + 25);
        m_vPoints[5]->setPosition(x - 25, y - 25);
    }
    
    m_vPoints[0]->setPosition(x - 5, y - 5);
    m_vPoints[1]->setPosition(x + 5, y + 5);
    m_vPoints[2]->setPosition(x - 15, y - 15);
    m_vPoints[3]->setPosition(x + 15, y + 15);
}
void Formation::Danheng(){
    Danzong();
    RotatePoints();
}
void Formation::Lunxing(){
    if (m_iShipCount == 6){
        m_vPoints[0]->setPosition(8, 0);
        m_vPoints[1]->setPosition(-8, 0);
        m_vPoints[2]->setPosition(24, 0);
        m_vPoints[3]->setPosition(-24, 0);
        m_vPoints[4]->setPosition(0, 20);
        m_vPoints[5]->setPosition(0, -20);
    }
    else if (m_iShipCount == 5){
        m_vPoints[0]->setPosition(0, 0);
        m_vPoints[1]->setPosition(-15, 0);
        m_vPoints[2]->setPosition(15, 0);
        m_vPoints[3]->setPosition(0, 15);
        m_vPoints[4]->setPosition(0, -15);
    }
}


void Formation::AddBattleBorder()
{
    m_pBorder = Sprite::create("BattleMain/image 372.png");
    this->addChild(m_pBorder);
}

void Formation::RotatePoints()
{
    for (int i = 0; i < m_vPoints.size(); i++)
    {
        int x = m_vPoints[i]->getPosition().x;
        int y = m_vPoints[i]->getPosition().y;
        m_vPoints[i]->setPosition(y, x);
    }
}


void Formation::ShowPoints()
{
    for (int i = 0; i < m_vPoints.size(); i++)
        m_vPoints[i]->setVisible(true);
}
void Formation::HidePoints()
{
    for (int i = 0; i < m_vPoints.size(); i++)
        m_vPoints[i]->setVisible(false);
}



/*
Formation::Formation(FormationType type,SallyScene* parent)
{
    this->type = type;
    
    shipCount = MAX_SHIPS_PER_FLEET;
    for (int i = 0; i < shipCount; i++){
        Sprite *temp = Sprite::create("BattleMain/image 686.png");
        temp->setVisible(false);
        points.push_back(temp);
        this->addChild(temp);
    }
    organizePoints();
    showPoints();
    initializePanel(parent);
    rotatePoints();
}
Formation::Formation(int shipCount, FormationType type)
{
    this->type = type;
    this->shipCount = shipCount;
    
    for (int i = 0; i < shipCount; i++){
        Sprite *temp = Sprite::create("BattleMain/image 686.png");
        temp->setVisible(false);
        points.push_back(temp);
        this->addChild(temp);
    }
    organizePoints();
}
Formation::Formation(int shipCount, FormationType type, bool isEnemy)
{
    this->type = type;
    this->shipCount = shipCount;
    pointUrl = "BattleMain/image 686.png";
    if (isEnemy)
        pointUrl = "BattleMain/image 688.png";
    for (int i = 0; i < shipCount; i++){
        Sprite *temp = Sprite::create(pointUrl);
        temp->setVisible(false);
        points.push_back(temp);
        this->addChild(temp);
    }
    organizePoints();
}

*/


/*
void Formation::initializePanel(SallyScene *parentSallyScene)
{
    this->parentSallyScene = parentSallyScene;
    panelBg = Sprite::create("SallyMain/image 684.png");
    panelBg->setZOrder(-1);
    this->addChild(panelBg);
    panelBg->setPosition(0, -18);
    switch (type)
    {
        case DanZong:
            button = MenuItemImage::create("SallyMain/image 692.png",
                                           "SallyMain/image 694.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,DanZong));
            break;
        case FuZong:
            button = MenuItemImage::create("SallyMain/image 697.png",
                                           "SallyMain/image 699.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,FuZong));
            break;
        case LunXing:
            button = MenuItemImage::create("SallyMain/image 702.png",
                                           "SallyMain/image 704.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,LunXing));
            break;
        case TiXing:
            button = MenuItemImage::create("SallyMain/image 707.png",
                                           "SallyMain/image 709.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,TiXing));
            break;
        case DanHeng:
            button = MenuItemImage::create("SallyMain/image 712.png",
                                           "SallyMain/image 714.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,DanHeng));
            break;
        default:
            break;
    }
    button->setPosition(0, -67);
    
    auto menu = Menu::create(button, NULL);
    this->addChild(menu);
    menu->setZOrder(1);
    menu->setPosition(Point::ZERO);
}
*/

NS_KCL_END
