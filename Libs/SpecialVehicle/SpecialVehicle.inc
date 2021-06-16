/*
 SpecialVehicle.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: TDI97, rasheed

 Website: https://adm.ct8.pl

 Plugins: ColAndreas, Streamer
 Modules: 3DTryg, EVF, Missile, VehPara, Mines, ExtendedGrenade

 File Version: 1.0.0
 ColAndreas Version: 1.5.0
 Streamer Version: 2.9.4
 3DTryg Version: 5.1.0

 Functions:
 SpecialVehicle::IsToggledSpecialAbility(vehicleid);
 SpecialVehicle::ToggleSpecialAbility(vehicleid,bool:toggle);
 SpecialVehicle::GetSpecialVehicleHealth(vehicleid);
 SpecialVehicle::SetDefaultDamage(vehicleid);
 SpecialVehicle::EnterPlayer(playerid);
 SpecialVehicle::ExitPlayer(playerid);
 SpecialVehicle::IsPlayerInSpecialVeh(playerid);
 SpecialVehicle::GetPlayerSpecialVehType(playerid);
 SpecialVehicle::GetVehicleAmmo(vehicleid);
 SpecialVehicle::SetVehicleAmmo(vehicleid,ammo);
 SpecialVehicle::GetVehicleSecondaryAmmo(vehicleid);
 SpecialVehicle::SetVehicleSecondaryAmmo(vehicleid,ammo);
 SpecialVehicle::GetDamage(vehicleid);
 SpecialVehicle::SetDamage(vehicleid,Float:damage);
 SpecialVehicle::GetVehicleDamage(vehicleid);
 SpecialVehicle::SetVehicleDamage(vehicleid,Float:vehicle_damage);
 SpecialVehicle::IsToggledTrunkInterior();
 SpecialVehicle::ToggleTrunkInterior(bool:toggle);
 SpecialVehicle::IsToggledTrailerInterior();
 SpecialVehicle::ToggleTrailerInterior(bool:toggle);
 SpecialVehicle::IsToggledMaverickMinigun(vehicleid);
 SpecialVehicle::ToggleMaverickMinigun(vehicleid,bool:toggle);
 SpecialVehicle::Create(modelid,Float:x,Float:y,Float:z,Float:angle,color1,color2,respawn_delay = -1,addsiren = 0,worldid = 0,interiorid = 0);
 SpecialVehicle::CreateMOC(Float:x,Float:y,Float:z,Float:z_angle,respawn_delay = -1,addsiren = 0,worldid = 0,interiorid = 0);
 SpecialVehicle::CreateMOCIncluded(vehicleid,respawn_delay = -1,addsiren = 0);

 Callbacks:
 OnPlayerEnterVehIntRequest(playerid,vehicleid);
 OnPlayerEnterSpecialSeat(playerid);
 OnPlayerEnterOppressor(playerid);
 OnPlayerUseCannonFail(playerid);
 OnPlayerShootRocketFail(playerid);
 OnSpecialTrailerNotConnected(playerid);
 OnPlayerShootOPRocketFail(playerid);
 OnPlayerEnterVehInterior(playerid,vehicleid,with_vehicle);
 OnPlayerExitVehInterior(playerid,vehicleid,with_vehicle);
 OnSpecialVehicleHasNoAmmo(playerid,vehicleid);
 OnSpecialTrailerAttachFail(playerid,vehicleid,trailerid);
*/

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] This include required Streamer v2.9.4 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS_VERSION
	#error [ADM] This include required ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#elseif (COLANDREAS_VERSION < 10500)
	#error [ADM] Update your ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version EVF.inc
#if !defined _EVF_include
	#error [ADM] This include required EVF.inc v3.3.3
#elseif !defined EVF_Version
	#error [ADM] Update your EVF.inc to v3.3.3
#elseif (EVF_Version < 30303)
	#error [ADM] Update your EVF.inc to v3.3.3
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] This include required 3DTryg.inc v5.1.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to v5.1.0
#elseif (TRYG3D_VERSION < 50100)
	#error [ADM] Update your 3DTryg.inc to v5.1.0
#endif

#if !defined TRYG3D_STREAMER
	#error [ADM] Module not initialized: TRYG3D_STREAMER
#endif

//Check Version Missile.inc
#if !defined _missile_launcher
	#error [ADM] This include required Missile.inc v2.3.1
#elseif !defined Missile_Version
	#error [ADM] Update your Missile.inc to v2.3.1
#elseif (Missile_Version < 20301)
	#error [ADM] Update your Missile.inc to v2.3.1
#endif

//Check Version ExtendedGrenade.inc
#if !defined _GRENADE_INCLUDE
	#error [ADM] This include required ExtendedGrenade.inc v1.1.0
#elseif !defined EXTENDED_GRENADE_VERSION
	#error [ADM] Update your ExtendedGrenade.inc to v1.1.0
#elseif (EXTENDED_GRENADE_VERSION < 10100)
	#error [ADM] Update your ExtendedGrenade.inc to v1.1.0
#endif

//Check Version Mines.inc
#if !defined _dynamic_mine_system
	#error [ADM] This include required Mines.inc v2.2.1
#elseif !defined DYNAMIC_MINE_VERSION
	#error [ADM] Update your Mines.inc to v2.2.1
#elseif (DYNAMIC_MINE_VERSION < 20201)
	#error [ADM] Update your Mines.inc to v2.2.1
#endif

#if !defined _vehicle_parachute
	#error [ADM] This include required VehPara v1.2.0
#endif

#if defined _SPECIAL_VEH_INCLUDE
	#endinput
#endif
#define _SPECIAL_VEH_INCLUDE
#define DYNAMIC_FILTERSCRIPT				"ALS:HOOK:METHOD"

#define SpecialVehicle::					SVEH_

#if !defined SPECIAL_VEH_TELEPORT_FREEZE
	#define SPECIAL_VEH_TELEPORT_FREEZE		2000
#endif

#if defined SPECIAL_VEH_USE_TEAMS
	#define SPECIAL_VEH_TEAM_TYPE 			GetPlayerTeam(playerid)
#else
	#define SPECIAL_VEH_TEAM_TYPE 			ANY_TEAM
#endif

#define SPECIAL_VEH_MAX_COMPONENTS			12

#define SPECIAL_VEH_MAX_SEAT_ANDROMADA		16

#define SPECIAL_VEH_TRUNK_NONE				0
#define SPECIAL_VEH_TRUNK_BACK				1
#define SPECIAL_VEH_TRUNK_FRONT				2
#define SPECIAL_VEH_TRUNK_TRAILER			3

#define SPECIAL_VEH_INTERIOR_ID				20

#define SPECIAL_VEH_INVALID_SEAT			-1

#define SPECIAL_VEH_AMMO_INFINITY			-1

#define SPECIAL_VEH_ENTER_FAIL				0
#define SPECIAL_VEH_ENTER_SUCCES			1
#define SPECIAL_VEH_ENTER_ONFOOT			2
#define SPECIAL_VEH_ENTER_NOT_ALLOWED		3

#define SPECIAL_VEH_ACTION_ENTER			0
#define SPECIAL_VEH_ACTION_EXIT				1

#define WEAPON_VEHICLE_INTERIOR				105

#define SPECIAL_VEH_MAX_TYPE				13

#define SVEH_GetValueBit(%0,%1)				((%0) >>> (%1) & 0x01)
#define SVEH_SetValueBit(%0,%1,%2)			((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define SVEH_SetCellValue(%0,%1,%2,%3)		((%0) = (((%0) & ~((((0x01 << (%2))-1) << (%1)*(%2)))) | ((%3) << (%1)*(%2))))
#define SVEH_GetCellValue(%0,%1,%2)			(((%0) & (((0x01 << (%2))-1) << (%1)*(%2))) >>> ((%1)*(%2)))

enum SpecialVehicle::EnumPlayer {
	bool:						SpecialVehicle::IsUseCannon,
	bool:						SpecialVehicle::IsUseMagnet,
	Float:						SpecialVehicle::X,
	Float:						SpecialVehicle::Y,
	Float:						SpecialVehicle::Z,
	Float:						SpecialVehicle::A,
								SpecialVehicle::VID,
	bool:						SpecialVehicle::IsUseTurbo,
								SpecialVehicle::MagnetVehicle,
								SpecialVehicle::InVehicle,
	SpecialVehicle::EnumType:	SpecialVehicle::VehicleType,
								SpecialVehicle::WeaponTick,
	bool:						SpecialVehicle::AutoShot
};

enum SpecialVehicle::EnumVehicle {
	bool:						SpecialVehicle::Overlay,
								SpecialVehicle::SeatUsed,
								SpecialVehicle::OnSeat,
								SpecialVehicle::OnVehicle,
								SpecialVehicle::Included,
	bool:						SpecialVehicle::Locked,
								SpecialVehicle::Ammo[2],
	Float:						SpecialVehicle::Damage,
	Float:						SpecialVehicle::VehicleDamage,
								SpecialVehicle::TruckID,
								SpecialVehicle::TrailerID,
								SpecialVehicle::Minigun,
	Float:						SpecialVehicle::SpawnHealth,
	STREAMER_TAG_3D_TEXT_LABEL:	SpecialVehicle::Text,
	STREAMER_TAG_OBJECT:		SpecialVehicle::Object[SPECIAL_VEH_MAX_COMPONENTS]
};

enum SpecialVehicle::EnumType {
	SPECIAL_VEH_TYPE_NONE,
	SPECIAL_VEH_TYPE_TRUNK_FRONT,
	SPECIAL_VEH_TYPE_TRUNK_BACK,
	SPECIAL_VEH_TYPE_TRUNK_TRAILER,
	SPECIAL_VEH_TYPE_MOC_TRAILER,
	SPECIAL_VEH_TYPE_ANDROMADA,
	SPECIAL_VEH_TYPE_RHINO,
	SPECIAL_VEH_TYPE_SWAT,	
	SPECIAL_VEH_TYPE_FBITRUCK,
	SPECIAL_VEH_TYPE_CARGOBOB,
	SPECIAL_VEH_TYPE_SHAMAL,
	SPECIAL_VEH_TYPE_AT400,
	SPECIAL_VEH_TYPE_NEVADA
};

new Float:	SpecialVehicle::ExitOffset[SpecialVehicle::EnumType:SPECIAL_VEH_MAX_TYPE] = {
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	5.2,
	4.0,	
	3.0,
	5.0,
	9.0,
	20.0,
	12.0
};

new 		SpecialVehicle::PlayerData[MAX_PLAYERS][SpecialVehicle::EnumPlayer],
			SpecialVehicle::VehicleData[MAX_VEHICLES][SpecialVehicle::EnumVehicle],
	Text:	SpecialVehicle::TextDrawViewFinderFlare,
	Text:	SpecialVehicle::TextDrawViewFinderRocket,
	Text:	SpecialVehicle::TextDrawViewFinderGun,
	bool:	SpecialVehicle::UseTrunkInterior = false,
	bool:	SpecialVehicle::UseTrailerInterior = false,
			SpecialVehicle::GSTR[256],
	bool:	SpecialVehicle::Mine[MAX_DYNAMIC_MINES],
			SpecialVehicle::MineBy[MAX_DYNAMIC_MINES] = {INVALID_VEHICLE_ID,...};
	
new Float:SpecialVehicle::AndromadaSeatBike[16][3] = {
	{-1666.0075,-213.0000,14.3684},
	{-1668.8075,-213.0000,14.3684},
	{-1666.0075,-217.0000,14.3684},
	{-1668.8075,-217.0000,14.3684},
	{-1666.0075,-225.0000,14.3684},
	{-1668.8075,-225.0000,14.3684},
	{-1666.0075,-229.0000,14.3684},
	{-1668.8075,-229.0000,14.3684},
	{-1666.0075,-237.0000,14.3684},
	{-1668.8075,-237.0000,14.3684},
	{-1666.0075,-241.0000,14.3684},
	{-1668.8075,-241.0000,14.3684},
	{-1666.0075,-249.0000,14.3684},
	{-1668.8075,-249.0000,14.3684},
	{-1666.0075,-253.0000,14.3684},
	{-1668.8075,-253.0000,14.3684}
};

new Float:SpecialVehicle::AndromadaSeatCar[4][3] = {
	{-1667.4075,-215.0000,14.3684},
	{-1667.4075,-227.0000,14.3684},
	{-1667.4075,-239.0000,14.3684},
	{-1667.4075,-251.0000,14.3684}
};

#define SVEH_IsToggledSpecialAbility(%0)		(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Overlay])

#define SVEH_IsPlayerInSpecialVeh(%0) 			(SpecialVehicle::PlayerData[(%0)][SpecialVehicle::InVehicle] != INVALID_VEHICLE_ID)
#define SVEH_GetPlayerSpecialVehType(%0)		(SpecialVehicle::PlayerData[(%0)][SpecialVehicle::VehicleType])

#define SVEH_GetVehicleAmmo(%0) 				(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Ammo][0])
#define SVEH_SetVehicleAmmo(%0,%1) 				(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Ammo][0] = (%1))

#define SVEH_GetVehicleSecondaryAmmo(%0) 		(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Ammo][1])
#define SVEH_SetVehicleSecondaryAmmo(%0,%1) 	(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Ammo][1] = (%1))

#define SVEH_IsToggledTrunkInterior()			(SpecialVehicle::UseTrunkInterior)
#define SVEH_ToggleTrunkInterior(%0)			(SpecialVehicle::UseTrunkInterior = (%0))

#define SVEH_IsToggledTrailerInterior()			(SpecialVehicle::UseTrailerInterior)
#define SVEH_ToggleTrailerInterior(%0)			(SpecialVehicle::UseTrailerInterior = (%0))

#define SVEH_IsToggledMaverickMinigun(%0)		(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Minigun])

#define SVEH_GetVehicleDamage(%0) 				(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::VehicleDamage])
#define SVEH_SetVehicleDamage(%0,%1) 			(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::VehicleDamage] = (%1))

#define SVEH_GetDamage(%0) 						(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Damage])
#define SVEH_SetDamage(%0,%1) 					(SpecialVehicle::VehicleData[(%0)][SpecialVehicle::Damage] = (%1))

forward OnPlayerEnterVehIntRequest(playerid,vehicleid);
forward OnPlayerEnterSpecialSeat(playerid);
forward OnPlayerEnterOppressor(playerid);
forward OnPlayerUseCannonFail(playerid);
forward OnPlayerShootRocketFail(playerid);
forward OnSpecialTrailerNotConnected(playerid);
forward OnPlayerShootOPRocketFail(playerid);
forward OnPlayerEnterVehInterior(playerid,vehicleid,with_vehicle);
forward OnPlayerExitVehInterior(playerid,vehicleid,with_vehicle);
forward OnSpecialVehicleHasNoAmmo(playerid,vehicleid);
forward OnSpecialTrailerAttachFail(playerid,vehicleid,trailerid);

stock Float:SpecialVehicle::GetSpecialVehicleHealth(vehicleid){
	if(!IsValidVehicle(vehicleid)) return 1000.0;
	switch(GetVehicleModel(vehicleid)){
		case 432, 548: return 25000.0;
		case 592: return 200000.0;
		case 428, 487, 497, 528, 577, 578, 601, 504, 520,
			 425, 476, 430, 470, 595, 417: return 12000.0;
		case 519, 522: return 5000.0;
		case 591, 515: return 50000.0;
	}
	return 1000.0;
}

