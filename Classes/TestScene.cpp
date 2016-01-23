//
//  TestScene.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 11/11/15.
//
//

#include "TestScene.h"
#include "Equip.h"
#include "XMLParser.h"

Scene* TestScene::createScene()
{
    auto scene=TestScene::create();
    
    auto layer=Layer::create();
    
    scene->addChild(layer);
    
    return scene;
}

TestScene::TestScene()
{
//    Sprite* bg=Sprite::create("equip/btxt_flat/001.png");
//    addChild(bg);
//    Equip* zhang1;
//    for (int i=0; i<1000; ++i)
//    {
//        zhang1=Equip::create(i, 1);
//    }
//    
//    EquipPrint::PrintEquipInfo(zhang1);
//    
//    log("asdfasdf");
//    
//    EquipPoolManager::getInstance()->print();
}


