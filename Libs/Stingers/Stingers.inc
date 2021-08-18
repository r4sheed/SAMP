/*
 Stingers.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer
 Modules: 3DTryg

 File Version: 1.1.2
 Streamer Version: 2.9.5
 3DTryg Version: 5.2.0

 Definitions:
 STINGER_TYPE_SMALL  //Object: 2899
 STINGER_TYPE_BIG    //Object: 2892

 Functions:
 CreateDynamicStinger(type,Float:x,Float:y,Float:z,Float:rx,Float:ty,Float:rz,worldid=-1,interiorid=-1,playerid=-1,Float:streamdistance=100.0,teamid=ANY_TEAM,byplayerid=INVALID_PLAYER_ID);
 DestroyDynamicStinger(mobid);

 Extended Functions:
 bool:IsDynamicStingerActive(mobid);
 GetDynamicStingerObjectID(mobid);
 GetDynamicStingerTeam(mobid);
 SetDynamicStingerTeam(mobid,teamid);
 GetDynamicStingerPlayerID(mobid);
 SetDynamicStingerPlayerID(mobid,byplayerid);
 GetPlayerActiveDynamicStinger(playerid);
 ToggleDynamicStingerDamage(mobid,bool:toggle);

 Callbacks:
 OnVehicleDamageByStinger(playerid,killerid,mobid,old_tires,new_tires);
*/

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR) || (!defined RemoveDynamicObjectMaterialText))
	#error [ADM] This include required Streamer v2.9.5 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] This include required 3DTryg.inc v5.2.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to v5.2.0
#elseif (TRYG3D_VERSION < 50200)
	#error [ADM] Update your 3DTryg.inc to v5.2.0
#endif

#if defined _Dynamic_Stingers
	#endinput
#endif
#define _Dynamic_Stingers
#define DYNAMIC_FILTERSCRIPT					"ALS:HOOK:METHOD"

#define Stingers_Version						(10102) //a.b.c 10000*a+100*b+c

#define STINGERS_EXTRA_ID_OFFSET				(500000)

#define INVALID_STINGER_ID						(0)

#define STINGER_TYPE_SMALL						(1)
#define STINGER_TYPE_BIG						(2)

#if !defined MAX_STINGERS
	#define MAX_STINGERS						(1000)
#endif

#if !defined ANY_TEAM
	#define ANY_TEAM							(0xFFFF)
#endif

enum e_stingers {
	bool:stin_active,
	stin_teamid,
	stin_byplayerid,
	STREAMER_TAG_AREA:stin_areaid,
	STREAMER_TAG_OBJECT:stin_objectid,
	stin_type,
	stin_damage
};

new	STREAMER_TAG_AREA:STIN_ActiveForPlayer[MAX_PLAYERS],
	STIN_PlayerStinger[MAX_PLAYERS],
	Float:STIN_PlayerHCP[MAX_PLAYERS][9],
	STIN_LastVehicle[MAX_PLAYERS],
	Stingers[MAX_STINGERS][e_stingers],
	StingersPartTable[] = {VEHICLE_PART_RFTIRE,VEHICLE_PART_LFTIRE,VEHICLE_PART_RRTIRE,VEHICLE_PART_LRTIRE};

#define IsDynamicStingerActive(%0)						Stingers[(%0)][stin_active]
#define GetDynamicStingerObjectID(%0)					Stingers[(%0)][stin_objectid]

#define GetDynamicStingerTeam(%0)						Stingers[(%0)][stin_teamid]
#define SetDynamicStingerTeam(%0,%1)					Stingers[(%0)][stin_teamid] = (%1)

#define GetDynamicStingerPlayerID(%0)					Stingers[(%0)][stin_byplayerid]
#define SetDynamicStingerPlayerID(%0,%1)				Stingers[(%0)][stin_byplayerid] = (%1)

#define ToggleDynamicStingerDamage(%0,%1)				Stingers[(%0)][stin_damage]

forward OnVehicleDamageByStinger(playerid,killerid,mobid,old_tires,new_tires);

stock STIN_ConstructData(){
	new data_construct[e_stingers];
	data_construct[stin_teamid] = ANY_TEAM;
	data_construct[stin_byplayerid] = INVALID_PLAYER_ID;
	return data_construct;
}

stock STIN_GetFreeID(){
	for(new i = 1; i < MAX_STINGERS; i++){
		if(!IsDynamicStingerActive(i)) return i;
	}
	return INVALID_STINGER_ID;
}

