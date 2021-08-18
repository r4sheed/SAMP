/*
 StreamerFunction.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: Katarina Calzaghe

 Website: https://adm.ct8.pl

 Plugins: Streamer
 Modules: None

 File Version: 3.0.1
 Streamer Version: 2.9.5

 Compiler Options:
 DISABLE_STREAMER_SPEC_CHECK  //Turn off check streamer version
 ENABLE_BULLET_DYNAMIC_OBJECT //Turn on call OnPlayerWeaponShot when we shoot in a dynamic object
 DISABLE_STREAMER_SPEC_FIXES  //Turn off fixes (not recommended)

 Objects Functions:
 GetDynamicObjectModel(objectid);
 SetDynamicObjectModel(objectid,modelid);
 GetDynamicObjectVW(objectid);
 SetDynamicObjectVW(objectid,worldid);
 GetDynamicObjectINT(objectid);
 SetDynamicObjectINT(objectid,interiorid);
 GetDynamicObjectSD(objectid,&Float:streamdistance);
 SetDynamicObjectSD(objectid,Float:streamdistance);
 GetDynamicObjectDD(objectid,&Float:drawdistance);
 SetDynamicObjectDD(objectid,Float:drawdistance);
 GetDynamicObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);
 SetDynamicObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);
 GetDynamicObjectMoveSpeed(objectid,&Float:speed);
 SetDynamicObjectMoveSpeed(objectid,Float:speed);
 GetDynamicObjectMovePos(objectid,&Float:x,&Float:y,&Float:z);
 GetDynamicObjectMoveRot(objectid,&Float:rx,&Float:ry,&Float:rz);
 GetDynamicObjectMoveTime(objectid,&objstate,&rtime=0);
 SetDynamicObjectAttachSync(objectid,syncrotation);
 RemoveDynamicObjectMaterialAll(objectid);
 DeattachObjectDynamicObject(objectid);
 DeattachDynamicObjectComponent(objectid,type);
 DestroyDynamicObjectComponent(objectid,type);
 GetDynamicObjectArea(objectid);
 SetDynamicObjectArea(objectid,areaid);
 GetDynamicObjectPriority(objectid);
 SetDynamicObjectPriority(objectid,priority);
 GetDynamicObjectDatagram(objectid,data[]);
 SetDynamicObjectDatagram(objectid,data[]);
 RemoveDynamicObjectDatagram(objectid);
 bool:IsSetDynamicObjectDatagram(objectid);
 GetDynamicObjectInvertArea(objectid);
 SetDynamicObjectInvertArea(objectid,toggle);

 SAMP Functions:
 GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz);
 SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);
 CountObjects();
 CountPlayerObjects(playerid,bool:streamer = false);
 DestroyObjects();
 DestroyPlayerObjects(playerid,bool:streamer = false);
 GangZoneDestroyAll();

 Vehicle Functions:
 CountVehicles();
 DestroyVehicles();
 DestroyVehicleDynamicObject(vehicleid);
 DeattachVehicleDynamicObject(vehicleid);
 GetVehicleDatagram(vehicleid,data[]);
 SetVehicleDatagram(vehicleid,data[]);
 RemoveVehicleDatagram(vehicleid);
 IsSetVehicleDatagram(vehicleid);

 Check Point Functions:
 GetDynamicCPPos(checkpointid,&Float:x,&Float:y,&Float:z);
 SetDynamicCPPos(checkpointid,Float:x,Float:y,Float:z);
 GetDynamicCPSize(checkpointid,&Float:size);
 SetDynamicCPSize(checkpointid,Float:size);
 GetDynamicCPVW(checkpointid);
 SetDynamicCPVW(checkpointid,worldid);
 GetDynamicCPINT(checkpointid);
 SetDynamicCPINT(checkpointid,interiorid);
 GetDynamicCPSD(checkpointid,&Float:streamdistance);
 SetDynamicCPSD(checkpointid,Float:streamdistance);
 GetDynamicCPArea(checkpointid);
 SetDynamicCPArea(checkpointid,areaid);
 GetDynamicCPPriority(checkpointid);
 SetDynamicCPPriority(checkpointid,priority);
 GetDynamicCPDatagram(checkpointid,data[]);
 SetDynamicCPDatagram(checkpointid,data[]);
 RemoveDynamicCPDatagram(checkpointid);
 bool:IsSetDynamicCPDatagram(checkpointid);
 GetDynamicCPInvertArea(checkpointid);
 SetDynamicCPInvertArea(checkpointid,toggle);

 Race Check Point Functions:
 GetDynamicRaceCPPos(checkpointid,&Float:x,&Float:y,&Float:z);
 SetDynamicRaceCPPos(checkpointid,Float:x,Float:y,Float:z);
 GetDynamicRaceCPNext(checkpointid,&Float:nextx,&Float:nexty,&Float:nextz);
 SetDynamicRaceCPNext(checkpointid,Float:nextx,Float:nexty,Float:nextz);
 GetDynamicRaceCPType(checkpointid);
 SetDynamicRaceCPType(checkpointid,type);
 GetDynamicRaceCPSize(checkpointid,&Float:size);
 SetDynamicRaceCPSize(checkpointid,Float:size);
 GetDynamicRaceCPVW(checkpointid);
 SetDynamicRaceCPVW(checkpointid,worldid);
 GetDynamicRaceCPINT(checkpointid);
 SetDynamicRaceCPINT(checkpointid,interiorid);
 GetDynamicRaceCPSD(checkpointid,&Float:streamdistance);
 SetDynamicRaceCPSD(checkpointid,Float:streamdistance);
 GetDynamicRaceCPArea(checkpointid);
 SetDynamicRaceCPArea(checkpointid,areaid);
 GetDynamicRaceCPPriority(checkpointid);
 SetDynamicRaceCPPriority(checkpointid,priority);
 GetDynamicRaceCPDatagram(checkpointid,data[]);
 SetDynamicRaceCPDatagram(checkpointid,data[]);
 RemoveDynamicRaceCPDatagram(checkpointid);
 bool:IsSetDynamicRaceCPDatagram(checkpointid);
 GetDynamicRaceCPInvertArea(checkpointid);
 SetDynamicRaceCPInvertArea(checkpointid,toggle);

 Player Functions:
 DestroyPlayerDynamicObject(playerid);
 DeattachPlayerDynamicObject(playerid);

 MapIcon Functions:
 GetDynamicMapIconPos(iconid,&Float:x,&Float:y,&Float:z);
 SetDynamicMapIconPos(iconid,Float:x,Float:y,Float:z);
 GetDynamicMapIconType(iconid);
 SetDynamicMapIconType(iconid,type);
 GetDynamicMapIconStyle(iconid);
 SetDynamicMapIconStyle(iconid,style);
 GetDynamicMapIconVW(iconid);
 SetDynamicMapIconVW(iconid,worldid);
 GetDynamicMapIconINT(iconid);
 SetDynamicMapIconINT(iconid,interiorid);
 GetDynamicMapIconSD(iconid,&Float:streamdistance);
 SetDynamicMapIconSD(iconid,Float:streamdistance);
 SetDynamicMapIconColor(iconid,color);
 GetDynamicMapIconColor(iconid);
 GetDynamicMapIconArea(iconid);
 SetDynamicMapIconArea(iconid,areaid);
 GetDynamicMapIconPriority(iconid);
 SetDynamicMapIconPriority(iconid,priority);
 GetDynamicMapIconDatagram(iconid,data[]);
 SetDynamicMapIconDatagram(iconid,data[]);
 RemoveDynamicMapIconDatagram(iconid);
 bool:IsSetDynamicMapIconDatagram(iconid);
 GetDynamicMapIconInvertArea(iconid);
 SetDynamicMapIconInvertArea(iconid,toggle);

 Pickup Functions:
 GetDynamicPickupPos(pickupid,&Float:x,&Float:y,&Float:z);
 SetDynamicPickupPos(pickupid,Float:x,Float:y,Float:z);
 GetDynamicPickupModel(pickupid);
 SetDynamicPickupModel(pickupid,modelid);
 GetDynamicPickupVW(pickupid);
 SetDynamicPickupVW(pickupid,worldid);
 GetDynamicPickupINT(pickupid);
 SetDynamicPickupINT(pickupid,interiorid);
 GetDynamicPickupSD(pickupid,&Float:streamdistance);
 SetDynamicPickupSD(pickupid,Float:streamdistance);
 GetDynamicPickupType(pickupid);
 SetDynamicPickupType(pickupid,type);
 GetDynamicPickupArea(pickupid);
 SetDynamicPickupArea(pickupid,areaid);
 GetDynamicPickupPriority(pickupid);
 SetDynamicPickupPriority(pickupid,priority);
 GetDynamicPickupDatagram(pickupid,data[]);
 SetDynamicPickupDatagram(pickupid,data[]);
 RemoveDynamicPickupDatagram(pickupid);
 bool:IsSetDynamicPickupDatagram(pickupid);
 GetDynamicPickupInvertArea(pickupid);
 SetDynamicPickupInvertArea(pickupid,toggle);

 3DText Functions:
 GetDynamic3DTextPos(id,&Float:x,&Float:y,&Float:z);
 SetDynamic3DTextPos(id,Float:x,Float:y,Float:z);
 GetDynamic3DTextDD(id,Float:drawdistance);
 SetDynamic3DTextDD(id,Float:drawdistance);
 GetDynamic3DTextSD(id,&Float:streamdistance);
 SetDynamic3DTextSD(id,Float:streamdistance);
 GetDynamic3DTextVW(id);
 SetDynamic3DTextVW(id,worldid);
 GetDynamic3DTextINT(id);
 SetDynamic3DTextINT(id,interiorid);
 GetDynamic3DTextColor(id);
 SetDynamic3DTextColor(id,color);
 GetDynamic3DTextArea(id);
 SetDynamic3DTextArea(id,areaid);
 GetDynamic3DTextPriority(id);
 SetDynamic3DTextPriority(id,priority);
 SetDynamic3DTextTestLos(id,testlos);
 AttachDynamic3DTextToPlayer(id,attachedplayer);
 AttachDynamic3DTextToVehicle(id,attachedvehicle);
 GetDynamic3DTextDatagram(id,data[]);
 SetDynamic3DTextDatagram(id,data[]);
 RemoveDynamic3DTextDatagram(id);
 bool:IsSetDynamic3DTextDatagram(id);
 GetDynamic3DTextInvertArea(id);
 SetDynamic3DTextInvertArea(id,toggle);

 Area Functions:
 GetDynamicCirclePos(areaid,&Float:x,&Float:y);
 SetDynamicCirclePos(areaid,Float:x,Float:y);
 GetDynamicCylinderPos(areaid,&Float:x,&Float:y,&Float:minz,&Float:maxz);
 SetDynamicCylinderPos(areaid,Float:x,Float:y,Float:minz,Float:maxz);
 GetDynamicSpherePos(areaid,&Float:x,&Float:y,&Float:z);
 SetDynamicSpherePos(areaid,Float:x,Float:y,Float:z);
 GetDynamicRectanglePos(areaid,&Float:minx,&Float:miny,&Float:maxx,&Float:maxy);
 SetDynamicRectanglePos(areaid,Float:minx,Float:miny,Float:maxx,Float:maxy);
 GetDynamicCubePos(areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz);
 SetDynamicCubePos(areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);
 GetDynamicCuboidPos(areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz);
 SetDynamicCuboidPos(areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);
 GetDynamicAreaVW(areaid);
 SetDynamicAreaVW(areaid,worldid);
 GetDynamicAreaINT(areaid);
 SetDynamicAreaINT(areaid,interiorid);
 GetDynamicAreaSize(areaid,Float:size);
 SetDynamicAreaSize(areaid,Float:size);
 GetDynamicAreaDatagram(areaid,data[]);
 SetDynamicAreaDatagram(areaid,data[]);
 RemoveDynamicAreaDatagram(areaid);
 bool:IsSetDynamicAreaDatagram(areaid);

 Actor Functions:
 GetDynamicActorModel(actorid);
 SetDynamicActorModel(actorid,modelid);
 GetDynamicActorArea(actorid);
 SetDynamicActorArea(actorid,areaid);
 GetDynamicActorPriority(actorid);
 SetDynamicActorPriority(actorid,priority);
 GetDynamicActorSD(actorid,&Float:streamdistance);
 SetDynamicActorSD(actorid,Float:streamdistance);
 GetDynamicActorDatagram(actorid,data[]);
 SetDynamicActorDatagram(actorid,data[]);
 RemoveDynamicActorDatagram(actorid);
 IsSetDynamicActorDatagram(actorid);
 GetDynamicActorInterior(actorid);
 SetDynamicActorInterior(actorid,interiorid);
 DestroyAllDynamicActors();
 CountDynamicActors();
 GetDynamicActorInvertArea(actorid);
 SetDynamicActorInvertArea(actorid,toggle);

 Dynamic Vehicle Functions:
 SetDynamicVehicleModel(vehicleid,modelid);
 GetDynamicVehicleSiren(vehicleid);
 SetDynamicVehicleSiren(vehicleid,siren);
 GetDynamicVehicleRespawnTime(vehicleid);
 SetDynamicVehicleRespawnTime(vehicleid,respawndelay);
 GetDynamicVehicleArea(vehicleid);
 SetDynamicVehicleArea(vehicleid,areaid);
 GetDynamicVehiclePriority(vehicleid);
 SetDynamicVehiclePriority(vehicleid,priority);
 GetDynamicVehicleSD(vehicleid,&Float:streamdistance);
 SetDynamicVehicleSD(vehicleid,Float:streamdistance);
 GetDynamicVehicleInvertArea(vehicleid);
 SetDynamicVehicleInvertArea(vehicleid,toggle);
 GetDynamicVehicleDatagram(vehicleid,data[]);
 SetDynamicVehicleDatagram(vehicleid,data[]);
 RemoveDynamicVehicleDatagram(vehicleid);
 IsSetDynamicVehicleDatagram(vehicleid);
 DestroyAllDynamicVehicles();
 CountDynamicVehicles();

 Anti Area Functions:
 IsPointInAntiArea(areaid,Float:x,Float:y,Float:z);
 IsPlayerInAntiArea(playerid,areaid,recheck = 0);
 IsPlayerInAnyAntiArea(playerid,recheck = 0);
 IsAnyPlayerInAntiArea(areaid,recheck = 0);
 IsAnyPlayerInAnyAntiArea(recheck = 0);

 Anti Area Callbacks:
 OnPlayerEnterAntiArea(playerid,areaid);
 OnPlayerLeaveAntiArea(playerid,areaid);

 Pool Size Functions:
 GetDynamicObjectPoolSize();
 GetDynamicPickupPoolSize();
 GetDynamicCPPoolSize();
 GetDynamicRaceCPPoolSize();
 GetDynamicMapIconPoolSize();
 GetDynamic3DTextPoolSize();
 GetDynamicAreaPoolSize();
 GetDynamicActorPoolSize();
 GetDynamicVehiclePoolSize();

 Update Functions:
 UpdateAllDynamicItem(type);
 UpdateAllDynamicElements();
 UpdateAllDynamicObjects();
 UpdateAllDynamicPickups();
 UpdateAllDynamicCPs();
 UpdateAllDynamicRaceCPs();
 UpdateAllDynamicMapIcons();
 UpdateAllDynamic3DTextLabels();
 UpdateAllDynamicAreas();
 UpdateAllDynamicActors();
 UpdateAllDynamicVehicles();

 Foreach Functions:
 ForDynamicObjects(variable);
 ForDynamicPickups(variable);
 ForDynamicCPs(variable);
 ForDynamicRaceCPs(variable);
 ForDynamicMapIcons(variable);
 ForDynamic3DTextLabels(variable);
 ForDynamicAreas(variable);
 ForDynamicActors(variable);
 ForDynamicVehicles(variable);

 Nearest Item Functions:
 GetNearestVisibleItem(playerid,type);
 GetNearestVisibleObject(playerid);
 GetNearestVisiblePickup(playerid);
 GetNearestVisibleCP(playerid);
 GetNearestVisibleRaceCP(playerid);
 GetNearestVisibleMapIcon(playerid);
 GetNearestVisible3DText(playerid);
 GetNearestVisibleArea(playerid);
 GetNearestVisibleActor(playerid);
 GetNearestVisibleVehicle(playerid);

 Extended Functions:
 bool:IsValidStreamer(version);
 GetStreamerVersion();
 GetValidStreamerVersion();
 GetStreamerVersionName(name[], value = GET_STREAMER_VERSION, maxdest = sizeof name);
 CheckStreamerVersion();
 GetStreamerDatagram(type,itemid,data[]);
 SetStreamerDatagram(type,itemid,data[]);
 RemoveStreamDatagram(type,itemid);
 bool:IsSetStreamerDatagram(type,itemid);
 GetStreamerSpecActiveCount();

 Definitions:
 DEFAULT_VISIBLE_OBJECT
 DEFAULT_VISIBLE_PICKUP
 DEFAULT_VISIBLE_MAP_ICON
 DEFAULT_VISIBLE_3D_TEXT
 DEFAULT_VISIBLE_ACTOR
 INVALID_DYNAMIC_OBJECT_ID
 INVALID_DYNAMIC_PICKUP_ID
 INVALID_DYNAMIC_CP_ID
 INVALID_DYNAMIC_RACE_CP_ID
 INVALID_DYNAMIC_MAP_ICON_ID
 INVALID_DYNAMIC_3D_TEXT_ID
 INVALID_DYNAMIC_AREA_ID
 INVALID_DYNAMIC_ACTOR_ID
 INVALID_DYNAMIC_VEHICLE_ID
 INVALID_PICKUP_ID
 INVALID_STREAMER_COMPONENT
 MAX_STREAM_SIZE

 Fixes:
 DestroyDynamicObject         -> Resets the variable after the destruction of the DynamicObject.
 DestroyDynamicPickup         -> Resets the variable after the destruction of the DynamicPickup.
 DestroyDynamicCP             -> Resets the variable after the destruction of the DynamicCP.
 DestroyDynamicRaceCP         -> Resets the variable after the destruction of the DynamicRaceCP.
 DestroyDynamicMapIcon        -> Resets the variable after the destruction of the DynamicMapIcon.
 DestroyDynamic3DTextLabel    -> Resets the variable after the destruction of the Dynamic3DTextLabel.
 DestroyDynamicArea           -> Resets the variable after the destruction of the DynamicArea.
 DestroyDynamicActor          -> Resets the variable after the destruction of the DynamicActor.
 DestroyDynamicVehicle        -> Resets the variable after the destruction of the DynamicVehicle.
 DestroyObject                -> Resets the variable after the destruction of the Object.
 DestroyPlayerObject          -> Resets the variable after the destruction of the PlayerObject.
 DestroyPickup                -> Resets the variable after the destruction of the Pickup.
 Delete3DTextLabel            -> Resets the variable after the destruction of the 3DTextLabel.
 DeletePlayer3DTextLabel      -> Resets the variable after the destruction of the Player3DTextLabel.
 AttachDynamicObjectToObject  -> Changes the priority of the parent to be greater than the priority of sub-objects.
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

#if defined _streamer_spec
	#endinput
#endif
#define _streamer_spec

#if defined STREAMER_TYPE_VEHICLE
	#define SSpec_StreamerVehicle
#endif

#define Streamer_Spec_Version 					(30001) //a.b.c 10000*a+100*b+c
#if defined GetPlayerCustomSkin
	#define STREAMER_SPEC_SAMP_VERSION			"0.3 DL"
#else
	#define STREAMER_SPEC_SAMP_VERSION			"0.3.7"
#endif
#define Valid_Streamer_Version 					(0x295)

#if defined INVALID_DYNAMIC_OBJECT_ID
	#if (INVALID_DYNAMIC_OBJECT_ID != INVALID_STREAMER_ID)
		#error [ADM] Invalid DestroyDynamicObject Hook version. Invalid definition INVALID_DYNAMIC_OBJECT_ID
	#endif
	#undef INVALID_DYNAMIC_OBJECT_ID
#endif

#define INVALID_DYNAMIC_OBJECT_ID				STREAMER_TAG_OBJECT:		INVALID_STREAMER_ID
#define INVALID_DYNAMIC_PICKUP_ID				STREAMER_TAG_PICKUP:		INVALID_STREAMER_ID
#define INVALID_DYNAMIC_CP_ID					STREAMER_TAG_CP:			INVALID_STREAMER_ID
#define INVALID_DYNAMIC_RACE_CP_ID				STREAMER_TAG_RACE_CP:		INVALID_STREAMER_ID
#define INVALID_DYNAMIC_MAP_ICON_ID				STREAMER_TAG_MAP_ICON:		INVALID_STREAMER_ID
#define INVALID_DYNAMIC_3D_TEXT_ID				STREAMER_TAG_3D_TEXT_LABEL:	INVALID_STREAMER_ID
#define INVALID_DYNAMIC_AREA_ID					STREAMER_TAG_AREA:			INVALID_STREAMER_ID
#define INVALID_DYNAMIC_ACTOR_ID				STREAMER_TAG_ACTOR:			INVALID_STREAMER_ID

#if defined SSpec_StreamerVehicle
	#define INVALID_DYNAMIC_VEHICLE_ID			STREAMER_TAG_VEHICLE:		INVALID_STREAMER_ID
#endif

#define DEFAULT_VISIBLE_OBJECT					500
#define DEFAULT_VISIBLE_PICKUP					4096
#define DEFAULT_VISIBLE_MAP_ICON				100
#define DEFAULT_VISIBLE_3D_TEXT					1024
#define DEFAULT_VISIBLE_ACTOR					1000

#if defined SSpec_StreamerVehicle
	#define DEFAULT_VISIBLE_VEHICLE				2000
#endif

#if !defined INVALID_PICKUP_ID
	#define INVALID_PICKUP_ID					-1
#endif

#if !defined MAX_STREAM_SIZE
	#define MAX_STREAM_SIZE						256
#endif

#if !defined INVALID_STREAMER_COMPONENT
	#define INVALID_STREAMER_COMPONENT			-1
#endif

#define STREAMEX_VEHICLE						12

#define Streamer::								Streamer_

#if !defined isnull
	#define isnull(%1) 							((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define GET_STREAMER_VERSION					0xFFFFFFFF

#define MOVE_OBJECT_STATE_STOP					0
#define MOVE_OBJECT_STATE_MOVED					1
#define MOVE_OBJECT_STATE_INVALID				2

#define BULLET_HIT_TYPE_DYNAMIC_OBJECT			15

#define GetStreamerVersion()					Streamer::IncludeFileVersion
#define GetValidStreamerVersion()				Valid_Streamer_Version

//DynamicObject
#define GetDynamicObjectModel(%1)				Streamer::GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MODEL_ID)
#define SetDynamicObjectModel(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MODEL_ID,(%2))
#define GetDynamicObjectINT(%1)					Streamer::GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicObjectINT(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicObjectVW(%1)					Streamer::GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicObjectVW(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicObjectSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicObjectSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicObjectDD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define SetDynamicObjectDD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define GetDynamicObjectMoveSpeed(%1,%2) 		Streamer::GetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MOVE_SPEED,(%2))
#define SetDynamicObjectMoveSpeed(%1,%2) 		Streamer::SetFloatData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_MOVE_SPEED,(%2))
#define DeattachObjectDynamicObject(%1)			Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID)
#define SetDynamicObjectAttachSync(%1,%2)		Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_SYNC_ROTATION,(%2))
#define GetDynamicObjectArea(%1)				STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_AREA_ID)
#define SetDynamicObjectArea(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamicObjectPriority(%1)			Streamer::GetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_PRIORITY)
#define SetDynamicObjectPriority(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_OBJECT,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicObjectInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_OBJECT,(%1))
#define SetDynamicObjectInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_OBJECT,(%1),(%2))
#define GetDynamicObjectDatagram(%1,%2)			GetStreamerDatagram(STREAMER_TYPE_OBJECT,(%1),(%2))
#define SetDynamicObjectDatagram(%1,%2)			SetStreamerDatagram(STREAMER_TYPE_OBJECT,(%1),(%2))
#define RemoveDynamicObjectDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_OBJECT,(%1))
#define IsSetDynamicObjectDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_OBJECT,(%1))
#define UpdateAllDynamicObjects() 				UpdateAllDynamicItem(STREAMER_TYPE_OBJECT)

//DynamicPickup
#define GetDynamicPickupModel(%1)				Streamer::GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_MODEL_ID)
#define SetDynamicPickupModel(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_MODEL_ID,(%2))
#define GetDynamicPickupSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicPickupSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicPickupVW(%1)					Streamer::GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicPickupVW(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicPickupINT(%1)					Streamer::GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicPickupINT(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicPickupType(%1)				Streamer::GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_TYPE)
#define SetDynamicPickupType(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_TYPE,(%2))
#define GetDynamicPickupArea(%1)				STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_AREA_ID)
#define SetDynamicPickupArea(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamicPickupPriority(%1)			Streamer::GetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_PRIORITY)
#define SetDynamicPickupPriority(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_PICKUP,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicPickupInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_PICKUP,(%1))
#define SetDynamicPickupInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_PICKUP,(%1),(%2))
#define GetDynamicPickupDatagram(%1,%2)			GetStreamerDatagram(STREAMER_TYPE_PICKUP,(%1),(%2))
#define SetDynamicPickupDatagram(%1,%2)			SetStreamerDatagram(STREAMER_TYPE_PICKUP,(%1),(%2))
#define RemoveDynamicPickupDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_PICKUP,(%1))
#define IsSetDynamicPickupDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_PICKUP,(%1))
#define UpdateAllDynamicPickups()				UpdateAllDynamicItem(STREAMER_TYPE_PICKUP)
#define GetDynamicPickupPos(%0,%1,%2,%3)		Streamer::GetItemPos(STREAMER_TYPE_PICKUP,(%0),(%1),(%2),(%3))
#define SetDynamicPickupPos(%0,%1,%2,%3)		Streamer::SetItemPos(STREAMER_TYPE_PICKUP,(%0),(%1),(%2),(%3))

//DynamicCP
#define GetDynamicCPSize(%1,%2)					Streamer::GetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicCPSize(%1,%2)					Streamer::SetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_SIZE,(%2))
#define GetDynamicCPArea(%1)					STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_AREA_ID)
#define SetDynamicCPArea(%1,%2)					Streamer::SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamicCPPriority(%1)				Streamer::GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_PRIORITY)
#define SetDynamicCPPriority(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicCPSD(%1,%2)					Streamer::GetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicCPSD(%1,%2)					Streamer::SetFloatData(STREAMER_TYPE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicCPVW(%1)						Streamer::GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicCPVW(%1,%2)					Streamer::SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicCPINT(%1)						Streamer::GetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicCPINT(%1,%2)					Streamer::SetIntData(STREAMER_TYPE_CP,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicCPInvertArea(%1)				Streamer::IsToggleItemInvAreas(STREAMER_TYPE_CP,(%1))
#define SetDynamicCPInvertArea(%1,%2)			Streamer::ToggleItemInvAreas(STREAMER_TYPE_CP,(%1),(%2))
#define GetDynamicCPDatagram(%1,%2)				GetStreamerDatagram(STREAMER_TYPE_CP,(%1),(%2))
#define SetDynamicCPDatagram(%1,%2)				SetStreamerDatagram(STREAMER_TYPE_CP,(%1),(%2))
#define RemoveDynamicCPDatagram(%1)				RemoveStreamDatagram(STREAMER_TYPE_CP,(%1))
#define IsSetDynamicCPDatagram(%1)				IsSetStreamerDatagram(STREAMER_TYPE_CP,(%1))
#define UpdateAllDynamicCPs()					UpdateAllDynamicItem(STREAMER_TYPE_CP)
#define GetDynamicCPPos(%0,%1,%2,%3)			Streamer::GetItemPos(STREAMER_TYPE_CP,(%0),(%1),(%2),(%3))
#define SetDynamicCPPos(%0,%1,%2,%3)			Streamer::SetItemPos(STREAMER_TYPE_CP,(%0),(%1),(%2),(%3))

//DynamicRaceCP
#define GetDynamicRaceCPSize(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicRaceCPSize(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_SIZE,(%2))
#define GetDynamicRaceCPArea(%1)				STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_AREA_ID)
#define SetDynamicRaceCPArea(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamicRaceCPPriority(%1)			Streamer::GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_PRIORITY)
#define SetDynamicRaceCPPriority(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicRaceCPSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicRaceCPSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicRaceCPType(%1)				Streamer::GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_TYPE)
#define SetDynamicRaceCPType(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_TYPE,(%2))
#define GetDynamicRaceCPVW(%1)					Streamer::GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicRaceCPVW(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicRaceCPINT(%1)					Streamer::GetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicRaceCPINT(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_RACE_CP,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicRaceCPInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_RACE_CP,(%1))
#define SetDynamicRaceCPInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_RACE_CP,(%1),(%2))
#define GetDynamicRaceCPDatagram(%1,%2)			GetStreamerDatagram(STREAMER_TYPE_RACE_CP,(%1),(%2))
#define SetDynamicRaceCPDatagram(%1,%2)			SetStreamerDatagram(STREAMER_TYPE_RACE_CP,(%1),(%2))
#define RemoveDynamicRaceCPDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_RACE_CP,(%1))
#define IsSetDynamicRaceCPDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_RACE_CP,(%1))
#define UpdateAllDynamicRaceCPs()				UpdateAllDynamicItem(STREAMER_TYPE_RACE_CP)
#define GetDynamicRaceCPPos(%0,%1,%2,%3)		Streamer::GetItemPos(STREAMER_TYPE_RACE_CP,(%0),(%1),(%2),(%3))
#define SetDynamicRaceCPPos(%0,%1,%2,%3)		Streamer::SetItemPos(STREAMER_TYPE_RACE_CP,(%0),(%1),(%2),(%3))

//DynamicMapIcon
#define GetDynamicMapIconColor(%1)				Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_COLOR)
#define SetDynamicMapIconColor(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_COLOR,(%2))
#define GetDynamicMapIconArea(%1)				STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_AREA_ID)
#define SetDynamicMapIconArea(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamicMapIconPriority(%1)			Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_PRIORITY)
#define SetDynamicMapIconPriority(%1,%2)		Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicMapIconSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicMapIconSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicMapIconType(%1)				Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_TYPE)
#define SetDynamicMapIconType(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_TYPE,(%2))
#define GetDynamicMapIconVW(%1)					Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicMapIconVW(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicMapIconINT(%1)				Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicMapIconINT(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicMapIconStyle(%1)				Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STYLE)
#define SetDynamicMapIconStyle(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,(%1),E_STREAMER_STYLE,(%2))
#define GetDynamicMapIconDatagram(%1,%2)		GetStreamerDatagram(STREAMER_TYPE_MAP_ICON,(%1),(%2))
#define SetDynamicMapIconDatagram(%1,%2)		SetStreamerDatagram(STREAMER_TYPE_MAP_ICON,(%1),(%2))
#define GetDynamicMapIconInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_MAP_ICON,(%1))
#define SetDynamicMapIconInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_MAP_ICON,(%1),(%2))
#define RemoveDynamicMapIconDatagram(%1)		RemoveStreamDatagram(STREAMER_TYPE_MAP_ICON,(%1))
#define IsSetDynamicMapIconDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_MAP_ICON,(%1))
#define UpdateAllDynamicMapIcons()				UpdateAllDynamicItem(STREAMER_TYPE_MAP_ICON)
#define GetDynamicMapIconPos(%0,%1,%2,%3)		Streamer::GetItemPos(STREAMER_TYPE_MAP_ICON,(%0),(%1),(%2),(%3))
#define SetDynamicMapIconPos(%0,%1,%2,%3)		Streamer::SetItemPos(STREAMER_TYPE_MAP_ICON,(%0),(%1),(%2),(%3))

//Dynamic3DText
#define GetDynamic3DTextDD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define SetDynamic3DTextDD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_DRAW_DISTANCE,(%2))
#define GetDynamic3DTextSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamic3DTextSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamic3DTextVW(%1)					Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_WORLD_ID)
#define SetDynamic3DTextVW(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamic3DTextINT(%1)					Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamic3DTextINT(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamic3DTextColor(%1)				Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_COLOR)
#define SetDynamic3DTextColor(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_COLOR,(%2))
#define SetDynamic3DTextTestLos(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_TEST_LOS,(%2))
#define AttachDynamic3DTextToPlayer(%1,%2)		Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_ATTACHED_PLAYER,(%2))
#define AttachDynamic3DTextToVehicle(%1,%2)		Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_ATTACHED_VEHICLE,(%2))
#define GetDynamic3DTextArea(%1)				STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_AREA_ID)
#define SetDynamic3DTextArea(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamic3DTextPriority(%1)			Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_PRIORITY)
#define SetDynamic3DTextPriority(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamic3DTextInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_3D_TEXT_LABEL,(%1))
#define SetDynamic3DTextInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_3D_TEXT_LABEL,(%1),(%2))
#define GetDynamic3DTextDatagram(%1,%2)			GetStreamerDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1),(%2))
#define SetDynamic3DTextDatagram(%1,%2)			SetStreamerDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1),(%2))
#define RemoveDynamic3DTextDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1))
#define IsSetDynamic3DTextDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_3D_TEXT_LABEL,(_:%1))
#define UpdateAllDynamic3DTextLabels()			UpdateAllDynamicItem(STREAMER_TYPE_3D_TEXT_LABEL)
#define GetDynamic3DTextPos(%0,%1,%2,%3)		Streamer::GetItemPos(STREAMER_TYPE_3D_TEXT_LABEL,(%0),(%1),(%2),(%3))
#define SetDynamic3DTextPos(%0,%1,%2,%3)		Streamer::SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL,(%0),(%1),(%2),(%3))

//DynamicArea
#define GetDynamicAreaVW(%1)					Streamer::GetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_WORLD_ID)
#define SetDynamicAreaVW(%1,%2)					Streamer::SetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_WORLD_ID,(%2))
#define GetDynamicAreaINT(%1)					Streamer::GetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicAreaINT(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_AREA,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicAreaSize(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_AREA,(%1),E_STREAMER_SIZE,(%2))
#define SetDynamicAreaSize(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_AREA,(%1),E_STREAMER_SIZE,(%2))
#define GetDynamicAreaDatagram(%1,%2)			GetStreamerDatagram(STREAMER_TYPE_AREA,(%1),(%2))
#define SetDynamicAreaDatagram(%1,%2)			SetStreamerDatagram(STREAMER_TYPE_AREA,(%1),(%2))
#define RemoveDynamicAreaDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_AREA,(%1))
#define IsSetDynamicAreaDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_AREA,(%1))
#define UpdateAllDynamicAreas()					UpdateAllDynamicItem(STREAMER_TYPE_AREA)
#define GetDynamicSpherePos(%0,%1,%2,%3)		Streamer::GetItemPos(STREAMER_TYPE_AREA,(%0),(%1),(%2),(%3))
#define SetDynamicSpherePos(%0,%1,%2,%3)		Streamer::SetItemPos(STREAMER_TYPE_AREA,(%0),(%1),(%2),(%3))

//DynamicActor
#define GetDynamicActorModel(%1)				Streamer::GetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_MODEL_ID)
#define SetDynamicActorModel(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_MODEL_ID,(%2))
#define GetDynamicActorInterior(%1)				Streamer::GetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_INTERIOR_ID)
#define SetDynamicActorInterior(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_INTERIOR_ID,(%2))
#define GetDynamicActorArea(%1)					STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_AREA_ID)
#define SetDynamicActorArea(%1,%2)				Streamer::SetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_AREA_ID,(_:%2))
#define GetDynamicActorPriority(%1)				Streamer::GetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_PRIORITY)
#define SetDynamicActorPriority(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_PRIORITY,(%2))
#define GetDynamicActorSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define SetDynamicActorSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_ACTOR,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
#define GetDynamicActorInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_ACTOR,(%1))
#define SetDynamicActorInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_ACTOR,(%1),(%2))
#define GetDynamicActorDatagram(%1,%2)			GetStreamerDatagram(STREAMER_TYPE_ACTOR,(%1),(%2))
#define SetDynamicActorDatagram(%1,%2)			SetStreamerDatagram(STREAMER_TYPE_ACTOR,(%1),(%2))
#define RemoveDynamicActorDatagram(%1)			RemoveStreamDatagram(STREAMER_TYPE_ACTOR,(%1))
#define IsSetDynamicActorDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_ACTOR,(%1))
#define DestroyAllDynamicActors()				Streamer::DestroyAllItems(STREAMER_TYPE_ACTOR,1)
#define CountDynamicActors()					Streamer::CountItems(STREAMER_TYPE_ACTOR,1)
#define UpdateAllDynamicActors()				UpdateAllDynamicItem(STREAMER_TYPE_ACTOR)

//DynamicVehicle
#if defined SSpec_StreamerVehicle

	#define SetDynamicVehicleModel(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_MODEL_ID,(%2))
	#define GetDynamicVehicleSiren(%1)				Streamer::GetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_SIREN)
	#define SetDynamicVehicleSiren(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_SIREN,(%2))
	#define GetDynamicVehicleRespawnTime(%1)		Streamer::GetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_RESPAWN_TIME)
	#define SetDynamicVehicleRespawnTime(%1,%2)		Streamer::SetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_RESPAWN_TIME,(%2))
	#define GetDynamicVehicleArea(%1)				STREAMER_TAG_AREA:Streamer::GetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_AREA_ID)
	#define SetDynamicVehicleArea(%1,%2)			Streamer::SetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_AREA_ID,(_:%2))
	#define GetDynamicVehiclePriority(%1)			Streamer::GetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_PRIORITY)
	#define SetDynamicVehiclePriority(%1,%2)		Streamer::SetIntData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_PRIORITY,(%2))
	#define GetDynamicVehicleSD(%1,%2)				Streamer::GetFloatData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
	#define SetDynamicVehicleSD(%1,%2)				Streamer::SetFloatData(STREAMER_TYPE_VEHICLE,(%1),E_STREAMER_STREAM_DISTANCE,(%2))
	#define GetDynamicVehicleInvertArea(%1)			Streamer::IsToggleItemInvAreas(STREAMER_TYPE_VEHICLE,(%1))
	#define SetDynamicVehicleInvertArea(%1,%2)		Streamer::ToggleItemInvAreas(STREAMER_TYPE_VEHICLE,(%1),(%2))
	#define GetDynamicVehicleDatagram(%1,%2)		GetStreamerDatagram(STREAMER_TYPE_VEHICLE,(%1),(%2))
	#define SetDynamicVehicleDatagram(%1,%2)		SetStreamerDatagram(STREAMER_TYPE_VEHICLE,(%1),(%2))
	#define RemoveDynamicVehicleDatagram(%1)		RemoveStreamDatagram(STREAMER_TYPE_VEHICLE,(%1))
	#define IsSetDynamicVehicleDatagram(%1)			IsSetStreamerDatagram(STREAMER_TYPE_VEHICLE,(%1))
	#define DestroyAllDynamicVehicles()				Streamer::DestroyAllItems(STREAMER_TYPE_VEHICLE,1)
	#define CountDynamicVehicles()					Streamer::CountItems(STREAMER_TYPE_VEHICLE,1)

	#define GetDynamicVehiclePoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_VEHICLE)
	#define ForDynamicVehicles(%1)					for(new STREAMER_TAG_VEHICLE:%1 = STREAMER_TAG_VEHICLE:1, STREAMER_TAG_VEHICLE:p_%1 = STREAMER_TAG_VEHICLE:GetDynamicVehiclePoolSize(); _:%1 <= _:p_%1; STREAMER_TAG_VEHICLE:((_:%1)+=1))
	#define GetNearestVisibleVehicle(%0)			GetNearestVisibleItem((%0),STREAMER_TYPE_VEHICLE)
	
	#define UpdateAllDynamicVehicles()				UpdateAllDynamicItem(STREAMER_TYPE_VEHICLE)
	
#endif

//DynamicAntiArea
#define IsPlayerInAntiArea(%0,%1,%2)			(!IsPlayerInDynamicArea(%0,%1,%2))
#define IsPlayerInAnyAntiArea(%0,%1)			(!IsPlayerInAnyDynamicArea(%0,%1))
#define IsAnyPlayerInAntiArea(%0,%1)			(!IsAnyPlayerInDynamicArea(%0,%1))
#define IsAnyPlayerInAnyAntiArea(%0)			(!IsAnyPlayerInAnyDynamicArea(%0))
#define IsPointInAntiArea(%0,%1,%2,%3)			(!IsPointInDynamicArea(%0,%1,%2,%3))

//Vehicle
#define GetVehicleDatagram(%1,%2)				GetStreamerDatagram(STREAMEX_VEHICLE,(%1),(%2))
#define SetVehicleDatagram(%1,%2)				SetStreamerDatagram(STREAMEX_VEHICLE,(%1),(%2))
#define RemoveVehicleDatagram(%1)				RemoveStreamDatagram(STREAMEX_VEHICLE,(%1))
#define IsSetVehicleDatagram(%1)				IsSetStreamerDatagram(STREAMEX_VEHICLE,(%1))

//PoolSize
#define GetDynamicObjectPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_OBJECT)
#define GetDynamicPickupPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_PICKUP)
#define GetDynamicCPPoolSize()					Streamer::GetUpperBound(STREAMER_TYPE_CP)
#define GetDynamicRaceCPPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_RACE_CP)
#define GetDynamicMapIconPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_MAP_ICON)
#define GetDynamic3DTextPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL)
#define GetDynamicAreaPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_AREA)
#define GetDynamicActorPoolSize()				Streamer::GetUpperBound(STREAMER_TYPE_ACTOR)

//Foreach
#define ForDynamicObjects(%1)					for(new STREAMER_TAG_OBJECT:		%1 = STREAMER_TAG_OBJECT:		1, STREAMER_TAG_OBJECT:			p_%1 = STREAMER_TAG_OBJECT:			GetDynamicObjectPoolSize();		_:%1 <= _:p_%1; STREAMER_TAG_OBJECT:		((_:%1)+=1))
#define ForDynamicPickups(%1)					for(new STREAMER_TAG_PICKUP:		%1 = STREAMER_TAG_PICKUP:		1, STREAMER_TAG_PICKUP:			p_%1 = STREAMER_TAG_PICKUP:			GetDynamicPickupPoolSize();		_:%1 <= _:p_%1; STREAMER_TAG_PICKUP:		((_:%1)+=1))
#define ForDynamicCPs(%1)						for(new STREAMER_TAG_CP:			%1 = STREAMER_TAG_CP:			1, STREAMER_TAG_CP:				p_%1 = STREAMER_TAG_CP:				GetDynamicCPPoolSize();			_:%1 <= _:p_%1; STREAMER_TAG_CP:			((_:%1)+=1))
#define ForDynamicRaceCPs(%1)					for(new STREAMER_TAG_RACE_CP:		%1 = STREAMER_TAG_RACE_CP:		1, STREAMER_TAG_RACE_CP:		p_%1 = STREAMER_TAG_RACE_CP:		GetDynamicRaceCPPoolSize();		_:%1 <= _:p_%1; STREAMER_TAG_RACE_CP:		((_:%1)+=1))
#define ForDynamicMapIcons(%1)					for(new STREAMER_TAG_MAP_ICON:		%1 = STREAMER_TAG_MAP_ICON:		1, STREAMER_TAG_MAP_ICON:		p_%1 = STREAMER_TAG_MAP_ICON:		GetDynamicMapIconPoolSize();	_:%1 <= _:p_%1; STREAMER_TAG_MAP_ICON:		((_:%1)+=1))
#define ForDynamic3DTextLabels(%1)				for(new STREAMER_TAG_3D_TEXT_LABEL:	%1 = STREAMER_TAG_3D_TEXT_LABEL:1, STREAMER_TAG_3D_TEXT_LABEL:	p_%1 = STREAMER_TAG_3D_TEXT_LABEL:	GetDynamic3DTextPoolSize(); 	_:%1 <= _:p_%1; STREAMER_TAG_3D_TEXT_LABEL:	((_:%1)+=1))
#define ForDynamicAreas(%1)						for(new STREAMER_TAG_AREA:			%1 = STREAMER_TAG_AREA:			1, STREAMER_TAG_AREA:			p_%1 = STREAMER_TAG_AREA:			GetDynamicAreaPoolSize();		_:%1 <= _:p_%1; STREAMER_TAG_AREA:			((_:%1)+=1))
#define ForDynamicActors(%1)					for(new STREAMER_TAG_ACTOR:			%1 = STREAMER_TAG_ACTOR:		1, STREAMER_TAG_ACTOR:			p_%1 = STREAMER_TAG_ACTOR:			GetDynamicActorPoolSize();		_:%1 <= _:p_%1; STREAMER_TAG_ACTOR:			((_:%1)+=1))

//GetNearestVisibleItem
#define GetNearestVisibleObject(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_OBJECT)
#define GetNearestVisiblePickup(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_PICKUP)
#define GetNearestVisibleCP(%0)					GetNearestVisibleItem((%0),STREAMER_TYPE_CP)
#define GetNearestVisibleRaceCP(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_RACE_CP)
#define GetNearestVisibleMapIcon(%0)			GetNearestVisibleItem((%0),STREAMER_TYPE_MAP_ICON)
#define GetNearestVisible3DText(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_3D_TEXT_LABEL)
#define GetNearestVisibleArea(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_AREA)
#define GetNearestVisibleActor(%0)				GetNearestVisibleItem((%0),STREAMER_TYPE_ACTOR)

//Internal
#define GetStreamerSpecActiveCount() 			GetSVarInt("ADM:StreamerSpec:ACTIVE")

//extra names
#define SetDynamic3DTextAttachPlayer			AttachDynamic3DTextToPlayer
#define SetDynamic3DTextAttachVehicle			AttachDynamic3DTextToVehicle

//Datagram
stock GetStreamerDatagram(type,STREAMER_ALL_TAGS:itemid,data[]){
	new address[32];
	format(address,sizeof(address),"Stream:%d:%d",type,_:itemid);
	GetSVarString(address,data,MAX_STREAM_SIZE);
}

stock SetStreamerDatagram(type,STREAMER_ALL_TAGS:itemid,const data[]){
	new address[32];
	format(address,sizeof(address),"Stream:%d:%d",type,_:itemid);
	SetSVarString(address,data);
}

stock RemoveStreamDatagram(type,STREAMER_ALL_TAGS:itemid){
	new address[32];
	format(address,sizeof(address),"Stream:%d:%d",type,_:itemid);
	DeleteSVar(address);
}

stock bool:IsSetStreamerDatagram(type,STREAMER_ALL_TAGS:itemid){
	new stream_data[MAX_STREAM_SIZE];
	GetStreamerDatagram(type,_:itemid,stream_data);
	if(isnull(stream_data)) return false;
	return true;
}

stock bool:IsValidStreamer(version){
	return (GetStreamerVersion() == version);
}

stock GetStreamerVersionName(name[], value = GET_STREAMER_VERSION, maxdest = sizeof name){
	if(value == GET_STREAMER_VERSION) value = GetStreamerVersion();
	new ver_str[10];
	format(ver_str,sizeof(ver_str),"%03x",value);
	format(name,maxdest,"%d.%d.%d",(ver_str[0]-48),(ver_str[1]-48),(ver_str[2]-48));
}

stock SetDynamicObjectPosAndRot(STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	SetDynamicObjectPos(objectid,x,y,z);
	SetDynamicObjectRot(objectid,rx,ry,rz);
}

stock GetDynamicObjectPosAndRot(STREAMER_TAG_OBJECT:objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	GetDynamicObjectPos(objectid,x,y,z);
	GetDynamicObjectRot(objectid,rx,ry,rz);
}

stock SetObjectPosAndRot(objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz){
	SetObjectPos(objectid,x,y,z);
	SetObjectRot(objectid,rx,ry,rz);
}

stock GetObjectPosAndRot(objectid,&Float:x,&Float:y,&Float:z,&Float:rx,&Float:ry,&Float:rz){
	GetObjectPos(objectid,x,y,z);
	GetObjectRot(objectid,rx,ry,rz);
}

stock CountObjects(){
	new count = 0;
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(IsValidObject(i)) count++;
	}
	return count;
}

stock DestroyObjects(){
	new count = 0;
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(IsValidObject(i)){
			DestroyObject(i);
			count++;
		}
	}
	return count;
}

stock CountVehicles(){
	new count = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		if(IsValidVehicle(i)) count++;
	}
	return count;
}

stock DestroyVehicles(){
	new count = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		if(IsValidVehicle(i)){
			DestroyVehicle(i);
			count++;
		}
	}
	return count;
}

stock GangZoneDestroyAll(){
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		GangZoneDestroy(i);
	}
}

stock CountPlayerObjects(playerid,bool:streamer = false){
	new count = 0;
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				count++;
			}
		} else {
			if(Streamer::GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					count++;
				}
			}
		}
	}
	return count;
}

stock DestroyPlayerObjects(playerid,bool:streamer = false){
	new count = 0;
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(streamer){
			if(IsValidPlayerObject(playerid,i)){
				DestroyPlayerObject(playerid,i);
				count++;
			}
		} else {
			if(Streamer::GetItemStreamerID(playerid,STREAMER_TYPE_OBJECT,i) == INVALID_STREAMER_ID){
				if(IsValidPlayerObject(playerid,i)){
					DestroyPlayerObject(playerid,i);
					count++;
				}
			}
		}
	}
	return count;
}

stock DestroyVehicleDynamicObject(vehicleid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				DestroyDynamicObject(i);
				count++;
			}
		}
	}
	return count;
}

stock DeattachVehicleDynamicObject(vehicleid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE) == vehicleid){
				Streamer::SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_VEHICLE,INVALID_VEHICLE_ID);
				count++;
			}
		}
	}
	return count;
}

stock DeattachPlayerDynamicObject(playerid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				Streamer::SetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER,INVALID_PLAYER_ID);
				count++;
			}
		}
	}
	return count;
}

stock DestroyPlayerDynamicObject(playerid){
	new count = 0;
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_ATTACHED_PLAYER) == playerid){
				DestroyDynamicObject(i);
				count++;
			}
		}
	}
	return count;
}

stock GetDynamicRaceCPNext(STREAMER_TAG_RACE_CP:checkpointid,&Float:nextx,&Float:nexty,&Float:nextz){
	Streamer::GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_X,nextx);
	Streamer::GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Y,nexty);
	Streamer::GetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Z,nextz);
}

stock SetDynamicRaceCPNext(STREAMER_TAG_RACE_CP:checkpointid,Float:nextx,Float:nexty,Float:nextz){
	Streamer::SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_X,nextx);
	Streamer::SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Y,nexty);
	Streamer::SetFloatData(STREAMER_TYPE_RACE_CP,checkpointid,E_STREAMER_NEXT_Z,nextz);
}

stock GetDynamicObjectMovePos(STREAMER_TAG_OBJECT:objectid,&Float:x,&Float:y,&Float:z){
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,x);
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,y);
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,z);
}

stock GetDynamicObjectMoveRot(STREAMER_TAG_OBJECT:objectid,&Float:rx,&Float:ry,&Float:rz){
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_X,rx);
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Y,ry);
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_R_Z,rz);
}

stock GetDynamicCirclePos(STREAMER_TAG_AREA:areaid,&Float:x,&Float:y){
	new Float:z;
	Streamer::GetItemPos(STREAMER_TYPE_AREA,areaid,x,y,z);
}

stock SetDynamicCirclePos(STREAMER_TAG_AREA:areaid,Float:x,Float:y){
	new Float:z;
	Streamer::SetItemPos(STREAMER_TYPE_AREA,areaid,x,y,z);
}

stock GetDynamicCylinderPos(STREAMER_TAG_AREA:areaid,&Float:x,&Float:y,&Float:minz,&Float:maxz){
	new Float:z;
	Streamer::GetItemPos(STREAMER_TYPE_AREA,areaid,x,y,z);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock SetDynamicCylinderPos(STREAMER_TAG_AREA:areaid,Float:x,Float:y,Float:minz,Float:maxz){
	new Float:z;
	Streamer::SetItemPos(STREAMER_TYPE_AREA,areaid,x,y,z);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock GetDynamicCubePos(STREAMER_TAG_AREA:areaid,&Float:minx,&Float:miny,&Float:minz,&Float:maxx,&Float:maxy,&Float:maxz){
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock SetDynamicCubePos(STREAMER_TAG_AREA:areaid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
}

stock GetDynamicRectanglePos(STREAMER_TAG_AREA:areaid,&Float:minx,&Float:miny,&Float:maxx,&Float:maxy){
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
}

stock SetDynamicRectanglePos(STREAMER_TAG_AREA:areaid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
	Streamer::SetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
}

stock DestroyDynamicObjectComponent(STREAMER_TAG_OBJECT:objectid,type){
	new count = 0;
	switch(type){
		case STREAMER_TYPE_OBJECT: {
			ForDynamicObjects(i){
				if(Streamer::GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == _:objectid){
					DestroyDynamicObject(i);
					count++;
				}
			}
		}
		case STREAMER_TYPE_AREA: {
			ForDynamicAreas(i){
				if(Streamer::GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == _:objectid){
					DestroyDynamicArea(i);
					count++;
				}
			}
		}
		default: return INVALID_STREAMER_COMPONENT;
	}
	return count;
}

stock DeattachDynamicObjectComponent(STREAMER_TAG_OBJECT:objectid,type){
	new count = 0;
	switch(type){
		case STREAMER_TYPE_OBJECT: {
			ForDynamicObjects(i){
				if(Streamer::GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == _:objectid){
					Streamer::SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_STREAMER_ID);
					count++;
				}
			}
		}
		case STREAMER_TYPE_AREA: {
			ForDynamicAreas(i){
				if(Streamer::GetIntData(type,i,E_STREAMER_ATTACHED_OBJECT) == _:objectid){
					Streamer::SetIntData(type,i,E_STREAMER_ATTACHED_OBJECT,INVALID_VEHICLE_ID);
					count++;
				}
			}
		}
		default: return INVALID_STREAMER_COMPONENT;
	}
	return count;
}

stock GetDynamicObjectMoveTime(STREAMER_TAG_OBJECT:objectid,&objstate,&rtime=0){
	if(!IsValidDynamicObject(objectid)){
		objstate = MOVE_OBJECT_STATE_INVALID;
		rtime = 0;
		return rtime;
	} else if(IsDynamicObjectMoving(objectid)){
		new Float:piox,Float:pioy,Float:pioz,Float:piotx,Float:pioty,Float:piotz,Float:objspeed;
		GetDynamicObjectPos(objectid,piox,pioy,pioz);
		GetDynamicObjectMovePos(objectid,piotx,pioty,piotz);
		GetDynamicObjectMoveSpeed(objectid,objspeed);
		rtime = floatround((VectorSize(piox-piotx,pioy-pioty,pioz-piotz)/objspeed)*1000.0);
		objstate = MOVE_OBJECT_STATE_MOVED;
		return rtime;
	} else {
		objstate = MOVE_OBJECT_STATE_STOP;
		rtime = 0;
		return rtime;
	}
}

stock UpdateAllDynamicItem(type){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++) Streamer::Update(i,type);
}

stock UpdateAllDynamicElements(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++) Streamer::Update(i);
}

stock RemoveDynamicObjectMaterialAll(STREAMER_TAG_OBJECT:objectid){
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialUsed(objectid,i)){
			RemoveDynamicObjectMaterial(objectid,i);
		}
	}
}

stock CheckStreamerVersion(){
	if(!IsValidStreamer(GetValidStreamerVersion())){
		new str1[32], str2[32];
		GetStreamerVersionName(str1,GetStreamerVersion());
		GetStreamerVersionName(str2,GetValidStreamerVersion());
		printf("[ADM] Error: Your Streamer %s It is not compatible with this version Streamer Functions, update your Streamer to %s",str1,str2);
	}
}

stock GetNearestVisibleItem(playerid,type){
	new Float:x, Float:y, Float:z, max_element, tmp_item, itemid = INVALID_STREAMER_ID,
		Float:min_radius = 20000.0, Float:distance, idx_max = 0, idx = 0;
	
	GetPlayerPos(playerid,x,y,z);
	idx_max = Streamer::CountVisibleItems(playerid,type,1);
	switch(type){
		case STREAMER_TYPE_OBJECT, STREAMER_TYPE_PICKUP, STREAMER_TYPE_MAP_ICON, STREAMER_TYPE_3D_TEXT_LABEL, STREAMER_TYPE_ACTOR: {
			max_element = Streamer::GetVisibleItems(type,playerid);
			while(idx <= max_element && idx_max > 0){
				if((tmp_item = Streamer::GetItemStreamerID(playerid,type,idx)) != INVALID_STREAMER_ID){
					idx_max--;
					Streamer::GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
					if(distance < min_radius){
						itemid = tmp_item;
						min_radius = distance;
					}
				}
				idx++;
			}
		}
		
		#if defined SSpec_StreamerVehicle
			case STREAMER_TYPE_VEHICLE: {
				max_element = Streamer::GetVisibleItems(type,playerid);
				while(idx <= max_element && idx_max > 0){
					if((tmp_item = Streamer::GetItemStreamerID(playerid,type,idx)) != INVALID_STREAMER_ID){
						idx_max--;
						Streamer::GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
						if(distance < min_radius){
							itemid = tmp_item;
							min_radius = distance;
						}
					}
					idx++;
				}
			}
		#endif

		case STREAMER_TYPE_CP: {
			itemid = _:GetPlayerVisibleDynamicCP(playerid);
		}
		
		case STREAMER_TYPE_RACE_CP: {
			itemid = _:GetPlayerVisibleDynamicRaceCP(playerid);
		}
		
		case STREAMER_TYPE_AREA: {
			max_element = GetDynamicAreaPoolSize(), idx = 1;
			while(idx <= max_element && idx_max > 0){
				if(IsValidDynamicArea(STREAMER_TAG_AREA:idx)){
					if(Streamer::IsItemVisible(playerid,type,idx)){
						idx_max--;
						Streamer::GetDistanceToItem(x,y,z,type,tmp_item,distance,3);
						if(distance < min_radius){
							itemid = tmp_item;
							min_radius = distance;
						}
					}
				}
				idx++;
			}
		}
		
		default: return INVALID_STREAMER_ID;
	}
	return itemid;
}

#define GetDynamicCuboidPos 					GetDynamicCubePos
#define SetDynamicCuboidPos						SetDynamicCubePos

/****************************************************************************************************
 *                                                                                                  *
 * Fix Destroy Object Hook                                                                          *
 *                                                                                                  *
 ****************************************************************************************************/

