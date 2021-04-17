/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                 Military Dynamic Mines System                                                  *
 *                                                                                                                                *
 * Copyright © 2021 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Website: https://adm.ct8.pl                                                                                                    *
 *                                                                                                                                *
 * Plugins: Streamer                                                                                                              *
 * Modules: 3DTryg                                                                                                                *
 *                                                                                                                                *
 * File Version: 2.2.1                                                                                                            *
 * Streamer Version: 2.9.4                                                                                                        *
 * 3DTryg Version: 4.8.6                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * Mines::Create(type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,                *
 *                   worldid,interiorid,playerid,Float:streamdistance,mine_object = MINE_OBJECT_STANDARD,teamid = ANY_TEAM,       *
 *                   detect_type = MINE_DETECT_TYPE_ALL,byplayerid = INVALID_PLAYER_ID,Float:damage=-1.0,                         *
 *                   Float:vehicle_damage=-1.0);                                                                                  *
 * Mines::CreateEx(objectid,type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,     *
 *                     Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,teamid = ANY_TEAM,             *
 *                     detect_type = MINE_DETECT_TYPE_ALL,byplayerid = INVALID_PLAYER_ID,Float:damage=-1.0,                       *
 *                     Float:vehicle_damage=-1.0);                                                                                *
 * Mines::Destroy(mobid);                                                                                                         *
 * Mines::GetExplodeVisibility();                                                                                                 *
 * Mines::SetExplodeVisibility(Float:streamdistance);                                                                             *
 * Mines::ForceRespawn(mobid);                                                                                                    *
 * Mines::Count();                                                                                                                *
 * Mines::GetObjectID(mobid);                                                                                                     *
 * Mines::GetAreaID(mobid);                                                                                                       *
 * Mines::GetPos(mobid,&Float:x,&Float:y,&Float:z);                                                                               *
 * Mines::SetPos(mobid,Float:x,Float:y,Float:z);                                                                                  *
 * Mines::GetRot(mobid,&Float:rx,&Float:ry,&Float:rz);                                                                            *
 * Mines::SetRot(mobid,Float:rx,Float:ry,Float:rz);                                                                               *
 * Mines::GetDetectionRange(mobid,&Float:detection_range);                                                                        *
 * Mines::SetDetectionRange(mobid,Float:detection_range);                                                                         *
 * Mines::GetExplodeRadius(mobid,&Float:explode_radius);                                                                          *
 * Mines::SetExplodeRadius(mobid,Float:explode_radius);                                                                           *
 * Mines::GetHealth(mobid,&Float:health);                                                                                         *
 * Mines::SetHealth(mobid,Float:health);                                                                                          *
 * Mines::GetMaxHealth(mobid,&Float:health);                                                                                      *
 * Mines::SetMaxHealth(mobid,Float:health);                                                                                       *
 * Mines::GetVirtualWorld(mobid);                                                                                                 *
 * Mines::SetVirtualWorld(mobid,worldid);                                                                                         *
 * Mines::GetInterior(mobid);                                                                                                     *
 * Mines::SetInterior(mobid,interiorid);                                                                                          *
 * Mines::GetStreamDistance(mobid,&Float:streamdistance);                                                                         *
 * Mines::SetStreamDistance(mobid,Float:streamdistance);                                                                          *
 * Mines::GetTeam(mobid);                                                                                                         *
 * Mines::SetTeam(mobid,teamid);                                                                                                  *
 * Mines::GetType(mobid);                                                                                                         *
 * Mines::SetType(mobid,type);                                                                                                    *
 * Mines::GetRespawnTime(mobid);                                                                                                  *
 * Mines::SetRespawnTime(mobid,respawntime);                                                                                      *
 * Mines::GetDamage(mobid);                                                                                                       *
 * Mines::SetDamage(mobid,Float:damage);                                                                                          *
 * Mines::GetVehicleDamage(mobid);                                                                                                *
 * Mines::SetVehicleDamage(mobid,Float:damage);                                                                                   *
 * Mines::Update(variable);                                                                                                       *
 *                                                                                                                                *
 * Extended Grenade Functions:                                                                                                    *
 * Mines::GetEffectVisibility();                                                                                                  *
 * Mines::SetEffectVisibility(Float:streamdistance);                                                                              *
 * Mines::GetSpecialWeapon(mobid);                                                                                                *
 * Mines::SetSpecialWeapon(mobid,special_weaponid);                                                                               *
 * Mines::GetEffectID(mobid);                                                                                                     *
 * Mines::SetEffectID(mobid,effectid);                                                                                            *
 * Mines::GetEffectDMG(mobid);                                                                                                    *
 * Mines::SetEffectDMG(mobid,Float:damage);                                                                                       *
 * Mines::GetEffectVDMG(mobid);                                                                                                   *
 * Mines::SetEffectVDMG(mobid,Float:veh_damage);                                                                                  *
 * Mines::GetEffectTime(mobid);                                                                                                   *
 * Mines::SetEffectTime(mobid,seconds);                                                                                           *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,Float:radius,damagerid);                                             *
 *                                                                                                                                *
 **********************************************************************************************************************************/

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7 (adm.ct8.pl/r/download)
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.4 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v4.8.6
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v4.8.6
#elseif (TRYG3D_VERSION < 40806)
	#error [ADM] Update you 3DTryg.inc to v4.8.6
