/*
 Knife.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: Katarina Calzaghe

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg

 File Version: 2.7.0
 Streamer Version: 2.9.5
 ColAndreas Version: 1.5.0
 3DTryg Version: 5.2.0

 Functions:
 Knife::ToggleUseTeam(bool:toggle);            //default: false
 Knife::IsToggleUseTeam();
 Knife::ToggleForAll(bool:toggle);             //default: false
 Knife::IsToggleForAll();
 Knife::ToggleForPlayer(playerid,bool:toggle); //default: false
 Knife::IsToggleForPlayer(playerid);
 Knife::GetDamage(playerid);
 Knife::SetDamage(playerid,Float:amount);
 Knife::GetSpeed(playerid);
 Knife::SetSpeed(playerid,Float:speed);
 Knife::GetRange(playerid);
 Knife::SetRange(playerid,Float:range);
 Knife::GetAmmo(playerid);
 Knife::SetAmmo(playerid,ammo);
 Knife::TogglePoisoning(playerid,bool:toggle);
 Knife::IsTogglePoisoning(playerid);
 Knife::GetPoisoningTime(playerid);
 Knife::SetPoisoningTime(playerid,seconds);
 Knife::GetPoisoningDamage(playerid);
 Knife::SetPoisoningDamage(playerid,Float:damage);

 Callbacks:
 OnPlayerRequestKnifeShot(playerid,targetid);
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
	#error [ADM] This include required 3DTryg.inc v5.2.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to v5.2.0
#elseif (TRYG3D_VERSION < 50200)
	#error [ADM] Update your 3DTryg.inc to v5.2.0
#endif

#if !defined TRYG3D_COLANDREAS
	#error [ADM] Module not initialized: TRYG3D_COLANDREAS
#endif

#if defined _knife_shot
	#endinput
#endif
#define _knife_shot
#define DYNAMIC_FILTERSCRIPT				"ALS:HOOK:METHOD"

#define KNIFE_SHOT_VERSION					(20700) //a.b.c 10000*a+100*b+c

#define Knife::								Knife_

#if !defined KNIFE_SPEED
	#define KNIFE_SPEED 					(12.0)
#endif

#if !defined KNIFE_MAX_RADIUS
	#define KNIFE_MAX_RADIUS				(15.0)
#endif

#if !defined KNIFE_DAMAGE
	#define KNIFE_DAMAGE					(10.0)
#endif

#if !defined KNIFE_DOT_POISONING
	#define KNIFE_DOT_POISONING				(2.5)
#endif

#if !defined KNIFE_POISONING_TIME
	#define KNIFE_POISONING_TIME			(15)	//seconds
#endif

#define WEAPON_KNIFE_THROWN					(103)
#define WEAPON_KNIFE_POISONING				(104)

#define KNIFE_REFRESH_ACTION				(1000)	//1 sec
#define KNIFE_REFRESH_MISS					(5000)	//5 sec

#define KNIFE_WEAPON_AMMO_INFINITY			(-1)

enum Knife::EnumPlayer {
			Knife::LockTarget,
			Knife::Step,
			Knife::Time,
	Float:	Knife::Damage,
	Float:	Knife::Speed,
	Float:	Knife::Range,
	Float:	Knife::DOT,
			Knife::TimeDOT,
			Knife::PoisoningActive,
			Knife::PoisoningTime,
	Float:	Knife::PoisoningDMG,
			Knife::Ammo,
			Knife::PoisoningKiller,
	bool:	Knife::Enabled
};

new 		Knife::PlayerData[MAX_PLAYERS][Knife::EnumPlayer],
	bool:	Knife::EnabledForAll = false,
	bool:	Knife::UsePlayerTeam = false,
			Knife::UpdateTimer;

#define Knife_ToggleUseTeam(%0)				Knife::UsePlayerTeam = (%0)
#define Knife_IsToggleUseTeam()				Knife::UsePlayerTeam
#define Knife_ToggleForAll(%0)				Knife::EnabledForAll = (%0)
#define Knife_IsToggleForAll()				Knife::EnabledForAll
#define Knife_ToggleForPlayer(%0,%1)		Knife::PlayerData[(%0)][Knife::Enabled] = (%1)
#define Knife_IsToggleForPlayer(%0)			Knife::PlayerData[(%0)][Knife::Enabled]
#define Knife_GetDamage(%0)					Knife::PlayerData[(%0)][Knife::Damage]
#define Knife_SetDamage(%0,%1)				Knife::PlayerData[(%0)][Knife::Damage] = (%1)
#define Knife_GetSpeed(%0)					Knife::PlayerData[(%0)][Knife::Speed]
#define Knife_SetSpeed(%0,%1)				Knife::PlayerData[(%0)][Knife::Speed] = (%1)
#define Knife_GetRange(%0)					Knife::PlayerData[(%0)][Knife::Range]
#define Knife_SetRange(%0,%1)				Knife::PlayerData[(%0)][Knife::Range] = (%1)
#define Knife_GetAmmo(%0)					Knife::PlayerData[(%0)][Knife::Ammo]
#define Knife_SetAmmo(%0,%1)				Knife::PlayerData[(%0)][Knife::Ammo] = (%1)
#define Knife_IsTogglePoisoning(%0)			Knife::PlayerData[(%0)][Knife::PoisoningActive]
#define Knife_TogglePoisoning(%0,%1)		Knife::PlayerData[(%0)][Knife::PoisoningActive] = (%1)
#define Knife_GetPoisoningTime(%0)			Knife::PlayerData[(%0)][Knife::PoisoningTime]
#define Knife_SetPoisoningTime(%0,%1)		Knife::PlayerData[(%0)][Knife::PoisoningTime] = (%1)
#define Knife_GetPoisoningDamage(%0)		Knife::PlayerData[(%0)][Knife::PoisoningDMG]
#define Knife_SetPoisoningDamage(%0,%1)		Knife::PlayerData[(%0)][Knife::PoisoningDMG] = (%1)

#if defined OnPlayerRequestKnifeShot
	forward OnPlayerRequestKnifeShot(playerid,targetid);
#endif

T3D:function Knife::Shot(playerid){
	new Float:mx, Float:my, Float:mz, Float:mrz, Float:mtx, Float:mty, Float:mtz, mvw, mint, Float:trz,
		Float:px, Float:py, Float:pz, mtime, pteam, Float:T3D:dist;
	GetPlayerPos(playerid,mx,my,mz);
	GetPlayerFacingAngle(playerid,mrz);
	mvw = GetPlayerVirtualWorld(playerid);
	mint = GetPlayerInterior(playerid);
	GetPointInFront2D(mx,my,mrz,Knife::GetRange(playerid),mtx,mty);
	Knife::PlayerData[playerid][Knife::LockTarget] = INVALID_PLAYER_ID;
	new Float:T3D:ldist = 20000;
	pteam = GetPlayerTeam(playerid);
	
	Tryg3D::Foreach(i){
		if(i != playerid){
			if(!Knife::IsToggleUseTeam() || (Knife::IsToggleUseTeam() && (pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM))){
				if(Tryg3D::IsPlayerSpawned(i)){
					GetPlayerPos(i,px,py,pz);
					if(GetPlayerVirtualWorld(i) == mvw && GetPlayerInterior(i) == mint){
						if(Area::PointInCylinder3D(px,py,pz,mx,my,mz,mtx,mty,mz,2.0)){
							if((T3D:dist = GetDistanceBetweenPoints3D(px,py,pz,mx,my,mz)) < T3D:ldist){
								T3D:ldist = T3D:dist;
								Knife::PlayerData[playerid][Knife::LockTarget] = i;
							}
						}
					}
				}
			}
		}
	}
	
	#if defined OnPlayerRequestKnifeShot
		if(!OnPlayerRequestKnifeShot(playerid,Knife::PlayerData[playerid][Knife::LockTarget])) return INVALID_PLAYER_ID;
	#endif
	
	if(Knife::GetAmmo(playerid) != KNIFE_WEAPON_AMMO_INFINITY){
		if(Knife::GetAmmo(playerid) <= 0) return INVALID_PLAYER_ID;
		Knife::SetAmmo(playerid,Knife::GetAmmo(playerid)-1);
	}
	
	if(Knife::PlayerData[playerid][Knife::LockTarget] == INVALID_PLAYER_ID){
		trz = Tryg3D::CompressRotation(mrz+90.0);
		new STREAMER_TAG_OBJECT:tmpobj = CreateDynamicObject(335,mx,my,mz,0.0,90.0,trz,mvw,mint,-1);
		GetPointInFront3DCol(mx,my,mz,356.7,mrz,Knife::GetRange(playerid),mtx,mty,mtz);		
		GetMoveTime(mx,my,mz,mtx,mty,mtz,Knife::GetSpeed(playerid),mtime);
		MoveDynamicObject(tmpobj,mtx,mty,mtz,Knife::GetSpeed(playerid),0.0,110.0,trz);
		SetTimerEx("Knife_Destroy",mtime+KNIFE_REFRESH_MISS,false,"ddd",_:tmpobj,INVALID_PLAYER_ID,playerid);
	} else {
		GetPlayerPos(Knife::PlayerData[playerid][Knife::LockTarget],px,py,pz);
		GetRotationFor2Point2D(mx,my,px,py,trz);
		trz = Tryg3D::CompressRotation(trz+90.0);
		new STREAMER_TAG_OBJECT:tmpobj = CreateDynamicObject(335,mx,my,mz,0.0,90.0,trz,mvw,mint,-1);
		GetMoveTime(mx,my,mz,px,py,pz,Knife::GetSpeed(playerid),mtime);
		MoveDynamicObject(tmpobj,px,py,pz,Knife::GetSpeed(playerid),0.0,90.0,trz);
		SetTimerEx("Knife_Destroy",mtime,false,"ddd",_:tmpobj,Knife::PlayerData[playerid][Knife::LockTarget],playerid);
	}
	Knife::PlayerData[playerid][Knife::Time] = GetTickCount();
	return Knife::PlayerData[playerid][Knife::LockTarget];
}

T3D:function Knife::Destroy(STREAMER_TAG_OBJECT:objectid,targetid,playerid){
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	if(targetid != INVALID_PLAYER_ID){
		Tryg3D::GivePlayerDamage(targetid,Knife::GetDamage(playerid),playerid,WEAPON_KNIFE_THROWN,3);
		ApplyAnimation(targetid,"ped","SHOT_partial",4.1,0,1,1,1,1,1);
		if(Knife::IsTogglePoisoning(playerid)){
			if(Knife::GetPoisoningDamage(playerid) > Knife::PlayerData[targetid][Knife::DOT]){
				Knife::PlayerData[targetid][Knife::DOT] = Knife::GetPoisoningDamage(playerid);
				if(Knife::PlayerData[targetid][Knife::TimeDOT] == 0){
					Knife::PlayerData[targetid][Knife::TimeDOT] = GetTickCount()+(Knife::GetPoisoningTime(playerid)*1000);
				} else {
					Knife::PlayerData[targetid][Knife::TimeDOT] += (Knife::GetPoisoningTime(playerid)*1000);
				}
				Knife::PlayerData[targetid][Knife::PoisoningKiller] = playerid;
				SetPlayerAttachedObject(targetid,0,18729,1,0.1,0.1,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
			}
		}
	}
	return 1;
}

T3D:function Knife::OnUpdate(){
	new cur_tick = GetTickCount();
	Tryg3D::Foreach(playerid){
		if(Knife::PlayerData[playerid][Knife::DOT] > 0.0){
			if(cur_tick >= Knife::PlayerData[playerid][Knife::TimeDOT] && Knife::PlayerData[playerid][Knife::TimeDOT] != 0){
				Knife::PlayerData[playerid][Knife::TimeDOT] = 0;
				Knife::PlayerData[playerid][Knife::DOT] = 0;
				Knife::PlayerData[playerid][Knife::PoisoningKiller] = INVALID_PLAYER_ID;
				RemovePlayerAttachedObject(playerid,0);
			} else if(Knife::PlayerData[playerid][Knife::TimeDOT] != 0){
				SetPlayerAttachedObject(playerid,0,18729,1,0.1,0.1,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
				Tryg3D::GivePlayerDamage(playerid,Knife::PlayerData[playerid][Knife::DOT],Knife::PlayerData[playerid][Knife::PoisoningKiller],WEAPON_KNIFE_POISONING,3);
			}
		}
	}
	return 1;
}

T3D:function Knife::Init(){
	for(new i = 0; i < MAX_PLAYERS; i++){
		Knife::SetDamage(i,KNIFE_DAMAGE);
		Knife::SetSpeed(i,KNIFE_SPEED);
		Knife::SetRange(i,KNIFE_MAX_RADIUS);
		Knife::SetAmmo(i,KNIFE_WEAPON_AMMO_INFINITY);
		Knife::SetPoisoningTime(i,KNIFE_POISONING_TIME);
		Knife::SetPoisoningDamage(i,KNIFE_DOT_POISONING);
		Knife::PlayerData[i][Knife::PoisoningKiller] = INVALID_PLAYER_ID;
	}
	Knife::UpdateTimer = SetTimer("Knife_OnUpdate",1000,true);
	return 1;
}

T3D:function Knife::Exit(){
	KillTimer(Knife::UpdateTimer);
	return 1;
}

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if((Knife::IsToggleForAll() || Knife::IsToggleForPlayer(playerid)) && !IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) == 0){
		if(GetTickCount()-Knife::PlayerData[playerid][Knife::Time] >= KNIFE_REFRESH_ACTION){
			if(GetPlayerWeapon(playerid) == 4){
				if(newkeys == KEY_FIRE && Knife::PlayerData[playerid][Knife::Step] == 1){
					Knife::PlayerData[playerid][Knife::Step] = 0;
					Knife::Shot(playerid);
				}
				if(newkeys == KEY_HANDBRAKE && Knife::PlayerData[playerid][Knife::Step] == 0){
					Knife::PlayerData[playerid][Knife::Step] = 1;
				}
			}
		}
	}
	#if defined Knife_OnPlayerKeyStateChange
		Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange Knife_OnPlayerKeyStateChange
#if defined Knife_OnPlayerKeyStateChange
	forward Knife_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	Knife::ToggleForPlayer(playerid,false);
	Knife::SetDamage(playerid,KNIFE_DAMAGE);
	Knife::SetSpeed(playerid,KNIFE_SPEED);
	Knife::SetRange(playerid,KNIFE_MAX_RADIUS);
	Knife::SetAmmo(playerid,KNIFE_WEAPON_AMMO_INFINITY);
	Knife::SetPoisoningTime(playerid,KNIFE_POISONING_TIME);
	Knife::SetPoisoningDamage(playerid,KNIFE_DOT_POISONING);
	Knife::PlayerData[playerid][Knife::PoisoningKiller] = INVALID_PLAYER_ID;
	#if defined Knife_OnPlayerConnect
		Knife_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Knife_OnPlayerConnect
#if defined Knife_OnPlayerConnect
	forward Knife_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	Knife::PlayerData[playerid][Knife::DOT] = 0.0;
	Knife::PlayerData[playerid][Knife::TimeDOT] = 0;
	Knife::PlayerData[playerid][Knife::PoisoningKiller] = INVALID_PLAYER_ID;
	#if defined Knife_OnPlayerSpawn
		Knife_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn Knife_OnPlayerSpawn
#if defined Knife_OnPlayerSpawn
	forward Knife_OnPlayerSpawn(playerid);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid, killerid, reason){
	Knife::PlayerData[playerid][Knife::DOT] = 0.0;
	Knife::PlayerData[playerid][Knife::TimeDOT] = 0;
	Knife::PlayerData[playerid][Knife::PoisoningKiller] = INVALID_PLAYER_ID;
	#if defined Knife_OnPlayerDeath
		Knife_OnPlayerDeath(playerid, killerid, reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath Knife_OnPlayerDeath
#if defined Knife_OnPlayerDeath
	forward Knife_OnPlayerDeath(playerid, killerid, reason);
#endif


new bool:CRC_KnifeInit = true,
	bool:CRC_KnifeExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_KnifeInit){
		CRC_KnifeInit = false;
		Knife::Init();
	}
	#if defined Knife_OnFilterScriptInit
		Knife_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Knife_OnFilterScriptInit
#if defined Knife_OnFilterScriptInit
	forward Knife_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_KnifeInit){
		CRC_KnifeInit = false;
		Knife::Init();
	}
	#if defined Knife_OnGameModeInit
		Knife_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Knife_OnGameModeInit
#if defined Knife_OnGameModeInit
	forward Knife_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_KnifeExit){
		CRC_KnifeExit = false;
		Knife::Exit();
	}
	#if defined Knife_OnFilterScriptExit
		Knife_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit Knife_OnFilterScriptExit
#if defined Knife_OnFilterScriptExit
	forward Knife_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_KnifeExit){
		CRC_KnifeExit = false;
		Knife::Exit();
	}
	#if defined Knife_OnGameModeExit
		Knife_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit Knife_OnGameModeExit
#if defined Knife_OnGameModeExit
	forward Knife_OnGameModeExit();
#endif
//EOF