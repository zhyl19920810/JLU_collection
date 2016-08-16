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
#include "Panel.hpp"

using namespace cocos2d;

class LayerCover;


NS_KCL_BEGIN

class KantaiDestroyEntity;

class PortFactoryLayer : public Panel
{
    friend class KantaiDestroyEntity;
public:
    PortFactoryLayer();
    CREATE_FUNC(PortFactoryLayer);
private:
    bool init();
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
    void showList(int position);
private:
    void initContainer();
    void buildCallback(Ref* pSender);
    
    std::vector<FactoryContainer*> container;
    BuildKantaiEntity* entity;
    //destroy
public:
    void showSelect(Kantai* kantai);
    void showDestroy(Ref* pSender);
    void finishBuildingKantai(int position);
    
private:
    void destroyKantai(Kantai* kantai,int fuel,int steel,int ammo,int al);
    void destroyCallback(Kantai* kantai,int fuel,int steel,int ammo,int al);
    void initDestroyShipEntity();
    FactoryListEntity* destoryList;
    KantaiDestroyEntity* kantaiDestroyEntity;
    
    
    
    //other
private:
    void NullCallback(Ref* pSender);
    int arsenalPosition;
};


NS_KCL_END

#endif /* defined(__kancolle_alpha__portFactoryLayer__) */