#endif

#if defined _dynamic_mine_system
	#endinput
#endif
#define _dynamic_mine_system
#define DYNAMIC_FILTERSCRIPT					"ALS:HOOK:METHOD"

#if defined _GRENADE_INCLUDE
	#if (EXTENDED_GRENADE_VERSION < 10100)
		#error [ADM] Update you ExtendedGrenade.inc to v1.1.0
	#else
		#define DYNAMIC_MINES_GRENADE
	#endif
#endif

#define Mines::									Mines_
#define DYNAMIC_MINE_VERSION					(20201)

#define MINE_OBJECT_STANDARD					(0)
#define MINE_OBJECT_UNDERWATER					(1)
#define MINE_OBJECT_LASER						(3)
#define MINE_OBJECT_PIZZA						(4)

#if !defined MAX_DYNAMIC_MINES
	#define MAX_DYNAMIC_MINES					(2048)
#endif

#define MINE_EXTRA_ID_OFFSET					(200001)
#define MINE_INFINITY_HEALTH					(1000000.0)

#define MINE_STATUS_UNACTIVE					(0)
#define MINE_STATUS_ACTIVE						(1)
#define MINE_STATUS_DAMAGED						(2)

#define MINE_TYPE_EXPLODE_SMALL					(12)
#define MINE_TYPE_EXPLODE_NORMAL				(2)
#define MINE_TYPE_EXPLODE_LARGE					(6)
#define MINE_TYPE_EXPLODE_HUGE					(7)

#define INVALID_MINE_ID							(0)

#define MINE_DESTROY_TYPE_DETECT				(0)	//When mine has been destroyed by detection range
#define MINE_DESTROY_TYPE_KILL					(1)	//When mine has been destroyed by player shoot

#define MINE_DETECT_TYPE_ALL					(0)
#define MINE_DETECT_TYPE_PLAYER					(1)
#define MINE_DETECT_TYPE_VEHICLE				(2)

#if !defined ANY_TEAM
	#define ANY_TEAM							(0xFFFF)
#endif

enum Mines::Enum {
							Mines::Active,
	STREAMER_TAG_OBJECT:	Mines::Object,
	STREAMER_TAG_AREA:		Mines::Area,
							Mines::TickCount,
							Mines::Type,
							Mines::RespawnTime,
	Float:					Mines::Health,
	Float:					Mines::MaxHealth,
	Float:					Mines::Explode,
							Mines::TeamID,
							Mines::DetectType,
							Mines::PlayerID,
							Mines::SpecialWeapon,
							Mines::EffectID,
	Float:					Mines::EffectDMG,
	Float:					Mines::EffectVDMG,
							Mines::EffectTime,
	Float:					Mines::Damage,
	Float:					Mines::VehicleDamage
}

