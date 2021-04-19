/*
 Graffiti.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: Robin

 Website: https://adm.ct8.pl

 Plugins: Streamer
 Modules: 3DTryg

 File Version: 1.0.3
 Streamer Version: 2.9.4
 3DTryg Version: 4.8.6

 Functions:
 Graffiti::Init();
 Graffiti::CountGangTags(gangid);
 Graffiti::SetGang(mobid,gangid);
 Graffiti::SetGangName(mobid,color,name[]);
 Graffiti::ResetGangTags();

 Callbacks:
 OnGraffitiTagChanged(mobid,playerid,gangid,old_gangid);
 OnGraffitiTagCreated(mobid,gangid);
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

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v4.8.6
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v4.8.6
#elseif (TRYG3D_VERSION < 40806)
	#error [ADM] Update you 3DTryg.inc to v4.8.6
#endif

#if defined _graffiti_los_santos
	#endinput
#endif
#define _graffiti_los_santos
#define DYNAMIC_FILTERSCRIPT						"ALS:HOOK:METHOD"

#define Graffiti:: 						Graffiti_

#if !defined GRAFFITI_DEFAULT_GANG
	#define GRAFFITI_DEFAULT_GANG		0
#endif

#if !defined GRAFFITI_DEFAULT_COLOR
	#define GRAFFITI_DEFAULT_COLOR 		0x003D00FF
#endif

#if !defined GRAFFITI_DEFAULT_NAME
	#define GRAFFITI_DEFAULT_NAME		"Sekhmete Axion Rush"
#endif

#define MAX_GRAFFITI 					100
#define GRAFFITI_EXTRA_ID_OFFSET		5000000
#define GRAFFITI_DATA_FILE 				"graffiti.bin"

enum Graffiti::Enum {
	STREAMER_TAG_OBJECT:Graffiti::objectid,
	Graffiti::gangid,
	STREAMER_TAG_AREA:Graffiti::areaid,
	Graffiti::playerid,
	Graffiti::tick
};

new Graffiti::Data[MAX_GRAFFITI][Graffiti::Enum],
	bool:Graffiti::Loaded = false,
	Graffiti::RemoveBuilding[] = {1490, 1524, 1525, 1526, 1527, 1528, 1529, 1530, 1531};

forward OnGraffitiTagChanged(mobid,playerid,gangid,old_gangid);
forward OnGraffitiTagCreated(mobid,gangid);
forward Graffiti::GetPlayerGang(playerid);

#define Graffiti_RGBAToARGB(%0)						((((%0) << 24) & 0xFF000000) | (((%0) >>> 8) & 0xFFFFFF))
#define Graffiti_GetItemAdress(%0)					(48+((%0)*20))

#define Graffiti_ExtractValue(%0,%1,%2,%3,%4)		((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))

#define Graffiti_MergeValue(%0,%1,%2,%3,%4)			((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define Graffiti_MergeFloat(%0,%1,%2,%3,%4)			((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#if defined _Data_Convert
	#define Graffiti_strreplace strreplace
#else
	stock Graffiti::strreplace(string[],const search[],const replacement[],bool:ignorecase = false,pos = 0,limit = -1,maxlength = sizeof(string)){
		if(limit == 0) return 0;

		new sublen = strlen(search),
			replen = strlen(replacement),
			bool:packed = ispacked(string),
			maxlen = maxlength,
			len = strlen(string),
			count = 0;
		
		if(packed) maxlen *= 4;
		if(!sublen) return 0;
		
		while(-1 != (pos = strfind(string, search, ignorecase, pos))){
			strdel(string, pos, pos + sublen);
			len -= sublen;
			
			if(replen && len + replen < maxlen){
				strins(string, replacement, pos, maxlength);

				pos += replen;
				len += replen;
			}

			// Is there a limit of number of replacements, if so, did we break it?
			if(limit != -1 && ++count >= limit)	break;
		}

		return count;
	}
#endif

stock Graffiti::CountGangTags(gangid){
	new Graffiti::count;
	for(new mobid = 0; mobid < MAX_GRAFFITI; mobid++){
		if(Graffiti::Data[mobid][Graffiti::gangid] == gangid){
			Graffiti::count++;
		}
	}
	return Graffiti::count;
}

stock Graffiti::Init(){
	if(Graffiti::Loaded) return 0;
	if(!fexist(GRAFFITI_DATA_FILE)){
		printf("[ADM] Error: Cannot load file '/scriptfiles/%s' file not exist",GRAFFITI_DATA_FILE);
		return 0;
	}
	new File:inpf = fopen(GRAFFITI_DATA_FILE,io_read);
	if(!inpf){
		printf("[ADM] Error: Cannot open file '/scriptfiles/%s' access denied",GRAFFITI_DATA_FILE);
		return 0;
	}
	printf("[ADM] Info: Load Los Santos Gang Graffiti for SA:MP 0.3.7 by Abyss Morgan",GRAFFITI_DATA_FILE);
	fseek(inpf,Graffiti::GetItemAdress(0),seek_start);
	new Float:x, Float:y, Float:z, Float:rz, gangid, new_name[64];
	format(new_name,sizeof(new_name),"%s",GRAFFITI_DEFAULT_NAME);
	Graffiti::strreplace(new_name," ","\n");
	for(new mobid = 0; mobid < MAX_GRAFFITI; mobid++){
		Graffiti::MergeValue(gangid,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
		Graffiti::MergeFloat(x,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
		Graffiti::MergeFloat(y,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
		Graffiti::MergeFloat(z,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
		Graffiti::MergeFloat(rz,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
		
		rz = Tryg3D::CompressRotation(rz+180.0);
		
		Graffiti::Data[mobid][Graffiti::gangid] = gangid;
		Graffiti::Data[mobid][Graffiti::playerid] = INVALID_PLAYER_ID;
		
		Graffiti::Data[mobid][Graffiti::objectid] = CreateDynamicObject(19482,x,y,z,0.0,0.0,rz,0,0);
		SetDynamicObjectMaterialText(Graffiti::Data[mobid][Graffiti::objectid],0,new_name,OBJECT_MATERIAL_SIZE_256x256,"Blackadder ITC",35,1,Graffiti::RGBAToARGB(GRAFFITI_DEFAULT_COLOR),0,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
		
		Graffiti::Data[mobid][Graffiti::areaid] = CreateDynamicSphere(x,y,z,2.0,0,0);
		Streamer::SetIntData(STREAMER_TYPE_AREA,Graffiti::Data[mobid][Graffiti::areaid],E_STREAMER_EXTRA_ID,(mobid+GRAFFITI_EXTRA_ID_OFFSET));
		
		CallLocalFunction("OnGraffitiTagCreated","dd",mobid,gangid);
	}
	fclose(inpf);
	Graffiti::Loaded = true;
	return 1;
}

stock Graffiti::SetGang(mobid,gangid){
	Graffiti::Data[mobid][Graffiti::gangid] = gangid;
	Graffiti::Data[mobid][Graffiti::playerid] = INVALID_PLAYER_ID;
	if(gangid == GRAFFITI_DEFAULT_GANG){
		new new_name[64];
		format(new_name,sizeof(new_name),"%s",GRAFFITI_DEFAULT_NAME);
		Graffiti::strreplace(new_name," ","\n");
		SetDynamicObjectMaterialText(Graffiti::Data[mobid][Graffiti::objectid],0,new_name,OBJECT_MATERIAL_SIZE_256x256,"Blackadder ITC",35,1,Graffiti::RGBAToARGB(GRAFFITI_DEFAULT_COLOR),0,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	}
	new File:outf = fopen(GRAFFITI_DATA_FILE,io_readwrite);
	if(!outf){
		printf("[ADM] Error: Cannot open file '/scriptfiles/%s' access denied",GRAFFITI_DATA_FILE);
		return 0;
	}
	fseek(outf,Graffiti::GetItemAdress(mobid),seek_start);
	new int1, int2, int3, int4;
	Graffiti::ExtractValue(gangid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	fclose(outf);
	return 1;
}

stock Graffiti::SetGangName(mobid,color,name[]){
	if(strlen(name) < 1) return 0;
	new new_name[64];
	format(new_name,sizeof(new_name),"%s",name);
	Graffiti::strreplace(new_name," ","\n");
	SetDynamicObjectMaterialText(Graffiti::Data[mobid][Graffiti::objectid],0,new_name,OBJECT_MATERIAL_SIZE_256x256,"Blackadder ITC",35,1,Graffiti::RGBAToARGB(color),0,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	return 1;
}

stock Graffiti::ResetGangTags(){
	if(!fexist(GRAFFITI_DATA_FILE)){
		printf("[ADM] Error: Cannot load file '/scriptfiles/%s' file not exist",GRAFFITI_DATA_FILE);
		return 0;
	}
	new File:outf = fopen(GRAFFITI_DATA_FILE,io_readwrite);
	if(!outf){
		printf("[ADM] Error: Cannot open file '/scriptfiles/%s' access denied",GRAFFITI_DATA_FILE);
		return 0;
	}
	new new_name[64];
	format(new_name,sizeof(new_name),"%s",GRAFFITI_DEFAULT_NAME);
	Graffiti::strreplace(new_name," ","\n");
	
	new int1, int2, int3, int4;
	Graffiti::ExtractValue(GRAFFITI_DEFAULT_GANG,int1,int2,int3,int4);
	for(new mobid = 0; mobid < MAX_GRAFFITI; mobid++){
		fseek(outf,Graffiti::GetItemAdress(mobid),seek_start);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
		Graffiti::Data[mobid][Graffiti::gangid] = GRAFFITI_DEFAULT_GANG;
		Graffiti::Data[mobid][Graffiti::playerid] = INVALID_PLAYER_ID;
		
		SetDynamicObjectMaterialText(Graffiti::Data[mobid][Graffiti::objectid],0,new_name,OBJECT_MATERIAL_SIZE_256x256,"Blackadder ITC",35,1,Graffiti::RGBAToARGB(GRAFFITI_DEFAULT_COLOR),0,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	}
	fclose(outf);
	return 1;
}

//Hook: OnPlayerUpdate
public OnPlayerUpdate(playerid){
	if(GetPlayerWeapon(playerid) == 41 && Graffiti::GetPlayerGang(playerid) != GRAFFITI_DEFAULT_GANG){
		new max_areas = GetPlayerNumberDynamicAreas(playerid);
		if(max_areas){
			new keys, updown, leftright, STREAMER_TAG_AREA:player_areas[64], mobid, Float:x, Float:y, Float:z, gangid;
			gangid = Graffiti::GetPlayerGang(playerid);
			GetPlayerKeys(playerid,keys,updown,leftright);
			GetPlayerDynamicAreas(playerid,player_areas,max_areas);
			for(new k = 0; k < max_areas; k++){
				mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID) - GRAFFITI_EXTRA_ID_OFFSET;
				if(mobid >= 0 && mobid < MAX_GRAFFITI){
					if(Graffiti::Data[mobid][Graffiti::gangid] != gangid){
						if(player_areas[k] == Graffiti::Data[mobid][Graffiti::areaid]){
							GetDynamicObjectPos(Graffiti::Data[mobid][Graffiti::objectid],x,y,z);
							if(IsPlayerAimingAt(playerid,x,y,z,3.0)){
								if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,5.0,x,y,z)){
									if(Graffiti::Data[mobid][Graffiti::playerid] != playerid){
										Graffiti::Data[mobid][Graffiti::playerid] = playerid;
										Graffiti::Data[mobid][Graffiti::tick] = GetTickCount() + 3000;
									} else if(GetTickCount() >= Graffiti::Data[mobid][Graffiti::tick] && Graffiti::Data[mobid][Graffiti::tick] != 0){
										Graffiti::SetGang(mobid,gangid);
										CallLocalFunction("OnGraffitiTagChanged","ddd",mobid,playerid,gangid,Graffiti::Data[mobid][Graffiti::gangid]);
									}
								} else {
									Graffiti::Data[mobid][Graffiti::tick] = GetTickCount() + 3000;
								}
							}
						}
					}
				}
				
				mobid = -1;
			}
		}
	}
	#if defined GF_OnPlayerUpdate
		GF_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate GF_OnPlayerUpdate
#if defined GF_OnPlayerUpdate
	forward GF_OnPlayerUpdate(playerid);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	
	//Spray Tag
	for(new i = 0, j = sizeof(Graffiti::RemoveBuilding); i < j; i++){
		RemoveBuildingForPlayer(playerid,Graffiti::RemoveBuilding[i],0.0,0.0,0.0,20000.0);
	}
	
	#if defined GF_OnPlayerConnect
		GF_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect GF_OnPlayerConnect
#if defined GF_OnPlayerConnect
	forward GF_OnPlayerConnect(playerid);
#endif

//EOF
