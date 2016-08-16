//
//  TimeUtil.cpp
//  kancolle_beta
//
//  Created by 岩林张 on 8/15/16.
//
//

#include "TimeUtil.hpp"
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <ratio>


NS_KCL_BEGIN


uint64_t TimeUtil::m_beginTimeStamp = TimeUtil::getLocalTimestamp();
std::chrono::steady_clock::time_point TimeUtil::m_beginTimePoint = std::chrono::steady_clock::now();


uint64_t TimeUtil::getTimestamp()
{
    uint64_t seconds=0;
    std::chrono::steady_clock::time_point _endTimePoint = std::chrono::steady_clock::now();
    seconds = std::chrono::duration_cast<std::chrono::seconds>(_endTimePoint - m_beginTimePoint).count();
    
    return m_beginTimeStamp+seconds;
}

uint64_t TimeUtil::getLocalTimestamp()
{
    return std::time(nullptr);
}


void TimeUtil::setTimestamp(uint64_t timestamp)
{
    m_beginTimePoint = std::chrono::steady_clock::now();
    m_beginTimeStamp = timestamp;
}

std::tm TimeUtil::getTime()
{
    std::time_t _timestamp = getTimestamp();
    return *std::localtime(&_timestamp);
}


NS_KCL_END