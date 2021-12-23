//#define STREAMER_ENABLE_TAGS
#define TRYG3D_ENABLE_COLANDREAS

#include <a_samp> 
#include <streamer> 
#include <ColAndreas> 
#include <sscanf2> 

#include <FoxForeach/FoxForeach>
#include <3DTryg/3DTryg>

#include <Hunting/Hunting>

public OnFilterScriptInit(){ 

    new STREAMER_TAG_AREA:my_zone = CreateDynamicRectangle(-100.0,-100.0,100.0,100.0); 
    for(new i = 0; i < 5; i++){ 
        Hunting::Create(HUNTING_TYPE_COW,0.0,0.0,3.0,55.0,30,.moving_area=my_zone); 
        Hunting::Create(HUNTING_TYPE_DEER,5.0,0.0,3.0,55.0,30,.moving_area=my_zone); 
    } 

    return 1; 
} 

public OnPlayerTakeHuntDrop(playerid,mobid,drop){ 
    if(drop){ 
        SendClientMessage(playerid,-1,"You received $2500"); 
        GivePlayerMoney(playerid,2500); 
    } 
    return 0; //set drop flag 0 
} 

public OnPlayerKillHuntAnimal(playerid,mobid){ 
     
    SendClientMessage(playerid,-1,"Animal has been killed !"); 
     
    return 1; 
} 

public OnPlayerApproachingAnimal(playerid,mobid,mob_state){ 

    if(mob_state == HUNTING_STATE_DEAD){ 
        SendClientMessage(playerid,-1,"Press Y to raise prize."); 
    } 
     
    return 1; 
} 

public OnPlayerExitApproachingAnimal(playerid,mobid,mob_state){ 

    return 1; 
} 

public OnAnimalTakeDamage(mobid,playerid,Float:amount,weaponid){ 
     
    if(weaponid != 34) return 0; //sniper only :D 
     
    return 1; 
} 

public OnHuntAnimalRespawn(mobid){ 
     
    return 1; 
} 

public OnAnimalScareStateChanged(mobid,playerid,isscared){ 

    return 1; 
} 

//only called if press time > 0 
public OnPlayerHuntDropStateChange(playerid,mobid,drop_state){ 
    switch(drop_state){ 
        case HUNTING_DROP_STATE_FINISH: { 
            //your code 
        } 
        case HUNTING_DROP_STATE_START: { 
            //your code 
        } 
        case HUNTING_DROP_STATE_INTERRUPT: { 
            //your code 
        } 
    } 
    return 1; 
}  