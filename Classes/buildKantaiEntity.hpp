//
//  buildKantaiEntity.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#ifndef buildKantaiEntity_hpp
#define buildKantaiEntity_hpp

#include "cocos2d.h"
#include "buildKantaiUnit.hpp"
USING_NS_CC;


NS_KCL_BEGIN

class BuildKantaiEntity:public Node
{
public:
    static BuildKantaiEntity* create(factoryBuildingMode mode);
    bool init(factoryBuildingMode mode);
    
    void showEntity();
    void hideEntity();
private:
    void initBg();
    bool hidden;
    Sprite* imgbg;
    Menu* mn;
    
    FuelBuildUnit* fuelUnit;
    SteelBuildUnit* steelUnit;
    AmmoBuildUnit* ammoUnit;
    AlBuildUnit* AlUnit;
    factoryBuildingMode mode;
    
    MenuItemSprite* startBuild;
    Sprite* startBuildUp;
    void setStartBuildVisible(bool bVisible);
    bool canStartBuild();
    void startBuildCallback(Ref* pSender);
    void callback(Ref* pSender);
    void updateButton();

};

NS_KCL_END

#endif /* buildKantaiEntity_hpp */