stock GetPlayerActiveDynamicStinger(playerid){
	if(STIN_ActiveForPlayer[playerid] == INVALID_STREAMER_ID) return INVALID_STINGER_ID;
	return STIN_PlayerStinger[playerid];
}

stock CreateDynamicStinger(type,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid=-1,interiorid=-1,playerid=-1,Float:streamdistance=100.0,teamid=ANY_TEAM,byplayerid=INVALID_PLAYER_ID){
	new mobid = STIN_GetFreeID();
	if(mobid == INVALID_STINGER_ID){
		printf("[ADM] Error: Failed to CreateDynamicStinger limit %d exceeded, add #define MAX_STINGERS before Stingers.inc",MAX_STINGERS);
		return INVALID_STINGER_ID;
	}
	new objectid, Float:size;
	switch(type){
		case STINGER_TYPE_SMALL: {
			objectid = 2899;
			size = 3.0*4.98878;
		}
		case STINGER_TYPE_BIG: {
			objectid = 2892;
			size = 3.0*10.04429;
		}
	}
	Stingers[mobid] = STIN_ConstructData();
	
	Stingers[mobid][stin_damage] = true;
	Stingers[mobid][stin_teamid] = teamid;
	Stingers[mobid][stin_byplayerid] = byplayerid;
	Stingers[mobid][stin_areaid] = CreateDynamicSphere(x,y,z,size,worldid,interiorid,playerid);
	Stingers[mobid][stin_objectid] = CreateDynamicObject(objectid,x,y,z,rx,ry,rz,worldid,interiorid,playerid,streamdistance);
	Stingers[mobid][stin_type] = type;
	
	AttachDynamicAreaToObject(Stingers[mobid][stin_areaid],Stingers[mobid][stin_objectid]);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Stingers[mobid][stin_areaid],E_STREAMER_EXTRA_ID,(mobid+STINGERS_EXTRA_ID_OFFSET));
	Stingers[mobid][stin_active] = true;
	
	return mobid;
}