new 		Mines::Data[MAX_DYNAMIC_MINES][Mines::Enum],
			Mines::UpperBound = 0,
			Mines::Timer,
	Float:	Mines::ExplosionVisibility = 200.0,
	Float:	Mines::EffectVisibility = 200.0;

#define Mines_Update(%0)						for(new %0 = 1; %0 <= Mines::UpperBound; %0++) if(Mines::Data[(%0)][Mines::Active] != MINE_STATUS_UNACTIVE)

#define Mines_GetObjectID(%0)					Mines::Data[(%0)][Mines::Object]
#define Mines_GetAreaID(%0)						Mines::Data[(%0)][Mines::Area]

#define Mines_GetExplodeVisibility()			Mines::ExplosionVisibility
#define Mines_SetExplodeVisibility(%0)			Mines::ExplosionVisibility = (%0)

#define Mines_GetPos(%0,%1,%2,%3)				GetDynamicObjectPos(Mines::Data[(%0)][Mines::Object],%1,%2,%3)
#define Mines_SetPos(%0,%1,%2,%3)				SetDynamicObjectPos(Mines::Data[(%0)][Mines::Object],%1,%2,%3)

#define Mines_GetRot(%0,%1,%2,%3)				GetDynamicObjectRot(Mines::Data[(%0)][Mines::Object],%1,%2,%3)
#define Mines_SetRot(%0,%1,%2,%3)				SetDynamicObjectRot(Mines::Data[(%0)][Mines::Object],%1,%2,%3)

#define Mines_GetDetectionRange(%0,%1)			Streamer::GetFloatData(STREAMER_TYPE_AREA,Mines::Data[(%0)][Mines::Area],E_STREAMER_SIZE,(%1))
#define Mines_SetDetectionRange(%0,%1)			Streamer::SetFloatData(STREAMER_TYPE_AREA,Mines::Data[(%0)][Mines::Area],E_STREAMER_SIZE,(%1))

#define Mines_GetExplodeRadius(%0,%1)			(%1) = Mines::Data[(%0)][Mines::Explode]
#define Mines_SetExplodeRadius(%0,%1)			Mines::Data[(%0)][Mines::Explode] = (%1)

#define Mines_GetHealth(%0,%1)					(%1) = Mines::Data[(%0)][Mines::Health]
#define Mines_SetHealth(%0,%1)					Mines::Data[(%0)][Mines::Health] = (%1)

#define Mines_GetMaxHealth(%0,%1)				(%1) = Mines::Data[(%0)][Mines::MaxHealth]
#define Mines_SetMaxHealth(%0,%1)				Mines::Data[(%0)][Mines::MaxHealth] = (%1)

#define Mines_GetTeam(%0)						Mines::Data[(%0)][Mines::TeamID]
#define Mines_SetTeam(%0,%1)					Mines::Data[(%0)][Mines::TeamID] = (%1)

#define Mines_GetVirtualWorld(%0)				Streamer::GetIntData(STREAMER_TYPE_OBJECT,Mines::Data[(%0)][Mines::Object],E_STREAMER_WORLD_ID,(%1))
#define Mines_GetInterior(%0)					Streamer::GetIntData(STREAMER_TYPE_OBJECT,Mines::Data[(%0)][Mines::Object],E_STREAMER_INTERIOR_ID,(%1))

#define Mines_GetType(%0)						Mines::Data[(%0)][Mines::Type]
#define Mines_SetType(%0,%1)					Mines::Data[(%0)][Mines::Type] = (%1)

