/*
 Hunting.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: Katarina Calzaghe

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg

 File Version: 1.4.3
 Streamer Version: 2.9.4
 ColAndreas Version: 1.5.0
 3DTryg Version: 5.1.0

 Functions:
 Hunting::Create(type,Float:x,Float:y,Float:z,Float:health,respawntime,worldid=-1,interiorid=-1,playerid=-1,Float:streamdistance=200.0,moving_area = 0);
 Hunting::Destroy(mobid);
 Hunting::Respawn(mobid);
 Hunting::ForceRespawn(mobid,Float:x,Float:y,Float:z);
 Hunting::Kill(mobid,playerid=INVALID_PLAYER_ID);
 Hunting::Stop(mobid,delay=-1);
 Hunting::GoTo(mobid,Float:x,Float:y,bool:disable_moving=false);
 Hunting::GetDrop(mobid);
 Hunting::SetDrop(mobid,drop);
 Hunting::GetPos(mobid,Float:x,Float:y,Float:z);
 Hunting::SetPos(mobid,Float:x,Float:y,Float:z,bool:disable_moving=false);
 Hunting::GetScaredRange(mobid);
 Hunting::SetScaredRange(mobid,Float:range);
 Hunting::GetHealth(mobid);
 Hunting::SetHealth(mobid,Float:health);
 Hunting::GetSpawnHealth(mobid);
 Hunting::SetSpawnHealth(mobid,Float:health);
 Hunting::GetRespawnTime(mobid);
 Hunting::SetRespawnTime(mobid,respawntime);
 Hunting::GetSpawn(mobid,&Float:x,&Float:y,&Float:z);
 Hunting::SetSpawn(mobid,Float:x,Float:y,Float:z);
 Hunting::GetInterior(mobid);
 Hunting::SetInterior(mobid,interiorid);
 Hunting::GetVirtualWorld(mobid);
 Hunting::SetVirtualWorld(mobid,worldid);
 Hunting::GetSpeed(mobid);
 Hunting::SetSpeed(mobid,Float:speed);
 Hunting::GetPressTime(mobid);
 Hunting::SetPressTime(mobid,miliseconds);
 Hunting::GetFacingAngle(mobid);
 Hunting::SetCalmTime(mobid,time=0);
 Hunting::IsPlayerInRange(playerid,mobid,Float:range);
 Hunting::IsToggledMoving(mobid);
 Hunting::ToggleMoving(mobid,toggle);
 Hunting::IsValid(mobid);
 Hunting::IsSpawned(mobid);
 Hunting::IsDead(mobid);
 Hunting::IsScared(mobid);
 Hunting::IsStopped(mobid);
 Hunting::IsMoving(mobid);

 Extended Functions:
 Hunting::Count();
 Hunting::GetKey();
 Hunting::SetKey(key);
 Hunting::GetFreeID();
 Hunting::GetActiveMob(playerid,mob_state);

 Callbacks:
 OnPlayerTakeHuntDrop(playerid,mobid,drop); //return 0 set drop flag 0
 OnPlayerKillHuntAnimal(playerid,mobid);
 OnPlayerApproachingAnimal(playerid,mobid,mob_state);
 OnPlayerExitApproachingAnimal(playerid,mobid,mob_state);
 OnAnimalTakeDamage(mobid,playerid,Float:amount,weaponid);
 OnHuntAnimalRespawn(mobid);
 OnAnimalScareStateChanged(mobid,playerid,isscared);
 OnPlayerHuntDropStateChange(playerid,mobid,drop_state);
*/
 
#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] This include required Streamer v2.9.4 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS_VERSION
	#error [ADM] This include required ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#elseif (COLANDREAS_VERSION < 10500)
	#error [ADM] Update your ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] This include required 3DTryg.inc v5.1.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to v5.1.0
#elseif (TRYG3D_VERSION < 50100)
	#error [ADM] Update your 3DTryg.inc to v5.1.0
#endif

#if !defined TRYG3D_COLANDREAS
	#error [ADM] Module not initialized: TRYG3D_COLANDREAS
#endif

#if defined _hunting_system
	#endinput
#endif
#define _hunting_system
#define DYNAMIC_FILTERSCRIPT					"ALS:HOOK:METHOD"

#define Hunting::								Hunt_

#if !defined MAX_HUNTING_ANIMALS
	#define MAX_HUNTING_ANIMALS					(100)
#endif

#if !defined HUNTING_UPDATE_INTERVAL
	#define HUNTING_UPDATE_INTERVAL				(500)
#endif

#define HUNT_EXTRA_ID_OFFSET					(600000)
#define HUNT_EXTRA_ID_OFFSET_B					(HUNT_EXTRA_ID_OFFSET + MAX_HUNTING_ANIMALS)

#define HUNTING_TYPE_COW						(19833)
#define HUNTING_TYPE_DEER						(19315)

