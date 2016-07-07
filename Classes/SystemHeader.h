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


#define NS_KCL_BEGIN namespace kancolle{
#define NS_KCL_END   }
#define USING_NS_KCL using namespace kancolle


NS_KCL_BEGIN


#define equilp_type int
#define equilp_iter int
#define plane_load int
#define FONT_ADDRESS "/Volumes/opengl/kancolle_alpha/Resources/fonts/arial.ttf"
#define DATEBASE_ADDRESS "/Volumes/opengl/kancolle_alpha/Resources/database/kancolle_2.sqlite3"
#define MAX_PLAYER_LV 100
#define MAX_PLAYER_LV_EXP -1



///kantai type
typedef enum
{
    Destroyer=1,   //驱逐舰
    Light_Cruiser=2,    //轻巡洋舰
    Torpedo_Cruiser=3,  //重雷装巡洋舰
    Heavy_Cruiser=4,    //重巡洋舰
    Training_Cruiser=5,//练习巡洋舰
    Air_Cruiser=6,    //航空巡洋舰
    Supply_Ship=7,  //补给舰
    Landing_craft=8,//扬陆舰
    Battleship=9,//低速战舰
    Battle_Cruiser=10,   //高速战舰
    Battle_Carrier=11, //航空战舰
    Workboat=12,//工作舰
    Light_Carrier=13,    //轻空母
    Carrier=14, //正规航母
    Armor_Carrier=15,//装甲空母
    Seaplane_Carrier=16,//水上机母舰
    Submarine=17,//潜水舰
    Diving_Carrier=18,//潜水空母
    Diving_Mothership=19,//潜水母舰
}KantaiType;

class Help
{
public:
    static std::string getKantaiType(KantaiType type)
    {
        switch (type)
        {
            case Destroyer:
                return "驱逐舰";
            case Light_Cruiser:
                return "轻巡洋舰";
            case Torpedo_Cruiser:
                return "重雷装巡洋舰";
            case Heavy_Cruiser:
                return "重巡洋舰";
            case Training_Cruiser:
                return "练习巡洋舰";
            case Air_Cruiser:
                return "航空巡洋舰";
            case Supply_Ship:
                return "补给舰";
            case Landing_craft:
                return "扬陆舰";
            case Battleship:
                return "低速战舰";
            case Battle_Cruiser:
                return "高速战舰";
            case Battle_Carrier:
                return "航空战舰";
            case Workboat:
                return "工作舰";
            case Light_Carrier:
                return "轻空母";
            case Carrier:
                return "正规航母";
            case Armor_Carrier:
                return "装甲空母";
            case Seaplane_Carrier:
                return "水上机母舰";
            case Submarine:
                return "潜水舰";
            case Diving_Carrier:
                return "潜水空母";
            case Diving_Mothership:
                return "潜水母舰";
            default:
                return "";
        }
    }
 
};




typedef enum
{
    range_non=0,
    range_short=1,
    range_mid=2,
    range_long=3,
    range_exlong=4
    //range_no=5
}Shooting_Range;


typedef enum
{
    Free=1,
    Repairing=2,
    Expedition=3,
    Error=4
}KantaiState;


typedef enum
{
    low_speed=1,
    mid_speed=2,
    high_speed=3
}Move_Speed;

typedef enum
{
    normal,
    tiny,
    mid,
    large,
    drown
}BrokenType;
//装备分类
typedef enum
{
    AttackEquip_Radio=130,     //攻击装备与雷达
    Aircraft=131,                 //舰载机
    SeaPlane=132,            //水上机
    AntiSubmarineEquip=133,            //对潜装备
    Intensify_Equip=134,            //对空机枪与强化设备
    Others=135,            //其他装备
    Deep_Sea_Equip=136            //深海装备
}EquipScope;

//装备种类
typedef enum
{
    no_equipment=0,
    Small_Caliber=1,            //小口径主炮
    Medium_Caliber=2,            //中口径主炮
    Large_Caliber=3,            //大口径主炮
    Vice_Gun=4,            //副炮
    Torpedo=5,            //鱼雷
    Radar=6,            //雷达(電探)
    Shell=7,            //炮弹
    Fighter=8,            //舰上战斗机
    Bomber=9,            //舰上轰炸机
    Attacker=10,            //舰上强击机
    Surv_Aircraft=11,            //舰上侦察机
    Mari_Bomber=12,            //水上轰炸机
    Mari_Surv=13,            //水上侦察机
    Sonar=14,            //声纳
    Depth_charge=15,            //深水炸弹
    AntiSubmarine_Aircraft=16,            //反潜巡逻机
    AntiAir_MachineGun=17,            //对空机枪
    Engine=18,            //发动机
    Append_Armor=19,            //追加装甲
    Repair_Equip=20,            //修理要员
    AntiAir_Equip=21,            //高射装置
    OthersType=22,            //其他装备类型
    Deep_Sea_Type=23            //深海装备类型
}EquipType;

typedef enum
{
    INIT_UNIT,
    READ_KANTAI_DATABASE
}LoadState;



class NameResolution
{
public:
    static std::string EquipScopeReso(int _equipScope);
    
    static std::string EquipTypeReso(int _equipType);
    
    static std::string KantaiTypeReso(int _kantaiType);
private:
    
    
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
    static int getMaxFuelByLV(int _currLV);
    
    static int getMaxAmmoByLV(int _currLV);
    
    static int getMaxSteelByLV(int _currLV);
    
    static int getMaxAluminiumByLV(int _currLV);
    
    static int getMaxKantaiSize(int _currLV);
    
    static int getMaxEquipSize(int _currLV);

    static int _getMaxPropByLV(int _currLV);
    
};

NS_KCL_END

#endif /* defined(__kancolle_alpha__SystemHeader__) */
