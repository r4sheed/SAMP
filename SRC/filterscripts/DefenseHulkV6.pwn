/****************************************************************************************************
 *                                                                                                  *
 * Reaver Defense Hulk Prototype v1.4 made by Abyss Morgan                                          *
 *                                                                                                  *
 * Website:  adm.ct8.pl                                                                             *
 * Download: adm.ct8.pl/r/download                                                                  *
 *                                                                                                  *
 ****************************************************************************************************/
 
#include <a_samp>
#include <streamer>
#include <mapandreas>
#include <YSF>
#include <ColAndreas>

#include <3DTryg>
#include <EngineV6>

#define SD_VERYHIGH					(999.0)

#define MAX_DEFENSE_HULK			(3)
#define MAX_NGC_NPC					(300)

#define MOB_SPEED_SLOW				(5.0)
#define MOB_SPEED_NORMAL			(10.0)
#define MOB_SPEED_FAST				(25.0)

new DefenseHulkTimer,
	STREAMER_TAG_OBJECT:DefenseHulk[MAX_DEFENSE_HULK][23],
	DefenseHulkStatus[MAX_DEFENSE_HULK],
	STREAMER_TAG_OBJECT:NGCFighter[MAX_NGC_NPC][4],
	NGCFighterPool,
	STREAMER_TAG_OBJECT:DragonHead[MAX_NGC_NPC][4],
	DragonHeadPool,
	STREAMER_TAG_OBJECT:UnderDudeHead[MAX_NGC_NPC][4],
	UnderDudeHeadPool,
	STREAMER_TAG_OBJECT:NGCCommander[MAX_NGC_NPC][4],
	NGCCommanderPool,
	STREAMER_TAG_OBJECT:NGCExcavator[MAX_NGC_NPC][4],
	NGCExcavatorPool;
	
forward OnMobUpdate(tec);