#define HUNTING_STATE_DESTROYED					(0)
#define HUNTING_STATE_SPAWNED					(1)
#define HUNTING_STATE_DEAD						(2)

#define HUNTING_DROP_STATE_FINISH				(0)
#define HUNTING_DROP_STATE_START				(1)
#define HUNTING_DROP_STATE_INTERRUPT			(2)

#define INVALID_HUNTING_ID						(0)

#define HUNTING_NO_AUTO_RESPAWN					(-1)

enum Hunting::enum {
	STREAMER_TAG_OBJECT:Hunting::objectid,
	STREAMER_TAG_AREA:Hunting::drop_area,
	STREAMER_TAG_AREA:Hunting::scared_area,
	STREAMER_TAG_AREA:Hunting::areaid,
	Hunting::type,
	Float:Hunting::health,
	Float:Hunting::spawn_health,
	Hunting::state,
	Hunting::respawntime,
	Hunting::drop,
	Hunting::respawn_tick,
	Float:Hunting::X,
	Float:Hunting::Y,
	Float:Hunting::Z,
	Float:Hunting::tX,
	Float:Hunting::tY,
	Float:Hunting::rZ,
	Float:Hunting::speed,
	Hunting::moving,
	Hunting::calm,
	Hunting::press_time,
	Hunting::last_scared,
	Hunting::stop_delay,
	Hunting::last_respawn
}

new Hunting::Data[MAX_HUNTING_ANIMALS][Hunting::enum],
	Hunting::Upperbound = 0,
	Hunting::Key = KEY_YES,
	Hunting::Timer = -1,
	Hunting::PlayerPress[MAX_PLAYERS];
	
#if defined OnPlayerTakeHuntDrop
	forward OnPlayerTakeHuntDrop(playerid,mobid,drop);
#endif

#if defined OnPlayerKillHuntAnimal
	forward OnPlayerKillHuntAnimal(playerid,mobid);
#endif

#if defined OnPlayerApproachingAnimal
	forward OnPlayerApproachingAnimal(playerid,mobid,mob_state);
#endif

#if defined OnPlayerExitApproachingAnimal
	forward OnPlayerExitApproachingAnimal(playerid,mobid,mob_state);
#endif

#if defined OnAnimalTakeDamage
	forward OnAnimalTakeDamage(mobid,playerid,Float:amount,weaponid);
#endif

#if defined OnHuntAnimalRespawn
	forward OnHuntAnimalRespawn(mobid);
#endif

#if defined OnAnimalScareStateChanged
	forward OnAnimalScareStateChanged(mobid,playerid,isscared);
#endif

#if defined OnPlayerHuntDropStateChange
	forward OnPlayerHuntDropStateChange(playerid,mobid,drop_state);
#endif

#define Hunt_GetKey()							Hunting::Key
#define Hunt_SetKey(%0)							Hunting::Key = (%0)

#define Hunt_SetDrop(%0,%1)						Hunting::Data[(%0)][Hunting::drop] = (%1)
#define Hunt_GetDrop(%0)						Hunting::Data[(%0)][Hunting::drop]

#define Hunt_ToggleMoving(%0,%1)				Hunting::Data[(%0)][Hunting::moving] = (%1)
#define Hunt_IsToggledMoving(%0)				Hunting::Data[(%0)][Hunting::moving]

#define Hunt_GetPos(%0,%1,%2,%3)				GetDynamicObjectPos(Hunting::Data[(%0)][Hunting::objectid],(%1),(%2),(%3))

#define Hunt_GetHealth(%0)						Hunting::Data[(%0)][Hunting::health]
#define Hunt_SetHealth(%0,%1)					Hunting::Data[(%0)][Hunting::health] = (%1)

#define Hunt_GetSpawnHealth(%0)					Hunting::Data[(%0)][Hunting::spawn_health]
#define Hunt_SetSpawnHealth(%0,%1)				Hunting::Data[(%0)][Hunting::spawn_health] = (%1)

#define Hunt_GetRespawnTime(%0)					Hunting::Data[(%0)][Hunting::respawntime]
#define Hunt_SetRespawnTime(%0,%1)				Hunting::Data[(%0)][Hunting::respawntime] = (%1)

#define Hunt_IsValid(%0)						(Hunting::Data[(%0)][Hunting::state] != HUNTING_STATE_DESTROYED)
#define Hunt_IsSpawned(%0)						(Hunting::Data[(%0)][Hunting::state] == HUNTING_STATE_SPAWNED)
#define Hunt_IsDead(%0)							(Hunting::Data[(%0)][Hunting::state] == HUNTING_STATE_DEAD)

#define Hunt_GetSpeed(%0)						Hunting::Data[(%0)][Hunting::speed]
#define Hunt_SetSpeed(%0,%1)					Hunting::Data[(%0)][Hunting::speed] = (%1)