#define Mines_GetRespawnTime(%0)				Mines::Data[(%0)][Mines::RespawnTime]
#define Mines_SetRespawnTime(%0,%1)				Mines::Data[(%0)][Mines::RespawnTime] = (%1)

#define Mines_GetDamage(%0)						Mines::Data[(%0)][Mines::Damage]
#define Mines_SetDamage(%0,%1)					Mines::Data[(%0)][Mines::Damage] = (%1)

#define Mines_GetVehicleDamage(%0)				Mines::Data[(%0)][Mines::VehicleDamage]
#define Mines_SetVehicleDamage(%0,%1)			Mines::Data[(%0)][Mines::VehicleDamage] = (%1)

#define Mines_GetEffectVisibility()				Mines::EffectVisibility
#define Mines_SetEffectVisibility(%0)			Mines::EffectVisibility = (%0)

#define Mines_GetSpecialWeapon(%0)				Mines::Data[(%0)][Mines::SpecialWeapon]
#define Mines_SetSpecialWeapon(%0,%1)			Mines::Data[(%0)][Mines::SpecialWeapon] = (%1)

#define Mines_GetEffectID(%0)					Mines::Data[(%0)][Mines::EffectID]
#define Mines_SetEffectID(%0,%1)				Mines::Data[(%0)][Mines::EffectID] = (%1)

#define Mines_GetEffectDMG(%0)					Mines::Data[(%0)][Mines::EffectDMG]
#define Mines_SetEffectDMG(%0,%1)				Mines::Data[(%0)][Mines::EffectDMG] = (%1)

#define Mines_GetEffectVDMG(%0)					Mines::Data[(%0)][Mines::EffectVDMG]
#define Mines_SetEffectVDMG(%0,%1)				Mines::Data[(%0)][Mines::EffectVDMG] = (%1)

#define Mines_GetEffectTime(%0)					Mines::Data[(%0)][Mines::EffectTime]
#define Mines_SetEffectTime(%0,%1)				Mines::Data[(%0)][Mines::EffectTime] = (%1)

#define Mines_GetStreamDistance(%0,%1)			Streamer::GetFloatData(STREAMER_TYPE_OBJECT,Mines::Data[(%0)][Mines::Object],E_STREAMER_STREAM_DISTANCE,(%1))

stock Mines::SetVirtualWorld(mobid,worldid){
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_WORLD_ID,worldid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Mines::Data[mobid][Mines::Area],E_STREAMER_WORLD_ID,worldid);
}

stock Mines::SetInterior(mobid,interiorid){
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_INTERIOR_ID,interiorid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Mines::Data[mobid][Mines::Area],E_STREAMER_INTERIOR_ID,interiorid);
}

stock Mines::SetStreamDistance(mobid,Float:streamdistance){
	Streamer::SetFloatData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,Mines::Data[mobid][Mines::Area],E_STREAMER_STREAM_DISTANCE,streamdistance);
}

stock Mines::Count(){
	new cnt = 0;
	for(new mobid = 1; mobid <= Mines::UpperBound; mobid++){
		if(Mines::Data[mobid][Mines::Active] != MINE_STATUS_UNACTIVE) cnt++;
	}
	return cnt;
}

stock Mines::GetFreeID(){
	for(new mobid = 1; mobid < MAX_DYNAMIC_MINES; mobid++){
		if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_UNACTIVE) return mobid;
	}
	return INVALID_MINE_ID;
}

forward OnDynamicMineUpdate();
forward OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,Float:radius,damagerid);

stock Mines::Respawn(mobid){
	if(mobid <= 0 || mobid >= MAX_DYNAMIC_MINES) return 0;
	if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_ACTIVE) return 0;
	new worldid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_WORLD_ID);
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_WORLD_ID,worldid-10000); //show mine
	Mines::Data[mobid][Mines::TickCount] = 0;
	Mines::Data[mobid][Mines::Health] = Mines::Data[mobid][Mines::MaxHealth];
	Mines::Data[mobid][Mines::Active] = MINE_STATUS_ACTIVE;
	return 1;
}

