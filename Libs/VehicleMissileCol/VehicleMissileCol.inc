/*
 VehicleMissileCol.inc
 Copyright © 2022 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg, Missile

 File Version: 2.0.0
 Streamer Version: 2.9.5
 ColAndreas Version: 1.5.0
 3DTryg Version: Gen. 2 v1.0.0
 Missile Version: 2.3.0

 Vehicle Weapons:
 - Mini Missile (Dual rocket)
 - Heavy Missile (Six rocket of high firepower)
 - Rhino Missile (Rhino explosion)
 - Bomber Missile (Quadruple-ground missiles)
 - Mortar Missile (Marica mortar)
 - Mega Missile (Heavy Marica mortar)
 - Congreve Rocket (Large area of destruction)
 - Havoc Rocket (Circle ground missile)
 - Ground Bomb (Standard bomb)

 Functions Mini Missile:
 ToggleVehicleMiniMissile(vehicleid,toggle);
 IsToggleVehicleMiniMissile(vehicleid);
 Float:GetVehicleMiniMissileSpeed(vehicleid);
 SetVehicleMiniMissileSpeed(vehicleid,Float:speed);
 GetVehicleMiniMissileReload(vehicleid);
 SetVehicleMiniMissileReload(vehicleid,time);
 Float:GetVehicleMiniMissileDistance(vehicleid);
 SetVehicleMiniMissileDistance(vehicleid,Float:distance);
 GetVehicleMiniMissileKey(vehicleid);
 SetVehicleMiniMissileKey(vehicleid,key);
 GetVehicleMiniMissileAmmo(vehicleid);
 SetVehicleMiniMissileAmmo(vehicleid,ammo);
 Float:GetVehicleMiniMissileDMG(vehicleid);
 SetVehicleMiniMissileDMG(vehicleid,Float:damage);
 Float:GetVehicleMiniMissileVehDMG(vehicleid);
 SetVehicleMiniMissileVehDMG(vehicleid,Float:damage);

 Functions Heavy Missile:
 ToggleVehicleHeavyMissile(vehicleid,toggle);
 IsToggleVehicleHeavyMissile(vehicleid);
 Float:GetVehicleHeavyMissileSpeed(vehicleid);
 SetVehicleHeavyMissileSpeed(vehicleid,Float:speed);
 GetVehicleHeavyMissileReload(vehicleid);
 SetVehicleHeavyMissileReload(vehicleid,time);
 Float:GetVehicleHeavyMissileDistance(vehicleid);
 SetVehicleHeavyMissileDistance(vehicleid,Float:distance);
 GetVehicleHeavyMissileKey(vehicleid);
 SetVehicleHeavyMissileKey(vehicleid,key);
 GetVehicleHeavyMissileAmmo(vehicleid);
 SetVehicleHeavyMissileAmmo(vehicleid,ammo);
 Float:GetVehicleHeavyMissileDMG(vehicleid);
 SetVehicleHeavyMissileDMG(vehicleid,Float:damage);
 Float:GetVehicleHeavyMissileVehDMG(vehicleid);
 SetVehicleHeavyMissileVehDMG(vehicleid,Float:damage);

 Functions Rhino Missile:
 ToggleVehicleRhinoMissile(vehicleid,toggle);
 IsToggleVehicleRhinoMissile(vehicleid);
 GetVehicleRhinoMissileReload(vehicleid);
 SetVehicleRhinoMissileReload(vehicleid,time);
 Float:GetVehicleRhinoMissileDistance(vehicleid);
 SetVehicleRhinoMissileDistance(vehicleid,Float:distance);
 GetVehicleRhinoMissileKey(vehicleid);
 SetVehicleRhinoMissileKey(vehicleid,key);
 GetVehicleRhinoMissileAmmo(vehicleid);
 SetVehicleRhinoMissileAmmo(vehicleid,ammo);
 Float:GetVehicleRhinoMissileDMG(vehicleid);
 SetVehicleRhinoMissileDMG(vehicleid,Float:damage);
 Float:GetVehicleRhinoMissileVehDMG(vehicleid);
 SetVehicleRhinoMissileVehDMG(vehicleid,Float:damage);

 Functions Bomber Missile:
 ToggleVehicleBomberMissile(vehicleid,toggle);
 IsToggleVehicleBomberMissile(vehicleid);
 Float:GetVehicleBomberMissileSpeed(vehicleid);
 SetVehicleBomberMissileSpeed(vehicleid,Float:speed);
 GetVehicleBomberMissileReload(vehicleid);
 SetVehicleBomberMissileReload(vehicleid,time);
 Float:GetVehicleBomberMissileDistance(vehicleid);
 SetVehicleBomberMissileDistance(vehicleid,Float:distance);
 GetVehicleBomberMissileKey(vehicleid);
 SetVehicleBomberMissileKey(vehicleid,key);
 GetVehicleBomberMissileAmmo(vehicleid);
 SetVehicleBomberMissileAmmo(vehicleid,ammo);
 Float:GetVehicleBomberMissileDMG(vehicleid);
 SetVehicleBomberMissileDMG(vehicleid,Float:damage);
 Float:GetVehicleBomberMissileVehDMG(vehicleid);
 SetVehicleBomberMissileVehDMG(vehicleid,Float:damage);

 Functions Mortar Missile:
 ToggleVehicleMortarMissile(vehicleid,toggle);
 IsToggleVehicleMortarMissile(vehicleid);
 Float:GetVehicleMortarMissileSpeed(vehicleid);
 SetVehicleMortarMissileSpeed(vehicleid,Float:speed);
 GetVehicleMortarMissileReload(vehicleid);
 SetVehicleMortarMissileReload(vehicleid,time);
 Float:GetVehicleMortarMissileDistance(vehicleid);
 SetVehicleMortarMissileDistance(vehicleid,Float:distance);
 GetVehicleMortarMissileKey(vehicleid);
 SetVehicleMortarMissileKey(vehicleid,key);
 Float:GetVehicleMortarMissileHeight(vehicleid);
 SetVehicleMortarMissileHeight(vehicleid,Float:height);
 Float:GetVehicleMortarMissileRotation(vehicleid);
 SetVehicleMortarMissileRotation(vehicleid,Float:rotation);
 GetVehicleMortarMissileAmmo(vehicleid);
 SetVehicleMortarMissileAmmo(vehicleid,ammo);
 GetVehicleMortarMissileAimSys(vehicleid);
 SetVehicleMortarMissileAimSys(vehicleid,toggle);
 Float:GetVehicleMortarMissileDMG(vehicleid);
 SetVehicleMortarMissileDMG(vehicleid,Float:damage);
 Float:GetVehicleMortarMissileVehDMG(vehicleid);
 SetVehicleMortarMissileVehDMG(vehicleid,Float:damage);

 Functions Mega Missile:
 ToggleVehicleMegaMissile(vehicleid,toggle);
 IsToggleVehicleMegaMissile(vehicleid);
 Float:GetVehicleMegaMissileSpeed(vehicleid);
 SetVehicleMegaMissileSpeed(vehicleid,Float:speed);
 GetVehicleMegaMissileReload(vehicleid);
 SetVehicleMegaMissileReload(vehicleid,time);
 Float:GetVehicleMegaMissileDistance(vehicleid);
 SetVehicleMegaMissileDistance(vehicleid,Float:distance);
 GetVehicleMegaMissileKey(vehicleid);
 SetVehicleMegaMissileKey(vehicleid,key);
 Float:GetVehicleMegaMissileHeight(vehicleid);
 SetVehicleMegaMissileHeight(vehicleid,Float:height);
 Float:GetVehicleMegaMissileRotation(vehicleid);
 SetVehicleMegaMissileRotation(vehicleid,Float:rotation);
 GetVehicleMegaMissileAmmo(vehicleid);
 SetVehicleMegaMissileAmmo(vehicleid,ammo);
 GetVehicleMegaMissileAimSys(vehicleid);
 SetVehicleMegaMissileAimSys(vehicleid,toggle);
 Float:GetVehicleMegaMissileDMG(vehicleid);
 SetVehicleMegaMissileDMG(vehicleid,Float:damage);
 Float:GetVehicleMegaMissileVehDMG(vehicleid);
 SetVehicleMegaMissileVehDMG(vehicleid,Float:damage);

 Functions Congreve Rocket:
 ToggleVehicleCongreve(vehicleid,toggle);
 IsToggleVehicleCongreve(vehicleid);
 Float:GetVehicleCongreveSpeed(vehicleid);
 SetVehicleCongreveSpeed(vehicleid,Float:speed);
 GetVehicleCongreveReload(vehicleid);
 SetVehicleCongreveReload(vehicleid,time);
 Float:GetVehicleCongreveDistance(vehicleid);
 SetVehicleCongreveDistance(vehicleid,Float:distance);
 GetVehicleCongreveKey(vehicleid);
 SetVehicleCongreveKey(vehicleid,key);
 Float:GetVehicleCongreveSpread(vehicleid);
 SetVehicleCongreveSpread(vehicleid,Float:spread);
 GetVehicleCongreveSalvo(vehicleid);
 SetVehicleCongreveSalvo(vehicleid,salvo);
 GetVehicleCongreveAmmo(vehicleid);
 SetVehicleCongreveAmmo(vehicleid,ammo);
 Float:GetVehicleCongreveDMG(vehicleid);
 SetVehicleCongreveDMG(vehicleid,Float:damage);
 Float:GetVehicleCongreveVehDMG(vehicleid);
 SetVehicleCongreveVehDMG(vehicleid,Float:damage);

 Functions Havoc Rocket:
 ToggleVehicleHavoc(vehicleid,toggle);
 IsToggleVehicleHavoc(vehicleid);
 Float:GetVehicleHavocSpeed(vehicleid);
 SetVehicleHavocSpeed(vehicleid,Float:speed);
 GetVehicleHavocReload(vehicleid);
 SetVehicleHavocReload(vehicleid,time);
 Float:GetVehicleHavocDistance(vehicleid);
 SetVehicleHavocDistance(vehicleid,Float:distance);
 GetVehicleHavocKey(vehicleid);
 SetVehicleHavocKey(vehicleid,key);
 Float:GetVehicleHavocSpread(vehicleid);
 SetVehicleHavocSpread(vehicleid,Float:spread);
 GetVehicleHavocSalvo(vehicleid);
 SetVehicleHavocSalvo(vehicleid,salvo);
 GetVehicleHavocAmmo(vehicleid);
 SetVehicleHavocAmmo(vehicleid,ammo);
 Float:GetVehicleHavocDMG(vehicleid);
 SetVehicleHavocDMG(vehicleid,Float:damage);
 Float:GetVehicleHavocVehDMG(vehicleid);
 SetVehicleHavocVehDMG(vehicleid,Float:damage);

 Functions Ground Bomb:
 ToggleVehicleGroundBomb(vehicleid,toggle);
 IsToggleVehicleGroundBomb(vehicleid);
 Float:GetVehicleGroundBombSpeed(vehicleid);
 SetVehicleGroundBombSpeed(vehicleid,Float:speed);
 GetVehicleGroundBombReload(vehicleid);
 SetVehicleGroundBombReload(vehicleid,time);
 Float:GetVehicleGroundBombDistance(vehicleid);
 SetVehicleGroundBombDistance(vehicleid,Float:distance);
 GetVehicleGroundBombKey(vehicleid);
 SetVehicleGroundBombKey(vehicleid,key);
 GetVehicleGroundBombAmmo(vehicleid);
 SetVehicleGroundBombAmmo(vehicleid,ammo);
 Float:GetVehicleGroundBombDMG(vehicleid);
 SetVehicleGroundBombDMG(vehicleid,Float:damage);
 Float:GetVehicleGroundBombVehDMG(vehicleid);
 SetVehicleGroundBombVehDMG(vehicleid,Float:damage);

 Functions Ground Bomb (Extended Grenade):
 GetVehicleGroundBombType(vehicleid);
 SetVehicleGroundBombType(vehicleid,special_weaponid);
 GetVehicleGroundBombEffect(vehicleid);
 SetVehicleGroundBombEffect(vehicleid,effectid);
 Float:GetVehicleGroundBombEffectDMG(vehicleid);
 SetVehicleGroundBombEffectDMG(vehicleid,Float:damage);
 Float:GetVehicleGroundBombEffectVDMG(vehicleid);
 SetVehicleGroundBombEffectVDMG(vehicleid,Float:veh_damage);
 GetVehicleGroundBombEffectTime(vehicleid);
 SetVehicleGroundBombEffectTime(vehicleid,seconds);

 Functions Flare:
 ToggleVehicleFlare(vehicleid,toggle);
 IsToggleVehicleFlare(vehicleid);
 Float:GetVehicleFlareSpeed(vehicleid);
 SetVehicleFlareSpeed(vehicleid,Float:speed);
 GetVehicleFlareReload(vehicleid);
 SetVehicleFlareReload(vehicleid,time);
 Float:GetVehicleFlareDistance(vehicleid);
 SetVehicleFlareDistance(vehicleid,Float:distance);
 GetVehicleFlareKey(vehicleid);
 SetVehicleFlareKey(vehicleid,key);
 GetVehicleFlareSalvo(vehicleid);
 SetVehicleFlareSalvo(vehicleid,salvo);
 GetVehicleFlareAmmo(vehicleid);
 SetVehicleFlareAmmo(vehicleid,ammo);

 Player Functions:
 GetMiniMissileRemainingTime(playerid);
 GetHeavyMissileRemainingTime(playerid);
 GetRhinoMissileRemainingTime(playerid);
 GetBomberMissileRemainingTime(playerid);
 GetMortarMissileRemainingTime(playerid);
 GetMegaMissileRemainingTime(playerid);
 GetCongreveRemainingTime(playerid);
 GetHavocRemainingTime(playerid);
 GetGroundBombRemainingTime(playerid);
 GetFlareRemainingTime(playerid);
 IsVehicleMissileAimSysReady(playerid);
 SetVehicleMissileAimTarget(playerid,Float:x=0.0,Float:y=0.0);

 Extended Functions:
 Float:GetMissileStreamDistance();
 SetMissileStreamDistance(Float:streamdistance);
 DisarmVehicleMissile(vehicleid);
 SetVehicleMissileDefaultConfig(vehicleid);
 ToggleMissileAutoDisarm(bool:toggle);
 bool:IsToggleMissileAutoDisarm();
 OnVehicleShot(playerid,type);
 OnVehicleMissileInit();
 GetMissileRemainingTime(playerid,type);
 GetVehicleMissileAmmo(vehicleid,type);
 SetVehicleMissileAmmo(vehicleid,type,ammo);

 Callbacks:
 OnVehicleArmed(playerid,vehicleid);
 OnVehicleMissileRequestLaunch(playerid,type,vehicleid);
 OnVehicleMissileLaunched(playerid,type,vehicleid);
*/

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR) || (!defined RemoveDynamicObjectMaterialText))
	#error [ADM] This include required Streamer v2.9.5 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS_VERSION
	#error [ADM] This include required ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#elseif (COLANDREAS_VERSION < 10500)
	#error [ADM] Update your ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version Missile.inc
