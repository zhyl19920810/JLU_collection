//
//  equipDB.h
//  kancolle_alpha
//
//  Created by 岩林张 on 10/11/15.
//
//

#ifndef __kancolle_alpha__equipDB__
#define __kancolle_alpha__equipDB__

#include "cocos2d.h"
#include "databaseBase.h"

using namespace cocos2d;

#define sEquipDB EquipDB::getInstance()

class EquipDB:public DBBase
{
public:
    int getNewEquipByNumber(int equipNumber,int kantaiKey=-1,int position=0);
    
    void deleteEquipKey(int equipKey,bool InKantai);
    
    void deleteEquipRelation(int equipKey);
    
    void changeEquipPosition(int _equipKey, int _kantaiKey, int _position);
    
    
    static EquipDB* getInstance();
protected:
    EquipDB();
    
private:
    static EquipDB* equipDB;
};



#endif /* defined(__kancolle_alpha__equipDB__) */
