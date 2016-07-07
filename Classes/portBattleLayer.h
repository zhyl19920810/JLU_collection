//
//  portBattleLayer.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/21/15.
//
//

#ifndef __kancolle_alpha__portBattleLayer__
#define __kancolle_alpha__portBattleLayer__

#include "cocos2d.h"

USING_NS_CC;

NS_KCL_BEGIN

class MissionSelectPage;


class PortBattleLayer:public Layer
{
public:
    CREATE_FUNC(PortBattleLayer);
    
    bool init();
    
    void callBack1(Ref* pSender);
    
    void callBack2(Ref* pSender);
    
    void ShowMissionSelectPage(Ref* pSender);
    
    void hideMissionPage();
private:
    Node* parent;
    
    MissionSelectPage * missionPage;
private:
    void initLayer();

};

NS_KCL_END

#endif /* defined(__kancolle_alpha__portBattleLayer__) */
