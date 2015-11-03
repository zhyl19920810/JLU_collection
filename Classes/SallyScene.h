//
//  SallyScene.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#ifndef __kancolle_alpha__SallyScene__
#define __kancolle_alpha__SallyScene__

#include "cocos2d.h"
#include "Mission.h"
#include "Compass.h"
#include "Formation.h"



USING_NS_CC;

enum SallyStatus{
    sally_start,
    sally_move,
    sally_formation,
    sally_battle,
};

class SallyScene:public Scene
{
public:
    SallyScene(Mission* mission);
    
    void setFormationCallback(Ref* pSender, FormationType formation);
    
    
    
    
private:
    SallyStatus status;
    
    Mission* mission;
    MissionNode* currentMissionNode;

    Sprite* bgImg;
    Sprite* sallyMap;
    Compass * bottomCompass;
    Sprite* bottomBorder;
    Label* bottomLabel;
    Sprite* temptimer;
    Sprite* ship;
    Sprite *flagShip;
    
    std::vector<Formation*> formations;
    
    bool showingBottomPanel;
    
    Sprite* nodePointShader;
    
    void initializeFormationPanel();
private:
    void sallyStart();
    void sallyMove();
    void sallyBattle();
    void sallyFormation();
    void sallyFinish();
    void onStatusOverCallBack();
    void nextStatus(float DelayTime);
    
private://Bottom Panel
    void hideBottomPanel();
    void showBottomPanel();
};


#endif /* defined(__kancolle_alpha__SallyScene__) */