#if !defined _missile_launcher
	#error [ADM] This include required Missile.inc v2.3.0
#elseif !defined Missile_Version
	#error [ADM] Update your Missile.inc to v2.3.0
#elseif (Missile_Version < 20300)
	#error [ADM] Update your Missile.inc to v2.3.0
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_REMASTERED_INCLUDE
	#error [ADM] This include required 3DTryg.inc Gen. 2 v1.0.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to Gen. 2 v1.0.0
#elseif (TRYG3D_VERSION < 10000)
	#error [ADM] Update your 3DTryg.inc to Gen. 2 v1.0.0
#endif

#if !defined TRYG3D_MOD_PLAYER
	#error [ADM] Module not initialized: TRYG3D_MOD_PLAYER (add #define TRYG3D_ENABLE_PLAYER before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_VEHICLE
	#error [ADM] Module not initialized: TRYG3D_MOD_VEHICLE (add #define TRYG3D_ENABLE_VEHICLE before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_UNIVERSAL
	#error [ADM] Module not initialized: TRYG3D_MOD_UNIVERSAL (add #define TRYG3D_ENABLE_UNIVERSAL before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_CAST3D
	#error [ADM] Module not initialized: TRYG3D_MOD_CAST3D (add #define TRYG3D_ENABLE_CAST3D before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_COLANDREAS
	#error [ADM] Module not initialized: TRYG3D_MOD_COLANDREAS (add #define TRYG3D_ENABLE_COLANDREAS before include 3DTryg.inc)
#endif

#if defined _veh_missile_launcher
	#endinput
