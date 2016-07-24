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
class SoundPanelButton;



class PortScene:public Scene
{
    friend class MainPanelState;
    friend class PortPanelState;
    friend class SoundPanelState;
public:
    static PortScene* createScene();
    CREATE_FUNC(PortScene);
    PortScene();
    ~PortScene();
    
    
    
public:
    void SetCurrPanel(PanelType type);
    PanelType getCurrPanelType() const;
    void changeToSoundPanel();
    void updateUILayerAttr();
    
private:
    bool init() override;
    void initSoundButton();

private:
    bool openSoundPanel;
    PanelType currentPanelType;
    PortStateMachine portStateMachine;
    LayerSelecter* layerSelecter;
    PortUILayer* portUIlayer;
    PortBgLayer* portBgLayer;
    SoundPanelButton* soundButton;
    
private:
    void initBlurGLprogram();
    cocos2d::GLProgramState* blurGLProgramState=NULL;
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portScene__) */
