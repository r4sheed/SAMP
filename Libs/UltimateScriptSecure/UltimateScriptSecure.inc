/************************************************************************************************************************************
 *                                                                                                                                  *
 *                                                      Ultimate Script Secure                                                      *
 *                                                                                                                                  *
 * Copyright © 2022 Abyss Morgan. All rights reserved.                                                                              *
 *                                                                                                                                  *
 * Website: https://adm.ct8.pl                                                                                                      *
 *                                                                                                                                  *
 * Plugins: None                                                                                                                    *
 * Modules: None                                                                                                                    *
 *                                                                                                                                  *
 * File Version: 5.0.0                                                                                                              *
 *                                                                                                                                  *
 * Functions:                                                                                                                       *
 * USS_Init(); //Return 1 if success, 0 if failure                                                                                  *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#if defined USS_SYSTEM
	#endinput
#endif
#define USS_SYSTEM

#define USS_ANONYMOUS		"$USS_ANYONE"

#define USS_RULE_IP_PORT	(0b00000001)	//Check Server IP and Port
#define USS_RULE_LID		(0b00000010)	//Check Server License Date
#define USS_RULE_PLAYERS	(0b00000100)	//Check Server Players
#define USS_RULE_RCON		(0b00001000)	//Check Server Rcon password
#define USS_RULE_LANG		(0b00010000)	//Check Server Language
#define USS_RULE_WEBACK		(0b00100000)	//Use Web Ack System

#define USS_RULE_SUCCESS	(0b00000000)
#define USS_RULE_ALL		(0b11111111)
#define USS_RULE_STANDARD	(USS_RULE_IP_PORT | USS_RULE_LID)

enum e_server_config {
	ADM_ADMserverIP[16],
	ADM_ServerPort,
	ADM_LicenseID,
	ADM_MaxPlayers,
	ADM_RconPassword[32],
	ADM_Language[32],
	ADM_RuleType	//default 
}

/************************************************************************************************************************************
 *                                                                                                                                  *
 * User Configuration                                                                                                               *
 *                                                                                                                                  *
 * IP - string                                                                                                                      *
 * PORT - integer value                                                                                                             *
 * LicenseID - integer value //YYYYMMDD                                                                                             *
 * MaxPlayers - integer value                                                                                                       *
 * RconPassword - string                                                                                                            *
 * Language - string                                                                                                                *
 * RuleType - integer value //e.g. USS_RULE_IP_PORT | USS_RULE_PLAYERS                                                              *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
//#define ENABLE_WEB_ACK		//additional option (definitions below apply to this option)
//#define SCRIPT_ACK_KEY		"{BOBO_HAHA,ACCESSCONTROL,TRUE}"
//#define SCRIPT_ACK_URL		"example.com/secure_adm/index.php"
//#define SCRIPT_ANTI_FLOOD		(123) //change this number
//#define SCRIPT_ACK_TIME		(10000) //10 second

//IP Port LicenseID MaxPlayers RconPassword Language RuleType
new ADMServerList[][e_server_config] = {
	{ "127.0.0.1", 7777, 20210501, 500, "123", "Polish", USS_RULE_STANDARD},
	{ "127.0.0.1", 7778, 20210501, 500, "123", "English", USS_RULE_STANDARD},
	{ USS_ANONYMOUS, 0, 20210501, 150, "123", "English", USS_RULE_LID} //USS_ANONYMOUS - special option for any ip/port
};

forward USS_OnScriptError(errorid);
public USS_OnScriptError(errorid){
	switch(errorid){
		case USS_RULE_SUCCESS: {
			//script init succesfuly :)
		}
		case USS_RULE_IP_PORT: {
			print("[ADM] Error: This script is stolen.");
			SendRconCommand("exit");
		}
		case USS_RULE_LID: {
			print("[ADM] Error: Script license has expired.");
			SendRconCommand("exit");
		}
		case USS_RULE_PLAYERS: {
			print("[ADM] Error: Invalid server config, check your max players.");
			SendRconCommand("exit");
		}
		case USS_RULE_RCON: {
			print("[ADM] Error: Invalid server config, check your rcon password.");
			SendRconCommand("exit");
		}
		case USS_RULE_LANG: {
			print("[ADM] Error: Invalid server config, check your language.");
			SendRconCommand("exit");
		}
		case USS_RULE_WEBACK: {
			print("[ADM] Error: The script did not get permission to activation.");
			SendRconCommand("exit");
		}
	}
	return 1;
}

/************************************************************************************************************************************
 *                                                                                                                                  *
 * Script Secure                                                                                                                    *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define INVALID_SERVERID		(-1)

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

//Web ACK System
#if defined ENABLE_WEB_ACK
	#if !defined SCRIPT_ACK_KEY
		#error [ADM] Please #define SCRIPT_ACK_KEY "key"
	#endif
	
	#if !defined SCRIPT_ACK_URL
		#error [ADM] Please #define SCRIPT_ACK_URL "ack_url"
	#endif
	
	#if !defined SCRIPT_ANTI_FLOOD
		#error [ADM] Please #define SCRIPT_ANTI_FLOOD <random number>
	#endif
#else
	#if !defined SCRIPT_ACK_KEY
		#define SCRIPT_ACK_KEY		"none"
	#endif
	
	#if !defined SCRIPT_ACK_URL
		#define SCRIPT_ACK_URL		"none"
	#endif
	
	#if !defined SCRIPT_ANTI_FLOOD
		#define SCRIPT_ANTI_FLOOD	(0)
	#endif
#endif

new bool:ADMWebCheck = false;

forward ScriptSecureADMWeb(index,response_code,data[]);
forward ADMWebACKCheck(important);

public ScriptSecureADMWeb(index,response_code,data[]){
	if(strfind(data,SCRIPT_ACK_KEY,false) != -1){
		ADMWebCheck = true;
	} else {
		CallLocalFunction("USS_OnScriptError","d",USS_RULE_WEBACK);
		return 0;
	}
	return 1;
}

public ADMWebACKCheck(important){
	if(!ADMWebCheck){
		CallLocalFunction("USS_OnScriptError","d",USS_RULE_WEBACK);
		return 0;
	}
	return 1;
}

stock USS_FindServerID(){
	new ADMserverIP[16], serverPort = GetServerVarAsInt("port");
	GetServerVarAsString("bind",ADMserverIP,sizeof(ADMserverIP));
	for(new i = 0, j = sizeof(ADMServerList); i < j; i++){
		if(!strcmp(ADMserverIP,ADMServerList[i][ADM_ADMserverIP],true) && !isnull(ADMserverIP)){
			if(serverPort == ADMServerList[i][ADM_ServerPort]){
				return i;
			}
		} else if(!strcmp(USS_ANONYMOUS,ADMServerList[i][ADM_ADMserverIP],true)){
			return i;
		}
	}
	return INVALID_SERVERID;
}

USS_Init(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
	
	//IP and PORT check
	new sid = USS_FindServerID();
	if(sid == INVALID_SERVERID){
		CallLocalFunction("USS_OnScriptError","d",USS_RULE_IP_PORT);
		return 0;
	}
	
	//Date Check
	if(ADMServerList[sid][ADM_RuleType] & USS_RULE_LID){
		new tmpdate, tmpyear, tmpmonth, tmpday;
		getdate(tmpyear,tmpmonth,tmpday);
		tmpdate = (10000*tmpyear)+(100*tmpmonth)+tmpday;
		if(tmpdate > ADMServerList[sid][ADM_LicenseID]){
			CallLocalFunction("USS_OnScriptError","d",USS_RULE_LID);
			return 0;
		}
	}
	
	//Check server.cfg
	if(ADMServerList[sid][ADM_RuleType] & USS_RULE_PLAYERS){
		if(GetMaxPlayers() != ADMServerList[sid][ADM_MaxPlayers]){
			CallLocalFunction("USS_OnScriptError","d",USS_RULE_PLAYERS);
			return 0;
		}
	}
	
	new rtemp[32];
	
	if(ADMServerList[sid][ADM_RuleType] & USS_RULE_RCON){
		GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,ADMServerList[sid][ADM_RconPassword],false) != 0){
			CallLocalFunction("USS_OnScriptError","d",USS_RULE_RCON);
			return 0;
		}
		rtemp = "";
	}
	
	if(ADMServerList[sid][ADM_RuleType] & USS_RULE_LANG){
		GetServerVarAsString("language",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,ADMServerList[sid][ADM_Language],false) != 0 || isnull(rtemp)){
			CallLocalFunction("USS_OnScriptError","d",USS_RULE_LANG);
			return 0;
		}
		rtemp = "";
	}
	
	#pragma unused rtemp
	
	//Web ACK System
	#if defined ENABLE_WEB_ACK
		if(ADMServerList[sid][ADM_RuleType] & USS_RULE_WEBACK){
			new buffer[256];
			format(buffer,sizeof(buffer),"%s?code=%d&bind=%s&port=%d",SCRIPT_ACK_URL,SCRIPT_ANTI_FLOOD,ADMServerList[sid][ADM_ADMserverIP],ADMServerList[sid][ADM_ServerPort]);
			HTTP(SCRIPT_ANTI_FLOOD,HTTP_POST,buffer," ","ScriptSecureADMWeb");
			SetTimerEx("ADMWebACKCheck",SCRIPT_ACK_TIME, false, "d", 1);
		}
	#endif
	
	return 1;
}

//EOF