stock DestroyDynamicStinger(mobid){
	if(mobid <= 0 || mobid >= MAX_STINGERS) return 0;
	if(!IsDynamicStingerActive(mobid)) return 0;
	if(IsValidDynamicObject(Stingers[mobid][stin_objectid])){
		DestroyDynamicObject(Stingers[mobid][stin_objectid]);
		Stingers[mobid][stin_objectid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Stingers[mobid][stin_areaid])){
		DestroyDynamicArea(Stingers[mobid][stin_areaid]);
		Stingers[mobid][stin_areaid] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	Stingers[mobid] = STIN_ConstructData();
	return 1;
}

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	new mobid = (Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-STINGERS_EXTRA_ID_OFFSET);
	if(mobid >= 1 && mobid < MAX_STINGERS){
		if(Stingers[mobid][stin_areaid] == areaid){
			if(GetDynamicStingerPlayerID(mobid) != playerid){
				if((GetDynamicStingerTeam(mobid) != GetPlayerTeam(playerid)) || (GetDynamicStingerTeam(mobid) == ANY_TEAM)){
					//Save Current object data, for OnPlayerUpdate
					GetDynamicObjectPos(GetDynamicStingerObjectID(mobid),STIN_PlayerHCP[playerid][0],STIN_PlayerHCP[playerid][1],STIN_PlayerHCP[playerid][2]);
					GetDynamicObjectRot(GetDynamicStingerObjectID(mobid),STIN_PlayerHCP[playerid][3],STIN_PlayerHCP[playerid][4],STIN_PlayerHCP[playerid][5]);
					
					STIN_LastVehicle[playerid] = GetPlayerVehicleID(playerid);
					STIN_PlayerStinger[playerid] = mobid;
					
					STIN_ActiveForPlayer[playerid] = areaid;
				}
			}
		}
	}
	#if defined STIN_OnPlayerEnterDynamicArea
		STIN_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea STIN_OnPlayerEnterDynamicArea
#if defined STIN_OnPlayerEnterDynamicArea
	forward STIN_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerLeaveDynamicArea
public OnPlayerLeaveDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	new mobid = (Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-STINGERS_EXTRA_ID_OFFSET);
	if(mobid >= 1 && mobid < MAX_STINGERS){
		if(Stingers[mobid][stin_areaid] == areaid && STIN_ActiveForPlayer[playerid] == areaid){
			STIN_ActiveForPlayer[playerid] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
		}
	}
	#if defined STIN_OnPlayerLeaveDynamicArea
		STIN_OnPlayerLeaveDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea STIN_OnPlayerLeaveDynamicArea
#if defined STIN_OnPlayerLeaveDynamicArea
	forward STIN_OnPlayerLeaveDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerUpdate
public OnPlayerUpdate(playerid){
 	if(STIN_ActiveForPlayer[playerid] != STREAMER_TAG_AREA:INVALID_STREAMER_ID && STIN_LastVehicle[playerid] != 0){
		new mobid = STIN_PlayerStinger[playerid];
		if(Stingers[mobid][stin_damage]){
			new panels,doors,lights,tires,TireStatus[4],new_tires;
			GetVehicleDamageStatus(STIN_LastVehicle[playerid],panels,doors,lights,tires);
			TireStatus[0] = (tires >> 1 & 0x1);
			TireStatus[1] = (tires >> 3 & 0x1);
			TireStatus[2] = (tires & 0x1);
			TireStatus[3] = (tires >> 2 & 0x1);
			
			new Float:size_x,Float:size_y;
			switch(Stingers[mobid][stin_type]){
				case STINGER_TYPE_SMALL: {
					size_x = 1.151422*1.005;
					size_y = 4.98878*1.005;
				}
				case STINGER_TYPE_BIG: {
					size_x = 1.22695*1.005;
					size_y = 10.04429*1.005;
				}
			}
			
			for(new i = 0; i < 4; i++){
				if(!TireStatus[i]){
					GetVehiclePartPos(STIN_LastVehicle[playerid],StingersPartTable[i],STIN_PlayerHCP[playerid][6],STIN_PlayerHCP[playerid][7],STIN_PlayerHCP[playerid][8]);
					if(Area::PointInCube3D(
						STIN_PlayerHCP[playerid][6],STIN_PlayerHCP[playerid][7],STIN_PlayerHCP[playerid][8],
						STIN_PlayerHCP[playerid][0],STIN_PlayerHCP[playerid][1],STIN_PlayerHCP[playerid][2],
						STIN_PlayerHCP[playerid][3],STIN_PlayerHCP[playerid][4],STIN_PlayerHCP[playerid][5],
						size_x,size_y,3.0
					)){
						TireStatus[i] = 1;
					}
				}
			}
			new_tires = (TireStatus[2] | (TireStatus[0] << 1) | (TireStatus[3] << 2) | (TireStatus[1] << 3));
			if(tires != new_tires){
				UpdateVehicleDamageStatus(STIN_LastVehicle[playerid],panels,doors,lights,new_tires);
				CallRemoteFunction("OnVehicleDamageByStinger","ddddd",playerid,Stingers[mobid][stin_byplayerid],mobid,tires,new_tires);
			}
		}
	}
	#if defined STIN_OnPlayerUpdate
		STIN_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

#if defined STIN_OnPlayerUpdate
	forward STIN_OnPlayerUpdate(playerid);
#endif
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate STIN_OnPlayerUpdate

//Hook: OnPlayerStateChange
public OnPlayerStateChange(playerid,newstate,oldstate){
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER){
		STIN_LastVehicle[playerid] = GetPlayerVehicleID(playerid);
    } else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT){
		STIN_LastVehicle[playerid] = 0;
	}
	#if defined STIN_OnPlayerStateChange
		STIN_OnPlayerStateChange(playerid,newstate,oldstate);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange STIN_OnPlayerStateChange
#if defined STIN_OnPlayerStateChange
	forward STIN_OnPlayerStateChange(playerid,newstate,oldstate);
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	STIN_ActiveForPlayer[playerid] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	STIN_LastVehicle[playerid] = 0;
	#if defined STIN_OnPlayerDisconnect
		STIN_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect STIN_OnPlayerDisconnect
#if defined STIN_OnPlayerDisconnect
	forward STIN_OnPlayerDisconnect(playerid,reason);
#endif

new bool:CRC_STINInit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_STINInit){
		CRC_STINInit = false;
		for(new mobid = 1; mobid < MAX_STINGERS; mobid++){
			Stingers[mobid] = STIN_ConstructData();
		}
	}
	#if defined STIN_OnFilterScriptInit
		STIN_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit STIN_OnFilterScriptInit
#if defined STIN_OnFilterScriptInit
	forward STIN_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_STINInit){
		CRC_STINInit = false;
		for(new mobid = 1; mobid < MAX_STINGERS; mobid++){
			Stingers[mobid] = STIN_ConstructData();
		}
	}
	#if defined STIN_OnGameModeInit
		STIN_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit STIN_OnGameModeInit
#if defined STIN_OnGameModeInit
	forward STIN_OnGameModeInit();
#endif


//EOF