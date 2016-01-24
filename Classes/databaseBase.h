//
//  databaseBase.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#ifndef __kancolle_alpha__databaseBase__
#define __kancolle_alpha__databaseBase__

#include "cocos2d.h"
#include "sqlite3.h"

using namespace cocos2d;

class DBBase
{
public:
    static void init(const std::string &pathName);
    static void end();
    
    
protected:
    static sqlite3* kancolleDB;
    
};


class DateUtils
{
public:
    // 格式化时间返回
    static std::string getCurrentTime(const char* format);
    // 获取系统毫秒时间
    static double getMillSecond();
    
};




#endif /* defined(__kancolle_alpha__databaseBase__) */
