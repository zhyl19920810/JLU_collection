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
public:
    static PortScene* createScene();
    
    void SetCurrLayer(LayerType type);
    
    bool init();
    
    void menuSettingCallback(Ref* pSender);
    
    void menuHandlingCallback(Ref* pSender);
    
    void changeFurnitureCallback(Ref* psSender);
    
private:
    PortScene();
    
    
    
    Sprite *black;
    
    LayerSelecter *layerSelecter;
    LayerType currentLayerType;
    Layer* currentLayer;
    PortMainLayer *mainlayer;
    PortFactoryLayer *factroylayer;
    //PortOrganizeLayer *organizelayer;
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