#endif
#define _veh_missile_launcher
#define DYNAMIC_FILTERSCRIPT					"ALS:HOOK:METHOD"

#if defined _GRENADE_INCLUDE
	#if (EXTENDED_GRENADE_VERSION < 10100)
		#error [ADM] Update your ExtendedGrenade.inc to v1.1.0
	#else
		#define VEHICLE_MISSILE_GRENADE
	#endif
#endif

#define VMC::									VMC_

#define MAX_VEHICLE_MISSILE_TYPE				(10)
#define VEHICLE_MISSILE_TYPE_MINI				(0)
#define VEHICLE_MISSILE_TYPE_HEAVY				(1)
#define VEHICLE_MISSILE_TYPE_BOMBER				(2)
#define VEHICLE_MISSILE_TYPE_RHINO				(3)
#define VEHICLE_MISSILE_TYPE_MORTAR				(4)
#define VEHICLE_MISSILE_TYPE_MEGA				(5)
#define VEHICLE_MISSILE_TYPE_CON				(6)
#define VEHICLE_MISSILE_TYPE_HAVOC				(7)
#define VEHICLE_MISSILE_TYPE_BOMB				(8)
#define VEHICLE_MISSILE_TYPE_FLARE				(9)

#define VEHICLE_MISSILE_SPEED_MINI				(40.0)
#define VEHICLE_MISSILE_SPEED_HEAVY				(40.0)
#define VEHICLE_MISSILE_SPEED_BOMBER			(40.0)
#define VEHICLE_MISSILE_SPEED_MORTAR			(40.0)
#define VEHICLE_MISSILE_SPEED_MEGA				(40.0)
#define VEHICLE_MISSILE_SPEED_CON				(80.0)
#define VEHICLE_MISSILE_SPEED_HAVOC				(80.0)
#define VEHICLE_MISSILE_SPEED_BOMB				(40.0)
#define VEHICLE_MISSILE_SPEED_FLARE				(80.0)

#define VEHICLE_MISSILE_RELOAD_MINI				(500) //500 ms
#define VEHICLE_MISSILE_RELOAD_HEAVY			(3000)
#define VEHICLE_MISSILE_RELOAD_BOMBER			(1000)
#define VEHICLE_MISSILE_RELOAD_RHINO			(250)
#define VEHICLE_MISSILE_RELOAD_MORTAR			(500)
#define VEHICLE_MISSILE_RELOAD_MEGA				(500)
#define VEHICLE_MISSILE_RELOAD_CON				(1000)
#define VEHICLE_MISSILE_RELOAD_HAVOC			(3000)
#define VEHICLE_MISSILE_RELOAD_BOMB				(1000)
#define VEHICLE_MISSILE_RELOAD_FLARE			(1000)

#define VEHICLE_MISSILE_DISTANCE_MINI			(1200.0)
#define VEHICLE_MISSILE_DISTANCE_HEAVY			(2000.0)
#define VEHICLE_MISSILE_DISTANCE_BOMBER			(1200.0)
#define VEHICLE_MISSILE_DISTANCE_RHINO			(12.0)
#define VEHICLE_MISSILE_DISTANCE_MORTAR			(250.0)
#define VEHICLE_MISSILE_DISTANCE_MEGA			(250.0)
#define VEHICLE_MISSILE_DISTANCE_CON			(500.0)
#define VEHICLE_MISSILE_DISTANCE_HAVOC			(1200.0)
#define VEHICLE_MISSILE_DISTANCE_BOMB			(1200.0)
#define VEHICLE_MISSILE_DISTANCE_FLARE			(50.0)

#define VEHICLE_MISSILE_KEY_MINI				(KEY_FIRE)
#define VEHICLE_MISSILE_KEY_HEAVY				(KEY_ACTION)
#define VEHICLE_MISSILE_KEY_BOMBER				(KEY_YES)
#define VEHICLE_MISSILE_KEY_RHINO				(KEY_FIRE)
#define VEHICLE_MISSILE_KEY_MORTAR				(KEY_YES)
#define VEHICLE_MISSILE_KEY_MEGA				(KEY_YES)
#define VEHICLE_MISSILE_KEY_CON					(KEY_NO)
#define VEHICLE_MISSILE_KEY_HAVOC				(KEY_YES)
#define VEHICLE_MISSILE_KEY_BOMB				(KEY_YES)
#define VEHICLE_MISSILE_KEY_FLARE				(KEY_ANALOG_LEFT)

#define VEHICLE_MISSILE_HEIGHT_MORTAR			(50.0)
#define VEHICLE_MISSILE_HEIGHT_MEGA				(50.0)
#define VEHICLE_MISSILE_ROTATION				(0.0)

#define VEHICLE_MISSILE_SPREAD_CON				(15.0)
#define VEHICLE_MISSILE_SALVO_CON				(8)
#define VEHICLE_MISSILE_SPREAD_HAVOC			(30.0)
#define VEHICLE_MISSILE_SALVO_HAVOC				(10)
#define VEHICLE_MISSILE_SALVO_FLARE				(5)

#define VEHICLE_WEAPON_AMMO_INFINITY			(-1)

#define VEHICLE_FLARE_TYPE_HYDRA				0
#define VEHICLE_FLARE_TYPE_RED					1

//Get Compress Adress
#define GetVehicleConfigAddress(%0)				(floatround((%0)/32))
#define GetVehicleConfigBit(%0)					((%0) % 32)

//BitFunctions.inc
#define VMC_GetValueBit(%0,%1)					((%0) >>> (%1) & 0x01)
#define VMC_SetValueBit(%0,%1,%2)				((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

