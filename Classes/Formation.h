//
//  Formation.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#ifndef __kancolle_beta__Formation__
#define __kancolle_beta__Formation__

#include "cocos2d.h"
#include "BattleModel.h"

NS_KCL_BEGIN

class SallyScene;
USING_NS_CC;

#define MAX_SHIPS_PER_FLEET 6

class Formation:public Node
{
public:
    Formation(int shipCount,FormationType type,bool enemy=false);
    Formation(FormationType type,SallyScene* parent);
    
    
    void intializePanel(SallyScene* parentSallyScene);
    FormationType getType();
    void addBattleBorder();
    void showPoints();
    void hidePoints();
    void rotatePoints();
    
private:
    void organizePoints();
    void danzong();
    void fuzong();
    void tixing();
    void danheng();
    void lunxing();
    
    
private:
    
    std::string pointUrl;
    FormationType type;
    int shipCount;
    Sprite* border;
    std::vector<Sprite*> points;
    
    
    Sprite* panelBg;
    MenuItemImage* button;
    SallyScene *parentSallyScene;
    
    
    
};

NS_KCL_END



#endif /* defined(__kancolle_beta__Formation__) */
