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



class PortState
{
public:
    virtual void Enter(LayerType,PortScene*)=0;
    virtual void Exit(LayerType,PortScene*)=0;
    virtual ~PortState(){}
private:
};

class MainLayerState:public PortState
{
public:
    void Enter(LayerType,PortScene*);
    void Exit(LayerType,PortScene*);
};


class PortLayerState:public PortState
{
public:
    void Enter(LayerType,PortScene*);
    void Exit(LayerType,PortScene*);
};

class NullState:public PortState
{
public:
    void Enter(LayerType,PortScene*){}
    void Exit(LayerType,PortScene*){}
};
//class SoundLayerState:public PortState
//{
//public:
//
//};


class PortStateMachine
{
public:
    PortStateMachine(PortScene* _owner);
    
    void setCurrentState(PortState* s){m_pCurrentState=s;}
    void setPreviousState(PortState* s){m_pPreviousState=s;}
    
    void changeState(LayerType newType);
    PortState* getState(LayerType newType);
    
    void revertToPreviousState()
    {
        //changeState(m_pPreviousState);
    }
    
    
private:
    PortScene* owner;
    PortState* m_pPreviousState;
    PortState* m_pCurrentState;
    PortLayerState portLayerState;
    MainLayerState mainLayerState;
    NullState      nullState;
};









class PortScene:public Scene
{
    friend class GameManger;
public:
    static PortScene* createScene();
    
    PortScene();
    ~PortScene();
    void SetCurrLayer(LayerType type);
    LayerType getCurrLayerType() const;
    
    CREATE_FUNC(PortScene);
    
    
    void pauseLayerSelecterButton();
    void resumeLayerSelecterButton();
private:
    bool init() override;

public:
    LayerType currentLayerType;
    LayerSelecter* layerSelecter;
    PortUILayer* portUIlayer;
    PortBgLayer* portBgLayer;
    PortStateMachine portStateMachine;
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portScene__) */
