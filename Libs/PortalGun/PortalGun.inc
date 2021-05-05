/*
 PortalGun.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg

 File Version: 1.2.1
 Streamer Version: 2.9.4
 ColAndreas Version: 1.4.0
 3DTryg Version: 5.1.0

 Functions:
 TogglePrivatePortalGun(bool:toggle);            //default: false
 bool:IsTogglePrivatePortalGun();
 ToggleUseTeamPortalGun(bool:toggle);            //default: false
 bool:IsToggleUseTeamPortalGun();
 TogglePortalGunForAll(bool:toggle);             //default: true
 bool:IsTogglePortalGunForAll();
 TogglePortalGunForPlayer(playerid,toggle);      //default: 0
 IsTogglePortalGunForPlayer(playerid);
 Float:GetPortalGunSpeed(playerid);
 SetPortalGunSpeed(playerid,Float:speed);
 Float:GetPortalGunStreamDistance();
 SetPortalGunStreamDistance(Float:streamdistance);
 ForceOpenPortalGunRing(playerid,portal_id,Float:ox,Float:oy,Float:oz,Float:tx,Float:ty,Float:tz,worldid,interiorid);
 ForceClosePortalGunRing(playerid);
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

#if defined _portal_gun
	#endinput
#endif
#define _portal_gun
#define DYNAMIC_FILTERSCRIPT					"ALS:HOOK:METHOD"

#define PG_GetValueBit(%0,%1)					((%0) >>> (%1) & 0x01)
#define PG_SetValueBit(%0,%1,%2)				((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define PG_GetConfigAddress(%0)					(floatround((%0)/32))
#define PG_GetConfigBit(%0)						((%0) % 32)
#define PG_GetConfigSize(%0)					(((%0) / 32)+1)

#define PG_IsToggleConfigInformation(%0,%1)		PG_GetValueBit(%0[PG_GetConfigAddress(%1)],PG_GetConfigBit(%1))
#define PG_ToggleConfigInformation(%0,%1,%2)	PG_SetValueBit(%0[PG_GetConfigAddress(%1)],PG_GetConfigBit(%1),((%2) & 0x1))

#define PORTAL_EXTRA_ID_OFFSET					(400000)
#define PORTAL_GUN_SPEED 						(70.0)
#define PORTAL_GUN_BLUE							(0)
#define PORTAL_GUN_ORANGE						(1)

new STREAMER_TAG_OBJECT:PortalGunRing[MAX_PLAYERS][2],
	STREAMER_TAG_AREA:PortalGunZone[MAX_PLAYERS][2],
	PlayerInPortal[MAX_PLAYERS],
	Float:PortalGunSpeed[MAX_PLAYERS],
	PortalEnabledForPlayer[PG_GetConfigSize(MAX_PLAYERS)],
	PlayerPortalType[PG_GetConfigSize(MAX_PLAYERS)],
	Float:PortalGunStreamDistance = 100.0,
	bool:PortalEnabledForAll = true,
	bool:PortalGunUsePlayerTeam = false,
	bool:PrivatePortalGun = false;

#define TogglePrivatePortalGun(%0)			PrivatePortalGun = (%0)
#define IsTogglePrivatePortalGun()			PrivatePortalGun
#define TogglePortalGunForAll(%0)			PortalEnabledForAll = (%0)
#define IsTogglePortalGunForAll()			PortalEnabledForAll
#define TogglePortalGunForPlayer(%0,%1)		PG_ToggleConfigInformation(PortalEnabledForPlayer,(%0),(%1))
#define IsTogglePortalGunForPlayer(%0)		PG_IsToggleConfigInformation(PortalEnabledForPlayer,(%0))
#define SetPortalGunType(%0,%1)				PG_ToggleConfigInformation(PlayerPortalType,(%0),(%1))
#define GetPortalGunType(%0)				PG_IsToggleConfigInformation(PlayerPortalType,(%0))
#define GetPortalGunSpeed(%0)				PortalGunSpeed[(%0)]
#define SetPortalGunSpeed(%0,%1)			PortalGunSpeed[(%0)] = (%1)
#define GetPortalGunStreamDistance()		PortalGunStreamDistance
#define SetPortalGunStreamDistance(%0)		PortalGunStreamDistance = (%0)
#define ToggleUseTeamPortalGun(%0)			PortalGunUsePlayerTeam = (%0)
#define IsToggleUseTeamPortalGun()			PortalGunUsePlayerTeam

T3D:function ForceOpenPortalGunRing(playerid,portal_id,Float:ox,Float:oy,Float:oz,Float:tx,Float:ty,Float:tz,worldid,interiorid){
	new Float:T3D:rx,Float:T3D:rz,Float:px,Float:py,Float:pz;
	
	GetWallRotation(ox,oy,oz, tx,ty,tz, T3D:rx,T3D:rz, px,py,pz, 1.0, 0.2);
	
	if(IsValidDynamicObject(PortalGunRing[playerid][portal_id])) DestroyDynamicObject(PortalGunRing[playerid][portal_id]);
	if(IsValidDynamicArea(PortalGunZone[playerid][portal_id])) DestroyDynamicArea(PortalGunZone[playerid][portal_id]);

	PortalGunRing[playerid][portal_id] = CreateDynamicObject(1316,ox,oy,oz,T3D:rx,0.0,Tryg3D::CompressRotation(T3D:rz-90.0),worldid,interiorid,-1,GetPortalGunStreamDistance());
	if(portal_id == PORTAL_GUN_ORANGE){
		SetDynamicObjectMaterial(PortalGunRing[playerid][portal_id],0,1316,"ingame","CJ_W_GRAD",0xFFFF6600);
	} else {
		SetDynamicObjectMaterial(PortalGunRing[playerid][portal_id],0,1316,"ingame","CJ_W_GRAD",0xFF00FFFF);
	}
	PortalGunZone[playerid][portal_id] = CreateDynamicSphere(0.0,0.0,-6000.0,1.5,worldid,interiorid,-1);
	AttachDynamicAreaToObject(PortalGunZone[playerid][portal_id],PortalGunRing[playerid][portal_id]);
	Streamer::SetIntData(STREAMER_TYPE_AREA,PortalGunZone[playerid][portal_id],E_STREAMER_EXTRA_ID,playerid+PORTAL_EXTRA_ID_OFFSET);
	MoveDynamicObject(PortalGunRing[playerid][portal_id],px,py,pz,GetPortalGunSpeed(playerid));
}

T3D:function ForceClosePortalGunRing(playerid){
	if(IsValidDynamicObject(PortalGunRing[playerid][0])) DestroyDynamicObject(PortalGunRing[playerid][0]);
	if(IsValidDynamicObject(PortalGunRing[playerid][1])) DestroyDynamicObject(PortalGunRing[playerid][1]);
	PortalGunRing[playerid][0] = PortalGunRing[playerid][1] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	
	if(IsValidDynamicArea(PortalGunZone[playerid][0])) DestroyDynamicArea(PortalGunZone[playerid][0]);
	if(IsValidDynamicArea(PortalGunZone[playerid][1])) DestroyDynamicArea(PortalGunZone[playerid][1]);
	PortalGunZone[playerid][0] = PortalGunZone[playerid][1] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	return 1;
}

T3D:function PortalGunInit(){
	for(new i = 0; i < MAX_PLAYERS; i++){
		SetPortalGunSpeed(i,PORTAL_GUN_SPEED);
	}
}

new CRC_PortalInit = true;

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsTogglePortalGunForAll() || IsTogglePortalGunForPlayer(playerid)){
		if(GetPlayerWeapon(playerid) == 33 && !IsPlayerInAnyVehicle(playerid)){
			if(Tryg3D::KeyPressed(KEY_YES)){
				if(GetPortalGunType(playerid)){
					SetPortalGunType(playerid,PORTAL_GUN_BLUE);
					GameTextForPlayer(playerid,"~b~Portal Gun Ring",1500,4);
				} else {
					SetPortalGunType(playerid,PORTAL_GUN_ORANGE);
					GameTextForPlayer(playerid,"~r~~h~~h~Portal Gun Ring",1500,4);
				}
			}
		}
	}
	#if defined PG_OnPlayerKeyStateChange
		PG_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange PG_OnPlayerKeyStateChange
#if defined PG_OnPlayerKeyStateChange
	forward PG_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	ForceClosePortalGunRing(playerid);
	#if defined PG_OnPlayerDisconnect
		PG_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect PG_OnPlayerDisconnect
#if defined PG_OnPlayerDisconnect
	forward PG_OnPlayerDisconnect(playerid,reason);
#endif

//Hook: OnPlayerWeaponShot
public OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ){
	if(IsTogglePortalGunForAll() || IsTogglePortalGunForPlayer(playerid)){
		if(weaponid == 33){
			new portal_id, F4[Float3D];
			if(!(fX == 0.0 || fY == 0.0 || fZ == 0.0)){
				switch(hittype){
					case BULLET_HIT_TYPE_VEHICLE, BULLET_HIT_TYPE_OBJECT, BULLET_HIT_TYPE_PLAYER_OBJECT, BULLET_HIT_TYPE_PLAYER: {
						GetPlayerLastShotVectors(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
					}
					default: {
						GetPlayerLastShotVectors(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
						F4[T3D:tX] = fX, F4[T3D:tY] = fY, F4[T3D:tZ] = fZ;
					}
				}
			}
			if(!(F4[T3D:X] == 0.0 || F4[T3D:Y] == 0.0 || F4[T3D:Z] == 0.0)){
				if(GetPortalGunType(playerid)){
					portal_id = PORTAL_GUN_ORANGE;
				} else {
					portal_id = PORTAL_GUN_BLUE;
				}
				ForceOpenPortalGunRing(playerid,portal_id,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
			}
		}
	}
	#if defined PG_OnPlayerWeaponShot
		PG_OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,fX,fY,fZ);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot PG_OnPlayerWeaponShot
#if defined PG_OnPlayerWeaponShot
	forward PG_OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	new pstate = GetPlayerState(playerid);
	if(pstate != 1 && pstate != 2 && pstate != 3) return 1;
	
	new targetid = (Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID)-PORTAL_EXTRA_ID_OFFSET);
	if(targetid >= 0 && targetid < MAX_PLAYERS){
		if(!IsTogglePrivatePortalGun() || (IsTogglePrivatePortalGun() && playerid == targetid)){
			if(!IsToggleUseTeamPortalGun() || (IsToggleUseTeamPortalGun() && (GetPlayerTeam(playerid) == GetPlayerTeam(targetid) || GetPlayerTeam(targetid) == NO_TEAM || GetPlayerTeam(playerid) == NO_TEAM))){
				new portal_id = -1;
				if(PortalGunZone[targetid][PORTAL_GUN_ORANGE] == areaid){
					portal_id = PORTAL_GUN_BLUE;
				} else if(PortalGunZone[targetid][PORTAL_GUN_BLUE] == areaid){
					portal_id = PORTAL_GUN_ORANGE;
				}
				if(portal_id != -1 && IsValidDynamicObject(PortalGunRing[targetid][portal_id])){
					if(!IsDynamicObjectMoving(PortalGunRing[targetid][PORTAL_GUN_BLUE]) && !IsDynamicObjectMoving(PortalGunRing[targetid][PORTAL_GUN_ORANGE])){
						if(GetTickCount()-PlayerInPortal[playerid] >= 1500){
							PlayerInPortal[playerid] = GetTickCount();
							new F4[Float3D];
							GetDynamicObjectPos(PortalGunRing[targetid][portal_id],F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
							GetDynamicObjectRot(PortalGunRing[targetid][portal_id],F4[T3D:rX],F4[T3D:rY],F4[T3D:rZ]);
							F4[T3D:VW] = Streamer::GetIntData(STREAMER_TYPE_OBJECT,PortalGunRing[targetid][portal_id],E_STREAMER_WORLD_ID);
							F4[T3D:INT] = Streamer::GetIntData(STREAMER_TYPE_OBJECT,PortalGunRing[targetid][portal_id],E_STREAMER_INTERIOR_ID);
							
							F4[T3D:rX] = Tryg3D::CompressRotation(F4[T3D:rX]+90.0);
							
							new Float:T3D:vx,Float:T3D:vy,Float:T3D:vz,
								Float:T3D:tvx,Float:T3D:tvy,Float:T3D:tvz;
							if(IsPlayerInAnyVehicle(playerid)){
								new Float:T3D:x,Float:T3D:y,Float:T3D:z;
								GetVehicleVelocity(GetPlayerVehicleID(playerid),T3D:vx,T3D:vy,T3D:vz);
								ShiftLineRotationVector(0.0,0.0,0.0,T3D:vx,T3D:vy,T3D:vz,Tryg3D::CompressRotation(F4[T3D:rX]+90.0),0.0,F4[T3D:rZ],T3D:tvx,T3D:tvy,T3D:tvz);
								GetVehicleModelInfo(GetVehicleModel(GetPlayerVehicleID(playerid)),VEHICLE_MODEL_INFO_SIZE,T3D:x,T3D:y,T3D:z);
								GetPointInFront3D(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],F4[T3D:rZ],((T3D:y+1.0)/2.0),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
								GetRotationFor2Point2D(F4[T3D:X],F4[T3D:Y],F4[T3D:tX],F4[T3D:tY],F4[T3D:rZ]);
								SetPlayerAbsolutePositionVeh(playerid,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F4[T3D:rZ],F4[T3D:VW],F4[T3D:INT],-1);
								
								SetVehicleVelocity(GetPlayerVehicleID(playerid),T3D:tvx,T3D:tvy,T3D:tvz);
							} else {
								GetPlayerVelocity(playerid,T3D:vx,T3D:vy,T3D:vz);
								ShiftLineRotationVector(0.0,0.0,0.0,T3D:vx,T3D:vy,T3D:vz,Tryg3D::CompressRotation(F4[T3D:rX]+90.0),0.0,F4[T3D:rZ],T3D:tvx,T3D:tvy,T3D:tvz);
								
								GetPointInFront3D(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],F4[T3D:rZ],2.0,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
								GetRotationFor2Point2D(F4[T3D:X],F4[T3D:Y],F4[T3D:tX],F4[T3D:tY],F4[T3D:rZ]);
								SetPlayerAbsolutePosition(playerid,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F4[T3D:rZ],F4[T3D:VW],F4[T3D:INT],-1);
								SetPlayerVelocity(playerid,T3D:tvx,T3D:tvy,T3D:tvz);
							}
						}
					}
				}
			}
		}
	}	
	#if defined PG_OnPlayerEnterDynamicArea
		PG_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea PG_OnPlayerEnterDynamicArea
#if defined PG_OnPlayerEnterDynamicArea
	forward PG_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_PortalInit){
		CRC_PortalInit = false;
		PortalGunInit();
	}
	#if defined PG_OnFilterScriptInit
		PG_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit PG_OnFilterScriptInit
#if defined PG_OnFilterScriptInit
	forward PG_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_PortalInit){
		CRC_PortalInit = false;
		PortalGunInit();
	}
	#if defined PG_OnGameModeInit
		PG_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit PG_OnGameModeInit
#if defined PG_OnGameModeInit
	forward PG_OnGameModeInit();
#endif

//EOF