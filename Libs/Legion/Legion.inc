/*
Legion V3.5 Copyright © 2021 Abyss Morgan, Unrea1
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

#if !defined COLANDREAS
	#error [ADM] You need ColAndreas v1.4.0 (github.com/Pottus/ColAndreas/releases)
#endif

#if !defined _FCNPC_included
	#error [ADM] You need FCNPC v2.0.0 (github.com/ziggi/FCNPC/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v5.1.1
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v5.1.1
#elseif (TRYG3D_VERSION < 50101)
	#error [ADM] Update you 3DTryg.inc to v5.1.1
#endif

//Check Version SWAP.inc
#if !defined _SWAP_include
	#error [ADM] You need SWAP.inc v1.3.0 (adm.ct8.pl/d/SWAP.inc)
#elseif !defined SWAP_Version
	#error [ADM] Update you SWAP.inc to v1.3.0 (adm.ct8.pl/d/SWAP.inc)
#elseif (SWAP_Version < 10300)
	#error [ADM] Update you SWAP.inc to v1.3.0 (adm.ct8.pl/d/SWAP.inc)
#endif

#define Legion::						Legion_

#if !defined MAX_LEGION_NPC
	#define MAX_LEGION_NPC 				900
#endif

#if !defined LEGION_DEFAULT_HEALTH
	#define LEGION_DEFAULT_HEALTH		(200.0)
#endif

#if !defined LEGION_DEFAULT_ARMOUR
	#define LEGION_DEFAULT_ARMOUR		(200.0)
#endif

#if !defined LEGION_INTEREST_DEFUALT
	#define LEGION_INTEREST_DEFUALT		(5)
#endif

#if !defined LEGION_INTEREST_MAX
	#define LEGION_INTEREST_MAX			(10)
#endif

#define LEGION_WEAPON_AUTO				(-1)
#define LEGION_WEAPON_ACC_AUTO			(-1.0)
#if !defined LEGION_TEAM_ID
	#define LEGION_TEAM_ID				(69)
#endif

#define LEGION_Z_DIFF					(0.992288)
#define LEGION_Z_CLIMBING				(1.50)

#define LEGION_EXTRA_ID_OFFSET_A		(10000000)
#define LEGION_EXTRA_ID_OFFSET_B		(10004000)

#define LEGION_SWAP_FILE				"LegionScore.bin"

enum Legion::StateList {
	LEGION_STATE_CREATE,
	LEGION_STATE_DEAD,
	LEGION_STATE_ONFOOT,
	LEGION_STATE_ENTER_VEHICLE,
	LEGION_STATE_VEHICLE_DRIVER,
	LEGION_STATE_VEHICLE_PASSENGER,
	LEGION_STATE_EXIT_VEHICLE
};

enum Legion::CommandList {
	LEGION_CMD_MOVE_NEARBY,
	LEGION_CMD_STAY_HERE,
	LEGION_CMD_GOTO_POINT,
	LEGION_CMD_GET_PASSENGERS,
	LEGION_CMD_GO_AS_PASSENGER,
	LEGION_CMD_GOTO_CP
};

enum Legion::EnumNPC {
	bool:					Legion::active,
							Legion::skinid,
	Float:					Legion::X,
	Float:					Legion::Y,
	Float:					Legion::Z,
	Float:					Legion::A,
							Legion::VW,
							Legion::INT,
							Legion::TeamID,
							Legion::color,
	Float:					Legion::health,
	Float:					Legion::armour,
							Legion::weaponid,
							Legion::RespawnTime,
							Legion::LastTarget,
							Legion::NextCommandTime,
							Legion::Interest,
	Float:					Legion::InterestX,
	Float:					Legion::InterestY,
	Float:					Legion::InterestZ,
							Legion::PathID,
	bool:					Legion::Agresive,
	bool:					Legion::DefendingZone,
	bool:					Legion::InCheckPoint,
	STREAMER_TAG_CP:		Legion::CheckPoint,
	Legion::StateList:		Legion::State,
	Legion::CommandList:	Legion::Command,
	Float:					Legion::acc,
	STREAMER_TAG_AREA:		Legion::ears,
	STREAMER_TAG_AREA:		Legion::col,
	STREAMER_TAG_AREA:		Legion::move_area,
	STREAMER_TAG_AREA:		Legion::defending_area,
	STREAMER_TAG_AREA:		Legion::detection_col[128],
							Legion::max_areas,
							Legion::AreaNPC,
	Float:					Legion::GotoX,
	Float:					Legion::GotoY,
	Float:					Legion::GotoZ,
							Legion::MoveType,
	Float:					Legion::MoveSpeed,
							Legion::MovePath,
							Legion::WaitForDriver,
							Legion::WaitForPassengers,
							Legion::WaitSupportDone
};

enum Legion::EnumWeapon {
							Legion::WeaponID,
	Float:					Legion::Accuracy
};

new Legion::WeaponList[][Legion::EnumWeapon] = {
	{WEAPON_COLT45,0.90},
	{WEAPON_SILENCED,0.90},
	{WEAPON_DEAGLE,0.80},
	{WEAPON_SHOTGUN,0.80},
	{WEAPON_SAWEDOFF,0.70},
	{WEAPON_SHOTGSPA,0.70},
	{WEAPON_UZI,0.80},
	{WEAPON_MP5,0.65},
	{WEAPON_AK47,0.70},
	{WEAPON_M4,0.70},
	{WEAPON_TEC9,0.80},
	{WEAPON_RIFLE,0.65},
	{WEAPON_SNIPER,0.90},
	{WEAPON_ROCKETLAUNCHER,0.10},
	{WEAPON_MINIGUN,0.10}
};

//No encryption required
new LEGION_SWAP_KEY[][] = {
	{0},
	{0}
};

new Legion::Data[MAX_PLAYERS][Legion::EnumNPC],
	Legion::VehicleLock[MAX_VEHICLES],
	Legion::NPC[MAX_LEGION_NPC],
	Legion::LastScore[MAX_PLAYERS];

#define Legion_Fresh(%0)					Legion::Data[(%0)] = Legion::DataConstruct()
#define Legion_CanMove(%0)					Legion::Data[(%0)][Legion::weaponid] != 35 && Legion::Data[(%0)][Legion::weaponid] != 34 && Legion::Data[(%0)][Legion::Command] != LEGION_CMD_STAY_HERE && !Legion::Data[(%0)][Legion::InCheckPoint]
#define Legion_GetAgressive(%0)				Legion::Data[(%0)][Legion::Agresive]
#define Legion_SetAgressive(%0,%1)			Legion::Data[(%0)][Legion::Agresive] = (%1)
#define Legion_GetCommand(%0)				Legion::Data[(%0)][Legion::Command]
#define Legion_SetCommand(%0,%1)			Legion::Data[(%0)][Legion::Command] = (%1)
#define Legion_GetState(%0)					Legion::Data[(%0)][Legion::State]
#define Legion_SetState(%0,%1)				Legion::Data[(%0)][Legion::State] = (%1)
#define Legion_GetDefending(%0)				Legion::Data[(%0)][Legion::DefendingZone]
#define Legion_SetDefending(%0,%1)			Legion::Data[(%0)][Legion::DefendingZone] = (%1)
#define Legion_GetNextCommandTime(%0)		Legion::Data[(%0)][Legion::NextCommandTime]
#define Legion_SetNextCommandTime(%0,%1)	Legion::Data[(%0)][Legion::NextCommandTime] = (%1)
#define Legion_GetInterest(%0)				Legion::Data[(%0)][Legion::Interest]
#define Legion_SetInterest(%0,%1)			Legion::Data[(%0)][Legion::Interest] = (%1)
#define Legion_GetInterestPos(%0,%1,%2,%3)	(%1) = Legion::Data[(%0)][Legion::InterestX], (%2) = Legion::Data[(%0)][Legion::InterestY], (%3) = Legion::Data[(%0)][Legion::InterestZ]
#define Legion_SetInterestPos(%0,%1,%2,%3)	Legion::Data[(%0)][Legion::InterestX] = (%1),Legion::Data[(%0)][Legion::InterestY] = (%2),Legion::Data[(%0)][Legion::InterestZ] = (%3)

stock Legion::DataConstruct(){
	new data_construct[Legion::EnumNPC];
	data_construct[Legion::LastTarget] = INVALID_PLAYER_ID;
	return data_construct;
}

stock Legion::SetRandomWeapon(npcid){
	new Legion::Rand = random(sizeof(Legion::WeaponList));
	Legion::SetWeapon(npcid,Legion::WeaponList[Legion::Rand][Legion::WeaponID],Legion::WeaponList[Legion::Rand][Legion::Accuracy]);
}

stock Legion::Init(){
	if(!fexist(LEGION_SWAP_FILE)){
		SWAP::reserve(LEGION_SWAP_FILE,MAX_PLAYERS*4);
	}
	for(new npcid = 0; npcid < MAX_PLAYERS; npcid++){
		Legion::Fresh(npcid);
	}
	for(new vehicleid = 0; vehicleid < MAX_VEHICLES; vehicleid++){
		Legion::VehicleLock[vehicleid] = INVALID_PLAYER_ID;
	}
}

T3D:function Legion::OnProtocolUpdate(){
	new cur_tick = GetTickCount(), npcid;
	for(new i = 0; i < MAX_LEGION_NPC; i++){
		npcid = Legion::NPC[i];
		if(npcid != INVALID_PLAYER_ID){
			//SetPlayerFakePing(npcid,randomex(25,50));
			switch(Legion::Data[npcid][Legion::State]){
				case LEGION_STATE_DEAD: {
					if(GetTickCount() > Legion::Data[npcid][Legion::RespawnTime]){
						Legion::Data[npcid][Legion::RespawnTime] = 0;
						FCNPC::Respawn(npcid);
					}
				}
			}
			if(Legion::Data[npcid][Legion::InCheckPoint]){
				if(Legion::GetZoneOwner(Legion::Data[npcid][Legion::CheckPoint]) == Legion::Data[npcid][Legion::TeamID]){
					Legion::Data[npcid][Legion::InCheckPoint] = false;
					Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
					Legion::SyncArea(npcid);
				}
			}
			if(Legion::GetNextCommandTime(npcid) > cur_tick && Legion::GetNextCommandTime(npcid) != 0){
				if(Legion::LastScore[npcid] != GetPlayerScore(npcid)){
					Legion::LastScore[npcid] = GetPlayerScore(npcid);
					SWAP::write_int(LEGION_SWAP_FILE,LEGION_SWAP_KEY,(npcid*4),Legion::LastScore[npcid]);
				}
				if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
					switch(Legion::GetState(npcid)){
						case LEGION_STATE_ONFOOT: {
							switch(Legion::GetCommand(npcid)){
								case LEGION_CMD_MOVE_NEARBY: {
									if(!Legion::GetDefending(npcid) && Legion::Data[npcid][Legion::WaitForDriver] == 0){
										if(Legion::GetInterest(npcid) == 0){
											new Float:x,Float:y,Float:z;
											if(Legion::GetRandomCaptureZone(npcid,x,y,z)){
												Legion::SetInterest(npcid,LEGION_INTEREST_DEFUALT);
												Legion::SetInterestPos(npcid,x,y,z);
											}
										}
										if(Legion::GetInterest(npcid) > 0){
											Legion::GotoOnMap(npcid,Legion::Data[npcid][Legion::InterestX],Legion::Data[npcid][Legion::InterestY],Legion::Data[npcid][Legion::InterestZ]);
										}
									}
								}
							}
							
						}
					}
				}
				Legion::SetNextCommandTime(npcid,cur_tick+randomex(3000,10000));
			}
		}
	}
	return 1;
}

stock Legion::Exit(){
	for(new npcid = 0; npcid < MAX_PLAYERS; npcid++){
		if(Legion::Data[npcid][Legion::active]){
			if(FCNPC::IsValid(npcid)){
				FCNPC::Destroy(npcid);
			}
		}
	}
}

stock Legion::Attach(npcid){
	SetPlayerAttachedObject(npcid,0,331,6,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,1,335,11,0.142010,-0.100988,0.055910,76.125000,75.876144,1.143326,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,2,346,8,-0.028010,-0.033822,0.097883,270.000000,15.999426,354.161499,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,3,351,16,0.100795,0.057224,-0.082939,180.000000,243.483581,180.000000,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,4,352,7,0.138560,-0.033982,-0.047630,281.671447,276.618591,4.068862,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,5,355,1,-0.130044,-0.127836,0.025491,2.044970,6.239807,6.833646,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,6,342,16,-0.110845,-0.041751,0.087840,55.051963,84.884071,247.221984,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,7,365,12,0.174919,-0.004211,-0.142508,0.000000,270.000000,0.000000,1.000000,1.000000,1.000000 );
	SetPlayerAttachedObject(npcid,8,369,2,0.000000,0.078037,0.000000,0.000000,0.000000,0.000000,1.000000,1.000000,1.000000 );
}

stock Legion::ClearMovePath(npcid){
	if(FCNPC::IsValidMovePath(Legion::Data[npcid][Legion::MovePath])){
		FCNPC::DestroyMovePath(Legion::Data[npcid][Legion::MovePath]);
		Legion::Data[npcid][Legion::MovePath] = FCNPC_INVALID_MOVEPATH_ID;
	}
}

stock Legion::LockVehicleForNPC(npcid,vehicleid,bool:locked){
	if(!IsValidVehicle(vehicleid)) return 0;
	if(FCNPC::IsValid(Legion::VehicleLock[vehicleid])) return 0;
	if(locked){
		Legion::VehicleLock[vehicleid] = npcid;
	} else {
		Legion::VehicleLock[vehicleid] = INVALID_PLAYER_ID;
	}
	return 1;
}

stock Legion::IsLegionOnLine(npcid,Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz){
	Legion::Data[npcid][Legion::max_areas] = GetNumberDynamicAreasForLine(x,y,z,tx,ty,tz);
	if(Legion::Data[npcid][Legion::max_areas]){
		GetDynamicAreasForLine(x,y,z,tx,ty,tz,Legion::Data[npcid][Legion::detection_col],128);
		for(new k = 0; k < Legion::Data[npcid][Legion::max_areas]; k++){
			if(k >= 128) break;
			Legion::Data[npcid][Legion::AreaNPC] = Streamer::GetIntData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::detection_col][k],E_STREAMER_EXTRA_ID) - LEGION_EXTRA_ID_OFFSET_B;
			if(Legion::Data[npcid][Legion::AreaNPC] >= 0 && Legion::Data[npcid][Legion::AreaNPC] < MAX_PLAYERS){
				if(Legion::Data[npcid][Legion::detection_col][k] == Legion::Data[Legion::Data[npcid][Legion::AreaNPC]][Legion::col]){
					if(Legion::Data[npcid][Legion::AreaNPC] != npcid){
						if(IsPointInDynamicArea(Legion::Data[npcid][Legion::detection_col][k],x,y,z)) return 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

stock Legion::SetWeapon(npcid,weaponid,Float:accuracy){
	Legion::Data[npcid][Legion::weaponid] = weaponid;
	Legion::Data[npcid][Legion::acc] = accuracy;
	FCNPC::SetWeapon(npcid,weaponid);
	FCNPC::SetAmmo(npcid,9999);
	FCNPC::SetWeaponAccuracy(npcid,weaponid,accuracy);
	FCNPC::UseInfiniteAmmo(npcid,true);
	Legion::Attach(npcid);
}

stock Legion::GetVehicle(npcid,Float:maxdist){
	new Float:distance = 20000.0, foundvid = INVALID_VEHICLE_ID, Float:tmpdistance, tmp_driver,
		Float:px, Float:py, Float:pz,
		Float:x, Float:y, Float:z, worldid = FCNPC::GetVirtualWorld(npcid), interiorid = FCNPC::GetInterior(npcid);
	FCNPC::GetPosition(npcid,x,y,z);
	for(new vehicleid = 1, j = GetVehiclePoolSize(); vehicleid <= j; vehicleid++){
		switch(GetVehicleModel(vehicleid)){
			case 430, 435, 446, 449, 450, 452, 453, 454, 464, 465,
				 472, 473, 484, 493, 501, 537, 538, 564, 569, 570,
				 584, 590, 591, 594, 595, 606, 607, 608, 610, 611: continue;
			default: {
				if(IsVehicleFlag(GetVehicleFlags(vehicleid),VF_STREET) && Legion::VehicleLock[vehicleid] == INVALID_PLAYER_ID){
					if(worldid != -1 && GetVehicleVirtualWorld(vehicleid) != worldid) continue;
					if(interiorid != -1 && GetVehicleInterior(vehicleid) != interiorid) continue;
					GetVehiclePos(vehicleid,px,py,pz);
					tmpdistance = VectorSize(x-px,y-py,z-pz);
					if(maxdist > 0.0 && tmpdistance > maxdist) continue;
					if(tmpdistance < distance){
						tmp_driver = GetVehicleDriver(vehicleid);
						if(IsPlayerConnected(tmp_driver)) continue;
						distance = tmpdistance;
						foundvid = vehicleid;
					}
				}
			}
		}
	}
	return foundvid;
}

stock Legion::GotoOnMap(npcid,Float:x,Float:y,Float:z){
	Legion::Data[npcid][Legion::GotoX] = x;
	Legion::Data[npcid][Legion::GotoY] = y;
	Legion::Data[npcid][Legion::GotoZ] = z;
	Legion::Data[npcid][Legion::Command] = LEGION_CMD_GOTO_POINT;
}

stock Legion::MoveWithPath(npcid,Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,move_type,Float:move_speed){
	Legion::Data[npcid][Legion::MoveType] = move_type;
	Legion::Data[npcid][Legion::MoveSpeed] = move_speed;
	Legion::ClearMovePath(npcid);
	Legion::Data[npcid][Legion::MovePath] = FCNPC::CreateMovePath();
	FCNPC::AddPointToMovePath(Legion::Data[npcid][Legion::MovePath],x,y,z);
	
	new MapNode:nodeid[2];
	GetClosestMapNodeToPoint(x,y,z,nodeid[0]);
	GetClosestMapNodeToPoint(tx,ty,tz,nodeid[1]);
	
	FindPathThreaded(nodeid[0],nodeid[1],"OnLegionPathCalculated","d",npcid);
	
	//CalculatePath(NearestNodeFromPoint(x,y,z),NearestNodeFromPoint(tx,ty,tz),(npcid+2000),false,_,true);
}

T3D:function OnLegionPathCalculated(Path:pathid, npcid, start_time) {
    if(!IsValidPath(pathid)) return 0;
	new amount_of_nodes, MapNode:nodeid, Float:x, Float:y, Float:z;
    GetPathSize(pathid,amount_of_nodes);
	if(IsPlayerConnected(npcid)){
		new Float:ox,Float:oy,Float:oz;
		if(IsPlayerInAnyVehicle(npcid)){
			GetVehicleModelInfo(GetVehicleModel(FCNPC::GetVehicleID(npcid)),VEHICLE_MODEL_INFO_SIZE,ox,oy,oz);
			oz /= 2.0;
		} else {
			oz = LEGION_Z_DIFF;
			GetPathNode(pathid,0,nodeid);
			GetMapNodePos(nodeid,x,y,z);
			FCNPC::SetTargetAngle(npcid,x,y);
		}
		for(new i = 0; i < amount_of_nodes; i++){
			GetPathNode(pathid,0,nodeid);
			GetMapNodePos(nodeid,x,y,z);
			InteriorFindZ(x,y,z,2.0);
			FCNPC::AddPointToMovePath(Legion::Data[npcid][Legion::MovePath],x,y,z+oz);
		}
		FCNPC::GoByMovePath(npcid,Legion::Data[npcid][Legion::MovePath],0,Legion::Data[npcid][Legion::MoveType],Legion::Data[npcid][Legion::MoveSpeed],FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
	}
    DestroyPath(pathid);
    return 1;
}

/*
public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size,Float:NodePosX[],Float:NodePosY[],Float:NodePosZ[]){
	new npcid = routeid - 2000;
	if(IsPlayerConnected(npcid)){
		new Float:ox,Float:oy,Float:oz;
		if(IsPlayerInAnyVehicle(npcid)){
			GetVehicleModelInfo(GetVehicleModel(FCNPC::GetVehicleID(npcid)),VEHICLE_MODEL_INFO_SIZE,ox,oy,oz);
			oz /= 2.0;
		} else {
			oz = LEGION_Z_DIFF;
			FCNPC::SetTargetAngle(npcid,NodePosX[0],NodePosY[0]);
		}
		for(new i = 0; i < amount_of_nodes; i++){
			InteriorFindZ(NodePosX[i],NodePosY[i],NodePosZ[i],2.0);
			FCNPC::AddPointToMovePath(Legion::Data[npcid][Legion::MovePath],NodePosX[i],NodePosY[i],NodePosZ[i]+oz);
		}
		FCNPC::GoByMovePath(npcid,Legion::Data[npcid][Legion::MovePath],0,Legion::Data[npcid][Legion::MoveType],Legion::Data[npcid][Legion::MoveSpeed],FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
	}
	return 1;
}
*/