stock SpecialVehicle::GetVehicleBootType(vehicleid){
	if(!IsValidVehicle(vehicleid)) return SPECIAL_VEH_TRUNK_NONE;
	switch(GetVehicleModel(vehicleid)){
		case	400,401,402,404,405,409,410,412,419,420,
				421,426,429,434,436,438,439,445,458,466,
				467,474,477,479,480,489,490,491,492,495,
				496,505,506,507,516,517,518,526,527,529,
				533,534,536,540,542,545,546,547,549,550,
				551,555,558,559,560,561,562,565,566,567,
				575,576,579,580,585,587,589,596,597,598,
				599,602,603,604: return SPECIAL_VEH_TRUNK_BACK;
				
		case	415,451,541: return SPECIAL_VEH_TRUNK_FRONT;
		
		case	584,435,450,591: return SPECIAL_VEH_TRUNK_TRAILER;
	}
	return SPECIAL_VEH_TRUNK_NONE;
}

stock SpecialVehicle::AndromadaVehToBig(vehicleid){
	if(!IsValidVehicle(vehicleid)) return 0;
	switch(GetVehicleModel(vehicleid)){
		case 	403, 406, 407, 408, 409, 427, 431, 433, 437, 442,
				443, 444, 455, 456, 508, 514, 515, 524, 532, 537,
				538, 544, 556, 557, 588, 432: return 1;
		case 578, 601: {
			if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]) return 0;
			return 1;
		}
	}
	return 0;
}

stock SpecialVehicle::LinkComponent(vehicleid,worldid,interiorid){
	if(!IsValidVehicle(vehicleid)) return 0;
	for(new k = 0; k < 4; k++){
		if(IsValidDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k])){
			Streamer::SetIntData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],E_STREAMER_WORLD_ID,worldid);
			Streamer::SetIntData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],E_STREAMER_INTERIOR_ID,interiorid);
		}
	}
	return 1;
}

stock SpecialVehicle::SetDefaultDamage(vehicleid){
	if(!IsValidVehicle(vehicleid)) return 0;
	switch(GetVehicleModel(vehicleid)){
		case 470, 497, 504, 528, 487: {
			SpecialVehicle::SetDamage(vehicleid,15.0);
			SpecialVehicle::SetVehicleDamage(vehicleid,100.0);
		}
		case 522: {
			SpecialVehicle::SetDamage(vehicleid,15.0);
			SpecialVehicle::SetVehicleDamage(vehicleid,500.0);
		}
		case 578, 515: {
			SpecialVehicle::SetDamage(vehicleid,15.0);
			SpecialVehicle::SetVehicleDamage(vehicleid,5000.0);
		}
	}
	return 1;
}

stock SpecialVehicle::LinkPlayersInVehicle(vehicleid,link_action,target_vehicle=INVALID_VEHICLE_ID,SpecialVehicle::EnumType:target_type=SPECIAL_VEH_TYPE_NONE){
	if(!IsValidVehicle(vehicleid)) return 0;
	Tryg3D::Foreach(playerid){
		if(GetPlayerVehicleID(playerid) == vehicleid){
			switch(link_action){
				case SPECIAL_VEH_ACTION_ENTER: {
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,target_vehicle,1);
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = target_vehicle;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = target_type;
					if(target_type == SPECIAL_VEH_TYPE_ANDROMADA){
						GivePlayerWeapon(playerid,46,1);
					}
				}
				case SPECIAL_VEH_ACTION_EXIT: {
					CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,target_vehicle,1);
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
				}
			}
		}
	}
	return 1;
}

stock SpecialVehicle::ToggleSpecialAbility(vehicleid,bool:toggle){
	if(!IsValidVehicle(vehicleid)) return 0;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay] = toggle;
	if(toggle){
		SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SpawnHealth] = SpecialVehicle::GetSpecialVehicleHealth(vehicleid);
		SpecialVehicle::CreateOverlay(vehicleid);
	} else {
		SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SpawnHealth] = 1000.0;
		SpecialVehicle::DestroyOverlay(vehicleid);
	}
	SetVehicleHealth(vehicleid,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SpawnHealth]);
	SpecialVehicle::SetDefaultDamage(vehicleid);
	return 1;
}

stock SpecialVehicle::ToggleMaverickMinigun(vehicleid,bool:toggle){
	if(!IsValidVehicle(vehicleid)) return 0;
	new modelid = GetVehicleModel(vehicleid);
	if(modelid == 497 || modelid == 487){
		if(toggle){
			if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Minigun]){
				for(new k = 0; k < 4; k++){
					if(IsValidDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k])){
						DestroyDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
						SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
					}
				}
			}
			new Float:x,Float:y,Float:z;
			GetVehiclePos(vehicleid,x,y,z);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(2985,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2] = CreateDynamicObject(2985,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0xFF000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],0,5150,"wiresetc_las2","metpat64",0xFF000000);
			for(new k = 0; k < 4; k++){
				SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
			}
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,2.7,2.0,-1.0,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,2.7,2.0,0.9,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],vehicleid,-2.7,2.0,-1.0,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],vehicleid,-2.7,2.0,0.9,0.0,0.0,0.0);
		} else {
			Tryg3D::Foreach(i){
				if(IsPlayerInAnyVehicle(i)){
					if(GetPlayerVehicleID(i) == vehicleid){
						if(SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon]){
							SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon] = false;
							SpecialVehicle::PlayerData[i][SpecialVehicle::AutoShot] = false;
							AttachCameraToDynamicObject(i,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
							SetCameraBehindPlayer(i);
							TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderGun);
							TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderFlare);
							TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderRocket);
						}
					}
				}
			}
			for(new k = 0; k < 4; k++){
				if(IsValidDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k])){
					DestroyDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
					SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
				}
			}
		}
		SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Minigun] = toggle;
		return 1;
	}
	return 0;
}

stock SpecialVehicle::Create(modelid,Float:x,Float:y,Float:z,Float:angle,color1,color2,respawn_delay = -1,addsiren = 0,worldid = 0,interiorid = 0){
	new vehicleid = EVF::CreateVehicle(modelid,x,y,z,angle,color1,color2,respawn_delay,addsiren,worldid,interiorid);
	if(!IsValidVehicle(vehicleid)) return INVALID_VEHICLE_ID;
	SpecialVehicle::ToggleSpecialAbility(vehicleid,true);
	return vehicleid;
}

stock SpecialVehicle::UpdateText(vehicleid){
	if(!SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]) return 0;
	switch(GetVehicleModel(vehicleid)){
		case 601: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Anti Missile]{FFFFFF}");
		}
		case 522: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Oppressor]{FFFFFF}");
		}
		case 578: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Anti Air]{FFFFFF}");
		}
		case 591: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Mobile Operations Center]{FFFFFF}\nCargo: %d/1",SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed]);
		}
		case 497, 487: {
			if(SpecialVehicle::IsToggledMaverickMinigun(vehicleid)){
				format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Valkyrie]{FFFFFF}");
			} else {
				format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Air Support]{FFFFFF}");
			}
		}
		case 504: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Armed Tampa]{FFFFFF}");
		}
		case 528: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Insurgent]{FFFFFF}");
		}
		case 592: {
			new seat_cnt;
			for(new seatid = 0; seatid < 16; seatid++){
				if(SpecialVehicle::GetValueBit(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],seatid) == 0b1){
					seat_cnt++;
				}
			}
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Cargo Plane]{FFFFFF}\nCargo: %d/16",seat_cnt);
		}
		case 470: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Armed Patriot]{FFFFFF}");
		}
		case 595: {
			format(SpecialVehicle::GSTR,sizeof(SpecialVehicle::GSTR),"[Armed Launch]{FFFFFF}");
		}
		default: {
			SpecialVehicle::GSTR = "";
		}
	}
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
		format(SpecialVehicle::GSTR,256,"%s\nAmmo: %d",SpecialVehicle::GSTR,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Ammo][0]);
	}
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Ammo][1] != SPECIAL_VEH_AMMO_INFINITY){
		format(SpecialVehicle::GSTR,256,"%s\nSecondary Ammo: %d",SpecialVehicle::GSTR,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Ammo][1]);
	}
	UpdateDynamic3DTextLabelText(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Text],0x00AAFFFF,SpecialVehicle::GSTR);
	return 1;
}

stock SpecialVehicle::CreateMOC(Float:x,Float:y,Float:z,Float:z_angle,respawn_delay = -1,addsiren = 0,worldid = 0,interiorid = 0){
	new vehicleid = CreateVehicle(515,x,y,z,z_angle,1,1,respawn_delay,addsiren);
	if(!IsValidVehicle(vehicleid)) return INVALID_VEHICLE_ID;
	SetVehicleInterior(vehicleid,interiorid);
	SetVehicleVirtualWorld(vehicleid,worldid);
	SpecialVehicle::ToggleSpecialAbility(vehicleid,true);
	new Float:tx,Float:ty,trailerid;
	GetPointInFront2D(x,y,Tryg3D::CompressRotation(z_angle-180.0),9.38,tx,ty);
	trailerid = CreateVehicle(591,tx,ty,z,z_angle,1,1,respawn_delay,addsiren);
	if(!IsValidVehicle(trailerid)){
		DestroyVehicle(vehicleid);
		return INVALID_VEHICLE_ID;
	}
	SetVehicleInterior(trailerid,interiorid);
	SetVehicleVirtualWorld(trailerid,worldid);
	SpecialVehicle::ToggleSpecialAbility(trailerid,true);
	SpecialVehicle::VehicleData[trailerid][SpecialVehicle::TruckID] = vehicleid;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TrailerID] = trailerid;
	AttachTrailerToVehicle(trailerid,vehicleid);
	return vehicleid;
}

stock SpecialVehicle::CreateMOCIncluded(vehicleid,respawn_delay = -1,addsiren = 0){
	if(!IsValidVehicle(vehicleid)) return INVALID_VEHICLE_ID;
	new trailerid = SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TrailerID];
	if(GetVehicleModel(trailerid) != 591) return INVALID_VEHICLE_ID;
	if(!SpecialVehicle::VehicleData[trailerid][SpecialVehicle::Overlay]) return INVALID_VEHICLE_ID;
	if(SpecialVehicle::VehicleData[trailerid][SpecialVehicle::SeatUsed]) return INVALID_VEHICLE_ID;
	new vid = SpecialVehicle::Create(470,300.5814,1997.0906,17.3813,0.0,0,0,respawn_delay,addsiren,trailerid,SPECIAL_VEH_INTERIOR_ID);
	if(!IsValidVehicle(vid)) return INVALID_VEHICLE_ID;
	SpecialVehicle::VehicleData[trailerid][SpecialVehicle::SeatUsed] = 1;
	SpecialVehicle::VehicleData[trailerid][SpecialVehicle::Locked] = true;
	SpecialVehicle::VehicleData[vid][SpecialVehicle::Included] = trailerid;
	SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat] = 1;
	SpecialVehicle::VehicleData[vid][SpecialVehicle::OnVehicle] = trailerid;
	SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,SPECIAL_VEH_INTERIOR_ID);
	SpecialVehicle::LinkComponent(vid,trailerid,SPECIAL_VEH_INTERIOR_ID);
	SwitchVehicleEngine(vid,false);
	SpecialVehicle::UpdateText(trailerid);
	return vid;
}

