//
//  PortState.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/19/16.
//
//

#ifndef PortState_hpp
#define PortState_hpp

#include "cocos2d.h"
#include "SystemHeader.h"
#include "ViewMgrMacro.hpp"

NS_KCL_BEGIN

class PortScene;

class PortState
{
public:
    virtual void Enter(PanelType,PortScene*)=0;
    virtual void Exit(PanelType,PortScene*)=0;
    virtual ~PortState(){}
private:
};

class MainPanelState:public PortState
{
public:
    void Enter(PanelType,PortScene*);
    void Exit(PanelType,PortScene*);
};


class PortPanelState:public PortState
{
public:
    void Enter(PanelType,PortScene*);
    void Exit(PanelType,PortScene*);
};

class NullState:public PortState
{
public:
    void Enter(PanelType,PortScene*){}
    void Exit(PanelType,PortScene*){}
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
    
    void changeState(PanelType newType);
    PortState* getState(PanelType newType);
    
    void revertToPreviousState()
    {
        //changeState(m_pPreviousState);
    }
    
    
private:
    PortScene* owner;
    PortState* m_pPreviousState;
    PortState* m_pCurrentState;
    PortPanelState portPanelState;
    MainPanelState mainPanelState;
    NullState      nullState;
};


NS_KCL_END



#endif /* PortState_hpp */