stock Legion::Create(const name[],skinid,color,Float:x,Float:y,Float:z,Float:angle,worldid=0,interiorid=0,Float:health=LEGION_DEFAULT_HEALTH,Float:armour=LEGION_DEFAULT_ARMOUR,weaponid=LEGION_WEAPON_AUTO,Float:accuracy=LEGION_WEAPON_ACC_AUTO,teamid=LEGION_TEAM_ID){
	new npcid = FCNPC::Create(name);
	if(!FCNPC::IsValid(npcid)) return INVALID_PLAYER_ID;
	
	Legion::Fresh(npcid);
	
	Legion::Data[npcid][Legion::State] = LEGION_STATE_CREATE;
	Legion::Data[npcid][Legion::Command] = LEGION_CMD_STAY_HERE;
	Legion::Data[npcid][Legion::skinid] = skinid;
	Legion::Data[npcid][Legion::X] = x;
	Legion::Data[npcid][Legion::Y] = y;
	Legion::Data[npcid][Legion::Z] = z;
	Legion::Data[npcid][Legion::A] = angle;
	Legion::Data[npcid][Legion::VW] = worldid;
	Legion::Data[npcid][Legion::INT] = interiorid;
	Legion::Data[npcid][Legion::TeamID] = teamid;
	Legion::Data[npcid][Legion::color] = color;
	Legion::Data[npcid][Legion::health] = health;
	Legion::Data[npcid][Legion::armour] = armour;
	Legion::Data[npcid][Legion::LastTarget] = INVALID_PLAYER_ID;
	Legion::Data[npcid][Legion::col] = CreateDynamicSphere(x,y,z,2.0,worldid,interiorid);
	Legion::Data[npcid][Legion::ears] = CreateDynamicSphere(x,y,z,8.0,worldid,interiorid);
	Legion::Data[npcid][Legion::move_area] = CreateDynamicCircle(x,y,200.0,worldid,interiorid);
	Legion::Data[npcid][Legion::defending_area] = CreateDynamicRectangle(-10.0,-10.0,10.0,10.0);
	Legion::Data[npcid][Legion::MovePath] = FCNPC_INVALID_MOVEPATH_ID;
	
	AttachDynamicAreaToPlayer(Legion::Data[npcid][Legion::ears],npcid);
	AttachDynamicAreaToPlayer(Legion::Data[npcid][Legion::col],npcid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::ears],E_STREAMER_EXTRA_ID,npcid+LEGION_EXTRA_ID_OFFSET_A);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::col],E_STREAMER_EXTRA_ID,npcid+LEGION_EXTRA_ID_OFFSET_B);
	
	SetPlayerTeam(npcid,Legion::Data[npcid][Legion::TeamID]);
	
	Legion::Data[npcid][Legion::active] = true;
	Legion::Spawn(npcid);
	if(weaponid == LEGION_WEAPON_AUTO){
		Legion::SetRandomWeapon(npcid);
	} else {
		Legion::Data[npcid][Legion::weaponid] = weaponid;
	}
	if(accuracy == LEGION_WEAPON_ACC_AUTO){
		for(new i = 0, j = sizeof(Legion::WeaponList); i < j; i++){
			if(Legion::Data[npcid][Legion::weaponid] == Legion::WeaponList[i][Legion::WeaponID]){
				accuracy = Legion::WeaponList[i][Legion::Accuracy];
				break;
			}
		}
	}
	Legion::SetWeapon(npcid,Legion::Data[npcid][Legion::weaponid],accuracy);
	ShowNPCInTabList(npcid);
	return npcid;
}

