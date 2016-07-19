//
//  ViewMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#ifndef ViewMgr_hpp
#define ViewMgr_hpp

#include "ViewMgrMacro.hpp"
#include "Panel.hpp"
#include "cocos2d.h"
#include <deque>

NS_KCL_BEGIN
#define VIEW_MGR (ViewMgr::getInstance())


class ViewMgr:cocos2d::Ref
{
public:
    struct PanelStruct
    {
        PanelType		type;
        Panel*  		panel = nullptr;
        cocos2d::Value	data = cocos2d::Value::Null;
        bool			needCrossDay = false;
    };
    
    struct SceneStruct
    {
        SceneType		type;
        cocos2d::Scene*		scene = nullptr;
        cocos2d::Value	data = cocos2d::Value::Null;
        bool			needCrossDay = false;
        std::deque<PanelStruct>	panelQueue;
    };
    
    static ViewMgr* getInstance();
    static void destory();
    
    cocos2d::Scene* showScene(SceneType sceneType,bool replaceScene=true,const cocos2d::Value& data=cocos2d::Value::Null);
    Panel* showPanel(PanelType panelType,bool replacePanel=true,bool prePanelVisible=false,const cocos2d::Value& data=cocos2d::Value::Null);
    
    cocos2d::Scene* popScene();
    
    cocos2d::Scene* getScene(SceneType sceneType);
    Panel* getPanel(PanelType layerType);
private:
    ViewMgr();
    
    cocos2d::Director* m_director;
    std::deque<SceneStruct> sceneStack;
    
    PanelType currPanelType;
};


NS_KCL_END


#endif /* ViewMgr_hpp */
