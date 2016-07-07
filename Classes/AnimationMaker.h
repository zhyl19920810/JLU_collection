//
//  AnimationMaker.h
//  kancolle_beta
//
//  Created by 岩林张 on 10/24/15.
//
//

#ifndef __kancolle_beta__AnimationMaker__
#define __kancolle_beta__AnimationMaker__

#include "cocos2d.h"
#include "SystemHeader.h"


USING_NS_CC;


NS_KCL_BEGIN

class AnimationMaker
{
public:
    static float playPlaneAnimation(Node* parent,float delay);
    
    static float playAirBattleAnimation(Node* parent,float delay);
    
    static float playExplodeAnimation(Node* parent,float delay,Point position);
    
    static float playExplodeAnimation(Node* parent, float delay, Point position,int times);
    
    static float FlyToCenterLeftAndFadeOut(Node* target,float delay);
    
    static float FlyToPositionAndFadeOut(Node* target, float delay,Point position,float stayingTime);
    
    static void makeExplodeAnimation();
    
    static void playShakingAnimation(Node* target, float delay);
    
    static void playDamageNumberAnimation(Point position, Node*parent, float delay, bool miss, bool critical, int damage,CallFunc* callback);
    
    static void InitDamageNumber();
    
private:
    static bool damageNumberInitialized;
};

NS_KCL_END

#endif /* defined(__kancolle_beta__AnimationMaker__) */
