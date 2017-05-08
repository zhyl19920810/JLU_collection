//
//  SallyScene.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/3/17.
//
//

#ifndef SallyScene_hpp
#define SallyScene_hpp

#include "SystemHeader.h"

NS_KCL_BEGIN

USING_NS_CC;

class SallyScene:public Scene
{
public:
    static SallyScene* create();

    
private:
    bool init();
};

NS_KCL_END


//#include "cocos2d.h"
//#include "GameModel.hpp"
//#include "formation.h"
//using namespace cocos2d;

//enum SallyStatus{
//    sally_start,
//    sally_move,
//    sally_formation,
//    sally_battle,
//};
//
//
//class SallyScene : public Scene{
//public:
//    SallyScene(Mission* mission);
//    void setFormationCallback(Ref* pSender, FormationType formation);
//private:
//    
//    SallyStatus status;
//    
//    
//    Mission* mission;
//    MissionNode* currentMissionNode;
//    
//    Sprite* bgImg;
//    Sprite* sallyMap;
//    Compass * bottomCompass;
//    Sprite* bottomBorder;
//    Label* bottomLabel;
//    Sprite* temptimer;
//    Sprite* ship;
//    Sprite *flagShip;
//    
//    bool showingBottomPanel;
//    
//    Sprite* nodePointShader;
//    
//    std::vector<Formation*> formations;
//    void initializeFormationPanel();
//private:
//    void sallyStart();
//    void sallyMove();
//    void sallyBattle();
//    void sallyFormation();
//    void sallyFinish();
//    void onStatusOverCallBack();
//    void nextStatus(float DelayTime);
//    
//private://Bottom Panel
//    void hideBottomPanel();
//    void showBottomPanel();
//    
//    
//};









#endif /* SallyScene_hpp */
