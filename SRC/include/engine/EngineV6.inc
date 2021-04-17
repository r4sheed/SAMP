/***********************************************************************************************************************************
 *                                                                                                                                 *
 *                                            NGCM Mob Move Engine System 6.0 Epsilon X                                            *
 *                                                                                                                                 *
 * Copyright © 2019 Abyss Morgan. All rights reserved.                                                                             *
 *                                                                                                                                 *
 * Website:  adm.ct8.pl                                                                                                            *
 * Download: adm.ct8.pl/r/download                                                                                                 *
 *                                                                                                                                 *
 * Plugins: Streamer, ColAndreas                                                                                                   *
 * Modules: 3DTryg                                                                                                                 *
 *                                                                                                                                 *
 * File Version: 6.0.24                                                                                                            *
 * Streamer Version: 2.9.4                                                                                                         *
 * ColAndreas Version: 1.4.0                                                                                                       *
 * 3DTryg Version: 4.8.5                                                                                                           *
 *                                                                                                                                 *
 * Functions:                                                                                                                      *
 * GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0);                  *
 *                                                                                                                                 *
 * Gamma Engine X Functions:                                                                                                       *
 * EngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed);                                           *
 * EngineExcavatorUpdate(objectid,areaid,EngineX:engineid,Float:speed);                                                            *
 *                                                                                                                                 *
 * Delta Engine X Functions:                                                                                                       *
 * DeltaEngineRotation(objectid,EngineX:engineid,Float:speed = 0.05);                                                              *
 * DeltaEngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed);                                      *
 *                                                                                                                                 *
 * Epsilon Engine X Functions:                                                                                                     *
 * EpsilonEngineRotation(objectid,EngineX:engineid,Float:speed = 0.05); //the same as DeltaEngineRotation                          *
 * EpsilonEngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed,Float:cut_size=5.0);                 *
 * EngineXCA(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed,Float:cut_size=5.0);                      *
 *                                                                                                                                 *
 ***********************************************************************************************************************************
 *                                                                                                                                 *
 * Why epsilon since the sixth version ?                                                                                           *
 *                                                                                                                                 *
 * 1.0 - Do whatever you want. (Sphere)                                                                                            *
 * 2.0 Alpha - Turn, look straight ahead, fly. (Sphere)                                                                            *
 * 3.0 Beta - Turn, look straight ahead, fly. (Area Cube)                                                                          *
 * 4.0 Gamma X - Choose a direction, look straight ahead, fly. (Any Area)                                                          *
 * 5.0 Delta X - Choose a direction, slowly turn, look straight ahead, fly. (Any Area)                                             *
 * 6.0 Epsilon X - Choose a direction, slowly turn, look straight ahead, find collision point, fly. (Any Area)                     *
 *                                                                                                                                 *
 * Why X ?                                                                                                                         *
 * Do not ask XD                                                                                                                   *
 *                                                                                                                                 *
 ***********************************************************************************************************************************/

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.4 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS
	#error [ADM] You need ColAndreas v1.4.0 (github.com/Pottus/ColAndreas/releases)
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v4.8.5 (adm.ct8.pl/d/3DTryg.inc)
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v4.8.5 (adm.ct8.pl/d/3DTryg.inc)
#elseif (TRYG3D_VERSION < 40805)
	#error [ADM] Update you 3DTryg.inc to v4.8.5 (adm.ct8.pl/d/3DTryg.inc)
#endif

#if defined _NOX_ENGINE_X
	#endinput
#endif
#define _NOX_ENGINE_X
#define DYNAMIC_FILTERSCRIPT		"ALS:HOOK:METHOD"

#define NOX_ENGINE_X_Version			(60024)
#define NOX_VERSION						"6.0 Epsilon X"
#define NT_VERSION						"1.0"

//Engine ID
#define ENGINE_NORMAL 					(EngineX:0)		//[Object: 1681, 18846 OR ANY] 	|| 6.0 X
#define ENGINE_FIGHTER					(EngineX:1)		//[Object: 10757]				|| 6.0 X
#define ENGINE_SUPPLY					(EngineX:2)		//[Object: 1683, 3528]			|| 6.0 X
#if defined NGCM_KERNEL
	#define ENGINE_NGCMS				(EngineX:3)		//[NGCMotherShip.ngcm]			|| 4.0 X
	#define ENGINE_ARCMS				(EngineX:4)		//[ArcusMS.ngcm]				|| 4.0 X
	#define ENGINE_COMMANDER			(EngineX:5)		//[Commander.ngcm]				|| 4.0 X
