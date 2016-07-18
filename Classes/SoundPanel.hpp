//
//  SoundPanel.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 7/16/16.
//
//

#ifndef SoundPanel_hpp
#define SoundPanel_hpp

#include "cocos2d.h"
#include "SystemHeader.h"
#include "Panel.hpp"


NS_KCL_BEGIN


class SoundPanel:public Panel
{
public:
    CREATE_FUNC(SoundPanel);
    
private:
    bool init();
};

NS_KCL_END


#endif /* SoundPanel_hpp */
