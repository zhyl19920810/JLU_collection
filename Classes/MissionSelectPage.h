//
//  MissionSelectPage.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/22/15.
//
//

#ifndef __kancolle_alpha__MissionSelectPage__
#define __kancolle_alpha__MissionSelectPage__

#include "cocos2d.h"
#include "MissionContainer.h"
USING_NS_CC;

class MissionSelectPage :public Node
{
public:
    MissionSelectPage(Node *parent);
    
    void moveOut();
    
    void moveIn();
    
    void setCurrentArea(Ref* pSender, int areaId);

    void startMission(Ref* pSender, int index);
    
    inline bool isHidden(){ return Hidden; }
private:
    int currentArea;
    Node* parent;
    Menu *menu;
    bool Hidden;
    MissionContainer *container1, *container2, *container3, *container4;
    
};



#endif /* defined(__kancolle_alpha__MissionSelectPage__) */
