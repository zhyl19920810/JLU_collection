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
class PortScene;


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



template <class entity_type>
class State
{
public:
    virtual void Enter(entity_type*)=0;
    virtual void Execute(entity_type*)=0;
    virtual void Exit(entity_type*)=0;
    virtual ~State(){}
private:
};

class SoundLayerState:public State <PortScene>
{
public:
    
};

class MainLayerState:public State<PortScene>
{
public:
    
};


class SelecterLayerState:public State<PortScene>
{
public:
    
};


template<class entity_type>
class StateMachine
{
public:
    void setCurrentState(State<entity_type>* s){m_pCurrentState=s;}
    void setPreviousState(State<entity_type>* s){m_pPreviousState=s;}
    
    void changeState(State<entity_type*> pNewState)
    {
        m_pPreviousState=m_pCurrentState;
        m_pCurrentState->Exit();
        m_pCurrentState=pNewState;
        pNewState->Enter();
    }
    
    void revertToPreviousState()
    {
        changeState(m_pPreviousState);
    }
    
    
private:
    State<entity_type*> m_pPreviousState;
    State<entity_type*> m_pCurrentState;
    
};




class PortUILayer:public Layer
{
public:
    PortUILayer();
    
    
    CREATE_FUNC(PortUILayer);
    
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
    
    void menuHandlingCallback(Ref* pSender);
    void changeFurnitureCallback(Ref* psSender);
    void startCircle();
    void endCircle();
    void update(float dt) override;
    
private:
    bool init() override;
    
    
private:
    Sprite *black;
    
    
    LayerType currentLayerType;
    Layer* currentLayer;
    PortMainLayer *mainlayer;
    PortFactoryLayer *factroylayer;
    PortOrganizeLayer *organizelayer;
    PortRemodeLayer *remodelayer;
    PortRepairLayer *repairlayer;
    PortSupplyLayer *supplylayer;
    PortBattleLayer *battlelayer;
    
    
    
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


class PortBgLayer:public Layer
{
public:
    CREATE_FUNC(PortBgLayer);
    
    
private:
    bool init() override;
    Sprite *bgImage;
    
};




class PortScene:public Scene
{
    friend class GameManger;
public:
    static PortScene* createScene();
    
    PortScene();
    ~PortScene();
    void SetCurrLayer(LayerType type);
    CREATE_FUNC(PortScene);
    
    
    void pauseLayerSelecterButton();
    void resumeLayerSelecterButton();
private:
    bool init() override;

public:
    LayerSelecter* layerSelecter;
    PortUILayer* portUIlayer;
    PortBgLayer* portBgLayer;
};



#endif /* defined(__kancolle_alpha__portScene__) */