forward DefenseHulkUpdate(mobid);
forward CreateDefenseHulk(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyDefenseHulk(mobid);

forward FighterUpdate(mobid);
forward CreateFighter(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyFighter(mobid);

forward CommanderUpdate(mobid);
forward CreateCommander(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyCommander(mobid);

forward ExcavatorUpdate(mobid);
forward CreateExcavator(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyExcavator(mobid);

forward DragonUpdate(mobid);
forward CreateDragon(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyDragon(mobid);

forward UnderDudeUpdate(mobid);
forward CreateUnderDude(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid);
forward DestroyUnderDude(mobid);

public OnFilterScriptInit(){

    // Load the SA map

	
	DefenseHulkTimer = SetTimerEx("OnMobUpdate", 500, true, "d", 1);
	
	new STREAMER_TAG_AREA:myarea = CreateDynamicCube(-3000.0,-3000.0,-100.0,3000.0,3000.0,300.0);
	
	CreateDefenseHulk(0, 0.0,0.0,50.0, 0,0, myarea);
	
	
	CreateFighter(11, -2119.5449,496.9574,35.1719, 0,0, myarea);
	
	//CreateDefenseHulk(1, 500.0,0.0,50.0, 0,0, myarea);
	
	for(new i = 0; i < 10; i++){
		CreateFighter(i, -2119.5449,496.9574,35.1719, 0,0, myarea);
		CreateCommander(i, -2119.5449,496.9574,35.1719, 0,0, myarea);
		CreateDragon(i, -2119.5449,496.9574,35.1719, 0,0, myarea);
		CreateExcavator(i, 0.0,0.0,3.0, 0,0, myarea);
		CreateUnderDude(i, -2170.0430,1623.7864,-6.0942, 0,0, myarea);
	}
	
	return 1;
}

public OnFilterScriptExit(){
	KillTimer(DefenseHulkTimer);
	return 1;
}

public OnMobUpdate(tec){
	#pragma unused tec
	for(new i = 0; i < MAX_DEFENSE_HULK; i++){
		if(DefenseHulkStatus[i] == (1)){
			DefenseHulkUpdate(i);
		}
	}
	
	for(new i = 0; i <= NGCFighterPool; i++){
		if(NGCFighter[i][2] == 1){
			FighterUpdate(i);
		}
	}
	
	for(new i = 0; i <= DragonHeadPool; i++){
		if(DragonHead[i][2] == 1){
			DragonUpdate(i);
		}
	}
	
	for(new i = 0; i <= NGCCommanderPool; i++){
		if(NGCCommander[i][2] == 1){
			CommanderUpdate(i);
		}
	}
	
	for(new i = 0; i <= NGCExcavatorPool; i++){
		if(NGCExcavator[i][2] == 1){
			ExcavatorUpdate(i);
		}
	}
	
	
	for(new i = 0; i <= UnderDudeHeadPool; i++){
		if(UnderDudeHead[i][2] == 1){
			UnderDudeUpdate(i);
		}
	}
	return 1;
}

public DefenseHulkUpdate(mobid){
	if(DefenseHulkStatus[mobid] == (1)){
		EngineXCA(DefenseHulk[mobid][22],DefenseHulk[mobid][0],ENGINE_NORMAL,50,200,25,MOB_SPEED_SLOW);
	}
	return 1;
}

public CreateDefenseHulk(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	new color = 0xFFFF0000;
	
	DefenseHulk[mobid][22] = CreateDynamicObject(1489,0.000000,0.000000,0.000000+9000.0,0.000000,0.000000,0.000000,-1,-1,-1,20000.0);

	DefenseHulk[mobid][2] = CreateDynamicObject(4832,-40.000000,0.000000,-0.699996,270.000000,270.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][2],DefenseHulk[mobid][22],-40.000000,0.000000,-0.699996,270.000000,270.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][2],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][3] = CreateDynamicObject(4832,40.000000,0.000000,0.599998,90.000000,0.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][3],DefenseHulk[mobid][22],40.000000,0.000000,0.599998,90.000000,0.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][3],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][4] = CreateDynamicObject(4832,40.000000,48.000000,0.599998,90.000000,0.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][4],DefenseHulk[mobid][22],40.000000,48.000000,0.599998,90.000000,0.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][4],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][5] = CreateDynamicObject(4832,-40.000000,48.000000,-0.699996,270.000000,270.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][5],DefenseHulk[mobid][22],-40.000000,48.000000,-0.699996,270.000000,270.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][5],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][6] = CreateDynamicObject(4832,40.000000,-48.000000,0.599998,90.000000,0.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][6],DefenseHulk[mobid][22],40.000000,-48.000000,0.599998,90.000000,0.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][6],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][7] = CreateDynamicObject(4832,-40.000000,-48.000000,-0.699996,270.000000,270.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][7],DefenseHulk[mobid][22],-40.000000,-48.000000,-0.699996,270.000000,270.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][7],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][8] = CreateDynamicObject(4832,-40.000000,96.000000,-0.699996,270.000000,270.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][8],DefenseHulk[mobid][22],-40.000000,96.000000,-0.699996,270.000000,270.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][8],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][9] = CreateDynamicObject(4832,40.000000,96.000000,0.599998,90.000000,0.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][9],DefenseHulk[mobid][22],40.000000,96.000000,0.599998,90.000000,0.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][9],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][10] = CreateDynamicObject(4832,40.000000,-96.000000,0.599998,90.000000,0.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][10],DefenseHulk[mobid][22],40.000000,-96.000000,0.599998,90.000000,0.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][10],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][11] = CreateDynamicObject(4832,-40.000000,-96.000000,-0.699996,270.000000,270.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][11],DefenseHulk[mobid][22],-40.000000,-96.000000,-0.699996,270.000000,270.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],1,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],2,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],3,2707,"Shopping","white",color); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],4,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],5,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],6,2707,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][11],0,2707,"Shopping","white",color); 

	DefenseHulk[mobid][12] = CreateDynamicObject(7236,-30.000000,-140.000000,0.000000,90.000000,0.000000,315.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][12],DefenseHulk[mobid][22],-30.000000,-140.000000,0.000000,90.000000,0.000000,315.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][12],0,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][12],1,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][12],2,2707,"Shopping","white",color); 

	DefenseHulk[mobid][13] = CreateDynamicObject(7236,30.000000,-140.000000,0.000000,90.000000,0.000000,45.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][13],DefenseHulk[mobid][22],30.000000,-140.000000,0.000000,90.000000,0.000000,45.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][13],0,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][13],1,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][13],2,2707,"Shopping","white",color); 

	DefenseHulk[mobid][14] = CreateDynamicObject(7236,0.000000,50.000000,15.000000,45.000000,0.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][14],DefenseHulk[mobid][22],0.000000,50.000000,15.000000,45.000000,0.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][14],0,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][14],1,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][14],2,2707,"Shopping","white",color); 

	DefenseHulk[mobid][15] = CreateDynamicObject(7236,0.000000,-140.000000,-20.000000,135.000000,0.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][15],DefenseHulk[mobid][22],0.000000,-140.000000,-20.000000,135.000000,0.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][15],0,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][15],1,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][15],2,2707,"Shopping","white",color); 

	DefenseHulk[mobid][16] = CreateDynamicObject(6930,0.000000,-110.000000,16.000000,0.000000,0.000000,270.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][16],DefenseHulk[mobid][22],0.000000,-110.000000,16.000000,0.000000,0.000000,270.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],0,10817,"airportgnd_sfse","black64",0x00000000);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],1,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],2,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],3,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],4,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],5,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][16],6,2707,"Shopping","white",color);

	DefenseHulk[mobid][17] = CreateDynamicObject(6930,0.000000,-110.000000,-16.000000,0.000000,180.000000,270.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][17],DefenseHulk[mobid][22],0.000000,-110.000000,-16.000000,0.000000,180.000000,270.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],0,10817,"airportgnd_sfse","black64",0x00000000);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],1,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],2,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],3,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],4,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],5,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][17],6,2707,"Shopping","white",color);

	DefenseHulk[mobid][18] = CreateDynamicObject(7236,0.000000,-140.000000,20.000000,45.000000,0.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][18],DefenseHulk[mobid][22],0.000000,-140.000000,20.000000,45.000000,0.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][18],0,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][18],1,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][18],2,2707,"Shopping","white",color); 

	DefenseHulk[mobid][19] = CreateDynamicObject(7236,0.000000,50.000000,-15.000000,135.000000,0.000000,0.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][19],DefenseHulk[mobid][22],0.000000,50.000000,-15.000000,135.000000,0.000000,0.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][19],0,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][19],1,10817,"airportgnd_sfse","black64",0x00000000); 
	SetDynamicObjectMaterial(DefenseHulk[mobid][19],2,2707,"Shopping","white",color); 

	DefenseHulk[mobid][20] = CreateDynamicObject(9237,10.000000,128.000000,0.000000,0.000000,90.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][20],DefenseHulk[mobid][22],10.000000,128.000000,0.000000,0.000000,90.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][20],0,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][20],1,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][20],2,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][20],3,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][20],4,2707,"Shopping","white",color);

	DefenseHulk[mobid][21] = CreateDynamicObject(9237,-10.000000,128.000000,0.000000,0.000000,90.000000,90.000000,worldid,interiorid,-1,SD_VERYHIGH,SD_VERYHIGH);
	AttachDynamicObjectToObject(DefenseHulk[mobid][21],DefenseHulk[mobid][22],-10.000000,128.000000,0.000000,0.000000,90.000000,90.000000,1);
	SetDynamicObjectMaterial(DefenseHulk[mobid][21],0,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][21],1,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][21],2,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][21],3,2707,"Shopping","white",color);
	SetDynamicObjectMaterial(DefenseHulk[mobid][21],4,2707,"Shopping","white",color);
	
	SetDynamicObjectPos(DefenseHulk[mobid][22],x,y,z);
	DefenseHulkStatus[mobid] = (1);
	DefenseHulk[mobid][0] = areaid;
	return 1;
}