new VehicleConfigMiniMissile[63],
	VehicleConfigHeavyMissile[63],
	VehicleConfigRhinoMissile[63],
	VehicleConfigBomberMissile[63],
	VehicleConfigMortarMissile[63],
	VehicleConfigMegaMissile[63],
	VehicleConfigCongreveMissile[63],
	VehicleConfigHavocMissile[63],
	VehicleConfigGroundBomb[63],
	VehicleConfigFlare[63],
	
	VehicleMegaTargeting[63],
	VehicleMortarTargeting[63],
	
	VMC::Tick[MAX_PLAYERS][MAX_VEHICLE_MISSILE_TYPE],
	Float:VMC::Target[MAX_PLAYERS][2],
	
	VMC::Reload[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	VMC::Key[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	Float:VMC::Speed[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	Float:VMC::Distance[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	VMC::Ammo[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	Float:VMC::Damage[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	Float:VMC::VehDamage[MAX_VEHICLES][MAX_VEHICLE_MISSILE_TYPE],
	
	VMC::BombType[MAX_VEHICLES],
	VMC::BombEffect[MAX_VEHICLES],
	
	Float:VMC::BombEffectDMG[MAX_VEHICLES],
	Float:VMC::BombEffectVDMG[MAX_VEHICLES],
	VMC::BombEffectTime[MAX_VEHICLES],
	
	Float:VehicleMortarHeight[MAX_VEHICLES],
	Float:VehicleMortarRotation[MAX_VEHICLES],
	Float:VehicleMegaHeight[MAX_VEHICLES],
	Float:VehicleMegaRotation[MAX_VEHICLES],
	Float:VehicleCongreveSpread[MAX_VEHICLES],
	Float:VehicleHavocSpread[MAX_VEHICLES],
	VehicleCongreveSalvo[MAX_VEHICLES],
	VehicleFlareSalvo[MAX_VEHICLES],
	VehicleHavocSalvo[MAX_VEHICLES],
	VehicleFlareType[MAX_VEHICLES],
	
	Float:MissileStreamDistance = 200.0,
	bool:VehicleMissileAutoDisarm = false;


#define IsToggleVehicleMiniMissile(%0)			VMC_GetValueBit(VehicleConfigMiniMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleMiniMissile(%0,%1)			VMC_SetValueBit(VehicleConfigMiniMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleMiniMissileSpeed(%0)			VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define SetVehicleMiniMissileSpeed(%0,%1)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define GetVehicleMiniMissileReload(%0)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define SetVehicleMiniMissileReload(%0,%1)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define GetVehicleMiniMissileDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define SetVehicleMiniMissileDistance(%0,%1)	VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define GetVehicleMiniMissileKey(%0)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define SetVehicleMiniMissileKey(%0,%1)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define GetVehicleMiniMissileDMG(%0)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define SetVehicleMiniMissileDMG(%0,%1)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define GetVehicleMiniMissileVehDMG(%0)			VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define SetVehicleMiniMissileVehDMG(%0,%1)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)

#define IsToggleVehicleHeavyMissile(%0)			VMC_GetValueBit(VehicleConfigHeavyMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleHeavyMissile(%0,%1)		VMC_SetValueBit(VehicleConfigHeavyMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleHeavyMissileSpeed(%0)			VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define SetVehicleHeavyMissileSpeed(%0,%1)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define GetVehicleHeavyMissileReload(%0)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define SetVehicleHeavyMissileReload(%0,%1)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define GetVehicleHeavyMissileDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define SetVehicleHeavyMissileDistance(%0,%1)	VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define GetVehicleHeavyMissileKey(%0)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define SetVehicleHeavyMissileKey(%0,%1)		VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define GetVehicleHeavyMissileDMG(%0)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define SetVehicleHeavyMissileDMG(%0,%1)		VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define GetVehicleHeavyMissileVehDMG(%0)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define SetVehicleHeavyMissileVehDMG(%0,%1)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)

#define IsToggleVehicleBomberMissile(%0)		VMC_GetValueBit(VehicleConfigBomberMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleBomberMissile(%0,%1)		VMC_SetValueBit(VehicleConfigBomberMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleBomberMissileSpeed(%0)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define SetVehicleBomberMissileSpeed(%0,%1)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define GetVehicleBomberMissileReload(%0)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define SetVehicleBomberMissileReload(%0,%1)	VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define GetVehicleBomberMissileDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define SetVehicleBomberMissileDistance(%0,%1)	VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define GetVehicleBomberMissileKey(%0)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define SetVehicleBomberMissileKey(%0,%1)		VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define GetVehicleBomberMissileDMG(%0)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define SetVehicleBomberMissileDMG(%0,%1)		VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define GetVehicleBomberMissileVehDMG(%0)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define SetVehicleBomberMissileVehDMG(%0,%1)	VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)

#define IsToggleVehicleRhinoMissile(%0)			VMC_GetValueBit(VehicleConfigRhinoMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleRhinoMissile(%0,%1)		VMC_SetValueBit(VehicleConfigRhinoMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleRhinoMissileReload(%0)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define SetVehicleRhinoMissileReload(%0,%1)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define GetVehicleRhinoMissileDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define SetVehicleRhinoMissileDistance(%0,%1)	VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define GetVehicleRhinoMissileKey(%0)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define SetVehicleRhinoMissileKey(%0,%1)		VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define GetVehicleRhinoMissileDMG(%0)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define SetVehicleRhinoMissileDMG(%0,%1)		VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define GetVehicleRhinoMissileVehDMG(%0)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define SetVehicleRhinoMissileVehDMG(%0,%1)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)

#define IsToggleVehicleMortarMissile(%0)		VMC_GetValueBit(VehicleConfigMortarMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleMortarMissile(%0,%1)		VMC_SetValueBit(VehicleConfigMortarMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleMortarMissileSpeed(%0)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define SetVehicleMortarMissileSpeed(%0,%1)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define GetVehicleMortarMissileReload(%0)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define SetVehicleMortarMissileReload(%0,%1)	VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define GetVehicleMortarMissileDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define SetVehicleMortarMissileDistance(%0,%1)	VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define GetVehicleMortarMissileKey(%0)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define SetVehicleMortarMissileKey(%0,%1)		VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define GetVehicleMortarMissileHeight(%0)		VehicleMortarHeight[(%0)]
#define SetVehicleMortarMissileHeight(%0,%1)	VehicleMortarHeight[(%0)] = (%1)
#define GetVehicleMortarMissileRotation(%0)		VehicleMortarRotation[(%0)]
#define SetVehicleMortarMissileRotation(%0,%1)	VehicleMortarRotation[(%0)] = (%1)
#define GetVehicleMortarMissileDMG(%0)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define SetVehicleMortarMissileDMG(%0,%1)		VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define GetVehicleMortarMissileVehDMG(%0)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define SetVehicleMortarMissileVehDMG(%0,%1)	VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define GetVehicleMortarMissileAimSys(%0)		VMC_GetValueBit(VehicleMortarTargeting[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define SetVehicleMortarMissileAimSys(%0,%1)	VMC_SetValueBit(VehicleMortarTargeting[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))

#define IsToggleVehicleMegaMissile(%0)			VMC_GetValueBit(VehicleConfigMegaMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleMegaMissile(%0,%1)			VMC_SetValueBit(VehicleConfigMegaMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleMegaMissileSpeed(%0)			VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define SetVehicleMegaMissileSpeed(%0,%1)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define GetVehicleMegaMissileReload(%0)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define SetVehicleMegaMissileReload(%0,%1)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define GetVehicleMegaMissileDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define SetVehicleMegaMissileDistance(%0,%1)	VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define GetVehicleMegaMissileKey(%0)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define SetVehicleMegaMissileKey(%0,%1)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define GetVehicleMegaMissileHeight(%0)			VehicleMegaHeight[(%0)]
#define SetVehicleMegaMissileHeight(%0,%1)		VehicleMegaHeight[(%0)] = (%1)
#define GetVehicleMegaMissileRotation(%0)		VehicleMegaRotation[(%0)]
#define SetVehicleMegaMissileRotation(%0,%1)	VehicleMegaRotation[(%0)] = (%1)
#define GetVehicleMegaMissileDMG(%0)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define SetVehicleMegaMissileDMG(%0,%1)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define GetVehicleMegaMissileVehDMG(%0)			VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define SetVehicleMegaMissileVehDMG(%0,%1)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define GetVehicleMegaMissileAimSys(%0)			VMC_GetValueBit(VehicleMegaTargeting[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define SetVehicleMegaMissileAimSys(%0,%1)		VMC_SetValueBit(VehicleMegaTargeting[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))

#define IsToggleVehicleCongreve(%0)				VMC_GetValueBit(VehicleConfigCongreveMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleCongreve(%0,%1)			VMC_SetValueBit(VehicleConfigCongreveMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleCongreveSpeed(%0)				VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define SetVehicleCongreveSpeed(%0,%1)			VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)
#define GetVehicleCongreveReload(%0)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define SetVehicleCongreveReload(%0,%1)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)
#define GetVehicleCongreveDistance(%0)			VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define SetVehicleCongreveDistance(%0,%1)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)
#define GetVehicleCongreveKey(%0)				VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define SetVehicleCongreveKey(%0,%1)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)
#define GetVehicleCongreveSpread(%0)			VehicleCongreveSpread[(%0)]
#define SetVehicleCongreveSpread(%0,%1)			VehicleCongreveSpread[(%0)] = (%1)
#define GetVehicleCongreveSalvo(%0)				VehicleCongreveSalvo[(%0)]
#define SetVehicleCongreveSalvo(%0,%1)			VehicleCongreveSalvo[(%0)] = (%1)
#define GetVehicleCongreveDMG(%0)				VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define SetVehicleCongreveDMG(%0,%1)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)
#define GetVehicleCongreveVehDMG(%0)			VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define SetVehicleCongreveVehDMG(%0,%1)			VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)

#define IsToggleVehicleHavoc(%0)				VMC_GetValueBit(VehicleConfigHavocMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleHavoc(%0,%1)				VMC_SetValueBit(VehicleConfigHavocMissile[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleHavocSpeed(%0)				VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define SetVehicleHavocSpeed(%0,%1)				VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)
#define GetVehicleHavocReload(%0)				VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define SetVehicleHavocReload(%0,%1)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)
#define GetVehicleHavocDistance(%0)				VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define SetVehicleHavocDistance(%0,%1)			VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)
#define GetVehicleHavocKey(%0)					VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define SetVehicleHavocKey(%0,%1)				VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)
#define GetVehicleHavocSpread(%0)				VehicleHavocSpread[(%0)]
#define SetVehicleHavocSpread(%0,%1)			VehicleHavocSpread[(%0)] = (%1)
#define GetVehicleHavocSalvo(%0)				VehicleHavocSalvo[(%0)]
#define SetVehicleHavocSalvo(%0,%1)				VehicleHavocSalvo[(%0)] = (%1)
#define GetVehicleHavocDMG(%0)					VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define SetVehicleHavocDMG(%0,%1)				VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)
#define GetVehicleHavocVehDMG(%0)				VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define SetVehicleHavocVehDMG(%0,%1)			VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)

#define IsToggleVehicleGroundBomb(%0)			VMC_GetValueBit(VehicleConfigGroundBomb[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleGroundBomb(%0,%1)			VMC_SetValueBit(VehicleConfigGroundBomb[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleGroundBombSpeed(%0)			VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define SetVehicleGroundBombSpeed(%0,%1)		VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)
#define GetVehicleGroundBombReload(%0)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define SetVehicleGroundBombReload(%0,%1)		VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)
#define GetVehicleGroundBombDistance(%0)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define SetVehicleGroundBombDistance(%0,%1)		VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)
#define GetVehicleGroundBombKey(%0)				VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define SetVehicleGroundBombKey(%0,%1)			VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)
#define GetVehicleGroundBombDMG(%0)				VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define SetVehicleGroundBombDMG(%0,%1)			VMC::Damage[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)
#define GetVehicleGroundBombVehDMG(%0)			VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define SetVehicleGroundBombVehDMG(%0,%1)		VMC::VehDamage[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)

#define IsToggleVehicleFlare(%0)				VMC_GetValueBit(VehicleConfigFlare[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0))
#define ToggleVehicleFlare(%0,%1)				VMC_SetValueBit(VehicleConfigFlare[GetVehicleConfigAddress(%0)],GetVehicleConfigBit(%0),(%1))
#define GetVehicleFlareSpeed(%0)				VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_FLARE]
#define SetVehicleFlareSpeed(%0,%1)				VMC::Speed[(%0)][VEHICLE_MISSILE_TYPE_FLARE] = (%1)
#define GetVehicleFlareReload(%0)				VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_FLARE]
#define SetVehicleFlareReload(%0,%1)			VMC::Reload[(%0)][VEHICLE_MISSILE_TYPE_FLARE] = (%1)
#define GetVehicleFlareDistance(%0)				VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_FLARE]
#define SetVehicleFlareDistance(%0,%1)			VMC::Distance[(%0)][VEHICLE_MISSILE_TYPE_FLARE] = (%1)
#define GetVehicleFlareKey(%0)					VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_FLARE]
#define SetVehicleFlareKey(%0,%1)				VMC::Key[(%0)][VEHICLE_MISSILE_TYPE_FLARE] = (%1)
#define GetVehicleFlareSalvo(%0)				VehicleFlareSalvo[(%0)]
#define SetVehicleFlareSalvo(%0,%1)				VehicleFlareSalvo[(%0)] = (%1)
#define GetVehicleFlareType(%0)					VehicleFlareType[(%0)]
#define SetVehicleFlareType(%0,%1)				VehicleFlareType[(%0)] = (%1)

#define GetMissileStreamDistance()				MissileStreamDistance
#define SetMissileStreamDistance(%0)			MissileStreamDistance = (%0)

#define IsToggleMissileAutoDisarm()				VehicleMissileAutoDisarm
#define ToggleMissileAutoDisarm(%0)				VehicleMissileAutoDisarm = (%0)

#define GetMiniMissileRemainingTime(%0)			GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_MINI)
#define GetHeavyMissileRemainingTime(%0)		GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_HEAVY)
#define GetRhinoMissileRemainingTime(%0)		GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_RHINO)
#define GetBomberMissileRemainingTime(%0)		GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_BOMBER)
#define GetMortarMissileRemainingTime(%0)		GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_MORTAR)
#define GetMegaMissileRemainingTime(%0)			GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_MEGA)
#define GetCongreveRemainingTime(%0)			GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_CON)
#define GetHavocRemainingTime(%0)				GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_HAVOC)
#define GetGroundBombRemainingTime(%0)			GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_BOMB)
#define GetFlareRemainingTime(%0)				GetMissileRemainingTime((%0),VEHICLE_MISSILE_TYPE_FLARE)

#define GetVehicleMiniMissileAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_MINI]
#define GetVehicleHeavyMissileAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_HEAVY]
#define GetVehicleRhinoMissileAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_RHINO]
#define GetVehicleBomberMissileAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_BOMBER]
#define GetVehicleMortarMissileAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_MORTAR]
#define GetVehicleMegaMissileAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_MEGA]
#define GetVehicleCongreveAmmo(%0)				VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_CON]
#define GetVehicleHavocAmmo(%0)					VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_HAVOC]
#define GetVehicleGroundBombAmmo(%0)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_BOMB]
#define GetVehicleFlareAmmo(%0)					VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_FLARE]

#define SetVehicleMiniMissileAmmo(%0,%1)		VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_MINI] = (%1)
#define SetVehicleHeavyMissileAmmo(%0,%1)		VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_HEAVY] = (%1)
#define SetVehicleRhinoMissileAmmo(%0,%1)		VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_RHINO] = (%1)
#define SetVehicleBomberMissileAmmo(%0,%1)		VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_BOMBER] = (%1)
#define SetVehicleMortarMissileAmmo(%0,%1)		VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_MORTAR] = (%1)
#define SetVehicleMegaMissileAmmo(%0,%1)		VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_MEGA] = (%1)
#define SetVehicleCongreveAmmo(%0,%1)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_CON] = (%1)
#define SetVehicleHavocAmmo(%0,%1)				VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_HAVOC] = (%1)
#define SetVehicleGroundBombAmmo(%0,%1)			VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_BOMB] = (%1)
#define SetVehicleFlareAmmo(%0,%1)				VMC::Ammo[(%0)][VEHICLE_MISSILE_TYPE_FLARE] = (%1)

#define GetVehicleGroundBombType(%0)			VMC::BombType[(%0)]
#define SetVehicleGroundBombType(%0,%1)			VMC::BombType[(%0)] = (%1)
#define GetVehicleGroundBombEffect(%0)			VMC::BombEffect[(%0)]
#define SetVehicleGroundBombEffect(%0,%1)		VMC::BombEffect[(%0)] = (%1)

#define GetVehicleGroundBombEffectDMG(%0)		VMC::BombEffectDMG[(%0)]
#define SetVehicleGroundBombEffectDMG(%0,%1)	VMC::BombEffectDMG[(%0)] = (%1)
#define GetVehicleGroundBombEffectVDMG(%0)		VMC::BombEffectVDMG[(%0)]
#define SetVehicleGroundBombEffectVDMG(%0,%1)	VMC::BombEffectVDMG[(%0)] = (%1)
#define GetVehicleGroundBombEffectTime(%0)		VMC::BombEffectTime[(%0)]
#define SetVehicleGroundBombEffectTime(%0,%1)	VMC::BombEffectTime[(%0)] = (%1)
 
#define GetVehicleMissileAmmo(%0,%1)			VMC::Ammo[(%0)][(%1)]
#define SetVehicleMissileAmmo(%0,%1,2)			VMC::Ammo[(%0)][(%1)] = (%2)

forward OnVehicleArmed(playerid,vehicleid);

#if defined OnVehicleMissileRequestLaunch
	forward OnVehicleMissileRequestLaunch(playerid,type,vehicleid);
#endif

#if defined OnVehicleMissileLaunched
	forward OnVehicleMissileLaunched(playerid,type,vehicleid);
#endif

stock GetMissileRemainingTime(playerid,type){
	if(!IsPlayerInAnyVehicle(playerid)) return 0;
	new vehicleid = GetPlayerVehicleID(playerid), c_time = GetTickCount()-VMC::Tick[playerid][type];
	if(c_time < VMC::Reload[vehicleid][type] && VMC::Tick[playerid][type] != 0) return VMC::Reload[vehicleid][type]-c_time;
	return 0;
}

stock DisarmVehicleMissile(vehicleid){
	ToggleVehicleMiniMissile(vehicleid,0);
	ToggleVehicleHeavyMissile(vehicleid,0);
	ToggleVehicleRhinoMissile(vehicleid,0);
	ToggleVehicleBomberMissile(vehicleid,0);
	ToggleVehicleMortarMissile(vehicleid,0);
	ToggleVehicleMegaMissile(vehicleid,0);
	ToggleVehicleCongreve(vehicleid,0);
	ToggleVehicleHavoc(vehicleid,0);
	ToggleVehicleGroundBomb(vehicleid,0);
	ToggleVehicleFlare(vehicleid,0);
}

stock IsVehicleMissileAimSysReady(playerid){
	if(VMC::Target[playerid][0] == 0.0 && VMC::Target[playerid][1] == 0.0) return 0;
	return 1;
}

stock SetVehicleMissileAimTarget(playerid,Float:x=0.0,Float:y=0.0){
	VMC::Target[playerid][0] = x;
	VMC::Target[playerid][1] = y;
}

stock SetVehicleMissileDefaultConfig(vehicleid){
	SetVehicleMiniMissileSpeed(vehicleid,VEHICLE_MISSILE_SPEED_MINI);
	SetVehicleMiniMissileReload(vehicleid,VEHICLE_MISSILE_RELOAD_MINI);
	SetVehicleMiniMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_MINI);
	SetVehicleMiniMissileKey(vehicleid,VEHICLE_MISSILE_KEY_MINI);
	SetVehicleMiniMissileAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleMiniMissileDMG(vehicleid,-1.0);
	SetVehicleMiniMissileVehDMG(vehicleid,-1.0);
	
	SetVehicleHeavyMissileSpeed(vehicleid,VEHICLE_MISSILE_SPEED_HEAVY);
	SetVehicleHeavyMissileReload(vehicleid,VEHICLE_MISSILE_RELOAD_HEAVY);
	SetVehicleHeavyMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_HEAVY);
	SetVehicleHeavyMissileKey(vehicleid,VEHICLE_MISSILE_KEY_HEAVY);
	SetVehicleHeavyMissileAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleHeavyMissileDMG(vehicleid,-1.0);
	SetVehicleHeavyMissileVehDMG(vehicleid,-1.0);
	
	SetVehicleBomberMissileSpeed(vehicleid,VEHICLE_MISSILE_SPEED_BOMBER);
	SetVehicleBomberMissileReload(vehicleid,VEHICLE_MISSILE_RELOAD_BOMBER);
	SetVehicleBomberMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_BOMBER);
	SetVehicleBomberMissileKey(vehicleid,VEHICLE_MISSILE_KEY_BOMBER);
	SetVehicleBomberMissileAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleBomberMissileDMG(vehicleid,-1.0);
	SetVehicleBomberMissileVehDMG(vehicleid,-1.0);
	
	SetVehicleRhinoMissileReload(vehicleid,VEHICLE_MISSILE_RELOAD_RHINO);
	SetVehicleRhinoMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_RHINO);
	SetVehicleRhinoMissileKey(vehicleid,VEHICLE_MISSILE_KEY_RHINO);
	SetVehicleRhinoMissileAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleRhinoMissileDMG(vehicleid,-1.0);
	SetVehicleRhinoMissileVehDMG(vehicleid,-1.0);
	
	SetVehicleMortarMissileSpeed(vehicleid,VEHICLE_MISSILE_SPEED_MORTAR);
	SetVehicleMortarMissileReload(vehicleid,VEHICLE_MISSILE_RELOAD_MORTAR);
	SetVehicleMortarMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_MORTAR);
	SetVehicleMortarMissileKey(vehicleid,VEHICLE_MISSILE_KEY_MORTAR);
	SetVehicleMortarMissileHeight(vehicleid,VEHICLE_MISSILE_HEIGHT_MORTAR);
	SetVehicleMortarMissileAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleMortarMissileAimSys(vehicleid,0);
	SetVehicleMortarMissileDMG(vehicleid,-1.0);
	SetVehicleMortarMissileVehDMG(vehicleid,-1.0);
	
	SetVehicleMegaMissileSpeed(vehicleid,VEHICLE_MISSILE_SPEED_MEGA);
	SetVehicleMegaMissileReload(vehicleid,VEHICLE_MISSILE_RELOAD_MEGA);
	SetVehicleMegaMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_MEGA);
	SetVehicleMegaMissileKey(vehicleid,VEHICLE_MISSILE_KEY_MEGA);
	SetVehicleMegaMissileHeight(vehicleid,VEHICLE_MISSILE_HEIGHT_MEGA);
	SetVehicleMegaMissileAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleMegaMissileAimSys(vehicleid,0);
	SetVehicleMegaMissileDMG(vehicleid,-1.0);
	SetVehicleMegaMissileVehDMG(vehicleid,-1.0);
	
	SetVehicleCongreveSpeed(vehicleid,VEHICLE_MISSILE_SPEED_CON);
	SetVehicleCongreveReload(vehicleid,VEHICLE_MISSILE_RELOAD_CON);
	SetVehicleCongreveDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_CON);
	SetVehicleCongreveKey(vehicleid,VEHICLE_MISSILE_KEY_CON);
	SetVehicleCongreveSpread(vehicleid,VEHICLE_MISSILE_SPREAD_CON);
	SetVehicleCongreveSalvo(vehicleid,VEHICLE_MISSILE_SALVO_CON);
	SetVehicleCongreveAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleCongreveDMG(vehicleid,-1.0);
	SetVehicleCongreveVehDMG(vehicleid,-1.0);
	
	SetVehicleHavocSpeed(vehicleid,VEHICLE_MISSILE_SPEED_HAVOC);
	SetVehicleHavocReload(vehicleid,VEHICLE_MISSILE_RELOAD_HAVOC);
	SetVehicleHavocDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_HAVOC);
	SetVehicleHavocKey(vehicleid,VEHICLE_MISSILE_KEY_HAVOC);
	SetVehicleHavocSpread(vehicleid,VEHICLE_MISSILE_SPREAD_HAVOC);
	SetVehicleHavocSalvo(vehicleid,VEHICLE_MISSILE_SALVO_HAVOC);
	SetVehicleHavocAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleHavocDMG(vehicleid,-1.0);
	SetVehicleHavocVehDMG(vehicleid,-1.0);
	
	SetVehicleGroundBombSpeed(vehicleid,VEHICLE_MISSILE_SPEED_BOMB);
	SetVehicleGroundBombReload(vehicleid,VEHICLE_MISSILE_RELOAD_BOMB);
	SetVehicleGroundBombDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_BOMB);
	SetVehicleGroundBombKey(vehicleid,VEHICLE_MISSILE_KEY_BOMB);
	SetVehicleGroundBombAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
	SetVehicleGroundBombDMG(vehicleid,-1.0);
	SetVehicleGroundBombVehDMG(vehicleid,-1.0);
	SetVehicleGroundBombType(vehicleid,0);
	SetVehicleGroundBombEffect(vehicleid,0);
	SetVehicleGroundBombEffectDMG(vehicleid,82.5);
	SetVehicleGroundBombEffectVDMG(vehicleid,825);
	SetVehicleGroundBombEffectTime(vehicleid,25);
	
	SetVehicleFlareSpeed(vehicleid,VEHICLE_MISSILE_SPEED_FLARE);
	SetVehicleFlareReload(vehicleid,VEHICLE_MISSILE_RELOAD_FLARE);
	SetVehicleFlareDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_FLARE);
	SetVehicleFlareKey(vehicleid,VEHICLE_MISSILE_KEY_FLARE);
	SetVehicleFlareSalvo(vehicleid,VEHICLE_MISSILE_SALVO_FLARE);
	SetVehicleFlareAmmo(vehicleid,VEHICLE_WEAPON_AMMO_INFINITY);
}

