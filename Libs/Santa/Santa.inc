/*
 Santa.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg, StreamerFunction

 File Version: 1.4.4
 Streamer Version: 2.9.5
 ColAndreas Version: 1.5.0
 3DTryg Version: 5.3.0
 StreamerFunction Version: 3.0.0

 Functions:
 Santa::SetSpawnRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,bool:reset=true);
 Santa::SetSpawnPolygon(Float:points[],maxpoints=sizeof(points),bool:reset=true);

 Callbacks:
 OnSantaPickupReward(playerid);
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

#if defined _santa_gifts
	#endinput
#endif
#define _santa_gifts

#define Santa::						Santa_

#if !defined MAX_SANTAGIFTS
	#define	MAX_SANTAGIFTS			(100)
#endif

#if !defined REFRESH_SANTAGIFTS
	#define REFRESH_SANTAGIFTS		(2*60*60*1000)	//2 hour
#endif

new STREAMER_TAG_PICKUP:Santa::Pickup[MAX_SANTAGIFTS],
	Float:				Santa::SpawnZoneRectangle[4],
	Float:				Santa::SpawnZonePolygon[MAX_POLYGON_POINTS],
						Santa::SpawnZonePolygonSize,
						Santa::SpawnZoneType,
						Santa::Timer;

#if defined SANTA_IS_EASTER_EVENT
	//Easter
	new SantaPickupModel[][1] = {
		{19341},
		{19342},
		{19343},
		{19344},
		{19345}
	};
#elseif defined SANTA_IS_EASTER_HALLOWEEN
	//Halloween
	new SantaPickupModel[][1] = {
		{19320},	//pumpkin
		{19527},	//cauldron
		{19339}		//coffin
	};
#else
	//Christmas
	new SantaPickupModel[][1] = {
		{19054},
		{19055},
		{19056},
		{19057},
		{19058}
	};
#endif

forward OnSantaPickupReward(playerid);

stock Santa::SetSpawnRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,bool:reset=true){
	Santa::SpawnZoneType = 0;
	Santa::SpawnZoneRectangle[0] = minx;
	Santa::SpawnZoneRectangle[1] = miny;
	Santa::SpawnZoneRectangle[2] = maxx;
	Santa::SpawnZoneRectangle[3] = maxy;
	if(reset) Santa::Reset();
	return 1;
}

stock Santa::SetSpawnPolygon(Float:points[],maxpoints=sizeof(points),bool:reset=true){
	if(maxpoints > MAX_POLYGON_POINTS) return 0;
	Santa::SpawnZoneType = 1;
	for(new i = 0; i < maxpoints; i++) Santa::SpawnZonePolygon[i] = points[i];
	Santa::SpawnZonePolygonSize = maxpoints;
	if(reset) Santa::Reset();
	return 1;
}

stock Santa::RandomCreate(giftid,bool:reset){
	new smodel = random(sizeof(SantaPickupModel)),Float:x,Float:y,Float:z;
	switch(Santa::SpawnZoneType){
		case 0: {
			Random::PointInRectangle(Santa::SpawnZoneRectangle[0],Santa::SpawnZoneRectangle[1],Santa::SpawnZoneRectangle[2],Santa::SpawnZoneRectangle[3],x,y);
			while(IsPointInWater(x,y,0.0)){
				Random::PointInRectangle(Santa::SpawnZoneRectangle[0],Santa::SpawnZoneRectangle[1],Santa::SpawnZoneRectangle[2],Santa::SpawnZoneRectangle[3],x,y);
			}
		}
		case 1: {
			Random::PointInPolygon(Santa::SpawnZonePolygon,x,y,Santa::SpawnZonePolygonSize);
			while(IsPointInWater(x,y,0.0)){
				Random::PointInPolygon(Santa::SpawnZonePolygon,x,y,Santa::SpawnZonePolygonSize);
			}
		}
	}
	ColAndreas::FindZ_For2DCoord(x,y,z);
	if(reset){
		Streamer::SetItemPos(STREAMER_TYPE_PICKUP,Santa::Pickup[giftid],x,y,z+1.0);
		Streamer::SetIntData(STREAMER_TYPE_PICKUP,Santa::Pickup[giftid],E_STREAMER_MODEL_ID,SantaPickupModel[smodel][0]);
	} else {
		Santa::Pickup[giftid] = CreateDynamicPickup(SantaPickupModel[smodel][0],2,x,y,z+1.0,0,0);
	}
	return 1;
}

stock Santa::Init(){
	if(!Tryg3D::IsColAndreasInit()){
		printf("[ADM] Error: Invalid ColAndreas Memory.");
		return 0;
	}
	Santa::SetSpawnRectangle(-3000.0,-3000.0,3000.0,3000.0,false);
	for(new mobid = 0; mobid < MAX_SANTAGIFTS; mobid++) Santa::RandomCreate(mobid,false);
	Santa::Timer = SetTimer("Santa_Reset",REFRESH_SANTAGIFTS,true);
	return 1;
}

T3D:function Santa::Reset(){
	if(!Tryg3D::IsColAndreasInit()){
		printf("[ADM] Error: Invalid ColAndreas Memory.");
		return 0;
	}
	for(new mobid = 0; mobid < MAX_SANTAGIFTS; mobid++) Santa::RandomCreate(mobid,true);
	return 1;
}

new bool:CRC_SantaInit = true,
	bool:CRC_SantaExit = true;

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_SantaInit){
		CRC_SantaInit = false;
		if(!Santa::Init()) printf("[ADM] Error: Failed to init Santa.inc");
	}
	#if defined Santa_OnGameModeInit
		Santa_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Santa_OnGameModeInit
#if defined Santa_OnGameModeInit
	forward Santa_OnGameModeInit();
#endif

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_SantaInit){
		CRC_SantaInit = false;
		if(!Santa::Init()) printf("[ADM] Error: Failed to init Santa.inc");
	}
	#if defined Santa_OnFilterScriptInit
		Santa_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Santa_OnFilterScriptInit
#if defined Santa_OnFilterScriptInit
	forward Santa_OnFilterScriptInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_SantaExit){
		CRC_SantaExit = false;
		KillTimer(Santa::Timer);
	}
	#if defined Santa_OnFilterScriptExit
		Santa_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit Santa_OnFilterScriptExit
#if defined Santa_OnFilterScriptExit
	forward Santa_OnFilterScriptExit();
#endif

//OnPlayerPickUpDynamicPickup
public OnPlayerPickUpDynamicPickup(playerid,STREAMER_TAG_PICKUP:pickupid){
	for(new mobid = 0; mobid < MAX_SANTAGIFTS; mobid++){
		if(pickupid == Santa::Pickup[mobid]){
			Santa::RandomCreate(mobid,true);
			CallLocalFunction("OnSantaPickupReward","d",playerid);
			return 1;
		}
	}
	#if defined Santa_OnPlayerPickUpPickup
		Santa_OnPlayerPickUpPickup(playerid,pickupid);
	#endif
	return 1;
}

#if defined _LS_OnPlayerPickUpDynamicPickup
	#undef OnPlayerPickUpDynamicPickup
#else
	#define _LS_OnPlayerPickUpDynamicPickup
#endif
#define OnPlayerPickUpDynamicPickup Santa_OnPlayerPickUpPickup
#if defined Santa_OnPlayerPickUpPickup
	forward Santa_OnPlayerPickUpPickup(playerid,STREAMER_TAG_PICKUP:pickupid);
#endif
//EOF