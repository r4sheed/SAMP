/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                           )(   San Andreas Object Image Loader   )(                                            *
 *                                                                                                                                *
 * Copyright © 2021 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Website:  https://adm.ct8.pl                                                                                                   *
 *                                                                                                                                *
 * Plugins: Streamer, SScanf                                                                                                      *
 * Modules: None                                                                                                                  *
 *                                                                                                                                *
 * File Version: 2.5.0                                                                                                            *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                                                 *
 * Streamer Version: 2.9.3                                                                                                        *
 * SScanf Version: 2.8.2                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * SAOI::CreateFile(const name[],author[],version[],description[] = "");                                                          *
 * SAOI::LoadObjectImage(const name[],bool:save_logs,bool:fast_boot,bool:security_check); //params: true,false,true               *
 * SAOI::UnloadObjectImage(index);                                                                                                *
 * SAOI::GetFileAuthor(index,author[],version[],description[]);                                                                   *
 * SAOI::IsFileLoaded(const name[],&index=INVALID_SAOI_FILE);                                                                     *
 * SAOI::SaveDynamicObject(objectid,const name[]);                                                                                *
 * SAOI::SaveDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:textid,const name[]);                                                  *
 * SAOI::SaveDynamicPickup(pickupid,const name[]);                                                                                *
 * SAOI::SaveDynamicMapIcon(iconid,const name[]);                                                                                 *
 * SAOI::SaveDynamicArea(areaid,const name[]);                                                                                    *
 * SAOI::SaveDynamicActor(actorid,const name[]);                                                                                  *
 * SAOI::SetBumperIP(const name[],server_ip[]);                                                                                   *
 * SAOI::SetBumperPort(const name[],server_port);                                                                                 *
 * SAOI::SetEOF(const name[]);                                                                                                    *
 * SAOI::GetPositionFlag(index,&Float:x,&Float:y,&Float:z,&Float:angle,&virtualworld,&interior);                                  *
 * SAOI::SetPositionFlag(const name[],Float:x,Float:y,Float:z,Float:angle,virtualworld,interior);                                 *
 * SAOI::SaveRemoveBuilding(const name[],modelid,Float:x,Float:y,Float:z,Float:radius);                                           *
 * SAOI::SaveVehicle(const name[],vehicletype,Float:x,Float:y,Float:z,Float:rotation,color1,color2,respawn_delay,addsiren=0,      *
 *                       worldid=0,interiorid=0);                                                                                 *
 * SAOI::GetFileCreationDate(index,output[],max_dest = sizeof(output));                                                           *
 * SAOI::CountDynamicObject(index);                                                                                               *
 * SAOI::CountDynamic3DTextLabel(index);                                                                                          *
 * SAOI::CountDynamicPickup(index);                                                                                               *
 * SAOI::CountDynamicMapIcon(index);                                                                                              *
 * SAOI::CountDynamicArea(index);                                                                                                 *
 * SAOI::CountDynamicActor(index);                                                                                                *
 * SAOI::CountVehicle(index);                                                                                                     *
 * SAOI::CountMaterial(index);                                                                                                    *
 * SAOI::CountMaterialText(index);                                                                                                *
 * SAOI::CountRemoveBuilding(index);                                                                                              *
 * SAOI::CountColAndreasObject(index);                                                                                            *
 * SAOI::GetFileName(index);                                                                                                      *
 * SAOI::GetLoadTime(index);                                                                                                      *
 * SAOI::GetActiveTime(index);                                                                                                    *
 * SAOI::GetFileSize(index);                                                                                                      *
 * SAOI::CountFileLoaded();                                                                                                       *
 * SAOI::CountAllElementsByIndex(index);                                                                                          *
 * SAOI::CountAllElements();                                                                                                      *
 * SAOI::IsPositionFlagSet(index);                                                                                                *
 * SAOI::ToggleVisibleItems(const name[],playerid,type,toggle);                                                                   *
 * SAOI::WriteHash(const name[]);                                                                                                 *
 *                                                                                                                                *
 * Extended Functions:                                                                                                            *
 * SAOI::GetFreeID();                                                                                                             *
 * SAOI::IsLoaded(index);                                                                                                         *
 * SAOI::IsStatic(index);                                                                                                         *
 * SAOI::IsReadOnly(index);                                                                                                       *
 * SAOI::IsProtected(index);                                                                                                      *
 * SAOI::GetFreeRemoveBuildingID();                                                                                               *
 * SAOI::RemoveBuilding(index,modelid,Float:x,Float:y,Float:z,Float:radius);                                                      *
 * SAOI::GetRemoveBuilding(remove_id,&index,&modelid,&Float:x,&Float:y,&Float:z,&Float:radius);                                   *
 * SAOI::DropRemoveBuildings(index);                                                                                              *
 * SAOI::CleanupElements(index);                                                                                                  *
 * SAOI::DropElements(index);                                                                                                     *
 * SAOI::RemoveBuildingsForPlayer(playerid);                                                                                      *
 * SAOI::UpdateBuildingsForPlayer(playerid,index);                                                                                *
 * SAOI::CountRemovedBuildings();                                                                                                 *
 * SAOI::GetMemoryLoaded();                                                                                                       *
 * SAOI::GetErrorName(index,error_name[],maxdest = sizeof(error_name));                                                           *
 * SAOI::HexStringToString(input[],output[],maxdest = sizeof(output));                                                            *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * SAOI::OnRemovedBuildings(playerid,buildings);                                                                                  *
 * SAOI::OnVehicleDestroyed(vehicleid);                                                                                           *
 * SAOI::OnVehicleCreated(vehicleid);                                                                                             *
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

#if !defined sscanf
	#error [ADM] You need SScanf v2.8.2
#endif

#if ((!defined _MD5_HASH) || (!defined MD5_HashFile))
	#error [ADM] You need MD5.inc
#endif

#if defined _streamer_spec
	#if !defined DISABLE_STREAMER_SPEC_FIXES
		#error [ADM] Invalid mechanism StreamerFunction.inc:DestroyFix (Use #define DISABLE_STREAMER_SPEC_FIXES before StreamerFunction.inc)
	#endif
#endif

#if defined _SAOI_LOADER
	#endinput
#endif
#define _SAOI_LOADER

#define SAOI_LOADER_VERSION 				(20500)			//a.b[c] 10000*a+100*b+c

#define SAOI_HEADER_KEY						"SAOI 2.2 ADM"	//You can never change !!!

#define INVALID_SAOI_FILE					(0)				//You can never change !!!
#define SAOI_EXTRA_ID_OFFSET				(1000000)		//You can never change !!!

#define MAX_SAOI_FILE_SIZE					(0x4000000)		//64 MB
#define MAX_SAOI_NAME_SIZE					(122)			//path = 122 + 6
#define MAX_SAOI_ERROR_NAME					(80)

#define MAX_SAOI_AUTHOR_SIZE 				(32)			//Max Value: 255 (auto resize header, compatible with all version) 
#define MAX_SAOI_VERSION_SIZE 				(32)			//Max Value: 255 (auto resize header, compatible with all version)
#define MAX_SAOI_DESCRIPTION_SIZE 			(128)			//Max Value: 255 (auto resize header, compatible with all version)

#define MAX_FONT_NAME 						(32)			//Max Value: 255 (These limits can be changed according to the San Andreas)
#define MAX_TXD_NAME						(32)			//Max Value: 255 (These limits can be changed according to the San Andreas)
#define MAX_TEXTURE_NAME					(32)			//Max Value: 255 (These limits can be changed according to the San Andreas)
#define MAX_TEXT_NAME						(2048)			//Max Value: 65535 (These limits can be changed according to the San Andreas)

#if !defined MAX_REMOVE_OBJECTS
	#define MAX_REMOVE_OBJECTS				(1000)
#endif

#if !defined MAX_SAOI_FILE
	#define MAX_SAOI_FILE					(2001)			//more ? why not
#endif

#if (MAX_SAOI_FILE > 32768)
	#error [ADM] MAX_SAOI_FILE is too high, maximum value is 32768
#endif

#define SAOI_ERROR_UNEXEC					(0)				//function unexecutable
#define SAOI_ERROR_SUCCESS					(-1)			//success
#define SAOI_ERROR_INPUT_NOT_EXIST			(-2)			//input file not exist
#define SAOI_ERROR_OUTPUT_NOT_EXIST			(-3)			//output file not exist
#define SAOI_ERROR_INPUT_EXIST				(-4)			//input file exist
#define SAOI_ERROR_OUTPUT_EXIST				(-5)			//output file exist
#define SAOI_ERROR_INPUT_NOT_OPEN			(-6)			//error open input file
#define SAOI_ERROR_OUTPUT_NOT_OPEN			(-7)			//error open output file
#define SAOI_ERROR_FILE_SIZE				(-8)			//invalid file size
#define SAOI_ERROR_INVALID_OBJECTID			(-9)			//invalid objectid
#define SAOI_ERROR_AUTHOR_SIZE				(-10)			//invalid author size
#define SAOI_ERROR_VERSION_SIZE				(-11)			//invalid version size
#define SAOI_ERROR_DESCRIPTION_SIZE			(-12)			//invalid description size
#define SAOI_ERROR_INVALID_HEADER			(-13)			//invalid header
#define SAOI_ERROR_INPUT_EXTENSION			(-14)			//invalid input extension
#define SAOI_ERROR_OUTPUT_EXTENSION			(-15)			//invalid output extension
#define SAOI_ERROR_NOT_ENOUGH_CAPACITY		(-16)			//not enough capacity, to load new file
#define SAOI_ERROR_INVALID_ARG_COUNT		(-17)			//number of arguments exceeds the specified arguments (error structure version)
#define SAOI_ERROR_INVALID_SERVER_IP		(-18)			//bumper: invalid server ip
#define SAOI_ERROR_INVALID_SERVER_PORT		(-19)			//bumper: invalid server port
#define SAOI_ERROR_MEMORY_BLOCKED			(-20)			//memory blocked
#define SAOI_ERROR_IS_LOADED				(-21)			//file is already loaded
#define SAOI_ERROR_INVALID_HASH				(-22)			//invalid datagram hash

#define ELEMENT_FLAG_ANTI_AREA				(0)
#define ELEMENT_FLAG_NO_CAMERA_COL			(1)
#define ELEMENT_FLAG_COLANDREAS				(2)
#define ELEMENT_FLAG_COLSTATIC				(3)

#define INVALID_REMOVE_BUILDING_ID			(-1)

#define SAOI_BUMPER_OBJECT					(101)
#define SAOI_BUMPER_PICKUP					(102)
#define SAOI_BUMPER_3D_TEXT_LABEL			(103)
#define SAOI_BUMPER_MAPICON					(104)
#define SAOI_BUMPER_ACTOR					(105)
#define SAOI_BUMPER_VEHICLE					(106)
#define SAOI_BUMPER_AREA_CIRCLE				(107)
#define SAOI_BUMPER_AREA_CYLINDER			(108)
#define SAOI_BUMPER_AREA_SPHERE				(109)
#define SAOI_BUMPER_AREA_RECTANGLE			(110)
#define SAOI_BUMPER_AREA_CUBOID				(111)
#define SAOI_BUMPER_AREA_POLYGON			(112)

#define SAOI_BUMPER_IP						(201)
#define SAOI_BUMPER_PORT					(202)
#define SAOI_BUMPER_POS						(203)
#define SAOI_BUMPER_CREATED					(204)
#define SAOI_BUMPER_REMOVEBUILDING			(205)
#define SAOI_BUMPER_EOF						(255)

#define SAOI::								SAOI_
#define ColAndreas:: 						CA_
#define Streamer:: 							Streamer_