forward OnVehicleShot(playerid,type);

public OnVehicleShot(playerid,type){
	new vid = GetPlayerVehicleID(playerid);
	
	#if defined OnVehicleMissileRequestLaunch
		if(!OnVehicleMissileRequestLaunch(playerid,type,vid)) return 0;
	#endif

	switch(type){
		case VEHICLE_MISSILE_TYPE_MINI: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}

			new F4[Float3D], F5[Float3D];
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rY]-180.0,F5[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,10.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rY],F5[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,10.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}

		case VEHICLE_MISSILE_TYPE_HEAVY: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}

			new F4[Float3D], F5[Float3D];
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation(F5[T3D:rY]+15.0),F5[T3D:rZ]+90.0,6.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,8.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation(F5[T3D:rY]+45.0),F5[T3D:rZ]+90.0,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,8.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation(F5[T3D:rY]+75.0),F5[T3D:rZ]+90.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,8.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation(F5[T3D:rY]+105.0),F5[T3D:rZ]+90.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,8.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation(F5[T3D:rY]+135.0),F5[T3D:rZ]+90.0,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,8.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation(F5[T3D:rY]+165.0),F5[T3D:rZ]+90.0,6.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,8.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BIG,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);
			
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}

		case VEHICLE_MISSILE_TYPE_BOMBER: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}

			new F4[Float3D], F5[Float3D];
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			F5[T3D:rX] = Tryg3D::CompressRotation(F5[T3D:rX]-45.0);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,10.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]-90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,10.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]+45.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,10.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ]-45.0,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,10.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}

		case VEHICLE_MISSILE_TYPE_RHINO: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}

			new F5[Float3D];
			Tryg3D::GetPointInFrontOfVehicleCol(vid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],VMC::Distance[vid][type]);

			if(VMC::Damage[vid][type] == -1.0){
				Tryg3D::CastExplosion(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],MISSILE_TYPE_EXPLODE_NORMAL,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance());
			} else {
				if(VMC::VehDamage[vid][type] == -1.0) VMC::VehDamage[vid][type] = 750.0;
				Tryg3D::CastExplosionDMG(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],MISSILE_TYPE_EXPLODE_NORMAL,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,GetMissileStreamDistance(),.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type],.byplayerid=playerid);
			}
			
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
		
		case VEHICLE_MISSILE_TYPE_MORTAR: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}
			new F4[Float3D], F5[Float3D], Float:VMC::dist, remote_cnt, Float:arc_height;
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			
			if(GetVehicleMortarMissileAimSys(vid)){
				if(!IsVehicleMissileAimSysReady(playerid)) return 1;
				
				if((VMC::dist = Tryg3D::GetDistance2D(VMC::Target[playerid][0],VMC::Target[playerid][1],F5[T3D:X],F5[T3D:Y])) > VMC::Distance[vid][type]){
					new Float:tx,Float:ty;
					Tryg3D::GetPointFor2Point2DEx(F5[T3D:X],F5[T3D:Y],VMC::Target[playerid][0],VMC::Target[playerid][1],VMC::dist,tx,ty);
					VMC::Target[playerid][0] = tx;
					VMC::Target[playerid][1] = ty;
					VMC::dist = VMC::Distance[vid][type];
				}
				
				arc_height = (VMC::dist/2.0);
				remote_cnt = floatround(VMC::dist/15.0);
				
				if(remote_cnt > MAX_MISSILE_REMOTE_TARGET) remote_cnt = MAX_MISSILE_REMOTE_TARGET;
				if(remote_cnt < 4) remote_cnt = 4;
				
				Tryg3D::GetRotationFor2Point2D(F5[T3D:X],F5[T3D:Y],VMC::Target[playerid][0],VMC::Target[playerid][1],F4[T3D:rZ]);
			} else {
				Tryg3D::GetPlayerCameraZAngle(playerid,F4[T3D:rZ]);
				
				arc_height = GetVehicleMortarMissileHeight(vid);
				remote_cnt = MAX_MISSILE_REMOTE_TARGET;
				VMC::dist = VMC::Distance[vid][type];
			}
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);
			
			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F4[T3D:rZ]-90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,VehicleMortarRotation[vid],.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F4[T3D:rZ]+90.0,3.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,15.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,-VehicleMortarRotation[vid],.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);
			
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
		
		case VEHICLE_MISSILE_TYPE_MEGA: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}
			new F4[Float3D], F5[Float3D], Float:VMC::dist, remote_cnt, Float:arc_height;
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			
			if(GetVehicleMegaMissileAimSys(vid)){
				if(!IsVehicleMissileAimSysReady(playerid)) return 1;
				
				if((VMC::dist = Tryg3D::GetDistance2D(VMC::Target[playerid][0],VMC::Target[playerid][1],F5[T3D:X],F5[T3D:Y])) > VMC::Distance[vid][type]){
					new Float:tx,Float:ty;
					Tryg3D::GetPointFor2Point2DEx(F5[T3D:X],F5[T3D:Y],VMC::Target[playerid][0],VMC::Target[playerid][1],VMC::dist,tx,ty);
					VMC::Target[playerid][0] = tx;
					VMC::Target[playerid][1] = ty;
					VMC::dist = VMC::Distance[vid][type];
				}
				
				arc_height = (VMC::dist/2.0);
				remote_cnt = floatround(VMC::dist/15.0);
				
				if(remote_cnt > MAX_MISSILE_REMOTE_TARGET) remote_cnt = MAX_MISSILE_REMOTE_TARGET;
				if(remote_cnt < 4) remote_cnt = 4;
				
				Tryg3D::GetRotationFor2Point2D(F5[T3D:X],F5[T3D:Y],VMC::Target[playerid][0],VMC::Target[playerid][1],F4[T3D:rZ]);
			} else {
				Tryg3D::GetPlayerCameraZAngle(playerid,F4[T3D:rZ]);
				
				arc_height = GetVehicleMegaMissileHeight(vid);
				remote_cnt = MAX_MISSILE_REMOTE_TARGET;
				VMC::dist = VMC::Distance[vid][type];
			}
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);
			
			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+60.0),8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,-VehicleMegaRotation[vid],.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+120.0),8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,-VehicleMegaRotation[vid],.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+240.0),8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,VehicleMegaRotation[vid],.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+300.0),8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,VehicleMegaRotation[vid],.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			Tryg3D::GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F4[T3D:rZ],8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			Tryg3D::GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],VMC::dist,F4[T3D:tX],F4[T3D:tY]);
			ColAndreas::FindZ_For2DCoord(F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,true,remote_cnt,arc_height,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);

			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
		
		case VEHICLE_MISSILE_TYPE_CON: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}
			
			new F4[Float3D], F5[Vectors3D];
			Tryg3D::GetPointInFrontOfVehicle3D(vid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],5.0);
			Tryg3D::GetVehicleRotation(vid,F4[T3D:rX],F4[T3D:rY],F4[T3D:rZ]);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);
			
			for(new i = 0; i < GetVehicleCongreveSalvo(vid); i++){
				Tryg3D::GetPointOnSphericalSector(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],F4[T3D:rZ],VMC::Distance[vid][type],GetVehicleCongreveSpread(vid),GetVehicleCongreveSpread(vid),F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				Tryg3D::MovePointCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,15.0,25.0,VMC::Speed[vid][type],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],playerid,ANY_TEAM,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);
			}
			
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
		
		case VEHICLE_MISSILE_TYPE_HAVOC: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}
			
			new F4[Float3D], F5[Float3D];
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			Tryg3D::GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],270.0,F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);
			
			for(new i = 0; i < GetVehicleHavocSalvo(vid); i++){
				Tryg3D::GetPointInFront2D(F4[T3D:tX],F4[T3D:tY],Tryg3D::CompressRotation((float(i)/GetVehicleHavocSalvo(vid))*360.0+F5[T3D:rZ]),GetVehicleHavocSpread(vid),F5[T3D:tX],F5[T3D:tY]);
				Tryg3D::MovePointCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],-100.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,15.0,25.0,VMC::Speed[vid][type],F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_HYDRA,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],playerid,ANY_TEAM,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);
			}
			
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
		
		case VEHICLE_MISSILE_TYPE_BOMB: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}
			
			new F4[Float3D], F5[Float3D];
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);
			
			Tryg3D::GetPointInFrontOfVehicle3D(vid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],1.0);
			Tryg3D::GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],270.0,F5[T3D:rZ],VMC::Distance[vid][type],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			
			if(GetVehicleGroundBombType(vid) == 0){
				Missile::Launch(MISSILE_TYPE_EXPLODE_HUGE,15.0,25.0,VMC::Speed[vid][type],F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BOMB_STATIC,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);
			} else {
				Missile::Launch(14,15.0,25.0,VMC::Speed[vid][type],F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_BOMB_STATIC,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,ANY_TEAM,.damage=VMC::Damage[vid][type],.vehicle_damage=VMC::VehDamage[vid][type]);
			}
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
		
		case VEHICLE_MISSILE_TYPE_FLARE: {
			if(GetTickCount()-VMC::Tick[playerid][type] < VMC::Reload[vid][type]) return 1;
			if(VMC::Ammo[vid][type] != VEHICLE_WEAPON_AMMO_INFINITY){
				if(VMC::Ammo[vid][type] <= 0) return 1;
				VMC::Ammo[vid][type]--;
			}

			new F4[Float3D], F5[Float3D];
			GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			
			F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
			F4[T3D:INT] = GetPlayerInterior(playerid);
			
			for(new i = 0; i < GetVehicleFlareSalvo(vid); i++){
				Tryg3D::GetPointInFrontOfVehicle3D(vid,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],((i+1)*(VMC::Distance[vid][type]/GetVehicleFlareSalvo(vid)))*-1.0);
				switch(GetVehicleFlareType(vid)){
					case VEHICLE_FLARE_TYPE_RED: {
						Missile::Launch(0,15.0,0.0,VMC::Speed[vid][type],F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_FLARE_1,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);
					}
					case VEHICLE_FLARE_TYPE_HYDRA: {
						Missile::Launch(0,15.0,0.0,VMC::Speed[vid][type],F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:VW],F4[T3D:INT],-1,GetMissileStreamDistance(),MISSILE_OBJECT_FLARE_2,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid);
					}
				}
			}
			
			VMC::Tick[playerid][type] = GetTickCount();
			
			#if defined OnVehicleMissileLaunched
				OnVehicleMissileLaunched(playerid,type,vid);
			#endif
		}
	}

	return 1;
}

