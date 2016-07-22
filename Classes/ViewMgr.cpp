//
//  ViewMgr.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#include "ViewMgr.hpp"
#include "ViewMgrFactory.hpp"


NS_KCL_BEGIN

ViewMgr::ViewMgr()
{
    m_director=cocos2d::Director::getInstance();
    currPanelType=PanelType::NONE;
}


ViewMgr* ViewMgr::getInstance()
{
    static ViewMgr m_viewMgr;
    return &m_viewMgr;
}


cocos2d::Scene* ViewMgr::showScene(SceneType sceneType,bool replaceScene,const cocos2d::Value& data)
{
    cocos2d::Scene* _scene=ViewMgrFactory::getScene(sceneType);
    _scene->setTag(static_cast<int>(sceneType));
    if (!m_director->getRunningScene())
    {
        SceneStruct sceneStruct;
        sceneStruct.type=sceneType;
        sceneStruct.scene=_scene;
        sceneStruct.data=data;
        sceneStack.push_front(sceneStruct);
        m_director->runWithScene(_scene);
    }
    else
    {
        if (replaceScene)
        {
            auto queue=sceneStack.begin()->panelQueue;
            for (auto it=queue.begin(); it!=queue.end(); ++it)
            {
                if (currPanelType==it->type) {
                    currPanelType=PanelType::NONE;
                }
            }
            sceneStack.pop_front();
            m_director->replaceScene(_scene);
        }
        else
        {
            m_director->pushScene(_scene);
        }
        SceneStruct sceneStruct;
        sceneStruct.type=sceneType;
        sceneStruct.scene=_scene;
        sceneStruct.data=data;
        sceneStack.push_front(sceneStruct);
    }
    return _scene;
}

Panel* ViewMgr::showPanel(PanelType panelType,bool replaceScene,bool prePanelVisible,const cocos2d::Value& data)
{
    if (panelType==currPanelType||panelType==PanelType::NONE) {
        return ViewMgrFactory::getPanel(panelType);
    }
    
    Panel* prePanel=getPanel(currPanelType);
    if (replaceScene)
    {
        if (prePanel)
        {
            sceneStack.begin()->scene->removeChild(prePanel);
            auto& queue=sceneStack.begin()->panelQueue;
            for (auto it=queue.begin(); it!=queue.end(); ++it)
            {
                if (currPanelType==it->type)
                {
                    queue.erase(it);
                    break;
                }
            }
        }
    }
    else
    {
        prePanel->setVisible(prePanelVisible);
    }
    
    
    Panel* _panel=getPanel(panelType);
    if (!_panel)
    {
        _panel=ViewMgrFactory::getPanel(panelType);
        _panel->setTag(static_cast<int>(panelType));
        PanelStruct layerStruct;
        layerStruct.type=panelType;
        layerStruct.data=data;
        layerStruct.panel=_panel;
        sceneStack.begin()->panelQueue.push_front(layerStruct);
        sceneStack.begin()->scene->addChild(_panel);
    }
    _panel->setVisible(true);
    
    currPanelType=panelType;
    
    return _panel;
}

cocos2d::Scene* ViewMgr::popScene()
{
    auto queue=sceneStack.begin()->panelQueue;
    for (auto it=queue.begin(); it!=queue.end(); ++it)
    {
        if (currPanelType==it->type) {
            currPanelType=PanelType::NONE;
        }
    }
    cocos2d::Director::getInstance()->popScene();
    sceneStack.pop_front();
    return m_director->getRunningScene();
}


cocos2d::Scene* ViewMgr::getScene(kancolle::SceneType sceneType)
{
    if (sceneType==SceneType::HOME)
    {
        return NULL;
    }
    for (auto it=sceneStack.begin(); it!=sceneStack.end(); ++it)
    {
        if (it->type==sceneType)
        {
            return it->scene;
        }
    }
    return NULL;
}

Panel* ViewMgr::getPanel(kancolle::PanelType panelType)
{
    if (sceneStack.empty()||panelType==PanelType::NONE)
    {
        return NULL;
    }
    
    auto panelQueue=sceneStack.begin()->panelQueue;
    for (auto it=panelQueue.begin(); it!=panelQueue.end(); ++it)
    {
        if (it->type==panelType)
        {
            return it->panel;
        }
    }

    return NULL;
}




NS_KCL_END