/****************************************************************************************************
 *                                                                                                  *
 *                                          Rcon Fireworks                                          *
 *                                                                                                  *
 * Copyright © 2019 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Website:  adm.ct8.pl                                                                             *
 * Download: adm.ct8.pl/r/download                                                                  *
 *                                                                                                  *
 * Plugins: Streamer                                                                                *
 * Modules: 3DTryg                                                                                  *
 *                                                                                                  *
 * File Version: 2.1.0                                                                              *
 * Streamer Version: 2.9.4                                                                          *
 * 3DTryg Version: 4.8.5                                                                            *
 *                                                                                                  *
 ****************************************************************************************************/

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.4 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v4.8.5 (adm.ct8.pl/d/3DTryg.inc)
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v4.8.5 (adm.ct8.pl/d/3DTryg.inc)
#elseif (TRYG3D_VERSION < 40805)
	#error [ADM] Update you 3DTryg.inc to v4.8.5 (adm.ct8.pl/d/3DTryg.inc)
#endif

#define FIREWORK_ELEMENT			(256)
#define FIREWORKS_SPEED				(5.0)
#define FIREWORKS_RADIUS			(300.0)

new FireworkObj[FIREWORK_ELEMENT], bool:FireworkActive = false;

forward CreateFireworks(Float:x,Float:y,Float:z);
forward DestroyFireworks(tec);

public CreateFireworks(Float:x,Float:y,Float:z){
	FireworkActive = true;
	z+=25.0;
	for(new i = 0; i < FIREWORK_ELEMENT; i++){
		FireworkObj[i] = CreateDynamicObject(354,x,y,z,0.0,0.0,0.0,0,0,-1,200.0);
	}
	new F4[Float3D], tit;
	for(new i = 0; i < 64; i++){
		GetPointInFront3D(x,y,z,0.0,(i*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	for(new i = 64; i < 128; i++){
		GetPointInFront3D(x,y,z,5.0,((i-64)*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	for(new i = 128; i < 192; i++){
		GetPointInFront3D(x,y,z,10.0,((i-128)*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	for(new i = 192; i < 256; i++){
		GetPointInFront3D(x,y,z,15.0,((i-128)*5.625),FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
		MoveDynamicObject(FireworkObj[i],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED);
	}
	GetPointInFront3D(x,y,z,0.0,0.0,FIREWORKS_RADIUS,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
	GetMoveTime(x,y,z,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],FIREWORKS_SPEED,tit);
	SetTimerEx("DestroyFireworks",tit,0,"d",1);
	return 1;
}


public DestroyFireworks(tec){
	for(new i = 0; i < FIREWORK_ELEMENT; i++){
		if(IsValidDynamicObject(FireworkObj[i])) DestroyDynamicObject(FireworkObj[i]);
	}
	FireworkActive = false;
	return 1;
}

CMD:xbumm(playerid){
	if(!IsPlayerAdmin(playerid)) return 0;
	if(FireworkActive) return SendClientMessage(playerid,0xFFFFFFFF,"››› Function active");
	new F4[Float3D];
	GetPlayerPos(playerid,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
	CreateFireworks(F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
	SendClientMessageToAll(0xFFFFFFFF,"{9E3DFF}››› Fired fireworks");
	return 1;
}

//EOF