T3D:function OnVehicleMissileInit(){
	for(new i = 0; i < MAX_VEHICLES; i++){
		SetVehicleMissileDefaultConfig(i);
		DisarmVehicleMissile(i);
	}
	return 1;
}

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0){
		new vid = GetPlayerVehicleID(playerid);
		if(Tryg3D::KeyPressed(GetVehicleMiniMissileKey(vid))){
			if(IsToggleVehicleMiniMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_MINI);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleHeavyMissileKey(vid))){
			if(IsToggleVehicleHeavyMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_HEAVY);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleBomberMissileKey(vid))){
			if(IsToggleVehicleBomberMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_BOMBER);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleRhinoMissileKey(vid))){
			if(IsToggleVehicleRhinoMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_RHINO);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleMortarMissileKey(vid))){
			if(IsToggleVehicleMortarMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_MORTAR);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleMegaMissileKey(vid))){
			if(IsToggleVehicleMegaMissile(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_MEGA);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleCongreveKey(vid))){
			if(IsToggleVehicleCongreve(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_CON);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleHavocKey(vid))){
			if(IsToggleVehicleHavoc(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_HAVOC);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleGroundBombKey(vid))){
			if(IsToggleVehicleGroundBomb(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_BOMB);
			}
		}
		if(Tryg3D::KeyPressed(GetVehicleFlareKey(vid))){
			if(IsToggleVehicleFlare(vid)){
				OnVehicleShot(playerid,VEHICLE_MISSILE_TYPE_FLARE);
			}
		}
	}
	#if defined VMC_OnPlayerKeyStateChange
		VMC_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange VMC_OnPlayerKeyStateChange
