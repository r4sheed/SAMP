/*
 Magic.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: Katarina Calzaghe

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg

 File Version: 1.3.0
 Streamer Version: 2.9.4
 ColAndreas Version: 1.4.0
 3DTryg Version: 5.1.0

 Functions:
 Magic::ToggleUseTeam(bool:toggle);            //default: false
 Magic::IsToggleUseTeam();
 Magic::ToggleForAll(bool:toggle);             //default: false
 Magic::IsToggleForAll();
 Magic::ToggleForPlayer(playerid,bool:toggle); //default: false
 Magic::IsToggleForPlayer(playerid);
 Magic::GetDamage(playerid);
 Magic::SetDamage(playerid,Float:amount);
 Magic::GetSpeed(playerid);
 Magic::SetSpeed(playerid,Float:speed);
 Magic::GetRange(playerid);
 Magic::SetRange(playerid,Float:range);
 Magic::GetAmmo(playerid);
 Magic::SetAmmo(playerid,ammo);
 Magic::TogglePoisoning(playerid,bool:toggle);
 Magic::IsTogglePoisoning(playerid);
 Magic::GetPoisoningTime(playerid);
 Magic::SetPoisoningTime(playerid,seconds);
 Magic::GetPoisoningDamage(playerid);
 Magic::SetPoisoningDamage(playerid,Float:damage);
 Magic::SetProjectile(playerid,modelid=18693,Float:rx=90.0,Float:ry=0.0,Float:rz=0.0,Float:offx=0.0,Float:offy=0.0,Float:offz=0.0);
 Magic::GetProjectile(playerid,&modelid,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:offx=0.0,&Float:offy=0.0,&Float:offz=0.0);

 Callbacks:
 OnPlayerRequestMagicShot(playerid,targetid);
*/

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.4 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS
	#error [ADM] You need ColAndreas v1.4.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v5.1.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v5.1.0
#elseif (TRYG3D_VERSION < 50100)
	#error [ADM] Update you 3DTryg.inc to v5.1.0
#endif

#if defined _magic_shot
	#endinput
#endif
#define _magic_shot
#define DYNAMIC_FILTERSCRIPT				"ALS:HOOK:METHOD"

#define MAGIC_SHOT_VERSION					(1.3.0) //a.b.c 10000*a+100*b+c

#define Magic::								Magic_

#if !defined MAGIC_SPEED
	#define MAGIC_SPEED 					(12.0)
#endif

#if !defined MAGIC_MAX_RADIUS
	#define MAGIC_MAX_RADIUS				(15.0)
#endif

#if !defined MAGIC_DAMAGE
	#define MAGIC_DAMAGE					(10.0)
#endif

#if !defined MAGIC_DOT_POISONING
	#define MAGIC_DOT_POISONING				(2.5)
#endif

#if !defined MAGIC_POISONING_TIME
	#define MAGIC_POISONING_TIME			(15)	//seconds
#endif

#define WEAPON_MAGIC_BULLET					(106)
#define WEAPON_MAGIC_POISONING				(107)

#define MAGIC_REFRESH_ACTION				(1000)	//1 sec
	
#define MAGIC_WEAPON_AMMO_INFINITY			(-1)

enum Magic::EnumPlayer {
			Magic::LockTarget,
			Magic::Step,
			Magic::Time,
	Float:	Magic::Damage,
	Float:	Magic::Speed,
	Float:	Magic::Range,
	Float:	Magic::DOT,
			Magic::TimeDOT,
			Magic::PoisoningActive,
			Magic::PoisoningTime,
	Float:	Magic::PoisoningDMG,
			Magic::Ammo,
			Magic::PoisoningKiller,
	bool:	Magic::Enabled,
			Magic::Projectile[Float3D]
};

new 		Magic::PlayerData[MAX_PLAYERS][Magic::EnumPlayer],
	bool:	Magic::EnabledForAll = false,
	bool:	Magic::UsePlayerTeam = false,
			Magic::UpdateTimer;

