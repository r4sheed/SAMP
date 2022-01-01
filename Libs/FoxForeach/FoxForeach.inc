/****************************************************************************************************
 *                                                                                                  *
 *                                      )(   FoX Foreach   )(                                       *
 *                                                                                                  *
 * Copyright © 2022 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Website: https://adm.ct8.pl                                                                      *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.2.1                                                                              *
 *                                                                                                  *
 * Functions:                                                                                       *
 * FoxForeach(variable,tag); //Tags: Player, Bot, Character                                         *
 *                                                                                                  *
 * Player Functions:                                                                                *
 * CountFoxPlayer();                                                                                *
 * FoxForeachRandomPlayer();                                                                        *
 * bool:IsPlayerInFoxPool(playerid);                                                                *
 *                                                                                                  *
 * Bot Functions:                                                                                   *
 * CountFoxBot();                                                                                   *
 * FoxForeachRandomBot();                                                                           *
 * bool:IsBotInFoxPool(playerid);                                                                   *
 *                                                                                                  *
 * Character Functions:                                                                             *
 * CountFoxCharacter();                                                                             *
 * FoxForeachRandomCharacter();                                                                     *
 * bool:IsCharacterInFoxPool(playerid);                                                             *
 *                                                                                                  *
 * Extended functions:                                                                              *
 * foX(variable,beginning,end);                                                                     *
 * PoolForeach(variable);                                                                           *
 *                                                                                                  *
 * Auto functions:                                                                                  *
 * FoxForeachInit();                                                                                *
 * bool:FoxAddPlayer(playerid);                                                                     *
 * bool:FoxRemovePlayer(playerid);                                                                  *
 * bool:FoxAddBot(playerid);                                                                        *
 * bool:FoxRemoveBot(playerid);                                                                     *
 * bool:FoxAddCharacter(playerid);                                                                  *
 * bool:FoxRemoveCharacter(playerid);                                                               *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined TRYG3D_SAMP_INCLUDE || defined _3D_Tryg
	#error [ADM] Please include FoxForeach before 3DTryg, for increase loop speed.
#endif

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if defined _FoX_Foreach
	#endinput
#endif
#define _FoX_Foreach

#define FoxForeach(%0,%1)				for(new %0 = Fox%1[0], i_%0 = 0; i_%0 <= Fox%1Upp; i_%0++, %0 = Fox%1[i_%0])
#define CountFoxPlayer()				(FoxPlayerUpp+1)
#define CountFoxBot()					(FoxBotUpp+1)
#define CountFoxCharacter()				(FoxCharacterUpp+1)

#define foX(%1,%2,%3)					for(new %1 = %2; %1 <= %3; %1++)

#if !defined PoolForeach
	#define PoolForeach(%1)				for(new %1 = 0, p_%1 = GetPlayerPoolSize(); %1 <= p_%1; %1++)
#endif

new FoxPlayer[MAX_PLAYERS],
	FoxBot[MAX_PLAYERS],
	FoxCharacter[MAX_PLAYERS],
	FoxPlayerUpp = -1,
	FoxBotUpp = -1,
	FoxCharacterUpp = -1;

stock bool:IsPlayerInFoxPool(playerid){
	for(new i = 0; i <= FoxPlayerUpp; i++){
		if(FoxPlayer[i] == playerid){
			return true;
		}
	}
	return false;
}

stock bool:FoxAddPlayer(playerid){
	if(IsPlayerInFoxPool(playerid)) return false;
	FoxPlayerUpp++;
	FoxPlayer[FoxPlayerUpp] = playerid;
	return true;
}

stock FoxForeachRandomPlayer(){
	if(FoxPlayerUpp == -1) return 0;
	new playerid = FoxPlayer[random(FoxPlayerUpp+1)];
	if(IsPlayerConnected(playerid)) return playerid;
	return 0;
}

stock bool:FoxRemovePlayer(playerid){
	if(!IsPlayerInFoxPool(playerid)) return false;
	for(new i = 0; i <= FoxPlayerUpp; i++){
		if(FoxPlayer[i] == playerid){
			if(FoxPlayerUpp == 0){
				FoxPlayer[i] = 0;
			} else if(i == FoxPlayerUpp){
				FoxPlayer[i] = 0;
			} else {
				FoxPlayer[i] = FoxPlayer[FoxPlayerUpp];
				FoxPlayer[FoxPlayerUpp] = 0;
			}
			FoxPlayerUpp--;
			break;
		}
	}
	return true;
}

stock bool:IsBotInFoxPool(playerid){
	for(new i = 0; i <= FoxBotUpp; i++){
		if(FoxBot[i] == playerid){
			return true;
		}
	}
	return false;
}

stock bool:FoxAddBot(playerid){
	if(IsBotInFoxPool(playerid)) return false;
	FoxBotUpp++;
	FoxBot[FoxBotUpp] = playerid;
	return true;
}

stock FoxForeachRandomBot(){
	if(FoxBotUpp == -1) return 0;
	new playerid = FoxBot[random(FoxBotUpp+1)];
	if(IsBotConnected(playerid)) return playerid;
	return 0;
}

stock bool:FoxRemoveBot(playerid){
	if(!IsBotInFoxPool(playerid)) return false;
	for(new i = 0; i <= FoxBotUpp; i++){
		if(FoxBot[i] == playerid){
			if(FoxBotUpp == 0){
				FoxBot[i] = 0;
			} else if(i == FoxBotUpp){
				FoxBot[i] = 0;
			} else {
				FoxBot[i] = FoxBot[FoxBotUpp];
				FoxBot[FoxBotUpp] = 0;
			}
			FoxBotUpp--;
			break;
		}
	}
	return true;
}

stock bool:IsCharacterInFoxPool(playerid){
	for(new i = 0; i <= FoxCharacterUpp; i++){
		if(FoxCharacter[i] == playerid){
			return true;
		}
	}
	return false;
}

stock bool:FoxAddCharacter(playerid){
	if(IsCharacterInFoxPool(playerid)) return false;
	FoxCharacterUpp++;
	FoxCharacter[FoxCharacterUpp] = playerid;
	return true;
}

stock FoxForeachRandomCharacter(){
	if(FoxCharacterUpp == -1) return 0;
	new playerid = FoxCharacter[random(FoxCharacterUpp+1)];
	if(IsCharacterConnected(playerid)) return playerid;
	return 0;
}

stock bool:FoxRemoveCharacter(playerid){
	if(!IsCharacterInFoxPool(playerid)) return false;
	for(new i = 0; i <= FoxCharacterUpp; i++){
		if(FoxCharacter[i] == playerid){
			if(FoxCharacterUpp == 0){
				FoxCharacter[i] = 0;
			} else if(i == FoxCharacterUpp){
				FoxCharacter[i] = 0;
			} else {
				FoxCharacter[i] = FoxCharacter[FoxCharacterUpp];
				FoxCharacter[FoxCharacterUpp] = 0;
			}
			FoxCharacterUpp--;
			break;
		}
	}
	return true;
}

stock FoxForeachInit(){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			if(IsPlayerNPC(i)){
				FoxAddBot(i);
			} else {
				FoxAddPlayer(i);
			}
			FoxAddCharacter(i);
		}
	}
	return 1;
}

new bool:CRC_FoxForeachInit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_FoxForeachInit){
		CRC_FoxForeachInit = false;
		FoxForeachInit();
	}
	#if defined FoX_OnFilterScriptInit
		FoX_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit FoX_OnFilterScriptInit
#if defined FoX_OnFilterScriptInit
	forward FoX_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_FoxForeachInit){
		CRC_FoxForeachInit = false;
		FoxForeachInit();
	}
	#if defined FoX_OnGameModeInit
		FoX_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FoX_OnGameModeInit
#if defined FoX_OnGameModeInit
	forward FoX_OnGameModeInit();
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	if(IsPlayerNPC(playerid)){
		FoxRemoveBot(playerid);
	} else {
		FoxRemovePlayer(playerid);
	}
	FoxRemoveCharacter(playerid);
	#if defined FoX_OnPlayerDisconnect
		FoX_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect FoX_OnPlayerDisconnect
#if defined FoX_OnPlayerDisconnect
	forward FoX_OnPlayerDisconnect(playerid,reason);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	if(IsPlayerNPC(playerid)){
		FoxAddBot(playerid);
	} else {
		FoxAddPlayer(playerid);
	}
	FoxAddCharacter(playerid);
	#if defined FoX_OnPlayerConnect
		FoX_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FoX_OnPlayerConnect
#if defined FoX_OnPlayerConnect
	forward FoX_OnPlayerConnect(playerid);
#endif

//EOF