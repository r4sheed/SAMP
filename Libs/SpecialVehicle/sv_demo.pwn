#define FILTERSCRIPT

#define STREAMER_ENABLE_TAGS

#define TRYG3D_ENABLE_PLAYER
#define TRYG3D_ENABLE_VEHICLE
#define TRYG3D_ENABLE_UNIVERSAL
#define TRYG3D_ENABLE_CAST3D
#define TRYG3D_ENABLE_COLANDREAS
#define TRYG3D_ENABLE_STREAMER
#define TRYG3D_ENABLE_GRENADEDETECTION

#include <a_samp>
#include <izcmd>
#include <sscanf2>
#include <streamer>
#include <colandreas>
#include <EVF/EVF>
#include <3DTryg/3DTryg>
#include <ExtendedGrenade/ExtendedGrenade>
#include <Mines/Mines>
#include <Missile/Missile>
#include <VehPara/VehPara>

#define SPECIAL_VEH_USE_TEAMS	//atention if you turn on teams NO_TEAM is treated as an ordinary team
#include <SpecialVehicle/SpecialVehicle>

public OnPlayerEnterVehIntRequest(playerid,vehicleid){
	//if vehicle is owned by another team you can block enter to interior here by return 0;
	return 1;
}

public OnPlayerEnterSpecialSeat(playerid){
	GameTextForPlayer(playerid,"Press ~k~~VEHICLE_HORN~ to enable/disable special weapon",2500,4);
	return 1;
}

public OnPlayerEnterOppressor(playerid){
	GameTextForPlayer(playerid,"Hold ~k~~VEHICLE_FIREWEAPON_ALT~ for use booster",1000,4);
	return 1;
}

public OnPlayerUseCannonFail(playerid){
	GameTextForPlayer(playerid,"You cannot use cannon now",1000,4);
	return 1;
}

public OnPlayerEnterVehInterior(playerid,vehicleid,with_vehicle){
	GameTextForPlayer(playerid,"You entered to vehicle interior, press ~k~~GROUP_CONTROL_BWD~ to exit",2500,4);
	return 1;
}

public OnPlayerExitVehInterior(playerid,vehicleid,with_vehicle){
	GameTextForPlayer(playerid,"You exit from vehicle interior",2500,4);
	return 1;
}

public OnPlayerShootRocketFail(playerid){
	GameTextForPlayer(playerid,"You can shoot only aerial targets",1000,4);
	return 1;
}

public OnSpecialTrailerNotConnected(playerid){
	GameTextForPlayer(playerid,"Trailer is not connected to Truck",1000,4);
	return 1;
}

public OnPlayerShootOPRocketFail(playerid){
	GameTextForPlayer(playerid,"You can shoot only when you on air",1000,4);
	return 1;
}

public OnSpecialVehicleHasNoAmmo(playerid,vehicleid){
	GameTextForPlayer(playerid,"You don't have ammo",1000,4);
	return 1;
}

public OnSpecialTrailerAttachFail(playerid,vehicleid,trailerid){
	SendClientMessage(playerid,0xFFFFFFFF,"You can only attach MOC trailer by MOC Truck");
	return 1;
}

CMD:e(playerid){
	switch(SpecialVehicle::EnterPlayer(playerid)){
		case SPECIAL_VEH_ENTER_FAIL: {
			SendClientMessage(playerid,0xFFFFFFFF,"You are not near a special vehicle");
		}
		case SPECIAL_VEH_ENTER_SUCCES: {
			
		}
		case SPECIAL_VEH_ENTER_ONFOOT: {
			SendClientMessage(playerid,0xFFFFFFFF,"You must be on foot");
		}
		case SPECIAL_VEH_ENTER_NOT_ALLOWED: {
			SendClientMessage(playerid,0xFFFFFFFF,"You can't enter a special vehicle");
		}
	}
	return 1;
}

CMD:spawn_moc(playerid){
	
	new Float:x,Float:y,Float:z,Float:z_angle;
	GetPlayerPos(playerid,x,y,z);
	GetPlayerFacingAngle(playerid,z_angle);
	SpecialVehicle::CreateMOC(x,y,z,z_angle,-1,0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid)); 
	
	return 1;
}

public OnFilterScriptInit(){
	Tryg3D::Foreach(playerid){
		Streamer::ToggleIdleUpdate(playerid,1);
	}
	SpecialVehicle::ToggleTrunkInterior(true);
	SpecialVehicle::ToggleTrailerInterior(true);

	new vid = SpecialVehicle::CreateMOC(1509.7998,1208.1492,11.8114,0.0,-1,1);
	SpecialVehicle::CreateMOCIncluded(vid,-1,1);
	
	SpecialVehicle::Create(577,1550.6296,1313.1257,10.7899,269.6724,-1,-1);
	SpecialVehicle::Create(432,1622.5732,1291.4335,10.8218,96.5474,-1,-1);
	SpecialVehicle::Create(528,1623.0045,1280.0103,10.8567,95.9787,-1,-1);
	SpecialVehicle::Create(601,1625.7404,1269.3386,10.5713,104.5200,-1,-1);
	SpecialVehicle::Create(548,1612.2839,1240.3584,12.3805,0.1176,-1,-1);
	SpecialVehicle::Create(519,1540.3129,1245.1423,11.7314,90.5341,-1,-1);
	SpecialVehicle::Create(592,1477.5725,1270.1030,12.0196,360.0000,-1,-1);
	SpecialVehicle::Create(522,1487.4178,1188.2659,10.3750,358.2807,-1,-1);
	SpecialVehicle::Create(522,1483.5496,1188.6095,10.4020,0.0000,-1,-1);
	SpecialVehicle::Create(522,1477.1483,1187.3604,10.4024,0.0000,-1,-1);
	SpecialVehicle::Create(522,1467.1956,1186.1696,10.4027,0.0000,-1,-1);
	SpecialVehicle::Create(470,1608.9338,1310.1045,10.8222,183.7841,-1,-1);
	SpecialVehicle::Create(504,1602.8472,1309.8759,10.6237,183.2850,-1,-1);
	SpecialVehicle::Create(578,1596.7998,1309.7645,11.4597,183.0829,-1,-1);
	vid = SpecialVehicle::Create(497,1586.3444,1334.7446,11.0314,175.6142,-1,-1);
	SpecialVehicle::ToggleMaverickMinigun(vid,true);
	
	SpecialVehicle::Create(487,1608.0543,1336.7684,10.9983,165.5369,1,1); // 
	SpecialVehicle::Create(497,1570.7330,1353.5186,11.0395,201.9240,1,1); // 
	SpecialVehicle::Create(553,1521.3716,1268.5316,12.1325,0.0,1,1); // 

	SpecialVehicle::Create(428,1574.9442,1335.1356,10.9834,174.7876,-1,-1);
	
	return 1;
}

public OnFilterScriptExit(){
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		if(IsValidVehicle(i)){
			DestroyVehicle(i);
		}
	}
	return 1;
}