#define Hunt_GetPressTime(%0)					Hunting::Data[(%0)][Hunting::press_time]
#define Hunt_SetPressTime(%0,%1)				Hunting::Data[(%0)][Hunting::press_time] = (%1)

#define Hunt_IsScared(%0)						(Hunting::Data[(%0)][Hunting::calm] != 0)

#define Hunt_IsStopped(%0)						(Hunting::Data[(%0)][Hunting::stop_delay] != 0 || !Hunting::Data[(%0)][Hunting::moving])

stock Hunting::Count(){
	new cnt = 0;
	for(new mobid = 1; mobid <= Hunting::Upperbound; mobid++){
		if(Hunting::IsValid(mobid)) cnt++;
	}
	return cnt;
}

stock Hunting::GetFreeID(){
	for(new mobid = 1; mobid < MAX_HUNTING_ANIMALS; mobid++){
		if(!Hunting::IsValid(mobid)) return mobid;
	}
	return INVALID_HUNTING_ID;
}

stock Hunting::Construct(){
	new Hunting::data_construct[Hunting::enum];
	
	Hunting::data_construct[Hunting::speed] = 0.8;
	Hunting::data_construct[Hunting::last_scared] = INVALID_PLAYER_ID;
	
	return Hunting::data_construct;
}

stock Hunting::SetCalmTime(mobid,time=0){		
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	if(!Hunting::IsScared(mobid)) return 0;
	Hunting::Data[mobid][Hunting::calm] = GetTickCount() + time;
	return 1;
}

stock Hunting::Stop(mobid,delay=-1){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(delay > 0){
		Hunting::ToggleMoving(mobid,0);
		Hunting::Data[mobid][Hunting::stop_delay] = GetTickCount() + delay;
	} else {
		Hunting::Data[mobid][Hunting::stop_delay] = 0;
		if(delay != -1) Hunting::ToggleMoving(mobid,0);
	}
	StopDynamicObject(Hunting::Data[mobid][Hunting::objectid]);
	return 1;
}

stock Hunting::IsMoving(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	new Float:x,Float:y,Float:z;
	Hunting::GetPos(mobid,x,y,z);
	return (GetDistanceBetweenPoints2D(Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],x,y) > 0.0);
}

stock Hunting::SetSpawn(mobid,Float:x,Float:y,Float:z){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	Hunting::Data[mobid][Hunting::X] = x;
	Hunting::Data[mobid][Hunting::Y] = y;
	Hunting::Data[mobid][Hunting::Z] = z;
	return 1;
}

stock Hunting::GetSpawn(mobid,&Float:x,&Float:y,&Float:z){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	x = Hunting::Data[mobid][Hunting::X];
	y = Hunting::Data[mobid][Hunting::Y];
	z = Hunting::Data[mobid][Hunting::Z];
	return 1;
}

stock Float:Hunting::GetScaredRange(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0.0;
	if(!Hunting::IsValid(mobid)) return 0.0;
	new Float:Hunting::range;
	Streamer::GetFloatData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::scared_area],E_STREAMER_SIZE,Hunting::range);
	return Hunting::range;
}

stock Hunting::SetScaredRange(mobid,Float:range){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	Streamer::SetFloatData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::scared_area],E_STREAMER_SIZE,range);
	return 1;
}

stock Hunting::GetInterior(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	return Streamer::GetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_INTERIOR_ID);
}

stock Hunting::SetInterior(mobid,interiorid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_INTERIOR_ID,interiorid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::drop_area],E_STREAMER_INTERIOR_ID,interiorid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::scared_area],E_STREAMER_INTERIOR_ID,interiorid);
	return 1;
}

stock Hunting::GetVirtualWorld(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	return Streamer::GetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_WORLD_ID);
}

stock Hunting::SetVirtualWorld(mobid,worldid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_WORLD_ID,worldid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::drop_area],E_STREAMER_WORLD_ID,worldid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::scared_area],E_STREAMER_WORLD_ID,worldid);
	return 1;
}

stock Hunting::GoTo(mobid,Float:x,Float:y,bool:disable_moving=false){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsSpawned(mobid)) return 0;
	
	new Float:z;
	ColAndreas::FindZ_For2DCoord(x,y,z);
	if(IsPointInWater(x,y) || IsPointInUnderground(x,y,z)) return 0;
	if(Hunting::Data[mobid][Hunting::areaid] != STREAMER_TAG_AREA:INVALID_STREAMER_ID){
		if(!IsPointInDynamicArea(Hunting::Data[mobid][Hunting::areaid],x,y,z)) return 0;
	}
	
	new F4[Vectors3D], tmp_moving = Hunting::IsToggledMoving(mobid);
	
	Hunting::ToggleMoving(mobid,0);
	Hunting::Stop(mobid);
	Hunting::GetPos(mobid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
	
	Hunting::Data[mobid][Hunting::tX] = x;
	Hunting::Data[mobid][Hunting::tY] = y;
	GetRotationFor2Point2D(F4[T3D:X],F4[T3D:Y],x,y,Hunting::Data[mobid][Hunting::rZ]);
	
	if(!disable_moving){
		Hunting::ToggleMoving(mobid,1);
	} else {
		Hunting::ToggleMoving(mobid,tmp_moving);
	}
	return 1;
}