#if defined VMC_OnPlayerKeyStateChange
	forward VMC_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

#if defined VEHICLE_MISSILE_GRENADE
	//Hook: OnMissileDestroy
	public OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid){
		if(byplayerid != INVALID_PLAYER_ID){
			if(IsPlayerInAnyVehicle(byplayerid) && GetPlayerVehicleSeat(byplayerid) == 0){
				new vid = GetPlayerVehicleID(byplayerid);
				if(GetVehicleGroundBombType(vid) != GRENADE_SPECIAL_WEAPON_NONE){
					Grenade::CreateGrenadeEffect(GetVehicleGroundBombType(vid),GetVehicleGroundBombEffect(vid),x,y,z,GetPlayerVirtualWorld(byplayerid),GetPlayerInterior(byplayerid),-1,300.0,GetVehicleGroundBombEffectDMG(vid),GetVehicleGroundBombEffectVDMG(vid),GetVehicleGroundBombEffectTime(vid),byplayerid);
				}
			}
		}
		#if defined VMC_OnMissileDestroy
			VMC_OnMissileDestroy(mobid,x,y,z,type,killerid,byplayerid);
		#endif
		return 1;
	}

	#if defined _ALS_OnMissileDestroy
		#undef OnMissileDestroy
	#else
		#define _ALS_OnMissileDestroy
	#endif
	#define OnMissileDestroy VMC_OnMissileDestroy
	#if defined VMC_OnMissileDestroy
		forward VMC_OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid);
	#endif