stock Legion::GetTarget(npcid,Float:max_dist=0.0){
	if(!Legion::Data[npcid][Legion::Agresive]) return INVALID_PLAYER_ID;
	if(Legion::Data[npcid][Legion::State] == LEGION_STATE_DEAD) return INVALID_PLAYER_ID;
	new Float:x, Float:y, Float:z, Float:angle, pteam = GetPlayerTeam(npcid),pool_players[MAX_PLAYERS], pool_upp = -1;
	FCNPC::GetPosition(npcid,x,y,z);
	angle = FCNPC::GetAngle(npcid);
	if(max_dist <= 0.0){
		switch(Legion::Data[npcid][Legion::weaponid]){
			case 34, 35: {
				max_dist = 220.0;
			}
			default: {
				max_dist = 150.0;
			}
		}
	}
	Tryg3D::Foreach(i){
		if(GetPlayerTeam(i) != pteam){
			if(Item::GetDistance(i,item_player,npcid,item_fcnpc) <= max_dist && FCNPC::IsStreamedIn(npcid,i)){
				if(GetPlayerState(i) != PLAYER_STATE_SPECTATING && GetPlayerState(i) != PLAYER_STATE_WASTED){
					if(Item::OnFakeScreen(x,y,z,i,item_player,0.0,angle)){
						pool_upp++;
						pool_players[pool_upp] = i;
					}
				}
			}
		}
	}
	if(pool_upp == -1) return INVALID_PLAYER_ID;
	return pool_players[random(pool_upp+1)];
}

