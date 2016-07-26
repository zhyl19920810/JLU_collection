//
//  signBoardGirl.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/8/16.
//
//

#ifndef signBoardGirl_hpp
#define signBoardGirl_hpp

#include "cocos2d.h"
#include "SystemHeader.h"

NS_KCL_BEGIN




class SignBoardGirl:public cocos2d::Node
{
public:
    SignBoardGirl();
    
    
    static SignBoardGirl* create();
    void updateGirl(cocos2d::Sprite* sprite=NULL);
    void setEnable();
    void setDisable();
    
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    bool init() override;
    
    cocos2d::Sprite* girl;
    cocos2d::EventListenerTouchOneByOne* _eventListner;
};

NS_KCL_END


#endif /* signBoardGirl_hpp */