#define Magic_ToggleUseTeam(%0)				Magic::UsePlayerTeam = (%0)
#define Magic_IsToggleUseTeam()				Magic::UsePlayerTeam
#define Magic_ToggleForAll(%0)				Magic::EnabledForAll = (%0)
#define Magic_IsToggleForAll()				Magic::EnabledForAll
#define Magic_IsToggleForPlayer(%0)			Magic::PlayerData[(%0)][Magic::Enabled]
#define Magic_GetDamage(%0)					Magic::PlayerData[(%0)][Magic::Damage]
#define Magic_SetDamage(%0,%1)				Magic::PlayerData[(%0)][Magic::Damage] = (%1)
#define Magic_GetSpeed(%0)					Magic::PlayerData[(%0)][Magic::Speed]
#define Magic_SetSpeed(%0,%1)				Magic::PlayerData[(%0)][Magic::Speed] = (%1)
#define Magic_GetRange(%0)					Magic::PlayerData[(%0)][Magic::Range]
#define Magic_SetRange(%0,%1)				Magic::PlayerData[(%0)][Magic::Range] = (%1)
#define Magic_GetAmmo(%0)					Magic::PlayerData[(%0)][Magic::Ammo]
#define Magic_SetAmmo(%0,%1)				Magic::PlayerData[(%0)][Magic::Ammo] = (%1)
#define Magic_IsTogglePoisoning(%0)			Magic::PlayerData[(%0)][Magic::PoisoningActive]
#define Magic_TogglePoisoning(%0,%1)		Magic::PlayerData[(%0)][Magic::PoisoningActive] = (%1)
#define Magic_GetPoisoningTime(%0)			Magic::PlayerData[(%0)][Magic::PoisoningTime]
#define Magic_SetPoisoningTime(%0,%1)		Magic::PlayerData[(%0)][Magic::PoisoningTime] = (%1)
#define Magic_GetPoisoningDamage(%0)		Magic::PlayerData[(%0)][Magic::PoisoningDMG]
#define Magic_SetPoisoningDamage(%0,%1)		Magic::PlayerData[(%0)][Magic::PoisoningDMG] = (%1)

#if defined OnPlayerRequestMagicShot
	forward OnPlayerRequestMagicShot(playerid,targetid);
#endif

stock Magic::SetProjectile(playerid,modelid=18693,Float:rx=90.0,Float:ry=0.0,Float:rz=0.0,Float:offx=0.0,Float:offy=0.0,Float:offz=0.0){
	Magic::PlayerData[playerid][Magic::Projectile][T3D:INT] = modelid;
	Magic::PlayerData[playerid][Magic::Projectile][T3D:rX] = rx;
	Magic::PlayerData[playerid][Magic::Projectile][T3D:rY] = ry;
	Magic::PlayerData[playerid][Magic::Projectile][T3D:rZ] = rz;
	Magic::PlayerData[playerid][Magic::Projectile][T3D:X] = offx;
	Magic::PlayerData[playerid][Magic::Projectile][T3D:Y] = offy;
	Magic::PlayerData[playerid][Magic::Projectile][T3D:Z] = offz;
}

stock Magic::GetProjectile(playerid,&modelid,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:offx=0.0,&Float:offy=0.0,&Float:offz=0.0){
	modelid = Magic::PlayerData[playerid][Magic::Projectile][T3D:INT];
	rx = Magic::PlayerData[playerid][Magic::Projectile][T3D:rX];
	ry = Magic::PlayerData[playerid][Magic::Projectile][T3D:rY];
	rz = Magic::PlayerData[playerid][Magic::Projectile][T3D:rZ];
	offx = Magic::PlayerData[playerid][Magic::Projectile][T3D:X];
	offy = Magic::PlayerData[playerid][Magic::Projectile][T3D:Y];
	offz = Magic::PlayerData[playerid][Magic::Projectile][T3D:Z];
}

stock Magic::ToggleForPlayer(playerid,bool:toggle){
	Magic::PlayerData[playerid][Magic::Enabled] = toggle;
	if(toggle){
		SetPlayerAttachedObject(playerid,7,338,6,0.080000,-0.010000,0.000000,0.000000,353.134094,65.000000,0.300000,0.300000,0.300000);
	} else {
		RemovePlayerAttachedObject(playerid,7);
	}
}