#endif
#define ENGINE_ELITE					(EngineX:6)		//[Object: 14553] 				|| 6.0 X
#define ENGINE_UBOOT					(EngineX:7)		//[Object: 9958]				|| 6.0 X
#define ENGINE_SHIP						(EngineX:8)		//[Object: 8493]				|| 6.0 CA (not recommended to use version 6.0 X)
#define ENGINE_MINI						(EngineX:9)		//[Object: 2510, 2512]			|| 6.0 X
#define ENGINE_EXCAVATOR 				(EngineX:10)	//[Object: 18248]				|| 4.1 G (Ground)
#define ENGINE_UNDERDUDE				(EngineX:11)	//[Object: 1379]				|| 6.0 U (Underwater)

//DeltaEngineRotation Speed
#define DELTA_ENGINE_SPEED_NORMAL 		(0.050)
#define DELTA_ENGINE_SPEED_FIGHTER		(0.050)
#define DELTA_ENGINE_SPEED_SUPPLY		(0.020)
#define DELTA_ENGINE_SPEED_NGCMS		(0.050)
#define DELTA_ENGINE_SPEED_ARCMS		(0.050)
#define DELTA_ENGINE_SPEED_COMMANDER	(0.050)
#define DELTA_ENGINE_SPEED_ELITE		(0.010)
#define DELTA_ENGINE_SPEED_UBOOT		(0.005)
#define DELTA_ENGINE_SPEED_SHIP			(0.050)
#define DELTA_ENGINE_SPEED_MINI			(0.050)
//#define DELTA_ENGINE_SPEED_EXCAVATOR	(0.001)
#define DELTA_ENGINE_SPEED_UNDERDUDE	(0.050)

new bool:EngineXLoaded = false;

forward OnEngineXInit();
forward OnEngineXExit();

public OnEngineXInit(){
	Tryg3D::SafeColAndreasInit();
	if(!Tryg3D::IsColAndreasInit()){
		printf("[ADM] Error: Invalid ColAndreas Memory.");
		printf("[ADM] Error: NGCM Mob Move Engine System %s not loaded.",NOX_VERSION);
		return 0;
	}
	printf("[ADM] Info: NGCM Mob Move Engine System %s loaded.",NOX_VERSION);
	EngineXLoaded = true;
	return 1;
}

public OnEngineXExit(){

	if(!EngineXLoaded) return 0;
	printf("[ADM] Info: NGCM Mob Move Engine System %s unloaded.",NOX_VERSION);
	EngineXLoaded = false;
	return 1;
}

new bool:CRC_EngineXInit = true,
	bool:CRC_EngineXExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_EngineXInit){
		CRC_EngineXInit = false; 
		OnEngineXInit();
	}
	#if defined NOX_OnFilterScriptInit
		NOX_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit NOX_OnFilterScriptInit
#if defined NOX_OnFilterScriptInit
	forward NOX_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_EngineXInit){
		CRC_EngineXInit = false; 
		OnEngineXInit();
	}
	#if defined NOX_OnGameModeInit
		NOX_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit NOX_OnGameModeInit
#if defined NOX_OnGameModeInit
	forward NOX_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_EngineXExit){
		CRC_EngineXExit = false; 
		OnEngineXExit();
	}
	#if defined NOX_OnFilterScriptExit
		NOX_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit NOX_OnFilterScriptExit
#if defined NOX_OnFilterScriptExit
	forward NOX_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_EngineXExit){
		CRC_EngineXExit = false; 
		OnEngineXExit();
	}
	#if defined NOX_OnGameModeExit
		NOX_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit NOX_OnGameModeExit
#if defined NOX_OnGameModeExit
	forward NOX_OnGameModeExit();
#endif

stock GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0){
	if(!EngineXLoaded) return 0;
	GetRandomClockPos(x,y,z,radius,tx,ty,tz,trz,rz);
	new Float:tmpz;
	ColAndreas::FindZ_For2DCoord(tx,ty,tmpz);
	if(tz < tmpz+50.0){
		tz += 50.0;
	}
	return 1;
}