//BitFunctions.inc
#define SAOI_GetValueBit(%0,%1)				((%0) >>> (%1) & 0x01)
#define SAOI_SetValueBit(%0,%1,%2)			((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define SAOI_ExtractValue(%0,%1,%2,%3,%4)	((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define SAOI_ExtractFloat(%0,%1,%2,%3,%4)	((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define SAOI_MergeValue(%0,%1,%2,%3,%4)		((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define SAOI_MergeFloat(%0,%1,%2,%3,%4)		((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#define SAOI_IntMod(%0)						(0xFF & (%0)+128)
#define SAOI_Comp(%0,%1)					(SAOI_IntMod(%0) != (%1))
#define SAOI_Foreach(%0)					for(new %0 = 1; %0 < MAX_SAOI_FILE; %0++)
#define SAOI_GetByteFloat(%0,%1,%2)			SAOI_MergeFloat((%1),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false)), %2+=4
#define SAOI_GetByteInteger(%0,%1,%2)		SAOI_MergeValue((%1),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false)), %2+=4
#define SAOI_GetArgument(%0,%1,%2)			(%1) = fgetchar((%0),0,false), %2++
#define SAOI_GetValue(%0,%1,%2)				SAOI_MergeValue((%1),0,0,fgetchar((%0),0,false),fgetchar((%0),0,false)), %2+=2
#define SAOI_GetArgumentMod(%0,%1,%2)		(%1) = SAOI_IntMod(fgetchar((%0),0,false)), %2++

#define SAOI_Function::						stock
#define SAOI_Public::%0(%1)					forward %0(%1); public %0(%1)

#if !defined isnull
	#define isnull(%1) 						((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined MAX_POLYGON_POINTS
	#define MAX_POLYGON_POINTS 				(256)
#endif

#if (defined COLANDREAS)
	#define SAOI_ColAndreas
#endif

enum e_remove_building {
	SAOI::index,
	SAOI::modelid,
	Float:SAOI::X,
	Float:SAOI::Y,
	Float:SAOI::Z,
	Float:SAOI::R
};

enum e_saoi {
	bool:			SAOI::status,
					SAOI::name[MAX_SAOI_NAME_SIZE],
					SAOI::author[MAX_SAOI_AUTHOR_SIZE],
					SAOI::version[MAX_SAOI_VERSION_SIZE],
					SAOI::description[MAX_SAOI_DESCRIPTION_SIZE],
	bool:			SAOI::is_static,
					SAOI::cnt_object,
					SAOI::cnt_pickup,
					SAOI::cnt_3dtext,
					SAOI::cnt_mapicon,
					SAOI::cnt_area,
					SAOI::cnt_actor,
					SAOI::cnt_vehicle,
					SAOI::cnt_material,
					SAOI::cnt_materialtext,
					SAOI::cnt_removebuilding,
					SAOI::offset_object,
					SAOI::offset_pickup,
					SAOI::offset_3dtext,
					SAOI::offset_mapicon,
					SAOI::offset_area,
					SAOI::offset_actor,
					SAOI::offset_vehicle,
	
	#if defined SAOI_ColAndreas
		SAOI::cnt_caobject,
		SAOI::offset_caobject,
	#endif
	
	SAOI::load_time,
	SAOI::active_tick,
	SAOI::file_size,
	bool:SAOI::write_lock,
	
	Float:SAOI::X,
	Float:SAOI::Y,
	Float:SAOI::Z,
	Float:SAOI::A,
	SAOI::VW,
	SAOI::INT,
	
	SAOI::created[32],
	
	SAOI::hash[16],
	bool:SAOI::protected
};

new SAOI::File[MAX_SAOI_FILE][e_saoi],
	SAOI::Vehicles[MAX_VEHICLES],
	SAOI::RemoveBuildings[MAX_REMOVE_OBJECTS][e_remove_building],
	SAOI::RemoveUpperbound = INVALID_REMOVE_BUILDING_ID,
	bool:SAOI::PlayerFirstSpawn[MAX_PLAYERS],
	bool:SAOI::Access = false;
	
forward SAOI_OnRemovedBuildings(playerid,buildings);
forward SAOI_OnVehicleDestroyed(vehicleid);
forward SAOI_OnVehicleCreated(vehicleid);

#define SAOI_IsStatic(%0) 					(SAOI::File[(%0)][SAOI::is_static])
#define SAOI_IsLoaded(%0) 					(SAOI::File[(%0)][SAOI::status])
#define SAOI_GetFileSize(%0)				(SAOI::File[(%0)][SAOI::file_size])
#define SAOI_GetActiveTime(%0)				(GetTickCount()-SAOI::File[(%0)][SAOI::active_tick])
#define SAOI_GetFileName(%0)				(SAOI::File[(%0)][SAOI::name])
#define SAOI_GetLoadTime(%0)				(SAOI::File[(%0)][SAOI::load_time])
#define SAOI_IsReadOnly(%0)					(SAOI::File[(%0)][SAOI::write_lock])
#define SAOI_IsProtected(%0)				(SAOI::File[(%0)][SAOI::protected])
#define SAOI_CountDynamicObject(%0)			(SAOI::File[(%0)][SAOI::cnt_object])
#define SAOI_CountDynamicPickup(%0)			(SAOI::File[(%0)][SAOI::cnt_pickup])
#define SAOI_CountDynamic3DTextLabel(%0)	(SAOI::File[(%0)][SAOI::cnt_3dtext])
#define SAOI_CountDynamicActor(%0)			(SAOI::File[(%0)][SAOI::cnt_actor])
#define SAOI_CountDynamicMapIcon(%0)		(SAOI::File[(%0)][SAOI::cnt_mapicon])
#define SAOI_CountDynamicArea(%0)			(SAOI::File[(%0)][SAOI::cnt_area])
#define SAOI_CountVehicle(%0)				(SAOI::File[(%0)][SAOI::cnt_vehicle])
#define SAOI_CountMaterial(%0)				(SAOI::File[(%0)][SAOI::cnt_material])
#define SAOI_CountMaterialText(%0)			(SAOI::File[(%0)][SAOI::cnt_materialtext])
#define SAOI_CountRemoveBuilding(%0)		(SAOI::File[(%0)][SAOI::cnt_removebuilding])

#if defined SAOI_ColAndreas
	#define SAOI_CountColAndreasObject(%0)	(SAOI::File[(%0)][SAOI::cnt_caobject])
#endif

SAOI::Function:: SAOI::GetErrorName(index,error_name[],maxdest = sizeof(error_name)){
	switch(index){
		case SAOI_ERROR_UNEXEC: 				format(error_name,maxdest,"Error function unexecutable");
		case SAOI_ERROR_SUCCESS:				format(error_name,maxdest,"Success");
		case SAOI_ERROR_INPUT_NOT_EXIST: 		format(error_name,maxdest,"Error input file not exist");
		case SAOI_ERROR_OUTPUT_NOT_EXIST: 		format(error_name,maxdest,"Error output file not exist");
		case SAOI_ERROR_INPUT_EXIST: 			format(error_name,maxdest,"Error input file exist");
		case SAOI_ERROR_OUTPUT_EXIST:		 	format(error_name,maxdest,"Error output file exist");
		case SAOI_ERROR_INPUT_NOT_OPEN: 		format(error_name,maxdest,"Error open input file");
		case SAOI_ERROR_OUTPUT_NOT_OPEN: 		format(error_name,maxdest,"Error open output file");
		case SAOI_ERROR_FILE_SIZE: 				format(error_name,maxdest,"Error invalid file size");
		case SAOI_ERROR_INVALID_OBJECTID:	 	format(error_name,maxdest,"Error invalid objectid");
		case SAOI_ERROR_AUTHOR_SIZE: 			format(error_name,maxdest,"Error invalid author size");
		case SAOI_ERROR_VERSION_SIZE: 			format(error_name,maxdest,"Error invalid version size");
		case SAOI_ERROR_DESCRIPTION_SIZE:	 	format(error_name,maxdest,"Error invalid description size");
		case SAOI_ERROR_INVALID_HEADER: 		format(error_name,maxdest,"Error invalid header");
		case SAOI_ERROR_INPUT_EXTENSION: 		format(error_name,maxdest,"Error invalid input extension");
		case SAOI_ERROR_OUTPUT_EXTENSION: 		format(error_name,maxdest,"Error invalid output extension");
		case SAOI_ERROR_NOT_ENOUGH_CAPACITY: 	format(error_name,maxdest,"Error not enough capacity, to load new file");
		case SAOI_ERROR_INVALID_ARG_COUNT: 		format(error_name,maxdest,"Error number of arguments exceeds the specified arguments");
		case SAOI_ERROR_INVALID_SERVER_IP:		format(error_name,maxdest,"Error invalid server ip");
		case SAOI_ERROR_INVALID_SERVER_PORT:	format(error_name,maxdest,"Error invalid server port");
		case SAOI_ERROR_MEMORY_BLOCKED:			format(error_name,maxdest,"Error memory blocked");
		case SAOI_ERROR_IS_LOADED:				format(error_name,maxdest,"Error file is already loaded");
		case SAOI_ERROR_INVALID_HASH:			format(error_name,maxdest,"Error invalid datagram hash");
	}
}

SAOI::Function:: SAOI::Construct(){
	new SAOI::data[e_saoi];
	#if defined SAOI_ColAndreas
		SAOI::data[SAOI::offset_caobject] = -1;
	#endif
	return SAOI::data;
}

SAOI::Function:: SAOI::CountAllElementsByIndex(index){
	new items = 0;
	items += SAOI::CountDynamicObject(index);
	items += SAOI::CountDynamicPickup(index);
	items += SAOI::CountDynamic3DTextLabel(index);
	items += SAOI::CountDynamicMapIcon(index);
	items += SAOI::CountDynamicArea(index);
	items += SAOI::CountDynamicActor(index);
	items += SAOI::CountVehicle(index);
	items += SAOI::CountMaterial(index);
	items += SAOI::CountMaterialText(index);
	items += SAOI::CountRemoveBuilding(index);
	#if defined SAOI_ColAndreas
		items += SAOI::CountColAndreasObject(index);
	#endif
	return items;
}

SAOI::Function:: SAOI::CountAllElements(){
	new items = 0;
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)){
			items += SAOI::CountAllElementsByIndex(i);
		}
	}
	return items;
}