#if !defined DISABLE_STREAMER_SPEC_FIXES
	//Hook: DestroyDynamicObject
	stock SF_DestroyDynamicObject(&STREAMER_TAG_OBJECT:objectid){
		new dobj = DestroyDynamicObject(objectid);
		objectid = INVALID_DYNAMIC_OBJECT_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicObject
		#undef DestroyDynamicObject
	#else
		#define _ALS_DestroyDynamicObject
	#endif
	#define DestroyDynamicObject SF_DestroyDynamicObject

	//Hook: DestroyDynamicPickup
	stock SF_DestroyDynamicPickup(&STREAMER_TAG_PICKUP:pickupid){
		new dobj = DestroyDynamicPickup(pickupid);
		pickupid = INVALID_DYNAMIC_PICKUP_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicPickup
		#undef DestroyDynamicPickup
	#else
		#define _ALS_DestroyDynamicPickup
	#endif
	#define DestroyDynamicPickup SF_DestroyDynamicPickup

	//Hook: DestroyDynamicCP
	stock SF_DestroyDynamicCP(&STREAMER_TAG_CP:checkpointid){
		new dobj = DestroyDynamicCP(checkpointid);
		checkpointid = INVALID_DYNAMIC_CP_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicCP
		#undef DestroyDynamicCP
	#else
		#define _ALS_DestroyDynamicCP
	#endif
	#define DestroyDynamicCP SF_DestroyDynamicCP

	//Hook: DestroyDynamicRaceCP
	stock SF_DestroyDynamicRaceCP(&STREAMER_TAG_RACE_CP:checkpointid){
		new dobj = DestroyDynamicRaceCP(checkpointid);
		checkpointid = INVALID_DYNAMIC_RACE_CP_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicRaceCP
		#undef DestroyDynamicRaceCP
	#else
		#define _ALS_DestroyDynamicRaceCP
	#endif
	#define DestroyDynamicRaceCP SF_DestroyDynamicRaceCP

	//Hook: DestroyDynamicMapIcon
	stock SF_DestroyDynamicMapIcon(&STREAMER_TAG_MAP_ICON:iconid){
		new dobj = DestroyDynamicMapIcon(iconid);
		iconid = INVALID_DYNAMIC_MAP_ICON_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicMapIcon
		#undef DestroyDynamicMapIcon
	#else
		#define _ALS_DestroyDynamicMapIcon
	#endif
	#define DestroyDynamicMapIcon SF_DestroyDynamicMapIcon

	//Hook: DestroyDynamic3DTextLabel
	stock SF_DestroyDynamic3DTextLabel(&STREAMER_TAG_3D_TEXT_LABEL:id){
		new dobj = DestroyDynamic3DTextLabel(id);
		id = INVALID_DYNAMIC_3D_TEXT_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamic3DTextLabel
		#undef DestroyDynamic3DTextLabel
	#else
		#define _ALS_DestroyDynamic3DTextLabel
	#endif
	#define DestroyDynamic3DTextLabel SF_DestroyDynamic3DTextLabel

	//Hook: DestroyDynamicArea
	stock SF_DestroyDynamicArea(&STREAMER_TAG_AREA:areaid){
		new dobj = DestroyDynamicArea(areaid);
		areaid = INVALID_DYNAMIC_AREA_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicArea
		#undef DestroyDynamicArea
	#else
		#define _ALS_DestroyDynamicArea
	#endif
	#define DestroyDynamicArea SF_DestroyDynamicArea
	
	//Hook: DestroyDynamicActor
	stock SF_DestroyDynamicActor(&STREAMER_TAG_ACTOR:actorid){
		new dobj = DestroyDynamicActor(actorid);
		actorid = INVALID_DYNAMIC_ACTOR_ID;
		return dobj;
	}

	#if defined _ALS_DestroyDynamicActor
		#undef DestroyDynamicActor
	#else
		#define _ALS_DestroyDynamicActor
	#endif
	#define DestroyDynamicActor SF_DestroyDynamicActor
	
	//Hook: AttachDynamicObjectToObject
	stock SF_AttachDynamicObjectToObject(STREAMER_TAG_OBJECT:objectid,attachtoid,Float:offsetx,Float:offsety,Float:offsetz,Float:rx,Float:ry,Float:rz,syncrotation = 1){
		new dobj = AttachDynamicObjectToObject(objectid,attachtoid,offsetx,offsety,offsetz,rx,ry,rz,syncrotation);
		if(GetDynamicObjectPriority(objectid) <= GetDynamicObjectPriority(attachtoid)){
			SetDynamicObjectPriority(objectid,GetDynamicObjectPriority(attachtoid)+1);
		}
		return dobj;
	}

	#if defined _LS_AttachDynamicObjectToObject
		#undef AttachDynamicObjectToObject
	#else
		#define _LS_AttachDynamicObjectToObject
	#endif
	#define AttachDynamicObjectToObject SF_AttachDynamicObjectToObject

	//Hook: DestroyObject
	stock SF_DestroyObject(&objectid){
		new dobj = DestroyObject(objectid);
		objectid = INVALID_OBJECT_ID;
		return dobj;
	}

	#if defined _ALS_DestroyObject
		#undef DestroyObject
	#else
		#define _ALS_DestroyObject
	#endif
	#define DestroyObject SF_DestroyObject

	//Hook: DestroyPlayerObject
	stock SF_DestroyPlayerObject(playerid,&objectid){
		new dobj = DestroyPlayerObject(playerid,objectid);
		objectid = INVALID_OBJECT_ID;
		return dobj;
	}

	#if defined _ALS_DestroyPlayerObject
		#undef DestroyPlayerObject
	#else
		#define _ALS_DestroyPlayerObject
	#endif
	#define DestroyPlayerObject SF_DestroyPlayerObject

	//Hook: DestroyPickup
	stock SF_DestroyPickup(&pickupid){
		new dobj = DestroyPickup(pickupid);
		pickupid = INVALID_PICKUP_ID;
		return dobj;
	}

	#if defined _ALS_DestroyPickup
		#undef DestroyPickup
	#else
		#define _ALS_DestroyPickup
	#endif
	#define DestroyPickup SF_DestroyPickup

	//Hook: Delete3DTextLabel
	stock SF_Delete3DTextLabel(&Text3D:id){
		new dobj = Delete3DTextLabel(id);
		id = Text3D:INVALID_3DTEXT_ID;
		return dobj;
	}

	#if defined _ALS_Delete3DTextLabel
		#undef Delete3DTextLabel
	#else
		#define _ALS_Delete3DTextLabel
	#endif
	#define Delete3DTextLabel SF_Delete3DTextLabel

	//Hook: DeletePlayer3DTextLabel
	stock SF_DeletePlayer3DTextLabel(playerid,&PlayerText3D:id){
		new dobj = DeletePlayer3DTextLabel(playerid,id);
		id = PlayerText3D:INVALID_3DTEXT_ID;
		return dobj;
	}

	#if defined _ALS_DeletePlayer3DTextLabel
		#undef DeletePlayer3DTextLabel
	#else
		#define _ALS_DeletePlayer3DTextLabel
	#endif
	#define DeletePlayer3DTextLabel SF_DeletePlayer3DTextLabel
	
	
	#if defined SSpec_StreamerVehicle
		//Hook: DestroyDynamicVehicle
		stock SF_DestroyDynamicVehicle(&STREAMER_TAG_VEHICLE:vehicleid){
			new dobj = DestroyDynamicVehicle(vehicleid);
			vehicleid = INVALID_DYNAMIC_VEHICLE_ID;
			return dobj;
		}

		#if defined _ALS_DestroyDynamicVehicle
			#undef DestroyDynamicVehicle
		#else
			#define _ALS_DestroyDynamicVehicle
		#endif
		#define DestroyDynamicVehicle SF_DestroyDynamicVehicle
	#endif
	
#endif

/****************************************************************************************************
 *                                                                                                  *
 * DynamicAntiArea Hook                                                                             *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined OnPlayerEnterAntiArea
	forward OnPlayerEnterAntiArea(playerid,STREAMER_TAG_AREA:areaid);
#endif
#if defined OnPlayerLeaveAntiArea
	forward OnPlayerLeaveAntiArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	#if defined OnPlayerLeaveAntiArea
		OnPlayerLeaveAntiArea(playerid,areaid);
	#endif
	#if defined SSpec_OnPlayerEnterDynamicArea
		SSpec_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea SSpec_OnPlayerEnterDynamicArea
#if defined SSpec_OnPlayerEnterDynamicArea
	forward SSpec_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerLeaveDynamicArea
public OnPlayerLeaveDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	#if defined OnPlayerEnterAntiArea
		OnPlayerEnterAntiArea(playerid,areaid);
	#endif
	#if defined SSpec_OnPlayerLeaveDynamicArea
		SSpec_OnPlayerLeaveDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea SSpec_OnPlayerLeaveDynamicArea
#if defined SSpec_OnPlayerLeaveDynamicArea
	forward SSpec_OnPlayerLeaveDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

/****************************************************************************************************
 *                                                                                                  *
 * OnPlayerWeaponShot for Streamer Object                                                           *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined ENABLE_BULLET_DYNAMIC_OBJECT

	//Hook: OnPlayerShootDynamicObject
	public OnPlayerShootDynamicObject(playerid,weaponid,STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z){
		new Float:ox, Float:oy, Float:oz, Float:tx, Float:ty, Float:tz;
		GetPlayerLastShotVectors(playerid,ox,oy,oz,tx,ty,tz);
		#if defined OnPlayerWeaponShot
			OnPlayerWeaponShot(playerid,weaponid,BULLET_HIT_TYPE_DYNAMIC_OBJECT,0,tx,ty,tz);
		#endif
		#if defined SSpec_OnShootDynamicObject
			SSpec_OnShootDynamicObject(playerid,weaponid,objectid,x,y,z);
		#endif
		return 1;
	}

	#if defined _ALS_OnPlayerShootDynamicObject
		#undef OnPlayerShootDynamicObject
	#else
		#define _ALS_OnPlayerShootDynamicObject
	#endif
	#define OnPlayerShootDynamicObject SSpec_OnShootDynamicObject
	#if defined SSpec_OnShootDynamicObject
		forward SSpec_OnShootDynamicObject(playerid,weaponid,STREAMER_TAG_OBJECT:objectid,Float:x,Float:y,Float:z);
	#endif
	
#endif

/****************************************************************************************************
 *                                                                                                  *
 * FilterScript/GameMode Init Hook                                                                  *
 *                                                                                                  *
 ****************************************************************************************************/

new bool:CRC_StreamerFunctionInit = true,
	bool:CRC_StreamerFunctionExit = true;

stock StreamerSpecInit(){
	SetSVarInt("ADM:StreamerSpec:ACTIVE",GetStreamerSpecActiveCount()+1);
	
	//Welcome to StreamerFunction
	new ver_name[16];
	format(ver_name,sizeof(ver_name),"%d.%d.%d",(Streamer::Spec_Version / 10000),((Streamer::Spec_Version % 10000) / 100),((Streamer::Spec_Version % 10000) % 100));
	if(GetSVarInt("ADM:StreamerSpec:INIT") == 0){
		SetSVarInt("ADM:StreamerSpec:INIT",1);
		printf("[ADM] Info: Load Streamer Functions v%s for SA:MP %s by Abyss Morgan",ver_name,STREAMER_SPEC_SAMP_VERSION);
	}
	
	#if !defined DISABLE_STREAMER_SPEC_CHECK
		CheckStreamerVersion();
	#endif
}

stock StreamerSpecExit(){
	SetSVarInt("ADM:StreamerSpec:ACTIVE",GetStreamerSpecActiveCount()-1);
	
	//Goodbye StreamerSpec
	new ver_name[16];
	format(ver_name,sizeof(ver_name),"%d.%d.%d",(Streamer::Spec_Version / 10000),((Streamer::Spec_Version % 10000) / 100),((Streamer::Spec_Version % 10000) % 100));
	if(GetStreamerSpecActiveCount() == 0){
		SetSVarInt("ADM:StreamerSpec:INIT",0);
		printf("[ADM] Info: Unload Streamer Functions v%s for SA:MP %s by Abyss Morgan",ver_name,STREAMER_SPEC_SAMP_VERSION);
	}
}

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_StreamerFunctionInit){
		CRC_StreamerFunctionInit = false;
		StreamerSpecInit();
	}
	#if defined SSpec_OnFilterScriptInit
		SSpec_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SSpec_OnFilterScriptInit
#if defined SSpec_OnFilterScriptInit
	forward SSpec_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_StreamerFunctionInit){
		CRC_StreamerFunctionInit = false;
		StreamerSpecInit();
	}
	#if defined SSpec_OnGameModeInit
		SSpec_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SSpec_OnGameModeInit
#if defined SSpec_OnGameModeInit
	forward SSpec_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_StreamerFunctionExit){
		CRC_StreamerFunctionExit = false;
		StreamerSpecExit();
	}
	#if defined SSpec_OnFilterScriptExit
		SSpec_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SSpec_OnFilterScriptExit
#if defined SSpec_OnFilterScriptExit
	forward SSpec_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_StreamerFunctionExit){
		CRC_StreamerFunctionExit = false;
		StreamerSpecExit();
	}
	#if defined SSpec_OnGameModeExit
		SSpec_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit SSpec_OnGameModeExit
#if defined SSpec_OnGameModeExit
	forward SSpec_OnGameModeExit();
#endif

//EOF