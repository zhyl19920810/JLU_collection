//
//  portScene.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portScene__
#define __kancolle_alpha__portScene__

#include "cocos2d.h"

class LayerSelecter;
class PortMainLayer;
class PortSupplyLayer;
class PortFactoryLayer;
class PortRepairLayer;
class PortRemodeLayer;
class PortBattleLayer;
class PortOrganizeLayer;

USING_NS_CC;

enum LayerType{
    main,
    organize,
    supply,
    remode,
    factory,
    repair,
    battle,
    empty
};


class PortScene:public Scene
{
    friend class GameManger;
public:
    static PortScene* createScene();
    
    PortScene();
    ~PortScene();
    void SetCurrLayer(LayerType type);
    
    bool init() override;
    
    void startCircle();
    void endCircle();
    
    void onEnter() override;
    
    void onExit() override;
    
    void menuSettingCallback(Ref* pSender);
    
    void menuHandlingCallback(Ref* pSender);
    
    void changeFurnitureCallback(Ref* psSender);
    
    CREATE_FUNC(PortScene);
    
    void changeLabelFuel(int fuel)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",fuel);
        labelFuel->setString(name);
    }
    void changeLabelSteel(int steel)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",steel);
        labelSteel->setString(name);
    }
    void changeLabelAmmo(int ammo)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",ammo);
        labelAmmo->setString(name);
    }
    void changeLabelAluminium(int aluminium)
    {
        char name[20];
        bzero(name, sizeof(name));
        sprintf(name, "%d",aluminium);
        labelAluminium->setString(name);
    }
    
    void update(float dt) override;
private:
    
    Sprite *black;
    
    LayerSelecter *layerSelecter;
    LayerType currentLayerType;
    Layer* currentLayer;
    PortMainLayer *mainlayer;
    PortFactoryLayer *factroylayer;
    PortOrganizeLayer *organizelayer;
    PortRemodeLayer *remodelayer;
    PortRepairLayer *repairlayer;
    PortSupplyLayer *supplylayer;
    PortBattleLayer *battlelayer;
    
    Sprite *bgImage;
    
    Label *labelFuel;
    Label *labelSteel;
    Label *labelAmmo;
    Label *labelAluminium;
    
    Sprite *title;
    Label *playerName;
    Label  *playerLevel;
    Label  *playerTitle;
    Label *fleetCount;
    Label *shipCount;
    Label *quickRepairCount;
    Label *devToolCount;
};



#endif /* defined(__kancolle_alpha__portScene__) */