SAOI::Function:: SAOI::CountRemovedBuildings(){
	if(!SAOI::Access) return 0;
	new cnt = 0;
	for(new i = SAOI::RemoveUpperbound; i >= 0; i--){
		if(SAOI::RemoveBuildings[i][SAOI::modelid] != 0){
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::GetFreeRemoveBuildingID(){
	if(!SAOI::Access) return INVALID_REMOVE_BUILDING_ID;
	for(new i = 0; i < MAX_REMOVE_OBJECTS; i++){
		if(SAOI::RemoveBuildings[i][SAOI::modelid] == 0){
			if(i > SAOI::RemoveUpperbound) SAOI::RemoveUpperbound = i;
			return i;
		}
	}
	return INVALID_REMOVE_BUILDING_ID;
}

SAOI::Function:: SAOI::GetRemoveBuilding(remove_id,&index,&modelid,&Float:x,&Float:y,&Float:z,&Float:radius){
	if(!SAOI::Access) return 0;
	if(SAOI::RemoveBuildings[remove_id][SAOI::modelid] == 0) return 0;
	modelid = SAOI::RemoveBuildings[remove_id][SAOI::modelid];
	x = SAOI::RemoveBuildings[remove_id][SAOI::X];
	y = SAOI::RemoveBuildings[remove_id][SAOI::Y];
	z = SAOI::RemoveBuildings[remove_id][SAOI::Z];
	radius = SAOI::RemoveBuildings[remove_id][SAOI::R];
	index = SAOI::RemoveBuildings[remove_id][SAOI::index];
	return 1;
}

SAOI::Function:: SAOI::RemoveBuilding(index,modelid,Float:x,Float:y,Float:z,Float:radius){
	if(!SAOI::Access) return INVALID_REMOVE_BUILDING_ID;
	if(!SAOI::IsLoaded(index)) return INVALID_REMOVE_BUILDING_ID;
	new remove_id = SAOI::GetFreeRemoveBuildingID();
	if(remove_id == INVALID_REMOVE_BUILDING_ID) return INVALID_REMOVE_BUILDING_ID;
	SAOI::RemoveBuildings[remove_id][SAOI::modelid] = modelid;
	SAOI::RemoveBuildings[remove_id][SAOI::X] = x;
	SAOI::RemoveBuildings[remove_id][SAOI::Y] = y;
	SAOI::RemoveBuildings[remove_id][SAOI::Z] = z;
	SAOI::RemoveBuildings[remove_id][SAOI::R] = radius;
	SAOI::RemoveBuildings[remove_id][SAOI::index] = index;
	return remove_id;
}

SAOI::Function:: SAOI::DropRemoveBuildings(index){
	if(!SAOI::Access) return 0;
	if(!SAOI::IsLoaded(index)) return 0;
	new cnt = 0;
	for(new i = SAOI::RemoveUpperbound; i >= 0; i--){
		if(SAOI::RemoveBuildings[i][SAOI::index] == index){
			SAOI::RemoveBuildings[i][SAOI::modelid] = 0;
			SAOI::RemoveBuildings[i][SAOI::X] = 0.0;
			SAOI::RemoveBuildings[i][SAOI::Y] = 0.0;
			SAOI::RemoveBuildings[i][SAOI::Z] = 0.0;
			SAOI::RemoveBuildings[i][SAOI::R] = 0.0;
			SAOI::RemoveBuildings[i][SAOI::index] = INVALID_SAOI_FILE;
			if(i == SAOI::RemoveUpperbound) SAOI::RemoveUpperbound--;
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::RemoveBuildingsForPlayer(playerid){
	if(!SAOI::Access) return 0;
	new cnt = 0;
	for(new i = SAOI::RemoveUpperbound; i >= 0; i--){
		if(SAOI::RemoveBuildings[i][SAOI::modelid] != 0){
			RemoveBuildingForPlayer(playerid,SAOI::RemoveBuildings[i][SAOI::modelid],SAOI::RemoveBuildings[i][SAOI::X],SAOI::RemoveBuildings[i][SAOI::Y],SAOI::RemoveBuildings[i][SAOI::Z],SAOI::RemoveBuildings[i][SAOI::R]);
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::HexStringToString(const input[],output[],maxdest = sizeof(output)){
	new asize = (strlen(input)/2), offset = 0, unit[2];
	if(asize > maxdest) return 0;
	for(new i = 0; i < asize; i++){
		if(input[offset] >= 97){
			unit[0] = (input[offset]-87);
		} else if(input[offset] < 58){
			unit[0] = (input[offset]-48);
		} else {
			unit[0] = (input[offset]-55);
		}
		if(input[offset+1] >= 97){
			unit[1] = (input[offset+1]-87);
		} else if(input[offset+1] < 58){
			unit[1] = (input[offset+1]-48);
		} else {
			unit[1] = (input[offset+1]-55);
		}
		output[i] = (unit[0]*16)+unit[1];
		offset += 2;
	}
	output[asize] = EOS;
	return 1;
}

SAOI::Function:: SAOI::WriteHash(const name[]){
	if(!fexist(name)) return 0;
	new file_hash[33], tmp_hash[16];
	format(file_hash,sizeof(file_hash),MD5::HashFile(name,strlen(SAOI_HEADER_KEY) + 16));
	SAOI::HexStringToString(file_hash,tmp_hash);
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,strlen(SAOI_HEADER_KEY),seek_start);
	for(new i = 0; i < 16; i++) fputchar(outf,tmp_hash[i],false);
	fclose(outf);
	return 1;
}

SAOI::Function:: SAOI::GetFileAuthor(index,author[],version[],description[]){
	if(!SAOI::Access) return 0;
	if(!SAOI::IsLoaded(index)) return 0;
	format(author,MAX_SAOI_AUTHOR_SIZE,"%s",SAOI::File[index][SAOI::author]);
	format(version,MAX_SAOI_VERSION_SIZE,"%s",SAOI::File[index][SAOI::version]);
	format(description,MAX_SAOI_DESCRIPTION_SIZE,"%s",SAOI::File[index][SAOI::description]);
	return 1;
}

SAOI::Function:: SAOI::UpdateBuildingsForPlayer(playerid,index){
	if(!SAOI::Access) return 0;
	if(!SAOI::IsLoaded(index)) return 0;
	new cnt = 0;
	for(new i = SAOI::RemoveUpperbound; i >= 0; i--){
		if(SAOI::RemoveBuildings[i][SAOI::modelid] != 0 && SAOI::RemoveBuildings[i][SAOI::index] == index){
			RemoveBuildingForPlayer(playerid,SAOI::RemoveBuildings[i][SAOI::modelid],SAOI::RemoveBuildings[i][SAOI::X],SAOI::RemoveBuildings[i][SAOI::Y],SAOI::RemoveBuildings[i][SAOI::Z],SAOI::RemoveBuildings[i][SAOI::R]);
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::GetFreeID(){
	if(!SAOI::Access) return INVALID_SAOI_FILE;
	SAOI::Foreach(i){
		if(!SAOI::IsLoaded(i)) return i;
	}
	return INVALID_SAOI_FILE;
}

SAOI::Function:: SAOI::CountFileLoaded(){
	if(!SAOI::Access) return 0;
	new cnt = 0;
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)) cnt++;
	}
	return cnt;
}

SAOI::Function:: SAOI::GetMemoryLoaded(){
	if(!SAOI::Access) return 0;
	new cnt = 0;
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)) cnt += SAOI::File[i][SAOI::file_size];
	}
	return cnt;
}

SAOI::Function:: SAOI::SetEOF(const name[]){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	fputchar(outf,SAOI_BUMPER_EOF,false);
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::GetFileCreationDate(index,output[],max_dest = sizeof(output)){
	if(!SAOI::Access) return false;
	if(!SAOI::IsLoaded(index)) return false;
	format(output,max_dest,"%s",SAOI::File[index][SAOI::created]);
	return true;
}

SAOI::Function:: SAOI::GetPositionFlag(index,&Float:x,&Float:y,&Float:z,&Float:angle,&virtualworld,&interior){
	if(!SAOI::Access) return false;
	if(!SAOI::IsLoaded(index)) return false;
	x = SAOI::File[index][SAOI::X];
	y = SAOI::File[index][SAOI::Y];
	z = SAOI::File[index][SAOI::Z];
	angle = SAOI::File[index][SAOI::A];
	virtualworld = SAOI::File[index][SAOI::VW];
	interior = SAOI::File[index][SAOI::INT];
	return true;
}

SAOI::Function:: SAOI::IsPositionFlagSet(index){
	if(!SAOI::Access) return false;
	if(!SAOI::IsLoaded(index)) return false;
	if(SAOI::File[index][SAOI::X] == 0.0 && SAOI::File[index][SAOI::Y] == 0.0 && SAOI::File[index][SAOI::Z] == 0.0 && SAOI::File[index][SAOI::A] == 0.0) return false;
	return true;
}

SAOI::Function:: SAOI::SetPositionFlag(const name[],Float:x,Float:y,Float:z,Float:angle,virtualworld,interior){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append), int1, int2, int3, int4;
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	fputchar(outf,SAOI_BUMPER_POS,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(angle,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(virtualworld,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractValue(interior,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveRemoveBuilding(const name[],modelid,Float:x,Float:y,Float:z,Float:radius){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append), int1, int2, int3, int4;
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	fputchar(outf,SAOI_BUMPER_REMOVEBUILDING,false);
	
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(radius,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::IsFileLoaded(const name[],&index=INVALID_SAOI_FILE){
	if(!SAOI::Access) return false;
	new tmp_saoi_name[MAX_SAOI_NAME_SIZE];
	format(tmp_saoi_name,MAX_SAOI_NAME_SIZE,"%s",name);
	for(new i = strlen(tmp_saoi_name)-1; i >= 0; i--){
		if(tmp_saoi_name[i] == '.'){
			tmp_saoi_name[i] = EOS;
			break;
		}
	}
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)){
			if(!strcmp(tmp_saoi_name,SAOI::File[i][SAOI::name],true)){
				index = i;
				return true;
			}
		}
	}
	return false;
}

SAOI::Function:: SAOI::CreateFile(const name[],author[],version[],description[] = ""){
	if(fexist(name)) return SAOI_ERROR_OUTPUT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new year,month,day,hour,minute,second;
	getdate(year,month,day);
	gettime(hour,minute,second);
	
	fwrite(outf,SAOI_HEADER_KEY);
	for(new i = 0; i < 16; i++) fputchar(outf,0,false);
	
	//Create Header
	new author_size = strlen(author),
		version_size = strlen(version),
		description_size = strlen(description);
	
	if(author_size > MAX_SAOI_AUTHOR_SIZE){
		fclose(outf);
		return SAOI_ERROR_AUTHOR_SIZE;
	}
	if(version_size > MAX_SAOI_VERSION_SIZE ){
		fclose(outf);
		return SAOI_ERROR_VERSION_SIZE;
	}
	if(description_size > MAX_SAOI_DESCRIPTION_SIZE){
		fclose(outf);
		return SAOI_ERROR_DESCRIPTION_SIZE;
	}
	
	new key[32];
	for(new i = 0; i < 32; i++){
		key[i] = random(255)+1;
	}
	
	new step;
	
	step = 0;
	for(new i = 0; i < author_size; i++){
		author[i] = ((author[i]+key[step]) & 0xFF);
		step++;
		if(step >= 32) step = 0;
	}
	fputchar(outf,author_size,false);
	for(new i = 0; i < author_size; i++){
		fputchar(outf,author[i],false);
	}
	
	step = 0;
	for(new i = 0; i < version_size; i++){
		version[i] = ((version[i]+key[step]) & 0xFF);
		step++;
		if(step >= 32) step = 0;
	}
	fputchar(outf,version_size,false);
	for(new i = 0; i < version_size; i++){
		fputchar(outf,version[i],false);
	}
	
	step = 0;
	for(new i = 0; i < description_size; i++){
		description[i] = ((description[i]+key[step]) & 0xFF);
		step++;
		if(step >= 32) step = 0;
	}
	fputchar(outf,description_size,false);
	for(new i = 0; i < description_size; i++){
		fputchar(outf,description[i],false);
	}
	
	for(new i = 0; i < 32; i++){
		fputchar(outf,((256-key[i]) & 0xFF),false);
	}

	fputchar(outf,SAOI_BUMPER_CREATED,false);
	
	new int1, int2, int3, int4;
	SAOI::ExtractValue(year,int1,int2,int3,int4);
	fputchar(outf,SAOI::IntMod(int3),false);
	fputchar(outf,SAOI::IntMod(int4),false);
	
	fputchar(outf,SAOI::IntMod(month),false);
	fputchar(outf,SAOI::IntMod(day),false);
	fputchar(outf,SAOI::IntMod(hour),false);
	fputchar(outf,SAOI::IntMod(minute),false);
	fputchar(outf,SAOI::IntMod(second),false);
	
	#pragma unused int1,int2
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicObject(objectid,const name[]){
	if(!IsValidDynamicObject(objectid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, Float:streamdistance, Float:drawdistance, areaid, priority,
		arg_count = 14, material_used = 0, material_text_used = 0, element_flag;
	
	//Get Object Info
	modelid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MODEL_ID);
	GetDynamicObjectPos(objectid,x,y,z);
	GetDynamicObjectRot(objectid,rx,ry,rz);
	worldid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_WORLD_ID);
	interiorid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_INTERIOR_ID);
	
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_DRAW_DISTANCE,drawdistance);
	
	areaid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_AREA_ID);
	priority = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_PRIORITY);
	
	if(Streamer::IsToggleItemInvAreas(STREAMER_TYPE_OBJECT,objectid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	if(GetDynamicObjectNoCameraCol(objectid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_NO_CAMERA_COL,1);
	}
	
	element_flag |= (Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID) & 0xFF);
	
	//Count Arg
	for(new i = arg_count; i > 7; i--){
		switch(i){
			case 14: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 13: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(drawdistance == STREAMER_OBJECT_DD){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_OBJECT,false);
	fputchar(outf,arg_count,false);
	
	//Save Object Info
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(rx,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(ry,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(rz,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 8){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractFloat(drawdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 14){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	
	//Get and Save Object Material
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialUsed(objectid,i)){
			SAOI::SetValueBit(material_used,i,1);
		}
	}
	
	SAOI::ExtractValue(material_used,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	new mid, txdname[MAX_TXD_NAME], texturename[MAX_TEXTURE_NAME], materialcolor;
	for(new i = 0; i < 16; i++){
		if(SAOI::GetValueBit(material_used,i) == 1){
			GetDynamicObjectMaterial(objectid,i,mid,txdname,texturename,materialcolor);
			
			SAOI::ExtractValue(mid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			fputchar(outf,strlen(txdname),false);
			for(new k = 0, l = strlen(txdname); k < l; k++){
				fputchar(outf,SAOI::IntMod(txdname[k]),false);
			}
			
			fputchar(outf,strlen(texturename),false);
			for(new k = 0, l = strlen(texturename); k < l; k++){
				fputchar(outf,SAOI::IntMod(texturename[k]),false);
			}
			
			SAOI::ExtractValue(materialcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
		}
	}
	
	//Get and Save Object Material Text
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialTextUsed(objectid,i)){
			SAOI::SetValueBit(material_text_used,i,1);
		}
	}
	
	SAOI::ExtractValue(material_text_used,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	new text[MAX_TEXT_NAME], materialsize, fontface[MAX_FONT_NAME], fontsize, bold, fontcolor, backcolor, textalignment;
	for(new i = 0; i < 16; i++){
		if(SAOI::GetValueBit(material_text_used,i) == 1){
			GetDynamicObjectMaterialText(objectid,i,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
			
			new len = strlen(text);
			SAOI::ExtractValue(len,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			for(new k = 0, l = strlen(text); k < l; k++){
				fputchar(outf,SAOI::IntMod(text[k]),false);
			}
			
			fputchar(outf,materialsize,false);
			
			fputchar(outf,strlen(fontface),false);
			for(new k = 0, l = strlen(fontface); k < l; k++){
				fputchar(outf,SAOI::IntMod(fontface[k]),false);
			}
			
			fputchar(outf,fontsize,false);
			
			fputchar(outf,bold,false);
			
			SAOI::ExtractValue(fontcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractValue(backcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			fputchar(outf,textalignment,false);
			
		}
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicPickup(pickupid,const name[]){
	if(!IsValidDynamicPickup(pickupid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new modelid, Float:x, Float:y, Float:z, type, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 11, element_flag;
	
	//Get Pickup Info
	modelid = Streamer::GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_MODEL_ID);
	
	Streamer::GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_X,x);
	Streamer::GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Y,y);
	Streamer::GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Z,z);
	
	worldid = Streamer::GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_WORLD_ID);
	interiorid = Streamer::GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_INTERIOR_ID);
	
	Streamer::GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	type = Streamer::GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_TYPE);
	
	areaid = Streamer::GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_AREA_ID);
	priority = Streamer::GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_PRIORITY);
	
	if(Streamer::IsToggleItemInvAreas(STREAMER_TYPE_PICKUP,pickupid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 5; i--){
		switch(i){
			case 11: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 7: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 6: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_PICKUP,false);
	fputchar(outf,arg_count,false);
	
	//Save Pickup Info
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(type,int1,int2,int3,int4);
	fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 6){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 7){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 8){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:textid,const name[]){
	if(!IsValidDynamic3DTextLabel(textid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new Float:x, Float:y, Float:z, testlos, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 14, element_flag, textsize, text[2048], color, Float:drawdistance;
	
	//Get 3DTextLabel Info
	GetDynamic3DTextLabelText(textid,text,sizeof(text));
	textsize = strlen(text);
	
	Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_X,x);
	Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_Y,y);
	Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_Z,z);
	
	worldid = Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_WORLD_ID);
	interiorid = Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_INTERIOR_ID);
	
	Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer::GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_DRAW_DISTANCE,drawdistance);
	testlos = Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_TEST_LOS);
	color = Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_COLOR);
	
	areaid = Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_AREA_ID);
	priority = Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_PRIORITY);
	
	if(Streamer::IsToggleItemInvAreas(STREAMER_TYPE_3D_TEXT_LABEL,textid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 7; i--){
		switch(i){
			case 14: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 13: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(testlos == 0){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_3D_TEXT_LABEL,false);
	fputchar(outf,arg_count,false);
	
	//Save 3DTextLabel Info
	SAOI::ExtractValue(textsize,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	for(new k = 0; k < textsize; k++){
		fputchar(outf,SAOI::IntMod(text[k]),false);
	}
	
	SAOI::ExtractValue(color,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(drawdistance,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	if(arg_count >= 8){
		SAOI::ExtractValue(testlos,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 14){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicMapIcon(iconid,const name[]){
	if(!IsValidDynamicMapIcon(iconid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new Float:x, Float:y, Float:z, type, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 12, element_flag, color, style;
	
	//Get MapIcon Info
	Streamer::GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_X,x);
	Streamer::GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Y,y);
	Streamer::GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Z,z);
	
	worldid = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_WORLD_ID);
	interiorid = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_INTERIOR_ID);
	
	Streamer::GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	type = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_TYPE);
	color = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_COLOR);
	style = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_STYLE);
	
	areaid = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_AREA_ID);
	priority = Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_PRIORITY);
	
	if(Streamer::IsToggleItemInvAreas(STREAMER_TYPE_MAP_ICON,iconid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 5; i--){
		switch(i){
			case 12: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(style == MAPICON_LOCAL){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 7: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 6: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_MAPICON,false);
	fputchar(outf,arg_count,false);
	
	//Save MapIcon Info
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(type,int1,int2,int3,int4);
	fputchar(outf,int4,false);
	
	SAOI::ExtractValue(color,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 6){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 7){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 8){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(style,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicActor(actorid,const name[]){
	if(!IsValidDynamicActor(actorid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new Float:x, Float:y, Float:z, Float:z_angle, modelid, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 13, element_flag, invulnerable = 0, Float:health;
	
	//Get Actor Info
	GetDynamicActorPos(actorid,x,y,z);
	GetDynamicActorFacingAngle(actorid,z_angle);
	
	modelid = Streamer::GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_MODEL_ID);
	worldid = GetDynamicActorVirtualWorld(actorid);
	interiorid = Streamer::GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_INTERIOR_ID);
	
	if(IsDynamicActorInvulnerable(actorid)) invulnerable = 1;
	
	Streamer::GetFloatData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	GetDynamicActorHealth(actorid,health);
	
	areaid = Streamer::GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_AREA_ID);
	priority = Streamer::GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_PRIORITY);
	
	if(Streamer::IsToggleItemInvAreas(STREAMER_TYPE_ACTOR,actorid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 5; i--){
		switch(i){
			case 13: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 7: {
				if(health == 100.0){
					arg_count--;
				} else {
					break;
				}
			}
			case 6: {
				if(invulnerable == 1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_ACTOR,false);
	fputchar(outf,arg_count,false);
	
	//Save Actor Info
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z_angle,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 6){
		SAOI::ExtractValue(invulnerable,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 7){
		SAOI::ExtractFloat(health,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 8){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicArea(areaid,const name[]){
	if(!IsValidDynamicArea(areaid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	switch(Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_TYPE)){
		case STREAMER_AREA_TYPE_CIRCLE: {
			//Get Area Data
			new arg_count = 6, Float:x, Float:y, Float:size, worldid = -1, interiorid = -1;
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_SIZE,size);
	
			worldid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 4; i--){
				switch(i){
					case 6: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 5: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_CIRCLE,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(x,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(y,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(size,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 5){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 6){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_CYLINDER: {
			//Get Area Data
			new arg_count = 8, Float:x, Float:y, Float:minz, Float:maxz, Float:size, worldid = -1, interiorid = -1;
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_SIZE,size);
	
			worldid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 6; i--){
				switch(i){
					case 8: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 7: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_CYLINDER,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(x,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(y,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(size,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 7){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 8){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_SPHERE: {
			//Get Area Data
			new arg_count = 7, Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1;
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Z,z);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_SIZE,size);
	
			worldid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 5; i--){
				switch(i){
					case 7: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 6: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_SPHERE,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(x,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(y,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(z,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(size,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 6){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 7){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_RECTANGLE: {
			//Get Area Data
			new arg_count = 7, Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1;
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	
			worldid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 5; i--){
				switch(i){
					case 7: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 6: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_RECTANGLE,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(miny,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxy,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 6){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 7){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_CUBOID: {
			//Get Area Data
			new arg_count = 9, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1;
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
	
			worldid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 7; i--){
				switch(i){
					case 9: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 8: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_CUBOID,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(miny,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxy,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 8){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 9){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_POLYGON: {
			//Get Area Data
			new arg_count = 7, Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, worldid = -1, interiorid = -1, Float:Polygon_Points[MAX_POLYGON_POINTS*2], max_points;
			
			GetDynamicPolygonPoints(areaid,Polygon_Points,sizeof(Polygon_Points));
			max_points = GetDynamicPolygonNumberPoints(areaid) * 2;
			
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
			Streamer::GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
			
			worldid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 3; i--){
				switch(i){
					case 7: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 6: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 5: {
						if(maxz == FLOAT_INFINITY){
							arg_count--;
						} else {
							break;
						}
					}
					case 4: {
						if(minz == -FLOAT_INFINITY){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_POLYGON,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractValue(max_points,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			for(new k = 0; k < max_points; k++){
				SAOI::ExtractFloat(Polygon_Points[k],int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			
			if(arg_count >= 4){
				SAOI::ExtractFloat(minz,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			
			if(arg_count >= 5){
				SAOI::ExtractFloat(maxz,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			
			if(arg_count >= 6){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 7){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveVehicle(const name[],vehicletype,Float:x,Float:y,Float:z,Float:rotation,color1,color2,respawn_delay,addsiren=0,worldid=0,interiorid=0){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	if(color1 == -1) color1 = 0xFFFF;
	if(color2 == -1) color2 = 0xFFFF;
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_VEHICLE,false);

	//Save Vehicle Info
	SAOI::ExtractValue(vehicletype,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(rotation,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(color1,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(color2,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractValue(respawn_delay,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);	
	
	SAOI::ExtractValue(addsiren,int1,int2,int3,int4);
	fputchar(outf,int4,false);

	SAOI::ExtractValue(worldid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SetBumperIP(const name[],server_ip[]){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new serv_ipsum[4], saoi_ipsum[4];
	sscanf(server_ip,"p<.>dddd",serv_ipsum[0],serv_ipsum[1],serv_ipsum[2],serv_ipsum[3]);
	
	saoi_ipsum[0] = SAOI::IntMod(serv_ipsum[3]);
	saoi_ipsum[1] = SAOI::IntMod(serv_ipsum[2]);
	saoi_ipsum[2] = SAOI::IntMod(serv_ipsum[1]);
	saoi_ipsum[3] = SAOI::IntMod(serv_ipsum[0]);
	
	fputchar(outf,SAOI_BUMPER_IP,false);
	for(new i = 0; i < 4; i++){
		fputchar(outf,saoi_ipsum[i],false);
	}

	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SetBumperPort(const name[],server_port){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new serv_portsum[4], saoi_portsum[4];
	SAOI::ExtractValue(server_port,serv_portsum[0],serv_portsum[1],serv_portsum[2],serv_portsum[3]);
	
	saoi_portsum[0] = SAOI::IntMod(serv_portsum[3]);
	saoi_portsum[1] = SAOI::IntMod(serv_portsum[2]);
	saoi_portsum[2] = SAOI::IntMod(serv_portsum[1]);
	saoi_portsum[3] = SAOI::IntMod(serv_portsum[0]);
	
	fputchar(outf,SAOI_BUMPER_PORT,false);
	for(new i = 0; i < 4; i++){
		fputchar(outf,saoi_portsum[i],false);
	}

	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::CleanupElements(index){
	if(!SAOI::IsLoaded(index)) return false;
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index);
	
	//Remove Buildings
	SAOI::DropRemoveBuildings(index);
	
	//Objects
	if(SAOI::File[index][SAOI::cnt_object] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_object], i = SAOI::File[index][SAOI::offset_object], j = Streamer::GetUpperBound(STREAMER_TYPE_OBJECT);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicObject(STREAMER_TAG_OBJECT:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,STREAMER_TAG_OBJECT:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicObject(STREAMER_TAG_OBJECT:i);
				}
			}
			i++;
		}
	}

	//ColAndreas::CreateObject
	#if defined SAOI_ColAndreas
		if(SAOI::File[index][SAOI::cnt_caobject] > 0){
			new max_idx = SAOI::File[index][SAOI::cnt_caobject], i = SAOI::File[index][SAOI::offset_caobject];
			while(i < MAX_CA_OBJECTS && max_idx > 0){
				if(ColAndreas::GetObjectExtraID(i,ColAndreas::EXTRA_1) == extraid){
					max_idx--;
					ColAndreas::DestroyObject_DC(i);
				}
				i++;
			}
		}
	#endif
	
	//3DTextLabels
	if(SAOI::File[index][SAOI::cnt_3dtext] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_3dtext], i = SAOI::File[index][SAOI::offset_3dtext], j = Streamer::GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL);
		while(i <= j && max_idx > 0){
			if(IsValidDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,STREAMER_TAG_3D_TEXT_LABEL:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:i);
				}
			}
			i++;
		}
	}
	
	//Pickups
	if(SAOI::File[index][SAOI::cnt_pickup] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_pickup], i = SAOI::File[index][SAOI::offset_pickup], j = Streamer::GetUpperBound(STREAMER_TYPE_PICKUP);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicPickup(STREAMER_TAG_PICKUP:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_PICKUP,STREAMER_TAG_PICKUP:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicPickup(STREAMER_TAG_PICKUP:i);
				}
			}
			i++;
		}
	}
	
	//MapIcons
	if(SAOI::File[index][SAOI::cnt_mapicon] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_mapicon], i = SAOI::File[index][SAOI::offset_mapicon], j = Streamer::GetUpperBound(STREAMER_TYPE_MAP_ICON);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicMapIcon(STREAMER_TAG_MAP_ICON:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,STREAMER_TAG_MAP_ICON:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicMapIcon(STREAMER_TAG_MAP_ICON:i);
				}
			}
			i++;
		}
	}
	
	//Actors
	if(SAOI::File[index][SAOI::cnt_actor] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_actor], i = SAOI::File[index][SAOI::offset_actor], j = Streamer::GetUpperBound(STREAMER_TYPE_ACTOR);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicActor(STREAMER_TAG_ACTOR:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_ACTOR,STREAMER_TAG_ACTOR:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicActor(STREAMER_TAG_ACTOR:i);
				}
			}
			i++;
		}
	}
	
	//Areas
	if(SAOI::File[index][SAOI::cnt_area] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_area], i = SAOI::File[index][SAOI::offset_area], j = Streamer::GetUpperBound(STREAMER_TYPE_AREA);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicArea(STREAMER_TAG_AREA:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_AREA,STREAMER_TAG_AREA:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicArea(STREAMER_TAG_AREA:i);
				}
			}
			i++;
		}
	}
	
	//Vehicles
	new prot_i = 0;
	if(SAOI::File[index][SAOI::cnt_vehicle] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_vehicle], i = SAOI::File[index][SAOI::offset_vehicle], j = GetVehiclePoolSize();
		while(i <= j && max_idx > 0){
			prot_i = i;
			if(IsValidVehicle(i)){
				if(SAOI::Vehicles[i] == index){
					max_idx--;
					DestroyVehicle(prot_i);
					CallRemoteFunction("SAOI_OnVehicleDestroyed","d",i);
					CallRemoteFunction("EVF_RemoveVehicle","d",i);
					SAOI::Vehicles[i] = INVALID_SAOI_FILE;
				}
			}
			i++;
		}
	}
	
	return true;
}

SAOI::Function:: SAOI::DropElements(index){
	if(!SAOI::IsLoaded(index)) return false;
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index);
	
	//Objects
	if(SAOI::File[index][SAOI::cnt_object] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_object], i = SAOI::File[index][SAOI::offset_object], j = Streamer::GetUpperBound(STREAMER_TYPE_OBJECT);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicObject(STREAMER_TAG_OBJECT:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,STREAMER_TAG_OBJECT:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					Streamer::SetIntData(STREAMER_TYPE_OBJECT,STREAMER_TAG_OBJECT:i,E_STREAMER_EXTRA_ID,0);
				}
			}
			i++;
		}
	}

	//ColAndreas::CreateObject
	#if defined SAOI_ColAndreas
		if(SAOI::File[index][SAOI::cnt_caobject] > 0){
			new max_idx = SAOI::File[index][SAOI::cnt_caobject], i = SAOI::File[index][SAOI::offset_caobject];
			while(i < MAX_CA_OBJECTS && max_idx > 0){
				if(ColAndreas::GetObjectExtraID(i,ColAndreas::EXTRA_1) == extraid){
					max_idx--;
					ColAndreas::SetObjectExtraID(i,ColAndreas::EXTRA_1,0);
				}
				i++;
			}
		}
	#endif
	
	//3DTextLabels
	if(SAOI::File[index][SAOI::cnt_3dtext] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_3dtext], i = SAOI::File[index][SAOI::offset_3dtext], j = Streamer::GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL);
		while(i <= j && max_idx > 0){
			if(IsValidDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,STREAMER_TAG_3D_TEXT_LABEL:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,STREAMER_TAG_3D_TEXT_LABEL:i,E_STREAMER_EXTRA_ID,0);
				}
			}
			i++;
		}
	}
	
	//Pickups
	if(SAOI::File[index][SAOI::cnt_pickup] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_pickup], i = SAOI::File[index][SAOI::offset_pickup], j = Streamer::GetUpperBound(STREAMER_TYPE_PICKUP);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicPickup(STREAMER_TAG_PICKUP:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_PICKUP,STREAMER_TAG_PICKUP:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					Streamer::SetIntData(STREAMER_TYPE_PICKUP,STREAMER_TAG_PICKUP:i,E_STREAMER_EXTRA_ID,0);
				}
			}
			i++;
		}
	}
	
	//MapIcons
	if(SAOI::File[index][SAOI::cnt_mapicon] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_mapicon], i = SAOI::File[index][SAOI::offset_mapicon], j = Streamer::GetUpperBound(STREAMER_TYPE_MAP_ICON);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicMapIcon(STREAMER_TAG_MAP_ICON:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,STREAMER_TAG_MAP_ICON:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,STREAMER_TAG_MAP_ICON:i,E_STREAMER_EXTRA_ID,0);
				}
			}
			i++;
		}
	}
	
	//Actors
	if(SAOI::File[index][SAOI::cnt_actor] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_actor], i = SAOI::File[index][SAOI::offset_actor], j = Streamer::GetUpperBound(STREAMER_TYPE_ACTOR);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicActor(STREAMER_TAG_ACTOR:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_ACTOR,STREAMER_TAG_ACTOR:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					Streamer::SetIntData(STREAMER_TYPE_ACTOR,STREAMER_TAG_ACTOR:i,E_STREAMER_EXTRA_ID,0);
				}
			}
			i++;
		}
	}
	
	//Areas
	if(SAOI::File[index][SAOI::cnt_area] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_area], i = SAOI::File[index][SAOI::offset_area], j = Streamer::GetUpperBound(STREAMER_TYPE_AREA);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicArea(STREAMER_TAG_AREA:i)){
				if(Streamer::GetIntData(STREAMER_TYPE_AREA,STREAMER_TAG_AREA:i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					Streamer::SetIntData(STREAMER_TYPE_AREA,STREAMER_TAG_AREA:i,E_STREAMER_EXTRA_ID,0);
				}
			}
			i++;
		}
	}
	
	//Vehicles
	if(SAOI::File[index][SAOI::cnt_vehicle] > 0){
		new max_idx = SAOI::File[index][SAOI::cnt_vehicle], i = SAOI::File[index][SAOI::offset_vehicle], j = GetVehiclePoolSize();
		while(i <= j && max_idx > 0){
			if(IsValidVehicle(i)){
				if(SAOI::Vehicles[i] == index){
					max_idx--;
					SAOI::Vehicles[i] = INVALID_SAOI_FILE;
				}
			}
			i++;
		}
	}
	
	return true;
}

SAOI::Public:: SAOI::LoadObjectImage(const name[],bool:save_logs,bool:fast_boot,bool:security_check){
	if(!SAOI::Access) return SAOI_ERROR_MEMORY_BLOCKED;
	new index = SAOI::GetFreeID();
	if(index == INVALID_SAOI_FILE) return SAOI_ERROR_NOT_ENOUGH_CAPACITY;
	if(!fast_boot && SAOI::IsFileLoaded(name)) return SAOI_ERROR_IS_LOADED;
	
	new NTTime = GetTickCount();
	if(!fexist(name)) return SAOI_ERROR_INPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_INPUT_EXTENSION;
	
	new file_hash[33];
	if(security_check){
		format(file_hash,sizeof(file_hash),MD5::HashFile(name,strlen(SAOI_HEADER_KEY) + 16));
	}
	
	new File:inpf = fopen(name,io_read);
	if(!inpf) return SAOI_ERROR_INPUT_NOT_OPEN;
	new asize = flength(inpf), offset = 0;
	if(asize > MAX_SAOI_FILE_SIZE || asize < 0){
		fclose(inpf);
		return SAOI_ERROR_FILE_SIZE;
	}

	SAOI::File[index] = SAOI::Construct();
	SAOI::File[index][SAOI::status] = true;
	format(SAOI::File[index][SAOI::name],MAX_SAOI_NAME_SIZE,"%s",name);
	for(new i = strlen(SAOI::File[index][SAOI::name])-1; i >= 0; i--){
		if(SAOI::File[index][SAOI::name][i] == '.'){
			SAOI::File[index][SAOI::name][i] = EOS;
			break;
		}
	}
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index);
	
	new modelid, texture_modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid,
		Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance, areaid, priority,
		arg_count, material_used, material_text_used, elementid, element_flag,
		txdname[MAX_TXD_NAME], texturename[MAX_TEXTURE_NAME], materialcolor, txdsize, texturenamesize,
		text[MAX_TEXT_NAME], fontface[MAX_FONT_NAME], textsize, materialsize, fontfacesize, bold, fontcolor, backcolor,
		textalignment, fontsize, load_time, type, style, color,
		color1, color2, respawn_delay, addsiren, Float:size, invulnerable, Float:health,
		Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz,
		Float:Polygon_Points[MAX_POLYGON_POINTS*2], max_points, DynamicAreas[512], testlos, tmp_hash[16];
	
	#if defined SAOI_ColAndreas
		new col_elementid;
	#endif
	
	if(security_check){
		SAOI::HexStringToString(file_hash,tmp_hash);
	}
	
	//Get Header
	new h_len = strlen(SAOI_HEADER_KEY), h_key[32];
	for(new i = 0; i < h_len; i++){
		SAOI::GetArgument(inpf,h_key[i],offset);
	}
	h_key[h_len] = EOS;
	if(!strcmp(h_key,SAOI_HEADER_KEY,true)){
		new author_size, version_size, description_size, key[32];
		
		new tmp_crc = 16;
		for(new i = 0; i < 16; i++){
			SAOI::GetArgument(inpf,SAOI::File[index][SAOI::hash][i],offset);
			if(SAOI::File[index][SAOI::hash][i] == 0) tmp_crc--;
		}
		SAOI::File[index][SAOI::protected] = (tmp_crc)?(true):(false);
		if(tmp_crc && security_check){
			for(new i = 0; i < 16; i++){
				if(tmp_hash[i] != SAOI::File[index][SAOI::hash][i]){
					SAOI::File[index][SAOI::status] = false;
					fclose(inpf);
					return SAOI_ERROR_INVALID_HASH;
				}
			}
		}
		
		SAOI::GetArgument(inpf,author_size,offset);
		for(new i = 0; i < author_size; i++){
			SAOI::GetArgument(inpf,SAOI::File[index][SAOI::author][i],offset);
		}
		
		SAOI::GetArgument(inpf,version_size,offset);
		for(new i = 0; i < version_size; i++){
			SAOI::GetArgument(inpf,SAOI::File[index][SAOI::version][i],offset);
		}
		
		SAOI::GetArgument(inpf,description_size,offset);
		for(new i = 0; i < description_size; i++){
			SAOI::GetArgument(inpf,SAOI::File[index][SAOI::description][i],offset);
		}
		
		for(new i = 0; i < 32; i++){
			SAOI::GetArgument(inpf,key[i],offset);
		}
		
		new step;
		
		step = 0;
		for(new i = 0; i < author_size; i++){
			SAOI::File[index][SAOI::author][i] = ((SAOI::File[index][SAOI::author][i]+key[step++ % 32]) & 0xFF);
		}
		
		step = 0;
		for(new i = 0; i < version_size; i++){
			SAOI::File[index][SAOI::version][i] = ((SAOI::File[index][SAOI::version][i]+key[step++ % 32]) & 0xFF);
		}
		
		step = 0;
		for(new i = 0; i < description_size; i++){
			SAOI::File[index][SAOI::description][i] = ((SAOI::File[index][SAOI::description][i]+key[step++ % 32]) & 0xFF);
		}
	} else {
		SAOI::File[index][SAOI::status] = false;
		fclose(inpf);
		return SAOI_ERROR_INVALID_HEADER;
	}
	
	while(offset < asize){
		//Get Arg Count
		SAOI::GetArgument(inpf,arg_count,offset);
		switch(arg_count){
			case SAOI_BUMPER_OBJECT: {
				SAOI::GetArgument(inpf,arg_count,offset);
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				material_used = 0;
				material_text_used = 0;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				drawdistance = STREAMER_OBJECT_DD;
				areaid = -1;
				priority = 0;
				element_flag = 0;
		
				SAOI::GetByteInteger(inpf,modelid,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetByteFloat(inpf,rx,offset);
				SAOI::GetByteFloat(inpf,ry,offset);
				SAOI::GetByteFloat(inpf,rz,offset);
				
				if(arg_count >= 8)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 9)	SAOI::GetByteInteger(inpf,interiorid,offset);
				if(arg_count >= 10)	SAOI::GetByteFloat(inpf,streamdistance,offset);
				if(arg_count >= 11)	SAOI::GetByteFloat(inpf,drawdistance,offset);
				if(arg_count >= 12)	SAOI::GetByteInteger(inpf,areaid,offset);
				if(arg_count >= 13)	SAOI::GetByteInteger(inpf,priority,offset);
				if(arg_count >= 14)	SAOI::GetArgument(inpf,element_flag,offset);
				
				if(areaid == -1){
					elementid = _:CreateDynamicObject(modelid,x,y,z,rx,ry,rz,worldid,interiorid,-1,streamdistance,drawdistance,STREAMER_TAG_AREA:areaid,priority);
				} else {
					elementid = _:CreateDynamicObject(modelid,x,y,z,rx,ry,rz,worldid,interiorid,-1,streamdistance,drawdistance,STREAMER_TAG_AREA:DynamicAreas[areaid],priority);
				}
				//Get Materials
				SAOI::GetValue(inpf,material_used,offset);
				
				for(new mat = 0; mat < 16; mat++){
					if(SAOI::GetValueBit(material_used,mat) == 1){
						SAOI::GetByteInteger(inpf,texture_modelid,offset);
						
						SAOI::GetArgument(inpf,txdsize,offset);
						for(new i = 0; i < txdsize; i++){
							SAOI::GetArgumentMod(inpf,txdname[i],offset);
						}
						txdname[txdsize] = EOS;
						
						SAOI::GetArgument(inpf,texturenamesize,offset);
						
						for(new i = 0; i < texturenamesize; i++){
							SAOI::GetArgumentMod(inpf,texturename[i],offset);
						}
						texturename[texturenamesize] = EOS;

						SAOI::GetByteInteger(inpf,materialcolor,offset);
						
						SetDynamicObjectMaterial(STREAMER_TAG_OBJECT:elementid,mat,texture_modelid,txdname,texturename,materialcolor);
						SAOI::File[index][SAOI::cnt_material]++;
					}
				}
				
				//Get Materials Text
				SAOI::GetValue(inpf,material_text_used,offset);
	
				for(new mat = 0; mat < 16; mat++){
					if(SAOI::GetValueBit(material_text_used,mat) == 1){
						
						SAOI::GetValue(inpf,textsize,offset);
						for(new i = 0; i < textsize; i++){
							SAOI::GetArgumentMod(inpf,text[i],offset);
						}
						text[textsize] = EOS;
						
						SAOI::GetArgument(inpf,materialsize,offset);
						
						SAOI::GetArgument(inpf,fontfacesize,offset);
						for(new i = 0; i < fontfacesize; i++){
							SAOI::GetArgumentMod(inpf,fontface[i],offset);
						}
						fontface[fontfacesize] = EOS;
						
						SAOI::GetArgument(inpf,fontsize,offset);
						SAOI::GetArgument(inpf,bold,offset);
						
						SAOI::GetByteInteger(inpf,fontcolor,offset);
						SAOI::GetByteInteger(inpf,backcolor,offset);
						
						SAOI::GetArgument(inpf,textalignment,offset);
						
						SetDynamicObjectMaterialText(STREAMER_TAG_OBJECT:elementid,mat,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
						SAOI::File[index][SAOI::cnt_materialtext]++;
					}
				}
				if(SAOI::File[index][SAOI::offset_object] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_object] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_OBJECT,elementid,E_STREAMER_EXTRA_ID,extraid);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer::ToggleItemInvAreas(STREAMER_TYPE_OBJECT,elementid,1);
				}
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_NO_CAMERA_COL) == 1){
					SetDynamicObjectNoCameraCol(STREAMER_TAG_OBJECT:elementid);
				}
				SAOI::File[index][SAOI::cnt_object]++;
				#if defined SAOI_ColAndreas
					if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_COLANDREAS) == 1){
						col_elementid = _:ColAndreas::CreateObject(modelid,x,y,z,rx,ry,rz,true);
						ColAndreas::SetObjectExtraID(col_elementid,ColAndreas::EXTRA_1,extraid);
						SAOI::File[index][SAOI::cnt_caobject]++;
						if(SAOI::File[index][SAOI::offset_caobject] == -1){
							SAOI::File[index][SAOI::offset_caobject] = col_elementid;
						}
					} else if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_COLSTATIC) == 1){
						ColAndreas::CreateObject(modelid,x,y,z,rx,ry,rz,false);
						SAOI::File[index][SAOI::cnt_caobject]++;
						SAOI::File[index][SAOI::is_static] = true;
					}
				#endif
				continue;
			}
			
			case SAOI_BUMPER_ACTOR: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				invulnerable = 1;
				health = 100.0;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				areaid = -1;
				priority = 0;
				element_flag = 0;
				
				SAOI::GetByteInteger(inpf,modelid,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetByteFloat(inpf,rz,offset);
			
				if(arg_count >= 6)	SAOI::GetArgument(inpf,invulnerable,offset);
				if(arg_count >= 7)	SAOI::GetByteFloat(inpf,health,offset);
				if(arg_count >= 8)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 9)	SAOI::GetByteInteger(inpf,interiorid,offset);
				if(arg_count >= 10)	SAOI::GetByteFloat(inpf,streamdistance,offset);
				if(arg_count >= 11)	SAOI::GetByteInteger(inpf,areaid,offset);
				if(arg_count >= 12)	SAOI::GetByteInteger(inpf,priority,offset);
				if(arg_count >= 13)	SAOI::GetArgument(inpf,element_flag,offset);
				
				if(areaid == -1){
					elementid = _:CreateDynamicActor(modelid,x,y,z,rz,invulnerable,health,worldid,interiorid,-1,streamdistance,STREAMER_TAG_AREA:areaid,priority);
				} else {
					elementid = _:CreateDynamicActor(modelid,x,y,z,rz,invulnerable,health,worldid,interiorid,-1,streamdistance,STREAMER_TAG_AREA:DynamicAreas[areaid],priority);
				}
				
				if(SAOI::File[index][SAOI::offset_actor] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_actor] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_ACTOR,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer::ToggleItemInvAreas(STREAMER_TYPE_ACTOR,elementid,1);
				}
				SAOI::File[index][SAOI::cnt_actor]++;
				continue;
			}
			
			case SAOI_BUMPER_3D_TEXT_LABEL: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				textsize = 0;
				text = "";
				testlos = 0;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				areaid = -1;
				priority = 0;
				element_flag = 0;
				
				SAOI::GetValue(inpf,textsize,offset);
				for(new i = 0; i < textsize; i++){
					SAOI::GetArgumentMod(inpf,text[i],offset);
				}
				text[textsize] = EOS;
				
				SAOI::GetByteInteger(inpf,color,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetByteFloat(inpf,drawdistance,offset);
				
				if(arg_count >= 8)	SAOI::GetArgument(inpf,testlos,offset);
				if(arg_count >= 9)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 10)	SAOI::GetByteInteger(inpf,interiorid,offset);
				if(arg_count >= 11)	SAOI::GetByteFloat(inpf,streamdistance,offset);
				if(arg_count >= 12)	SAOI::GetByteInteger(inpf,areaid,offset);
				if(arg_count >= 13)	SAOI::GetByteInteger(inpf,priority,offset);
				if(arg_count >= 14)	SAOI::GetArgument(inpf,element_flag,offset);
				
				if(areaid == -1){
					elementid = _:_:CreateDynamic3DTextLabel(text,color,x,y,z,drawdistance,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,testlos,worldid,interiorid,-1,streamdistance,STREAMER_TAG_AREA:areaid,priority);
				} else {
					elementid = _:_:CreateDynamic3DTextLabel(text,color,x,y,z,drawdistance,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,testlos,worldid,interiorid,-1,streamdistance,STREAMER_TAG_AREA:DynamicAreas[areaid],priority);
				}
				
				if(SAOI::File[index][SAOI::offset_3dtext] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_3dtext] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer::ToggleItemInvAreas(STREAMER_TYPE_3D_TEXT_LABEL,elementid,1);
				}
				SAOI::File[index][SAOI::cnt_3dtext]++;
				continue;
			}
			
			case SAOI_BUMPER_PICKUP: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID, type = 0, worldid = -1, interiorid = -1, streamdistance = STREAMER_OBJECT_SD,
				areaid = -1, priority = 0, element_flag = 0;
		
				SAOI::GetByteInteger(inpf,modelid,offset);
				SAOI::GetArgument(inpf,type,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				
				if(arg_count >= 6)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 7)	SAOI::GetByteInteger(inpf,interiorid,offset);
				if(arg_count >= 8)	SAOI::GetByteFloat(inpf,streamdistance,offset);
				if(arg_count >= 9)	SAOI::GetByteInteger(inpf,areaid,offset);
				if(arg_count >= 10)	SAOI::GetByteInteger(inpf,priority,offset);
				if(arg_count >= 11)	SAOI::GetArgument(inpf,element_flag,offset);

				if(areaid == -1){
					elementid = _:CreateDynamicPickup(modelid,type,x,y,z,worldid,interiorid,-1,streamdistance,STREAMER_TAG_AREA:areaid,priority);
				} else {
					elementid = _:CreateDynamicPickup(modelid,type,x,y,z,worldid,interiorid,-1,streamdistance,STREAMER_TAG_AREA:DynamicAreas[areaid],priority);
				}
				
				if(SAOI::File[index][SAOI::offset_pickup] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_pickup] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_PICKUP,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer::ToggleItemInvAreas(STREAMER_TYPE_PICKUP,elementid,1);
				}
				SAOI::File[index][SAOI::cnt_pickup]++;
				continue;
			}

			case SAOI_BUMPER_MAPICON: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				style = 0;
				areaid = -1;
				priority = 0;
				element_flag = 0;
				
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetArgument(inpf,type,offset);
				SAOI::GetByteInteger(inpf,color,offset);
				
				if(arg_count >= 6)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 7)	SAOI::GetByteInteger(inpf,interiorid,offset);
				if(arg_count >= 8)	SAOI::GetByteFloat(inpf,streamdistance,offset);
				if(arg_count >= 9)	SAOI::GetArgument(inpf,style,offset);
				if(arg_count >= 10)	SAOI::GetByteInteger(inpf,areaid,offset);
				if(arg_count >= 11)	SAOI::GetByteInteger(inpf,priority,offset);
				if(arg_count >= 12)	SAOI::GetArgument(inpf,element_flag,offset);

				if(areaid == -1){
					elementid = _:CreateDynamicMapIcon(x,y,z,type,color,worldid,interiorid,-1,streamdistance,style,STREAMER_TAG_AREA:areaid,priority);
				} else {
					elementid = _:CreateDynamicMapIcon(x,y,z,type,color,worldid,interiorid,-1,streamdistance,style,STREAMER_TAG_AREA:DynamicAreas[areaid],priority);
				}
				
				if(SAOI::File[index][SAOI::offset_mapicon] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_mapicon] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_MAP_ICON,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer::ToggleItemInvAreas(STREAMER_TYPE_MAP_ICON,elementid,1);
				}
				SAOI::File[index][SAOI::cnt_mapicon]++;
				continue;
			}

			case SAOI_BUMPER_VEHICLE: {
				SAOI::GetValue(inpf,type,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetByteFloat(inpf,rz,offset);
				SAOI::GetValue(inpf,color1,offset);
				SAOI::GetValue(inpf,color2,offset);
				SAOI::GetByteInteger(inpf,respawn_delay,offset);
				SAOI::GetArgument(inpf,addsiren,offset);
				SAOI::GetByteInteger(inpf,worldid,offset);
				SAOI::GetByteInteger(inpf,interiorid,offset);
				
				if(color1 == 0xFFFF) color1 = -1;
				if(color2 == 0xFFFF) color2 = -1;
				
				elementid = _:CreateVehicle(type,x,y,z,rz,color1,color2,respawn_delay,addsiren);
				if(elementid == INVALID_VEHICLE_ID){
					printf("[SAOI DEBUG] Can't create vehicle, limit exceeded !");
				} else {
					if(interiorid != 0) LinkVehicleToInterior(elementid,interiorid);
					if(worldid != 0) SetVehicleVirtualWorld(elementid,worldid);
					SAOI::Vehicles[elementid] = index;
					
					CallRemoteFunction("SAOI_OnVehicleCreated","d",elementid);
					CallRemoteFunction("EVF_ImportVehicle","ddffffddddd",elementid,type,x,y,z,rz,color1,color2,worldid,interiorid,0);
					
					if(SAOI::File[index][SAOI::offset_vehicle] == 0){
						SAOI::File[index][SAOI::offset_mapicon] = elementid;
					}
					
					SAOI::File[index][SAOI::cnt_vehicle]++;
				}
				continue;
			}

			case SAOI_BUMPER_AREA_CIRCLE: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,size,offset);
				
				if(arg_count >= 5)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 6)	SAOI::GetByteInteger(inpf,interiorid,offset);

				elementid = _:CreateDynamicCircle(x,y,size,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOI::File[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_area] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOI::File[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_CYLINDER: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,minz,offset);
				SAOI::GetByteFloat(inpf,maxz,offset);
				SAOI::GetByteFloat(inpf,size,offset);
				
				if(arg_count >= 7)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 8)	SAOI::GetByteInteger(inpf,interiorid,offset);
				
				elementid = _:CreateDynamicCylinder(x,y,minz,maxz,size,worldid,interiorid,-1);
				
				DynamicAreas[areaid] = elementid;
				
				if(SAOI::File[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_area] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOI::File[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_SPHERE: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetByteFloat(inpf,size,offset);
				
				if(arg_count >= 6)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 7)	SAOI::GetByteInteger(inpf,interiorid,offset);

				elementid = _:CreateDynamicSphere(x,y,z,size,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOI::File[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_area] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOI::File[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_RECTANGLE: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid,offset);
				SAOI::GetByteFloat(inpf,minx,offset);
				SAOI::GetByteFloat(inpf,miny,offset);
				SAOI::GetByteFloat(inpf,maxx,offset);
				SAOI::GetByteFloat(inpf,maxy,offset);
				
				if(arg_count >= 6)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 7)	SAOI::GetByteInteger(inpf,interiorid,offset);
				
				elementid = _:CreateDynamicRectangle(minx,miny,maxx,maxy,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOI::File[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_area] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOI::File[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_CUBOID: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid,offset);
				SAOI::GetByteFloat(inpf,minx,offset);
				SAOI::GetByteFloat(inpf,miny,offset);
				SAOI::GetByteFloat(inpf,minz,offset);
				SAOI::GetByteFloat(inpf,maxx,offset);
				SAOI::GetByteFloat(inpf,maxy,offset);
				SAOI::GetByteFloat(inpf,maxz,offset);
				
				if(arg_count >= 8)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 9)	SAOI::GetByteInteger(inpf,interiorid,offset);

				elementid = _:CreateDynamicCube(minx,miny,minz,maxx,maxy,maxz,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOI::File[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_area] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOI::File[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_POLYGON: {
				SAOI::GetArgument(inpf,arg_count,offset);
				
				//Reset Data
				elementid = _:INVALID_STREAMER_ID;
				minz = -FLOAT_INFINITY;
				maxz = FLOAT_INFINITY;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid,offset);
				SAOI::GetValue(inpf,max_points,offset);
				
				for(new k = 0; k < max_points; k++){
					SAOI::GetByteFloat(inpf,Polygon_Points[k],offset);
				}
				
				if(arg_count >= 4)	SAOI::GetByteFloat(inpf,minz,offset);
				if(arg_count >= 5)	SAOI::GetByteFloat(inpf,maxz,offset);
				if(arg_count >= 6)	SAOI::GetByteInteger(inpf,worldid,offset);
				if(arg_count >= 7)	SAOI::GetByteInteger(inpf,interiorid,offset);

				elementid = _:CreateDynamicPolygon(Polygon_Points,minz,maxz,max_points,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOI::File[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOI::File[index][SAOI::offset_area] = elementid;
				}
				Streamer::SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOI::File[index][SAOI::cnt_area]++;
				continue;
			}
			
			case SAOI_BUMPER_REMOVEBUILDING: {
				//RemoveBuildingForPlayer
				SAOI::GetByteInteger(inpf,modelid,offset);
				SAOI::GetByteFloat(inpf,x,offset);
				SAOI::GetByteFloat(inpf,y,offset);
				SAOI::GetByteFloat(inpf,z,offset);
				SAOI::GetByteFloat(inpf,streamdistance,offset);
				SAOI::RemoveBuilding(index,modelid,x,y,z,streamdistance);
				SAOI::File[index][SAOI::cnt_removebuilding]++;
				continue;
			}
			case SAOI_BUMPER_CREATED: {
				new year,month,day,hour,minute,second;
				SAOI::MergeValue(year,0,0,SAOI::IntMod(fgetchar(inpf,0,false)),SAOI::IntMod(fgetchar(inpf,0,false))), offset +=2;
				SAOI::GetArgumentMod(inpf,month,offset);
				SAOI::GetArgumentMod(inpf,day,offset);
				SAOI::GetArgumentMod(inpf,hour,offset);
				SAOI::GetArgumentMod(inpf,minute,offset);
				SAOI::GetArgumentMod(inpf,second,offset);
				format(SAOI::File[index][SAOI::created],32,"%04d.%02d.%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
				continue;
			}
			case SAOI_BUMPER_POS: {
				SAOI::GetByteFloat(inpf,SAOI::File[index][SAOI::X],offset);
				SAOI::GetByteFloat(inpf,SAOI::File[index][SAOI::Y],offset);
				SAOI::GetByteFloat(inpf,SAOI::File[index][SAOI::Z],offset);
				SAOI::GetByteFloat(inpf,SAOI::File[index][SAOI::A],offset);
				SAOI::GetByteInteger(inpf,SAOI::File[index][SAOI::VW],offset);
				SAOI::GetByteInteger(inpf,SAOI::File[index][SAOI::INT],offset);
				continue;
			}
			case SAOI_BUMPER_IP: {
				new serv_ipsum[4], saoi_ipsum[4], serv_ip[16];
				GetServerVarAsString("bind",serv_ip,sizeof(serv_ip));
				for(new i = 0; i < 4; i++){
					SAOI::GetArgument(inpf,saoi_ipsum[i],offset);
				}
				sscanf(serv_ip,"p<.>dddd",serv_ipsum[0],serv_ipsum[1],serv_ipsum[2],serv_ipsum[3]);
				if(SAOI::Comp(serv_ipsum[0],saoi_ipsum[3]) || SAOI::Comp(serv_ipsum[1],saoi_ipsum[2]) || SAOI::Comp(serv_ipsum[2],saoi_ipsum[1]) || SAOI::Comp(serv_ipsum[3],saoi_ipsum[0])){
					fclose(inpf);
					fread(File:0xBABE,tmp_hash);
					return SAOI_ERROR_INVALID_SERVER_IP;
				}
				continue;
			}
			case SAOI_BUMPER_PORT: {
				new serv_port = GetServerVarAsInt("port"), serv_portsum[4], saoi_portsum[4];
				for(new i = 0; i < 4; i++){
					SAOI::GetArgument(inpf,saoi_portsum[i],offset);
				}
				SAOI::ExtractValue(serv_port,serv_portsum[0],serv_portsum[1],serv_portsum[2],serv_portsum[3]);
				if(SAOI::Comp(serv_portsum[0],saoi_portsum[3]) || SAOI::Comp(serv_portsum[1],saoi_portsum[2]) || SAOI::Comp(serv_portsum[2],saoi_portsum[1]) || SAOI::Comp(serv_portsum[3],saoi_portsum[0])){
					fclose(inpf);
					fread(File:0xBABE,tmp_hash);
					return SAOI_ERROR_INVALID_SERVER_PORT;
				}
				continue;
			}
			case SAOI_BUMPER_EOF: {
				SAOI::File[index][SAOI::write_lock] = true;
				break;
			}
			default: {
				SAOI::CleanupElements(index);
				SAOI::File[index][SAOI::status] = false;
				
				new d_raw[8], foffset = offset-1;
				for(new i = 0; i < 8; i++){
					if(offset < asize){
						d_raw[i] = fgetchar(inpf,0,false), offset++;
					} else {
						d_raw[i] = 0;
					}
				}

				fclose(inpf);
				
				//Print Error Backtrace
				printf(" ");
				printf("[SAOI DEBUG] Parse Error '%s' Offset 0x%08x Argument: 0x%02x Buffer: %02x %02x %02x %02x %02x %02x %02x %02x",name,foffset,arg_count,d_raw[0],d_raw[1],d_raw[2],d_raw[3],d_raw[4],d_raw[5],d_raw[6],d_raw[7]);
				printf("[SAOI DEBUG] File Size: 0x%08x",asize);
				if(isnull(SAOI::File[index][SAOI::created])){
					printf("[SAOI DEBUG] File Creation Date: (null)");
				} else {
					printf("[SAOI DEBUG] File Creation Date: %s",SAOI::File[index][SAOI::created]);
				}
				printf(" ");
				return SAOI_ERROR_INVALID_ARG_COUNT;
			}
		}
	}
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			CallRemoteFunction("SAOI_OnRemovedBuildings","dd",i,SAOI::UpdateBuildingsForPlayer(i,index));
		}
	}
	
	SAOI::File[index][SAOI::file_size] = flength(inpf);
	
	fclose(inpf);
	
	load_time = GetTickCount()-NTTime;
	
	SAOI::File[index][SAOI::load_time] = load_time;
	SAOI::File[index][SAOI::active_tick] = GetTickCount();
	
	if(save_logs){
		new buffer[256];
		format(buffer,sizeof buffer,"File %s has been loaded as %s in %d ms",name,(SAOI::IsStatic(index)?("static"):("dynamic")),load_time);
		printf(buffer);
		format(buffer,sizeof buffer,"Author: %s Version: %s Items: %d",SAOI::File[index][SAOI::author],SAOI::File[index][SAOI::version],SAOI::CountAllElementsByIndex(index));
		printf(buffer);
		if(!isnull(SAOI::File[index][SAOI::description])){
			format(buffer,sizeof buffer,"Description: %s",SAOI::File[index][SAOI::description]);
			printf(buffer);
		}
		printf(" ");
	}
	return index;
}