stock Hunting::SetPos(mobid,Float:x,Float:y,Float:z,bool:disable_moving=false){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	
	if(IsPointInWater(x,y) || IsPointInUnderground(x,y,z)) return 0;
	if(Hunting::Data[mobid][Hunting::areaid] != STREAMER_TAG_AREA:INVALID_STREAMER_ID){
		if(!IsPointInDynamicArea(Hunting::Data[mobid][Hunting::areaid],x,y,z)) return 0;
	}
	
	new tmp_moving = Hunting::IsToggledMoving(mobid);
	
	Hunting::ToggleMoving(mobid,0);
	Hunting::Stop(mobid);
	
	SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],x,y,z);
	
	Hunting::Data[mobid][Hunting::tX] = x;
	Hunting::Data[mobid][Hunting::tY] = y;
	
	if(!disable_moving){
		Hunting::ToggleMoving(mobid,1);
	} else {
		Hunting::ToggleMoving(mobid,tmp_moving);
	}
	return 1;
}

stock Hunting::Create(type,Float:x,Float:y,Float:z,Float:health,respawntime,worldid=-1,interiorid=-1,playerid=-1,Float:streamdistance=200.0,STREAMER_TAG_AREA:moving_area = STREAMER_TAG_AREA:INVALID_STREAMER_ID){
	new mobid = Hunting::GetFreeID();
	if(mobid == INVALID_HUNTING_ID){
		printf("[ADM] Error: Failed to Hunting::Create limit %d exceeded, add #define MAX_HUNTING_ANIMALS before Hunting.inc",MAX_HUNTING_ANIMALS);
		return mobid;
	}
	
	if(moving_area != STREAMER_TAG_AREA:INVALID_STREAMER_ID){
		if(!IsPointInDynamicArea(moving_area,x,y,z)){
			printf("[ADM] Error: Failed to Hunting::Create(%d,%f,%f,%f,...) position out of moving_area",type,x,y,z);
			return INVALID_HUNTING_ID;
		}
	} 
	if(IsPointInWater(x,y) || IsPointInUnderground(x,y,z)){
		printf("[ADM] Error: Failed to Hunting::Create(%d,%f,%f,%f,...) position out of world",type,x,y,z);
		return INVALID_HUNTING_ID;
	}
	
	Hunting::Data[mobid] = Hunting::Construct();
	
	new Float:tmp_float,Float:target_z;
	MovePointCol(x,y,z+1.0,x,y,-100.0,tmp_float,tmp_float,target_z);
	z = target_z;
	switch(type){
		case HUNTING_TYPE_COW: {
			Hunting::Data[mobid][Hunting::objectid] = CreateDynamicObject(type,x,y,z,0.0,0.0,184.0,worldid,interiorid,playerid,streamdistance);
		}
		case HUNTING_TYPE_DEER: {
			z += 0.5;
			Hunting::Data[mobid][Hunting::objectid] = CreateDynamicObject(type,x,y,z,0.0,0.0,90.0,worldid,interiorid,playerid,streamdistance);
		}
	}
	Hunting::Data[mobid][Hunting::drop_area] = CreateDynamicSphere(x,y,z,3.0,worldid,interiorid,playerid);
	Hunting::Data[mobid][Hunting::scared_area] = CreateDynamicSphere(x,y,z,5.0,worldid,interiorid,playerid);
	
	AttachDynamicAreaToObject(Hunting::Data[mobid][Hunting::drop_area],Hunting::Data[mobid][Hunting::objectid]);
	AttachDynamicAreaToObject(Hunting::Data[mobid][Hunting::scared_area],Hunting::Data[mobid][Hunting::objectid]);
	
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_EXTRA_ID,(mobid+HUNT_EXTRA_ID_OFFSET));
	Streamer::SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::drop_area],E_STREAMER_EXTRA_ID,(mobid+HUNT_EXTRA_ID_OFFSET));
	Streamer::SetIntData(STREAMER_TYPE_AREA,Hunting::Data[mobid][Hunting::scared_area],E_STREAMER_EXTRA_ID,(mobid+HUNT_EXTRA_ID_OFFSET_B));
	
	Hunting::Data[mobid][Hunting::areaid] = moving_area;
	
	Hunting::Data[mobid][Hunting::type] = type;
	Hunting::Data[mobid][Hunting::respawntime] = respawntime;
	Hunting::Data[mobid][Hunting::health] = health;
	Hunting::Data[mobid][Hunting::spawn_health] = health;
	Hunting::Data[mobid][Hunting::drop] = 1;
	Hunting::Data[mobid][Hunting::tX] = x;
	Hunting::Data[mobid][Hunting::tY] = y;
	Hunting::Data[mobid][Hunting::moving] = 1;
	Hunting::Data[mobid][Hunting::speed] = 0.8;
	Hunting::Data[mobid][Hunting::last_respawn] = 0;
	
	Hunting::SetSpawn(mobid,x,y,z);
	
	if(mobid > Hunting::Upperbound) Hunting::Upperbound = mobid;
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_SPAWNED;
	
	return mobid;
}