stock Mines::ForceRespawn(mobid){
	if(mobid <= 0 || mobid >= MAX_DYNAMIC_MINES) return 0;
	if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_UNACTIVE) return 0;
	if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_DAMAGED && Mines::Data[mobid][Mines::TickCount] != 0){
		Mines::Data[mobid][Mines::TickCount] = 0;
		Mines::Respawn(mobid);
	}
	return 1;
}

stock Mines::Create(type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,mine_object=MINE_OBJECT_STANDARD,teamid=ANY_TEAM,detect_type=MINE_DETECT_TYPE_ALL,byplayerid=INVALID_PLAYER_ID,Float:damage=-1.0,Float:vehicle_damage=-1.0){
	new mobid = Mines::GetFreeID();
	if(mobid == INVALID_MINE_ID){
		printf("[ADM] Error: Failed to Mines::Create limit %d exceeded, add #define MAX_DYNAMIC_MINES before Mines.inc",MAX_DYNAMIC_MINES);
		return INVALID_MINE_ID;
	}
	
	Mines::Data[mobid][Mines::Health] = health;
	Mines::Data[mobid][Mines::MaxHealth] = health;
	Mines::Data[mobid][Mines::Explode] = explode_radius;
	Mines::Data[mobid][Mines::TickCount] = 0;
	Mines::Data[mobid][Mines::Type] = type;
	Mines::Data[mobid][Mines::RespawnTime] = respawntime;
	Mines::Data[mobid][Mines::TeamID] = teamid;
	Mines::Data[mobid][Mines::DetectType] = detect_type;
	Mines::Data[mobid][Mines::PlayerID] = byplayerid;
	Mines::Data[mobid][Mines::Damage] = damage;
	Mines::Data[mobid][Mines::VehicleDamage] = vehicle_damage;
	Mines::Data[mobid][Mines::SpecialWeapon] = 0;
	Mines::Data[mobid][Mines::EffectID] = 0;
	Mines::Data[mobid][Mines::EffectDMG] = 5.0;
	Mines::Data[mobid][Mines::EffectVDMG] = 825;
	Mines::Data[mobid][Mines::EffectTime] = 25;
	
	if(Mines::Data[mobid][Mines::Damage] != -1.0 && Mines::Data[mobid][Mines::VehicleDamage] == -1.0) Mines::Data[mobid][Mines::VehicleDamage] = 750.0;
	
	switch(mine_object){
		case MINE_OBJECT_STANDARD:		Mines::Data[mobid][Mines::Object] = CreateDynamicObject(19602,x,y,z-0.93,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_UNDERWATER:	Mines::Data[mobid][Mines::Object] = CreateDynamicObject(2918,x,y,z-0.10,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_LASER:			Mines::Data[mobid][Mines::Object] = CreateDynamicObject(18643,x,y,z-0.09,180.0,90.0,0.0,worldid,interiorid,playerid,streamdistance);
		case MINE_OBJECT_PIZZA:			Mines::Data[mobid][Mines::Object] = CreateDynamicObject(19580,x,y,z+0.05,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
		
		default:						Mines::Data[mobid][Mines::Object] = CreateDynamicObject(19602,x,y,z-0.93,0.0,0.0,0.0,worldid,interiorid,playerid,streamdistance);
	}
	Mines::Data[mobid][Mines::Area] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(Mines::Data[mobid][Mines::Area],Mines::Data[mobid][Mines::Object]);
	
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Streamer::SetIntData(STREAMER_TYPE_AREA,Mines::Data[mobid][Mines::Area],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Mines::Data[mobid][Mines::Active] = MINE_STATUS_ACTIVE;
	if(mobid > Mines::UpperBound) Mines::UpperBound = mobid;
	return mobid;
}

stock Mines::CreateEx(objectid,type,Float:detection_range,Float:explode_radius,Float:health,respawntime,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,worldid,interiorid,playerid,Float:streamdistance,teamid=ANY_TEAM,detect_type=MINE_DETECT_TYPE_ALL,byplayerid=INVALID_PLAYER_ID,Float:damage=-1.0,Float:vehicle_damage=-1.0){
	new mobid = Mines::GetFreeID();
	if(mobid == INVALID_MINE_ID){
		printf("[ADM] Error: Failed to Mines::Create limit %d exceeded, add #define MAX_DYNAMIC_MINES before Mines.inc",MAX_DYNAMIC_MINES);
		return mobid;
	}
	Mines::Data[mobid][Mines::Health] = health;
	Mines::Data[mobid][Mines::MaxHealth] = health;
	Mines::Data[mobid][Mines::Explode] = explode_radius;
	Mines::Data[mobid][Mines::TickCount] = 0;
	Mines::Data[mobid][Mines::Type] = type;
	Mines::Data[mobid][Mines::RespawnTime] = respawntime;
	Mines::Data[mobid][Mines::TeamID] = teamid;
	Mines::Data[mobid][Mines::DetectType] = detect_type;
	Mines::Data[mobid][Mines::PlayerID] = byplayerid;
	Mines::Data[mobid][Mines::Damage] = damage;
	Mines::Data[mobid][Mines::VehicleDamage] = vehicle_damage;
	Mines::Data[mobid][Mines::SpecialWeapon] = 0;
	Mines::Data[mobid][Mines::EffectID] = 0;
	Mines::Data[mobid][Mines::EffectDMG] = 5.0;
	Mines::Data[mobid][Mines::EffectVDMG] = 825;
	Mines::Data[mobid][Mines::EffectTime] = 25;
	
	if(Mines::Data[mobid][Mines::Damage] != -1.0 && Mines::Data[mobid][Mines::VehicleDamage] == -1.0) Mines::Data[mobid][Mines::VehicleDamage] = 750.0;

	Mines::Data[mobid][Mines::Object] = CreateDynamicObject(objectid,x,y,z,rx,ry,rz,worldid,interiorid,playerid,streamdistance);
	Mines::Data[mobid][Mines::Area] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(Mines::Data[mobid][Mines::Area],Mines::Data[mobid][Mines::Object]);
	
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Streamer::SetIntData(STREAMER_TYPE_AREA,Mines::Data[mobid][Mines::Area],E_STREAMER_EXTRA_ID,(mobid+MINE_EXTRA_ID_OFFSET));
	Mines::Data[mobid][Mines::Active] = MINE_STATUS_ACTIVE;
	if(mobid > Mines::UpperBound) Mines::UpperBound = mobid;
	return mobid;
}

stock Mines::Destroy(mobid){
	if(mobid <= 0 || mobid >= MAX_DYNAMIC_MINES) return 0;
	if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_UNACTIVE) return 0;
	if(IsValidDynamicObject(Mines::Data[mobid][Mines::Object])) DestroyDynamicObject(Mines::Data[mobid][Mines::Object]);
	if(IsValidDynamicArea(Mines::Data[mobid][Mines::Area])) DestroyDynamicArea(Mines::Data[mobid][Mines::Area]);
	Mines::Data[mobid][Mines::Object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	Mines::Data[mobid][Mines::Area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	Mines::Data[mobid][Mines::Health] = 0.0;
	Mines::Data[mobid][Mines::MaxHealth] = 0.0;
	Mines::Data[mobid][Mines::Explode] = 0.0;
	Mines::Data[mobid][Mines::TickCount] = 0;
	Mines::Data[mobid][Mines::Type] = 0;
	Mines::Data[mobid][Mines::RespawnTime] = 0;
	Mines::Data[mobid][Mines::TeamID] = ANY_TEAM;
	Mines::Data[mobid][Mines::DetectType] = MINE_DETECT_TYPE_ALL;
	Mines::Data[mobid][Mines::Damage] = -1;
	Mines::Data[mobid][Mines::VehicleDamage] = -1;
	Mines::Data[mobid][Mines::Active] = MINE_STATUS_UNACTIVE;
	if(mobid == Mines::UpperBound) Mines::UpperBound--;
	return 1;
}

stock Mines::OnExplode(mobid,type,playerid){
	if(mobid <= 0 || mobid >= MAX_DYNAMIC_MINES) return 0;
	if(Mines::Data[mobid][Mines::Active] != MINE_STATUS_ACTIVE) return 0;
	new Float:minex, Float:miney, Float:minez,
		worldid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_WORLD_ID),
		interiorid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_INTERIOR_ID),
		Float:radius;
	
	Streamer::GetFloatData(STREAMER_TYPE_AREA,Mines::Data[mobid][Mines::Area],E_STREAMER_SIZE,radius);
	GetDynamicObjectPos(Mines::Data[mobid][Mines::Object],minex,miney,minez);
	
	if(Mines::GetDamage(mobid) == -1.0){
		CreateDynamicExplosion(minex,miney,minez,Mines::Data[mobid][Mines::Type],Mines::Data[mobid][Mines::Explode],worldid,interiorid,-1,Mines::GetExplodeVisibility());
	} else {
		if(Mines::GetVehicleDamage(mobid) == -1.0) Mines::Data[mobid][Mines::VehicleDamage] = 750.0;
		CreateDynamicExplosionDMG(minex,miney,minez,Mines::Data[mobid][Mines::Type],Mines::Data[mobid][Mines::Explode],worldid,interiorid,-1,Mines::GetExplodeVisibility(),Mines::GetDamage(mobid),Mines::GetVehicleDamage(mobid),Mines::Data[mobid][Mines::PlayerID]);
	}
	
	#if defined DYNAMIC_MINES_GRENADE
		Grenade::CreateGrenadeEffect(Mines::GetSpecialWeapon(mobid),Mines::GetEffectID(mobid),minex,miney,minez,worldid,interiorid,-1,Mines::GetEffectVisibility(),Mines::GetEffectDMG(mobid),Mines::GetEffectVDMG(mobid),Mines::GetEffectTime(mobid),Mines::Data[mobid][Mines::PlayerID]);
	#endif
	
	Mines::Data[mobid][Mines::TickCount] = GetTickCount()+(Mines::Data[mobid][Mines::RespawnTime]*1000);
	Mines::Data[mobid][Mines::Active] = MINE_STATUS_DAMAGED;
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Mines::Data[mobid][Mines::Object],E_STREAMER_WORLD_ID,worldid+10000); //hide mine
	CallRemoteFunction("OnMineDestroy","dfffddfd",mobid,minex,miney,minez,type,playerid,radius,Mines::Data[mobid][Mines::PlayerID]);
	return 1;
}

public OnDynamicMineUpdate(){
	new tick = GetTickCount();
	for(new mobid = 1; mobid <= Mines::UpperBound; mobid++){
		if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_DAMAGED){
			if((tick >= Mines::Data[mobid][Mines::TickCount]) && (Mines::Data[mobid][Mines::TickCount] != 0)){
				Mines::Data[mobid][Mines::TickCount] = 0;
				Mines::Respawn(mobid);
			}
		}
	}
	return 1;
}

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_DYNAMIC_MINES){
		if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_ACTIVE && Mines::Data[mobid][Mines::Object] == objectid && Mines::Data[mobid][Mines::PlayerID] != playerid){
			if((Mines::Data[mobid][Mines::TeamID] != GetPlayerTeam(playerid)) || (Mines::Data[mobid][Mines::TeamID] == ANY_TEAM) || (GetPlayerTeam(playerid) == NO_TEAM)){
				if(Mines::Data[mobid][Mines::Health] != MINE_INFINITY_HEALTH){
					Mines::Data[mobid][Mines::Health] -= Tryg3D::GetWeaponDamage(weaponid);
					new buffer[128];
					if(Mines::Data[mobid][Mines::Health] > 0){
						format(buffer,sizeof buffer,"Mine~n~~w~%.0f HP~n~~r~~h~~h~-%.0f HP",Mines::Data[mobid][Mines::Health],Tryg3D::GetWeaponDamage(weaponid));
					} else {
						format(buffer,sizeof buffer,"Mine~n~~w~0 HP~n~~r~~h~~h~-%.0f HP",Tryg3D::GetWeaponDamage(weaponid));
					}
					GameTextForPlayer(playerid,buffer,500,4);
					if(Mines::Data[mobid][Mines::Health] <= 0.0){
						Mines::OnExplode(mobid,MINE_DESTROY_TYPE_KILL,playerid);
					}
				}
			}
		}
	}
	#if defined MDM_OnPlayerShootDynamicObject
		MDM_OnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject MDM_OnPlayerShootDynamicObject
