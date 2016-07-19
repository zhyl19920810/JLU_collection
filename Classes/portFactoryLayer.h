//
//  portFactoryLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portFactoryLayer__
#define __kancolle_alpha__portFactoryLayer__

#include "cocos2d.h"
#include "FactoryContainer.hpp"
#include "arsenal.hpp"
#include "Player.h"
#include "buildKantaiEntity.hpp"
#include "FactoryListEntity.hpp"
#include "LayerCover.hpp"
#include "Panel.hpp"

using namespace cocos2d;

NS_KCL_BEGIN

class PortFactoryLayer : public Panel
{
public:
    PortFactoryLayer();
    CREATE_FUNC(PortFactoryLayer);
    
    bool init();
    
private:
    
private:
    //bg
    void initLayer();
    Sprite* bgimg;
    Sprite* arsenalBg;
    Menu* menu;
    
    
    //build
public:
    FactoryContainer* getContainer(int position);
    
    void startBuild(int fuel,int steel,int ammo,int al);
    void destroyKantai(Kantai* kantai,int fuel,int steel,int ammo,int al);
    
    void showDestroy(Ref* pSender);
    void hideDestroy(Ref* pSender);
    void hideList(Ref* pSender);
    void showList(int position);
private:
    BuildKantaiEntity* entity;
    FactoryListEntity* destoryList;
    void initContainer();
    std::vector<FactoryContainer*> container;
    void buildCallback(Ref* pSender);
    //void callBack(Ref* pSender);
    
    
    
    void NullCallback(Ref* pSender);
    
    LayerCover* destoryCover;
    LayerCover* listCover;
    
};


NS_KCL_END

#endif /* defined(__kancolle_alpha__portFactoryLayer__) */
