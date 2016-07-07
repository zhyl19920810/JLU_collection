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
    currLayerType=LayerType::NONE;
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
            auto queue=sceneStack.begin()->layerQueue;
            for (auto it=queue.begin(); it!=queue.end(); ++it)
            {
                if (currLayerType==it->type) {
                    currLayerType=LayerType::NONE;
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

cocos2d::Layer* ViewMgr::showLayer(LayerType layerType,bool replaceScene,bool preLayerVisible,const cocos2d::Value& data)
{
    cocos2d::Layer* _layer=getLayer(layerType);
    if (!_layer)
    {
        _layer=ViewMgrFactory::getLayer(layerType);
        _layer->setTag(static_cast<int>(layerType));
    }
    _layer->setVisible(true);
    if (replaceScene)
    {
        cocos2d::Layer* preLayer=getLayer(currLayerType);
        if (preLayer)
        {
            sceneStack.begin()->layerQueue.pop_front();
            sceneStack.begin()->scene->removeChild(preLayer);
        }
    }
    else
    {
        _layer->setVisible(preLayerVisible);
    }
    LayerStruct layerStruct;
    layerStruct.type=layerType;
    layerStruct.data=data;
    layerStruct.layer=_layer;
    sceneStack.begin()->layerQueue.push_front(layerStruct);
    sceneStack.begin()->scene->addChild(_layer);
    currLayerType=layerType;
    
    return _layer;
}

cocos2d::Scene* ViewMgr::popScene()
{
    auto queue=sceneStack.begin()->layerQueue;
    for (auto it=queue.begin(); it!=queue.end(); ++it)
    {
        if (currLayerType==it->type) {
            currLayerType=LayerType::NONE;
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

cocos2d::Layer* ViewMgr::getLayer(kancolle::LayerType layerType)
{
    if (layerType==LayerType::NONE)
    {
        return NULL;
    }
    for (auto it=sceneStack.begin(); it!=sceneStack.end(); ++it)
    {
        auto layerQueue=it->layerQueue;
        for (auto it2=layerQueue.begin(); it2!=layerQueue.end(); ++it2)
        {
            if (it2->type==layerType)
            {
                return it2->layer;
            }
        }
    }
    return NULL;
}




NS_KCL_END