stock Hunting::Destroy(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DESTROYED;
	
	if(IsValidDynamicObject(Hunting::Data[mobid][Hunting::objectid])){
		DestroyDynamicObject(Hunting::Data[mobid][Hunting::objectid]);
		Hunting::Data[mobid][Hunting::objectid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Hunting::Data[mobid][Hunting::drop_area])){
		DestroyDynamicArea(Hunting::Data[mobid][Hunting::drop_area]);
		Hunting::Data[mobid][Hunting::drop_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Hunting::Data[mobid][Hunting::scared_area])){
		DestroyDynamicArea(Hunting::Data[mobid][Hunting::scared_area]);
		Hunting::Data[mobid][Hunting::scared_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	
	Hunting::Data[mobid] = Hunting::Construct();
	
	if(mobid == Hunting::Upperbound) Hunting::Upperbound--;
	return 1;
}

stock Hunting::Respawn(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	Hunting::Data[mobid][Hunting::respawn_tick] = 0;
	
	if(GetTickCount() - Hunting::Data[mobid][Hunting::last_respawn] < 50 && Hunting::Data[mobid][Hunting::last_respawn] != 0){
		printf("[ADM] Error: Failed to Hunting::Respawn(%d) must pass 50 ms before the next respawn",mobid);
		return 0;
	}
	Hunting::Data[mobid][Hunting::last_respawn] = GetTickCount();
	
	if(Hunting::IsSpawned(mobid)){
		Hunting::Stop(mobid);
	}
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DEAD;
	
	Hunting::Data[mobid][Hunting::health] = Hunting::Data[mobid][Hunting::spawn_health];
	Hunting::SetDrop(mobid,1);
	
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],0,0,"","",0);
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],1,0,"","",0);
	new modelid = Streamer::GetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_MODEL_ID);
	Streamer::SetIntData(STREAMER_TYPE_OBJECT,Hunting::Data[mobid][Hunting::objectid],E_STREAMER_MODEL_ID,modelid);

	new Float:tmp_float,Float:target_z;
	MovePointCol(Hunting::Data[mobid][Hunting::X],Hunting::Data[mobid][Hunting::Y],Hunting::Data[mobid][Hunting::Z]+1.0,Hunting::Data[mobid][Hunting::X],Hunting::Data[mobid][Hunting::Y],-100.0,tmp_float,tmp_float,target_z);
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_DEER:	target_z += 0.5;
	}
	SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::X],Hunting::Data[mobid][Hunting::Y],target_z);
	
	Hunting::Data[mobid][Hunting::tX] = Hunting::Data[mobid][Hunting::X];
	Hunting::Data[mobid][Hunting::tY] = Hunting::Data[mobid][Hunting::Y];
	
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_COW:	SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,184.0);
		case HUNTING_TYPE_DEER:	SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,90.0);
	}
	
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_SPAWNED;
	#if defined OnHuntAnimalRespawn
		OnHuntAnimalRespawn(mobid);
	#endif
	return 1;
}

stock Hunting::IsPlayerInRange(playerid,mobid,Float:range){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	if(!IsPlayerConnected(playerid)) return 0;
	return (Item::GetDistance(playerid,item_player,Hunting::Data[mobid][Hunting::objectid],item_dynamic_object) <= range);
}

stock Float:Hunting::GetFacingAngle(mobid){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_COW:	return Tryg3D::CompressRotation(Hunting::Data[mobid][Hunting::rZ]+184.0);
		case HUNTING_TYPE_DEER:	return Tryg3D::CompressRotation(Hunting::Data[mobid][Hunting::rZ]+90.0);
	}
	return 1;
}

stock Hunting::ForceRespawn(mobid,Float:x,Float:y,Float:z){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsValid(mobid)) return 0;
	Hunting::SetSpawn(mobid,x,y,z);
	return Hunting::Respawn(mobid);
}