stock EngineX(STREAMER_TAG_OBJECT:objectid,STREAMER_TAG_AREA:areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed){
	if(!EngineXLoaded) return 0;
	new rad = maxradius-minradius, F5[Float3D];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
	
		case ENGINE_NORMAL: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_FIGHTER: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX+8.0)),Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX+8.0,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX)),Tryg3D::CompressRotation(randRZ-90.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,randRX,randRZ);
					}
				}
			}
		}
		
		#if defined NGCM_KERNEL
			case ENGINE_NGCMS: {
				#if (YSF_PLUGIN == 1)
					if(!IsDynamicObjectMoving(objectid)){
						new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
						GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
						GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX)),Tryg3D::CompressRotation(randRZ-90.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
						if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
							new Float:tmpz;
							ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
							if(tmpz+minz < F5[T3D:tZ]){
								MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,randRX,randRZ);
							}
						}
					}
				#else
					if(!IsObjectMoving(objectid)){
						new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
						GetObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
						GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX)),Tryg3D::CompressRotation(randRZ-90.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
						if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidObject(objectid))){
							new Float:tmpz;
							ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
							if(tmpz+minz < F5[T3D:tZ]){
								MoveObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,randRX,randRZ);
							}
						}
					}
				#endif
			}
			
			case ENGINE_ARCMS: {
				/*
				#if (YSF_PLUGIN == 1)
					if(!IsDynamicObjectMoving(objectid)){
						new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
						GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
						GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
						if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
							new Float:tmpz;
							ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
							if(tmpz+minz < F5[T3D:tZ]){
								MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
							}
						}
					}
				#else
				*/
				if(!IsObjectMoving(objectid)){
					new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
					GetObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
					GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
					if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidObject(objectid))){
						new Float:tmpz;
						ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
						if(tmpz+minz < F5[T3D:tZ]){
							MoveObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
						}
					}
				}
				//#endif
			}
			
			case ENGINE_COMMANDER: {
				if(!IsDynamicObjectMoving(objectid)){
					new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
					GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
					GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
					if((IsPointInDynamicArea(SpecialPolygon[areaid],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
						new Float:tmpz;
						ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
						if(tmpz+minz < F5[T3D:tZ]){
							MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
						}
					}
				}
			}
		#endif
		
		case ENGINE_ELITE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX+14.0)),Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX+14.0,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_UBOOT: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SHIP: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
	
		case ENGINE_MINI: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX)),Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_EXCAVATOR: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);				
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz > 0.0){
						Streamer::SetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID,randRZ);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_UNDERDUDE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(51)-25, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					if(IsPointInUnderwater(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])){
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
	}
	return 1;
}

stock EngineExcavatorUpdate(STREAMER_TAG_OBJECT:objectid,STREAMER_TAG_AREA:areaid,EngineX:engineid,Float:speed){
	if(!EngineXLoaded) return 0;
	new F5[Float3D];
	switch(engineid){
		case ENGINE_EXCAVATOR: {
			if(IsDynamicObjectMoving(objectid)){
				new randRZ;
				Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,F5[T3D:tX]);
				Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,F5[T3D:tY]);
				Streamer::GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,F5[T3D:tZ]);
				randRZ = Streamer::GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
					ColAndreas::FindZ_For2DCoord(F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
					F5[T3D:Z] += 7.0;
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:Z],speed,0.0,0.0,randRZ);
				}
			}
		}
	}
	return 1;
}

stock DeltaEngineRotation(STREAMER_TAG_OBJECT:objectid,EngineX:engineid,Float:speed = 0.050){
	if(!EngineXLoaded) return 0;
	new F5[Float3D];
	
	GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
	if(engineid == ENGINE_UNDERDUDE){
		F5[T3D:rX] = random(51)-25;
		F5[T3D:rY] = 0.0;
	} else {
		F5[T3D:rX] = random(91)-45;
		F5[T3D:rY] = random(20)-10;
	}
	F5[T3D:rZ] = random(360);
	
	if(engineid == ENGINE_SHIP || engineid == ENGINE_UBOOT){
		if(F5[T3D:Z] > 0.0){
			F5[T3D:Z]-=0.05;
		} else {
			F5[T3D:Z]+=0.05;
		}
	} else {
		F5[T3D:Z]+=0.05;
	}
	
	switch(engineid){
		case ENGINE_NORMAL: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
		}
		case ENGINE_FIGHTER: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,F5[T3D:rX]+8.0,F5[T3D:rY]+12.0,F5[T3D:rZ]);
		}
		case ENGINE_SUPPLY: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,F5[T3D:rY],F5[T3D:rX],F5[T3D:rZ]);
		}
		case ENGINE_ELITE: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,F5[T3D:rX]+14.0,F5[T3D:rY]+12.0,F5[T3D:rZ]);
		}
		case ENGINE_UBOOT: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,0.0,0.0,F5[T3D:rZ]);
		}
		case ENGINE_SHIP: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,0.0,0.0,F5[T3D:rZ]);
		}
		case ENGINE_MINI: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
		}
		/*
		//Invalid
		case ENGINE_EXCAVATOR: {
			Streamer::SetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID,floatround(F5[T3D:rZ]));
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,0.0,0.0,F5[T3D:rZ]-180.0);
		}
		*/
		case ENGINE_UNDERDUDE: {
			MoveDynamicObject(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
		}
	}
	return 1;
}