stock Legion::Spawn(npcid){
	Legion::ClearMovePath(npcid);
	FCNPC::Spawn(npcid,Legion::Data[npcid][Legion::skinid],Legion::Data[npcid][Legion::X],Legion::Data[npcid][Legion::Y],Legion::Data[npcid][Legion::Z]);
	FCNPC::SetAngle(npcid,Legion::Data[npcid][Legion::A]);
	FCNPC::SetVirtualWorld(npcid,Legion::Data[npcid][Legion::VW]);
	FCNPC::SetInterior(npcid,Legion::Data[npcid][Legion::INT]);
	FCNPC::SetHealth(npcid,Legion::Data[npcid][Legion::health]);
	FCNPC::SetArmour(npcid,Legion::Data[npcid][Legion::armour]);
	Legion::Data[npcid][Legion::InCheckPoint] = false;
	Legion::Data[npcid][Legion::DefendingZone] = false;
	Legion::Data[npcid][Legion::WaitForDriver] = 0;
	Legion::Data[npcid][Legion::RespawnTime] = 0;
	Legion::SetWeapon(npcid,Legion::Data[npcid][Legion::weaponid],Legion::Data[npcid][Legion::acc]);
	SetPlayerTeam(npcid,Legion::Data[npcid][Legion::TeamID]);
	for(new i = 0; i <= 10; i++){
		FCNPC::SetWeaponSkillLevel(npcid,i,999);
	}
	SetPlayerColor(npcid,Legion::Data[npcid][Legion::color]);
	FCNPC::SetInvulnerable(npcid,false);
	Streamer::SetItemPos(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::move_area],Legion::Data[npcid][Legion::X],Legion::Data[npcid][Legion::Y],0.0);
	Legion::Data[npcid][Legion::State] = LEGION_STATE_ONFOOT;
	Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
}

stock Legion::StartAttack(npcid,bool:force=false){
	if(!Legion::Data[npcid][Legion::Agresive]) return 0;
	if(Legion::Data[npcid][Legion::State] == LEGION_STATE_DEAD) return 0;
	if(!IsPlayerConnected(Legion::Data[npcid][Legion::LastTarget])) return Legion::StopAttack(npcid);
	new Float:x,Float:y,Float:z;
	FCNPC::GetPosition(npcid,x,y,z);
	if(!Item::OnFakeScreen(x,y,z,Legion::Data[npcid][Legion::LastTarget],item_player,0.0,FCNPC::GetAngle(npcid)) && !force) return Legion::StopAttack(npcid);
	FCNPC::AimAtPlayer(npcid,Legion::Data[npcid][Legion::LastTarget],true,1000,true);
	return 1;
}

stock Legion::StopAttack(npcid){
	FCNPC::StopAttack(npcid);
	FCNPC::StopAim(npcid);
	Legion::Data[npcid][Legion::LastTarget] = INVALID_PLAYER_ID;
	return 1;
}

stock Legion::SyncArea(npcid){
	new Float:x,Float:y,Float:z;
	FCNPC::GetPosition(npcid,x,y,z);
	Streamer::SetItemPos(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::move_area],x,y,0.0);
	return 1;
}

stock Legion::GetDefendingArea(npcid,&Float:minx,&Float:miny,&Float:maxx,&Float:maxy){
	Streamer::GetFloatData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::defending_area],E_STREAMER_MIN_X,minx);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::defending_area],E_STREAMER_MIN_Y,miny);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::defending_area],E_STREAMER_MAX_X,maxx);
	Streamer::GetFloatData(STREAMER_TYPE_AREA,Legion::Data[npcid][Legion::defending_area],E_STREAMER_MAX_Y,maxy);
}

stock Legion::SetDefendingArea(npcid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	if(IsValidDynamicArea(Legion::Data[npcid][Legion::defending_area])) DestroyDynamicArea(Legion::Data[npcid][Legion::defending_area]);
	Legion::Data[npcid][Legion::defending_area] = CreateDynamicRectangle(minx,miny,maxx,maxy);
}

public FCNPC::OnReachDestination(npcid){
	if(Legion::Data[npcid][Legion::active]){
		switch(Legion::Data[npcid][Legion::State]){
			case LEGION_STATE_ONFOOT: {
				if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID){
					if(!FCNPC::IsShooting(npcid) && Legion::Data[npcid][Legion::Agresive]){
						FCNPC::AimAtPlayer(npcid,Legion::Data[npcid][Legion::LastTarget],true,1000,true);
					}
				}
				if(Legion::Data[npcid][Legion::Command] == LEGION_CMD_GOTO_CP){
					FCNPC::Stop(npcid);
					FCNPC::ClearAnimations(npcid);
				}
			}
		}
	}
	return 1;
}

public FCNPC::OnSpawn(npcid){
	if(Legion::Data[npcid][Legion::active]){
		Legion::Attach(npcid);
		Legion::SyncArea(npcid);
		Legion::Data[npcid][Legion::State] = LEGION_STATE_ONFOOT;
		SetPlayerTeam(npcid,Legion::Data[npcid][Legion::TeamID]);
	}
	return 1;
}

public FCNPC::OnCreate(npcid){
	if(Legion::Data[npcid][Legion::active]){
		Legion::Attach(npcid);
		Streamer::ToggleIdleUpdate(npcid,1);
	}
	return 1;
}

public FCNPC::OnRespawn(npcid){
	if(Legion::Data[npcid][Legion::active]){
		Legion::Spawn(npcid);
		FCNPC::SetPosition(npcid,Legion::Data[npcid][Legion::X],Legion::Data[npcid][Legion::Y],Legion::Data[npcid][Legion::Z]);
		FCNPC::SetVirtualWorld(npcid,Legion::Data[npcid][Legion::VW]);
		FCNPC::SetInterior(npcid,Legion::Data[npcid][Legion::INT]);
	}
	return 1;
}

public FCNPC::OnDestroy(npcid){
	if(Legion::Data[npcid][Legion::active]){
		Legion::Fresh(npcid);
	}
	return 1;
}

public FCNPC::OnDeath(npcid, killerid, reason){
	if(Legion::Data[npcid][Legion::active]){
		if(Legion::GetInterest(npcid) > 0){
			Legion::SetInterest(npcid,Legion::GetInterest(npcid)-1);
		}
		Legion::Data[npcid][Legion::State] = LEGION_STATE_DEAD;
		if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID){
			Legion::StopAttack(npcid);
		}
		if(FCNPC::IsMoving(npcid)){
			FCNPC::Stop(npcid);
		}
		//FCNPC::Respawn(npcid);
		Legion::Data[npcid][Legion::RespawnTime] = GetTickCount()+4000;
	}
	return 1;
}