public DestroyDefenseHulk(mobid){
	DefenseHulkStatus[mobid] = (0);
	StopDynamicObject(DefenseHulk[mobid][22]);
	for(new i = 2; i < 23; i++){
		if(IsValidDynamicObject(DefenseHulk[mobid][i])){
			DestroyDynamicObject(DefenseHulk[mobid][i]);
		}
	}
	return 1;
}

// 0 objectid
// 1 areaid
// 2 status
// 3 step

public FighterUpdate(mobid){
	if(NGCFighter[mobid][2] == 1){
		if(!IsDynamicObjectMoving(NGCFighter[mobid][0])){
			if(NGCFighter[mobid][3] == 0){
				EpsilonEngineRotation(NGCFighter[mobid][0],ENGINE_FIGHTER);
				NGCFighter[mobid][3] = 1;
			} else {
				EpsilonEngineX(NGCFighter[mobid][0],NGCFighter[mobid][1],ENGINE_FIGHTER,50,100,5,MOB_SPEED_NORMAL);
				NGCFighter[mobid][3] = 0;
			}
		}
	}
	return 1;
}

public CreateFighter(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	NGCFighter[mobid][0] = CreateDynamicObject(10757,x,y,z+3.0,8.0,12.0,180.0,worldid,interiorid,-1,300.0);
	NGCFighter[mobid][1] = areaid;
	NGCFighter[mobid][3] = 0;
	
	if(NGCFighterPool < mobid) NGCFighterPool = mobid;
	
	NGCFighter[mobid][2] = 1;
	
	return 1;
}