stock Hunting::Kill(mobid,playerid=INVALID_PLAYER_ID){
	if(mobid <= 0 || mobid >= MAX_HUNTING_ANIMALS) return 0;
	if(!Hunting::IsSpawned(mobid)) return 0;
	Hunting::Data[mobid][Hunting::state] = HUNTING_STATE_DEAD;
	Hunting::Data[mobid][Hunting::health] = 0.0;
	
	#if defined OnAnimalScareStateChanged
		if(Hunting::IsScared(mobid)){
			OnAnimalScareStateChanged(mobid,Hunting::Data[mobid][Hunting::last_scared],0);
		}
	#endif
	Hunting::Data[mobid][Hunting::calm] = 0;
	Hunting::Data[mobid][Hunting::last_scared] = INVALID_PLAYER_ID;
	
	Hunting::Stop(mobid);
	
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],0,2806,"CJ_MEATY","CJ_FLESH_1",0);
	SetDynamicObjectMaterial(Hunting::Data[mobid][Hunting::objectid],1,2806,"CJ_MEATY","CJ_FLESH_1",0);
	
	new Float:tmp_float,Float:target_z,Float:x,Float:y,Float:z;
	Hunting::GetPos(mobid,x,y,z);
	Hunting::SetPos(mobid,x,y,z);
	MovePointCol(x,y,z+1.0,x,y,-100.0,tmp_float,tmp_float,target_z);
	
	switch(Hunting::Data[mobid][Hunting::type]){
		case HUNTING_TYPE_COW:	MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],x,y,target_z+0.3,0.5,0.0,90.0);
		case HUNTING_TYPE_DEER:	MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],x,y,target_z+0.1,0.5,270.0);
	}
	
	Hunting::Data[mobid][Hunting::respawn_tick] = GetTickCount() + (1000 * Hunting::Data[mobid][Hunting::respawntime]);
	
	#if defined OnPlayerKillHuntAnimal
		OnPlayerKillHuntAnimal(playerid,mobid);
	#endif
	return 1;
}

stock Hunting::GetActiveMob(playerid,mob_state){
	new max_areas = GetPlayerNumberDynamicAreas(playerid);
	if(max_areas){
		new STREAMER_TAG_AREA:player_areas[128], mobid;
		GetPlayerDynamicAreas(playerid,player_areas,max_areas);
		for(new k = 0; k < max_areas; k++){
			if(k >= 128) break;
			mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID)-HUNT_EXTRA_ID_OFFSET;
			if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
				if(player_areas[k] == Hunting::Data[mobid][Hunting::drop_area]){
					if(mob_state == Hunting::Data[mobid][Hunting::state]){
						return mobid;
					}
				}
			}
			mobid = INVALID_HUNTING_ID;
		}
	}
	return INVALID_HUNTING_ID;
}