stock SpecialVehicle::EnterPlayer(playerid){
	new F4[Vectors3D];
	for(new vehicleid = 1, vehicleid_j = GetVehiclePoolSize(); vehicleid <= vehicleid_j; vehicleid++){
		if(!IsValidVehicle(vehicleid)) continue;
		GetVehiclePos(vehicleid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
		switch(GetVehicleModel(vehicleid)){
			case 592: {
				if(IsPlayerInRangeOfPoint(playerid,25.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					if(IsPlayerInAnyVehicle(playerid)){
						new vid = GetPlayerVehicleID(playerid);
						switch(GetVehicleModel(vid)){
							case 470, 504, 528, 578, 601: {
								Tryg3D::Foreach(i){
									if(IsPlayerInAnyVehicle(i)){
										if(GetPlayerVehicleID(i) == vid && GetPlayerVehicleSeat(i) == 1){
											if(SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon]){
												SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon] = false;
												SpecialVehicle::PlayerData[i][SpecialVehicle::AutoShot] = false;
												AttachCameraToDynamicObject(i,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
												SetCameraBehindPlayer(i);
												TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderGun);
												TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderFlare);
												TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderRocket);
											}
										}
									}
								}
							}
						}
						if(IsVehicleFlag(GetVehicleFlags(vid),VF_BIKES) || IsVehicleFlag(GetVehicleFlags(vid),VF_RC)){
							for(new seatid = 0; seatid < 16; seatid++){
								if(SpecialVehicle::GetValueBit(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],seatid) == 0b0){
									SpecialVehicle::SetValueBit(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],seatid,0b1);
									SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat] = seatid;
									SpecialVehicle::VehicleData[vid][SpecialVehicle::OnVehicle] = vehicleid;
									if(!IsToggleVehicleParachute(vid)) ToggleVehicleParachute(vid,true);
									SwitchVehicleEngine(vid,false);
									SetPlayerAbsolutePositionVeh(playerid,SpecialVehicle::AndromadaSeatBike[seatid][0],SpecialVehicle::AndromadaSeatBike[seatid][1],SpecialVehicle::AndromadaSeatBike[seatid][2],180.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
									SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,SPECIAL_VEH_INTERIOR_ID);
									SpecialVehicle::LinkPlayersInVehicle(vid,SPECIAL_VEH_ACTION_ENTER,vehicleid,SPECIAL_VEH_TYPE_ANDROMADA);
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
										SpecialVehicle::LinkComponent(vid,vehicleid,SPECIAL_VEH_INTERIOR_ID);
									}
									SpecialVehicle::UpdateText(vehicleid);
									return SPECIAL_VEH_ENTER_SUCCES;
								}
							}
						} else if(IsVehicleFlag(GetVehicleFlags(vid),VF_STREET) && !SpecialVehicle::AndromadaVehToBig(vid)){
							for(new seatid = 0; seatid < 4; seatid++){
								if(SpecialVehicle::GetCellValue(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],seatid,4) == 0b0){
									SpecialVehicle::SetCellValue(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],seatid,4,0b1111);
									SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat] = seatid;
									SpecialVehicle::VehicleData[vid][SpecialVehicle::OnVehicle] = vehicleid;
									if(!IsToggleVehicleParachute(vid)) ToggleVehicleParachute(vid,true);
									SwitchVehicleEngine(vid,false);
									SetPlayerAbsolutePositionVeh(playerid,SpecialVehicle::AndromadaSeatCar[seatid][0],SpecialVehicle::AndromadaSeatCar[seatid][1],SpecialVehicle::AndromadaSeatCar[seatid][2],180.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
									SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,SPECIAL_VEH_INTERIOR_ID);
									SpecialVehicle::LinkPlayersInVehicle(vid,SPECIAL_VEH_ACTION_ENTER,vehicleid,SPECIAL_VEH_TYPE_ANDROMADA);
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
										SpecialVehicle::LinkComponent(vid,vehicleid,SPECIAL_VEH_INTERIOR_ID);
									}
									SpecialVehicle::UpdateText(vehicleid);
									return SPECIAL_VEH_ENTER_SUCCES;
								}
							}
						}
						return SPECIAL_VEH_ENTER_ONFOOT;
					} else {
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_ANDROMADA;
						SetPlayerAbsolutePosition(playerid,-1667.1566,-202.4945,15.1159,180.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
						GivePlayerWeapon(playerid,46,1);
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_ANDROMADA;
						CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
						return SPECIAL_VEH_ENTER_SUCCES;
					}
				}
			}
			case 591: {
				if(IsPlayerInRangeOfPoint(playerid,12.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
						if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
						if(IsPlayerInAnyVehicle(playerid)){
							new vid = GetPlayerVehicleID(playerid);
							if(!SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Locked] || (SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Locked] && SpecialVehicle::VehicleData[vid][SpecialVehicle::Included] == vehicleid)){
								if(GetVehicleModel(vid) == 470 && SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay] && !SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed]){
									Tryg3D::Foreach(i){
										if(IsPlayerInAnyVehicle(i)){
											if(GetPlayerVehicleID(i) == vid && GetPlayerVehicleSeat(i) == 1){
												if(SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon]){
													SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon] = false;
													SpecialVehicle::PlayerData[i][SpecialVehicle::AutoShot] = false;
													AttachCameraToDynamicObject(i,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
													SetCameraBehindPlayer(i);
													TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderGun);
													TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderFlare);
													TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderRocket);
												}
											}
										}
									}
									SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed] = 1;
									SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat] = 1;
									SpecialVehicle::VehicleData[vid][SpecialVehicle::OnVehicle] = vehicleid;
									RepairVehicle(vid);
									SetVehicleHealth(vid,SpecialVehicle::VehicleData[vid][SpecialVehicle::SpawnHealth]);
									SwitchVehicleEngine(vid,false);
									SetPlayerAbsolutePositionVeh(playerid,300.5814,1997.0906,17.3813,0.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
									SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,SPECIAL_VEH_INTERIOR_ID);
									SpecialVehicle::LinkPlayersInVehicle(vid,SPECIAL_VEH_ACTION_ENTER,vehicleid,SPECIAL_VEH_TYPE_MOC_TRAILER);
									SpecialVehicle::LinkComponent(vid,vehicleid,SPECIAL_VEH_INTERIOR_ID);
									SpecialVehicle::UpdateText(vehicleid);
									return SPECIAL_VEH_ENTER_SUCCES;
								}
							}
						} else {
							SetPlayerAbsolutePosition(playerid,301.7278,2001.1680,18.2882,0.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_MOC_TRAILER;
							CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
							return SPECIAL_VEH_ENTER_SUCCES;
						}
					} else {
						if(SpecialVehicle::IsToggledTrailerInterior()){
							if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
							if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_TRUNK_TRAILER;
							SetPlayerAbsolutePosition(playerid,153.2095,2031.7423,1046.8811,1.0000,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
							CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
							return SPECIAL_VEH_ENTER_SUCCES;
						}
					}
				}
			}
			case 432: {
				if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_RHINO;
					SetPlayerAbsolutePosition(playerid,304.7444,1948.0719,2017.6335,180.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			case 528: {
				if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_FBITRUCK;
					SetPlayerAbsolutePosition(playerid,1060.5330,1776.3317,10.8203,180.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			case 553: {
				if(IsPlayerInRangeOfPoint(playerid,8.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NEVADA;
					SetPlayerAbsolutePosition(playerid,1378.5438,1771.0582,10.8662,270.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			case 601: {
				if(IsPlayerInRangeOfPoint(playerid,4.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_SWAT;
					SetPlayerAbsolutePosition(playerid,1300.4564,1998.1667,1017.6385,0.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			case 548: {
				if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_CARGOBOB;
					GivePlayerWeapon(playerid,46,1);
					SetPlayerAbsolutePosition(playerid,1975.8558,-2631.8870,13.5577,270.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			case 519: {
				if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_SHAMAL;
					GivePlayerWeapon(playerid,46,1);
					SetPlayerAbsolutePosition(playerid,1894.1605,-4166.7290,2.4545,90.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			case 577: {
				if(IsPlayerInRangeOfPoint(playerid,20.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
					if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
					if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_AT400;
					GivePlayerWeapon(playerid,46,1);
					SetPlayerAbsolutePosition(playerid,16.0939,-14.7427,536.6696,180.0,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
					return SPECIAL_VEH_ENTER_SUCCES;
				}
			}
			default: {
				switch(SpecialVehicle::GetVehicleBootType(vehicleid)){
					case SPECIAL_VEH_TRUNK_BACK: {
						if(SpecialVehicle::IsToggledTrunkInterior()){
							if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
								if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
								if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_TRUNK_BACK;
								SetPlayerAbsolutePosition(playerid,196.02711,2081.85156,1024.48446,1.00000,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
								CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
								return SPECIAL_VEH_ENTER_SUCCES;
							}
						}
					}
					case SPECIAL_VEH_TRUNK_FRONT: {
						if(SpecialVehicle::IsToggledTrunkInterior()){
							if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
								if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
								if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_TRUNK_FRONT;
								SetPlayerAbsolutePosition(playerid,194.11169,2086.19580,1025.60100,1.00000,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
								CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
								return SPECIAL_VEH_ENTER_SUCCES;
							}
						}
					}
					case SPECIAL_VEH_TRUNK_TRAILER: {
						if(SpecialVehicle::IsToggledTrailerInterior()){
							if(IsPlayerInRangeOfPoint(playerid,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z])){
								if(IsPlayerInAnyVehicle(playerid)) return SPECIAL_VEH_ENTER_ONFOOT;
								if(!CallLocalFunction("OnPlayerEnterVehIntRequest","dd",playerid,vehicleid)) return SPECIAL_VEH_ENTER_NOT_ALLOWED;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = vehicleid;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_TRUNK_TRAILER;
								SetPlayerAbsolutePosition(playerid,153.2095,2031.7423,1046.8811,1.0000,vehicleid,SPECIAL_VEH_INTERIOR_ID,SPECIAL_VEH_TELEPORT_FREEZE);
								CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,vehicleid,0);
								return SPECIAL_VEH_ENTER_SUCCES;
							}
						}
					}
				}
			}
			
		}
	}
	return SPECIAL_VEH_ENTER_FAIL;
}

stock SpecialVehicle::ExitPlayer(playerid){
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] == INVALID_VEHICLE_ID) return 0;
	new vehicleid = SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle], F4[Float3D];
	switch(SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType]){
		case SPECIAL_VEH_TYPE_TRUNK_FRONT, SPECIAL_VEH_TYPE_TRUNK_BACK, SPECIAL_VEH_TYPE_TRUNK_TRAILER: {
			GetVehiclePos(vehicleid,F4[T3D:tX],F4[T3D:tY],F4[T3D:Z]);
			GetVehicleZAngle(vehicleid,F4[T3D:rZ]);
			if(IsVehicleOccupied(vehicleid)){
				GetVehiclePartPos(vehicleid,VEHICLE_PART_TRUNK,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],0.0,0.0,1.0);
			} else {
				GetPointInFront2D(F4[T3D:tX],F4[T3D:tY],Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),3.0,F4[T3D:X],F4[T3D:Y]);
			}
			SetPlayerAbsolutePosition(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rZ]+180.0,GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
			CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,vehicleid,0);
		}
		case SPECIAL_VEH_TYPE_MOC_TRAILER: {
			GetVehiclePos(vehicleid,F4[T3D:tX],F4[T3D:tY],F4[T3D:Z]);
			GetVehicleZAngle(vehicleid,F4[T3D:rZ]);
			if(IsVehicleOccupied(vehicleid)){
				Item::GetOrientationPos(vehicleid,item_vehicle,o_back,12.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			} else {
				GetPointInFront2D(F4[T3D:tX],F4[T3D:tY],Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),12.0,F4[T3D:X],F4[T3D:Y]);
			}
			if(IsPlayerInAnyVehicle(playerid)){
				new vid = GetPlayerVehicleID(playerid);
				if(IsCollisionFlag(Item::GetCollisionFlags(vehicleid,item_vehicle),POSITION_FLAG_GROUND)){
					InteriorFindZ(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],2.0,F4[T3D:Z]);
					SetPlayerAbsolutePositionVeh(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]+1.0,F4[T3D:rZ],GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
					SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,GetVehicleInterior(vehicleid));
				} else {
					SetPlayerAbsolutePositionVeh(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rZ],GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
					SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,GetVehicleInterior(vehicleid));
				}
				CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,vehicleid,1);
				SpecialVehicle::LinkPlayersInVehicle(vid,SPECIAL_VEH_ACTION_EXIT);
				if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
					SpecialVehicle::LinkComponent(vid,GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid));
				}
				SwitchVehicleEngine(vid,true);
				SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed] = 0;
				SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat] = SPECIAL_VEH_INVALID_SEAT;
				SpecialVehicle::VehicleData[vid][SpecialVehicle::OnVehicle] = INVALID_VEHICLE_ID;
			} else {
				if(IsCollisionFlag(Item::GetCollisionFlags(vehicleid,item_vehicle),POSITION_FLAG_GROUND)){
					InteriorFindZ(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],2.0,F4[T3D:Z]);
					SetPlayerAbsolutePosition(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]+1.0,Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
				} else {
					SetPlayerAbsolutePosition(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
				}
				CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,vehicleid,0);
			}
			SpecialVehicle::UpdateText(vehicleid);
		}
		case SPECIAL_VEH_TYPE_ANDROMADA: {
			GetVehiclePos(vehicleid,F4[T3D:tX],F4[T3D:tY],F4[T3D:Z]);
			GetVehicleZAngle(vehicleid,F4[T3D:rZ]);
			if(IsVehicleOccupied(vehicleid)){
				Item::GetOrientationPos(vehicleid,item_vehicle,o_back,25.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			} else {
				GetPointInFront2D(F4[T3D:tX],F4[T3D:tY],Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),25.0,F4[T3D:X],F4[T3D:Y]);
			}
			if(IsPlayerInAnyVehicle(playerid)){
				new vid = GetPlayerVehicleID(playerid);
				if(IsCollisionFlag(Item::GetCollisionFlags(vehicleid,item_vehicle),POSITION_FLAG_GROUND)){
					InteriorFindZ(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],2.0,F4[T3D:Z]);
					SetPlayerAbsolutePositionVeh(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]+1.0,F4[T3D:rZ],GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
					SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,GetVehicleInterior(vehicleid));
				} else {
					SetPlayerAbsolutePositionVeh(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rZ],GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
					SetVehiclePropertyValue(vid,e_VEHICLE_INTERIOR,GetVehicleInterior(vehicleid));
				}
				CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,vehicleid,1);
				SpecialVehicle::LinkPlayersInVehicle(vid,SPECIAL_VEH_ACTION_EXIT);
				if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
					SpecialVehicle::LinkComponent(vid,GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid));
				}
				SwitchVehicleEngine(vid,true);
				if(IsVehicleFlag(GetVehicleFlags(vid),VF_BIKES) || IsVehicleFlag(GetVehicleFlags(vid),VF_RC)){
					SpecialVehicle::SetValueBit(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat],0b0);
				} else if(IsVehicleFlag(GetVehicleFlags(vid),VF_STREET) && !SpecialVehicle::AndromadaVehToBig(vid)){
					SpecialVehicle::SetCellValue(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed],SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat],4,0b0000);
				}
				SpecialVehicle::VehicleData[vid][SpecialVehicle::OnSeat] = SPECIAL_VEH_INVALID_SEAT;
				SpecialVehicle::VehicleData[vid][SpecialVehicle::OnVehicle] = INVALID_VEHICLE_ID;
			} else {
				if(IsCollisionFlag(Item::GetCollisionFlags(vehicleid,item_vehicle),POSITION_FLAG_GROUND)){
					InteriorFindZ(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],2.0,F4[T3D:Z]);
					SetPlayerAbsolutePosition(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]+1.0,Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
				} else {
					SetPlayerAbsolutePosition(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
				}
				CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,vehicleid,0);
			}
			SpecialVehicle::UpdateText(vehicleid);
		}
		default: {
			GetVehicleZAngle(vehicleid,F4[T3D:rZ]);
			if(IsVehicleOccupied(vehicleid)){
				Item::GetOrientationPos(vehicleid,item_vehicle,o_back,SpecialVehicle::ExitOffset[SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType]],F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			} else {
				GetVehiclePos(vehicleid,F4[T3D:tX],F4[T3D:tY],F4[T3D:Z]);
				GetPointInFront2D(F4[T3D:tX],F4[T3D:tY],Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),SpecialVehicle::ExitOffset[SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType]],F4[T3D:X],F4[T3D:Y]);
			}
			InteriorFindZ(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],2.0,F4[T3D:Z]);
			SetPlayerAbsolutePosition(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]+1.0,Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),GetVehicleVirtualWorld(vehicleid),GetVehicleInterior(vehicleid),SPECIAL_VEH_TELEPORT_FREEZE);
			CallLocalFunction("OnPlayerExitVehInterior","ddd",playerid,vehicleid,0);
		}
	}
	new target_vehid = GetVehicleVirtualWorld(vehicleid);
	if(target_vehid != 0 && IsValidVehicle(target_vehid)){
		if(GetVehicleInterior(vehicleid) == SPECIAL_VEH_INTERIOR_ID){
			switch(GetVehicleModel(target_vehid)){
				case 592: {
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = target_vehid;
					SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_ANDROMADA;
					CallLocalFunction("OnPlayerEnterVehInterior","ddd",playerid,target_vehid,0);
					return 1;
				}
			}
		}
	}
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
	return 1;
}

