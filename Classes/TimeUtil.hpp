//
//  TimeUtil.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/15/16.
//
//

#ifndef TimeUtil_hpp
#define TimeUtil_hpp

#include "cocos2d.h"
#include "SystemHeader.h"


NS_KCL_BEGIN

class TimeUtil
{
public:
    static uint64_t getTimestamp();
    
    static uint64_t getLocalTimestamp();
    
    static void setTimestamp(uint64_t timestamp);
    
    static std::tm getTime();
    
private:
    static uint64_t m_beginTimeStamp;
    static std::chrono::steady_clock::time_point m_beginTimePoint;
};





NS_KCL_END


#endif /* TimeUtil_hpp */
