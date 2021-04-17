/*
#include <ADM/3DTryg>
*/

new MapClick[MAX_PLAYERS][Vectors3D];

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ){
	
	MapClick[playerid][T3D:X] = fX;
	MapClick[playerid][T3D:Y] = fY;
	
	return 1;
}

//Group teleportation
CMD:xtpmap(playerid,params[]){
	//admin ?
	new Float:distance, max_players = 0, idx = 0, Float:px, Float:py, Float:pz;
	if(sscanf(params,"f",distance)) return Msg(playerid,COLOR_ERROR,"Usage: /xtpmap <distance>");
	GetPlayerPos(playerid,px,py,pz);
	
	Tryg3D::Foreach(i){
		if(i != playerid){
			if(GetDistanceBetweenPlayers(playerid,i) <= distance) max_players++;
		}
	}
	
	new Float:x,Float:y,Float:z_angle,Float:MAz,Float:radius;
	if(max_players < 4){
		radius = 3.0;
	} else {
		radius = 3.0+(0.25*max_players);
	}
	CA_FindZ_For2DCoord(MapClick[playerid][T3D:X],MapClick[playerid][T3D:Y],MAz);
	SetPlayerPos(playerid,MapClick[playerid][T3D:X],MapClick[playerid][T3D:Y],MAz+1.5);
	SetPlayerInterior(playerid,0);
	SetPlayerVirtualWorld(playerid,0);
	
	if(max_players > 0){
		Tryg3D::Foreach(i){
			if(i != playerid){
				if(GetPlayerDistanceFromPoint(i,px,py,pz) <= distance){
					Random::PointOnClock(MapClick[playerid][T3D:X],MapClick[playerid][T3D:Y],radius,x,y,z_angle,single_clock(max_players,idx));
					CA_FindZ_For2DCoord(x,y,MAz);
					/*
					//FCNPC ?
					if(!IsPlayerNPC(i)){
						SetPlayerPos(i,x,y,MAz+1.5);
						GetPlayerFacingAngle(i,z_angle);
						SetPlayerInterior(i,0);
						SetPlayerVirtualWorld(i,0);
						SetCameraBehindPlayer(i);
					} else {
						FCNPC_SetPosition(i,x,y,MAz+1.5);
						FCNPC_SetAngle(i,z_angle);
						FCNPC_SetInterior(i,0);
						FCNPC_SetVirtualWorld(i,0);
					}
					*/

					SetPlayerPos(i,x,y,MAz+1.5);
					GetPlayerFacingAngle(i,z_angle);
					SetPlayerInterior(i,0);
					SetPlayerVirtualWorld(i,0);
					SetCameraBehindPlayer(i);
					
					idx++;
				}
			}
		}
	}
	return 1;
}

//Vehicle Teleport to map
CMD:vtpmap(playerid){
	//admin ?
	new Float:MAz,Float:z_angle;
	GetPlayerFacingAngle(playerid,z_angle);
	CA_FindZ_For2DCoord(MapClick[playerid][T3D:X],MapClick[playerid][T3D:Y],MAz);
	SetPlayerAbsolutePositionVeh(playerid,MapClick[playerid][T3D:X],MapClick[playerid][T3D:Y],MAz+1.5,z_angle,0,0);
	return 1;
}