stock SpecialVehicle::CreateOverlay(vehicleid){
	if(!IsValidVehicle(vehicleid)) return 0;
	SpecialVehicle::DestroyOverlay(vehicleid);
	new Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Text] = CreateDynamic3DTextLabel("",0x00AAFFFF,0.0,0.0,1.0,25.0,INVALID_PLAYER_ID,vehicleid,0,-1,-1,-1,25.0);
	SpecialVehicle::UpdateText(vehicleid);
	switch(GetVehicleModel(vehicleid)){
		case 595: {
			//Launch
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(2985,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,3.5,0.2,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,3.5,2.1,0.0,0.0,90.0);
		}
		case 548: {
			//Cargobob
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(3053,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,0.0,-2.1,0.0,0.0,0.0);
		}
		case 417: {
			//Leviathan
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(3053,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,0.0,-0.8,0.0,0.0,0.0);
		}
		case 428: {
			//Securicar
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(19601,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],0,14668,"711c","cj_white_wall2",0xFF006666);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,3.140000,-0.519999,-20.0,0.0,180.0);
		}
		case 601: {
			//swat tank
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(18848,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],1,3077,"blkbrdx","nf_blackbrd",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],4,3077,"blkbrdx","nf_blackbrd",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],5,3077,"blkbrdx","nf_blackbrd",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,-1.8,0.7,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,-1.8,6.4,0.0,0.0,90.0);
		}
		case 470: {
			//patriot
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(2985,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,-0.5,0.2,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,-0.5,2.1,0.0,0.0,90.0);
		}
		case 504: {
			//Bloodring Banger
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(2985,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2] = CreateDynamicObject(360,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3] = CreateDynamicObject(360,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,-0.5,0.0,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,-0.5,1.9,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],vehicleid,0.7,-0.5,0.89,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],vehicleid,-0.6,-0.5,0.89,0.0,0.0,90.0);
		}
		case 522: {
			//NRG-500
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(359,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.05,0.7,0.3,0.0,0.0,90.0);
		}
		case 528: {
			//fbitruck
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(2985,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,-1.1,0.2,0.0,0.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,-1.1,2.1,0.0,0.0,90.0);
		}
		case 578: {
			//dft
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(18848,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],1,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],3,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],4,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],5,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,-3.6,-1.0,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,-3.6,4.7,0.0,0.0,90.0);
		}
		case 487, 497: {
			//maverick
			if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Minigun]) SpecialVehicle::ToggleMaverickMinigun(vehicleid,true);
			for(new k = 4; k < 12; k++){
				SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = CreateDynamicObject(1698,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
				SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
			}
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],vehicleid,2.4-1.36,0.8001,-1.0,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][5],vehicleid,2.4-1.36,0.8,-1.0,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][6],vehicleid,-2.4+1.36,0.8001,-1.0,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][7],vehicleid,-2.4+1.36,0.8,-1.0,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][8],vehicleid,2.4,0.8001,-1.0,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][9],vehicleid,2.4,0.8,-1.0,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][10],vehicleid,-2.4,0.8001,-1.0,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][11],vehicleid,-2.4,0.8,-1.0,0.0,180.0,0.0);
		}
		case 592: {
			//andromada
			for(new k = 0; k < 8; k++){
				SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = CreateDynamicObject(18848,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
				SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
				SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],0,13628,"8stad","stadroof",0x00000000);
				SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],1,14581,"ab_mafiasuitea","barbersmir1",0x00000000);
				SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],3,14581,"ab_mafiasuitea","barbersmir1",0x00000000);
				SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],4,14581,"ab_mafiasuitea","barbersmir1",0x00000000);
				SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],5,14581,"ab_mafiasuitea","barbersmir1",0x00000000);
			}
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,5.5,0.0,3.0,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,-5.5,0.0,3.0,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],vehicleid,9.0,-2.0,2.9,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],vehicleid,-9.0,-2.0,2.9,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],vehicleid,15.0,-5.0,2.75,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][5],vehicleid,-15.0,-5.0,2.75,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][6],vehicleid,19.0,-7.0,2.6,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][7],vehicleid,-19.0,-7.0,2.6,0.0,180.0,0.0);
			
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][8] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][8],vehicleid,0.0,0.0,-2.5,0.0,0.0,0.0);
		}
		case 449: {
			//tram
			for(new k = 0; k < 12; k++){
				SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = CreateDynamicObject(1698,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			}
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,1.5,3.30873,-1.1,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,1.5,3.30873,-1.1,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],vehicleid,-1.5,3.30873,-1.1,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],vehicleid,-1.5,3.30873,-1.1,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],vehicleid,1.5,0.0,-1.1,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][5],vehicleid,1.5,0.0,-1.1,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][6],vehicleid,-1.5,0.0,-1.1,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][7],vehicleid,-1.5,0.0,-1.1,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][8],vehicleid,1.5,-3.30873,-1.1,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][9],vehicleid,1.5,-3.30873,-1.1,0.0,180.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][10],vehicleid,-1.5,-3.30873,-1.1,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][11],vehicleid,-1.5,-3.30873,-1.1,0.0,180.0,0.0);
		}
		case 515: {
			//MOC Truck (Roadtrain)
			for(new k = 0; k < 5; k++){
				SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = CreateDynamicObject(1698,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
				SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k],0,5150,"wiresetc_las2","metpat64",0xFF000000);
			}
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,4.5,-0.5,0.0,90.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,4.5,-0.5,0.0,270.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],vehicleid,0.0,4.5+0.24,-0.5,0.0,90.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],vehicleid,0.0,4.5+0.48,-0.5,0.0,90.0,90.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],vehicleid,0.0,4.5+0.72,-0.5,0.0,90.0,90.0);
			ChangeVehicleColor(vehicleid,0,0);
		}
		case 591: {
			//MOC Trailer
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0] = CreateDynamicObject(18848,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1] = CreateDynamicObject(1489,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],1,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],3,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],4,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],5,11631,"mp_ranchcut","mpCJ_Black_metal",0x00000000);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],0,5150,"wiresetc_las2","metpat64",0x00FFFFFF);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0]);
			SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1]);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][0],vehicleid,0.0,0.0,2.13,0.0,0.0,0.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][1],vehicleid,0.0,0.0,7.83,0.0,0.0,90.0);
			
			for(new k = 2; k < 8; k++){
				SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = CreateDynamicObject(3571,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
				SetDynamicObjectNoCameraCol(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
			}
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],vehicleid,-1.346,-2.01,0.4,90.0,0.0,270.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],0,10789,"xenon_sfse","slab64",0xFFAAAAAA);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][2],1,10789,"xenon_sfse","slab64",0xFFAAAAAA);
			
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],vehicleid,1.346,-2.04,0.4,90.0,0.0,90.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],0,10789,"xenon_sfse","slab64",0xFFAAAAAA);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][3],1,10789,"xenon_sfse","slab64",0xFFAAAAAA);
			
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],vehicleid,-1.348,-2.00,1.405,90.0,0.0,270.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],0,10789,"xenon_sfse","slab64",0xFFAAAAAA);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][4],1,10789,"xenon_sfse","slab64",0xFF3B3B3B);
				
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][5],vehicleid,1.348,-2.03,1.405,90.0,0.0,90.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][5],0,10789,"xenon_sfse","slab64",0xFFAAAAAA);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][5],1,10789,"xenon_sfse","slab64",0xFF3B3B3B);
			
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][6],vehicleid,-1.347,2.75,1.4,90.0,0.0,270.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][6],0,10789,"xenon_sfse","slab64",0xFF3B3B3B);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][6],1,10789,"xenon_sfse","slab64",0xFF3B3B3B);
				
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][7],vehicleid,1.347,2.72,1.4,90.0,0.0,90.0);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][7],0,10789,"xenon_sfse","slab64",0xFF3B3B3B);
			SetDynamicObjectMaterial(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][7],1,10789,"xenon_sfse","slab64",0xFF3B3B3B);
			
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][8] = CreateDynamicObject(10149,x,y,z,0.0,0.0,0.0,-1,-1,-1,250.0,250.0);
			AttachDynamicObjectToVehicle(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][8],vehicleid,0.0,-6.08,1.0,0.0,0.0,0.0);
			
			ChangeVehicleColor(vehicleid,0,0);
		}
	}
	return 1;
}

stock SpecialVehicle::DestroyOverlay(vehicleid){
	if(!IsValidVehicle(vehicleid)) return 0;
	for(new k = 0; k < SPECIAL_VEH_MAX_COMPONENTS; k++){
		if(IsValidDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k])){
			DestroyDynamicObject(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k]);
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Object][k] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		}
	}
	if(IsValidDynamic3DTextLabel(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Text])){
		DestroyDynamic3DTextLabel(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Text]);
		SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	return 1;
}