T3D:function Hunting::OnUpdate(){
	static	Float:tmp_float,Float:target_z,
			Float:x,Float:y,Float:z,
			Float:vx,Float:vy,Float:vz, cnt;
	
	for(new mobid = 1; mobid <= Hunting::Upperbound; mobid++){
		switch(Hunting::Data[mobid][Hunting::state]){
			case HUNTING_STATE_SPAWNED: {
				x = y = z = target_z = 0.0, cnt = 0;
				Hunting::GetPos(mobid,x,y,z);
				if(x == 0.0 && y == 0.0 && z == 0.0) continue;
				MovePointCol(x,y,z+1.0,x,y,-100.0,tmp_float,tmp_float,target_z);
				if(Hunting::IsToggledMoving(mobid)){
					if(GetDistanceBetweenPoints2D(Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],x,y) == 0.0){
						for(;;){
							cnt++;
							if(cnt >= 100) return 0;
							vx = vy = vz = 0.0;
							Random::PointInCircle(x,y,RandomFloat(5.0,25.0),vx,vy);
							if(GetDistanceBetweenPoints2D(x,y,vx,vy) <= 2.0 || IsPointInWater(vx,vy) || IsPointInUnderground(x,y,z+1.0)) continue;
							ColAndreas::FindZ_For2DCoord(vx,vy,vz);
							vz += 1.0;
							if(ColAndreas::RayCastLine(x,y,z+1.0,vx,vy,vz,tmp_float,tmp_float,tmp_float)) continue;
							if(Hunting::Data[mobid][Hunting::areaid] != STREAMER_TAG_AREA:INVALID_STREAMER_ID){
								if(!IsPointInDynamicArea(Hunting::Data[mobid][Hunting::areaid],vx,vy,vz)) continue;
							}
							if(Hunting::Data[mobid][Hunting::last_scared] != INVALID_PLAYER_ID){
								if(IsPlayerInRangeOfPoint(Hunting::Data[mobid][Hunting::last_scared],5.0,vx,vy,vz)) continue;
							}
							Hunting::Data[mobid][Hunting::tX] = vx;
							Hunting::Data[mobid][Hunting::tY] = vy;
							GetRotationFor2Point2D(x,y,vx,vy,Hunting::Data[mobid][Hunting::rZ]);
							break;
						}
					}
				} else {
					if(Hunting::Data[mobid][Hunting::stop_delay] != 0 && GetTickCount() >= Hunting::Data[mobid][Hunting::stop_delay]){
						Hunting::Data[mobid][Hunting::stop_delay] = 0;
						Hunting::ToggleMoving(mobid,1);
					}
				}
				if(GetTickCount() >= Hunting::Data[mobid][Hunting::calm] && Hunting::Data[mobid][Hunting::calm] != 0){
					Hunting::SetSpeed(mobid,0.8);
					#if defined OnAnimalScareStateChanged
						if(Hunting::IsScared(mobid)){
							OnAnimalScareStateChanged(mobid,Hunting::Data[mobid][Hunting::last_scared],0);
						}
					#endif
					Hunting::Data[mobid][Hunting::calm] = 0;
					Hunting::Data[mobid][Hunting::last_scared] = INVALID_PLAYER_ID;
				}
				switch(Hunting::Data[mobid][Hunting::type]){
					case HUNTING_TYPE_COW: {
						SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],x,y,target_z);
						SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,Tryg3D::CompressRotation(Hunting::Data[mobid][Hunting::rZ]+184.0));
						MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],target_z,Hunting::GetSpeed(mobid));
					}
					case HUNTING_TYPE_DEER: {
						SetDynamicObjectPos(Hunting::Data[mobid][Hunting::objectid],x,y,target_z+0.5);
						SetDynamicObjectRot(Hunting::Data[mobid][Hunting::objectid],0.0,0.0,Tryg3D::CompressRotation(Hunting::Data[mobid][Hunting::rZ]+90.0));
						MoveDynamicObject(Hunting::Data[mobid][Hunting::objectid],Hunting::Data[mobid][Hunting::tX],Hunting::Data[mobid][Hunting::tY],target_z+0.5,Hunting::GetSpeed(mobid));
					}
				}
			}
			case HUNTING_STATE_DEAD: {
				if(Hunting::Data[mobid][Hunting::respawntime] != HUNTING_NO_AUTO_RESPAWN){
					if(Hunting::Data[mobid][Hunting::respawn_tick] != 0 && GetTickCount() >= Hunting::Data[mobid][Hunting::respawn_tick]){
						Hunting::Respawn(mobid);
					}
				}
			}
		}
	}
	return 1;
}

//Hook: OnPlayerShootDynamicObject
public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z){
	new mobid = (Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID)-HUNT_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
		if(Hunting::Data[mobid][Hunting::objectid] == objectid && Hunting::IsSpawned(mobid)){
			Hunting::SetSpeed(mobid,8.0);
			Hunting::Data[mobid][Hunting::last_scared] = playerid;
			#if defined OnAnimalScareStateChanged
				if(!Hunting::IsScared(mobid)){
					OnAnimalScareStateChanged(mobid,playerid,1);
				}
			#endif
			Hunting::Data[mobid][Hunting::calm] = GetTickCount() + 30000;
			#if defined OnAnimalTakeDamage
				if(OnAnimalTakeDamage(mobid,playerid,Tryg3D::GetWeaponDamage(weaponid),weaponid)){
					Hunting::Data[mobid][Hunting::health] -= Tryg3D::GetWeaponDamage(weaponid);
				}
			#else
				Hunting::Data[mobid][Hunting::health] -= Tryg3D::GetWeaponDamage(weaponid);
			#endif
			if(Hunting::Data[mobid][Hunting::health] <= 0.0){
				Hunting::Kill(mobid,playerid);
			}
		}
	}
	#if defined HUN_OnPlayerShootDynamicObject
		HUN_OnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject HUN_OnPlayerShootDynamicObject
#if defined HUN_OnPlayerShootDynamicObject
	forward HUN_OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z);
