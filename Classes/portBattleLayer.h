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

class MissionSelectPage;


class PortBattleLayer:public Layer
{
public:
    PortBattleLayer(Node* parent);
    
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


#endif /* defined(__kancolle_alpha__portBattleLayer__) */