SAOI::Public:: SAOI::UnloadObjectImage(index){
	if(!SAOI::Access) return 0;
	if(!SAOI::IsLoaded(index) || SAOI::IsStatic(index)) return 0;
	SAOI::CleanupElements(index);
	SAOI::File[index] = SAOI::Construct();
	return 1;
}

SAOI::Public:: SAOI::ToggleVisibleItems(const name[],playerid,type,toggle){
	if(!SAOI::Access) return 0;
	new index;
	if(!SAOI::IsFileLoaded(name,index)) return 0;
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index), cnt = 0;
	
	switch(type){
		case STREAMER_TYPE_OBJECT: {
			//Objects
			if(SAOI::File[index][SAOI::cnt_object] > 0){
				new max_idx = SAOI::File[index][SAOI::cnt_object], i = SAOI::File[index][SAOI::offset_object], j = Streamer::GetUpperBound(STREAMER_TYPE_OBJECT);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicObject(STREAMER_TAG_OBJECT:i)){
						if(Streamer::GetIntData(STREAMER_TYPE_OBJECT,STREAMER_TAG_OBJECT:i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer::ToggleItem(playerid,type,STREAMER_TAG_OBJECT:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_PICKUP: {
			//Pickups
			if(SAOI::File[index][SAOI::cnt_pickup] > 0){
				new max_idx = SAOI::File[index][SAOI::cnt_pickup], i = SAOI::File[index][SAOI::offset_pickup], j = Streamer::GetUpperBound(STREAMER_TYPE_PICKUP);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicPickup(STREAMER_TAG_PICKUP:i)){
						if(Streamer::GetIntData(STREAMER_TYPE_PICKUP,STREAMER_TAG_PICKUP:i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer::ToggleItem(playerid,type,STREAMER_TAG_PICKUP:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_MAP_ICON: {
			//MapIcons
			if(SAOI::File[index][SAOI::cnt_mapicon] > 0){
				new max_idx = SAOI::File[index][SAOI::cnt_mapicon], i = SAOI::File[index][SAOI::offset_mapicon], j = Streamer::GetUpperBound(STREAMER_TYPE_MAP_ICON);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicMapIcon(STREAMER_TAG_MAP_ICON:i)){
						if(Streamer::GetIntData(STREAMER_TYPE_MAP_ICON,STREAMER_TAG_MAP_ICON:i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer::ToggleItem(playerid,type,STREAMER_TAG_MAP_ICON:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_3D_TEXT_LABEL: {
			//3DTextLabels
			if(SAOI::File[index][SAOI::cnt_3dtext] > 0){
				new max_idx = SAOI::File[index][SAOI::cnt_3dtext], i = SAOI::File[index][SAOI::offset_3dtext], j = Streamer::GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL);
				while(i <= j && max_idx > 0){
					if(IsValidDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:i)){
						if(Streamer::GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer::ToggleItem(playerid,type,STREAMER_TAG_3D_TEXT_LABEL:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_AREA: {
			//Areas
			if(SAOI::File[index][SAOI::cnt_area] > 0){
				new max_idx = SAOI::File[index][SAOI::cnt_area], i = SAOI::File[index][SAOI::offset_area], j = Streamer::GetUpperBound(STREAMER_TYPE_AREA);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicArea(STREAMER_TAG_AREA:i)){
						if(Streamer::GetIntData(STREAMER_TYPE_AREA,STREAMER_TAG_AREA:i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer::ToggleItem(playerid,type,STREAMER_TAG_AREA:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_ACTOR: {
			//Actors
			if(SAOI::File[index][SAOI::cnt_actor] > 0){
				new max_idx = SAOI::File[index][SAOI::cnt_actor], i = SAOI::File[index][SAOI::offset_actor], j = Streamer::GetUpperBound(STREAMER_TYPE_ACTOR);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicActor(STREAMER_TAG_ACTOR:i)){
						if(Streamer::GetIntData(STREAMER_TYPE_ACTOR,STREAMER_TAG_ACTOR:i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer::ToggleItem(playerid,type,STREAMER_TAG_ACTOR:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
	}
	return cnt;
}

new bool:CRC_SAOIInit = true,
	bool:CRC_SAOIExit = true;

SAOI::Public:: SAOI_RemoteCheck(){
	#if defined LOCK_SAOI_MEMORY
		if(GetSVarInt("ADM:SAOI:LOCK") == 0){
			SetSVarInt("ADM:SAOI:LOCK",1);
			SetSVarString("ADM:SAOI:FM",LOCK_SAOI_MEMORY);
			printf("[ADM] Info: SAOI has been attached to %s",LOCK_SAOI_MEMORY);
			SAOI::Access = true;
		} else {
			new saoi_fm_name[64];
			GetSVarString("ADM:SAOI:FM",saoi_fm_name,64);
			printf("[SAOI DEBUG] SAOI.inc was blocked by %s !",saoi_fm_name);
			printf("[SAOI DEBUG] You can not modify the memory remotely");
			SAOI::Access = false;
		}
	#else
		if(GetSVarInt("ADM:SAOI:LOCK") == 1){
			new saoi_fm_name[64];
			GetSVarString("ADM:SAOI:FM",saoi_fm_name,64);
			printf("[SAOI DEBUG] SAOI.inc was blocked by %s !",saoi_fm_name);
			printf("[SAOI DEBUG] You can not modify the memory remotely");
			SAOI::Access = false;
		} else {
			SAOI::Access = true;
		}
	#endif
	return 1;
}

SAOI::Function:: SAOI::Init(){
	CallRemoteFunction("SAOI_RemoteCheck","");
}

SAOI::Function:: SAOI::Exit(){
	#if defined LOCK_SAOI_MEMORY
		SetSVarInt("ADM:SAOI:LOCK",0);
		DeleteSVar("ADM:SAOI:FM");
		printf("[ADM] Info: SAOI has been detached from %s",LOCK_SAOI_MEMORY);
	#endif
	
	//Vehicles
	new prot_i = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		prot_i = i;
		if(IsValidVehicle(i)){
			if(SAOI::Vehicles[i] != INVALID_SAOI_FILE){
				DestroyVehicle(prot_i);
				CallRemoteFunction("SAOI_OnVehicleDestroyed","d",i);
				SAOI::Vehicles[i] = INVALID_SAOI_FILE;
			}
		}
	}
}

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	SAOI::PlayerFirstSpawn[playerid] = true;
	#if defined SAOI_OnPlayerConnect
		SAOI_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAOI_OnPlayerConnect
#if defined SAOI_OnPlayerConnect
	forward SAOI_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	if(SAOI::PlayerFirstSpawn[playerid]){
		SAOI::PlayerFirstSpawn[playerid] = false;
		CallRemoteFunction("SAOI_OnRemovedBuildings","dd",playerid,SAOI::RemoveBuildingsForPlayer(playerid));
	}
	#if defined SAOI_OnPlayerSpawn
		SAOI_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn SAOI_OnPlayerSpawn
#if defined SAOI_OnPlayerSpawn
	forward SAOI_OnPlayerSpawn(playerid);
#endif

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_SAOIInit){
		CRC_SAOIInit = false;
		SAOI::Init();
	}
	#if defined SAOI_OnFilterScriptInit
		SAOI_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SAOI_OnFilterScriptInit
#if defined SAOI_OnFilterScriptInit
	forward SAOI_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_SAOIInit){
		CRC_SAOIInit = false;
		SAOI::Init();
	}
	#if defined SAOI_OnGameModeInit
		SAOI_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SAOI_OnGameModeInit
#if defined SAOI_OnGameModeInit
	forward SAOI_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_SAOIExit){
		CRC_SAOIExit = false;
		SAOI::Exit();
	}
	#if defined SAOI_OnFilterScriptExit
		SAOI_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SAOI_OnFilterScriptExit
#if defined SAOI_OnFilterScriptExit
	forward SAOI_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_SAOIExit){
		CRC_SAOIExit = false;
		SAOI::Exit();
	}
	#if defined SAOI_OnGameModeExit
		SAOI_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit SAOI_OnGameModeExit
#if defined SAOI_OnGameModeExit
	forward SAOI_OnGameModeExit();
#endif

//EOF