#endif

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid){
	new Hunting::extraid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID), mobid;
	
	mobid = (Hunting::extraid - HUNT_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
		if(Hunting::Data[mobid][Hunting::drop_area] == areaid){
			#if defined OnPlayerApproachingAnimal
				OnPlayerApproachingAnimal(playerid,mobid,Hunting::Data[mobid][Hunting::state]);
			#endif
		}
	}
	
	mobid = (Hunting::extraid - HUNT_EXTRA_ID_OFFSET_B);
	if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
		if(Hunting::Data[mobid][Hunting::scared_area] == areaid){
			if(Hunting::Data[mobid][Hunting::state] == HUNTING_STATE_SPAWNED){
				Hunting::SetSpeed(mobid,8.0);
				Hunting::Data[mobid][Hunting::last_scared] = playerid;
				
				#if defined OnAnimalScareStateChanged
					if(!Hunting::IsScared(mobid)){
						OnAnimalScareStateChanged(mobid,playerid,1);
					}
				#endif
				
				Hunting::Data[mobid][Hunting::calm] = GetTickCount() + 30000;
			}
		}
	}	
	#if defined HUN_OnPlayerEnterDynamicArea
		HUN_OnPlayerEnterDynamicArea(playerid, areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea HUN_OnPlayerEnterDynamicArea
#if defined HUN_OnPlayerEnterDynamicArea
	forward HUN_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerLeaveDynamicArea
public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid){
	new Hunting::extraid = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID), mobid;
	
	mobid = (Hunting::extraid - HUNT_EXTRA_ID_OFFSET);
	if(mobid > 0 && mobid < MAX_HUNTING_ANIMALS){
		if(Hunting::Data[mobid][Hunting::drop_area] == areaid){
			#if defined OnPlayerExitApproachingAnimal
				OnPlayerExitApproachingAnimal(playerid,mobid,Hunting::Data[mobid][Hunting::state]);
			#endif
		}
	}
	
	#if defined HUN_OnPlayerLeaveDynamicArea
		HUN_OnPlayerLeaveDynamicArea(playerid, areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea HUN_OnPlayerLeaveDynamicArea
#if defined HUN_OnPlayerLeaveDynamicArea
	forward HUN_OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(Tryg3D::KeyPressed(Hunting::Key) && !IsPlayerInAnyVehicle(playerid)){
		new mobid = Hunting::GetActiveMob(playerid,HUNTING_STATE_DEAD);
		if(Hunting::GetPressTime(mobid) == 0){
			#if defined OnPlayerTakeHuntDrop
				Hunting::Data[mobid][Hunting::drop] = OnPlayerTakeHuntDrop(playerid,mobid,Hunting::Data[mobid][Hunting::drop]);
			#endif
		} else {
			#if defined OnPlayerHuntDropStateChange
				OnPlayerHuntDropStateChange(playerid,mobid,HUNTING_DROP_STATE_START);
			#endif
			Hunting::PlayerPress[playerid] = GetTickCount() + Hunting::GetPressTime(mobid);
		}
	}
	if(Tryg3D::KeyReleased(Hunting::Key) && !IsPlayerInAnyVehicle(playerid)){
		if(GetTickCount() >= Hunting::PlayerPress[playerid] && Hunting::PlayerPress[playerid] != 0){
			Hunting::PlayerPress[playerid] = 0;
			new mobid = Hunting::GetActiveMob(playerid,HUNTING_STATE_DEAD);
			if(Hunting::GetPressTime(mobid) > 0){
				#if defined OnPlayerHuntDropStateChange
					OnPlayerHuntDropStateChange(playerid,mobid,HUNTING_DROP_STATE_FINISH);
				#endif
				#if defined OnPlayerTakeHuntDrop
					Hunting::Data[mobid][Hunting::drop] = OnPlayerTakeHuntDrop(playerid,mobid,Hunting::Data[mobid][Hunting::drop]);
				#endif
			}
		} else {
			#if defined OnPlayerHuntDropStateChange
				new mobid = Hunting::GetActiveMob(playerid,HUNTING_STATE_DEAD);
				if(Hunting::GetPressTime(mobid) > 0){
					OnPlayerHuntDropStateChange(playerid,mobid,HUNTING_DROP_STATE_INTERRUPT);
				}
			#endif
		}
	}
	#if defined HUN_OnPlayerKeyStateChange
		HUN_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange HUN_OnPlayerKeyStateChange
#if defined HUN_OnPlayerKeyStateChange
	forward HUN_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

new bool:CRC_HuntingInit = true,
	bool:CRC_HuntingExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_HuntingInit){
		CRC_HuntingInit = false;
		Hunting::Timer = SetTimerEx("Hunt_OnUpdate",HUNTING_UPDATE_INTERVAL,true,"");
	}
	#if defined HUN_OnFilterScriptInit
		HUN_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit HUN_OnFilterScriptInit
#if defined HUN_OnFilterScriptInit
	forward HUN_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_HuntingInit){
		CRC_HuntingInit = false;
		Hunting::Timer = SetTimerEx("Hunt_OnUpdate",HUNTING_UPDATE_INTERVAL,true,"");
	}
	#if defined HUN_OnGameModeInit
		HUN_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit HUN_OnGameModeInit
#if defined HUN_OnGameModeInit
	forward HUN_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_HuntingExit){
		CRC_HuntingExit = false;
		KillTimer(Hunting::Timer);
	}
	#if defined HUN_OnFilterScriptExit
		HUN_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit HUN_OnFilterScriptExit
#if defined HUN_OnFilterScriptExit
	forward HUN_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_HuntingExit){
		CRC_HuntingExit = false;
		KillTimer(Hunting::Timer);
	}
	#if defined HUN_OnGameModeExit
		HUN_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit HUN_OnGameModeExit
#if defined HUN_OnGameModeExit
	forward HUN_OnGameModeExit();
#endif
