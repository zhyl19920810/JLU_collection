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
#include "SystemHeader.h"
#include "ViewMgrMacro.hpp"
#include "PortState.hpp"


USING_NS_CC;


NS_KCL_BEGIN

class LayerSelecter;
class PortMainLayer;
class PortSupplyLayer;
class PortFactoryLayer;
class PortRepairLayer;
class PortRemodeLayer;
class PortBattleLayer;
class PortOrganizeLayer;
class PortScene;
class PortUILayer;
class PortBgLayer;



class PortScene:public Scene
{
    friend class GameManger;
public:
    static PortScene* createScene();
    
    PortScene();
    ~PortScene();
    void SetCurrPanel(PanelType type);
    PanelType getCurrPanelType() const;
    
    CREATE_FUNC(PortScene);
    
    
    void pauseLayerSelecterButton();
    void resumeLayerSelecterButton();
private:
    bool init() override;

public:
    PanelType currentPanelType;
    LayerSelecter* layerSelecter;
    PortUILayer* portUIlayer;
    PortBgLayer* portBgLayer;
    PortStateMachine portStateMachine;
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portScene__) */
