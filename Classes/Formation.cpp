//
//  Formation.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#include "Formation.h"
#include "SallyScene.h"


Formation::Formation(int shipCount,FormationType type,bool enemy)
{
    this->type=type;
    this->shipCount=shipCount;
    
    pointUrl="interface/BattleMain/BattleMain_511.png";
    if (enemy)
    {
        pointUrl="interface/BattleMain/BattleMain_513.png";;
    }
    
    for (int i=0; i<shipCount; ++i)
    {
        Sprite* temp=Sprite::create(pointUrl);
        temp->setVisible(false);
        points.push_back(temp);
        addChild(temp);
    }
    organizePoints();
}

Formation::Formation(FormationType type,SallyScene* parent)
{
    this->type=type;
    
    shipCount=MAX_SHIPS_PER_FLEET;
    for (int i=0; i<shipCount; ++i)
    {
        Sprite* temp=Sprite::create("interface/BattleMain/BattleMain_511.png");
        temp->setVisible(false);
        points.push_back(temp);
        addChild(temp);
    }
    organizePoints();
    showPoints();
    intializePanel(parent);
    rotatePoints();
}

void Formation::showPoints()
{
    for (auto it=points.begin(); it!=points.end(); ++it)
    {
        (*it)->setVisible(true);
    }
}

void Formation::hidePoints()
{
    for (auto it=points.begin(); it!=points.end(); ++it)
    {
        (*it)->setVisible(false);
    }
}

void Formation::addBattleBorder()
{
    border=Sprite::create("interface/BattleMain/BattleMain_379.png");
    addChild(border);
    
}
void Formation::intializePanel(SallyScene* parent)
{
    parentSallyScene=parent;
    panelBg = Sprite::create("interface/SallyMain/SallyMain_622.png");
    panelBg->setZOrder(-1);
    this->addChild(panelBg);
    panelBg->setPosition(0, -18);
    
    
    switch (type)
    {
        case DanZong:
            button = MenuItemImage::create("interface/SallyMain/SallyMain_630.png","interface/SallyMain/SallyMain_632.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,DanZong));
            break;
        case FuZong:
            button = MenuItemImage::create("interface/SallyMain/SallyMain_635.png","interface/SallyMain/SallyMain_637.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,FuZong));
            break;
        case LunXing:
            button = MenuItemImage::create("interface/SallyMain/SallyMain_640.png",
                                           "interface/SallyMain/SallyMain_642.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,LunXing));
            break;
        case TiXing:
            button = MenuItemImage::create("interface/SallyMain/SallyMain_645.png",
                                           "interface/SallyMain/SallyMain_647.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,TiXing));
            break;
        case DanHeng:
            button = MenuItemImage::create("interface/SallyMain/SallyMain_650.png",
                                           "interface/SallyMain/SallyMain_652.png", CC_CALLBACK_1(SallyScene::setFormationCallback, parentSallyScene,DanHeng));
            break;
        default:
            break;
    }
    button->setPosition(0,-67);
    
    auto menu=Menu::create(button, NULL);
    addChild(menu);
    menu->setZOrder(1);
    menu->setPosition(Point::ZERO);
}


void Formation::organizePoints()
{
    if (shipCount==1)
    {
        return;
    }
    
    switch (type) {
        case DanZong:
        {
            danzong();
            break;
        }
        case FuZong:
        {
            fuzong();
            break;
        }
        case LunXing:
        {
            lunxing();
            break;
        }
        case TiXing:
        {
            tixing();
            break;
        }
        case DanHeng:
        {
            danheng();
            break;
        }
        default:
            break;
    }
}



void Formation::danzong()
{
    if (0==(shipCount&1))
    {
        for (int i=0,j=0; i<shipCount; ++i)
        {
            int x;
            
            if ((i&1)==0)
            {
                x=-8-16*i;
            }
            else
            {
                x=8+16*i;
                ++j;
            }
            points[i]->setPosition(x,0);
        }
    }
    else
    {
        for (int i=0,j=0; i<shipCount; ++i)
        {
            int x;
            if ((i&1)==0)
            {
                x=-18*j;
            }
            else
            {
                x=18*j;
                ++j;
            }
            points[i]->setPosition(x,0);
        }
    }
}



void Formation::fuzong()
{
    if (shipCount<4)
    {
        return;
    }
    int x=0,y=0;
    if (shipCount==5)
    {
        x=5;
        points[4]->setPosition(x-25,y-25);
    }
    if (shipCount==6)
    {
        points[4]->setPosition(x-25,y-25);
        points[5]->setPosition(x+25,y+25);
    }
    
    points[0]->setPosition(x-5,y-5);
    points[1]->setPosition(x+5,y+5);
    points[2]->setPosition(x-15,y-15);
    points[3]->setPosition(x+15,y+15);
}

void Formation::lunxing()
{
    if (shipCount==6)
    {
        points[0]->setPosition(8, 0);
        points[1]->setPosition(-8, 0);
        points[2]->setPosition(24, 0);
        points[3]->setPosition(-24, 0);
        points[4]->setPosition(0, 20);
        points[5]->setPosition(0, -20);
    }
    else if (shipCount == 5){
        points[0]->setPosition(0, 0);
        points[1]->setPosition(-15, 0);
        points[2]->setPosition(15, 0);
        points[3]->setPosition(0, 15);
        points[4]->setPosition(0, -15);
    }
}

void Formation::tixing()
{
    if (shipCount < 4)
        return;
    int x = 0, y = 0;
    if (shipCount == 5)
    {
        x = 5;
        points[4]->setPosition(x - 25, y - 25);
    }
    if (shipCount == 6)
    {
        points[4]->setPosition(x + 25, y + 25);
        points[5]->setPosition(x - 25, y - 25);
    }
    
    points[0]->setPosition(x - 5, y - 5);
    points[1]->setPosition(x + 5, y + 5);
    points[2]->setPosition(x - 15, y - 15);
    points[3]->setPosition(x + 15, y + 15);
    
}

void Formation::danheng()
{
    danzong();
    rotatePoints();
}
void Formation::rotatePoints()
{
    for (int i=0; i<points.size(); ++i)
    {
        int x=points[i]->getPosition().x;
        int y=points[i]->getPosition().y;
        points[i]->setPosition(y,x);
    }
}

