//
//  EquipMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/21/16.
//
//

#ifndef EquipMgr_hpp
#define EquipMgr_hpp


#define MAX_NAME_STRING 33
#define MAX_SUPSHIP 19
#include "Singleton.hpp"
#include "loadTxt.hpp"
#include "SystemHeader.h"
#include <string>

class EquipMgr:public Singleton<EquipMgr>
{
    friend class Singleton<EquipMgr>;
    
protected:
    EquipMgr();
    ~EquipMgr();
    
public:
    struct stEquipData
    {
        int equipKey;
        char equipName[MAX_NAME_STRING];
        EquipScope equipScope;
        EquipType equipType;
        bool isPlane;
        int firePower;
        int AviTorpedo;
        int AviBomb;
        int antiAir;
        int antiSubmarine;
        int searchEnemy;
        int hitRate;
        int dodge;
        Shooting_Range range;
        int armor;
        KantaiType supKantaiType[MAX_SUPSHIP];
        
        stEquipData()
        {
            bzero (this, sizeof (*this));
        }
    };
    
    typedef int MAPID;
    typedef stEquipData MAPDATA;
    
    bool loadConf();
    
    static void equipMapTxtFile(const char* aStrArray[],int aArrayLen,void* aArg)
    {
        EquipMgr* map = (EquipMgr*)aArg;
        map->initEquipMap(aStrArray, aArrayLen);
    }
    
    
    void initEquipMap(const char* aStrArray[], int aArrayLen);
    
    const map<MAPID,MAPDATA>* GetEquipMap () {return &equipMap;}
    
    MAPDATA* GetEquipMap(int equipKey)
    {
        auto it=equipMap.find(equipKey);
        if (it!=equipMap.end())
        {
            return &it->second;
        }
        CCASSERT(false,"can not find the equip");
    }
private:
    map<MAPID,MAPDATA>	equipMap;
};


#define sEquipMgr EquipMgr::getInstance()


#endif /* EquipMgr_hpp */