stock DeltaEngineX(STREAMER_TAG_OBJECT:objectid,STREAMER_TAG_AREA:areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed){
	if(!EngineXLoaded) return 0;
	new rad = maxradius-minradius, F5[Float3D];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
	
		case ENGINE_NORMAL: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_FIGHTER: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rX]+8.0)),Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rY])),Tryg3D::CompressRotation(F5[T3D:rZ]-90.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_ELITE: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rX]+14.0)),Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_UBOOT: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront2D(F5[T3D:X],F5[T3D:Y],Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_SHIP: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F5[T3D:rZ],randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,F5[T3D:rZ]);
				}
			}
		}
	
		case ENGINE_MINI: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rX])),Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_EXCAVATOR: return 0;
		
		case ENGINE_UNDERDUDE: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				if(IsPointInUnderwater(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])){
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
	}
	return 1;
}

stock EpsilonEngineX(STREAMER_TAG_OBJECT:objectid,STREAMER_TAG_AREA:areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed,Float:cut_size=5.0){
	if(!EngineXLoaded) return 0;
	new rad = maxradius-minradius, F5[Float3D];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
	
		case ENGINE_NORMAL: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_FIGHTER: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rX]+8.0)),Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rY])),Tryg3D::CompressRotation(F5[T3D:rZ]-90.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_ELITE: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rX]+14.0)),Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_UBOOT: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront2D(F5[T3D:X],F5[T3D:Y],Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_SHIP: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F5[T3D:rZ],randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,F5[T3D:rZ]);
				}
			}
		}
	
		case ENGINE_MINI: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(F5[T3D:rX])),Tryg3D::CompressRotation(F5[T3D:rZ]-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
				if(tmpz+minz < F5[T3D:tZ]){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
		case ENGINE_EXCAVATOR: return 0;
		
		case ENGINE_UNDERDUDE: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
			GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:rX],F5[T3D:rZ],randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
			if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
				if(IsPointInUnderwater(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])){
					MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
					MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,F5[T3D:rX],F5[T3D:rY],F5[T3D:rZ]);
				}
			}
		}
		
	}
	return 1;
}

#define EpsilonEngineRotation		DeltaEngineRotation

stock EngineXCA(STREAMER_TAG_OBJECT:objectid,STREAMER_TAG_AREA:areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed,Float:cut_size=5.0){
	if(!EngineXLoaded) return 0;
	new rad = maxradius-minradius, F5[Float3D];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
	
		case ENGINE_NORMAL: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_FIGHTER: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX+8.0)),Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX+8.0,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX)),Tryg3D::CompressRotation(randRZ-90.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,randRX,randRZ);
					}
				}
			}
		}
		
		case ENGINE_ELITE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX+14.0)),Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX+14.0,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_UBOOT: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SHIP: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					if(IsPointInWater(F5[T3D:tX],F5[T3D:tY],0.0)){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
	
		case ENGINE_MINI: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],Tryg3D::CompressRotation((-1.0)*(randRX)),Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz+minz < F5[T3D:tZ]){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_EXCAVATOR: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(randRZ-180.0),randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);				
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					ColAndreas::FindZ_For2DCoord(F5[T3D:tX],F5[T3D:tY],tmpz);
					if(tmpz > 0.0){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						Streamer::SetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID,randRZ);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_UNDERDUDE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(51)-25, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[T3D:X],F5[T3D:Y],F5[T3D:Z]);
				GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],randRX,randRZ,randR,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ]);
				if((IsPointInDynamicArea(areaid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])) && (IsValidDynamicObject(objectid))){
					if(IsPointInUnderwater(F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ])){
						MovePointColCutLineEx(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],cut_size);
						MoveDynamicObject(objectid,F5[T3D:tX],F5[T3D:tY],F5[T3D:tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
	}
	return 1;
}

//EOF