public FCNPC::OnTakeDamage(npcid, issuerid, Float:amount, weaponid, bodypart){
	if(IsPlayerNPC(issuerid)) return 0;
	if(Legion::Data[npcid][Legion::active]){
		if(issuerid != INVALID_PLAYER_ID){
			switch(Legion::Data[npcid][Legion::State]){
				case LEGION_STATE_ONFOOT: {
					switch(Legion::Data[npcid][Legion::Command]){
						case LEGION_CMD_GOTO_POINT: {
							FCNPC::Stop(npcid);
							Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
							Legion::SyncArea(npcid);
							if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
								Legion::Data[npcid][Legion::LastTarget] = issuerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							} else if(Item::GetDistance(issuerid,item_player,npcid,item_fcnpc) < Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc)){
								Legion::Data[npcid][Legion::LastTarget] = issuerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							}
						}
						case LEGION_CMD_GOTO_CP: {
							if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
								Legion::Data[npcid][Legion::LastTarget] = issuerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							} else if(Item::GetDistance(issuerid,item_player,npcid,item_fcnpc) < Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc)){
								Legion::Data[npcid][Legion::LastTarget] = issuerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							}
						}
						case LEGION_CMD_MOVE_NEARBY: {
							if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
								Legion::Data[npcid][Legion::LastTarget] = issuerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							} else if(Item::GetDistance(issuerid,item_player,npcid,item_fcnpc) < Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc)){
								Legion::Data[npcid][Legion::LastTarget] = issuerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							}
							if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID){
								if(FCNPC::IsStreamedIn(npcid,issuerid) && Item::GetDistance(issuerid,item_player,npcid,item_fcnpc) > 5.0){
									if(Legion::CanMove(npcid)){
										if(IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::move_area]) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::defending_area]))){
											if(FCNPC::IsMoving(npcid)) FCNPC::Stop(npcid);
											new Float:x,Float:y,Float:z,Float:px,Float:py,Float:pz,Float:tx,Float:ty,Float:tz,Float:ix,Float:iy;
											FCNPC::GetPosition(npcid,x,y,z);
											GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],ix,iy,pz);
											FCNPC::SetTargetAngle(npcid,ix,iy);
											Random::PointOnCircle(ix,iy,Tryg3D::RandomFloat(3.0,8.0),px,py);
											if(!IsPointBetween2Points2D(ix,iy,x,y,px,py) && !Legion::IsLegionOnLine(npcid,x,y,z,px,py,pz)){
												if(MovePointColWithVehicleCut(x,y,z,px,py,pz,tx,ty,tz,3.0)){
													if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && floatabs(z-tz) <= LEGION_Z_CLIMBING && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPointInDynamicArea(Legion::Data[npcid][Legion::defending_area],tx,ty,tz))){
														if(Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc) > 25.0){
															FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
															FCNPC::ApplyAnimation(npcid,"FAT","FatSprint",4.1,true,true,true,true,true);
														} else {
															FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
															FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
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
				}
				case LEGION_STATE_ENTER_VEHICLE: {
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						FCNPC::Stop(npcid);
						Legion::SyncArea(npcid);
						Legion::Data[npcid][Legion::State] = LEGION_STATE_ONFOOT;
					}
				}
				case LEGION_STATE_VEHICLE_DRIVER: {
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
						FCNPC::Stop(npcid);
						Legion::LockVehicleForNPC(npcid,FCNPC::GetVehicleID(npcid),false);
						FCNPC::ExitVehicle(npcid);
					}
				}
				case LEGION_STATE_VEHICLE_PASSENGER: {
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						if(GetVehicleSpeed(FCNPC::GetVehicleID(npcid)) <= 0.0){
							Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
							FCNPC::ExitVehicle(npcid);
						}
					}
				}
			}
		}
	}
	return 1;
}

public FCNPC::OnStreamOut(npcid, forplayerid){
	if(Legion::Data[npcid][Legion::active]){
		if(Legion::Data[npcid][Legion::LastTarget] == forplayerid){
			Legion::StopAttack(npcid);
		}
	}
	return 1;
}

