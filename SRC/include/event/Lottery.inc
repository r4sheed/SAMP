/****************************************************************************************************
 *                                                                                                  *
 *                                             Lottery                                              *
 *                                                                                                  *
 * Copyright © 2019 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Website:  adm.ct8.pl                                                                             *
 * Download: adm.ct8.pl/r/download                                                                  *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.0.0                                                                              *
 *                                                                                                  *
 ****************************************************************************************************/

#define LOTTERY_MIN_PLAYERS		(3)
#define LOTTERY_START_TIME		(5*60*1000) 	//5 minutes
#define LOTTERY_TRY_START_TIME	(3*60*1000)		//3 minutes (hmm, never used ?)
#define LOTTERY_PRICE			(3000)			//join price 3000 $

new Lottery_Players[MAX_PLAYERS],
	Lottery_Upperbound = -1,
	bool:Lottery_Status = false,
	Lottery_Timer = -1;

forward LotteryInit(); 		//auto hook
forward LotteryExit(); 		//auto hook
forward Lottery_LosRandom(important);	//auto hook

stock LOT_GetPlayerNick(playerid){
	new pnick[24];
	GetPlayerName(playerid,pnick,sizeof (pnick));
	return pnick;
}


stock bool:IsPlayerInLottery(playerid){
	for(new i = 0; i <= Lottery_Upperbound; i++){
		if(Lottery_Players[i] == playerid){
			return true;
		}
	}
	return false;
}

stock bool:Lottery_AddPlayer(playerid){
	if(IsPlayerInLottery(playerid)) return false;
	Lottery_Upperbound++;
	Lottery_Players[Lottery_Upperbound] = playerid;
	if(Lottery_Upperbound == (LOTTERY_MIN_PLAYERS-1) && Lottery_Status == false){
		//start
		Lottery_Status = true;
		new buffer[256];
		format(buffer,sizeof buffer,"[LOTTERY] I will start %d minutes, join now /lottery, Price %d $",LOTTERY_START_TIME/60000,LOTTERY_PRICE);
		SendClientMessageToAll(0x00FF00FF,buffer);
		Lottery_Timer = SetTimerEx("Lottery_LosRandom", LOTTERY_START_TIME, false, "d", 1);
	}
	return true;
}

stock bool:Lottery_RemovePlayer(playerid){
	if(!IsPlayerInLottery(playerid)) return false;
	for(new i = 0; i <= Lottery_Upperbound; i++){
		if(Lottery_Players[i] == playerid){
			if(i == Lottery_Upperbound || i == 0){
				Lottery_Players[i] = INVALID_PLAYER_ID;
			} else {
				Lottery_Players[i] = Lottery_Players[Lottery_Upperbound];
				Lottery_Players[Lottery_Upperbound] = INVALID_PLAYER_ID;
			}
			Lottery_Upperbound--;
			break;
		}
	}
	if(Lottery_Upperbound == 1 && Lottery_Status == true){
		KillTimer(Lottery_Timer);
		Lottery_Timer = -1;
		Lottery_Status = false;
		new buffer[256];
		format(buffer,sizeof buffer,"[LOTTERY] Was interrupted due to lack of players, join now /lottery, Price %d $",LOTTERY_PRICE);
		SendClientMessageToAll(0x00FF00FF,buffer);
	}
	return true;
}

new bool:CRC_LotteryInit = true,
	bool:CRC_LotteryExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_LotteryInit){
		CRC_LotteryInit = false;
		LotteryInit();
	}
	#if defined LOT_OnFilterScriptInit
		LOT_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit LOT_OnFilterScriptInit
#if defined LOT_OnFilterScriptInit
	forward LOT_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_LotteryInit){
		CRC_LotteryInit = false;
		LotteryInit();
	}
	#if defined LOT_OnGameModeInit
		LOT_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit LOT_OnGameModeInit
#if defined LOT_OnGameModeInit
	forward LOT_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_LotteryExit){
		CRC_LotteryExit = false;
		LotteryExit();
	}
	#if defined LOT_OnFilterScriptExit
		LOT_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit LOT_OnFilterScriptExit
#if defined LOT_OnFilterScriptExit
	forward LOT_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_LotteryExit){
		CRC_LotteryExit = false;
		LotteryExit();
	}
	#if defined LOT_OnGameModeExit
		LOT_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit LOT_OnGameModeExit
#if defined LOT_OnGameModeExit
	forward LOT_OnGameModeExit();
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	Lottery_RemovePlayer(playerid);
	#if defined LOT_OnPlayerDisconnect
		LOT_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect LOT_OnPlayerDisconnect
#if defined LOT_OnPlayerDisconnect
	forward LOT_OnPlayerDisconnect(playerid,reason);
#endif

public LotteryInit(){
	for(new i = 0, j = sizeof(Lottery_Players); i < j; i++){
		Lottery_Players[i] = INVALID_PLAYER_ID;
	}
	return 1;
}

public LotteryExit(){
	KillTimer(Lottery_Timer);
	Lottery_Timer = -1;
	return 1;
}

public Lottery_LosRandom(important){
	new rand = random(Lottery_Upperbound+1);
	new playerid = Lottery_Players[rand];
	if(IsPlayerConnected(playerid)){
		//winner
		new LotteryCash = (Lottery_Upperbound+1)*2000, buffer[256];

		format(buffer,sizeof buffer,"[LOTTERY] Player %s wins and keeps %d $",LOT_GetPlayerNick(playerid),LotteryCash);
		SendClientMessageToAll(0x00FF00FF,buffer);
		
		GivePlayerMoney(playerid,LotteryCash);

		//reset
		Lottery_Status = false;
		for(new i = 0; i <= Lottery_Upperbound; i++){
			Lottery_Players[i] = INVALID_PLAYER_ID;
		}
		Lottery_Upperbound = -1;
	} else {
		//Ups, coœ siê popsu³o i nie by³o mnie s³ychaæ
		Lottery_RemovePlayer(playerid);
		new buffer[256];
		format(buffer,sizeof buffer,"[LOTTERY] Failed to draw the player, join now /lottery, Price %d $",LOTTERY_PRICE);
		SendClientMessageToAll(0x00FF00FF,buffer);
		Lottery_Timer = SetTimerEx("Lottery_LosRandom", LOTTERY_TRY_START_TIME, false, "d", 1);
	}
	return 1;
}

CMD:lottery(playerid){
	if(IsPlayerInLottery(playerid)) return SendClientMessage(playerid,0xFFFFFFFF,"You are already joined to the lottery");
	if(GetPlayerMoney(playerid) < LOTTERY_PRICE){
		new buffer[256];
		format(buffer,sizeof buffer,"You need %d $",LOTTERY_PRICE);
		return SendClientMessage(playerid,0xFFFFFFFF,buffer);
	}
	GivePlayerMoney(playerid,-LOTTERY_PRICE);
	new buffer[256], cid;
	cid = LOTTERY_MIN_PLAYERS-(Lottery_Upperbound+2);
	if(cid < 0){
		format(buffer,sizeof buffer,"[LOTTERY] You have joined, for %d minutes start lottery",LOTTERY_START_TIME/60000);
	} else {
		format(buffer,sizeof buffer,"[LOTTERY] You have joined, need %d players to start lottery",cid);
	}
	SendClientMessage(playerid,0x00FF00FF,buffer);
	Lottery_AddPlayer(playerid);
	return 1;
}

//EOF