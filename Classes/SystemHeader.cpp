//
//  SystemHeader.cpp
//  kancolle_alpha
//
//  Created by 岩林张 on 7/31/15.
//
//

#include "SystemHeader.h"

NS_KCL_BEGIN

std::string NameResolution::EquipScopeReso(int _equipScope)
{
    switch (_equipScope)
    {
       case 130:
        {
            return "AttackEquip_Radio";
        }
        case 131:
        {
            return "Aircraft";
        }
        case 132:
        {
            return "SeaPlane";
        }
        case 133:
        {
            return "AntiSubmarineEquip";
        }
        case 134:
        {
            return "Intensify_Equip";
        }
        case 135:
        {
            return "Others";
        }
        case 136:
        {
            return "Deep_Sea_Equip";
        }
        default:
        {
            return nullptr;
        }
    }
    return nullptr;
}

std::string NameResolution::KantaiTypeReso(int _kantaiType)
{
    switch (_kantaiType)
    {
        case 101:
        {
            return "Escort";
        }
        case 102:
        {
            return "Destroyer";
        }
        case 103:
        {
            return "Light_Cruiser";
        }
        case 104:
        {
            return "Torpedo_Cruiser";
        }
        case 105:
        {
            return "Heavy_Cruiser";
        }
        case 106:
        {
            return "Air_Cruiser";
        }
        case 107:
        {
            return "Light_Carrier";
        }
        case 108:
        {
            return "Battle_Cruiser";
        }
        case 109:
        {
            return "Carrier";
        }
        case 110:
        {
            return "Battleship";
        }
        case 111:
        {
            return "Submarine";
        }
        case 112:
        {
            return "Diving_Carrier";
        }
        case 113:
        {
            return "Seaplane_Carrier";
        }
        case 114:
        {
            return "Landing_craft";
        }
        case 115:
        {
            return "Armor_Carrier";
        }
        case 116:
        {
            return "Workboat";
        }
        case 117:
        {
            return "Diving_Mothership";
        }
        case 118:
        {
            return "Training_Cruiser";
        }
        default:
        {
            return nullptr;
        }
            
    }
    
     
    
    return nullptr;
}



std::string NameResolution::EquipTypeReso(int _equipType)
{
    switch (_equipType)
    {
        case 140:
        {
            return "Small_Caliber";
        }
        case 141:
        {
            return "Medium_Caliber";
        }
        case 142:
        {
            return "Large_Caliber";
        }
        case 143:
        {
            return "Vice_Gun";
        }
        case 144:
        {
            return "Torpedo";
        }
        case 145:
        {
            return "Radar";
        }
        case 146:
        {
            return "Shell";
        }
        case 147:
        {
            return "Fighter";
        }
        case 148:
        {
            return "Bomber";
        }
        case 149:
        {
            return "Attacker";
        }
        case 150:
        {
            return "Surv_Aircraft";
        }
        case 151:
        {
            return "Mari_Bomber";
        }
        case 152:
        {
            return "Mari_Surv";
        }
        case 153:
        {
            return "Sonar";
        }
        case 154:
        {
            return "Depth_charge";
        }
        case 155:
        {
            return "AntiSubmarine_Aircraft";
        }
        case 156:
        {
            return "AntiAir_MachineGun";
        }
        case 157:
        {
            return "Engine";
        }
        case 158:
        {
            return "Append_Armor";
        }
        case 159:
        {
            return "Repair_Equip";
        }
        case 160:
        {
            return "AntiAir_Equip";
        }
        case 161:
        {
            return "OthersType";
        }
        case 162:
        {
            return "Deep_Sea_Type";
        }
        default:
        {
            return nullptr;
        }

    }
    return nullptr;
}





int InitPlayerProp::_getMaxPropByLV(int _currLV)
{
    int multiplier=10000;
    if (_currLV<=0)
    {
        return -1;
    }
    else if (_currLV<10)
    {
        return multiplier;
    }
    else if(_currLV<=MAX_PLAYER_LV)
    {
        return multiplier*(_currLV/10);
    }
    else
        return -1;
}

int InitPlayerProp::getMaxFuelByLV(int _currLV)
{
    return InitPlayerProp::_getMaxPropByLV(_currLV);
}

int InitPlayerProp::getMaxAmmoByLV(int _currLV)
{
    return InitPlayerProp::_getMaxPropByLV(_currLV);
}

int InitPlayerProp::getMaxSteelByLV(int _currLV)
{
    return InitPlayerProp::_getMaxPropByLV(_currLV);
}

int InitPlayerProp::getMaxAluminiumByLV(int _currLV)
{
    return InitPlayerProp::_getMaxPropByLV(_currLV);
}

int InitPlayerProp::getMaxKantaiSize(int _currLV)
{
    return 100;
}

int InitPlayerProp::getMaxEquipSize(int _currLV)
{
    return 1000;
    
}

NS_KCL_END