public FCNPC::OnUpdate(npcid){
	if(Legion::Data[npcid][Legion::active]){
		switch(Legion::Data[npcid][Legion::State]){
			case LEGION_STATE_ONFOOT: {
				if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
					Legion::Data[npcid][Legion::LastTarget] = Legion::GetTarget(npcid);
					if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID && Legion::Data[npcid][Legion::Command] == LEGION_CMD_GOTO_POINT){
						FCNPC::Stop(npcid);
						Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
						Legion::ClearMovePath(npcid);
						Legion::SyncArea(npcid);
					}
					Legion::StartAttack(npcid);
				} else {
					if(Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc) > 300.0){
						Legion::StopAttack(npcid);
					} else {
						if(!FCNPC::IsShooting(npcid) && Legion::Data[npcid][Legion::Agresive] && FCNPC::GetSpeed(npcid) < FCNPC_MOVE_SPEED_SPRINT){
							FCNPC::AimAtPlayer(npcid,Legion::Data[npcid][Legion::LastTarget],true,1000,true);
						}
					}
				}
				switch(Legion::Data[npcid][Legion::Command]){
					case LEGION_CMD_GOTO_CP: {
						if(!FCNPC::IsDead(npcid)){
							if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID){
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							}
							if(!FCNPC::IsMoving(npcid)){
								new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:px,Float:py,Float:pz,Float:ox,Float:oy,Float:oz,Float:target_z,bool:found = false;
								FCNPC::GetPosition(npcid,x,y,z);
								Streamer::GetItemPos(STREAMER_TYPE_CP,Legion::Data[npcid][Legion::CheckPoint],px,py,pz);
								if(GetDistanceBetweenPoints3D(x,y,z,px,py,pz) <= 1.0){
									if(!Legion::Data[npcid][Legion::InCheckPoint]){
										if(Legion::GetZoneOwner(Legion::Data[npcid][Legion::CheckPoint]) == Legion::Data[npcid][Legion::TeamID]){
											Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
											Legion::SyncArea(npcid);
										} else {
											Legion::Data[npcid][Legion::InCheckPoint] = true;
											CallRemoteFunction("OnPlayerEnterDynamicCP","dd",npcid,Legion::Data[npcid][Legion::CheckPoint]);
										}
										FCNPC::Stop(npcid);
										FCNPC::ClearAnimations(npcid);
									} else {
										if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
											FCNPC::SetAngle(npcid,Tryg3D::CompressRotation(FCNPC::GetAngle(npcid)+2.0));
										}
									}
								} else {
									if(GetDistanceBetweenPoints3D(x,y,z,px,py,pz) > 1.0){
										if(Item::ToPointIsVeh(px,py,pz,npcid,item_fcnpc)){
											GetPointFor2Point3D(x,y,z,px,py,pz,50.0,ox,oy,oz);
											for(new Float:ang = 0; ang < 360.0; ang += 1.0){
												GetPointInFront2D(ox,oy,ang,1.0,tx,ty);
												ColAndreas::FindGroundZ(tx,ty,z,target_z);
												tz = target_z + LEGION_Z_DIFF;
												if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty)){
													found = true;
													break;
												}
											}
											if(!found){
												if(!Item::ToPointIsVeh(x,py,z,npcid,item_fcnpc)){
													GetPointFor2Point2DEx(x,y,x,py,1.0,tx,ty);
												} else if(!Item::ToPointIsVeh(px,y,z,npcid,item_fcnpc)){
													GetPointFor2Point2DEx(x,y,px,y,1.0,tx,ty);
												} else {
													GetPointInFront2D(x,y,FCNPC::GetAngle(npcid),1.0,tx,ty);
												}
											}
											ColAndreas::FindGroundZ(tx,ty,z,target_z);
											tz = target_z + LEGION_Z_DIFF;
											if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz)){
												FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
												FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
											}
										} else if(GetDistanceBetweenPoints3D(x,y,z,px,py,pz) < 5.0){
											if(IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],px,py,pz)){
												if(!Legion::IsLegionOnLine(npcid,x,y,z,px,py,pz)){
													if(MovePointColWithVehicleCut(x,y,z,px,py,pz,tx,ty,tz,0.5)){
														if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz)){
															FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
															FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
														}
													}
												}
											}
										} else {
											if(IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],px,py,pz)){
												if(!Legion::IsLegionOnLine(npcid,x,y,z,px,py,pz)){
													if(MovePointColWithVehicleCut(x,y,z,px,py,pz,tx,ty,tz,0.5)){
														if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz)){
															if(GetDistanceBetweenPoints3D(x,y,z,px,py,pz) > 25.0){
																FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
																FCNPC::ApplyAnimation(npcid,"FAT","FatSprint",4.1,true,true,true,true,true);
															} else {
																FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
																FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
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
					}
					case LEGION_CMD_MOVE_NEARBY: {
						if(!FCNPC::IsDead(npcid)){
							if(!FCNPC::IsMoving(npcid)){
								if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
									new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:target_z;
									FCNPC::GetPosition(npcid,x,y,z);
									GetPointInFront2D(x,y,FCNPC::GetAngle(npcid),1.0,tx,ty);
									ColAndreas::FindGroundZ(tx,ty,z,target_z);
									tz = target_z + LEGION_Z_DIFF;
									if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPointInDynamicArea(Legion::Data[npcid][Legion::defending_area],tx,ty,tz))){
										FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
										FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
									} else {
										FCNPC::Stop(npcid);
										FCNPC::ClearAnimations(npcid);
										FCNPC::SetAngle(npcid,Tryg3D::RandomFloat(0.0,360.0));
									}
								} else {
									if(FCNPC::IsStreamedIn(npcid,Legion::Data[npcid][Legion::LastTarget])){
										if(Item::ToItemIsVeh(npcid,item_fcnpc,Legion::Data[npcid][Legion::LastTarget],item_player)){
											new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:px,Float:py,Float:pz,Float:ox,Float:oy,Float:oz,Float:target_z,bool:found = false;
											FCNPC::GetPosition(npcid,x,y,z);
											GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],px,py,pz);
											Random::PointOnCircle(px,py,Tryg3D::RandomFloat(3.0,8.0),px,py);
											GetPointFor2Point3D(x,y,z,px,py,pz,50.0,ox,oy,oz);
											for(new Float:ang = 0; ang < 360.0; ang += 1.0){
												GetPointInFront2D(ox,oy,ang,1.0,tx,ty);
												ColAndreas::FindGroundZ(tx,ty,z,target_z);
												tz = target_z + LEGION_Z_DIFF;
												if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty)){
													found = true;
													break;
												}
											}
											if(!found){
												if(!Item::ToPointIsVeh(x,py,z,npcid,item_fcnpc)){
													GetPointFor2Point2DEx(x,y,x,py,1.0,tx,ty);
												} else if(!Item::ToPointIsVeh(px,y,z,npcid,item_fcnpc)){
													GetPointFor2Point2DEx(x,y,px,y,1.0,tx,ty);
												} else {
													GetPointInFront2D(x,y,FCNPC::GetAngle(npcid),1.0,tx,ty);
												}
											}
											ColAndreas::FindGroundZ(tx,ty,z,target_z);
											tz = target_z + LEGION_Z_DIFF;
											if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && floatabs(z-tz) <= LEGION_Z_CLIMBING && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPointInDynamicArea(Legion::Data[npcid][Legion::defending_area],tx,ty,tz))){
												FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,false);
												FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
											}
										} else if(Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc) < 5.0){
											if(IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::move_area]) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::defending_area]))){
												if(Legion::CanMove(npcid)){
													new Float:x,Float:y,Float:z,Float:px,Float:py,Float:pz,Float:tx,Float:ty,Float:tz,Float:ix,Float:iy;
													FCNPC::GetPosition(npcid,x,y,z);
													GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],ix,iy,pz);
													FCNPC::SetTargetAngle(npcid,ix,iy);
													Random::PointOnCircle(ix,iy,Tryg3D::RandomFloat(3.0,8.0),px,py);
													if(!IsPointBetween2Points2D(ix,iy,x,y,px,py) && !Legion::IsLegionOnLine(npcid,x,y,z,px,py,pz)){
														if(MovePointColWithVehicleCut(x,y,z,px,py,pz,tx,ty,tz,3.0)){
															if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && floatabs(z-tz) <= LEGION_Z_CLIMBING && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPointInDynamicArea(Legion::Data[npcid][Legion::defending_area],tx,ty,tz))){
																FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,false);
																FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
															}
														}
													}
												}
											}
										} else {
											if(IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::move_area]) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::defending_area]))){
												if(Legion::CanMove(npcid)){
													new Float:x,Float:y,Float:z,Float:px,Float:py,Float:pz,Float:tx,Float:ty,Float:tz,Float:ix,Float:iy;
													FCNPC::GetPosition(npcid,x,y,z);
													GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],ix,iy,pz);
													FCNPC::SetTargetAngle(npcid,ix,iy);
													Random::PointOnCircle(ix,iy,Tryg3D::RandomFloat(3.0,8.0),px,py);
													if(!IsPointBetween2Points2D(ix,iy,x,y,px,py) && !Legion::IsLegionOnLine(npcid,x,y,z,px,py,pz)){
														if(MovePointColWithVehicleCut(x,y,z,px,py,pz,tx,ty,tz,3.0)){
															if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && floatabs(z-tz) <= LEGION_Z_CLIMBING && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPointInDynamicArea(Legion::Data[npcid][Legion::defending_area],tx,ty,tz))){
																if(Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc) > 25.0){
																	FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
																	FCNPC::ApplyAnimation(npcid,"FAT","FatSprint",4.1,true,true,true,true,true);
																} else {
																	FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
																	FCNPC::ApplyAnimation(npcid,"FAT","FatWalk",4.1,true,true,true,true,true);
																}
															}
														}
													}
												}
											}
										}
									}
								}
							} else {
								if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID){
									if(IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::move_area]) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPlayerInDynamicArea(Legion::Data[npcid][Legion::LastTarget],Legion::Data[npcid][Legion::defending_area]))){
										if(Legion::CanMove(npcid)){
											new Float:x,Float:y,Float:z,Float:px,Float:py,Float:pz,Float:tx,Float:ty,Float:tz,Float:ix,Float:iy;
											FCNPC::GetPosition(npcid,x,y,z);
											GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],ix,iy,pz);
											if(!FCNPC::IsMoving(npcid) || FCNPC::GetSpeed(npcid) < FCNPC_MOVE_SPEED_SPRINT) FCNPC::SetTargetAngle(npcid,ix,iy);
											Random::PointOnCircle(ix,iy,Tryg3D::RandomFloat(3.0,8.0),px,py);
											if(!IsPointBetween2Points2D(ix,iy,x,y,px,py) && !Legion::IsLegionOnLine(npcid,x,y,z,px,py,pz)){
												if(MovePointColWithVehicleCut(x,y,z,px,py,pz,tx,ty,tz,3.0)){
													if(!Item::ToPointIsVeh(tx,ty,tz,npcid,item_fcnpc) && !IsPointInWater(tx,ty) && floatabs(z-tz) <= LEGION_Z_CLIMBING && IsPointInDynamicArea(Legion::Data[npcid][Legion::move_area],tx,ty,tz) && (!Legion::Data[npcid][Legion::DefendingZone] || IsPointInDynamicArea(Legion::Data[npcid][Legion::defending_area],tx,ty,tz))){
														if(Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc) > 25.0){
															FCNPC::GoTo(npcid,tx,ty,tz,FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
															FCNPC::ApplyAnimation(npcid,"FAT","FatSprint",4.1,true,true,true,true,true);
														}
													}
												}
											}
										}
									}
								}
								new Float:x,Float:y,Float:z,Float:target_z,Float:tmp_float;
								FCNPC::GetPosition(npcid,x,y,z);
								ColAndreas::FindGroundZ(x,y,z,target_z);
								if(IsPointInUnderground(x,y,target_z+LEGION_Z_DIFF) && !ColAndreas::RayCastLine(x,y,z,x,y,z-1000.0,tmp_float,tmp_float,tmp_float)){
									ColAndreas::FindZ_For2DCoord(x,y,target_z);
								}
								FCNPC::SetPosition(npcid,x,y,(target_z+LEGION_Z_DIFF));
							}
						}
					}
					case LEGION_CMD_GOTO_POINT: {
						if(!FCNPC::IsDead(npcid)){
							if(Legion::Data[npcid][Legion::LastTarget] != INVALID_PLAYER_ID){
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							}
						}
						if(!FCNPC::IsMoving(npcid) && !FCNPC::IsValidMovePath(Legion::Data[npcid][Legion::MovePath])){
							new vehicleid = Legion::GetVehicle(npcid,50.0);
							if(IsValidVehicle(vehicleid)){
								if(!Item::ToItemIsWall(npcid,item_fcnpc,vehicleid,item_vehicle)){
									Legion::Data[npcid][Legion::State] = LEGION_STATE_ENTER_VEHICLE;
									Legion::LockVehicleForNPC(npcid,vehicleid,true);
									FCNPC::EnterVehicle(npcid,vehicleid,0,FCNPC_MOVE_TYPE_SPRINT);
									new max_passengers = GetVehicleSeats(vehicleid) - 1, seatid = 1;
									if(max_passengers > 0){
										new Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:maxx,Float:maxy;
										Legion::GetInterestPos(npcid,x,y,z);
										Legion::GetDefendingArea(npcid,minx,miny,maxx,maxy);
										Tryg3D::Foreach(i){
											if(max_passengers == 0) break;
											if(i != npcid && IsPlayerNPC(i)){
												if(Item::GetDistance(vehicleid,item_vehicle,i,item_fcnpc) < 50.0){
													if(Legion::Data[i][Legion::State] == LEGION_STATE_ONFOOT){
														Legion::Data[npcid][Legion::WaitForPassengers] = GetTickCount()+10000;
														Legion::Data[npcid][Legion::Command] = LEGION_CMD_GET_PASSENGERS;
														
														Legion::Data[i][Legion::Command] = LEGION_CMD_GO_AS_PASSENGER;
														Legion::Data[i][Legion::WaitForDriver] = GetTickCount()+10000;
														Legion::SetNextCommandTime(i,Legion::Data[i][Legion::WaitForDriver]+1000);
														Legion::SetInterest(i,LEGION_INTEREST_DEFUALT);
														Legion::SetInterestPos(i,x,y,z);
														Legion::SetDefendingArea(i,minx,miny,maxx,maxy);
														Legion::Data[i][Legion::GotoX] = Legion::Data[npcid][Legion::GotoX];
														Legion::Data[i][Legion::GotoY] = Legion::Data[npcid][Legion::GotoY];
														Legion::Data[i][Legion::GotoZ] = Legion::Data[npcid][Legion::GotoZ];
														FCNPC::Stop(i);
														FCNPC::EnterVehicle(i,vehicleid,seatid,FCNPC_MOVE_TYPE_SPRINT);
														max_passengers--;
														seatid++;
													}
												}
											}
										}
									}
								} else {
									new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz;
									GetVehiclePos(vehicleid,tx,ty,tz);
									FCNPC::GetPosition(npcid,x,y,z);
									Legion::MoveWithPath(npcid,x,y,z,tx,ty,tz,FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT);
								}
							} else {
								new Float:x,Float:y,Float:z;
								FCNPC::GetPosition(npcid,x,y,z);
								Legion::MoveWithPath(npcid,x,y,z,Legion::Data[npcid][Legion::GotoX],Legion::Data[npcid][Legion::GotoY],Legion::Data[npcid][Legion::GotoZ],FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT);
							}
						}
					}
				}
			}
			case LEGION_STATE_VEHICLE_DRIVER: {
				switch(Legion::Data[npcid][Legion::Command]){
					case LEGION_CMD_GET_PASSENGERS: {
						if(GetTickCount() >= Legion::Data[npcid][Legion::WaitForPassengers] && Legion::Data[npcid][Legion::WaitForPassengers] != 0){
							Legion::Data[npcid][Legion::WaitForPassengers] = 0;
							new Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:maxx,Float:maxy;
							FCNPC::GetPosition(npcid,x,y,z);
							Legion::Data[npcid][Legion::Command] = LEGION_CMD_GOTO_POINT;
							Legion::MoveWithPath(npcid,x,y,z,Legion::Data[npcid][Legion::GotoX],Legion::Data[npcid][Legion::GotoY],Legion::Data[npcid][Legion::GotoZ],FCNPC_MOVE_TYPE_DRIVE,FCNPC_MOVE_SPEED_AUTO);
							new vid = FCNPC::GetVehicleID(npcid);
							Legion::GetInterestPos(npcid,x,y,z);
							Legion::GetDefendingArea(npcid,minx,miny,maxx,maxy);
							Tryg3D::Foreach(i){
								if(Legion::Data[i][Legion::active] && i != npcid){
									if(Legion::Data[i][Legion::State] == LEGION_STATE_VEHICLE_PASSENGER){
										if(FCNPC::GetVehicleID(i) == vid){
											Legion::SetNextCommandTime(npcid,GetTickCount()+10000);
											Legion::SetInterest(npcid,LEGION_INTEREST_DEFUALT);
											Legion::SetInterestPos(npcid,x,y,z);
											Legion::SetDefendingArea(npcid,minx,miny,maxx,maxy);
										}
									}
								}
							}
						}
					}
				}
				if(IsPlayerConnected(Legion::GetTarget(npcid,25.0))){
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						new Float:x,Float:y,Float:z;
						GetVehiclePos(FCNPC::GetVehicleID(npcid),x,y,z);
						SetVehiclePos(FCNPC::GetVehicleID(npcid),x,y,z);
						Legion::Data[npcid][Legion::WaitForPassengers] = 0;
						Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
						FCNPC::Stop(npcid);
						Legion::LockVehicleForNPC(npcid,FCNPC::GetVehicleID(npcid),false);
						FCNPC::ExitVehicle(npcid);
					}
				}
			}
			case LEGION_STATE_VEHICLE_PASSENGER: {
				if(IsPlayerConnected(Legion::GetTarget(npcid,25.0))){
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						if(IsPlayerInAnyVehicle(npcid)){
							if(GetVehicleSpeed(FCNPC::GetVehicleID(npcid)) <= 0.0){
								Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
								FCNPC::ExitVehicle(npcid);
							}
						}
					}
				}
				if(GetTickCount() >= Legion::Data[npcid][Legion::WaitForDriver] && Legion::Data[npcid][Legion::WaitForDriver] != 0){
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						if(FCNPC::GetVehicleID(GetVehicleDriver(FCNPC::GetVehicleID(npcid))) != FCNPC::GetVehicleID(npcid)){
							Legion::SetInterest(npcid,0);
							Legion::Data[npcid][Legion::WaitForDriver] = 0;
							Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
							FCNPC::ExitVehicle(npcid);
						}
					}
				}
			}
		}
	}
	return 1;
}