stock SpecialVehicle::Init(){
	new STREAMER_TAG_OBJECT:SpecialVehicle::obj;
	
	SpecialVehicle::TextDrawViewFinderFlare = TextDrawCreate(320.0-8.0,240.0-24.0,"LD_BEAT:cring");
	TextDrawFont(SpecialVehicle::TextDrawViewFinderFlare,4);
	TextDrawColor(SpecialVehicle::TextDrawViewFinderFlare,0xFFFFFF90);
	TextDrawTextSize(SpecialVehicle::TextDrawViewFinderFlare,16.0,16.0);
	
	SpecialVehicle::TextDrawViewFinderGun = TextDrawCreate(320.0-4.0,240.0-20.0,"LD_BEAT:cring");
	TextDrawFont(SpecialVehicle::TextDrawViewFinderGun,4);
	TextDrawColor(SpecialVehicle::TextDrawViewFinderGun,0xCC0000FF);
	TextDrawTextSize(SpecialVehicle::TextDrawViewFinderGun,8.0,8.0);
	
	SpecialVehicle::TextDrawViewFinderRocket = TextDrawCreate(320.0-8.0,240.0-24.0,"LD_BEAT:cring");
	TextDrawFont(SpecialVehicle::TextDrawViewFinderRocket,4);
	TextDrawColor(SpecialVehicle::TextDrawViewFinderRocket,0xCC0000FF);
	TextDrawTextSize(SpecialVehicle::TextDrawViewFinderRocket,16.0,16.0);
	
	TextDrawHideForAll(SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForAll(SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForAll(SpecialVehicle::TextDrawViewFinderRocket);
	
	for(new playerid = 0; playerid < MAX_PLAYERS; playerid++){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
	}
	
	if(Streamer::GetVisibleItems(STREAMER_TYPE_OBJECT,-1) < 1000){
		Streamer::SetVisibleItems(STREAMER_TYPE_OBJECT,1000,-1);
	}
	
	//Andromada Interior by TDI97
	CreateDynamicObject(14548,-1667.25171,-231.57700,15.35910,13.02000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,-1668.71997,-201.21210,11.80350,-8.50000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,-1665.43994,-201.22250,11.80300,-8.50000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

	//AT-400 Interior by TDI97
	CreateDynamicObject(1846,21.39310,-63.56660,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1536,15.31090,-14.05210,535.67151,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19859,15.31130,-65.05510,536.92651,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19786,13.67240,-65.16700,537.60120,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(11728,15.09070,-13.96190,536.71112,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(11728,17.05620,-65.09310,537.05298,0.00000,0.00000,-180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19458,16.74250,-17.24963,538.78070,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,13.57780,-15.33890,535.59802,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,18.55790,-15.33890,535.59802,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,13.57780,-24.83890,535.59851,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,13.57780,-34.33890,535.59802,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,13.57780,-43.83890,535.59851,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,13.57780,-53.21890,535.59802,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,13.57780,-62.83890,535.59851,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,18.55790,-24.84060,535.59851,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,18.55790,-34.34150,535.59802,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,18.55790,-43.84060,535.59851,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,18.55790,-53.34060,535.59802,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19455,18.55790,-62.84060,535.59851,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-15.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-15.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-15.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-15.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-15.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-15.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-15.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-15.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-15.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-15.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-15.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-15.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-17.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-17.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-17.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-17.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-17.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-17.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-17.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-17.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-17.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-17.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-17.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-17.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-19.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-19.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-19.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-19.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-19.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-19.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-19.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-19.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-19.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-19.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-19.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-19.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-21.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-21.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-21.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-21.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-21.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-21.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-21.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-21.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-21.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-21.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-21.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-21.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-23.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-23.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-23.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-23.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-23.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-23.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-23.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-23.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-23.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-23.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-23.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-23.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-25.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-25.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-25.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-25.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-25.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-25.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-25.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-25.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-25.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-25.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-25.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-25.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-27.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-27.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-27.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-27.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-27.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-27.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-27.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-27.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-27.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-27.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-27.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-27.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-29.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-29.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-29.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-29.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-29.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-29.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-29.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-29.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-29.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-29.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-29.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-29.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-31.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-31.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-31.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-31.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-31.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-31.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-31.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-31.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-31.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-31.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-31.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-31.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-33.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-33.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-33.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-33.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-33.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-33.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-33.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-33.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-33.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-33.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-33.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-33.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-35.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-35.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-35.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-35.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-35.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-35.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-35.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-35.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-35.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-35.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-35.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-35.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-37.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-37.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-37.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-37.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-37.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-37.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-37.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-37.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-37.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-37.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-37.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-37.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-39.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-39.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-39.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-39.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-39.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-39.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-39.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-39.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-39.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-39.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-39.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-39.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-41.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-41.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-41.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-41.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-41.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-41.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-41.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-41.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-41.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-41.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-41.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-41.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-43.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-43.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-43.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-43.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-43.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-43.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-43.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-43.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-43.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-43.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-43.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-43.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-45.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-45.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-45.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-45.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-45.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-45.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-45.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-45.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-45.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-45.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-45.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-45.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-47.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-47.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-47.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-47.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-47.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-47.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-47.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-47.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-47.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-47.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-47.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-47.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-49.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-49.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-49.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-49.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-49.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-49.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-49.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-49.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-49.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-49.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-49.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-49.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-51.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-51.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-51.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-51.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-51.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-51.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-51.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-51.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-51.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-51.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-51.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-51.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-53.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-53.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-53.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-53.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-53.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-53.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-53.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-53.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-53.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-53.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-53.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-53.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-55.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-55.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-55.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-55.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-55.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-55.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-55.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-55.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-55.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-55.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-55.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-55.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-57.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-57.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-57.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-57.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-57.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-57.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-57.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-57.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-57.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-57.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-57.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-57.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-59.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-59.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-59.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-59.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-59.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-59.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-59.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-59.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-59.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-59.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-59.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-59.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.90537,-61.77886,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,18.21240,-61.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,17.47740,-61.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.25640,-61.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,13.97040,-61.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1562,14.66340,-61.77890,536.29480,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.90198,-61.41244,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,18.20900,-61.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,17.47400,-61.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,14.66000,-61.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.96700,-61.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1563,13.23200,-61.41240,536.86450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,16.00900,-65.35498,535.58392,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,15.97060,-54.86430,535.58362,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,15.97060,-44.37400,535.58392,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,15.97060,-33.88850,535.58362,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,15.97060,-23.39900,535.58392,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,15.97060,-12.97510,535.58362,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,15.77518,-13.99755,537.21661,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(11711,16.03500,-14.04200,538.38733,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-15.61600,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38500,-18.82250,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-22.02250,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-25.22430,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38500,-28.42500,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-31.62470,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-34.82980,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38500,-38.02960,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-41.20800,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-44.40480,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38500,-47.60500,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-50.80400,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38500,-53.99320,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-57.19310,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38500,-60.37350,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,20.38530,-63.57330,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,15.62767,-65.12579,537.21661,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19786,18.47890,-65.16700,537.58118,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-60.19360,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-57.11130,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-54.20900,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-50.70010,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-47.54080,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-44.42730,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-40.99540,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-37.82090,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-34.65660,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-31.51930,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.37349,-28.38988,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-25.17100,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-22.08220,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39310,-18.65810,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,21.39307,-15.62110,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-63.57330,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-60.37350,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-57.19310,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-53.99320,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-50.80400,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-47.60500,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-44.40480,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-41.20800,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-38.02960,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-34.82980,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-31.62470,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-28.42500,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-25.22430,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-22.02250,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-18.82250,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19404,11.78190,-15.61600,537.21661,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-15.56130,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-18.65810,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-22.08220,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-25.17100,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-28.38990,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-31.51930,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-34.65660,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-37.82090,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-40.99540,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-44.42730,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-47.54080,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-50.70010,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-54.20900,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-57.11130,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-60.19360,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1846,12.72100,-63.56660,537.33008,90.00000,90.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,13.43670,-60.26650,538.50110,0.00000,80.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,15.62770,-65.14580,540.28809,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,13.43670,-50.66440,538.50110,0.00000,80.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,13.43670,-41.04590,538.50110,0.00000,80.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,13.43670,-31.42640,538.50110,0.00000,80.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,13.43670,-21.80940,538.50110,0.00000,80.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,13.43670,-12.20860,538.50110,0.00000,80.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,18.74640,-61.38360,538.50110,0.00000,80.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,18.74640,-51.77640,538.50110,0.00000,80.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,18.74640,-42.15920,538.50110,0.00000,80.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,18.74026,-32.53336,538.50110,0.00000,80.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,18.74640,-22.96340,538.50110,0.00000,80.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19450,18.74640,-13.34660,538.50110,0.00000,80.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19458,16.72010,-26.87510,538.78040,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19458,16.73061,-36.46103,538.78070,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19458,16.57998,-45.54919,538.78040,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19458,16.58102,-55.03631,538.78070,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19458,16.39889,-61.12650,538.78040,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14553,15.84070,-41.09370,526.91742,12.50000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

	//Shamal Interior
	CreateDynamicObject(14404,1891.504150,-4159.505371,3.197141,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.563843,-4159.571777,2.037500,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.538452,-4170.821777,2.037498,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.552856,-4169.589844,2.056684,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.562378,-4168.301270,2.043864,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.554321,-4167.053711,2.050836,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.568481,-4165.810547,2.056400,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14405,1891.559570,-4164.451660,2.065336,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1518,1892.578003,-4158.128906,3.474201,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1518,1890.467773,-4158.104004,3.466745,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(955,1890.441895,-4167.008301,1.850188,0.0000,0.0000,90.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1649,1891.415771,-4153.192383,3.096034,0.0000,0.0000,0.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2406,1890.376221,-4164.333984,4.256859,18.9076,91.9597,91.7189,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2404,1890.386719,-4161.762695,4.292717,15.4699,90.2409,91.6415,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2405,1890.479004,-4159.889160,4.294949,0.8594,91.9597,83.9066,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1742,1889.848511,-4157.031738,1.442635,0.0000,0.0000,90.0000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

	//MOC Interior by TDI97
	CreateDynamicObject(19379,299.89371,1998.91150,16.58248,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,302.87750,1998.85596,18.37080,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,298.30411,1998.86938,18.37080,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(11359,300.57440,1994.05884,18.60050,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19425,300.46420,1999.15955,16.58285,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(14877,302.01886,2000.12390,15.17884,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,300.82800,2005.90747,17.19290,0.00000,90.00000,0.06000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,299.05209,2001.15149,15.53816,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,298.30630,2001.95532,18.37080,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,302.87000,2004.95654,18.37080,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,299.96463,2004.67126,18.37080,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19273,298.36652,1994.98877,18.22260,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19304,298.78659,2001.09644,17.73801,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2180,298.90060,2002.60999,17.22090,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2180,302.28171,2004.08643,17.22090,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19893,298.88843,2002.14575,18.02130,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19820,298.82681,2002.68982,18.00160,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19818,299.02881,2002.57275,18.11610,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2044,298.86499,2001.53625,18.04100,0.00000,0.00000,31.86000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19893,301.87793,2004.14587,18.02130,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1715,301.79489,2002.59155,17.24320,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1778,299.17789,2001.00989,16.67000,0.00000,0.00000,47.88002,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19836,299.39127,2000.02832,16.69060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19836,299.15125,2000.42346,16.69060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19836,298.82007,2000.27637,16.69060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1715,300.42850,2002.08154,17.24320,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18865,302.26648,2003.96155,18.02177,0.00000,0.00000,-37.62003,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2011,298.76215,2000.65332,16.65059,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1665,301.30109,2004.01355,18.04130,0.00000,0.00000,-87.06008,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19897,301.56021,2003.97327,18.04120,0.00000,0.00000,56.28008,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3384,300.33707,2004.64624,17.67468,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3384,299.29279,2004.64392,17.67470,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3388,298.17102,2003.62061,16.65551,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18635,300.35745,2003.91321,17.25657,90.00000,0.00000,-217.61833,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2035,302.76370,2002.32520,18.47230,90.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2035,302.76370,2002.32520,18.75230,90.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2035,302.76370,2002.32520,19.05230,90.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2035,302.76370,2002.32520,18.17230,90.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,299.89371,1998.91150,20.18110,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19379,300.07800,2008.46875,20.16110,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,299.86539,1994.08826,18.37080,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	
	//Cargobob Interior by TDI97
	CreateDynamicObject(3566,1983.65137,-2631.86719,10.08110,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1974.15967,-2631.83496,10.08110,50.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1980.27673,-2634.01611,16.62484,0.00000,150.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1981.22583,-2629.51343,16.62480,0.00000,150.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1982.20557,-2635.79175,13.49230,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1982.20557,-2627.73975,13.49230,0.00000,-90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1979.84387,-2630.34692,13.11470,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1980.76392,-2630.34692,13.11470,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1981.68396,-2630.34692,13.11470,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1984.92261,-2631.72729,8.16980,90.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1981.56592,-2633.06787,12.69945,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1981.22229,-2633.06787,12.69945,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1981.22229,-2633.06787,12.93180,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2358,1980.71362,-2633.08423,12.66190,0.00000,0.00000,-180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2358,1980.71362,-2633.08423,12.88983,0.00000,0.00000,-180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2358,1979.88733,-2633.05811,12.67390,0.00000,0.00000,-180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3015,1979.03442,-2633.05908,12.65787,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18647,1974.03113,-2631.76416,15.05428,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18647,1975.97437,-2631.76416,15.05430,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18647,1977.87402,-2631.76416,15.05430,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18647,1979.79858,-2631.76416,15.05430,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(18647,1981.76538,-2631.76416,15.05430,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

	//SWAT Tank Interior by TDI97
	CreateDynamicObject(3566,1300.17450,1992.66870,1014.16200,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19365,1301.82501,1999.91040,1016.69570,0.00000,30.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19365,1298.64001,1999.92200,1016.69570,0.00000,30.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1301.81000,1997.51208,1017.24430,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1301.81000,1996.72888,1017.24430,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1301.81000,1995.94348,1017.24430,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1298.60641,2002.41663,1017.24430,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1298.60641,2003.18994,1017.24430,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1298.60641,2003.96387,1017.24430,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1298.85614,2003.82581,1017.96290,90.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1301.52319,2003.84583,1017.96290,90.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19365,1301.82501,1999.91040,1018.44559,0.00000,-30.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19365,1298.52414,1999.99255,1018.44560,0.00000,-30.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1300.17450,1994.34058,1021.17700,0.00000,180.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1302.77420,1996.16589,1018.20890,90.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1297.76901,1996.16589,1018.20890,90.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1300.34711,1995.27405,1017.96290,90.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2634,1300.22369,2001.34387,1017.39221,0.00000,180.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2634,1300.26099,1997.63965,1017.39220,0.00000,180.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2690,1300.94739,1998.33533,1016.99495,0.00000,0.00000,-105.35999,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2035,1301.67508,1998.93896,1017.50193,0.00000,-80.00000,-23.76001,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	
	//Rhino Interior by TDI97
	CreateDynamicObject(19737,304.42200,1947.37170,2023.67930,0.00000,90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19737,303.74432,1948.13208,2023.38778,0.00000,90.00000,-15.83990,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19737,304.88800,1948.47913,2023.37763,0.00000,90.00000,-132.17984,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,304.78830,1946.07617,2018.84720,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,301.51370,1948.68616,2018.82720,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,307.33261,1948.42114,2018.86720,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,305.56512,1950.55310,2018.82721,0.00000,90.00000,-32.46000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,303.68640,1950.65637,2018.84720,0.00000,90.00000,24.30000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,306.57080,1948.38745,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,302.17001,1948.37769,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,304.80341,1944.09326,2018.43023,20.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,304.81387,1942.66003,2017.19110,90.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,303.85718,1951.13379,2017.19110,90.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,306.54541,1951.58801,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,302.19000,1951.57654,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,307.29660,1951.12061,2017.19110,90.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,302.18820,1945.19397,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,301.32349,1946.07617,2018.84720,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,308.15469,1946.07617,2018.86720,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,301.33829,1944.09326,2018.43020,20.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,301.34250,1942.66003,2017.19110,90.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,302.17661,1941.99939,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,306.57080,1945.19043,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,306.55081,1942.00281,2017.19110,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19371,304.53128,1947.94739,2020.30515,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19799,303.43921,1947.83508,2020.35790,-90.00000,90.00000,270.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3267,304.35083,1946.38220,2018.34556,0.00000,0.00000,-181.13924,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1278,304.31989,1934.26782,2021.89040,0.00000,80.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1663,305.34329,1944.09009,2016.83030,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2045,304.97339,1943.89490,2016.84740,-90.00000,0.00000,0.12000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2045,305.70221,1943.89490,2016.84740,-90.00000,0.00000,0.12000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,305.34729,1942.95251,2016.08430,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1663,303.37683,1944.14502,2016.83030,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2036,303.35291,1942.95544,2017.10482,90.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,305.35480,1942.91980,2018.48800,0.00000,180.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,303.39502,1942.95142,2018.65051,0.00000,180.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,304.46640,1943.47998,2016.08517,0.00000,0.00000,117.36028,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,306.15631,1943.59497,2016.04540,0.00000,0.00000,263.99954,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,304.44299,1943.47498,2018.48800,0.00000,180.00000,119.22015,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19526,306.15417,1943.59082,2018.48800,0.00000,180.00000,264.17816,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(16641,307.67734,1955.79907,2016.65303,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(16666,300.59299,1945.36292,2013.62920,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1663,303.29550,1946.16199,2016.95030,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3384,306.44589,1946.36267,2017.40450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3384,306.44589,1945.31897,2017.40450,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2061,302.48712,1950.96082,2016.92056,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2061,302.48709,1950.80078,2016.92060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2061,302.48709,1950.64075,2016.92060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2061,302.48709,1950.48071,2016.92060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2061,302.48709,1950.32068,2016.92060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2061,302.48709,1950.16064,2016.92060,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,304.90833,1951.53894,2014.15700,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,301.61960,1951.56860,2014.15810,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,299.33490,1947.68652,2017.10350,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,299.33490,1948.48572,2017.10350,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,299.33490,1949.28564,2017.10350,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,309.45929,1948.19128,2017.10350,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,309.45929,1948.99133,2017.10350,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,309.45929,1949.79126,2017.10350,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

	//Trunk Back Interior by TDI97
	SpecialVehicle::obj = CreateDynamicObject(19357,195.66347,2082.73560,1025.15251,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,194.97340,2082.81079,1023.45691,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,195.12892,2081.20923,1025.15250,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,195.32953,2084.10742,1025.15250,0.00000,0.00000,59.40001,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,195.43709,2082.75928,1025.46044,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,196.72398,2082.68701,1025.15251,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	CreateDynamicObject(2232,195.99791,2083.08911,1024.09868,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1718,196.24303,2083.42310,1025.01550,90.00000,0.00000,-29.04000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19624,195.86745,2083.06030,1025.01366,0.00000,-90.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	
	//Trunk Front Interior by TDI97
	SpecialVehicle::obj = CreateDynamicObject(19357,193.84818,2087.13721,1025.27059,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,193.71053,2087.05054,1024.62036,8.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,193.93849,2085.56763,1025.61930,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,193.74184,2087.22485,1026.36000,-8.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,193.88780,2088.69678,1025.61930,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	SpecialVehicle::obj = CreateDynamicObject(19357,194.40930,2087.02832,1025.27060,0.00000,0.00000,15.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	SetDynamicObjectMaterial(SpecialVehicle::obj,0,10412,"hotel1","carpet_red_256",0);
	CreateDynamicObject(11736,193.96291,2086.65186,1025.78178,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19627,193.93890,2085.87305,1026.05520,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19820,194.02928,2085.74976,1024.54174,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	
	//FBI Truck Interior by TDI97
	CreateDynamicObject(3566,1060.40063,1768.12146,7.33580,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1056.97021,1768.15613,10.89810,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1064.39465,1768.12854,10.89810,0.00000,-90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1060.40063,1768.12146,14.28651,0.00000,180.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1057.03821,1768.15686,10.83689,0.00000,30.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1064.14832,1768.10925,10.83690,0.00000,-30.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3566,1060.26538,1771.98853,14.21685,90.00000,180.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2185,1059.74634,1775.45447,9.79803,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1671,1061.06750,1775.04700,10.21430,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19893,1059.86255,1774.98889,10.60691,0.00000,0.00000,87.18013,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2963,1058.70398,1777.07068,10.88030,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2963,1062.72998,1777.04187,10.74030,0.00000,180.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1059.66943,1775.79712,9.95850,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1059.66943,1775.79712,10.19350,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

	//Trailer Interior by TDI97
	CreateDynamicObject(19446,153.25014,2036.07678,1045.79511,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1967,151.74440,2031.32007,1047.26250,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1965,154.74010,2031.30530,1047.26250,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,154.86005,2032.87256,1047.46740,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,151.65280,2032.92236,1047.46740,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,151.65280,2036.12744,1047.46740,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,151.65280,2039.32166,1047.46740,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,154.86000,2036.06079,1047.46740,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,154.86000,2039.26685,1047.46740,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19357,153.24335,2040.82288,1047.46740,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,153.24651,2038.13672,1042.08070,90.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,153.27278,2042.85034,1046.80652,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1685,153.20795,2039.56335,1047.61069,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1685,152.62318,2033.43359,1046.59566,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1685,152.60909,2035.26697,1046.59566,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1685,152.60585,2034.19897,1047.92680,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19446,153.25014,2036.07678,1048.83146,0.00000,90.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	
	//Nevada Interior by TDI97
	CreateDynamicObject(14404,1386.31763,1770.65576,11.61620,0.00000,0.00000,-90.06000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(9822,1391.23816,1774.76526,10.34795,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3015,1380.11951,1769.29578,9.85995,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2358,1380.84790,1769.30652,9.94953,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2358,1380.84790,1769.30652,10.17623,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2358,1380.84790,1769.30652,10.39939,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1381.16077,1772.04883,9.99860,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1381.16077,1772.04883,10.22993,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(3016,1380.68555,1772.02002,9.98884,0.00000,0.00000,21.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2359,1382.64600,1772.07153,10.03360,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19578,1382.27722,1772.01404,9.95340,0.00000,0.00000,-96.12000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19578,1382.39722,1772.01404,9.95340,0.00000,0.00000,-96.12000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19578,1382.53723,1772.01404,9.95340,0.00000,0.00000,-96.12000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19578,1382.65723,1772.01404,9.95340,0.00000,0.00000,-96.12000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1636,1383.72620,1771.91931,9.93555,0.00000,-40.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1636,1384.04614,1771.91931,9.93560,0.00000,-40.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1636,1384.36609,1771.91931,9.93560,0.00000,-40.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1636,1384.64612,1771.91931,9.93560,0.00000,-40.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2064,1382.37073,1769.78027,10.39533,0.00000,0.00000,91.49997,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19313,1384.81201,1778.28552,9.86620,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19313,1384.81201,1762.93445,9.86620,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19313,1384.81189,1765.92358,15.33595,0.00000,0.00000,90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2180,1386.26050,1769.61194,9.83130,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(321,1386.11877,1769.71545,10.72330,0.00000,110.00000,-80.16003,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19893,1386.76990,1769.62012,10.63860,0.00000,0.00000,180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(1663,1386.74121,1770.63757,10.26174,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2525,1378.90186,1768.10925,9.84060,0.00000,0.00000,-180.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(19873,1387.10278,1769.89368,10.68163,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2524,1379.18054,1769.68628,9.84640,0.00000,0.00000,-90.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);
	CreateDynamicObject(2944,1378.18018,1771.67688,11.26850,0.00000,0.00000,0.00000,-1,SPECIAL_VEH_INTERIOR_ID,-1,100.0);

}

stock SpecialVehicle::Exit(){
	TextDrawDestroy(SpecialVehicle::TextDrawViewFinderGun);
	TextDrawDestroy(SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawDestroy(SpecialVehicle::TextDrawViewFinderRocket);
	Tryg3D::Foreach(playerid){
		if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
			SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
			SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
			AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
			SetCameraBehindPlayer(playerid);
		}
	}
}

//Hook: OnMineDestroy
public OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,Float:radius,damagerid){
	if(SpecialVehicle::Mine[mobid]){
		SpecialVehicle::Mine[mobid] = false;
		Mines::Destroy(mobid);
	}
	#if defined SVEH_OnMineDestroy
		SVEH_OnMineDestroy(mobid,x,y,z,type,killerid,radius,damagerid);
	#endif
	return 1;
}

#if defined _ALS_OnMineDestroy
	#undef OnMineDestroy
#else
	#define _ALS_OnMineDestroy
#endif
#define OnMineDestroy SVEH_OnMineDestroy
#if defined SVEH_OnMineDestroy
	forward SVEH_OnMineDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,Float:radius,damagerid);
#endif

//Hook: OnVehicleSpawn
public OnVehicleSpawn(vehicleid){
	if(!IsValidVehicle(vehicleid)) return 0;
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
		SpecialVehicle::CreateOverlay(vehicleid);
		SetVehicleHealth(vehicleid,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SpawnHealth]);
		if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Included] != INVALID_VEHICLE_ID){
			SpecialVehicle::VehicleData[SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Included]][SpecialVehicle::SeatUsed] = 1;
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnVehicle] = SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Included];
		}
		SpecialVehicle::UpdateText(vehicleid);
	}
	#if defined SVEH_OnVehicleSpawn
		SVEH_OnVehicleSpawn(vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn SVEH_OnVehicleSpawn
#if defined SVEH_OnVehicleSpawn
	forward SVEH_OnVehicleSpawn(vehicleid);
#endif

//Hook: OnVehicleCreated
public OnVehicleCreated(vehicleid){
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
		SpecialVehicle::CreateOverlay(vehicleid);
		SetVehicleHealth(vehicleid,SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SpawnHealth]);
	}
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::SeatUsed] = 0;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnSeat] = SPECIAL_VEH_INVALID_SEAT;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Ammo][0] = SPECIAL_VEH_AMMO_INFINITY;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Ammo][1] = SPECIAL_VEH_AMMO_INFINITY;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TruckID] = INVALID_VEHICLE_ID;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TrailerID] = INVALID_VEHICLE_ID;
	SpecialVehicle::SetDefaultDamage(vehicleid);
	#if defined SVEH_OnVehicleCreated
		SVEH_OnVehicleCreated(vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleCreated
	#undef OnVehicleCreated
#else
	#define _ALS_OnVehicleCreated
#endif
#define OnVehicleCreated SVEH_OnVehicleCreated
#if defined SVEH_OnVehicleCreated
	forward SVEH_OnVehicleCreated(vehicleid);
#endif

//Hook: OnVehicleDeath
public OnVehicleDeath(vehicleid,killerid){
	new vid = SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnVehicle];
	if(vid != INVALID_VEHICLE_ID && SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Included] != vid){
		switch(GetVehicleModel(vid)){
			case 592: {
				if(IsVehicleFlag(GetVehicleFlags(vehicleid),VF_BIKES) || IsVehicleFlag(GetVehicleFlags(vehicleid),VF_RC)){
					SpecialVehicle::SetValueBit(SpecialVehicle::VehicleData[vid][SpecialVehicle::SeatUsed],SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnSeat],0b0);
				} else if(IsVehicleFlag(GetVehicleFlags(vehicleid),VF_STREET) && !SpecialVehicle::AndromadaVehToBig(vehicleid)){
					SpecialVehicle::SetCellValue(SpecialVehicle::VehicleData[vid][SpecialVehicle::SeatUsed],SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnSeat],4,0b0000);
				}
			}
			case 591: {
				SpecialVehicle::VehicleData[vid][SpecialVehicle::SeatUsed] = 0;
			}
		}
	}
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
		Tryg3D::Foreach(playerid){
			if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] == vehicleid){
				SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
				SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
				Tryg3D::GivePlayerDamage(playerid,100000.0,killerid,WEAPON_VEHICLE_INTERIOR,3);
			}
		}
		for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
			if(SpecialVehicle::VehicleData[i][SpecialVehicle::OnVehicle] == vehicleid){
				Tryg3D::Foreach(playerid){
					if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] == i){
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
						Tryg3D::GivePlayerDamage(playerid,100000.0,killerid,WEAPON_VEHICLE_INTERIOR,3);
					}
				}
				if(SpecialVehicle::VehicleData[i][SpecialVehicle::Included] != vehicleid){
					SpecialVehicle::VehicleData[i][SpecialVehicle::OnVehicle] = INVALID_VEHICLE_ID;
					SpecialVehicle::VehicleData[i][SpecialVehicle::OnSeat] = SPECIAL_VEH_INVALID_SEAT;
					SetVehicleToRespawn(i);
				}
			}
		}
		switch(GetVehicleModel(vehicleid)){
			case 528, 595: {
				Mines::Update(mobid){
					if(SpecialVehicle::Mine[mobid] && SpecialVehicle::MineBy[mobid] == vehicleid){
						SpecialVehicle::Mine[mobid] = false;
						SpecialVehicle::MineBy[mobid] = INVALID_VEHICLE_ID;
						Mines::Destroy(mobid);
					}
				}
			}
		}
	}
	#if defined SVEH_OnVehicleDeath
		SVEH_OnVehicleDeath(vehicleid,killerid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath SVEH_OnVehicleDeath
#if defined SVEH_OnVehicleDeath
	forward SVEH_OnVehicleDeath(vehicleid,killerid);
#endif

//Hook: OnVehicleDestroyed
public OnVehicleDestroyed(vehicleid){
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
		SpecialVehicle::DestroyOverlay(vehicleid);
		Tryg3D::Foreach(playerid){
			if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] == vehicleid){
				SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
				SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
				Tryg3D::GivePlayerDamage(playerid,100000.0,INVALID_PLAYER_ID,WEAPON_VEHICLE_INTERIOR,3);
			}
		}
		for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
			if(SpecialVehicle::VehicleData[i][SpecialVehicle::OnVehicle] == vehicleid){
				Tryg3D::Foreach(playerid){
					if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] == i){
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
						Tryg3D::GivePlayerDamage(playerid,100000.0,INVALID_PLAYER_ID,WEAPON_VEHICLE_INTERIOR,3);
					}
				}
				SetVehicleToRespawn(i);
			}
		}
	}
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TruckID] = INVALID_VEHICLE_ID;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TrailerID] = INVALID_VEHICLE_ID;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Included] = INVALID_VEHICLE_ID;
	SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Locked] = false;
	#if defined SVEH_OnVehicleDestroyed
		SVEH_OnVehicleDestroyed(vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleDestroyed
	#undef OnVehicleDestroyed
#else
	#define _ALS_OnVehicleDestroyed
#endif
#define OnVehicleDestroyed SVEH_OnVehicleDestroyed
#if defined SVEH_OnVehicleDestroyed
	forward SVEH_OnVehicleDestroyed(vehicleid);
#endif

//Hook: OnTrailerHooked
public OnTrailerHooked(playerid,vehicleid,trailerid){
	if(GetVehicleModel(vehicleid) == 515){
		if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay] || SpecialVehicle::VehicleData[trailerid][SpecialVehicle::Overlay]){
			if(SpecialVehicle::VehicleData[trailerid][SpecialVehicle::TruckID] != vehicleid || SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::TrailerID] != trailerid){
				DetachTrailerFromVehicle(vehicleid);
				CallLocalFunction("OnSpecialTrailerAttachFail","ddd",playerid,vehicleid,trailerid);
			}
		}
	}
	#if defined SVEH_OnTrailerHooked
		SVEH_OnTrailerHooked(playerid,vehicleid,trailerid);
	#endif
	return 1;
}

