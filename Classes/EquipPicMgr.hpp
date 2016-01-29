//
//  EquipPicMgr.hpp
//  kancolle_beta
//
//  Created by 岩林张 on 1/28/16.
//
//

#ifndef EquipPicMgr_hpp
#define EquipPicMgr_hpp


#include "loadTxt.hpp"
#include "Singleton.hpp"
#include <map>


#define MAX_EQUIP_NAME 50



class EquipPicMgr:public Singleton<EquipPicMgr>
{
    friend class Singleton<EquipPicMgr>;
    
    
protected:
    EquipPicMgr();
    ~EquipPicMgr();
    

public:
    struct stEquipPicData
    {
        char resource[MAX_EQUIP_NAME];
        stEquipPicData()
        {
            bzero (this, sizeof (*this));
        }
    };
    typedef int MAPID;
    typedef stEquipPicData MAPDATA;
    
    bool loadConf();
    
    static void equipPicTxtFile(const char* aStrArray[],int aArrayLen,void* aArg)
    {
        EquipPicMgr* map = (EquipPicMgr*)aArg;
        map->initEquipPic(aStrArray, aArrayLen);
    }
    void initEquipPic(const char* aStrArray[], int aArrayLen);
    
    stEquipPicData* getEquipPicMap(int equipNumber);
    
private:
    std::map<MAPID,MAPDATA> equipPicMap;
};


#define sEquipPicMgr EquipPicMgr::getInstance()



#endif /* EquipPicMgr_hpp */
