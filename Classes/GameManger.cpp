//
//  GameManger.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#include "GameManger.hpp"

GameManger::GameManger():
pSallyScene(NULL),
pGameScene(NULL)
{
    LoadResource();
}

GameManger::~GameManger()
{
    ClearResource();
}

void GameManger::LoadConfig()
{
    KantaiMgr::newInstance();
    EquipMgr::newInstance();
    ExpMgr::newInstance();
    sKantaiMgr.loadConf();
    sEquipMgr.loadConf();
    sExpMgr.loadConf();
}

void GameManger::LoadResource()
{
    ///需要全程加载的东西
}

void GameManger::ClearResource()
{
    //释放需要全程加载的东西
}