#if defined _ALS_OnTrailerHooked
	#undef OnTrailerHooked
#else
	#define _ALS_OnTrailerHooked
#endif
#define OnTrailerHooked SVEH_OnTrailerHooked
#if defined SVEH_OnTrailerHooked
	forward SVEH_OnTrailerHooked(playerid,vehicleid,trailerid);
#endif

//Hook: OnTrailerUnhooked
public OnTrailerUnhooked(playerid,vehicleid,trailerid){
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay] && SpecialVehicle::VehicleData[trailerid][SpecialVehicle::Overlay]){
		Tryg3D::Foreach(i){
			if(IsPlayerInAnyVehicle(i)){
				if(GetPlayerVehicleID(i) == vehicleid && GetPlayerVehicleSeat(i) == 1){
					if(SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon]){
						SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon] = false;
						SpecialVehicle::PlayerData[i][SpecialVehicle::AutoShot] = false;
						AttachCameraToDynamicObject(i,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
						SetCameraBehindPlayer(i);
						TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderGun);
						TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderFlare);
						TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderRocket);
					}
				}
			}
		}
	}
	#if defined SVEH_OnTrailerUnhooked
		SVEH_OnTrailerUnhooked(playerid,vehicleid,trailerid);
	#endif
	return 1;
}

#if defined _ALS_OnTrailerUnhooked
	#undef OnTrailerUnhooked
#else
	#define _ALS_OnTrailerUnhooked
#endif
#define OnTrailerUnhooked SVEH_OnTrailerUnhooked
#if defined SVEH_OnTrailerUnhooked
	forward SVEH_OnTrailerUnhooked(playerid,vehicleid,trailerid);
#endif

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid,weaponid,STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z){
	new T3D:vehicleid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_ATTACHED_VEHICLE);
	if(IsValidVehicle(T3D:vehicleid)){
		if(SpecialVehicle::VehicleData[T3D:vehicleid][SpecialVehicle::Overlay]){
			switch(GetVehicleModel(T3D:vehicleid)){
				case 515, 591: {
					new Float:T3D:HP[2],Float:T3D:health, T3D:trailerid;
					if(EVF::IsTrailer(T3D:vehicleid)){
						T3D:trailerid = T3D:vehicleid;
						T3D:vehicleid = SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::TruckID];
					} else {
						T3D:trailerid = SpecialVehicle::VehicleData[T3D:vehicleid][SpecialVehicle::TrailerID];
					}
					T3D:HP[0] = T3D:HP[1] = 0.0;
					if(IsValidVehicle(T3D:vehicleid)) GetVehicleHealth(T3D:vehicleid,T3D:HP[0]);
					if(IsValidVehicle(T3D:trailerid)) GetVehicleHealth(T3D:trailerid,T3D:HP[1]);
					if(T3D:HP[0] > T3D:HP[1]){
						T3D:health = (T3D:HP[0]-Tryg3D::GetWeaponDamage(weaponid));
					} else {
						T3D:health = (T3D:HP[1]-Tryg3D::GetWeaponDamage(weaponid));
					}
					if(IsValidVehicle(T3D:vehicleid)){
						if(T3D:health > 249.0){
							SetVehicleHealth(T3D:vehicleid,NLTZF(T3D:health));
						} else {
							CallLocalFunction("OnVehicleDeath","dd",T3D:vehicleid,playerid);
							SetVehicleToRespawn(T3D:vehicleid);
						}
					}
					if(IsValidVehicle(T3D:trailerid)){
						if(T3D:health > 249.0){
							SetVehicleHealth(T3D:trailerid,NLTZF(T3D:health));
						} else {	
							CallLocalFunction("OnVehicleDeath","dd",T3D:trailerid,playerid);
							SetVehicleToRespawn(T3D:trailerid);
						}
					}
				}
			}
		}
	}
	#if defined SVEH_OnShootDynamicObject
		SVEH_OnShootDynamicObject(playerid,weaponid,objectid,x,y,z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject SVEH_OnShootDynamicObject
#if defined SVEH_OnShootDynamicObject
	forward SVEH_OnShootDynamicObject(playerid,weaponid,STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z);
#endif

//Hook: OnPlayerWeaponShot
public OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ){
	if(hittype == BULLET_HIT_TYPE_VEHICLE){
		new T3D:vehicleid = hitid;
		if(IsValidVehicle(T3D:vehicleid)){
			if(SpecialVehicle::VehicleData[T3D:vehicleid][SpecialVehicle::Overlay]){
				switch(GetVehicleModel(T3D:vehicleid)){
					case 515, 591: {
						new Float:T3D:HP[2],Float:T3D:health, T3D:trailerid;
						if(EVF::IsTrailer(T3D:vehicleid)){
							T3D:trailerid = T3D:vehicleid;
							T3D:vehicleid = SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::TruckID];
						} else {
							T3D:trailerid = SpecialVehicle::VehicleData[T3D:vehicleid][SpecialVehicle::TrailerID];
						}
						T3D:HP[0] = T3D:HP[1] = 0.0;
						if(IsValidVehicle(T3D:vehicleid)) GetVehicleHealth(T3D:vehicleid,T3D:HP[0]);
						if(IsValidVehicle(T3D:trailerid)) GetVehicleHealth(T3D:trailerid,T3D:HP[1]);
						if(T3D:HP[0] > T3D:HP[1]){
							T3D:health = (T3D:HP[0]-Tryg3D::GetWeaponDamage(weaponid));
						} else {
							T3D:health = (T3D:HP[1]-Tryg3D::GetWeaponDamage(weaponid));
						}
						if(IsValidVehicle(T3D:vehicleid)){
							if(T3D:health > 249.0){
								SetVehicleHealth(T3D:vehicleid,NLTZF(T3D:health));
							} else {
								CallLocalFunction("OnVehicleDeath","dd",T3D:vehicleid,playerid);
								SetVehicleToRespawn(T3D:vehicleid);
							}
						}
						if(IsValidVehicle(T3D:trailerid)){
							if(T3D:health > 249.0){
								SetVehicleHealth(T3D:trailerid,NLTZF(T3D:health));
							} else {
								CallLocalFunction("OnVehicleDeath","dd",T3D:trailerid,playerid);
								SetVehicleToRespawn(T3D:trailerid);
							}
						}
					}
				}
			}
		}
	}
	#if defined SVEH_OnPlayerWeaponShot
		SVEH_OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,fX,fY,fZ);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot SVEH_OnPlayerWeaponShot
