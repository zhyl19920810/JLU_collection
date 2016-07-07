//
//  arsenalDB.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 2/1/16.
//
//

#ifndef arsenalDB_hpp
#define arsenalDB_hpp

#include "cocos2d.h"
#include "databaseBase.h"

USING_NS_CC;

NS_KCL_BEGIN

typedef struct
{
    int kantaiNumber;
    int position;
    int completeTime;
}ArsenalDBData;


class ArsenalDB:public DBBase
{
public:
    void initArsenalDB(int playerKey,std::vector<ArsenalDBData>& data);
    
    void insertKantai(int playerKey,int kantaiNumber,int position,int buildTime);
    
    void deleteKantai(int playerKey,int position);
    
    static ArsenalDB* getInstance();
protected:
    ArsenalDB();
private:
    static ArsenalDB* arsenalDB;
};

#define sArsenalDB ArsenalDB::getInstance()

NS_KCL_END

#endif /* arsenalDB_hpp */
