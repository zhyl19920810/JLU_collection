//
//  AnimationMaker.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 5/5/17.
//
//

#ifndef AnimationMaker_hpp
#define AnimationMaker_hpp

#include "SystemHeader.h"

NS_KCL_BEGIN

USING_NS_CC;

class AnimationMaker
{
public:
    static float playPlaneAnimation(float delay);
    static float playAirBattleAnimation(float delay);
    static float playExplodeAnimation(float delay, Point position);
    static float playExplodeAnimation(float delay, Point position,int times);
    static float FlyToCenterLeftAndFadeOut(Node* target,float delay);
    static float FlyToPositionAndFadeOut(Node* target, float delay,Point position,float stayingTime);
    static void makeExplodeAnimation();
    static void playShakingAnimation(Node* target, float delay);
    static void playDamageNumberAnimation(Point position,float delay, bool miss, bool critical, int damage,CallFunc* callback);
    static void InitDamageNumber();
private:
    static bool damageNumberInitialized;
    static std::string int2str(int &);
};

NS_KCL_END


#endif /* AnimationMaker_hpp */