#if defined SVEH_OnPlayerWeaponShot
	forward SVEH_OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ);
#endif

//Hook: OnPlayerUpdate
public OnPlayerUpdate(playerid){
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::VID] = GetPlayerVehicleID(playerid);
		Item::GetOrientationPosCol(SpecialVehicle::PlayerData[playerid][SpecialVehicle::VID],item_vehicle,o_down,6.0,SpecialVehicle::PlayerData[playerid][SpecialVehicle::X],SpecialVehicle::PlayerData[playerid][SpecialVehicle::Y],SpecialVehicle::PlayerData[playerid][SpecialVehicle::Z]);
		SetVehiclePos(SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle],SpecialVehicle::PlayerData[playerid][SpecialVehicle::X],SpecialVehicle::PlayerData[playerid][SpecialVehicle::Y],SpecialVehicle::PlayerData[playerid][SpecialVehicle::Z]);
		GetVehicleZAngle(SpecialVehicle::PlayerData[playerid][SpecialVehicle::VID],SpecialVehicle::PlayerData[playerid][SpecialVehicle::A]);
		SetVehicleZAngle(SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle],SpecialVehicle::PlayerData[playerid][SpecialVehicle::A]);
	}
	
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		if(IsPlayerInAnyVehicle(playerid)){
			new Float:rz,Float:z_angle, vid = GetPlayerVehicleID(playerid);
			if(IsValidVehicle(vid)){
				GetVehicleZAngle(vid,rz);
				GetPlayerCameraZAngle(playerid,z_angle);
				switch(GetVehicleModel(vid)){
					case 470: {
						Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz+90.0));
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 200){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									GetPointInFront2D(F5[T3D:X],F5[T3D:Y],rz,-0.5,F5[T3D:X],F5[T3D:Y]);
									GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
									F5[T3D:Z] += 2.1;
									GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
									PlayerPlaySound(playerid,1135,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									Missile::Launch(MISSILE_TYPE_EXPLODE_NONE,2.0,2.0,20.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,MISSILE_OBJECT_BULLET,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 592: {
						for(new k = 0; k < 8; k++){
							Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][k],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz));
						}
					}
					case 504: {
						Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz+90.0));
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 200){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									GetPointInFront2D(F5[T3D:X],F5[T3D:Y],rz,-0.5,F5[T3D:X],F5[T3D:Y]);
									GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
									F5[T3D:Z] += 1.9;
									GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
									MovePointColCutLine(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],5.0);
									PlayerPlaySound(playerid,1135,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									Missile::Launch(MISSILE_TYPE_EXPLODE_NONE,2.0,2.0,20.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,MISSILE_OBJECT_BULLET,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 528: {
						Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz+90.0));
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 200){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									GetPointInFront2D(F5[T3D:X],F5[T3D:Y],rz,-1.1,F5[T3D:X],F5[T3D:Y]);
									GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
									F5[T3D:Z] += 2.1;
									GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
									PlayerPlaySound(playerid,1135,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									Missile::Launch(MISSILE_TYPE_EXPLODE_NONE,2.0,2.0,20.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,MISSILE_OBJECT_BULLET,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 595: {
						Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz+90.0));
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 300){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									GetPointInFront2D(F5[T3D:X],F5[T3D:Y],rz,3.5,F5[T3D:X],F5[T3D:Y]);
									GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
									F5[T3D:Z] += 2.1;
									GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
									PlayerPlaySound(playerid,1135,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									Missile::Launch(MISSILE_TYPE_EXPLODE_SMALL,5.0,10.0,35.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,MISSILE_OBJECT_BULLET,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 601: {
						Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz));
					}
					case 515: {
						new T3D:trailerid = GetVehicleTrailer(vid);
						if(IsValidVehicle(T3D:trailerid)){
							GetVehicleZAngle(T3D:trailerid,rz);
							Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz));
						}
					}
					case 487, 497: {
						switch(GetPlayerVehicleSeat(playerid)){
							case 2: {
								Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][2],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz+90.0));	
							}
							case 3: {
								Streamer::SetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][0],E_STREAMER_ATTACH_R_Z,Tryg3D::CompressRotation(z_angle-rz+90.0));
							}
						}
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 200){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetPlayerCameraPos(playerid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
									GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
									PlayerPlaySound(playerid,1135,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									Missile::Launch(MISSILE_TYPE_EXPLODE_NONE,2.0,2.0,20.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,MISSILE_OBJECT_BULLET,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
				}
			}
		}
	}
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo]){
		new Float:vx,Float:vy,Float:vz,vid = GetPlayerVehicleID(playerid);
		GetVehiclePos(vid,vx,vy,vz);
		if(vz < 400.0){
			new tmp_keys,up_down_key,left_right_key,Float:z_angle;
			GetPlayerKeys(playerid,tmp_keys,up_down_key,left_right_key);
			switch(left_right_key){
				case KEY_LEFT: {
					GetVehicleZAngle(vid,z_angle);
					SetVehicleZAngle(vid,z_angle+5.0);
				}
				case KEY_RIGHT: {
					GetVehicleZAngle(vid,z_angle);
					SetVehicleZAngle(vid,z_angle-5.0);
				}
			}
			SetVehicleSpeed(vid,NMTVF(GetVehicleSpeed(vid)+5.0,100.0));
		}
	}
	#if defined SVEH_OnPlayerUpdate
		SVEH_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate SVEH_OnPlayerUpdate
#if defined SVEH_OnPlayerUpdate
	forward SVEH_OnPlayerUpdate(playerid);
#endif

//Hook: OnPlayerStateChange
public OnPlayerStateChange(playerid,newstate,oldstate){
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_PASSENGER){
		new vehicleid = GetPlayerVehicleID(playerid);
		if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
			if(GetPlayerInterior(playerid) == 0){
				switch(GetPlayerVehicleSeat(playerid)){
					case 1: {
						switch(GetVehicleModel(vehicleid)){
							case 470, 504, 528, 578, 601, 515, 592: {
								CallLocalFunction("OnPlayerEnterSpecialSeat","d",playerid);
							}
						}
					}
					case 2, 3: {
						switch(GetVehicleModel(vehicleid)){
							case 487, 497: {
								if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Minigun]){
									CallLocalFunction("OnPlayerEnterSpecialSeat","d",playerid);
								}	
							}
						}
					}
				}
			}
		}
	} else if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);
		if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
			if(GetPlayerInterior(playerid) == 0){
				switch(GetVehicleModel(vehicleid)){
					case 522: {
						SetPlayerArmedWeapon(playerid,0);
						CallLocalFunction("OnPlayerEnterOppressor","d",playerid);
					}
					case 595: {
						CallLocalFunction("OnPlayerEnterSpecialSeat","d",playerid);
					}
				}
			}
		}
	}
	#if defined SVEH_OnPlayerStateChange
		SVEH_OnPlayerStateChange(playerid,newstate,oldstate);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange SVEH_OnPlayerStateChange
#if defined SVEH_OnPlayerStateChange
	forward SVEH_OnPlayerStateChange(playerid,newstate,oldstate);
#endif

//Hook: OnPlayerEnterVehicle
public OnPlayerEnterVehicle(playerid,vehicleid,ispassenger){
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] != INVALID_VEHICLE_ID){
		if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnVehicle] != GetPlayerVirtualWorld(playerid)){
			SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::OnVehicle] = INVALID_VEHICLE_ID;
			SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
		}
		switch(SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType]){
			case SPECIAL_VEH_TYPE_ANDROMADA, SPECIAL_VEH_TYPE_MOC_TRAILER: {
				SwitchVehicleEngine(vehicleid,false);
			}
		}
	}
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
		AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
		SetCameraBehindPlayer(playerid);
	}
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	#if defined SVEH_OnPlayerEnterVehicle
		SVEH_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle SVEH_OnPlayerEnterVehicle
#if defined SVEH_OnPlayerEnterVehicle
	forward SVEH_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger);
#endif

//Hook: OnMissileDestroy
public OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid){
	if(byplayerid != INVALID_PLAYER_ID){
		if(IsPlayerInAnyVehicle(byplayerid) && GetPlayerVehicleSeat(byplayerid) == 0){
			new vid = GetPlayerVehicleID(byplayerid);
			if(GetVehicleModel(vid) == 504){
				Grenade::CreateGrenadeEffect(GRENADE_SPECIAL_WEAPON_GRENADE,GRENADE_EFFECT_BANG_GRENADE,x,y,z,GetPlayerVirtualWorld(byplayerid),GetPlayerInterior(byplayerid),-1,300.0,0.0,0.0,25,byplayerid);
			}
		}
	}
	#if defined SVEH_OnMissileDestroy
		SVEH_OnMissileDestroy(mobid,x,y,z,type,killerid,byplayerid);
	#endif
	return 1;
}

#if defined _ALS_OnMissileDestroy
	#undef OnMissileDestroy
#else
	#define _ALS_OnMissileDestroy
#endif
#define OnMissileDestroy SVEH_OnMissileDestroy
#if defined SVEH_OnMissileDestroy
	forward SVEH_OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid);
#endif

