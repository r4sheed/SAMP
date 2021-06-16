#define LOCK_SAOI_MEMORY				"Texture Studio"

//Check Version SAOI.inc
#if !defined _SAOI_LOADER
	#error This include required SAOI.inc v2.2.0 (8.ct8.pl/d/SAOI)
#elseif !defined SAOI_LOADER_VERSION
	#error Update your SAOI.inc to v2.2.0 (8.ct8.pl/d/SAOI)
#elseif (SAOI_LOADER_VERSION < 20200)
	#error Update your SAOI.inc to v2.2.0 (8.ct8.pl/d/SAOI)
#endif

YCMD:saoisave(playerid,params[]){
	new file_name[MAX_SAOI_NAME_SIZE];
	if(sscanf(params,"s[60] s[32]",file_name,saoi_author)) return SendClientMessage(playerid,0xFFFFFFFF,"Usage: /saoisave <file name> <author> (Your pos is a spawn)");
	
	new saoi_author[MAX_SAOI_AUTHOR_SIZE], SAOI:edi;
	
	//Create SAOI File, remove if exist
	if(fexist(file_name)) fremove(file_name);
	if((edi = SAOI::CreateFile(file_name,saoi_author,"1.0","Texture Studio Export") != SAOI_ERROR_SUCCESS){
		new buffer[256], error_name[MAX_SAOI_ERROR_NAME];
		SAOI::GetErrorName(edi,error_name);
		format(buffer,sizeof(buffer),"Cannot create SAOI File: %s",error_name);
		SendClientMessage(playerid,0xFFFFFFFF,buffer);
		return 1;
	}
	
	new Float:x,Float:y,Float:z,Float:FacingA;
	GetPlayerPos(playerid,x,y,z);
	GetPlayerFacingAngle(playerid,FacingA);
	SAOI::SetPositionFlag(file_name,x,y,z,FacingA,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
	
	SAOI::Dump(file_name);
	SendClientMessage(playerid,0xFFFFFFFF,"Done.");
	return 1;
}

SAOI::Public:: SAOI::Dump(const file_name[]){
	printf("[SAOI DUMP] Conversion Start");
	new saoi_count;

	saoi_count = 0;
	for(new i = 1, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i <= j; i++){
		if(IsValidDynamicObject(i)){
			SAOI::SaveDynamicObject(i,file_name);
			saoi_count++;
		}
	}
	printf("[SAOI DUMP] Objects converted: %d",saoi_count);
	
	saoi_count = 0;
	foreach(new i : Cars){
		SAOI::SaveVehicle(file_name,CarData[i][CarModel],CarData[i][CarSpawnX],CarData[i][CarSpawnY],CarData[i][CarSpawnZ],CarData[i][CarSpawnFA],CarData[i][CarColor1],CarData[i][CarColor2],-1,0,0,0);
		saoi_count++;
	}
	printf("[SAOI DUMP] Vehicles converted: %d",saoi_count);
	
	saoi_count = 0;
	for(new i = 0; i < MAX_REMOVE_BUILDING; i++){
		if(RemoveData[i][rModel] != 0){
			SAOI::SaveRemoveBuilding(file_name,RemoveData[i][rModel],RemoveData[i][rX],RemoveData[i][rY],RemoveData[i][rZ],RemoveData[i][rRange]);
			saoi_count++;
		}
	}
	printf("[SAOI DUMP] RemovedBuildings converted: %d",saoi_count);
	
	SAOI::SetEOF(file_name);
	SAOI::WriteHash(file_name);
	printf("[SAOI DUMP] Conversion End");
	return 1;
}