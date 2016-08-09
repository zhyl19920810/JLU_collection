//
//  KantaiDestroyEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 3/6/16.
//
//

#ifndef KantaiDestroyEntity_hpp
#define KantaiDestroyEntity_hpp


#include "cocos2d.h"
#include "kantaiCard.hpp"
#include "MenuItemTouch.hpp"
#include "unityEntity.hpp"

USING_NS_CC;

NS_KCL_BEGIN

class LayerCover;


class KantaiDestroyEntity:public UnitEntity
{
public:
    static KantaiDestroyEntity* create(Vec2 pos);
    KantaiDestroyEntity();
    void update(Kantai* kantai);
    void destroyCallback(Ref* pSender);
    bool canDestroyKantai(Kantai* kantai);
    
    
private:
    MenuItemButton* destroyButton;
    KantaiCard* kantaiCard;
    
    Label* fuel;
    Label* ammo;
    Label* steel;
    Label* al;
    
    int fuelVal;
    int ammoVal;
    int steelVal;
    int alVal;
    
    
private:
    bool init(Vec2 pos);
    void initTitle();
    void initEntity();
    void initBg();
    void initKantai();
};

NS_KCL_END

#endif /* KantaiDestroyEntity_hpp */