public DestroyFighter(mobid){
	NGCFighter[mobid][2] = 0;
	if(IsValidDynamicObject(NGCFighter[mobid][0])) DestroyDynamicObject(NGCFighter[mobid][0]);
	return 1;
}


public DragonUpdate(mobid){
	if(DragonHead[mobid][2] == 1){
		if(!IsDynamicObjectMoving(DragonHead[mobid][0])){
			if(DragonHead[mobid][3] == 0){
				EpsilonEngineRotation(DragonHead[mobid][0],ENGINE_SUPPLY);
				DragonHead[mobid][3] = 1;
			} else {
				EpsilonEngineX(DragonHead[mobid][0],DragonHead[mobid][1],ENGINE_SUPPLY,50,100,5,MOB_SPEED_NORMAL);
				DragonHead[mobid][3] = 0;
			}
		}
	}
	return 1;
}

public CreateDragon(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	DragonHead[mobid][0] = CreateDynamicObject(3528,x,y,z+3.0,0.0,0.0,90.0,worldid,interiorid,-1,300.0);
	DragonHead[mobid][1] = areaid;
	DragonHead[mobid][3] = 0;
	
	if(DragonHeadPool < mobid) DragonHeadPool = mobid;
	
	DragonHead[mobid][2] = 1;
	
	return 1;
}

public DestroyDragon(mobid){
	DragonHead[mobid][2] = 0;
	if(IsValidDynamicObject(DragonHead[mobid][0])) DestroyDynamicObject(DragonHead[mobid][0]);
	return 1;
}

public UnderDudeUpdate(mobid){
	if(UnderDudeHead[mobid][2] == 1){
		if(!IsDynamicObjectMoving(UnderDudeHead[mobid][0])){
			if(UnderDudeHead[mobid][3] == 0){
				EpsilonEngineRotation(UnderDudeHead[mobid][0],ENGINE_UNDERDUDE);
				UnderDudeHead[mobid][3] = 1;
			} else {
				EpsilonEngineX(UnderDudeHead[mobid][0],UnderDudeHead[mobid][1],ENGINE_UNDERDUDE,50,100,5,MOB_SPEED_NORMAL);
				UnderDudeHead[mobid][3] = 0;
			}
		}
	}
	return 1;
}

