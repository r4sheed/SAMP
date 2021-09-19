/*
 Missile.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg

 File Version: 2.3.1
 Streamer Version: 2.9.5
 ColAndreas Version: 1.5.0
 3DTryg Version: 5.3.0

 Functions:
 Missile::Launch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM,bool:remote=false,remote_count=MAX_MISSILE_REMOTE_TARGET,remote_height=1.0,Float:arc_roll=0.0,Float:damage=-1.0,Float:vehicle_damage=-1.0);
 Missile::LaunchAimPlayer(targetid,type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM,Float:damage=-1.0,Float:vehicle_damage=-1.0);
 Missile::StopAimPlayer(mobid);
 Missile::Destroy(mobid,type,playerid); 
 Missile::RemoteTarget(mobid,Float:tx,Float:ty,Float:tz,Float:speed = 0.0); 
 Missile::GetExplodeVisibility(); 
 Missile::SetExplodeVisibility(Float:explode_stream); 
 Missile::DisableAllAim(playerid);

 Extended Functions:
 Misile::GetObject(mobid);
 Misile::GetArea(mobid);
 Misile::GetType(mobid);
 Misile::GetExplode(mobid);
 Misile::GetPlayer(mobid);
 Misile::GetTeamID(mobid);
 Misile::GetVehicle(mobid);
 Misile::GetRemoteCount(mobid);
 Misile::GetRemoteID(mobid);
 Misile::GetSpeed(mobid);
 Misile::GetTargetID(mobid);
 Misile::GetDamage(mobid);
 Misile::GetVehicleDamage(mobid);
 
 Callbacks: 
 OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid);
 OnMissileDetectPlayer(playerid,killerid);
 OnMissileRequestLaunch(Float:x,Float:y,Float:z,playerid,targetid); 
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

#if !defined COLANDREAS_VERSION
	#error [ADM] This include required ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#elseif (COLANDREAS_VERSION < 10500)
	#error [ADM] Update your ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] This include required 3DTryg.inc v5.3.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to v5.3.0
#elseif (TRYG3D_VERSION < 50300)
	#error [ADM] Update your 3DTryg.inc to v5.3.0
#endif

#if !defined TRYG3D_COLANDREAS
	#error [ADM] Module not initialized: TRYG3D_COLANDREAS
#endif

#if defined _missile_launcher
	#endinput
#endif
#define _missile_launcher
#define DYNAMIC_FILTERSCRIPT				"ALS:HOOK:METHOD"

#define Missile::							Missile_

#define Missile_Version						(20301)

#define MISSILE_OBJECT_NORMAL				(0)
#define MISSILE_OBJECT_BIG					(1)
#define MISSILE_OBJECT_HYDRA				(2)
#define MISSILE_OBJECT_BOMB					(3)
#define MISSILE_OBJECT_BOMB_STATIC			(4)
#define MISSILE_OBJECT_FLARE_1				(5)
#define MISSILE_OBJECT_FLARE_2				(6)
#define MISSILE_OBJECT_BULLET				(7)

#if !defined MAX_MISSILE
	#define MAX_MISSILE						(2048)
#endif

#if !defined MAX_MISSILE_REMOTE_TARGET
	#define MAX_MISSILE_REMOTE_TARGET		(34)
#endif

#define MISSILE_EXTRA_ID_OFFSET				(300001)
#define MISSILE_REMOTE_PLAYER				(999)
#define MISSILE_REMOTE_FLARE				(989)

#define MISSILE_TYPE_EXPLODE_SMALL			(12)
#define MISSILE_TYPE_EXPLODE_NORMAL			(2)
#define MISSILE_TYPE_EXPLODE_LARGE			(6)
#define MISSILE_TYPE_EXPLODE_HUGE			(7)
#define MISSILE_TYPE_EXPLODE_NONE			(14)

#define MISSILE_DESTROY_TYPE_TARGET			(0)	//When rocket reaches its destination (always killerid=INVALID_PLAYER_ID)
#define MISSILE_DESTROY_TYPE_DETECT			(1)	//When rocket has been destroyed by detection range
#define MISSILE_DESTROY_TYPE_KILL			(2)	//When rocket has been destroyed by player

#define WEAPON_MISSILE_BULLET				(102)

#define INVALID_MISSILE_ID					(0)

#if !defined ANY_TEAM
	#define ANY_TEAM						(0xFFFF)
#endif

enum Missile::Enum {
	bool:					Missile::Active,
	STREAMER_TAG_OBJECT:	Missile::Object,
	STREAMER_TAG_AREA:		Missile::Area,
							Missile::Type,
	Float:					Missile::Explode,
							Missile::PlayerID,
							Missile::TeamID,
							Missile::Vehicle,
							Missile::RemoteCount,
							Missile::RemoteID,
	Float:					Missile::Speed,
							Missile::TargetID,
	Float:					Missile::Damage,
	Float:					Missile::VehicleDamage
}

new 		Missile::Data[MAX_MISSILE][Missile::Enum],
	Float:	Missile::Points[MAX_MISSILE][MAX_MISSILE_REMOTE_TARGET][3],
	bool:	Missile::PlayerAim[MAX_PLAYERS],
			Missile::UpperBound = -1,
	Float:	Missile::ExplosionVisibility = 200.0;

#define Missile_GetExplodeVisibility()			Missile::ExplosionVisibility
#define Missile_SetExplodeVisibility(%0)		Missile::ExplosionVisibility = (%0)

#define Missile_GetObject(%0)					Missile::Data[(%0)][Missile::Object]
#define Missile_GetArea(%0)						Missile::Data[(%0)][Missile::Area]
#define Missile_GetType(%0)						Missile::Data[(%0)][Missile::Type]
#define Missile_GetExplode(%0)					Missile::Data[(%0)][Missile::Explode]
#define Missile_GetPlayer(%0)					Missile::Data[(%0)][Missile::PlayerID]
#define Missile_GetTeamID(%0)					Missile::Data[(%0)][Missile::TeamID]
#define Missile_GetVehicle(%0)					Missile::Data[(%0)][Missile::Vehicle]
#define Missile_GetRemoteCount(%0)				Missile::Data[(%0)][Missile::RemoteCount]
#define Missile_GetRemoteID(%0)					Missile::Data[(%0)][Missile::RemoteID]
#define Missile_GetSpeed(%0)					Missile::Data[(%0)][Missile::Speed]
#define Missile_GetTargetID(%0)					Missile::Data[(%0)][Missile::TargetID]
#define Missile_GetDamage(%0)					Missile::Data[(%0)][Missile::Damage]
#define Missile_GetVehicleDamage(%0)			Missile::Data[(%0)][Missile::VehicleDamage]

stock Missile::GetFreeID(){
	for(new i = 1; i < MAX_MISSILE; i++){
		if(!Missile::Data[i][Missile::Active]) return i;
	}
	return INVALID_MISSILE_ID;
}

forward OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid);
forward OnMissileDetectPlayer(playerid,killerid);
#if defined OnMissileRequestLaunch
	forward OnMissileRequestLaunch(Float:x,Float:y,Float:z,playerid,targetid);
#endif

stock Missile::Launch(type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid, \
	Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM, \
	bool:remote=false,remote_count=MAX_MISSILE_REMOTE_TARGET,Float:remote_height=1.0,Float:arc_roll=0.0,Float:damage=-1.0,Float:vehicle_damage=-1.0){
	
	#if defined OnMissileRequestLaunch
		if(!OnMissileRequestLaunch(tx,ty,tz,byplayerid,INVALID_PLAYER_ID)) return INVALID_MISSILE_ID;
	#endif
	
	new mobid = Missile::GetFreeID();
	if(mobid == INVALID_MISSILE_ID){
		printf("[ADM] Error: Failed to Missile::Launch limit %d exceeded, add #define MAX_MISSILE before Missile.inc",MAX_MISSILE);
		return INVALID_MISSILE_ID;
	}
	if(mobid > Missile::UpperBound) Missile::UpperBound = mobid;
	
	new Float:rx, Float:rz;
	GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
	switch(missile_object){
		case MISSILE_OBJECT_NORMAL: {
			rz = Tryg3D::CompressRotation(rz-90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(3790,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BIG: {
			rz = Tryg3D::CompressRotation(rz-90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(3786,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_HYDRA: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(345,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BOMB: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(1636,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BOMB_STATIC: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(1636,x,y,z,0.0,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_FLARE_1: {
			rx = Tryg3D::CompressRotation(rx+90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(18728,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_FLARE_2: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(354,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BULLET: {
			rx = Tryg3D::CompressRotation(rx-90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(322,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
	}
	Missile::Data[mobid][Missile::Explode] = explode_radius;
	Missile::Data[mobid][Missile::PlayerID] = byplayerid;
	Missile::Data[mobid][Missile::TeamID] = teamid;
	Missile::Data[mobid][Missile::Speed] = speed;
	Missile::Data[mobid][Missile::TargetID] = INVALID_PLAYER_ID;
	Missile::Data[mobid][Missile::Damage] = damage;
	Missile::Data[mobid][Missile::VehicleDamage] = vehicle_damage;
	
	if(Missile::Data[mobid][Missile::Damage] != -1 && Missile::Data[mobid][Missile::VehicleDamage] == -1) Missile::Data[mobid][Missile::VehicleDamage] = 750.0;
	
	if(remote && remote_count > 0){
		if(remote_height <= 0.0) remote_height = 1.0;
		
		if(remote_count > MAX_MISSILE_REMOTE_TARGET) remote_count = MAX_MISSILE_REMOTE_TARGET;
		Missile::Data[mobid][Missile::RemoteCount] = remote_count-2;
		Missile::Data[mobid][Missile::RemoteID] = 2;
		
		GetArcPoints3D(x,y,z,tx,ty,tz,arc_roll,remote_height,Missile::Points[mobid],remote_count);
		
		new rid = remote_count-1;
		tx = Missile::Points[mobid][rid][0];
		ty = Missile::Points[mobid][rid][1];
		tz = Missile::Points[mobid][rid][2];
		
		MovePointCol(tx,ty,tz,tx,ty,tz-10000.0,Missile::Points[mobid][rid][0],Missile::Points[mobid][rid][1],Missile::Points[mobid][rid][2]);
		
		tx = Missile::Points[mobid][1][0];
		ty = Missile::Points[mobid][1][1];
		tz = Missile::Points[mobid][1][2];
		
		GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
		switch(missile_object){
			case MISSILE_OBJECT_NORMAL: {
				rz = Tryg3D::CompressRotation(rz-90.0);
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],0.0,rx,rz);
			}
			case MISSILE_OBJECT_BIG: {
				rz = Tryg3D::CompressRotation(rz-90.0);
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],0.0,rx,rz);
			}
			case MISSILE_OBJECT_HYDRA: {
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			}
			case MISSILE_OBJECT_BOMB: {
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			}
			case MISSILE_OBJECT_BOMB_STATIC: {
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],0.0,0.0,rz);
			}
			case MISSILE_OBJECT_FLARE_1: {
				rx = Tryg3D::CompressRotation(rx+90.0);
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			}
			case MISSILE_OBJECT_FLARE_2: {
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			}
			case MISSILE_OBJECT_BULLET: {
				rx = Tryg3D::CompressRotation(rx-90.0);
				SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			}
		}
	} else {
		Missile::Data[mobid][Missile::RemoteCount] = 0;
	}
	Missile::Data[mobid][Missile::Vehicle] = GetPlayerVehicleID(byplayerid);
	
	Missile::Data[mobid][Missile::Area] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(Missile::Data[mobid][Missile::Area],Missile::Data[mobid][Missile::Object]);
	
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missile::Data[mobid][Missile::Area],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	Missile::Data[mobid][Missile::Type] = type;
	
	switch(missile_object){
		case MISSILE_OBJECT_HYDRA, MISSILE_OBJECT_BOMB, MISSILE_OBJECT_FLARE_1, MISSILE_OBJECT_FLARE_2, MISSILE_OBJECT_BULLET: {
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,rx,0.0,rz);
		}
		case MISSILE_OBJECT_BOMB_STATIC: {
			if(remote && remote_count > 0){
				MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,rx,0.0,rz);
			} else {
				MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,0.0,0.0,rz);
			}
		}
		default: {
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,0.0,rx,rz);
		}
	}
	Missile::Data[mobid][Missile::Active] = true;
	return mobid;
}

stock Missile::LaunchAimPlayer(targetid,type,Float:detection_range,Float:explode_radius,Float:speed,Float:x,Float:y,Float:z,worldid,interiorid,playerid, \
	Float:streamdistance,missile_object,Float:tx,Float:ty,Float:tz,byplayerid=INVALID_PLAYER_ID,teamid=ANY_TEAM,Float:damage=-1.0,Float:vehicle_damage=-1.0){
	
	#if defined OnMissileRequestLaunch
		if(!OnMissileRequestLaunch(tx,ty,tz,byplayerid,targetid)) return INVALID_MISSILE_ID;
	#endif
	
	new mobid = Missile::GetFreeID();
	if(mobid == INVALID_MISSILE_ID){
		printf("[ADM] Error: Failed to Missile::Launch limit %d exceeded, add #define MAX_MISSILE before Missile.inc",MAX_MISSILE);
		return INVALID_MISSILE_ID;
	}
	if(mobid > Missile::UpperBound) Missile::UpperBound = mobid;
	
	new Float:rx, Float:rz;
	GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
	switch(missile_object){
		case MISSILE_OBJECT_NORMAL: {
			rz = Tryg3D::CompressRotation(rz-90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(3790,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BIG: {
			rz = Tryg3D::CompressRotation(rz-90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(3786,x,y,z,0.0,rx,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_HYDRA: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(345,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BOMB, MISSILE_OBJECT_BOMB_STATIC: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(1636,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_FLARE_1: {
			rx = Tryg3D::CompressRotation(rx+90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(18728,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_FLARE_2: {
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(354,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
		case MISSILE_OBJECT_BULLET: {
			rx = Tryg3D::CompressRotation(rx-90.0);
			Missile::Data[mobid][Missile::Object] = CreateDynamicObject(322,x,y,z,rx,0.0,rz,worldid,interiorid,playerid,streamdistance,streamdistance);
		}
	}
	Missile::Data[mobid][Missile::Explode] = explode_radius;
	Missile::Data[mobid][Missile::PlayerID] = byplayerid;
	Missile::Data[mobid][Missile::TeamID] = teamid;
	Missile::Data[mobid][Missile::Speed] = speed;
	Missile::Data[mobid][Missile::RemoteCount] = MISSILE_REMOTE_PLAYER;
	Missile::Data[mobid][Missile::Vehicle] = GetPlayerVehicleID(byplayerid);
	Missile::Data[mobid][Missile::TargetID] = targetid;
	
	Missile::Data[mobid][Missile::Damage] = damage;
	Missile::Data[mobid][Missile::VehicleDamage] = vehicle_damage;
	
	if(Missile::Data[mobid][Missile::Damage] != -1 && Missile::Data[mobid][Missile::VehicleDamage] == -1) Missile::Data[mobid][Missile::VehicleDamage] = 750.0;
	
	Missile::PlayerAim[targetid] = true;
	Missile::Data[mobid][Missile::Area] = CreateDynamicSphere(x,y,z,detection_range,worldid,interiorid,playerid);
	AttachDynamicAreaToObject(Missile::Data[mobid][Missile::Area],Missile::Data[mobid][Missile::Object]);
	
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missile::Data[mobid][Missile::Area],E_STREAMER_EXTRA_ID,(mobid+MISSILE_EXTRA_ID_OFFSET));
	Missile::Data[mobid][Missile::Type] = type;
	
	switch(missile_object){
		case MISSILE_OBJECT_HYDRA, MISSILE_OBJECT_BOMB, MISSILE_OBJECT_BOMB_STATIC, MISSILE_OBJECT_FLARE_1, MISSILE_OBJECT_FLARE_2, MISSILE_OBJECT_BULLET: {
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,rx,0.0,rz);
		}
		default: {
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,0.0,rx,rz);
		}
	}
	Missile::Data[mobid][Missile::Active] = true;
	return mobid;
}

stock Missile::StopAimPlayer(mobid){
	if(Missile::Data[mobid][Missile::Active]){
		if(Missile::Data[mobid][Missile::RemoteCount] == MISSILE_REMOTE_PLAYER){
			if(!IsPlayerConnected(Missile::Data[mobid][Missile::TargetID])){
				Missile::Data[mobid][Missile::TargetID] = INVALID_PLAYER_ID;
				Missile::Data[mobid][Missile::RemoteCount] = 0;
				return 1;
			}
		}
	}
	return 0;
}

stock Missile::DisableAllAim(playerid){
	Missile::PlayerAim[playerid] = false;
	new cnt = 0;
	for(new mobid = 0; mobid <= Missile::UpperBound; mobid++){
		if(Missile::Data[mobid][Missile::TargetID] == playerid){
			Missile::StopAimPlayer(mobid);
			cnt++;
		}
	}
	return cnt;
}

stock Missile::RemoteTarget(mobid,Float:tx,Float:ty,Float:tz,Float:speed = 0.0){
	if(mobid <= 0 || mobid >= MAX_MISSILE) return 0;
	if(!Missile::Data[mobid][Missile::Active]) return 0;
	if(speed == 0.0) speed = Missile::Data[mobid][Missile::Speed];
	new missile_modelid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_MODEL_ID),
		Float:x ,Float:y, Float:z, Float:rx, Float:rz;
	GetDynamicObjectPos(Missile::Data[mobid][Missile::Object],x,y,z);
	GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz);
	switch(missile_modelid){
		case 345, 1636, 354: {
			SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,rx,0.0,rz);
		}
		case 3790, 3786: {
			rz = Tryg3D::CompressRotation(rz-90.0);
			SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],0.0,rx,rz);
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,0.0,rx,rz);
		}
		case 18728: {
			rx = Tryg3D::CompressRotation(rx+90.0);
			SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,rx,0.0,rz);
		}
		case 322: {
			rx = Tryg3D::CompressRotation(rx-90.0);
			SetDynamicObjectRot(Missile::Data[mobid][Missile::Object],rx,0.0,rz);
			MoveDynamicObject(Missile::Data[mobid][Missile::Object],tx,ty,tz,speed,rx,0.0,rz);
		}
	}
	return 1;
}

stock Missile::Destroy(mobid,type,playerid){
	if(mobid <= 0 || mobid >= MAX_MISSILE) return 0;
	if(!Missile::Data[mobid][Missile::Active]) return 0;

	new Float:x, Float:y, Float:z,
		worldid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_WORLD_ID),
		interiorid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_INTERIOR_ID);
	
	GetDynamicObjectPos(Missile::Data[mobid][Missile::Object],x,y,z);
	
	switch(Streamer::GetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_MODEL_ID)){
		case 18728, 354: {
			new Float:tx,Float:ty,Float:tz,Float:speed,Float:detection_range;
			Streamer::GetFloatData(STREAMER_TYPE_AREA,Missile::Data[mobid][Missile::Area],E_STREAMER_SIZE,detection_range);
			for(new i = 0; i <= Missile::UpperBound; i++){
				if(i != mobid){
					if(Missile::Data[i][Missile::RemoteCount] != MISSILE_REMOTE_FLARE){
						switch(Streamer::GetIntData(STREAMER_TYPE_OBJECT,Missile::Data[i][Missile::Object],E_STREAMER_MODEL_ID)){
							case 18728, 354: {
							
							}
							default: {
								GetDynamicObjectPos(Missile::Data[i][Missile::Object],tx,ty,tz);
								if(GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz) <= detection_range){
									Missile::Data[i][Missile::RemoteCount] = MISSILE_REMOTE_FLARE;
									Streamer::GetFloatData(STREAMER_TYPE_OBJECT,Missile::Data[i][Missile::Object],E_STREAMER_MOVE_SPEED,speed);
									Missile::RemoteTarget(i,x,y,z,speed);
								}
							}
						}
					}
				}
			}
		}
		case 322: {
			if(Missile::Data[mobid][Missile::Type] == MISSILE_TYPE_EXPLODE_NONE && playerid != INVALID_PLAYER_ID){
				if(IsPlayerInAnyVehicle(playerid)){
					new T3D:vid = GetPlayerVehicleID(playerid), Float:T3D:health;
					GetVehicleHealth(T3D:vid,T3D:health);
					SetVehicleHealth(T3D:vid,NLTZF(T3D:health-NLTZF(Missile::Data[mobid][Missile::VehicleDamage])));
				} else {
					Tryg3D::GivePlayerDamage(playerid,NLTZF(Missile::Data[mobid][Missile::Damage]),Missile::Data[mobid][Missile::PlayerID],WEAPON_MISSILE_BULLET,3);
				}
			} else {
				if(Missile::Data[mobid][Missile::Damage] == -1.0){
					Cast3D::Explosion(x,y,z,Missile::Data[mobid][Missile::Type],Missile::Data[mobid][Missile::Explode],worldid,interiorid,-1,Missile::GetExplodeVisibility());
				} else {
					Cast3D::ExplosionDMG(x,y,z,Missile::Data[mobid][Missile::Type],Missile::Data[mobid][Missile::Explode],worldid,interiorid,-1,Missile::GetExplodeVisibility(),Missile::Data[mobid][Missile::Damage],Missile::Data[mobid][Missile::VehicleDamage],Missile::Data[mobid][Missile::PlayerID]);
				}
			}
		}
		default: {
			if(Missile::Data[mobid][Missile::Damage] == -1.0){
				Cast3D::Explosion(x,y,z,Missile::Data[mobid][Missile::Type],Missile::Data[mobid][Missile::Explode],worldid,interiorid,-1,Missile::GetExplodeVisibility());
			} else {
				Cast3D::ExplosionDMG(x,y,z,Missile::Data[mobid][Missile::Type],Missile::Data[mobid][Missile::Explode],worldid,interiorid,-1,Missile::GetExplodeVisibility(),Missile::Data[mobid][Missile::Damage],Missile::Data[mobid][Missile::VehicleDamage],Missile::Data[mobid][Missile::PlayerID]);
			}
		}
	}
	if(IsAnyPlayerInDynamicArea(Missile::Data[mobid][Missile::Area],1)){
		for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
			if(IsPlayerConnected(i)){
				if(IsPlayerInDynamicArea(i,Missile::Data[mobid][Missile::Area])){
					CallRemoteFunction("OnMissileDetectPlayer","dd",i,Missile::Data[mobid][Missile::PlayerID]);
				}
			}
		}
	}
	if(IsValidDynamicObject(Missile::Data[mobid][Missile::Object])) DestroyDynamicObject(Missile::Data[mobid][Missile::Object]);
	if(IsValidDynamicArea(Missile::Data[mobid][Missile::Area])) DestroyDynamicArea(Missile::Data[mobid][Missile::Area]);
	new byplayerid = Missile::Data[mobid][Missile::PlayerID];
	CallLocalFunction("OnMissileDestroy","dfffddd",mobid,x,y,z,type,playerid,byplayerid);
	Missile::Data[mobid][Missile::Object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	Missile::Data[mobid][Missile::Area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	Missile::Data[mobid][Missile::Type] = 0;
	Missile::Data[mobid][Missile::Explode] = 0.0;
	Missile::Data[mobid][Missile::PlayerID] = INVALID_PLAYER_ID;
	Missile::Data[mobid][Missile::TeamID] = ANY_TEAM;
	Missile::Data[mobid][Missile::Vehicle] = 0;
	Missile::Data[mobid][Missile::Speed] = 0.0;
	Missile::Data[mobid][Missile::RemoteCount] = 0;
	Missile::Data[mobid][Missile::RemoteID] = 0;
	Missile::Data[mobid][Missile::Damage] = -1.0;
	Missile::Data[mobid][Missile::VehicleDamage] = -1.0;
	Missile::Data[mobid][Missile::TargetID] = INVALID_PLAYER_ID;
	Missile::Data[mobid][Missile::Active] = false;
	if(mobid == Missile::UpperBound) Missile::UpperBound--;
	return 1;
}

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid,weaponid,STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z){
	if(IsValidDynamicObject(objectid)){
		new mobid = (Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
		if(mobid > 0 && mobid < MAX_MISSILE){
			if(Missile::Data[mobid][Missile::Active] && Missile::Data[mobid][Missile::Object] == objectid){
				if((Missile::Data[mobid][Missile::TeamID] != GetPlayerTeam(playerid)) || (Missile::Data[mobid][Missile::TeamID] == ANY_TEAM) || (GetPlayerTeam(playerid) == NO_TEAM)){
					Missile::Destroy(mobid,MISSILE_DESTROY_TYPE_KILL,playerid);
				}
			}
		}
	}
	#if defined MISOnPlayerShootDynamicObject
		MISOnPlayerShootDynamicObject(playerid,weaponid,objectid,x,y,z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject MISOnPlayerShootDynamicObject
#if defined MISOnPlayerShootDynamicObject
	forward MISOnPlayerShootDynamicObject(playerid,weaponid,STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	new pstate = GetPlayerState(playerid);
	if(pstate != 1 && pstate != 2 && pstate != 3) return 1;
	
	new mobid = (Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_MISSILE){
		if(Missile::Data[mobid][Missile::Active] && Missile::Data[mobid][Missile::PlayerID] != playerid && Missile::Data[mobid][Missile::Area] == areaid){
			if((Missile::Data[mobid][Missile::TeamID] != GetPlayerTeam(playerid)) || (Missile::Data[mobid][Missile::TeamID] == ANY_TEAM) || (GetPlayerTeam(playerid) == NO_TEAM)){
				if((Missile::Data[mobid][Missile::Vehicle] != GetPlayerVehicleID(playerid)) || (Missile::Data[mobid][Missile::Vehicle] == 0)){
					if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,Missile::Data[mobid][Missile::Object],E_STREAMER_MODEL_ID) != 18728){
						Missile::Destroy(mobid,MISSILE_DESTROY_TYPE_DETECT,playerid);
					}
				}
			}
		}
	}	
	#if defined MIS_OnPlayerEnterDynamicArea
		MIS_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea MIS_OnPlayerEnterDynamicArea
#if defined MIS_OnPlayerEnterDynamicArea
	forward MIS_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnDynamicObjectMoved
public OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid){
	if(IsValidDynamicObject(objectid)){
		new mobid = (Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-MISSILE_EXTRA_ID_OFFSET);
		if(mobid > 0 && mobid < MAX_MISSILE){
			if(Missile::Data[mobid][Missile::Active] && Missile::Data[mobid][Missile::Object] == objectid){
				if(Missile::Data[mobid][Missile::RemoteCount] == MISSILE_REMOTE_PLAYER){
					if(!IsPlayerConnected(Missile::Data[mobid][Missile::TargetID])){
						Missile::Data[mobid][Missile::TargetID] = INVALID_PLAYER_ID;
						Missile::Data[mobid][Missile::RemoteCount] = 0;
					}
				}
				if(Missile::Data[mobid][Missile::RemoteCount] <= 0 || Missile::Data[mobid][Missile::RemoteCount] == MISSILE_REMOTE_FLARE){
					Missile::Destroy(mobid,MISSILE_DESTROY_TYPE_TARGET,INVALID_PLAYER_ID);
				} else if(Missile::Data[mobid][Missile::RemoteCount] == MISSILE_REMOTE_PLAYER){
					new Float:px,Float:py,Float:pz;
					GetPlayerPos(Missile::Data[mobid][Missile::TargetID],px,py,pz);
					new Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz;
					GetDynamicObjectPos(objectid,x,y,z);
					MovePointCol(x,y,z,px,py,pz,tx,ty,tz);
					if(tx != px || ty != py || tz != pz){
						//collision
						Missile::Data[mobid][Missile::RemoteCount] = 0;
						Missile::RemoteTarget(mobid,tx,ty,tz);
					} else {
						Missile::RemoteTarget(mobid,tx,ty,tz);
					}
				} else {
					Missile::Data[mobid][Missile::RemoteCount]--;
					new remote_id = Missile::Data[mobid][Missile::RemoteID]++;
					new Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz;
					GetDynamicObjectPos(objectid,x,y,z);
					MovePointCol(x,y,z,Missile::Points[mobid][remote_id][0],Missile::Points[mobid][remote_id][1],Missile::Points[mobid][remote_id][2],tx,ty,tz);
					if(tx != Missile::Points[mobid][remote_id][0] || ty != Missile::Points[mobid][remote_id][1] || tz != Missile::Points[mobid][remote_id][2]){
						//collision
						Missile::Data[mobid][Missile::RemoteCount] = 0;
						Missile::RemoteTarget(mobid,tx,ty,tz);
					} else {
						Missile::RemoteTarget(mobid,tx,ty,tz);
					}
				}
			}
		}
	}
	#if defined MIS_OnDynamicObjectMoved
		MIS_OnDynamicObjectMoved(objectid);
	#endif
	return 1;
}

#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif
#define OnDynamicObjectMoved MIS_OnDynamicObjectMoved
#if defined MIS_OnDynamicObjectMoved
	forward MIS_OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid, killerid, reason){
	if(Missile::PlayerAim[playerid]){
		Missile::DisableAllAim(playerid);
	}
	#if defined MIS_OnPlayerDeath
		MIS_OnPlayerDeath(playerid, killerid, reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath MIS_OnPlayerDeath
#if defined MIS_OnPlayerDeath
	forward MIS_OnPlayerDeath(playerid, killerid, reason);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	
	Streamer::ToggleIdleUpdate(playerid,1);
	
	#if defined MIS_OnPlayerConnect
		MIS_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect MIS_OnPlayerConnect
#if defined MIS_OnPlayerConnect
	forward MIS_OnPlayerConnect(playerid);
#endif

//EOF