#endif

new bool:CRC_VehicleMissileInit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_VehicleMissileInit){
		CRC_VehicleMissileInit = false;
		OnVehicleMissileInit();
	}
	#if defined VMC_OnFilterScriptInit
		VMC_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit VMC_OnFilterScriptInit
#if defined VMC_OnFilterScriptInit
	forward VMC_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_VehicleMissileInit){
		CRC_VehicleMissileInit = false;
		OnVehicleMissileInit();
	}
	#if defined VMC_OnGameModeInit
		VMC_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit VMC_OnGameModeInit
#if defined VMC_OnGameModeInit
	forward VMC_OnGameModeInit();
#endif

//Hook: CreateVehicle
stock VMC_CreateVehicle(modelid,Float:x,Float:y,Float:z,Float:angle,color1,color2,respawn_delay,addsiren=0){
	new vehicleid = CreateVehicle(modelid,x,y,z,angle,color1,color2,respawn_delay,addsiren);
	if(IsToggleMissileAutoDisarm()){
		DisarmVehicleMissile(vehicleid);
		SetVehicleMissileDefaultConfig(vehicleid);
	}
	return vehicleid;
}
 
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle VMC_CreateVehicle
 
//Hook: AddStaticVehicle
stock VMC_AddStaticVehicle(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle,color1,color2){
	new vehicleid = AddStaticVehicle(modelid,spawn_x,spawn_y,spawn_z,angle,color1,color2);
	if(IsToggleMissileAutoDisarm()){
		DisarmVehicleMissile(vehicleid);
		SetVehicleMissileDefaultConfig(vehicleid);
	}
	return vehicleid;
}
 
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle VMC_AddStaticVehicle
 
//Hook: AddStaticVehicleEx
stock VMC_AddStaticVehicleEx(modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle,color1,color2,respawn_delay,addsiren=0){
	new vehicleid = AddStaticVehicleEx(modelid,spawn_x,spawn_y,spawn_z,angle,color1,color2,respawn_delay,addsiren);
	if(IsToggleMissileAutoDisarm()){
		DisarmVehicleMissile(vehicleid);
		SetVehicleMissileDefaultConfig(vehicleid);
	}
	return vehicleid;
}
 
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx VMC_AddStaticVehicleEx
 
//Hook: DestroyVehicle
stock VMC_DestroyVehicle(vehicleid){
	if(IsToggleMissileAutoDisarm()){
		DisarmVehicleMissile(vehicleid);
		SetVehicleMissileDefaultConfig(vehicleid);
	}
	return DestroyVehicle(vehicleid);
}
 
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle VMC_DestroyVehicle

//Hook: PutPlayerInVehicle
stock VMC_PutPlayerInVehicle(playerid,vehicleid,seatid){
	if(seatid == 0){
		if(IsToggleMissileAutoDisarm()){
			DisarmVehicleMissile(vehicleid);
			SetVehicleMissileDefaultConfig(vehicleid);
		}
		CallLocalFunction("OnVehicleArmed","dd",playerid,vehicleid);
	}
	return PutPlayerInVehicle(playerid,vehicleid,seatid);
}

#if defined _ALS_PutPlayerInVehicle
    #undef PutPlayerInVehicle
#else
    #define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle VMC_PutPlayerInVehicle

//Hook: OnPlayerEnterVehicle
public OnPlayerEnterVehicle(playerid,vehicleid,ispassenger){
	if(ispassenger == 0){
		if(IsToggleMissileAutoDisarm()){
			DisarmVehicleMissile(vehicleid);
			SetVehicleMissileDefaultConfig(vehicleid);
		}
		CallLocalFunction("OnVehicleArmed","dd",playerid,vehicleid);
	}
	#if defined VMC_OnPlayerEnterVehicle
		VMC_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle VMC_OnPlayerEnterVehicle
#if defined VMC_OnPlayerEnterVehicle
	forward VMC_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger);
#endif

//Hook: OnPlayerClickMap
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ){
	VMC::Target[playerid][0] = fX;
	VMC::Target[playerid][1] = fY;
	#if defined VMC_OnPlayerClickMap
		VMC_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerClickMap
	#undef OnPlayerClickMap
#else
	#define _ALS_OnPlayerClickMap
#endif
#define OnPlayerClickMap VMC_OnPlayerClickMap
#if defined VMC_OnPlayerClickMap
	forward VMC_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	VMC::Target[playerid][0] = VMC::Target[playerid][1] = 0.0;
	#if defined VMC_OnPlayerConnect
		VMC_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect VMC_OnPlayerConnect
#if defined VMC_OnPlayerConnect
	forward VMC_OnPlayerConnect(playerid);
#endif

//EOF