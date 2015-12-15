//
//  SystemHeader.h
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//

#ifndef __kancolle_alpha__SystemHeader__
#define __kancolle_alpha__SystemHeader__

#include "cocos2d.h"
#include <vector>
#define equilp_type int
#define equilp_iter int
#define plane_load int
#define FONT_ADDRESS "/Volumes/opengl/kancolle_alpha/Resources/fonts/arial.ttf"
#define DATEBASE_ADDRESS "/Volumes/opengl/kancolle_alpha/Resources/database/kancolle_2.sqlite3"




///kantai type
typedef enum
{
    
    Escort=101,  //海防舰
    Destroyer,   //驱逐舰
    Light_Cruiser,    //轻巡洋舰
    Torpedo_Cruiser,  //重雷装巡洋舰
    Heavy_Cruiser,    //重巡洋舰
    Air_Cruiser,    //航空巡洋舰
    Light_Carrier,    //轻空母
    Battle_Cruiser,   //巡洋战舰
    Carrier, //正规航母
    Battleship,//超弩级战舰
    Submarine,//潜水艇
    Diving_Carrier,//潜水空母
    Seaplane_Carrier,//水上机母舰
    Landing_craft,//扬陆舰
    Armor_Carrier,//装甲空母
    Workboat,//工作舰
    Diving_Mothership,//潜水母舰
    Training_Cruiser//练习巡洋舰
    
}KantaiType;

enum Shooting_Range{
    range_long,
    range_mid,
    range_short,
    range_exlong,
    range_non
};

enum BrokenType
{
    normal,
    tiny,
    mid,
    large,
    drown
};
//装备分类
typedef enum
{
    AttackEquip_Radio=130,     //攻击装备与雷达
    Aircraft,                 //舰载机
    SeaPlane,            //水上机
    AntiSubmarineEquip,            //对潜装备
    Intensify_Equip,            //对空机枪与强化设备
    Others,            //其他装备
    Deep_Sea_Equip            //深海装备
}equipScope;

//装备种类
typedef enum
{
    Small_Caliber=140,            //小口径主炮
    Medium_Caliber,            //中口径主炮
    Large_Caliber,            //大口径主炮
    Vice_Gun,            //副炮
    Torpedo,            //鱼雷
    Radar,            //雷达(電探)
    Shell,            //炮弹
    Fighter,            //舰上战斗机
    Bomber,            //舰上轰炸机
    Attacker,            //舰上强击机
    Surv_Aircraft,            //舰上侦察机
    Mari_Bomber,            //水上轰炸机
    Mari_Surv,            //水上侦察机
    Sonar,            //声纳
    Depth_charge,            //深水炸弹
    AntiSubmarine_Aircraft,            //反潜巡逻机
    AntiAir_MachineGun,            //对空机枪
    Engine,            //发动机
    Append_Armor,            //追加装甲
    Repair_Equip,            //修理要员
    AntiAir_Equip,            //高射装置
    OthersType,            //其他装备类型
    Deep_Sea_Type            //深海装备类型
}EquipType;


class NameResolution
{
public:
    static std::string EquipScopeReso(int _equipScope);
    
    static std::string EquipTypeReso(int _equipType);
    
    static std::string KantaiTypeReso(int _kantaiType);
private:
    
    
};

class updateExp
{
public:
    int getUpdateExpByType(int kantaiLV);
    
private:
    const std::vector<int> data={100,200,300,400,500,600,700,800,900,1000,1100};;
};



class calcKantaiStar
{
public:
    static int calcKantaiStarByAttr();
    
private:
    
};


class InitPlayerProp
{
public:
    int initPlayerUpdateExpByLV(int _currLV);
    
    int initMaxFuelByLV(int _currLV);
    
    int initMaxAmmoByLV(int _currLV);
    
    int initMaxSteelByLV(int _currLV);
    
    int initMaxAluminiumByLV(int _currLV);
    
    int initMaxKantaiSize(int _currLV);
    
    int initMaxEquipSize(int _currLV);
    
    
private:
    int _initMaxPropByLV(int _currLV);
    
    const std::vector<int> updateExpData={50,60,70,80,100,120};
    
    
};

class DatabaseKey
{
public:
    static int getFleetKey();
    static int getKantaiKey();
    static int getEquipKey();
    
    static void setFleetKey(int fleetKey);
    static void setKantaiKey(int kantaiKey);
    static void setEquipKey(int equipKey);
    
private:
    static int maxFleetKey;
    static int maxKantaiKey;
    static int maxEquipKey;
};



#endif /* defined(__kancolle_alpha__SystemHeader__) */
