//
//  TestScene.h
//  kancolle_beta
//
//  Created by 岩林张 on 11/11/15.
//
//

#ifndef __kancolle_beta__TestScene__
#define __kancolle_beta__TestScene__

#include "cocos2d.h"

USING_NS_CC;

class TestScene:public Scene
{
public:
    static Scene* createScene();
    
    CREATE_FUNC(TestScene);
    
    TestScene();
private:
};



#endif /* defined(__kancolle_beta__TestScene__) */