//Hook: OnPlayerExitVehicle
public OnPlayerExitVehicle(playerid,vehicleid){
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
		AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
		SetCameraBehindPlayer(playerid);
	}
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
	if(SpecialVehicle::VehicleData[vehicleid][SpecialVehicle::Overlay]){
		if(GetVehicleModel(vehicleid) == 592){
			Tryg3D::Foreach(i){
				if(i != playerid){
					if(GetPlayerVehicleID(i) == vehicleid){
						if(SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon]){
							TextDrawHideForPlayer(i,SpecialVehicle::TextDrawViewFinderRocket);
							SpecialVehicle::PlayerData[i][SpecialVehicle::IsUseCannon] = false;
							SpecialVehicle::PlayerData[i][SpecialVehicle::AutoShot] = false;
							AttachCameraToDynamicObject(i,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
							SetCameraBehindPlayer(i);
						}
						break;
					}
				}
			}
		}
	}
	#if defined SVEH_OnPlayerExitVehicle
		SVEH_OnPlayerExitVehicle(playerid,vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle SVEH_OnPlayerExitVehicle
#if defined SVEH_OnPlayerExitVehicle
	forward SVEH_OnPlayerExitVehicle(playerid,vehicleid);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid, killerid, reason){
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
		AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
		SetCameraBehindPlayer(playerid);
	}
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
	#if defined SVEH_OnPlayerDeath
		SVEH_OnPlayerDeath(playerid, killerid, reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath SVEH_OnPlayerDeath
#if defined SVEH_OnPlayerDeath
	forward SVEH_OnPlayerDeath(playerid, killerid, reason);
#endif

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(Tryg3D::KeyPressed(KEY_CTRL_BACK)){
		if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] != INVALID_VEHICLE_ID){
			if(!IsPlayerInAnyVehicle(playerid)){
				SpecialVehicle::ExitPlayer(playerid);
			}
		}
	}
	if(Tryg3D::KeyPressed(KEY_CROUCH)){
		if(IsPlayerInAnyVehicle(playerid)){
			if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] != INVALID_VEHICLE_ID && GetPlayerVehicleSeat(playerid) == 0){
				return SpecialVehicle::ExitPlayer(playerid);
			}
			new vid = GetPlayerVehicleID(playerid);
			if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
				switch(GetVehicleModel(vid)){
					case 595: {
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
							TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
							AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
							SetCameraBehindPlayer(playerid);
						} else {
							if(GetPlayerInterior(playerid) == 0){
								SetPlayerArmedWeapon(playerid,0);
								TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
								AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][1]);
							} else {
								CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
							}
						}
					}
					case 487, 497: {
						if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Minigun]){
							if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
								TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
								AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
								SetCameraBehindPlayer(playerid);
							} else {
								switch(GetPlayerVehicleSeat(playerid)){
									case 2: {
										if(GetPlayerInterior(playerid) == 0){
											SetPlayerArmedWeapon(playerid,0);
											TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
											SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
											AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][3]);
										} else {
											CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
										}
									}
									case 3: {
										if(GetPlayerInterior(playerid) == 0){
											SetPlayerArmedWeapon(playerid,0);
											TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
											SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
											AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][1]);
										} else {
											CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
										}
									}
								}
							}
						}
					}
					case 470, 504, 528: {
						if(GetPlayerVehicleSeat(playerid) == 1){
							if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
								TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
								AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
								SetCameraBehindPlayer(playerid);
							} else {
								if(GetPlayerInterior(playerid) == 0){
									SetPlayerArmedWeapon(playerid,0);
									TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
									AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][1]);
								} else {
									CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
								}
							}
						}
					}
					case 592: {
						if(GetPlayerVehicleSeat(playerid) == 1){
							if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
								TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
								AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
								SetCameraBehindPlayer(playerid);
							} else {
								if(IsVehicleOccupied(vid)){
									if(GetPlayerInterior(playerid) == 0){
										SetPlayerArmedWeapon(playerid,0);
										TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
										SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
										AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][8]);
									} else {
										CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
									}
								} else {
									CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
								}
							}
						}
					}
					case 601: {
						if(GetPlayerVehicleSeat(playerid) == 1){
							if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
								TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
								AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
								SetCameraBehindPlayer(playerid);
							} else {
								if(GetPlayerInterior(playerid) == 0){
									SetPlayerArmedWeapon(playerid,0);
									TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
									AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][1]);
								} else {
									CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
								}
							}
						}
					}
					case 578: {
						if(GetPlayerVehicleSeat(playerid) == 1){
							if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
								TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
								AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
								SetCameraBehindPlayer(playerid);
							} else {
								if(GetPlayerInterior(playerid) == 0){
									SetPlayerArmedWeapon(playerid,0);
									TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
									AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][1]);
								} else {
									CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
								}
							}
						}
					}
					case 515: {
						if(GetPlayerVehicleSeat(playerid) == 1){
							new T3D:trailerid = GetVehicleTrailer(vid);
							if(IsValidVehicle(T3D:trailerid)){
								if(SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Overlay]){
									if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
										TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
										SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
										SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
										AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
										SetCameraBehindPlayer(playerid);
									} else {
										if(GetPlayerInterior(playerid) == 0){
											SetPlayerArmedWeapon(playerid,0);
											TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
											SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = true;
											AttachCameraToDynamicObject(playerid,SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Object][1]);
										} else {
											CallLocalFunction("OnPlayerUseCannonFail","d",playerid);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(Tryg3D::KeyPressed(KEY_ACTION)){
		new vid = GetPlayerVehicleID(playerid);
		if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
			if(GetPlayerVehicleSeat(playerid) == 0){
				switch(GetVehicleModel(vid)){
					case 522: {
						SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = true;
						TextDrawShowForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
					}
					case 548, 417: {
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet]){
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
						} else {
							new F5[Float3D], Float:T3D:ldist = 20000, Float:T3D:dist, LockTarget = INVALID_VEHICLE_ID, Float:px, Float:py, Float:pz;
							GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
							F5[T3D:VW] = GetPlayerVirtualWorld(playerid);
							F5[T3D:INT] = GetPlayerInterior(playerid);
							GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],8.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
							for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
								if(i != vid){
									if(IsVehicleFlag(GetVehicleFlags(i),VF_STREET) && GetVehicleModel(i) != 515){
										GetVehiclePos(i,px,py,pz);
										if(GetVehicleVirtualWorld(i) == F5[T3D:VW] && GetVehicleInterior(i) == F5[T3D:INT]){
											if(Area::PointInCylinder3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],10.0)){
												if((T3D:dist = GetDistanceBetweenPoints3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z])) < T3D:ldist){
													T3D:ldist = T3D:dist;
													LockTarget = i;
												}
											}
										}
									}
								}
							}
							if(LockTarget != INVALID_VEHICLE_ID){
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = LockTarget;
								SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = true;
							}
						}
					}
				}
			}
			
		}
	}
	if(Tryg3D::KeyReleased(KEY_ACTION)){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
		TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	}
	if(Tryg3D::KeyPressed(KEY_FIRE)){
		if(IsPlayerInAnyVehicle(playerid)){
			new vid = GetPlayerVehicleID(playerid);
			if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Overlay]){
				if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
					switch(GetVehicleModel(vid)){
						case 592: {
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 5000){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D],F4[Float3D];
									GetVehiclePos(vid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
									Tryg3D::GetVehicleRotation(vid,F4[T3D:rX],F4[T3D:rY],F4[T3D:rZ]);
									GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
									
									F5[T3D:VW] = GetPlayerVirtualWorld(playerid);
									F5[T3D:INT] = GetPlayerInterior(playerid);
									
									for(new k = 0; k < 8; k++){
										Streamer::GetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][k],E_STREAMER_ATTACH_OFFSET_X,F5[T3D:X]);
										Streamer::GetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][k],E_STREAMER_ATTACH_OFFSET_Y,F5[T3D:Y]);
										Streamer::GetFloatData(STREAMER_TYPE_OBJECT,SpecialVehicle::VehicleData[vid][SpecialVehicle::Object][k],E_STREAMER_ATTACH_OFFSET_Z,F5[T3D:Z]);
										ShiftOffsetToPosition(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:rX],F4[T3D:rY],F4[T3D:rZ],F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
										GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],1200.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
										Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,10.0,20.0,100.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_HYDRA,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									}
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
						case 470, 504, 528, 487, 497, 595: {
							SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = true;
						}
						case 601: {
							if(IsPlayerLookAtSky(playerid)){
								if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 1000){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
										if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
											SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
											SpecialVehicle::UpdateText(vid);
										}
										new F5[Float3D],Float:rz;
										GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
										GetVehicleZAngle(vid,rz);
										GetPointInFront2D(F5[T3D:X],F5[T3D:Y],rz,-1.8,F5[T3D:X],F5[T3D:Y]);
										GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
										F5[T3D:Z] += 6.4;
										
										F5[T3D:VW] = GetPlayerVirtualWorld(playerid);
										F5[T3D:INT] = GetPlayerInterior(playerid);
										
										for(new i = 0; i < 5; i++){
											GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],(i+1)*(10.0),F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
											Missile::Launch(MISSILE_TYPE_EXPLODE_NONE,15.0,0.0,20.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_FLARE_2,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid);
										}
										SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
									} else {
										CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
									}
								}
							} else {
								CallLocalFunction("OnPlayerShootRocketFail","d",playerid);
							}
						}
						case 578: {
							if(IsPlayerLookAtSky(playerid)){
								if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 1000){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
										if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
											SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
											SpecialVehicle::UpdateText(vid);
										}
										new F5[Float3D], Float:T3D:ldist = 20000, Float:T3D:dist, pteam = GetPlayerTeam(playerid), LockTarget = INVALID_PLAYER_ID, Float:px, Float:py, Float:pz;
										GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
										GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
										F5[T3D:Z] += 4.3;
										
										F5[T3D:VW] = GetPlayerVirtualWorld(playerid);
										F5[T3D:INT] = GetPlayerInterior(playerid);
										GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
										
										Tryg3D::Foreach(i){
											if(i != playerid){
												if(pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM){
													if(IsPlayerInAnyVehicle(i) && IsVehicleFlag(GetVehicleFlags(GetPlayerVehicleID(i)),VF_AIRBORNE)){
														GetPlayerPos(i,px,py,pz);
														if(GetPlayerVirtualWorld(i) == F5[T3D:VW] && GetPlayerInterior(i) == F5[T3D:INT]){
															if(Area::PointInCylinder3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],10.0)){
																if((T3D:dist = GetDistanceBetweenPoints3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z])) < T3D:ldist){
																	T3D:ldist = T3D:dist;
																	LockTarget = i;
																}
															}
														}
													}
												}
											}
										}
										if(LockTarget == INVALID_PLAYER_ID){
											GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],800.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
											Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,10.0,20.0,150.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_BIG,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
										} else {
											GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],10.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
											Missile::LaunchAimPlayer(LockTarget,MISSILE_TYPE_EXPLODE_NORMAL,20.0,35.0,150.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_BIG,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
										}
										SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
									} else {
										CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
									}
								}
							}
						}
						case 515: {
							if(IsPlayerLookAtSky(playerid)){
								if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 1000){
									new T3D:trailerid = GetVehicleTrailer(vid);
									if(IsValidVehicle(T3D:trailerid)){
										if(SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
											if(SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
												SpecialVehicle::VehicleData[T3D:trailerid][SpecialVehicle::Ammo][0]--;
												SpecialVehicle::UpdateText(T3D:trailerid);
											}
											new F5[Float3D], Float:rz, Float:T3D:ldist = 20000, Float:T3D:dist, pteam = GetPlayerTeam(playerid), LockTarget = INVALID_PLAYER_ID, Float:px, Float:py, Float:pz;
											GetVehiclePos(T3D:trailerid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
											GetVehicleZAngle(T3D:trailerid,rz);
											GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
											F5[T3D:Z] += 7.83;
											
											F5[T3D:VW] = GetPlayerVirtualWorld(playerid);
											F5[T3D:INT] = GetPlayerInterior(playerid);
											GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
											
											Tryg3D::Foreach(i){
												if(i != playerid){
													if(pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM){
														if(IsPlayerInAnyVehicle(i) && IsVehicleFlag(GetVehicleFlags(GetPlayerVehicleID(i)),VF_AIRBORNE)){
															GetPlayerPos(i,px,py,pz);
															if(GetPlayerVirtualWorld(i) == F5[T3D:VW] && GetPlayerInterior(i) == F5[T3D:INT]){
																if(Area::PointInCylinder3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],10.0)){
																	if((T3D:dist = GetDistanceBetweenPoints3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z])) < T3D:ldist){
																		T3D:ldist = T3D:dist;
																		LockTarget = i;
																	}
																}
															}
														}
													}
												}
											}
											if(LockTarget == INVALID_PLAYER_ID){
												GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],800.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
												Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,10.0,20.0,150.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_BIG,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
											} else {
												GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],10.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
												Missile::LaunchAimPlayer(LockTarget,MISSILE_TYPE_EXPLODE_NORMAL,20.0,35.0,150.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_BIG,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
											}
											SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
										} else {
											CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,T3D:trailerid);
										}
									} else {
										CallLocalFunction("OnSpecialTrailerNotConnected","d",playerid);
									}
								}
							} else {
								CallLocalFunction("OnPlayerShootRocketFail","d",playerid);
							}
						}
					}
				}
				switch(GetVehicleModel(vid)){
					case 528: {
						if(GetPlayerVehicleSeat(playerid) == 0){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 5000){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									new mobid = Mines::Create(MINE_TYPE_EXPLODE_NORMAL,5.0,25.0,5.0,60,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,100.0,MINE_OBJECT_STANDARD,SPECIAL_VEH_TEAM_TYPE,MINE_DETECT_TYPE_ALL,playerid,100.0,2500.0);
									SpecialVehicle::Mine[mobid] = true;
									SpecialVehicle::MineBy[mobid] = vid;
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 595: {
						if(GetPlayerVehicleSeat(playerid) == 0 && !SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 5000){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									Item::GetOrientationPos(vid,item_vehicle,o_back,10.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
									new mobid = Mines::Create(MINE_TYPE_EXPLODE_NORMAL,5.0,25.0,5.0,60,F5[T3D:X],F5[T3D:Y],-0.5,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,100.0,MINE_OBJECT_UNDERWATER,SPECIAL_VEH_TEAM_TYPE,MINE_DETECT_TYPE_ALL,playerid,100.0,2500.0);
									SpecialVehicle::Mine[mobid] = true;
									SpecialVehicle::MineBy[mobid] = vid;
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 522: {
						if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo]){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 2500){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] == SPECIAL_VEH_AMMO_INFINITY){
									if(IsCollisionFlag(Item::GetCollisionFlags(vid,item_vehicle),POSITION_FLAG_AIR)){
										if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0] != SPECIAL_VEH_AMMO_INFINITY){
											SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][0]--;
											SpecialVehicle::UpdateText(vid);
										}
										new F5[Float3D], Float:T3D:ldist = 20000, Float:T3D:dist, pteam = GetPlayerTeam(playerid), LockTarget = INVALID_PLAYER_ID, Float:px, Float:py, Float:pz;
										GetVehiclePos(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
										Tryg3D::GetVehicleRotation(vid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
										F5[T3D:VW] = GetPlayerVirtualWorld(playerid);
										F5[T3D:INT] = GetPlayerInterior(playerid);
										GetPointInFront3DCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],300.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
										Tryg3D::Foreach(i){
											if(i != playerid){
												if(pteam != GetPlayerTeam(i) || GetPlayerTeam(i) == NO_TEAM || pteam == NO_TEAM){
													if(IsPlayerInAnyVehicle(i) && IsCollisionFlag(Item::GetCollisionFlags(GetPlayerVehicleID(i),item_vehicle),POSITION_FLAG_AIR)){
														GetPlayerPos(i,px,py,pz);
														if(GetPlayerVirtualWorld(i) == F5[T3D:VW] && GetPlayerInterior(i) == F5[T3D:INT]){
															if(Area::PointInCylinder3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],10.0)){
																if((T3D:dist = GetDistanceBetweenPoints3D(px,py,pz,F5[T3D:X],F5[T3D:Y],F5[T3D:Z])) < T3D:ldist){
																	T3D:ldist = T3D:dist;
																	LockTarget = i;
																}
															}
														}
													}
												}
											}
										}
										if(LockTarget == INVALID_PLAYER_ID){
											Item::GetOrientationPosCol(vid,item_vehicle,o_front,800.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
											Missile::Launch(MISSILE_TYPE_EXPLODE_SMALL,5.0,10.0,150.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_HYDRA,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
										} else {
											Item::GetOrientationPosCol(vid,item_vehicle,o_front,100.0,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
											Missile::LaunchAimPlayer(LockTarget,MISSILE_TYPE_EXPLODE_NORMAL,20.0,35.0,150.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:VW],F5[T3D:INT],-1,300.0,MISSILE_OBJECT_HYDRA,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
										}
										SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
									} else {
										CallLocalFunction("OnPlayerShootOPRocketFail","d",playerid);
									}
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
					case 504: {
						if(GetPlayerVehicleSeat(playerid) == 0){
							if(GetTickCount()-SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] >= 60000){
								if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] > 0 || SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] == SPECIAL_VEH_AMMO_INFINITY){
									if(SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1] != SPECIAL_VEH_AMMO_INFINITY){
										SpecialVehicle::VehicleData[vid][SpecialVehicle::Ammo][1]--;
										SpecialVehicle::UpdateText(vid);
									}
									new F5[Float3D];
									GetPointInFrontOfVehicle3D(vid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],3.0);
									GetPointInFrontOfVehicle3DCol(vid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],300.0);
									Missile::Launch(MISSILE_TYPE_EXPLODE_SMALL,5.0,10.0,100.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,300.0,MISSILE_OBJECT_HYDRA,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],playerid,SPECIAL_VEH_TEAM_TYPE,.damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::Damage],.vehicle_damage=SpecialVehicle::VehicleData[vid][SpecialVehicle::VehicleDamage]);
									SpecialVehicle::PlayerData[playerid][SpecialVehicle::WeaponTick] = GetTickCount();
								} else {
									CallLocalFunction("OnSpecialVehicleHasNoAmmo","dd",playerid,vid);
								}
							}
						}
					}
				}
			}
		}
	}
	
	if(Tryg3D::KeyReleased(KEY_FIRE)){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
	}
	#if defined SVEH_OnPlayerKeyStateChange
		SVEH_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange SVEH_OnPlayerKeyStateChange
#if defined SVEH_OnPlayerKeyStateChange
	forward SVEH_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
		AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
		SetCameraBehindPlayer(playerid);
	}
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
	#if defined SVEH_OnPlayerConnect
		SVEH_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SVEH_OnPlayerConnect
#if defined SVEH_OnPlayerConnect
	forward SVEH_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
		AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
		SetCameraBehindPlayer(playerid);
	}
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
	#if defined SVEH_OnPlayerDisconnect
		SVEH_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SVEH_OnPlayerDisconnect
#if defined SVEH_OnPlayerDisconnect
	forward SVEH_OnPlayerDisconnect(playerid,reason);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::InVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::VehicleType] = SPECIAL_VEH_TYPE_NONE;
	if(SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon]){
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseCannon] = false;
		SpecialVehicle::PlayerData[playerid][SpecialVehicle::AutoShot] = false;
		AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
		SetCameraBehindPlayer(playerid);
	}
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderGun);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderFlare);
	TextDrawHideForPlayer(playerid,SpecialVehicle::TextDrawViewFinderRocket);
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseMagnet] = false;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::MagnetVehicle] = INVALID_VEHICLE_ID;
	SpecialVehicle::PlayerData[playerid][SpecialVehicle::IsUseTurbo] = false;
	#if defined SVEH_OnPlayerSpawn
		SVEH_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn SVEH_OnPlayerSpawn
#if defined SVEH_OnPlayerSpawn
	forward SVEH_OnPlayerSpawn(playerid);
#endif

new CRC_SpecialVehicleInit = true,
	CRC_SpecialVehicleExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_SpecialVehicleInit){
		CRC_SpecialVehicleInit = false;
		SpecialVehicle::Init();
	}
	#if defined SVEH_OnFilterScriptInit
		SVEH_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SVEH_OnFilterScriptInit
#if defined SVEH_OnFilterScriptInit
	forward SVEH_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_SpecialVehicleInit){
		CRC_SpecialVehicleInit = false;
		SpecialVehicle::Init();
	}
	#if defined SVEH_OnGameModeInit
		SVEH_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SVEH_OnGameModeInit
#if defined SVEH_OnGameModeInit
	forward SVEH_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_SpecialVehicleExit){
		CRC_SpecialVehicleExit = false;
		SpecialVehicle::Exit();
	}
	#if defined SVEH_OnFilterScriptExit
		SVEH_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SVEH_OnFilterScriptExit
#if defined SVEH_OnFilterScriptExit
	forward SVEH_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_SpecialVehicleExit){
		CRC_SpecialVehicleExit = false;
		SpecialVehicle::Exit();
	}
	#if defined SVEH_OnGameModeExit
		SVEH_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit SVEH_OnGameModeExit
#if defined SVEH_OnGameModeExit
	forward SVEH_OnGameModeExit();
#endif
//EOF