T3D:function Magic::Shot(playerid){
	new Float:mx, Float:my, Float:mz, Float:mrz, Float:mtx, Float:mty, Float:mtz, mvw, mint,
		Float:px, Float:py, Float:pz, mtime, pteam, Float:ldist = 20000, Float:dist;
	GetPlayerPos(playerid,mx,my,mz);
	GetPlayerFacingAngle(playerid,mrz);
	mvw = GetPlayerVirtualWorld(playerid);
	mint = GetPlayerInterior(playerid);
	GetPointInFront2D(mx,my,mrz,Magic::GetRange(playerid),mtx,mty);
	Magic::PlayerData[playerid][Magic::LockTarget] = INVALID_PLAYER_ID;
	pteam = GetPlayerTeam(playerid);
	
	Tryg3D::Foreach(i){
		if(i != playerid){
			if(!Magic::IsToggleUseTeam() || (Magic::IsToggleUseTeam() && (pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM))){
				if(Tryg3D::IsPlayerSpawned(i)){
					GetPlayerPos(i,px,py,pz);
					if(GetPlayerVirtualWorld(i) == mvw && GetPlayerInterior(i) == mint){
						if(Area::PointInCylinder3D(px,py,pz,mx,my,mz,mtx,mty,mz,2.0)){
							if((dist = GetDistanceBetweenPoints3D(px,py,pz,mx,my,mz)) < ldist){
								ldist = dist;
								Magic::PlayerData[playerid][Magic::LockTarget] = i;
							}
						}
					}
				}
			}
		}
	}
	
	#if defined OnPlayerRequestMagicShot
		if(!OnPlayerRequestMagicShot(playerid,Magic::PlayerData[playerid][Magic::LockTarget])) return INVALID_PLAYER_ID;
	#endif
	
	if(Magic::GetAmmo(playerid) != MAGIC_WEAPON_AMMO_INFINITY){
		if(Magic::GetAmmo(playerid) <= 0) return 1;
		Magic::SetAmmo(playerid,Magic::GetAmmo(playerid)-1);
	}
	
	ApplyAnimation(playerid,"KNIFE","knife_3",4.1,0,1,1,0,0,1);
	if(Magic::PlayerData[playerid][Magic::LockTarget] == INVALID_PLAYER_ID){
		new STREAMER_TAG_OBJECT:tmpobj = CreateDynamicObject(Magic::PlayerData[playerid][Magic::Projectile][T3D:INT],mx+Magic::PlayerData[playerid][Magic::Projectile][T3D:X],my+Magic::PlayerData[playerid][Magic::Projectile][T3D:Y],mz+Magic::PlayerData[playerid][Magic::Projectile][T3D:Z],Magic::PlayerData[playerid][Magic::Projectile][T3D:rX],Magic::PlayerData[playerid][Magic::Projectile][T3D:rY],Tryg3D::CompressRotation(mrz+Magic::PlayerData[playerid][Magic::Projectile][T3D:rZ]),mvw,mint,-1,_,100.0);
		GetDynamicObjectPos(tmpobj,mx,my,mz);
		GetPointInFront3DCol(mx,my,mz,0.0,mrz,Magic::GetRange(playerid),mtx,mty,mtz);		
		GetMoveTime(mx,my,mz,mtx,mty,mtz,Magic::GetSpeed(playerid),mtime);
		MoveDynamicObject(tmpobj,mtx,mty,mtz,Magic::GetSpeed(playerid),Magic::PlayerData[playerid][Magic::Projectile][T3D:rX],Magic::PlayerData[playerid][Magic::Projectile][T3D:rY],Tryg3D::CompressRotation(mrz+Magic::PlayerData[playerid][Magic::Projectile][T3D:rZ]));
		SetTimerEx("Magic_Destroy",mtime,0,"ddd",_:tmpobj,INVALID_PLAYER_ID,playerid);
	} else {
		GetPlayerPos(Magic::PlayerData[playerid][Magic::LockTarget],px,py,pz);
		GetRotationFor2Point2D(mx,my,px,py,mrz);
		new STREAMER_TAG_OBJECT:tmpobj = CreateDynamicObject(Magic::PlayerData[playerid][Magic::Projectile][T3D:INT],mx+Magic::PlayerData[playerid][Magic::Projectile][T3D:X],my+Magic::PlayerData[playerid][Magic::Projectile][T3D:Y],mz+Magic::PlayerData[playerid][Magic::Projectile][T3D:Z],Magic::PlayerData[playerid][Magic::Projectile][T3D:rX],Magic::PlayerData[playerid][Magic::Projectile][T3D:rY],Tryg3D::CompressRotation(mrz+Magic::PlayerData[playerid][Magic::Projectile][T3D:rZ]),mvw,mint,-1,_,100.0);
		GetDynamicObjectPos(tmpobj,mx,my,mz);
		GetMoveTime(mx,my,mz,px,py,pz,Magic::GetSpeed(playerid),mtime);
		MoveDynamicObject(tmpobj,px,py,pz,Magic::GetSpeed(playerid),Magic::PlayerData[playerid][Magic::Projectile][T3D:rX],Magic::PlayerData[playerid][Magic::Projectile][T3D:rY],Tryg3D::CompressRotation(mrz+Magic::PlayerData[playerid][Magic::Projectile][T3D:rZ]));
		SetTimerEx("Magic_Destroy",mtime,0,"ddd",_:tmpobj,Magic::PlayerData[playerid][Magic::LockTarget],playerid);
	}
	Magic::PlayerData[playerid][Magic::Time] = GetTickCount();
	return Magic::PlayerData[playerid][Magic::LockTarget];
}