#if defined MDM_OnPlayerShootDynamicObject
	forward MDM_OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid){
	new mobid = (Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MINE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_DYNAMIC_MINES){
		if(Mines::Data[mobid][Mines::Active] == MINE_STATUS_ACTIVE && Mines::Data[mobid][Mines::Area] == areaid && Mines::Data[mobid][Mines::PlayerID] != playerid){
			new bool:tmp_det = false;
			switch(Mines::Data[mobid][Mines::DetectType]){
				case MINE_DETECT_TYPE_ALL:		tmp_det = true;
				case MINE_DETECT_TYPE_PLAYER: 	if(!IsPlayerInAnyVehicle(playerid)) tmp_det = true;
				case MINE_DETECT_TYPE_VEHICLE:	if(IsPlayerInAnyVehicle(playerid)) tmp_det = true;
			}
			if(((Mines::Data[mobid][Mines::TeamID] != GetPlayerTeam(playerid)) || (Mines::Data[mobid][Mines::TeamID] == ANY_TEAM) || (GetPlayerTeam(playerid) == NO_TEAM)) && tmp_det){
				Mines::Data[mobid][Mines::Health] = 0.0;
				Mines::OnExplode(mobid,MINE_DESTROY_TYPE_DETECT,playerid);
			}
		}
	}	
	#if defined MDM_OnPlayerEnterDynamicArea
		MDM_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea MDM_OnPlayerEnterDynamicArea
#if defined MDM_OnPlayerEnterDynamicArea
	forward MDM_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
#endif

new bool:CRC_MinesInit = true,
	bool:CRC_MinesExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_MinesInit){
		CRC_MinesInit = false;
		Mines::Timer = SetTimer("OnDynamicMineUpdate",1000,true);
	}
	#if defined MDM_OnFilterScriptInit
		MDM_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit MDM_OnFilterScriptInit
#if defined MDM_OnFilterScriptInit
	forward MDM_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_MinesInit){
		CRC_MinesInit = false;
		Mines::Timer = SetTimer("OnDynamicMineUpdate",1000,true);
	}
	#if defined MDM_OnGameModeInit
		MDM_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit MDM_OnGameModeInit
#if defined MDM_OnGameModeInit
	forward MDM_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_MinesExit){
		CRC_MinesExit = false;
		KillTimer(Mines::Timer);
	}
	#if defined MDM_OnFilterScriptExit
		MDM_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit MDM_OnFilterScriptExit
#if defined MDM_OnFilterScriptExit
	forward MDM_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_MinesExit){
		CRC_MinesExit = false;
		KillTimer(Mines::Timer);
	}
	#if defined MDM_OnGameModeExit
		MDM_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit MDM_OnGameModeExit
#if defined MDM_OnGameModeExit
	forward MDM_OnGameModeExit();
#endif

#pragma unused Mines_EffectVisibility

//EOF