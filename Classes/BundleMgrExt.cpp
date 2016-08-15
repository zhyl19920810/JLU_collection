//
//  BundleMgrExt.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/5/16.
//
//

#include "portScene.h"
#include "ViewMgr.hpp"
#include "portScene.h"
#define CACHE (UserDefault::getInstance())

NS_KCL_BEGIN

void exeLaunch()
{
    auto scene=dynamic_cast<PortScene*>(VIEW_MGR->showScene(SceneType::HOME));
    scene->SetCurrPanel(PanelType::PORT_MAINLAYER);
}


NS_KCL_END
