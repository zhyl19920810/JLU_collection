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


class EquipMgr:public Singleton<EquipMgr>
{
    friend class Singleton<EquipMgr>;
    
protected:
    EquipMgr();
    ~EquipMgr();
    
public:
    struct stEquipData
    {
        int equipNumber;
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
        int range;
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
    
    const map<MAPID,stEquipData>* GetEquipMap () {return &equipMap;}
    
    
private:
    map<MAPID,MAPDATA>	equipMap;
};


#define sEquipMgr EquipMgr::getInstance()


#endif /* EquipMgr_hpp */

