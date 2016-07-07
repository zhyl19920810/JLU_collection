//
//  DatabaseScene.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 7/30/15.
//
//

#include "DatabaseScene.h"
#include "Equip.h"
#include "kantai.h"
#include "databaseBase.h"
#include "databaseInit.h"
#include <time.h>

NS_KCL_BEGIN

Scene* DatabaseLayer::createScene()
{
    Scene* scene=Scene::create();
    
    Layer* layer=DatabaseLayer::create();
    
    scene->addChild(layer);
    
    return scene;
    
}


bool DatabaseLayer::init()
{
    
    if(!Layer::init())
    {
        CCASSERT(false, "database layer init fall");
        return false;
    }
    
    
    InitButton();
    
    
    return true;
    
}



void DatabaseLayer::InitButton()
{
    
    Label* label1=Label::createWithTTF("insert database", FONT_ADDRESS, 30);
    MenuItemLabel* menuItem1=MenuItemLabel::create(label1, CC_CALLBACK_1(DatabaseLayer::InsertDatabaseCallback, this));
    
    
    Label* label2=Label::createWithTTF("read database", FONT_ADDRESS, 30);
    MenuItemLabel* menuItem2=MenuItemLabel::create(label2, CC_CALLBACK_1(DatabaseLayer::ReadDatabaseCallback, this));
    

    Label* label3=Label::createWithTTF("data in database to XML", FONT_ADDRESS, 30);
    MenuItemLabel* menuItem3=MenuItemLabel::create(label3, CC_CALLBACK_1(DatabaseLayer::DataToXML, this));
    
    Menu* mn=Menu::create(menuItem1,menuItem2,menuItem3, NULL);
    mn->alignItemsVertically();
    addChild(mn);
}


std::string DateUtils::getCurrentTime(const char *format)
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    
    struct tm *tm = localtime(&tv.tv_sec);
    
    char currentTime[128];
    strftime(currentTime, 128, format, tm);
    
    log("CurrentTime %s", currentTime);
    
    return currentTime;
}

double DateUtils::getMillSecond()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    
    log("CurrentTime MillSecond %f", (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000);
    
    return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
}



void DatabaseLayer::ReadDatabaseCallback(Ref* pSender)
{
    
//    DBBase::init("/Volumes/opengl/kancolle_alpha/Resources/database/kancolle_2.sqlite3");
//    DBInit init;
//    //double start=DateUtils::getMillSecond();
//    auto player=init.initDB(1);
//    
////    LogPlayer::logPlayerData(player);
//////    auto fleet=player->findFleetByFleetKey(2);
//////    fleet->setFleetName("Fleet2");
//////    fleet->setFleetState(KANTAI_ATTACK);
////    
////    LogPlayer::logPlayerData(player);
//    
//    //double end=DateUtils::getMillSecond();
//    
//    //log("time is %f ms",end-start);
//    //log("time is %lu",end-start);
//    
//    DBBase::end();
}



//void DatabaseLayer::InsertDatabaseCallback(Ref* pSender)
//{
//    Equip zhang=Equip(1);
//    EquipPrint print;
//    print.PrintEquipInfo(zhang);
//}
void DatabaseLayer::InsertDatabaseCallback(Ref* pSender)
{
   // databaseImp::getNewKantaiByNumber(21);
}


void DatabaseLayer::DataToXML(Ref* pSender)
{
    
    
    
}

NS_KCL_END