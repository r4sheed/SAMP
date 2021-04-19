/*
 vnpc.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: FCNPC
 Modules: None

 File Version: 1.1.0

 Functions:
 ShowNPCInTabList(npcid);
 HideNPCInTabList(npcid);
*/

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if !defined _FCNPC_included
	#error [ADM] You need FCNPC v2.0.0 (github.com/ziggi/FCNPC/releases)
#endif

#if defined _visible_npc_inc
	#endinput
#endif
#define _visible_npc_inc

#define VNPC::				VNPC_

new bool:VNPC::IsNPCVisible[MAX_PLAYERS],
	bool:VNPC::FirstSpawn[MAX_PLAYERS];
	
stock VNPC::ShowNPCInTabListForPlayer(playerid,npcid){
	if(!IsPlayerNPC(npcid)) return 0;
	FCNPC_ShowInTabListForPlayer(npcid,playerid);
	return 1;
}

stock VNPC::HideNPCInTabListForPlayer(playerid,npcid){
	if(!IsPlayerNPC(npcid)) return 0;
	FCNPC_HideInTabListForPlayer(npcid,playerid);
	return 1;
}

stock ShowNPCInTabList(npcid){
	if(!IsPlayerNPC(npcid)) return 0;
	VNPC::IsNPCVisible[npcid] = true;
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i) && !IsPlayerNPC(i)){
			VNPC::ShowNPCInTabListForPlayer(i,npcid);
		}
	}
	return 1;
}

stock HideNPCInTabList(npcid){
	if(!IsPlayerNPC(npcid)) return 0;
	VNPC::IsNPCVisible[npcid] = false;
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i) && !IsPlayerNPC(i)){
			VNPC::HideNPCInTabListForPlayer(i,npcid);
		}
	}
	return 1;
}

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	if(IsPlayerNPC(playerid)){
		VNPC::IsNPCVisible[playerid] = false;
	}
	VNPC::FirstSpawn[playerid] = false;
	#if defined VNPC_OnPlayerConnect
		VNPC_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect VNPC_OnPlayerConnect
#if defined VNPC_OnPlayerConnect
	forward VNPC_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	if(!VNPC::FirstSpawn[playerid]){
		VNPC::FirstSpawn[playerid] = true;
		for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
			if(IsPlayerConnected(i) && IsPlayerNPC(i)){
				if(VNPC::IsNPCVisible[i]){
					VNPC::ShowNPCInTabListForPlayer(playerid,i);
				}
			}
		}
	}
	#if defined VNPC_OnPlayerSpawn
		VNPC_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn VNPC_OnPlayerSpawn
#if defined VNPC_OnPlayerSpawn
	forward VNPC_OnPlayerSpawn(playerid);
#endif 

//EOF