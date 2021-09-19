/*
 ExtendedGrenade.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg

 File Version: 1.1.2
 Streamer Version: 2.9.5
 ColAndreas Version: 1.5.0
 3DTryg Version: 5.3.0

 Functions:
 Grenade::IsWeaponEnable(playerid,special_weaponid);
 Grenade::WeaponEnable(playerid,special_weaponid,bool:enable);
 Grenade::GetSpecialAmmo(playerid,special_weaponid);
 Grenade::SetSpecialAmmo(playerid,special_weaponid,ammo);
 Grenade::GetEffectID(playerid,special_weaponid);
 Grenade::SetEffectID(playerid,special_weaponid,effectid);
 Grenade::GetDamage(playerid,special_weaponid);
 Grenade::SetDamage(playerid,special_weaponid,Float:damage);
 Grenade::GetVehicleDamage(playerid,special_weaponid);
 Grenade::SetVehicleDamage(playerid,special_weaponid,Float:damage);
 Grenade::GetTime(playerid,special_weaponid);
 Grenade::SetTime(playerid,special_weaponid,seconds);
 Grenade::IsToggleGasMask(playerid);
 Grenade::ToggleGasMask(playerid,bool:toggle);
 Grenade::GetSpecialWeaponID(weaponid);
 Grenade::GrenadeEffectByPlayer(playerid,special_weaponid,Float:x,Float:y,Float:z);
 Grenade::CreateGrenadeEffect(special_weaponid,effectid,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,Float:damage,Float:veh_damage,active_time=25,byplayerid=INVALID_PLAYER_ID);
 Grenade::DestroyEffect(mobid);
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

#if defined _dynamic_mine_system
	#error [ADM] Please include Mines.inc after ExtendedGrenade.inc for improvements
#endif

#if defined _veh_missile_launcher
	#error [ADM] Please include VehicleMissileCol.inc after ExtendedGrenade.inc for improvements
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

#if !defined TRYG3D_GRENADE_DETECTION
	#error [ADM] Module not initialized: TRYG3D_GRENADE_DETECTION (add #define ENABLE_3D_TRYG_GRENADEDETECTION before include 3DTryg.inc)
#endif

#if defined _MISSIONS_INCLUDE
	#error [ADM] Please include ExtendedGrenade before Missions, for initialize new features.
#endif

#if defined _GRENADE_INCLUDE
	#endinput
#endif
#define _GRENADE_INCLUDE
#define DYNAMIC_FILTERSCRIPT							"ALS:HOOK:METHOD"

#define EXTENDED_GRENADE_VERSION						(10100) //a.b.c 10000*a+100*b+c

#define Grenade::										Grenade_

#if !defined MAX_GRENADE_EFFECT
	#define MAX_GRENADE_EFFECT							2048
#endif

#if !defined GRENADE_DOT_TEAR_GAS
	#define GRENADE_DOT_TEAR_GAS						1.0
#endif

#if !defined GRENADE_DOT_FIRE
	#define GRENADE_DOT_FIRE							3.0
#endif

#if !defined GRENADE_EFFECT_TIME
	#define GRENADE_EFFECT_TIME							25	//seconds
#endif

#if !defined GRENADE_DEFAULT_PLAYER_DAMAGE
	#define GRENADE_DEFAULT_PLAYER_DAMAGE				82.5
#endif

#if !defined GRENADE_DEFAULT_VEHICLE_DAMAGE
	#define GRENADE_DEFAULT_VEHICLE_DAMAGE				825.0
#endif

#define INVALID_GRENADE_ID								-1

#define WEAPON_SUFFOCATION						 		100
#define WEAPON_NAPALM									101

#define GRENADE_MAX_SPECIAL_WEAPON						4

#define GRENADE_SPECIAL_WEAPON_NONE						0
#define GRENADE_SPECIAL_WEAPON_GRENADE					1
#define GRENADE_SPECIAL_WEAPON_TEARGAS					2
#define GRENADE_SPECIAL_WEAPON_MOLTOV					3

#define GRENADE_EFFECT_NONE								0

#define GRENADE_EFFECT_CLUSTER_BOMB_1					1
#define GRENADE_EFFECT_CLUSTER_BOMB_2					2
#define GRENADE_EFFECT_CLUSTER_BOMB_3					3
#define GRENADE_EFFECT_CLUSTER_BOMB_4					4
#define GRENADE_EFFECT_BANG_GRENADE						5

#define GRENADE_EFFECT_SMALL_SMOKE						1
#define GRENADE_EFFECT_HUGE_SMOKE_1						2
#define GRENADE_EFFECT_HUGE_SMOKE_2						3
#define GRENADE_EFFECT_HUGE_SMOKE_3						4

#define GRENADE_EFFECT_NAPALM							1

#define GRENADE_EXTRA_ID_OFFSET							1200000

enum Grenade::EnumPlayer {
	bool:	Grenade::Enabled[GRENADE_MAX_SPECIAL_WEAPON],
	bool:	Grenade::GasMask,
			Grenade::EffectID[GRENADE_MAX_SPECIAL_WEAPON],
			Grenade::Ammo[GRENADE_MAX_SPECIAL_WEAPON],
	Float:	Grenade::Damage[GRENADE_MAX_SPECIAL_WEAPON],
	Float:	Grenade::VehicleDamage[GRENADE_MAX_SPECIAL_WEAPON],
			Grenade::Time[GRENADE_MAX_SPECIAL_WEAPON],
			Grenade::StunTime,
	Float:	Grenade::GasDOT,
	Float:	Grenade::FireDOT
};

enum Grenade::EnumEffect {
	bool:					Grenade::Active,
							Grenade::Type,
							Grenade::Time,
	Float:					Grenade::DOT,
							Grenade::PlayerID,
	STREAMER_TAG_AREA:		Grenade::Area,
	STREAMER_TAG_OBJECT:	Grenade::Object[17]
};

new Grenade::PlayerData[MAX_PLAYERS][Grenade::EnumPlayer],
	Grenade::EffectData[MAX_GRENADE_EFFECT][Grenade::EnumEffect],
	Grenade::UpperBound = -1,
	Grenade::UpdateTimer,
	Text: Grenade::TextDrawFlash[3];

#define Grenade_IsWeaponEnable(%0,%1)			(Grenade::PlayerData[(%0)][Grenade::Enabled][(%1)])
#define Grenade_WeaponEnable(%0,%1,%2)			(Grenade::PlayerData[(%0)][Grenade::Enabled][(%1)] = (%2))

#define Grenade_GetSpecialAmmo(%0,%1)			(Grenade::PlayerData[(%0)][Grenade::Ammo][(%1)])
#define Grenade_SetSpecialAmmo(%0,%1,%2)		(Grenade::PlayerData[(%0)][Grenade::Ammo][(%1)] = (%2))

#define Grenade_GetEffectID(%0,%1)				(Grenade::PlayerData[(%0)][Grenade::EffectID][(%1)])
#define Grenade_SetEffectID(%0,%1,%2)			(Grenade::PlayerData[(%0)][Grenade::EffectID][(%1)] = (%2))

#define Grenade_GetDamage(%0,%1)				(Grenade::PlayerData[(%0)][Grenade::Damage][(%1)])
#define Grenade_SetDamage(%0,%1,%2)				(Grenade::PlayerData[(%0)][Grenade::Damage][(%1)] = (%2))

#define Grenade_GetVehicleDamage(%0,%1)			(Grenade::PlayerData[(%0)][Grenade::VehicleDamage][(%1)])
#define Grenade_SetVehicleDamage(%0,%1,%2)		(Grenade::PlayerData[(%0)][Grenade::VehicleDamage][(%1)] = (%2))

#define Grenade_GetTime(%0,%1)					(Grenade::PlayerData[(%0)][Grenade::Time][(%1)])
#define Grenade_SetTime(%0,%1,%2)				(Grenade::PlayerData[(%0)][Grenade::Time][(%1)] = (%2))

#define Grenade_IsToggleGasMask(%0)				(Grenade::PlayerData[(%0)][Grenade::GasMask])
#define Grenade_ToggleGasMask(%0,%1)			(Grenade::PlayerData[(%0)][Grenade::GasMask] = (%1))

stock Grenade::GetSpecialWeaponID(weaponid){
	switch(weaponid){
		case WEAPON_GRENADE: return GRENADE_SPECIAL_WEAPON_GRENADE;
		case WEAPON_TEARGAS: return GRENADE_SPECIAL_WEAPON_TEARGAS;
		case WEAPON_MOLTOV: return GRENADE_SPECIAL_WEAPON_MOLTOV;
	}
	return GRENADE_SPECIAL_WEAPON_NONE;
}

stock Grenade::GetFreeID(){
	for(new mobid = 1; mobid < MAX_GRENADE_EFFECT; mobid++){
		if(!Grenade::EffectData[mobid][Grenade::Active]) return mobid;
	}
	return INVALID_GRENADE_ID;
}

stock Grenade::CreateGrenadeEffect(special_weaponid,effectid,Float:x,Float:y,Float:z,worldid,interiorid,playerid,Float:streamdistance,Float:damage,Float:veh_damage,active_time=25,byplayerid=INVALID_PLAYER_ID){
	if(special_weaponid == GRENADE_SPECIAL_WEAPON_NONE || effectid == GRENADE_EFFECT_NONE) return INVALID_GRENADE_ID;
	new Float:tx,Float:ty,Float:tz,Float:rx,Float:rz;
	if(special_weaponid == GRENADE_SPECIAL_WEAPON_GRENADE){
		switch(effectid){
			case GRENADE_EFFECT_CLUSTER_BOMB_1: {
				for(new Grenade::i = 0; Grenade::i < 10; Grenade::i++){
					Random::PointInCircle(x,y,5.0,tx,ty);
					ColAndreas::FindZ_For2DCoord(tx,ty,tz);
					Cast3D::ExplosionDMG(tx,ty,tz+0.2,12,2.0,worldid,interiorid,playerid,streamdistance,damage,veh_damage,byplayerid);
				}
			}
			case GRENADE_EFFECT_CLUSTER_BOMB_2: {
				for(new Grenade::i = 0; Grenade::i < 8; Grenade::i++){
					Random::PointInCircle(x,y,15.0,tx,ty);
					ColAndreas::FindZ_For2DCoord(tx,ty,tz);
					Cast3D::ExplosionDMG(tx,ty,tz+0.2,2,2.0,worldid,interiorid,playerid,streamdistance,damage,veh_damage,byplayerid);
				}
			}
			case GRENADE_EFFECT_CLUSTER_BOMB_3: {
				for(new Grenade::i = 0; Grenade::i < 6; Grenade::i++){
					Random::PointInCircle(x,y,15.0,tx,ty);
					ColAndreas::FindZ_For2DCoord(tx,ty,tz);
					Cast3D::ExplosionDMG(tx,ty,tz+0.2,6,2.0,worldid,interiorid,playerid,streamdistance,damage,veh_damage,byplayerid);
				}
			}
			case GRENADE_EFFECT_CLUSTER_BOMB_4: {
				for(new Grenade::i = 0; Grenade::i < 6; Grenade::i++){
					Random::PointInCircle(x,y,20.0,tx,ty);
					ColAndreas::FindZ_For2DCoord(tx,ty,tz);
					Cast3D::ExplosionDMG(tx,ty,tz+0.2,7,2.0,worldid,interiorid,playerid,streamdistance,damage,veh_damage,byplayerid);
				}
			}
			case GRENADE_EFFECT_BANG_GRENADE: {
				Tryg3D::Foreach(eg_playerid){
					GetPlayerPos(eg_playerid,tx,ty,tz);
					GetPlayerCameraRotation(eg_playerid,rx,rz);
					if(Area::PointInSphericalSectorEx(x,y,z,tx,ty,tz,rx,rz,100.0,VERTICAL_CAMERA_RADIUS,HORIZONTAL_CAMERA_RADIUS,.collision_flags = TRYG3D_COLLISION_FLAG_OBJECT + TRYG3D_COLLISION_FLAG_VEHICLE)){
						if(Grenade::PlayerData[eg_playerid][Grenade::StunTime] == 0){
							Grenade::PlayerData[eg_playerid][Grenade::StunTime] = GetTickCount() + 5000;
						} else {
							Grenade::PlayerData[eg_playerid][Grenade::StunTime] += 5000;
						}
						TextDrawShowForPlayer(eg_playerid,Grenade::TextDrawFlash[0]);
						TextDrawHideForPlayer(eg_playerid,Grenade::TextDrawFlash[1]);
						TextDrawHideForPlayer(eg_playerid,Grenade::TextDrawFlash[2]);
					}
				}
			}
		}
		return INVALID_GRENADE_ID;
	}
	new mobid = Grenade::GetFreeID();
	if(mobid == INVALID_GRENADE_ID) return INVALID_GRENADE_ID;
	if(mobid > Grenade::UpperBound) Grenade::UpperBound = mobid;
	Grenade::EffectData[mobid][Grenade::Active] = true;
	Grenade::EffectData[mobid][Grenade::Type] = special_weaponid;
	Grenade::EffectData[mobid][Grenade::Time] = GetTickCount() + (active_time*1000);
	Grenade::EffectData[mobid][Grenade::PlayerID] = byplayerid;
	
	new Float:Grenade::Modiffier;
	switch(special_weaponid){
		case GRENADE_SPECIAL_WEAPON_TEARGAS: {
			switch(effectid){
				case GRENADE_EFFECT_SMALL_SMOKE: {
					Grenade::EffectData[mobid][Grenade::DOT] += damage;
					
					Grenade::EffectData[mobid][Grenade::Object][0] = CreateDynamicObject(18715,x,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Area] = CreateDynamicSphere(x,y,z,5.0,worldid,interiorid,-1);
					Streamer::SetIntData(STREAMER_TYPE_AREA,Grenade::EffectData[mobid][Grenade::Area],E_STREAMER_EXTRA_ID,GRENADE_EXTRA_ID_OFFSET+mobid);
				}
				case GRENADE_EFFECT_HUGE_SMOKE_1: {
					Grenade::EffectData[mobid][Grenade::DOT] += damage;
					
					Grenade::Modiffier = 7.0;
					Grenade::EffectData[mobid][Grenade::Object][0] = CreateDynamicObject(18715,x,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][1] = CreateDynamicObject(18715,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][2] = CreateDynamicObject(18715,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][3] = CreateDynamicObject(18715,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][4] = CreateDynamicObject(18715,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][5] = CreateDynamicObject(18715,x,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][6] = CreateDynamicObject(18715,x,y-Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][7] = CreateDynamicObject(18715,x+Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][8] = CreateDynamicObject(18715,x-Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Area] = CreateDynamicSphere(x,y,z,21.0,worldid,interiorid,-1);
					Streamer::SetIntData(STREAMER_TYPE_AREA,Grenade::EffectData[mobid][Grenade::Area],E_STREAMER_EXTRA_ID,GRENADE_EXTRA_ID_OFFSET+mobid);
				}
				case GRENADE_EFFECT_HUGE_SMOKE_2: {
					Grenade::EffectData[mobid][Grenade::DOT] += damage;
					
					Grenade::Modiffier = 8.0;
					Grenade::EffectData[mobid][Grenade::Object][0] = CreateDynamicObject(18671,x,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][1] = CreateDynamicObject(18671,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][2] = CreateDynamicObject(18671,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][3] = CreateDynamicObject(18671,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][4] = CreateDynamicObject(18671,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][5] = CreateDynamicObject(18671,x,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][6] = CreateDynamicObject(18671,x,y-Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][7] = CreateDynamicObject(18671,x+Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][8] = CreateDynamicObject(18671,x-Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Area] = CreateDynamicSphere(x,y,z,24.0,worldid,interiorid,-1);
					Streamer::SetIntData(STREAMER_TYPE_AREA,Grenade::EffectData[mobid][Grenade::Area],E_STREAMER_EXTRA_ID,GRENADE_EXTRA_ID_OFFSET+mobid);
				}
				case GRENADE_EFFECT_HUGE_SMOKE_3: {
					Grenade::EffectData[mobid][Grenade::DOT] += damage;
					
					Grenade::Modiffier = 10.0;
					Grenade::EffectData[mobid][Grenade::Object][0] = CreateDynamicObject(18697,x,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][1] = CreateDynamicObject(18697,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][2] = CreateDynamicObject(18697,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][3] = CreateDynamicObject(18697,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][4] = CreateDynamicObject(18697,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][5] = CreateDynamicObject(18697,x,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][6] = CreateDynamicObject(18697,x,y-Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][7] = CreateDynamicObject(18697,x+Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][8] = CreateDynamicObject(18697,x-Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Area] = CreateDynamicSphere(x,y,z,30.0,worldid,interiorid,-1);
					Streamer::SetIntData(STREAMER_TYPE_AREA,Grenade::EffectData[mobid][Grenade::Area],E_STREAMER_EXTRA_ID,GRENADE_EXTRA_ID_OFFSET+mobid);
				}
			}
		}
		case GRENADE_SPECIAL_WEAPON_MOLTOV: {
			switch(effectid){
				case GRENADE_EFFECT_NAPALM: {
					Grenade::EffectData[mobid][Grenade::DOT] += damage;
					
					Grenade::Modiffier = 2.0;
					z-= 1.0;
					Grenade::EffectData[mobid][Grenade::Object][0] = CreateDynamicObject(18691,x,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][1] = CreateDynamicObject(18691,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][2] = CreateDynamicObject(18691,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][3] = CreateDynamicObject(18691,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][4] = CreateDynamicObject(18691,x+Grenade::Modiffier,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][5] = CreateDynamicObject(18691,x,y+Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][6] = CreateDynamicObject(18691,x,y-Grenade::Modiffier,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][7] = CreateDynamicObject(18691,x+Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][8] = CreateDynamicObject(18691,x-Grenade::Modiffier,y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][9] = CreateDynamicObject(18691,x+(Grenade::Modiffier*2.0),y+(Grenade::Modiffier*2.0),z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][10] = CreateDynamicObject(18691,x+(Grenade::Modiffier*2.0),y+(Grenade::Modiffier*2.0),z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][11] = CreateDynamicObject(18691,x+(Grenade::Modiffier*2.0),y+(Grenade::Modiffier*2.0),z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][12] = CreateDynamicObject(18691,x+(Grenade::Modiffier*2.0),y+(Grenade::Modiffier*2.0),z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Object][13] = CreateDynamicObject(18691,x,y+(Grenade::Modiffier*2.0),z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][14] = CreateDynamicObject(18691,x,y-(Grenade::Modiffier*2.0),z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][15] = CreateDynamicObject(18691,x+(Grenade::Modiffier*2.0),y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					Grenade::EffectData[mobid][Grenade::Object][16] = CreateDynamicObject(18691,x-(Grenade::Modiffier*2.0),y,z,0.0,0.0,0.0,worldid,interiorid,-1,streamdistance,streamdistance);
					
					Grenade::EffectData[mobid][Grenade::Area] = CreateDynamicSphere(x,y,z,10.0,worldid,interiorid,-1);
					Streamer::SetIntData(STREAMER_TYPE_AREA,Grenade::EffectData[mobid][Grenade::Area],E_STREAMER_EXTRA_ID,GRENADE_EXTRA_ID_OFFSET+mobid);
				}
			}
		}
	}
	return mobid;
}

stock Grenade::GrenadeEffectByPlayer(playerid,special_weaponid,Float:x,Float:y,Float:z){
	return Grenade::CreateGrenadeEffect(special_weaponid,Grenade::GetEffectID(playerid,special_weaponid),x,y,z,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,Grenade::GetDamage(playerid,special_weaponid),Grenade::GetVehicleDamage(playerid,special_weaponid),Grenade::GetTime(playerid,special_weaponid),playerid);
}

stock Grenade::DestroyEffect(mobid){
	for(new Grenade::i = 0; Grenade::i < 9; Grenade::i++){
		if(IsValidDynamicObject(Grenade::EffectData[mobid][Grenade::Object][Grenade::i])){
			DestroyDynamicObject(Grenade::EffectData[mobid][Grenade::Object][Grenade::i]);
			Grenade::EffectData[mobid][Grenade::Object][Grenade::i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		}
	}
	if(Grenade::EffectData[mobid][Grenade::Type] == GRENADE_SPECIAL_WEAPON_MOLTOV){
		for(new Grenade::i = 9; Grenade::i < 17; Grenade::i++){
			if(IsValidDynamicObject(Grenade::EffectData[mobid][Grenade::Object][Grenade::i])){
				DestroyDynamicObject(Grenade::EffectData[mobid][Grenade::Object][Grenade::i]);
				Grenade::EffectData[mobid][Grenade::Object][Grenade::i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
			}
		}
	}
	if(IsValidDynamicArea(Grenade::EffectData[mobid][Grenade::Area])){
		DestroyDynamicArea(Grenade::EffectData[mobid][Grenade::Area]);
		Grenade::EffectData[mobid][Grenade::Area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	Grenade::EffectData[mobid][Grenade::PlayerID] = INVALID_PLAYER_ID;
	Grenade::EffectData[mobid][Grenade::Time] = 0;
	Grenade::EffectData[mobid][Grenade::DOT] = 0.0;
	Grenade::EffectData[mobid][Grenade::Type] = GRENADE_SPECIAL_WEAPON_NONE;
	Grenade::EffectData[mobid][Grenade::Active] = false;
	if(mobid == Grenade::UpperBound) Grenade::UpperBound--;
}

T3D:function Grenade::OnUpdate(){
	new cur_tick = GetTickCount(),Float:T3D:health,Float:T3D:armour,byplayerid,STREAMER_TAG_AREA:player_areas[128], mobid;
	Tryg3D::Foreach(playerid){
		if(!IsPlayerInAnyVehicle(playerid)){
			byplayerid = INVALID_PLAYER_ID;
			GetPlayerArmour(playerid,T3D:armour);
			GetPlayerHealth(playerid,T3D:health);
			if(T3D:armour == 0.0 && T3D:health-(Grenade::PlayerData[playerid][Grenade::GasDOT]+Grenade::PlayerData[playerid][Grenade::FireDOT]) <= 0.0){
				new max_areas = GetPlayerNumberDynamicAreas(playerid);
				if(max_areas){
					GetPlayerDynamicAreas(playerid,player_areas,max_areas);
					for(new k = 0; k < max_areas; k++){
						if(k >= 128) break;
						mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID) - GRENADE_EXTRA_ID_OFFSET;
						if(mobid >= 0 && mobid < MAX_GRENADE_EFFECT){
							if(player_areas[k] == Grenade::EffectData[mobid][Grenade::Area]){
								byplayerid = Grenade::EffectData[mobid][Grenade::PlayerID];
							}
						}
					}
				}
			}
			if(!Grenade::PlayerData[playerid][Grenade::GasMask]){
				if(Grenade::PlayerData[playerid][Grenade::GasDOT] > 0.0){
					Tryg3D::GivePlayerDamage(playerid,Grenade::PlayerData[playerid][Grenade::GasDOT],byplayerid,WEAPON_SUFFOCATION,9);	
				}
			}
			if(Grenade::PlayerData[playerid][Grenade::FireDOT] > 0.0){
				Tryg3D::GivePlayerDamage(playerid,Grenade::PlayerData[playerid][Grenade::FireDOT],byplayerid,WEAPON_NAPALM,9);	
			}
		}
		if(Grenade::PlayerData[playerid][Grenade::StunTime] != 0){
			if(cur_tick >= Grenade::PlayerData[playerid][Grenade::StunTime]){
				Grenade::PlayerData[playerid][Grenade::StunTime] = 0;
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[0]);
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[1]);
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[2]);
			} else if(cur_tick >= Grenade::PlayerData[playerid][Grenade::StunTime]-1500){
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[0]);
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[1]);
				TextDrawShowForPlayer(playerid,Grenade::TextDrawFlash[2]);
			} else if(cur_tick >= Grenade::PlayerData[playerid][Grenade::StunTime]-3000){
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[0]);
				TextDrawShowForPlayer(playerid,Grenade::TextDrawFlash[1]);
				TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[2]);
			}
		}
	}
	for(mobid = 1; mobid <= Grenade::UpperBound; mobid++){
		if(cur_tick >= Grenade::EffectData[mobid][Grenade::Time]){
			Grenade::DestroyEffect(mobid);
		}
	}
}

stock Grenade::Init(){
	Grenade::TextDrawFlash[0] = TextDrawCreate(0.0,0.0,"~n~~n~~n~~n~~n~~n~~n~");
	TextDrawLetterSize(Grenade::TextDrawFlash[0],0.0,10.0);
	TextDrawUseBox(Grenade::TextDrawFlash[0],1);
	TextDrawBoxColor(Grenade::TextDrawFlash[0],0xFFFFFFEE);
	
	Grenade::TextDrawFlash[1] = TextDrawCreate(0.0,0.0,"~n~~n~~n~~n~~n~~n~~n~");
	TextDrawLetterSize(Grenade::TextDrawFlash[1],0.0,10.0);
	TextDrawUseBox(Grenade::TextDrawFlash[1],1);
	TextDrawBoxColor(Grenade::TextDrawFlash[1],0xFFFFFFAA);
	
	Grenade::TextDrawFlash[2] = TextDrawCreate(0.0,0.0,"~n~~n~~n~~n~~n~~n~~n~");
	TextDrawLetterSize(Grenade::TextDrawFlash[2],0.0,10.0);
	TextDrawUseBox(Grenade::TextDrawFlash[2],1);
	TextDrawBoxColor(Grenade::TextDrawFlash[2],0xFFFFFF50);
	
	TextDrawHideForAll(Grenade::TextDrawFlash[0]);
	TextDrawHideForAll(Grenade::TextDrawFlash[1]);
	TextDrawHideForAll(Grenade::TextDrawFlash[2]);
	
	for(new playerid = 0; playerid < MAX_PLAYERS; playerid++){
		Grenade::SetDamage(playerid,GRENADE_SPECIAL_WEAPON_GRENADE,GRENADE_DEFAULT_PLAYER_DAMAGE);
		Grenade::SetVehicleDamage(playerid,GRENADE_SPECIAL_WEAPON_GRENADE,GRENADE_DEFAULT_VEHICLE_DAMAGE);
		
		Grenade::SetDamage(playerid,GRENADE_SPECIAL_WEAPON_TEARGAS,GRENADE_DOT_TEAR_GAS);
		Grenade::SetTime(playerid,GRENADE_SPECIAL_WEAPON_TEARGAS,GRENADE_EFFECT_TIME);
		
		Grenade::SetDamage(playerid,GRENADE_SPECIAL_WEAPON_MOLTOV,GRENADE_DOT_FIRE);
		Grenade::SetTime(playerid,GRENADE_SPECIAL_WEAPON_MOLTOV,GRENADE_EFFECT_TIME);
	}
	Grenade::UpdateTimer = SetTimer("Grenade_OnUpdate",1000,true);
}

stock Grenade::Exit(){
	TextDrawDestroy(Grenade::TextDrawFlash[0]);
	TextDrawDestroy(Grenade::TextDrawFlash[1]);
	TextDrawDestroy(Grenade::TextDrawFlash[2]);
	KillTimer(Grenade::UpdateTimer);
}

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	Grenade::ToggleGasMask(playerid,false);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[0]);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[1]);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[2]);
	#if defined EG_OnPlayerConnect
		EG_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect EG_OnPlayerConnect
#if defined EG_OnPlayerConnect
	forward EG_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[0]);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[1]);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[2]);
	Grenade::PlayerData[playerid][Grenade::GasDOT] = 0.0;
	Grenade::PlayerData[playerid][Grenade::FireDOT] = 0.0;
	#if defined EG_OnPlayerSpawn
		EG_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn EG_OnPlayerSpawn
#if defined EG_OnPlayerSpawn
	forward EG_OnPlayerSpawn(playerid);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid, killerid, reason){
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[0]);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[1]);
	TextDrawHideForPlayer(playerid,Grenade::TextDrawFlash[2]);
	Grenade::PlayerData[playerid][Grenade::GasDOT] = 0.0;
	Grenade::PlayerData[playerid][Grenade::FireDOT] = 0.0;
	#if defined EG_OnPlayerDeath
		EG_OnPlayerDeath(playerid, killerid, reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath EG_OnPlayerDeath
#if defined EG_OnPlayerDeath
	forward EG_OnPlayerDeath(playerid, killerid, reason);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	new mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID) - GRENADE_EXTRA_ID_OFFSET;
	if(mobid > 0 && mobid < MAX_GRENADE_EFFECT){
		if(Grenade::EffectData[mobid][Grenade::Area] == areaid){
			switch(Grenade::EffectData[mobid][Grenade::Type]){
				case GRENADE_SPECIAL_WEAPON_TEARGAS: {
					Grenade::PlayerData[playerid][Grenade::GasDOT] += Grenade::EffectData[mobid][Grenade::DOT];
				}
				case GRENADE_SPECIAL_WEAPON_MOLTOV: {
					Grenade::PlayerData[playerid][Grenade::FireDOT] += Grenade::EffectData[mobid][Grenade::DOT];
				}
			}
			
		}
	}
	#if defined EG_OnPlayerEnterDynamicArea
		EG_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea EG_OnPlayerEnterDynamicArea
#if defined EG_OnPlayerEnterDynamicArea
	forward EG_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerLeaveDynamicArea
public OnPlayerLeaveDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	new mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID) - GRENADE_EXTRA_ID_OFFSET;
	if(mobid > 0 && mobid < MAX_GRENADE_EFFECT){
		if(Grenade::EffectData[mobid][Grenade::Area] == areaid){
			switch(Grenade::EffectData[mobid][Grenade::Type]){
				case GRENADE_SPECIAL_WEAPON_TEARGAS: {
					Grenade::PlayerData[playerid][Grenade::GasDOT] -= Grenade::EffectData[mobid][Grenade::DOT];
				}
				case GRENADE_SPECIAL_WEAPON_MOLTOV: {
					Grenade::PlayerData[playerid][Grenade::FireDOT] -= Grenade::EffectData[mobid][Grenade::DOT];
				}
			}
		}
	}
	#if defined EG_OnPlayerLeaveDynamicArea
		EG_OnPlayerLeaveDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea EG_OnPlayerLeaveDynamicArea
#if defined EG_OnPlayerLeaveDynamicArea
	forward EG_OnPlayerLeaveDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerDroppingGrenade
public OnPlayerDroppingGrenade(playerid,weaponid,Float:x,Float:y,Float:z){
	new special_weaponid = Grenade::GetSpecialWeaponID(weaponid);
	if(special_weaponid != GRENADE_SPECIAL_WEAPON_NONE){
		if(Grenade::IsWeaponEnable(playerid,special_weaponid) && Grenade::GetSpecialAmmo(playerid,special_weaponid) > 0){
			Grenade::SetSpecialAmmo(playerid,special_weaponid,Grenade::GetSpecialAmmo(playerid,special_weaponid)-1);
			Grenade::GrenadeEffectByPlayer(playerid,special_weaponid,x,y,z);
		}
	}
	#if defined EG_OnPlayerDroppingGrenade
		EG_OnPlayerDroppingGrenade(playerid,weaponid,x,y,z);
	#endif
	return 1;
}

#if defined EG_OnPlayerDroppingGrenade
	forward EG_OnPlayerDroppingGrenade(playerid,weaponid,Float:x,Float:y,Float:z);
#endif
#if defined _ALS_OnPlayerDroppingGrenade
	#undef OnPlayerDroppingGrenade
#else
	#define _ALS_OnPlayerDroppingGrenade
#endif
#define OnPlayerDroppingGrenade EG_OnPlayerDroppingGrenade

new CRC_ExtendedGrenadenInit = true,
	CRC_ExtendedGrenadenExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_ExtendedGrenadenInit){
		CRC_ExtendedGrenadenInit = false;
		Grenade::Init();
	}
	#if defined EG_OnFilterScriptInit
		EG_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit EG_OnFilterScriptInit
#if defined EG_OnFilterScriptInit
	forward EG_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_ExtendedGrenadenInit){
		CRC_ExtendedGrenadenInit = false;
		Grenade::Init();
	}
	#if defined EG_OnGameModeInit
		EG_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit EG_OnGameModeInit
#if defined EG_OnGameModeInit
	forward EG_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_ExtendedGrenadenExit){
		CRC_ExtendedGrenadenExit = false;
		Grenade::Exit();
	}
	#if defined EG_OnFilterScriptExit
		EG_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit EG_OnFilterScriptExit
#if defined EG_OnFilterScriptExit
	forward EG_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_ExtendedGrenadenExit){
		CRC_ExtendedGrenadenExit = false;
		Grenade::Exit();
	}
	#if defined EG_OnGameModeExit
		EG_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit EG_OnGameModeExit
#if defined EG_OnGameModeExit
	forward EG_OnGameModeExit();
#endif
//EOF