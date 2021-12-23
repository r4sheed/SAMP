#define FILTERSCRIPT
#define ENABLE_STREAMER_TAGS

#include <a_samp>
#include <ColAndreas>
#include <streamer>
#include <FCNPC>
#include <GPS>
//#include <YSF>

#define TRYG3D_ENABLE_PLAYER
#define TRYG3D_ENABLE_VEHICLE
#define TRYG3D_ENABLE_COLANDREAS
#define TRYG3D_ENABLE_STREAMER
#define TRYG3D_ENABLE_FCNPC
#define TRYG3D_ENABLE_GRENADEDETECTION
#define TRYG3D_ENABLE_VEHICLECOL
#define TRYG3D_ENABLE_UNIVERSAL
#define TRYG3D_ENABLE_CAST3D

#include <vnpc/vnpc>
#include <3DTryg/3DTryg>
#include <SWAP/SWAP>
#include <EVF/EVF>

#define MAX_LEGION_NPC 50
#include <Legion/Legion>

public OnVehicleCreated(vehicleid){
	Tryg3D::SyncVehicleCollision(vehicleid);
	return 1;
}

public OnPlayerSpawn(playerid){
	SetPlayerHealth(playerid,100.0);
	SetPlayerArmour(playerid,100.0);
	GivePlayerWeapon(playerid,31,9000);
	GivePlayerWeapon(playerid,24,9000);
	GivePlayerWeapon(playerid,27,9000);
	//GivePlayerWeapon(playerid,38,9000);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason){
    SendDeathMessage(killerid, playerid, reason);
    return 1;
}

T3D:function Legion::GetNearestCheckPoint(npcid,&Float:tx,&Float:ty,&Float:tz,Float:maxdist){
	
	return 0;
}

T3D:function Legion::GetZoneOwner(checkpointid){

	return 0;
}

stock Legion::GetRandomCaptureZone(npcid,&Float:x,&Float:y,&Float:z){
	#pragma unused npcid
	/*Tryg3D::GetPointInRectangle(500.0,500.0,3000.0,3000.0,x,y);
	while(Tryg3D::IsPointInWater(x,y,0.0)){
		Tryg3D::GetPointInRectangle(500.0,500.0,3000.0,3000.0,x,y);
	}*/
	Tryg3D::GetPointInCircle(1431.6643,1692.0281,25.0,x,y);
	ColAndreas::FindZ_For2DCoord(x,y,z);
	z += TRYG3D_CHARACTER_GROUND_Z_DIFF;
	return 1;
}

public OnPlayerEnterDynamicCP(playerid,STREAMER_TAG_CP:checkpointid){

	return 1;
}

stock bool:IsValidSkin(skinid){
	if(skinid < 0 || skinid > 311) return false;
	if(skinid == 74) return false;
	return true;
}

public OnFilterScriptInit(){
	Tryg3D::InitVehicleCollision();

	new buffer[256], Float:x, Float:y, Float:z;
	for(new i = 0; i < MAX_LEGION_NPC; i++){
		format(buffer,sizeof(buffer),"NPC_%03d",i+1);
		
		Tryg3D::GetPointInCircle(1431.6643,1692.0281,25.0,x,y);
		ColAndreas::FindZ_For2DCoord(x,y,z);
		z += TRYG3D_CHARACTER_GROUND_Z_DIFF;
		
		Legion::NPC[i] = Legion::Create(buffer,163,0x003D00FF,x,y,z,Tryg3D::RandomFloat(0.0,360.0),0,0,100.0,100.0);
		Legion::SetAgressive(Legion::NPC[i],true);
	}
	
	return 1;
}

public OnFilterScriptExit(){
	Tryg3D::ExitVehicleCollision();
	return 1;
}

#pragma dynamic 64*1024