public FCNPC::OnFinishMovePath(npcid, pathid){
	if(pathid == Legion::Data[npcid][Legion::MovePath]){
		Legion::ClearMovePath(npcid);
		switch(Legion::Data[npcid][Legion::Command]){
			case LEGION_CMD_GOTO_POINT: {
				switch(Legion::Data[npcid][Legion::State]){
					case LEGION_STATE_VEHICLE_DRIVER: {
						new vehicleid = FCNPC::GetVehicleID(npcid);
						Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
						FCNPC::ExitVehicle(npcid);
						Tryg3D::Foreach(i){
							if(i != npcid && IsPlayerNPC(i)){
								if(FCNPC::GetVehicleID(i) == vehicleid){
									if(Legion::Data[i][Legion::State] == LEGION_STATE_VEHICLE_PASSENGER){
										Legion::Data[i][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
										FCNPC::ExitVehicle(i);
									}
								}
							}
						}
					}
					case LEGION_STATE_ONFOOT: {
						new Float:tx,Float:ty,Float:tz;
						FCNPC::GetPosition(npcid,tx,ty,tz);
						if(GetDistanceBetweenPoints3D(Legion::Data[npcid][Legion::GotoX],Legion::Data[npcid][Legion::GotoY],Legion::Data[npcid][Legion::GotoZ],tx,ty,tz) < 3.0){
							if(Legion::Data[npcid][Legion::PathID] != FCNPC_INVALID_MOVEPATH_ID){
								FCNPC::GoByMovePath(npcid,Legion::Data[npcid][Legion::PathID],0,FCNPC_MOVE_TYPE_WALK,FCNPC_MOVE_SPEED_WALK,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
							}
							Legion::Data[npcid][Legion::DefendingZone] = true;
							Legion::Data[npcid][Legion::Command] = LEGION_CMD_GOTO_CP;
							Legion::SyncArea(npcid);
						} else {
							Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
							Legion::SyncArea(npcid);
						}
					}
				}
			}
		}
	}
	return 1;
}

public FCNPC::OnVehicleEntryComplete(npcid, vehicleid, seatid){
	if(seatid == 0){
		Legion::Data[npcid][Legion::State] = LEGION_STATE_VEHICLE_DRIVER;
	} else {
		Legion::Data[npcid][Legion::State] = LEGION_STATE_VEHICLE_PASSENGER;
	}
	return 1;
}

public FCNPC::OnVehicleExitComplete(npcid, vehicleid){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,targetid,Float:target_z,Float:tmp_float;
	GetVehiclePos(vehicleid,x,y,z);
	FCNPC::GetPosition(npcid,tx,ty,tz);
	GetPointFor2Point2DEx(x,y,tx,ty,3.0,tx,ty);
	ColAndreas::FindGroundZ(tx,ty,tz,target_z);
	if(IsPointInUnderground(tx,ty,target_z+LEGION_Z_DIFF) && !ColAndreas::RayCastLine(tx,ty,tz,tx,ty,tz-1000.0,tmp_float,tmp_float,tmp_float)){
		ColAndreas::FindZ_For2DCoord(tx,ty,target_z);
	}
	FCNPC::SetPosition(npcid,tx,ty,(target_z+LEGION_Z_DIFF));
	targetid = Legion::GetTarget(npcid);
	if(IsPlayerConnected(targetid)){
		GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
		FCNPC::SetTargetAngle(npcid,x,y);
		Legion::StartAttack(npcid,true);
	}
	Legion::SyncArea(npcid);
	Legion::ClearMovePath(npcid);
	if(GetDistanceBetweenPoints3D(Legion::Data[npcid][Legion::GotoX],Legion::Data[npcid][Legion::GotoY],Legion::Data[npcid][Legion::GotoZ],tx,ty,tz) < 10.0){
		if(Legion::Data[npcid][Legion::PathID] != FCNPC_INVALID_MOVEPATH_ID){
			FCNPC::GoByMovePath(npcid,Legion::Data[npcid][Legion::PathID],0,FCNPC_MOVE_TYPE_SPRINT,FCNPC_MOVE_SPEED_SPRINT,FCNPC_MOVE_MODE_NONE,FCNPC_MOVE_PATHFINDING_NONE,0.0,true);
		}
		Legion::Data[npcid][Legion::DefendingZone] = true;
		Legion::Data[npcid][Legion::Command] = LEGION_CMD_GOTO_CP;
	} else {
		Legion::Data[npcid][Legion::Command] = LEGION_CMD_MOVE_NEARBY;
	}
	Legion::Data[npcid][Legion::State] = LEGION_STATE_ONFOOT;
	Legion::ClearMovePath(npcid);
	return 1;
}

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	if(IsValidDynamicArea(areaid)){
		if(!IsPlayerNPC(playerid)){
			new npcid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID) - LEGION_EXTRA_ID_OFFSET_A;
			if(npcid >= 0 && npcid < MAX_PLAYERS){
				if(Legion::Data[npcid][Legion::ears] == areaid){
					switch(Legion::Data[npcid][Legion::State]){
						case LEGION_STATE_ONFOOT: {
							if(Legion::Data[npcid][Legion::LastTarget] == INVALID_PLAYER_ID){
								if(Legion::Data[npcid][Legion::Agresive]){
									Legion::Data[npcid][Legion::LastTarget] = playerid;
									Legion::StartAttack(npcid,true);
									new Float:x,Float:y,Float:z;
									GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
									FCNPC::SetTargetAngle(npcid,x,y);
								}
							} else if(Item::GetDistance(playerid,item_player,npcid,item_fcnpc) < Item::GetDistance(Legion::Data[npcid][Legion::LastTarget],item_player,npcid,item_fcnpc)){
								Legion::Data[npcid][Legion::LastTarget] = playerid;
								Legion::StartAttack(npcid,true);
								new Float:x,Float:y,Float:z;
								GetPlayerPos(Legion::Data[npcid][Legion::LastTarget],x,y,z);
								FCNPC::SetTargetAngle(npcid,x,y);
							}
						}
						case LEGION_STATE_ENTER_VEHICLE: {
							if(Legion::Data[npcid][Legion::Agresive]){
								if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
									FCNPC::Stop(npcid);
									Legion::SyncArea(npcid);
									Legion::Data[npcid][Legion::State] = LEGION_STATE_ONFOOT;
									Legion::ClearMovePath(npcid);
								}
							}
						}
						case LEGION_STATE_VEHICLE_DRIVER: {
							if(Legion::Data[npcid][Legion::Agresive]){
								if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
									Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
									FCNPC::Stop(npcid);
									Legion::LockVehicleForNPC(npcid,FCNPC::GetVehicleID(npcid),false);
									FCNPC::ExitVehicle(npcid);
									Legion::ClearMovePath(npcid);
								}
							}
						}
						case LEGION_STATE_VEHICLE_PASSENGER: {
							if(Legion::Data[npcid][Legion::Agresive]){
								if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
									if(GetVehicleSpeed(FCNPC::GetVehicleID(npcid)) <= 0.0){
										Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
										FCNPC::ExitVehicle(npcid);
										Legion::ClearMovePath(npcid);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	#if defined Legion_OnPlayerEnterDynamicArea
		Legion_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea Legion_OnPlayerEnterDynamicArea
#if defined Legion_OnPlayerEnterDynamicArea
	forward Legion_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid, killerid, reason){
	Tryg3D::Foreach(npcid){
		if(IsPlayerNPC(npcid)){
			if(Legion::Data[npcid][Legion::active]){
				if(Legion::Data[npcid][Legion::LastTarget] == playerid){
					Legion::StopAttack(npcid);
				}
			}
		}
	}
	if(FCNPC::IsValid(killerid)){
		if(Legion::Data[killerid][Legion::active]){
			if(Legion::GetInterest(killerid) < LEGION_INTEREST_MAX){
				Legion::SetInterest(killerid,Legion::GetInterest(killerid)+1);
			}
		}
	}
	#if defined Legion_OnPlayerDeath
		Legion_OnPlayerDeath(playerid, killerid, reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath Legion_OnPlayerDeath
#if defined Legion_OnPlayerDeath
	forward Legion_OnPlayerDeath(playerid, killerid, reason);
#endif

//Hook: OnVehicleDeath
public OnVehicleDeath(vehicleid,killerid){
	Tryg3D::Foreach(npcid){
		if(IsPlayerNPC(npcid)){
			if(FCNPC::GetVehicleID(npcid) == vehicleid){
				if(Legion::Data[npcid][Legion::active]){
					if(IsCollisionFlag(Item::GetCollisionFlags(npcid,item_fcnpc),POSITION_FLAG_GROUND)){
						Legion::Data[npcid][Legion::State] = LEGION_STATE_EXIT_VEHICLE;
						FCNPC::Stop(npcid);
						FCNPC::ExitVehicle(npcid);
						Legion::ClearMovePath(npcid);
					} else {
						FCNPC::SetHealth(npcid,0.0);
					}
				}
			}
		}
	}
	Legion::VehicleLock[vehicleid] = INVALID_VEHICLE_ID;
	#if defined Legion_OnVehicleDeath
		Legion_OnVehicleDeath(vehicleid,killerid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath Legion_OnVehicleDeath
#if defined Legion_OnVehicleDeath
	forward Legion_OnVehicleDeath(vehicleid,killerid);
#endif

new bool:CRC_LegionInit = true,
	bool:CRC_LegionExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_LegionInit){
		CRC_LegionInit = false;
		Legion::Init();
	}
	#if defined Legion_OnFilterScriptInit
		Legion_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Legion_OnFilterScriptInit
#if defined Legion_OnFilterScriptInit
	forward Legion_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_LegionInit){
		CRC_LegionInit = false;
		Legion::Init();
	}
	#if defined Legion_OnGameModeInit
		Legion_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Legion_OnGameModeInit
#if defined Legion_OnGameModeInit
	forward Legion_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_LegionExit){
		CRC_LegionExit = false;
		Legion::Exit();
	}
	#if defined Legion_OnFilterScriptExit
		Legion_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit Legion_OnFilterScriptExit
#if defined Legion_OnFilterScriptExit
	forward Legion_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_LegionExit){
		CRC_LegionExit = false;
		Legion::Exit();
	}
	#if defined Legion_OnGameModeExit
		Legion_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit Legion_OnGameModeExit
#if defined Legion_OnGameModeExit
	forward Legion_OnGameModeExit();
#endif
//EOF
