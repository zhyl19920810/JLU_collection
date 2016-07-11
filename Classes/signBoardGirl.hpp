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
    
    
private:
    bool init() override;
    
    cocos2d::Sprite* girl;
};

NS_KCL_END


#endif /* signBoardGirl_hpp */