T3D:function Magic::Destroy(STREAMER_TAG_OBJECT:objectid,targetid,playerid){
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	if(targetid != INVALID_PLAYER_ID){
		Tryg3D::GivePlayerDamage(targetid,Magic::GetDamage(playerid),playerid,WEAPON_MAGIC_BULLET,3);
		ApplyAnimation(targetid,"ped","SHOT_partial",4.1,0,1,1,1,1,1);
		if(Magic::IsTogglePoisoning(playerid)){
			if(Magic::GetPoisoningDamage(playerid) > Magic::PlayerData[targetid][Magic::DOT]){
				Magic::PlayerData[targetid][Magic::DOT] = Magic::GetPoisoningDamage(playerid);
				if(Magic::PlayerData[targetid][Magic::TimeDOT] == 0){
					Magic::PlayerData[targetid][Magic::TimeDOT] = GetTickCount()+(Magic::GetPoisoningTime(playerid)*1000);
				} else {
					Magic::PlayerData[targetid][Magic::TimeDOT] += (Magic::GetPoisoningTime(playerid)*1000);
				}
				Magic::PlayerData[targetid][Magic::PoisoningKiller] = playerid;
				SetPlayerAttachedObject(targetid,0,18729,1,0.1,0.1,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
			}
		}
	}
	return 1;
}

T3D:function Magic::OnUpdate(){
	new cur_tick = GetTickCount();
	Tryg3D::Foreach(playerid){
		if(Magic::PlayerData[playerid][Magic::DOT] > 0.0){
			if(cur_tick >= Magic::PlayerData[playerid][Magic::TimeDOT] && Magic::PlayerData[playerid][Magic::TimeDOT] != 0){
				Magic::PlayerData[playerid][Magic::TimeDOT] = 0;
				Magic::PlayerData[playerid][Magic::DOT] = 0;
				Magic::PlayerData[playerid][Magic::PoisoningKiller] = INVALID_PLAYER_ID;
				RemovePlayerAttachedObject(playerid,0);
			} else if(Magic::PlayerData[playerid][Magic::TimeDOT] != 0){
				SetPlayerAttachedObject(playerid,0,18729,1,0.1,0.1,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
				Tryg3D::GivePlayerDamage(playerid,Magic::PlayerData[playerid][Magic::DOT],Magic::PlayerData[playerid][Magic::PoisoningKiller],WEAPON_MAGIC_POISONING,3);
			}
		}
	}
	return 1;
}

T3D:function Magic::Init(){
	for(new i = 0; i < MAX_PLAYERS; i++){
		Magic::SetDamage(i,MAGIC_DAMAGE);
		Magic::SetSpeed(i,MAGIC_SPEED);
		Magic::SetRange(i,MAGIC_MAX_RADIUS);
		Magic::SetProjectile(i);
		Magic::SetAmmo(i,MAGIC_WEAPON_AMMO_INFINITY);
		Magic::SetPoisoningTime(i,MAGIC_POISONING_TIME);
		Magic::SetPoisoningDamage(i,MAGIC_DOT_POISONING);
		Magic::PlayerData[i][Magic::PoisoningKiller] = INVALID_PLAYER_ID;
	}
	Magic::UpdateTimer = SetTimer("Magic_OnUpdate",1000,true);
}

T3D:function Magic::Exit(){
	KillTimer(Magic::UpdateTimer);
	return 1;
}

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(Magic::IsToggleForAll() || Magic::IsToggleForPlayer(playerid)){
		if(GetTickCount()-Magic::PlayerData[playerid][Magic::Time] >= MAGIC_REFRESH_ACTION){
			if(GetPlayerWeapon(playerid) == 0 && Tryg3D::KeyPressed(KEY_FIRE) && !IsPlayerInAnyVehicle(playerid)){
				Magic::Shot(playerid);
			}
		}
	}
	#if defined Magic_OnPlayerKeyStateChange
		Magic_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange Magic_OnPlayerKeyStateChange
#if defined Magic_OnPlayerKeyStateChange
	forward Magic_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	Magic::ToggleForPlayer(playerid,false);
	Magic::SetDamage(playerid,MAGIC_DAMAGE);
	Magic::SetSpeed(playerid,MAGIC_SPEED);
	Magic::SetRange(playerid,MAGIC_MAX_RADIUS);
	Magic::SetAmmo(playerid,MAGIC_WEAPON_AMMO_INFINITY);
	Magic::SetPoisoningTime(playerid,MAGIC_POISONING_TIME);
	Magic::SetPoisoningDamage(playerid,MAGIC_DOT_POISONING);
	Magic::PlayerData[playerid][Magic::PoisoningKiller] = INVALID_PLAYER_ID;
	#if defined Magic_OnPlayerConnect
		Magic_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Magic_OnPlayerConnect
#if defined Magic_OnPlayerConnect
	forward Magic_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	Magic::PlayerData[playerid][Magic::DOT] = 0.0;
	Magic::PlayerData[playerid][Magic::TimeDOT] = 0;
	Magic::PlayerData[playerid][Magic::PoisoningKiller] = INVALID_PLAYER_ID;
	#if defined Magic_OnPlayerSpawn
		Magic_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn Magic_OnPlayerSpawn
#if defined Magic_OnPlayerSpawn
	forward Magic_OnPlayerSpawn(playerid);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid, killerid, reason){
	Magic::PlayerData[playerid][Magic::DOT] = 0.0;
	Magic::PlayerData[playerid][Magic::TimeDOT] = 0;
	Magic::PlayerData[playerid][Magic::PoisoningKiller] = INVALID_PLAYER_ID;
	#if defined Magic_OnPlayerDeath
		Magic_OnPlayerDeath(playerid, killerid, reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath Magic_OnPlayerDeath
#if defined Magic_OnPlayerDeath
	forward Magic_OnPlayerDeath(playerid, killerid, reason);
#endif

new bool:CRC_MagicInit = true,
	bool:CRC_MagicExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_MagicInit){
		CRC_MagicInit = false;
		Magic::Init();
	}
	#if defined Magic_OnFilterScriptInit
		Magic_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Magic_OnFilterScriptInit
#if defined Magic_OnFilterScriptInit
	forward Magic_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_MagicInit){
		CRC_MagicInit = false;
		Magic::Init();
	}
	#if defined Magic_OnGameModeInit
		Magic_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Magic_OnGameModeInit
#if defined Magic_OnGameModeInit
	forward Magic_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_MagicExit){
		CRC_MagicExit = false;
		Magic::Exit();
	}
	#if defined Magic_OnFilterScriptExit
		Magic_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit Magic_OnFilterScriptExit
#if defined Magic_OnFilterScriptExit
	forward Magic_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_MagicExit){
		CRC_MagicExit = false;
		Magic::Exit();
	}
	#if defined Magic_OnGameModeExit
		Magic_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit Magic_OnGameModeExit
#if defined Magic_OnGameModeExit
	forward Magic_OnGameModeExit();
#endif
//EOF