public CreateUnderDude(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	UnderDudeHead[mobid][0] = CreateDynamicObject(1379,x,y,z,0.0,0.0,0.0,worldid,interiorid,-1,300.0);
	UnderDudeHead[mobid][1] = areaid;
	UnderDudeHead[mobid][3] = 0;
	
	if(UnderDudeHeadPool < mobid) UnderDudeHeadPool = mobid;
	
	UnderDudeHead[mobid][2] = 1;
	
	return 1;
}

public DestroyUnderDude(mobid){
	UnderDudeHead[mobid][2] = 0;
	if(IsValidDynamicObject(UnderDudeHead[mobid][0])) DestroyDynamicObject(UnderDudeHead[mobid][0]);
	return 1;
}



public CommanderUpdate(mobid){
	if(NGCCommander[mobid][2] == 1){
		if(!IsDynamicObjectMoving(NGCCommander[mobid][0])){
			if(NGCCommander[mobid][3] == 0){
				EpsilonEngineRotation(NGCCommander[mobid][0],ENGINE_NORMAL);
				NGCCommander[mobid][3] = 1;
			} else {
				EpsilonEngineX(NGCCommander[mobid][0],NGCCommander[mobid][1],ENGINE_NORMAL,50,100,5,MOB_SPEED_NORMAL);
				NGCCommander[mobid][3] = 0;
			}
		}
	}
	return 1;
}

public CreateCommander(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	NGCCommander[mobid][0] = CreateDynamicObject(1681,x,y,z+3.0,8.0,12.0,180.0,worldid,interiorid,-1,300.0);

	//skin
	SetDynamicObjectMaterial(NGCCommander[mobid][0],0,1676,"wshxrefpump","metalic128",0xFFFF0000);
	SetDynamicObjectMaterial(NGCCommander[mobid][0],1,1676,"wshxrefpump","metalic128",0xFFFF0000);

	NGCCommander[mobid][1] = areaid;
	NGCCommander[mobid][3] = 0;
	
	if(NGCCommanderPool < mobid) NGCCommanderPool = mobid;
	
	NGCCommander[mobid][2] = 1;
	
	return 1;
}

public DestroyCommander(mobid){
	NGCCommander[mobid][2] = 0;
	if(IsValidDynamicObject(NGCCommander[mobid][0])) DestroyDynamicObject(NGCCommander[mobid][0]);
	return 1;
}

public ExcavatorUpdate(mobid){
	if(NGCExcavator[mobid][2] == 1){
		EngineXCA(NGCExcavator[mobid][0],NGCExcavator[mobid][1],ENGINE_EXCAVATOR,50,100,1.0,MOB_SPEED_SLOW);
		EngineExcavatorUpdate(NGCExcavator[mobid][0],NGCExcavator[mobid][1],ENGINE_EXCAVATOR,MOB_SPEED_SLOW);		
	}
	return 1;
}

public CreateExcavator(mobid,Float:x,Float:y,Float:z,worldid,interiorid,areaid){
	
	NGCExcavator[mobid][0] = CreateDynamicObject(18248,x,y,z+7.0,0.0,0.0,185.0,worldid,interiorid,-1,300.0);
	NGCExcavator[mobid][1] = areaid;
	NGCExcavator[mobid][3] = 0;
	
	if(NGCExcavatorPool < mobid) NGCExcavatorPool = mobid;
	
	NGCExcavator[mobid][2] = 1;
	
	return 1;
}

public DestroyExcavator(mobid){
	NGCExcavator[mobid][2] = 0;
	if(IsValidDynamicObject(NGCExcavator[mobid][0])) DestroyDynamicObject(NGCExcavator[mobid][0]);
	return 1;
}

//EOF
