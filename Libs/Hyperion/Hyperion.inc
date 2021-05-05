/*
 Hyperion.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg, Missile, progress

 File Version: 1.0.0
 Streamer Version: 2.9.4
 ColAndreas Version: 1.4.0
 3DTryg Version: 5.1.0
 Missile Version: 2.3.0
 Progress Version: 1.3.1.0

 Functions:
 Hyperion::IsPlayerSaved(playerid);
 Hyperion::SavePlayer(playerid,bool:state);
 Hyperion::IsPlayerOnArea(playerid);
 Hyperion::CountPlayers();

 Callbacks:
 IsAllowedToJoinHyperion(playerid);
 OnHyperionBattleResults(playerid,isdead,iswinner);
 OnPlayerEnteringHyperion(playerid,teamid);
 OnPlayerExitHyperion(playerid);
 OnHyperionStateChange(hyperion_state);
 OnHyperionBattleFinished(teamid);
 OnHyperionHelpPresented(playerid);
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

//Check Version 3DTryg.inc
#if !defined TRYG3D_SAMP_INCLUDE
	#error [ADM] You need 3DTryg.inc v5.1.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update you 3DTryg.inc to v5.1.0
#elseif (TRYG3D_VERSION < 50100)
	#error [ADM] Update you 3DTryg.inc to v5.1.0
#endif

//Check Version Missile.inc
#if !defined _missile_launcher
	#error [ADM] You need Missile.inc v2.3.0
#elseif !defined Missile_Version
	#error [ADM] Update you Missile.inc to v2.3.0
#elseif (Missile_Version < 20300)
	#error [ADM] Update you Missile.inc to v2.3.0
#endif

#if !defined _progress_included
	#error [ADM] You need progress.inc
#endif

#define Hyperion::						Hyperion_

#if !defined HYPERION_VW
	#define HYPERION_VW					0
#endif

#if !defined HYPERION_HP_BONUS
	#define HYPERION_HP_BONUS 			20000.0
#endif

#if !defined HYPERION_HP_MORTAR
	#define HYPERION_HP_MORTAR			250000.0
#endif

#if !defined HYPERION_HP_MISSILE
	#define HYPERION_HP_MISSILE			100000.0
#endif

#if !defined HYPERION_HP_CONGREVE
	#define HYPERION_HP_CONGREVE		400000.0
#endif

#if !defined HYPERION_DAMAGE_MORTAR
	#define HYPERION_DAMAGE_MORTAR 		1000.0
#endif

#if !defined HYPERION_DAMAGE_MISSILE
	#define HYPERION_DAMAGE_MISSILE 	1500.0
#endif

#if !defined HYPERION_DAMAGE_CONGREVE
	#define HYPERION_DAMAGE_CONGREVE 	1000.0
#endif

#if !defined HYPERION_START_TIME
	#define HYPERION_START_TIME			90 //seconds
#endif

#if !defined HYPERION_MISSILE_STREAM
	#define HYPERION_MISSILE_STREAM		500.0
#endif

#define HYPERION_EXTRA_META				0x1000BABE

#define HYPERION_DETECTION_RANGE		15.0
#define HYPERION_MAX_OBJECTS			42
#define HYPERION_INVALID_GUARD			-1

#define HYPERION_MIN_QUEUE				6
#define HYPERION_MAX_QUEUE				42

#define HYPERION_WEAPON_NONE			0
#define HYPERION_WEAPON_MORTAR			1
#define HYPERION_WEAPON_MISSILE			2
#define HYPERION_WEAPON_CONGREVE		3

#define HYPERION_TEAM_GREEN				0
#define HYPERION_TEAM_BLUE				1
#define HYPERION_TEAM_INTERRUPT			-1

#define HYPERION_STATE_OFF        		0
#define HYPERION_STATE_STARTING     	1
#define HYPERION_STATE_ON          		2

#define HYPERION_SLOT_LEFT				0
#define HYPERION_SLOT_CENTER			1
#define HYPERION_SLOT_RIGHT				2

enum Hyperion::EnumSpawn {
	Float:						Hyperion::X,
	Float:						Hyperion::Y,
	Float:						Hyperion::Z,
	Float:						Hyperion::Angle,
								Hyperion::Slot,
								Hyperion::Type,
	Float:						Hyperion::Health
};

enum Hyperion::EnumGuard {
								Hyperion::Name[40],
								Hyperion::Type,
	Float:						Hyperion::X,
	Float:						Hyperion::Y,
	Float:						Hyperion::Z,
								Hyperion::Active,
	Float:						Hyperion::Health,
								Hyperion::Respawn,
								Hyperion::PlayerID,
	STREAMER_TAG_AREA:			Hyperion::Area,
	STREAMER_TAG_3D_TEXT_LABEL:	Hyperion::Text,
	STREAMER_TAG_OBJECT:		Hyperion::Object[4]
};

enum Hyperion::EnumPlayer {
	bool:	Hyperion::Saved,
	bool:	Hyperion::Dead,
	bool:	Hyperion::OnArea,
			Hyperion::WeaponType,
			Hyperion::TeamID,
			Hyperion::GuardID,
			Hyperion::Color,
			Hyperion::WeaponTick
};

enum Hyperion::EnumComponent {
			Hyperion::ModelID,
	Float:	Hyperion::X,
	Float:	Hyperion::Y,
	Float:	Hyperion::Z,
	Float:	Hyperion::rX,
	Float:	Hyperion::rY,
	Float:	Hyperion::rZ,
	bool:	Hyperion::Col
};

new Hyperion::WeaponName[][] = {
	"none",
	"Marica\nMortar",
	"Missile\nLaunchpad",
	"Congreve\nRocket"
};

new Hyperion::ObjectColor[2] = {
	0xFF00FF00,
	0xFF0000FF
};
			
new 						Hyperion::CountdownCount = 25,
							Hyperion::CountdownTimer,
							Hyperion::UpdateTimer,
							Hyperion::MaxPlayers,
	Bar:					Hyperion::ProgressBar,
							Hyperion::State,
							Hyperion::StartTick,
	STREAMER_TAG_3D_TEXT_LABEL:	Hyperion::ShipText[2],
							Hyperion::GSTR[256],
	STREAMER_TAG_OBJECT:	Hyperion::ShipObject[2][HYPERION_MAX_OBJECTS],
							Hyperion::Guard[2][21][Hyperion::EnumGuard],
							Hyperion::PlayerData[MAX_PLAYERS][Hyperion::EnumPlayer],
							Hyperion::PlayersList[HYPERION_MAX_QUEUE],
	Text:					Hyperion::TextDrawViewFinder,
	Text:					Hyperion::TextDrawInfo,
	Text:					Hyperion::TextDrawHealth,
	PlayerText:				Hyperion::TextDrawTurretHP[MAX_PLAYERS];

new Hyperion::SpawnList[HYPERION_MAX_QUEUE][Hyperion::EnumSpawn] = {
	{3250.0000,130.0000,16.24,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3350.0000,-130.0000,16.24,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3300.0000,160.0000,17.74,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3400.0000,-160.0000,17.74,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3200.0000,160.0000,17.74,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3300.0000,-160.0000,17.74,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3300.0000,250.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-1
	{3400.0000,-250.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-2
	
	{3250.0000,100.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_CONGREVE,HYPERION_HP_CONGREVE},	// [R] KT-1
	{3350.0000,-100.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_CONGREVE,HYPERION_HP_CONGREVE},	// [R] KT-2
	
	{3250.0000,130.0000,16.24,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3350.0000,-130.0000,16.24,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3300.0000,160.0000,17.74,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3400.0000,-160.0000,17.74,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3200.0000,160.0000,17.74,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3300.0000,-160.0000,17.74,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3200.0000,250.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-1
	{3300.0000,-250.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-2
	
	{3300.0000,130.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_CONGREVE,HYPERION_HP_CONGREVE},	// [R] KT-1
	{3400.0000,-130.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_CONGREVE,HYPERION_HP_CONGREVE},	// [R] KT-2
	
	{3250.0000,160.0000,17.74,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3350.0000,-160.0000,17.74,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3300.0000,190.0000,19.24,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3400.0000,-190.0000,19.24,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3200.0000,190.0000,19.24,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3300.0000,-190.0000,19.24,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3200.0000,130.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_CONGREVE,HYPERION_HP_CONGREVE},	// [R] KT-1
	{3300.0000,-130.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_CONGREVE,HYPERION_HP_CONGREVE},	// [R] KT-2
	
	{3250.0000,160.0000,17.74,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3350.0000,-160.0000,17.74,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3250.0000,190.0000,19.24,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3350.0000,-190.0000,19.24,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3300.0000,190.0000,19.24,180.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3400.0000,-190.0000,19.24,0.0000,HYPERION_SLOT_RIGHT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3300.0000,280.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-1
	{3400.0000,-280.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-2
	
	{3200.0000,190.0000,19.24,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3300.0000,-190.0000,19.24,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3250.0000,190.0000,19.24,180.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},	// [P] KT-1
	{3350.0000,-190.0000,19.24,0.0000,HYPERION_SLOT_LEFT,HYPERION_WEAPON_MISSILE,HYPERION_HP_MISSILE},		// [P] KT-2
	
	{3200.0000,280.0000,14.74,180.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR},		// [M] KT-1
	{3300.0000,-280.0000,14.74,0.0000,HYPERION_SLOT_CENTER,HYPERION_WEAPON_MORTAR,HYPERION_HP_MORTAR}		// [M] KT-2
};

new Float:Hyperion::BridgeSpawnGreen[][3] = {
	{3257.8218,232.0766,30.1174},
	{3255.8975,231.9067,30.1174},
	{3253.9492,231.5501,30.1174},
	{3251.7300,232.1609,30.1174},
	{3250.1157,231.7668,30.1174},
	{3248.1084,231.4469,30.1245},
	{3246.1252,231.4972,30.1245},
	{3243.3335,231.3482,30.1245},
	{3242.1448,232.0002,30.1245},
	{3249.6021,234.1605,30.1245},
	{3251.4106,233.7001,30.1174},
	{3253.4172,233.2105,30.1174},
	{3255.7563,233.6235,30.1174},
	{3258.6328,234.3035,30.1245},
	{3259.8538,235.5732,30.1245},
	{3256.9580,235.4426,30.1174},
	{3254.8447,235.4526,30.1174},
	{3254.6130,238.2337,30.1245},
	{3253.1323,237.7534,30.1245},
	{3251.5305,237.2965,30.1245},
	{3249.4365,237.4266,30.1245}
};

new Float:Hyperion::BridgeSpawnBlue[][3] = {
	{3357.8579,-232.0429,30.1245},
	{3355.4739,-232.0358,30.1245},
	{3353.8313,-231.5824,30.1245},
	{3351.9539,-232.0101,30.1245},
	{3350.1458,-232.3191,30.1245},
	{3348.6362,-231.8685,30.1174},
	{3347.2375,-232.0583,30.1174},
	{3345.3745,-232.6273,30.1174},
	{3343.8105,-232.1398,30.1174},
	{3342.3860,-231.6105,30.1174},
	{3341.3479,-233.9643,30.1245},
	{3343.5964,-233.5673,30.1174},
	{3344.7129,-234.1029,30.1174},
	{3347.3540,-233.3995,30.1174},
	{3349.6255,-234.5882,30.1174},
	{3348.6086,-237.1412,30.1245},
	{3346.9304,-236.6751,30.1245},
	{3344.7410,-236.1580,30.1174},
	{3342.5396,-235.5580,30.1245},
	{3344.6084,-238.1265,30.1245},
	{3347.3240,-237.9314,30.1245}
};

new Hyperion::Component[HYPERION_MAX_OBJECTS][Hyperion::EnumComponent] = {
	{9584,	0.0,		75.3,	19.1,0.0,0.0,270.0,false},
	{2634,	2.5,		58.4,	17.2,0.0,0.0,180.0,false},
	{9585,	-50.0,		30.0,	0.0,0.0,0.0,270.0,true},
	{9585,	0.0,		0.0,	0.0,0.0,0.0,270.0,true},
	{9585,	50.0,		30.0,	0.0,0.0,0.0,270.0,true},
	{9586,	-50.0,		32.3,	10.05,0.0,0.0,270.0,true},
	{9586,	50.0,		32.3,	10.05,0.0,0.0,270.0,true},
	{9586,	0.0,		2.3,	10.05,0.0,0.0,270.0,true},
	{7586,	31.435,		-13.0,	-4.0,0.0,90.0,0.0,true},
	{7586,	18.565,		87.0,	-4.0,0.0,90.0,180.0,true},
	{7586,	-31.435,	-13.0,	-4.0,0.0,90.0,180.0,true},
	{7586,	-18.565,	-13.0,	-4.0,0.0,90.0,0.0,true},
	{7586,	-31.435,	87.0,	-4.0,0.0,90.0,180.0,true},
	{7586,	-18.565,	87.0,	-4.0,0.0,90.0,0.0,true},
	{7586,	18.565,		-13.0,	-4.0,0.0,90.0,180.0,true},
	{7586,	31.435,		87.0,	-4.0,0.0,90.0,0.0,true},
	{7980,	1.6,		-70.0,	11.2,0.0,0.0,270.0,false},
	{7980,	1.6,		-40.0,	11.2,0.0,0.0,270.0,false},
	{7980,	1.6,		-10.0,	11.2,0.0,0.0,270.0,false},
	{7980,	1.6,		20.0,	11.2,0.0,0.0,270.0,false},
	{7980,	51.5,		-40.0,	11.2,0.0,0.0,270.0,false},
	{7980,	51.5,		-10.0,	11.2,0.0,0.0,270.0,false},
	{7980,	51.5,		20.0,	11.2,0.0,0.0,270.0,false},
	{7980,	51.5,		110.0,	11.2,0.0,0.0,270.0,false},
	{7980,	51.5,		80.0,	11.2,0.0,0.0,270.0,false},
	{7980,	-48.5,		80.0,	11.2,0.0,0.0,270.0,false},
	{7980,	-48.5,		110.0,	11.2,0.0,0.0,270.0,false},
	{7980,	-48.5,		-10.0,	11.2,0.0,0.0,270.0,false},
	{7980,	-48.5,		20.0,	11.2,0.0,0.0,270.0,false},
	{7980,	-48.5,		-40.0,	11.2,0.0,0.0,270.0,false},
	{8378,	55.0,		90.1,	8.6,90.0,0.0,270.0,true},
	{8378,	45.0,		90.1,	8.6,90.0,0.0,270.0,true},
	{8378,	-45.0,		90.1,	8.6,90.0,0.0,270.0,true},
	{8378,	-55.0,		90.1,	8.6,90.0,0.0,270.0,true},
	{8378,	5.0,		60.0,	8.6,90.0,0.0,270.0,true},
	{8378,	-5.0,		60.0,	8.6,90.0,0.0,270.0,true},
	{9698, -1.18384, 63.7621, 21.9682,   0.0,0.0,270.0,false},
	{9819, 6.27319, 60.63000, 25.8985,   0.0,0.0,270.0,false},
	{9822, 5.91504, 60.82761, 25.74176,   0.0,0.0,270.0,false},
	{9818, 0.53052, 60.40190, 26.6947,   0.0,0.0,270.0,false},
	{9820, 0.13062, 64.81650, 26.1471,   0.0,0.0,270.0,false},
	{9761, 0.00806, 1.56731, 19.9698,  0.0,0.0,270.0,false}
};

forward IsAllowedToJoinHyperion(playerid);
forward OnHyperionBattleResults(playerid,isdead,iswinner);
forward OnPlayerEnteringHyperion(playerid,teamid);
forward OnPlayerExitHyperion(playerid);
forward OnHyperionStateChange(hyperion_state);
forward OnHyperionBattleFinished(teamid);
forward OnHyperionHelpPresented(playerid);
forward OnHyperionPlayerDeath(playerid,killerid);

#define Hyperion_IsPlayerOnArea(%0)		(Hyperion::PlayerData[(%0)][Hyperion::OnArea])
#define Hyperion_IsPlayerSaved(%0)		(Hyperion::PlayerData[(%0)][Hyperion::Saved])
#define Hyperion_SavePlayer(%0,%1)		(Hyperion::PlayerData[(%0)][Hyperion::Saved] = (%1))

T3D:function Hyperion::FixCamera(playerid,teamid,guardid){
	AttachCameraToDynamicObject(playerid,Hyperion::Guard[teamid][guardid][Hyperion::Object][0]);
	return 1;
}

stock Hyperion::GetPlayerNick(playerid){
	new Hyperion::nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid,Hyperion::nick,MAX_PLAYER_NAME);
	return Hyperion::nick;
}

stock Hyperion::CreatePlayerTextDraw(playerid){
	Hyperion::TextDrawTurretHP[playerid] = CreatePlayerTextDraw(playerid,532.000000,386.000000," ");
	PlayerTextDrawAlignment(playerid,Hyperion::TextDrawTurretHP[playerid],2);
	PlayerTextDrawBackgroundColor(playerid,Hyperion::TextDrawTurretHP[playerid],255);
	PlayerTextDrawFont(playerid,Hyperion::TextDrawTurretHP[playerid],2);
	PlayerTextDrawLetterSize(playerid,Hyperion::TextDrawTurretHP[playerid],0.360000,1.600000);
	PlayerTextDrawColor(playerid,Hyperion::TextDrawTurretHP[playerid],-1);
	PlayerTextDrawSetOutline(playerid,Hyperion::TextDrawTurretHP[playerid],0);
	PlayerTextDrawSetProportional(playerid,Hyperion::TextDrawTurretHP[playerid],1);
	PlayerTextDrawSetShadow(playerid,Hyperion::TextDrawTurretHP[playerid],1);
	PlayerTextDrawUseBox(playerid,Hyperion::TextDrawTurretHP[playerid],1);
	PlayerTextDrawBoxColor(playerid,Hyperion::TextDrawTurretHP[playerid],0x00300030);
	PlayerTextDrawTextSize(playerid,Hyperion::TextDrawTurretHP[playerid],394.000000,209.000000);
	PlayerTextDrawHide(playerid,Hyperion::TextDrawTurretHP[playerid]);
}

stock Hyperion::CountPlayers(){
	new cnt = 0;
	Tryg3D::Foreach(playerid){
		if(Hyperion::PlayerData[playerid][Hyperion::Saved]){
			cnt++;
		}
	}
	return cnt;
}

stock Hyperion::EnterGuard(playerid,teamid,guardid){
	if(Hyperion::Guard[teamid][guardid][Hyperion::PlayerID] == playerid) return 1;
	Hyperion::Guard[teamid][guardid][Hyperion::PlayerID] = playerid;
	Hyperion::PlayerData[playerid][Hyperion::TeamID] = teamid;
	Hyperion::PlayerData[playerid][Hyperion::GuardID] = guardid;
	Hyperion::PlayerData[playerid][Hyperion::WeaponType] = Hyperion::Guard[teamid][guardid][Hyperion::Type];
	switch(teamid){
		case HYPERION_TEAM_GREEN: {
			SetPlayerColor(playerid,0x00FF00FF);
			PlayerTextDrawBoxColor(playerid,Hyperion::TextDrawTurretHP[playerid],0x00FF0030);
		}
		case HYPERION_TEAM_BLUE: {
			SetPlayerColor(playerid,0x00AAFFFF);
			PlayerTextDrawBoxColor(playerid,Hyperion::TextDrawTurretHP[playerid],0x00AAFF30);
		}
	}
	
	AttachCameraToDynamicObject(playerid,Hyperion::Guard[teamid][guardid][Hyperion::Object][0]);
	
	SetTimerEx("Hyperion_FixCamera",500,false,"ddd",playerid,teamid,guardid);
	return 1;
}

stock Hyperion::GuardStore(teamid,guardid,type,name[],Float:x,Float:y,Float:z,slotid){
	format(Hyperion::Guard[teamid][guardid][Hyperion::Name],42,"%s",name);
	Hyperion::Guard[teamid][guardid][Hyperion::Type] = type;
	
	new Float:multiplier = 1.0;
	if(teamid == HYPERION_TEAM_BLUE) multiplier = -1.0;
	switch(slotid){
		case HYPERION_SLOT_LEFT: {
			x += (9.55*multiplier);
		}
		case HYPERION_SLOT_CENTER: {
			x += (-0.1)*multiplier;
		}
		case HYPERION_SLOT_RIGHT: {
			x += (-9.75)*multiplier;
		}
	}
	Hyperion::Guard[teamid][guardid][Hyperion::X] = x;
	Hyperion::Guard[teamid][guardid][Hyperion::Y] = y;
	Hyperion::Guard[teamid][guardid][Hyperion::Z] = z;
	Hyperion::Guard[teamid][guardid][Hyperion::PlayerID] = INVALID_PLAYER_ID;
	
	switch(type){
		case HYPERION_WEAPON_MISSILE: {
			Hyperion::Guard[teamid][guardid][Hyperion::Object][1] = CreateDynamicObject(19943,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
			Hyperion::Guard[teamid][guardid][Hyperion::Object][2] = CreateDynamicObject(19943,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
		
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][1]);
			
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][2]);
		}
		case HYPERION_WEAPON_MORTAR: {
			Hyperion::Guard[teamid][guardid][Hyperion::Object][1] = CreateDynamicObject(3286,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
			Hyperion::Guard[teamid][guardid][Hyperion::Object][2] = CreateDynamicObject(3286,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
			
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],2,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][1]);
			
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],2,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][2]);
		}
		case HYPERION_WEAPON_CONGREVE: {
			Hyperion::Guard[teamid][guardid][Hyperion::Object][1] = CreateDynamicObject(3286,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);

			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],2,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][1]);
			
			Hyperion::Guard[teamid][guardid][Hyperion::Object][2] = CreateDynamicObject(3286,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);

			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],2,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][2]);
			
			Hyperion::Guard[teamid][guardid][Hyperion::Object][3] = CreateDynamicObject(3286,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);

			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][3],0,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][3],1,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(Hyperion::Guard[teamid][guardid][Hyperion::Object][3],2,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][3]);
		}
	}
	switch(teamid){
		case HYPERION_TEAM_GREEN: {
			Hyperion::SetGuardRotation(teamid,guardid,Hyperion::Guard[teamid][guardid][Hyperion::Type],0.0,180.0);
		}
		case HYPERION_TEAM_BLUE: {
			Hyperion::SetGuardRotation(teamid,guardid,Hyperion::Guard[teamid][guardid][Hyperion::Type],0.0,0.0);
		}
	}
}

stock Hyperion::GuardDestroy(teamid,guardid){
	Hyperion::Guard[teamid][guardid][Hyperion::PlayerID] = INVALID_PLAYER_ID;
	switch(teamid){
		case HYPERION_TEAM_GREEN: {
			Hyperion::SetGuardRotation(teamid,guardid,Hyperion::Guard[teamid][guardid][Hyperion::Type],0.0,180.0);
		}
		case HYPERION_TEAM_BLUE: {
			Hyperion::SetGuardRotation(teamid,guardid,Hyperion::Guard[teamid][guardid][Hyperion::Type],0.0,0.0);
		}
	}
	if(IsValidDynamicObject(Hyperion::Guard[teamid][guardid][Hyperion::Object][0])){
		DestroyDynamicObject(Hyperion::Guard[teamid][guardid][Hyperion::Object][0]);
		Hyperion::Guard[teamid][guardid][Hyperion::Object][0] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Hyperion::Guard[teamid][guardid][Hyperion::Text])){
		DestroyDynamic3DTextLabel(Hyperion::Guard[teamid][guardid][Hyperion::Text]);
		Hyperion::Guard[teamid][guardid][Hyperion::Text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Hyperion::Guard[teamid][guardid][Hyperion::Area])){
		DestroyDynamicArea(Hyperion::Guard[teamid][guardid][Hyperion::Area]);
		Hyperion::Guard[teamid][guardid][Hyperion::Area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	Hyperion::Guard[teamid][guardid][Hyperion::Active] = false;
}

stock Hyperion::SetGuardRotation(teamid,guardid,type,Float:rx,Float:rz){
	new Float:tx,Float:ty;
	switch(type){
		case HYPERION_WEAPON_MISSILE: {
			GetPointInFront2D(Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Tryg3D::CompressRotation(rz+90.0),1.2,tx,ty);
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],tx,ty,Hyperion::Guard[teamid][guardid][Hyperion::Z]+3.5);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0));
			GetPointInFront2D(Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Tryg3D::CompressRotation(rz-90.0),1.2,tx,ty);
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],tx,ty,Hyperion::Guard[teamid][guardid][Hyperion::Z]+3.5);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0));
		}
		case HYPERION_WEAPON_MORTAR: {
			GetPointInFront2D(Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Tryg3D::CompressRotation(rz+90.0),3.5,tx,ty);
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],tx,ty,Hyperion::Guard[teamid][guardid][Hyperion::Z]+7.0);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0));
			GetPointInFront2D(Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Tryg3D::CompressRotation(rz-90.0),3.5,tx,ty);
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],tx,ty,Hyperion::Guard[teamid][guardid][Hyperion::Z]+7.0);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0));
			
		}
		case HYPERION_WEAPON_CONGREVE: {
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+7.0);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][1],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0));
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+7.0);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][2],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0-40.0));
			SetDynamicObjectPos(Hyperion::Guard[teamid][guardid][Hyperion::Object][3],Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+7.0);
			SetDynamicObjectRot(Hyperion::Guard[teamid][guardid][Hyperion::Object][3],NMTVF(Tryg3D::CompressRotation(-rx+90.0),90.0),0.0,Tryg3D::CompressRotation(rz-180.0+40.0));
		}
	}
}

stock Hyperion::GuardCreate(teamid,guardid,Float:health,type){
	if(Hyperion::Guard[teamid][guardid][Hyperion::Active]) return 0;
	Hyperion::Guard[teamid][guardid][Hyperion::Area] = CreateDynamicSphere(Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z],HYPERION_DETECTION_RANGE,HYPERION_VW,0);

	new extra_meta_data[3];
	extra_meta_data[0] = HYPERION_EXTRA_META;
	extra_meta_data[1] = teamid;
	extra_meta_data[2] = guardid;
	Streamer::SetArrayData(STREAMER_TYPE_AREA,Hyperion::Guard[teamid][guardid][Hyperion::Area],E_STREAMER_EXTRA_ID,extra_meta_data);
	
	if(type == HYPERION_WEAPON_MORTAR){
		Hyperion::Guard[teamid][guardid][Hyperion::Object][0] = CreateDynamicObject(1489,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+100.0,0.0,0.0,0.0,HYPERION_VW,0,-1,500.0);
	} else {
		Hyperion::Guard[teamid][guardid][Hyperion::Object][0] = CreateDynamicObject(1489,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+15.0,0.0,0.0,0.0,HYPERION_VW,0,-1,500.0);
	}
	SetDynamicObjectNoCameraCol(Hyperion::Guard[teamid][guardid][Hyperion::Object][0]);
	new Float:td_z;
	switch(type){
		case HYPERION_WEAPON_MISSILE: {
			td_z += 5.0;
		}
		case HYPERION_WEAPON_MORTAR: {
			td_z += 11.0;
		}
		case HYPERION_WEAPON_CONGREVE: {
			td_z += 11.0;
		}
	}
	format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"%s\n{FFFFFF} %.0f HP",Hyperion::Guard[teamid][guardid][Hyperion::Name],health);
	switch(teamid){
		case HYPERION_TEAM_GREEN: {
			Hyperion::Guard[teamid][guardid][Hyperion::Text] = CreateDynamic3DTextLabel(Hyperion::GSTR,0x00FF00FF,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+td_z,800.0,.testlos=1,.worldid=HYPERION_VW,.interiorid=0,.streamdistance=800.0);
		}
		case HYPERION_TEAM_BLUE: {
			Hyperion::Guard[teamid][guardid][Hyperion::Text] = CreateDynamic3DTextLabel(Hyperion::GSTR,0x00AAFFFF,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+td_z,800.0,.testlos=1,.worldid=HYPERION_VW,.interiorid=0,.streamdistance=800.0);
		}
	}
	switch(teamid){
		case HYPERION_TEAM_GREEN: {
			Hyperion::SetGuardRotation(teamid,guardid,type,0.0,180.0);
		}
		case HYPERION_TEAM_BLUE: {
			Hyperion::SetGuardRotation(teamid,guardid,type,0.0,0.0);
		}
	}
	Hyperion::Guard[teamid][guardid][Hyperion::Health] = health;
	Hyperion::Guard[teamid][guardid][Hyperion::Active] = true;
	return 1;
}

stock Hyperion::Init(){
	printf("[ADM] Info: Load Hyperion v1.0.0 for SA:MP %s by Abyss Morgan",TRYG3D_SAMP_VERSION);
	new k = 0, STREAMER_TAG_OBJECT:tmp_object;
	for(new guardid = 0; guardid < 21; guardid++){
		for(new teamid = 0; teamid < 2; teamid++){
			Hyperion::GuardStore(teamid,guardid,Hyperion::SpawnList[k][Hyperion::Type],Hyperion::WeaponName[Hyperion::SpawnList[k][Hyperion::Type]],Hyperion::SpawnList[k][Hyperion::X],Hyperion::SpawnList[k][Hyperion::Y],Hyperion::SpawnList[k][Hyperion::Z],Hyperion::SpawnList[k][Hyperion::Slot]);
			Hyperion::CreateWeaponObject(Hyperion::Guard[teamid][guardid][Hyperion::Type],teamid,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]);
			
			if(Hyperion::Guard[teamid][guardid][Hyperion::Z] >= 16.24){
				tmp_object = CA_CreateDynamicObject_SC(18846,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+2.4-1.5,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
				SetDynamicObjectMaterial(tmp_object,0,5150,"wiresetc_las2","metpat64",0x00000000);
				SetDynamicObjectMaterial(tmp_object,1,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			}
			if(Hyperion::Guard[teamid][guardid][Hyperion::Z] >= 17.74){
				tmp_object = CA_CreateDynamicObject_SC(18846,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+2.4-3.0,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
				SetDynamicObjectMaterial(tmp_object,0,5150,"wiresetc_las2","metpat64",0x00000000);
				SetDynamicObjectMaterial(tmp_object,1,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			}
			if(Hyperion::Guard[teamid][guardid][Hyperion::Z] >= 19.24){
				tmp_object = CA_CreateDynamicObject_SC(18846,Hyperion::Guard[teamid][guardid][Hyperion::X],Hyperion::Guard[teamid][guardid][Hyperion::Y],Hyperion::Guard[teamid][guardid][Hyperion::Z]+2.4-4.5,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
				SetDynamicObjectMaterial(tmp_object,0,5150,"wiresetc_las2","metpat64",0x00000000);
				SetDynamicObjectMaterial(tmp_object,1,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			}
			k++;
		}
	}
	
	Tryg3D::Foreach(playerid){
		Hyperion::CreatePlayerTextDraw(playerid);
	}
	
	Hyperion::TextDrawViewFinder = TextDrawCreate(320.0-32.0,240.0-48.0,"LD_BEAT:cring");
	TextDrawFont(Hyperion::TextDrawViewFinder,4);
	TextDrawColor(Hyperion::TextDrawViewFinder,0x00FF0090);
	TextDrawTextSize(Hyperion::TextDrawViewFinder,64.0,64.0);

	Hyperion::TextDrawInfo = TextDrawCreate(535.000000,330.000000-50.0,"~g~-   ~w~vs   ~b~-");
	TextDrawAlignment(Hyperion::TextDrawInfo,2);
	TextDrawBackgroundColor(Hyperion::TextDrawInfo,-791621584);
	TextDrawFont(Hyperion::TextDrawInfo,1);
	TextDrawLetterSize(Hyperion::TextDrawInfo,0.759998,2.500000);
	TextDrawColor(Hyperion::TextDrawInfo,-1);
	TextDrawSetOutline(Hyperion::TextDrawInfo,1);
	TextDrawSetProportional(Hyperion::TextDrawInfo,0);

	Hyperion::TextDrawHealth = TextDrawCreate(535.000000,361.000000-50.0,"~g~-HP               ~b~-HP");
	TextDrawAlignment(Hyperion::TextDrawHealth,2);
	TextDrawBackgroundColor(Hyperion::TextDrawHealth,255);
	TextDrawFont(Hyperion::TextDrawHealth,1);
	TextDrawLetterSize(Hyperion::TextDrawHealth,0.340000,1.399999);
	TextDrawColor(Hyperion::TextDrawHealth,-1);
	TextDrawSetOutline(Hyperion::TextDrawHealth,0);
	TextDrawSetProportional(Hyperion::TextDrawHealth,1);
	TextDrawSetShadow(Hyperion::TextDrawHealth,1);
	
	if(Streamer::GetVisibleItems(STREAMER_TYPE_OBJECT,-1) < 1000){
		Streamer::SetVisibleItems(STREAMER_TYPE_OBJECT,1000,-1);
	}
	
	for(new playerid = 0; playerid < MAX_PLAYERS; playerid++){
		Hyperion::PlayerData[playerid][Hyperion::TeamID] = NO_TEAM;
		Hyperion::PlayerData[playerid][Hyperion::GuardID] = HYPERION_INVALID_GUARD;
	}
	Hyperion::LoadObject(HYPERION_TEAM_GREEN,Hyperion::ObjectColor[HYPERION_TEAM_GREEN],3250.0000,170.0000,4.0000,HYPERION_VW,0);
	Hyperion::LoadObject(HYPERION_TEAM_BLUE,Hyperion::ObjectColor[HYPERION_TEAM_BLUE],3350.0000,-170.0000,4.0000,HYPERION_VW,0);
	for(new i = 0; i < HYPERION_MAX_OBJECTS; i++){
		if(i == 3){
			SetDynamicObjectRot(Hyperion::ShipObject[1][i],0.0,0.0,90.0);
		} else {
			Hyperion::ConvertMega(3350.0000,-170.0000,4.0000,Hyperion::ShipObject[1][i]);
		}
	}
	new Float:x,Float:y,Float:z, Float:rx,Float:ry,Float:rz;
	for(new teamid = 0; teamid < 2; teamid++){
		for(new i = 0; i < HYPERION_MAX_OBJECTS; i++){
			GetDynamicObjectPos(Hyperion::ShipObject[teamid][i],x,y,z);
			GetDynamicObjectRot(Hyperion::ShipObject[teamid][i],rx,ry,rz);
			CA_CreateObject(Streamer::GetIntData(STREAMER_TYPE_OBJECT,Hyperion::ShipObject[teamid][i],E_STREAMER_MODEL_ID),x,y,z,rx,ry,rz,false);
		}
	}
	Hyperion::ShipText[0] = CreateDynamic3DTextLabel("Hyperion Mega Ship",0x00FF00FF,3250.0,236.0,34.0,800.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,HYPERION_VW,0,-1,800.0); //KT-1
	Hyperion::ShipText[1] = CreateDynamic3DTextLabel("Hyperion Mega Ship",0x00AAFFFF,3350.0,-236.0,34.0,800.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,HYPERION_VW,0,-1,800.0); //KT-2
	
	Hyperion::UpdateTimer = SetTimer("Hyperion_OnUpdate",1000,true);
}

stock Hyperion::Exit(){
	printf("[ADM] Info: Unload Hyperion v1.0.0 for SA:MP %s by Abyss Morgan",TRYG3D_SAMP_VERSION);
	if(Hyperion::State == HYPERION_STATE_ON){
		Hyperion::Finish();
	}
	TextDrawDestroy(Hyperion::TextDrawHealth);
	TextDrawDestroy(Hyperion::TextDrawInfo);
	TextDrawDestroy(Hyperion::TextDrawViewFinder);
	if(_:Hyperion::ProgressBar != -1) DestroyProgressBar(Hyperion::ProgressBar);
	KillTimer(Hyperion::UpdateTimer);
	for(new i = 0; i < MAX_PLAYERS; i++){
		PlayerTextDrawDestroy(i,Hyperion::TextDrawTurretHP[i]);
	}
	UpdateDynamic3DTextLabelText(Hyperion::ShipText[0],0x00FF00FF,"Hyperion Mega Ship");
	UpdateDynamic3DTextLabelText(Hyperion::ShipText[1],0x00AAFFFF,"Hyperion Mega Ship");
}

stock Hyperion::Start(){
	new aPlayers[HYPERION_MAX_QUEUE], aMaxPlayers = 0;
	
	Tryg3D::Foreach(playerid){
		if(Hyperion::PlayerData[playerid][Hyperion::Saved]){
			if(CallLocalFunction("IsAllowedToJoinHyperion","d",playerid)){
				aPlayers[aMaxPlayers++] = playerid;
			} else {
				Hyperion::PlayerData[playerid][Hyperion::Saved] = false;
			}
		}
	}

	if(aMaxPlayers < HYPERION_MIN_QUEUE){
		Tryg3D::Foreach(playerid){
			Hyperion::PlayerData[playerid][Hyperion::Saved] = false;
		}
		Hyperion::State = HYPERION_STATE_OFF;
		CallLocalFunction("OnHyperionStateChange","d",Hyperion::State);
		return 0;
	}

	TextDrawSetString(Hyperion::TextDrawInfo,"~g~-   ~w~vs   ~b~-");
	Hyperion::ProgressBar = CreateProgressBar(453.00,356.00-50.0,166.50,4.50,0x00FFFFFF,2.0);
	HideProgressBarForAll(Hyperion::ProgressBar);
	
	new teamid,used_guard[2];
	for(new i = 0; i < aMaxPlayers; i++){
		new playerid = aPlayers[i];
		teamid = (i % 2);
		
		CallLocalFunction("OnPlayerEnteringHyperion","dd",playerid,teamid);
		
		Hyperion::PlayerData[playerid][Hyperion::TeamID] = teamid;
		Hyperion::PlayerData[playerid][Hyperion::GuardID] = used_guard[teamid];
		Hyperion::PlayerData[playerid][Hyperion::WeaponType] = Hyperion::Guard[teamid][used_guard[teamid]][Hyperion::Type];
		
		Hyperion::PlayerData[playerid][Hyperion::Dead] = false;
		Hyperion::PlayerData[playerid][Hyperion::Saved] = false;
		Hyperion::PlayerData[playerid][Hyperion::OnArea] = true;
		Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = GetTickCount();
		
		SetPlayerHealth(playerid,100000.0);
		SetPlayerArmour(playerid,0.0);
		SetPlayerTime(playerid,0,0);
		SetPlayerWeather(playerid,17);
		ResetPlayerWeapons(playerid);

		Streamer::ToggleIdleUpdate(playerid,1);
		switch(teamid){
			case HYPERION_TEAM_BLUE: {
				SetPlayerAbsolutePosition(playerid,Hyperion::BridgeSpawnBlue[used_guard[teamid]][0],Hyperion::BridgeSpawnBlue[used_guard[teamid]][1],Hyperion::BridgeSpawnBlue[used_guard[teamid]][2],0.0,HYPERION_VW,0,2000,0);
			}
			case HYPERION_TEAM_GREEN: {
				SetPlayerAbsolutePosition(playerid,Hyperion::BridgeSpawnGreen[used_guard[teamid]][0],Hyperion::BridgeSpawnGreen[used_guard[teamid]][1],Hyperion::BridgeSpawnGreen[used_guard[teamid]][2],180.0,HYPERION_VW,0,2000,0);
			}
		}
		CallLocalFunction("OnHyperionHelpPresented","d",playerid);
		used_guard[teamid]++;
	}
	
	Hyperion::PlayersList = aPlayers;
	Hyperion::MaxPlayers = aMaxPlayers;
	Hyperion::CountdownCount = 25;
	Hyperion::CountdownTimer = SetTimer("Hyperion_Countdown",1000,true);
	Hyperion::StartTick = GetTickCount();
	return 1;
}

stock Hyperion::Finish(){
	Hyperion::State = HYPERION_STATE_OFF;
	if(_:Hyperion::ProgressBar != -1){
		HideProgressBarForAll(Hyperion::ProgressBar);
		DestroyProgressBar(Hyperion::ProgressBar);
	}
	TextDrawHideForAll(Hyperion::TextDrawInfo);
	TextDrawHideForAll(Hyperion::TextDrawHealth);
	TextDrawHideForAll(Hyperion::TextDrawViewFinder);

	new playerid;
	for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
		if(Hyperion::PlayersList[idx] == INVALID_PLAYER_ID) continue;
		if(IsPlayerConnected(Hyperion::PlayersList[idx])){
			if(Hyperion::PlayerData[Hyperion::PlayersList[idx]][Hyperion::OnArea]){
				Hyperion::PlayerExit(Hyperion::PlayersList[idx]);
			}
		}
		Hyperion::PlayersList[idx] = INVALID_PLAYER_ID;
	}
	for(new teamid = 0; teamid < 2; teamid++){
		for(new guardid = 0; guardid < 21; guardid++){
			Hyperion::GuardDestroy(teamid,guardid);
		}
	}
	Hyperion::MaxPlayers = 0;
	Hyperion::StartTick = 0;

	for(new i = 0; i < MAX_PLAYERS; i++){
		Hyperion::PlayerData[playerid][Hyperion::Saved] = false;
		Hyperion::PlayerData[playerid][Hyperion::Dead] = false;
		Hyperion::PlayerData[playerid][Hyperion::OnArea] = false;
		Hyperion::PlayerData[playerid][Hyperion::WeaponType] = HYPERION_WEAPON_NONE;
		Hyperion::PlayerData[playerid][Hyperion::TeamID] = NO_TEAM;
		Hyperion::PlayerData[playerid][Hyperion::GuardID] = HYPERION_INVALID_GUARD;
		Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = GetTickCount();
	}
	return 1;
}
	
stock Hyperion::PlayerExit(playerid){
	Hyperion::PlayerData[playerid][Hyperion::OnArea] = false;
	Hyperion::PlayerData[playerid][Hyperion::WeaponType] = HYPERION_WEAPON_NONE;
	Hyperion::PlayerData[playerid][Hyperion::TeamID] = NO_TEAM;
	Hyperion::PlayerData[playerid][Hyperion::GuardID] = HYPERION_INVALID_GUARD;
	AttachCameraToDynamicObject(playerid,STREAMER_TAG_OBJECT:INVALID_STREAMER_ID);
	SetPlayerTeam(playerid,NO_TEAM);
	SetCameraBehindPlayer(playerid);
	SetPlayerVirtualWorld(playerid,0);
	SetPlayerInterior(playerid,0);
	SetPlayerHealth(playerid,100.0);
	SpawnPlayer(playerid);
	if(Hyperion::PlayerData[playerid][Hyperion::Color] != 0){
		SetPlayerColor(playerid,Hyperion::PlayerData[playerid][Hyperion::Color]);
		Hyperion::PlayerData[playerid][Hyperion::Color] = 0;
	}
	Hyperion::PlayerData[playerid][Hyperion::Dead] = false;
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawInfo);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawHealth);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawViewFinder);
	if(_:Hyperion::ProgressBar != -1) HideProgressBarForPlayer(playerid,Hyperion::ProgressBar);
	PlayerTextDrawHide(playerid,Hyperion::TextDrawTurretHP[playerid]);
	CallLocalFunction("OnPlayerExitHyperion","d",playerid);
}

T3D:function Hyperion::Countdown(){
	new buffer[64],teamid,used_guard[2];

	if(Hyperion::CountdownCount <= 0){
		format(buffer,sizeof(buffer),"~g~GO!");
		KillTimer(Hyperion::CountdownTimer);
	} else {
		format(buffer,sizeof(buffer),"~r~%i",Hyperion::CountdownCount);
	}

	for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
		teamid = idx % 2;
		if(!IsPlayerConnected(Hyperion::PlayersList[idx])){
			used_guard[teamid]++;
			continue;
		}
		GameTextForPlayer(Hyperion::PlayersList[idx],buffer,1000,6);
		if(Hyperion::CountdownCount == 0){
			PlayerPlaySound(Hyperion::PlayersList[idx],1057,0.0,0.0,0.0);
			SetPlayerTeam(Hyperion::PlayersList[idx],teamid);
			Hyperion::PlayerData[Hyperion::PlayersList[idx]][Hyperion::Color] = GetPlayerColor(Hyperion::PlayersList[idx]);
			Hyperion::GuardCreate(teamid,used_guard[teamid],Hyperion::SpawnList[idx][Hyperion::Health]+(HYPERION_HP_BONUS*(Hyperion::MaxPlayers-6)),Hyperion::SpawnList[idx][Hyperion::Type]);
			Hyperion::EnterGuard(Hyperion::PlayersList[idx],teamid,used_guard[teamid]);
			
			TextDrawShowForPlayer(Hyperion::PlayersList[idx],Hyperion::TextDrawInfo);
			TextDrawShowForPlayer(Hyperion::PlayersList[idx],Hyperion::TextDrawHealth);
			TextDrawShowForPlayer(Hyperion::PlayersList[idx],Hyperion::TextDrawViewFinder);
			ShowProgressBarForPlayer(Hyperion::PlayersList[idx],Hyperion::ProgressBar);
			PlayerTextDrawShow(Hyperion::PlayersList[idx],Hyperion::TextDrawTurretHP[Hyperion::PlayersList[idx]]);
			
			used_guard[teamid]++;
		} else {
			PlayerPlaySound(Hyperion::PlayersList[idx],1056,0.0,0.0,0.0);
		}
	}
	Hyperion::CountdownCount--;
}

T3D:function Hyperion::OnUpdate(){
	if(Hyperion::State == HYPERION_STATE_OFF && Hyperion::CountPlayers() >= HYPERION_MIN_QUEUE){
		Hyperion::State = HYPERION_STATE_STARTING;
		Hyperion::StartTick = GetTickCount() + HYPERION_START_TIME*1000;
		CallLocalFunction("OnHyperionStateChange","d",Hyperion::State);
	} else if(Hyperion::State == HYPERION_STATE_STARTING && Hyperion::CountPlayers() < HYPERION_MIN_QUEUE){
		Hyperion::State = HYPERION_STATE_OFF;
		CallLocalFunction("OnHyperionStateChange","d",Hyperion::State);
	} else if(Hyperion::State == HYPERION_STATE_STARTING && Hyperion::StartTick <= GetTickCount()){
		Hyperion::State = HYPERION_STATE_ON;
		Hyperion::Start();
		if(Hyperion::State == HYPERION_STATE_ON){
			CallLocalFunction("OnHyperionStateChange","d",Hyperion::State);
		}
	} else if(Hyperion::State == HYPERION_STATE_ON){
		Hyperion::Update();
	}
}

stock Hyperion::Update(){
	if(Hyperion::State != HYPERION_STATE_ON) return 0;
	new _hp[2],_cnt[2],playerid,teamid,guardid;
	if(GetTickCount() >= (Hyperion::StartTick+2000) && Hyperion::StartTick != 0){
		for(guardid = 0; guardid < 21; guardid++){
			for(teamid = 0; teamid < 2; teamid++){
				format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"%s\n{FFFFFF} %.0f HP",Hyperion::Guard[teamid][guardid][Hyperion::Name],Hyperion::Guard[teamid][guardid][Hyperion::Health]);
				switch(teamid){
					case HYPERION_TEAM_GREEN: {
						UpdateDynamic3DTextLabelText(Hyperion::Guard[teamid][guardid][Hyperion::Text],0x00FF00FF,Hyperion::GSTR);
					}
					case HYPERION_TEAM_BLUE: {
						UpdateDynamic3DTextLabelText(Hyperion::Guard[teamid][guardid][Hyperion::Text],0x00AAFFFF,Hyperion::GSTR);
					}
				}
				if(Hyperion::Guard[teamid][guardid][Hyperion::Health] <= 0.0){
					if(IsPlayerConnected(Hyperion::Guard[teamid][guardid][Hyperion::PlayerID])){
						if(Hyperion::PlayerData[Hyperion::Guard[teamid][guardid][Hyperion::PlayerID]][Hyperion::OnArea]){
							Hyperion::PlayerExit(Hyperion::Guard[teamid][guardid][Hyperion::PlayerID]);
						}
					}
					Hyperion::GuardDestroy(teamid,guardid);
				}
			}
		}
	}
	for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
		playerid = Hyperion::PlayersList[idx];
		if(!IsPlayerConnected(playerid)){
			Hyperion::PlayersList[idx] = INVALID_PLAYER_ID;
			continue;
		}
		if(Hyperion::PlayerData[playerid][Hyperion::OnArea]){
			teamid = Hyperion::PlayerData[playerid][Hyperion::TeamID];
			guardid = Hyperion::PlayerData[playerid][Hyperion::GuardID];
			_hp[teamid] += floatround(Hyperion::Guard[teamid][guardid][Hyperion::Health]);
			_cnt[teamid]++;
			switch(Hyperion::PlayerData[playerid][Hyperion::WeaponType]){
				case HYPERION_WEAPON_MORTAR: {
					format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"~r~~h~Marica Mortar~n~~b~~h~~h~~h~~w~%.0f HP",Hyperion::Guard[teamid][guardid][Hyperion::Health]);
				}
				case HYPERION_WEAPON_MISSILE: {
					format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"~r~~h~Missile Launcher~n~~b~~h~~h~~h~~w~%.0f HP",Hyperion::Guard[teamid][guardid][Hyperion::Health]);
				}
				case HYPERION_WEAPON_CONGREVE: {
					format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"~r~~h~Congreve Rocket~n~~b~~h~~h~~h~~w~%.0f HP",Hyperion::Guard[teamid][guardid][Hyperion::Health]);
				}
			}
			PlayerTextDrawSetString(playerid,Hyperion::TextDrawTurretHP[playerid],Hyperion::GSTR);
			SetPlayerTime(playerid,0,0);
			SetPlayerWeather(playerid,17);
		}
	}
	
	_hp[0] += 1;
	_hp[1] += 1;
	
	SetProgressBarMaxValue(Hyperion::ProgressBar,float(_hp[0]+_hp[1]));
	SetProgressBarValue(Hyperion::ProgressBar,float(_hp[0]));
	SetProgressBarColor(Hyperion::ProgressBar,0x00000000+(floatround(255*_hp[0]/(_hp[0]+_hp[1]))<<16)+(floatround(255*_hp[1]/(_hp[0]+_hp[1]))<<8)+0xff);
	
	_hp[0] -= 1;
	_hp[1] -= 1;

	format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"~g~%d   ~w~vs   ~b~%d",_cnt[0],_cnt[1]);
	TextDrawSetString(Hyperion::TextDrawInfo,Hyperion::GSTR);
	format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"~g~%dHP			   ~b~%dHP~n~~n~~w~Hyperion Mega Ship",_hp[0],_hp[1]);
	TextDrawSetString(Hyperion::TextDrawHealth,Hyperion::GSTR);
	
	if(Hyperion::CountdownCount <= 0){
		format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"Hyperion Mega Ship\n{FFFFFF}%d HP",_hp[0]);
		UpdateDynamic3DTextLabelText(Hyperion::ShipText[0],0x00FF00FF,Hyperion::GSTR);
		format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"Hyperion Mega Ship\n{FFFFFF}%d HP",_hp[1]);
		UpdateDynamic3DTextLabelText(Hyperion::ShipText[1],0x00AAFFFF,Hyperion::GSTR);
	
		for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
			if(IsPlayerConnected(Hyperion::PlayersList[idx]) && Hyperion::PlayerData[Hyperion::PlayersList[idx]][Hyperion::OnArea]){
				UpdateProgressBar(Hyperion::ProgressBar,Hyperion::PlayersList[idx]);
			}
		}
	}

	if(_cnt[HYPERION_TEAM_GREEN] < 1 && _cnt[HYPERION_TEAM_BLUE] >= 1){
		CallLocalFunction("OnHyperionBattleFinished","d",HYPERION_TEAM_BLUE);
		for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
			playerid = Hyperion::PlayersList[idx];
			if(IsPlayerConnected(playerid)){
				if(Hyperion::PlayerData[playerid][Hyperion::TeamID] == HYPERION_TEAM_BLUE){
					CallLocalFunction("OnHyperionBattleResults","ddd",playerid,Hyperion::PlayerData[playerid][Hyperion::Dead],1);
				} else {
					CallLocalFunction("OnHyperionBattleResults","ddd",playerid,Hyperion::PlayerData[playerid][Hyperion::Dead],0);
				}
			}
		}
		Hyperion::Finish();
	} else if(_cnt[HYPERION_TEAM_BLUE] < 1 && _cnt[HYPERION_TEAM_GREEN] >= 1){
		CallLocalFunction("OnHyperionBattleFinished","d",HYPERION_TEAM_GREEN);
		for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
			playerid = Hyperion::PlayersList[idx];
			if(IsPlayerConnected(playerid)){
				if(Hyperion::PlayerData[playerid][Hyperion::TeamID] == HYPERION_TEAM_GREEN){
					CallLocalFunction("OnHyperionBattleResults","ddd",playerid,Hyperion::PlayerData[playerid][Hyperion::Dead],1);
				} else {
					CallLocalFunction("OnHyperionBattleResults","ddd",playerid,Hyperion::PlayerData[playerid][Hyperion::Dead],0);
				}
			}
		}
		Hyperion::Finish();
	} else if(_cnt[HYPERION_TEAM_BLUE] < 1 && _cnt[HYPERION_TEAM_GREEN] < 1){
		CallLocalFunction("OnHyperionBattleFinished","d",HYPERION_TEAM_INTERRUPT);
		Hyperion::Finish();
	}
	return 1;
}

stock Hyperion::OnMegaWeaponShot(playerid){
	new F4[Float3D], F5[Float3D], teamid, guardid;
	
	teamid = Hyperion::PlayerData[playerid][Hyperion::TeamID];
	guardid = Hyperion::PlayerData[playerid][Hyperion::GuardID];
	
	F5[T3D:X] = Hyperion::Guard[teamid][guardid][Hyperion::X];
	F5[T3D:Y] = Hyperion::Guard[teamid][guardid][Hyperion::Y];
	F5[T3D:Z] = Hyperion::Guard[teamid][guardid][Hyperion::Z] + 15.0;
	
	switch(Hyperion::PlayerData[playerid][Hyperion::WeaponType]){
		case HYPERION_WEAPON_MISSILE: {
			if(GetTickCount()-Hyperion::PlayerData[playerid][Hyperion::WeaponTick] < 500) return 1;

			GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
			
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],180.0,Tryg3D::CompressRotation(F5[T3D:rZ]+90.0),2.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],1500.0,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_SMALL,5.0,25.0,100.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MISSILE);

			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F5[T3D:rZ]+90.0),2.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront3DCol(F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F5[T3D:rX],F5[T3D:rZ],1500.0,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_SMALL,5.0,25.0,100.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_NORMAL,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MISSILE);

			Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = GetTickCount();
		}
		case HYPERION_WEAPON_MORTAR: {
			if(GetTickCount()-Hyperion::PlayerData[playerid][Hyperion::WeaponTick] < 3000) return 1;
			
			new Float:tx, Float:ty, Float:tz, Float:ox, Float:oy, Float:oz;
			
			GetPlayerCameraPos(playerid,ox,oy,oz);
			GetPlayerCameraRotation(playerid,F5[T3D:rX],F5[T3D:rZ]);
			GetPointInFront3DCol(ox,oy,oz,F5[T3D:rX],F5[T3D:rZ],3000.0,tx,ty,tz);
			GetRotationFor2Point2D(F5[T3D:X],F5[T3D:Y],tx,ty,F4[T3D:rZ]);
			
			new Float:Hyperion::dist = GetDistanceBetweenPoints2D(F5[T3D:X],F5[T3D:Y],tx,ty);
			
			new remote_cnt = floatround(Hyperion::dist/15.0);
		
			if(remote_cnt > MAX_MISSILE_REMOTE_TARGET) remote_cnt = MAX_MISSILE_REMOTE_TARGET;
			if(remote_cnt < 4) remote_cnt = 4;
		
			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+60.0),2.5,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],Hyperion::dist,F4[T3D:tX],F4[T3D:tY]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,35.0,80.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_BOMB,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],true,remote_cnt,(Hyperion::dist/3.0),.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MORTAR);

			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+120.0),2.5,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],Hyperion::dist,F4[T3D:tX],F4[T3D:tY]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,35.0,80.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_BOMB,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],true,remote_cnt,(Hyperion::dist/3.0),.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MORTAR);

			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+180.0),2.5,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],Hyperion::dist,F4[T3D:tX],F4[T3D:tY]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,35.0,80.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_BOMB,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],true,remote_cnt,(Hyperion::dist/3.0),.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MORTAR);

			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+240.0),2.5,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],Hyperion::dist,F4[T3D:tX],F4[T3D:tY]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,35.0,80.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_BOMB,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],true,remote_cnt,(Hyperion::dist/3.0),.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MORTAR);

			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,Tryg3D::CompressRotation(F4[T3D:rZ]+300.0),2.5,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],Hyperion::dist,F4[T3D:tX],F4[T3D:tY]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,35.0,80.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_BOMB,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],true,remote_cnt,(Hyperion::dist/3.0),.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MORTAR);

			GetPointInFront3D(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],0.0,F4[T3D:rZ],2.5,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
			GetPointInFront2D(F4[T3D:X],F4[T3D:Y],F4[T3D:rZ],Hyperion::dist,F4[T3D:tX],F4[T3D:tY]);
			Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,5.0,35.0,80.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_BOMB,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],true,remote_cnt,(Hyperion::dist/3.0),.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_MORTAR);

			Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = GetTickCount();
		}
		case HYPERION_WEAPON_CONGREVE: {
			if(GetTickCount()-Hyperion::PlayerData[playerid][Hyperion::WeaponTick] < 1500) return 1;
			
			GetPlayerCameraRotation(playerid,F4[T3D:rX],F4[T3D:rZ]);
			
			for(new i = 0; i < 12; i++){
				Random::PointOnSphericalSector(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:rX],F4[T3D:rZ],800.0,5.0,5.0,F4[T3D:X],F4[T3D:Y],F4[T3D:Z]);
				MovePointCol(F5[T3D:X],F5[T3D:Y],F5[T3D:Z],F4[T3D:X],F4[T3D:Y],F4[T3D:Z],F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ]);
				Missile::Launch(MISSILE_TYPE_EXPLODE_NORMAL,15.0,35.0,100.0,F5[T3D:X],F5[T3D:Y],F5[T3D:Z],HYPERION_VW,0,-1,HYPERION_MISSILE_STREAM,MISSILE_OBJECT_HYDRA,F4[T3D:tX],F4[T3D:tY],F4[T3D:tZ],playerid,Hyperion::PlayerData[playerid][Hyperion::TeamID],.damage=0.0,.vehicle_damage=HYPERION_DAMAGE_CONGREVE);
			}
			
			Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = GetTickCount();
		}
	}

	return 1;
}

stock Hyperion::ConvertMega(Float:x,Float:y,Float:z,STREAMER_TAG_OBJECT:objectid){
	if(!IsValidDynamicObject(objectid)) return 0;
	new Float:offset_x,Float:offset_y,Float:offset_z,
		Float:ox,Float:oy,Float:oz,
		Float:tx,Float:ty,Float:tz,
		Float:Hyperion::dist;

	GetDynamicObjectPos(objectid,ox,oy,oz);
	ShiftPositionToOffset(x,y,z,0.0,0.0,0.0,offset_x,offset_y,offset_z,ox,oy,oz);
	
	Hyperion::dist = VectorSize(offset_x,offset_y,offset_z);
	
	ShiftVectorRotation(offset_x,offset_y,offset_z,0.0,0.0,180.0,tx,ty,tz);
	
	tx *= Hyperion::dist;
	ty *= Hyperion::dist;
	tz *= Hyperion::dist;
	
	ShiftOffsetToPosition(x,y,z,0.0,0.0,0.0,tx,ty,tz,ox,oy,oz);
	SetDynamicObjectPos(objectid,ox,oy,oz);
	
	GetDynamicObjectRot(objectid,ox,oy,oz);
	SetDynamicObjectRot(objectid,ox,oy,oz+180.0);
	return 1;
}

stock Hyperion::CreateWeaponObject(type,teamid,Float:x,Float:y,Float:z){
	new STREAMER_TAG_OBJECT:tmp_object;
	switch(type){
		case HYPERION_WEAPON_CONGREVE, HYPERION_WEAPON_MORTAR: {
			for(new i = 0; i < 5; i++){
				tmp_object = CA_CreateDynamicObject_SC(18846,x,y,z+2.4+(1.5*i),0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
				SetDynamicObjectMaterial(tmp_object,0,5150,"wiresetc_las2","metpat64",0x00000000);
				SetDynamicObjectMaterial(tmp_object,1,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			}
		}
		case HYPERION_WEAPON_MISSILE: {
			tmp_object = CA_CreateDynamicObject_SC(18846,x,y,z+2.4,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
			SetDynamicObjectMaterial(tmp_object,0,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(tmp_object,1,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
			
			tmp_object = CA_CreateDynamicObject_SC(18846,x,y,z+2.4+0.5,0.0,0.0,0.0,HYPERION_VW,0,-1,800.0,800.0);
			SetDynamicObjectMaterial(tmp_object,0,5150,"wiresetc_las2","metpat64",0x00000000);
			SetDynamicObjectMaterial(tmp_object,1,5150,"wiresetc_las2","metpat64",Hyperion::ObjectColor[teamid]);
		}
	}
}

stock Hyperion::LoadObject(mobid,color,Float:x,Float:y,Float:z,worldid,interiorid){
	
	for(new k = 0; k < HYPERION_MAX_OBJECTS; k++){
		Hyperion::ShipObject[mobid][k] = CreateDynamicObject(Hyperion::Component[k][Hyperion::ModelID],x+Hyperion::Component[k][Hyperion::X],y+Hyperion::Component[k][Hyperion::Y],z+Hyperion::Component[k][Hyperion::Z],Hyperion::Component[k][Hyperion::rX],Hyperion::Component[k][Hyperion::rY],Hyperion::Component[k][Hyperion::rZ],worldid,interiorid,-1,800.0,800.0);
	}
	
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],0,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],1,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],2,5150,"wiresetc_las2","metpat64",0xFFFFFF00);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],3,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],4,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],5,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],6,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],7,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][0],8,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);

	SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][1],0,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	for(new i = 2; i <= 4; i++){
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],0,6150,"ufo_bar","metalic128",color);
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],1,6150,"ufo_bar","metalic128",color);
	}
	for(new i = 5; i <= 7; i++){
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],0,5150,"wiresetc_las2","metpat64",0x00000000);
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],1,5150,"wiresetc_las2","metpat64",0x00000000);
	}
	for(new i = 8; i <= 15; i++){
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],0,5150,"wiresetc_las2","metpat64",color); 
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],1,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	}
	for(new i = 16; i <= 29; i++){
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],0,5150,"wiresetc_las2","metpat64",color);
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],1,5150,"wiresetc_las2","metpat64",0xFF3B3B3B);
	}
	for(new i = 30; i <= 35; i++){
		SetDynamicObjectMaterial(Hyperion::ShipObject[mobid][i],0,10817,"airportgnd_sfse","black64",0x00000000);
	}
}

//Hook: OnMissileRequestLaunch
public OnMissileRequestLaunch(Float:x,Float:y,Float:z,playerid,targetid){
	if(!Hyperion::PlayerData[playerid][Hyperion::OnArea]){
		if(Area::PointInRectangle(x,y,3180.0000,-350.0000,3430.0000,350.0000)) return 0;
	}
	#if defined HYPER_OnMissileRequestLaunch
		return HYPER_OnMissileRequestLaunch(x,y,z,playerid,targetid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnMissileRequestLaunch
	#undef OnMissileRequestLaunch
#else
	#define _ALS_OnMissileRequestLaunch
#endif
#define OnMissileRequestLaunch HYPER_OnMissileRequestLaunch
#if defined HYPER_OnMissileRequestLaunch
	forward HYPER_OnMissileRequestLaunch(Float:x,Float:y,Float:z,playerid,targetid);
#endif

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(Tryg3D::KeyPressed(KEY_FIRE)){
		if(Hyperion::PlayerData[playerid][Hyperion::OnArea] && !Hyperion::PlayerData[playerid][Hyperion::Dead]){
			if(Hyperion::CountdownCount <= 0){
				if(Hyperion::PlayerData[playerid][Hyperion::WeaponType] != HYPERION_WEAPON_NONE){
					Hyperion::OnMegaWeaponShot(playerid);
				}
			}
		}
	}
	#if defined HYPER_OnPlayerKeyStateChange
		HYPER_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange HYPER_OnPlayerKeyStateChange
#if defined HYPER_OnPlayerKeyStateChange
	forward HYPER_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

//Hook: OnPlayerUpdate
public OnPlayerUpdate(playerid){
	if(Hyperion::PlayerData[playerid][Hyperion::OnArea] && Hyperion::CountdownCount <= 0){
		new Float:rz,Float:rx;
		switch(Hyperion::PlayerData[playerid][Hyperion::WeaponType]){
			case HYPERION_WEAPON_MISSILE, HYPERION_WEAPON_CONGREVE: {
				GetPlayerCameraRotation(playerid,rx,rz);
			}
			case HYPERION_WEAPON_MORTAR: {
				new Float:T3D:rx, Float:T3D:rz, Float:tx, Float:ty, Float:tz, Float:ox, Float:oy, Float:oz;
				GetPlayerCameraPos(playerid,ox,oy,oz);
				GetPlayerCameraRotation(playerid,T3D:rx,T3D:rz);
				GetPointInFront3DCol(ox,oy,oz,T3D:rx,T3D:rz,3000.0,tx,ty,tz);
				GetRotationFor2Point2D(Hyperion::Guard[Hyperion::PlayerData[playerid][Hyperion::TeamID]][Hyperion::PlayerData[playerid][Hyperion::GuardID]][Hyperion::X],Hyperion::Guard[Hyperion::PlayerData[playerid][Hyperion::TeamID]][Hyperion::PlayerData[playerid][Hyperion::GuardID]][Hyperion::Y],tx,ty,rz);
				rx = 35.0;
			}
		}
		Hyperion::SetGuardRotation(Hyperion::PlayerData[playerid][Hyperion::TeamID],Hyperion::PlayerData[playerid][Hyperion::GuardID],Hyperion::PlayerData[playerid][Hyperion::WeaponType],rx,rz);
	}
	#if defined HYPER_OnPlayerUpdate
		HYPER_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate HYPER_OnPlayerUpdate
#if defined HYPER_OnPlayerUpdate
	forward HYPER_OnPlayerUpdate(playerid);
#endif

//Hook: OnMissileDestroy
public OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid){
	if(byplayerid != INVALID_PLAYER_ID){
		new extra_meta_data[3], max_areas = GetNumberDynamicAreasForPoint(x,y,z), Float:Hyperion::damage, teamid, guardid;
		if(max_areas){
			new STREAMER_TAG_AREA:point_areas[128];
			GetDynamicAreasForPoint(x,y,z,point_areas,128);
			for(new k = 0; k < max_areas; k++){
				Streamer::GetArrayData(STREAMER_TYPE_AREA,point_areas[k],E_STREAMER_EXTRA_ID,extra_meta_data);
				if(extra_meta_data[0] == HYPERION_EXTRA_META){
					teamid = extra_meta_data[1];
					guardid = extra_meta_data[2];
					if(teamid >= 0 && teamid <= 1){
						if(guardid >= 0 && guardid < 21){
							if(point_areas[k] == Hyperion::Guard[teamid][guardid][Hyperion::Area]){
								if(teamid != Hyperion::PlayerData[byplayerid][Hyperion::TeamID]){
									Hyperion::damage = Missile::GetVehicleDamage(mobid) + Tryg3D::RandomFloat(0.0,Missile::GetVehicleDamage(mobid));
									if(Hyperion::damage > 0.0 && Hyperion::Guard[teamid][guardid][Hyperion::Health] > 0.0){
										if(Hyperion::Guard[teamid][guardid][Hyperion::Health] - Hyperion::damage <= 0.0){
											Hyperion::Guard[teamid][guardid][Hyperion::Health] = 0.0;
											CallLocalFunction("OnHyperionPlayerDeath","dd",Hyperion::Guard[teamid][guardid][Hyperion::PlayerID],byplayerid);
										} else {
											Hyperion::Guard[teamid][guardid][Hyperion::Health] -= Hyperion::damage;
										}
										format(Hyperion::GSTR,sizeof(Hyperion::GSTR),"~r~%s~n~~w~%.0f HP~n~~r~~h~~h~-%.0f HP",Hyperion::GetPlayerNick(Hyperion::Guard[teamid][guardid][Hyperion::PlayerID]),Hyperion::Guard[teamid][guardid][Hyperion::Health],Hyperion::damage);
										GameTextForPlayer(byplayerid,Hyperion::GSTR,1000,4);
									}
								}
							}
						}
					}
				}
				extra_meta_data = {0,-1,-1};
			}
		}
	}
	#if defined HYPER_OnMissileDestroy
		HYPER_OnMissileDestroy(mobid,x,y,z,type,killerid,byplayerid);
	#endif
	return 1;
}

#if defined _ALS_OnMissileDestroy
	#undef OnMissileDestroy
#else
	#define _ALS_OnMissileDestroy
#endif
#define OnMissileDestroy HYPER_OnMissileDestroy
#if defined HYPER_OnMissileDestroy
	forward HYPER_OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid);
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	PlayerTextDrawDestroy(playerid,Hyperion::TextDrawTurretHP[playerid]);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawInfo);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawHealth);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawViewFinder);
	if(_:Hyperion::ProgressBar != -1) HideProgressBarForPlayer(playerid,Hyperion::ProgressBar);
	
	Hyperion::PlayerData[playerid][Hyperion::Saved] = false;
	Hyperion::PlayerData[playerid][Hyperion::Dead] = false;
	Hyperion::PlayerData[playerid][Hyperion::OnArea] = false;
	Hyperion::PlayerData[playerid][Hyperion::WeaponType] = HYPERION_WEAPON_NONE;
	Hyperion::PlayerData[playerid][Hyperion::TeamID] = NO_TEAM;
	Hyperion::PlayerData[playerid][Hyperion::GuardID] = HYPERION_INVALID_GUARD;
	Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = 0;
	
	for(new idx = 0; idx < Hyperion::MaxPlayers; idx++){
		if(playerid == Hyperion::PlayersList[idx]){
			Hyperion::PlayersList[idx] = INVALID_PLAYER_ID;
		}
	}
	#if defined HYPER_OnPlayerDisconnect
		HYPER_OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect HYPER_OnPlayerDisconnect
#if defined HYPER_OnPlayerDisconnect
	forward HYPER_OnPlayerDisconnect(playerid,reason);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawInfo);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawHealth);
	TextDrawHideForPlayer(playerid,Hyperion::TextDrawViewFinder);
	if(_:Hyperion::ProgressBar != -1) HideProgressBarForPlayer(playerid,Hyperion::ProgressBar);
	
	Hyperion::PlayerData[playerid][Hyperion::Saved] = false;
	Hyperion::PlayerData[playerid][Hyperion::Dead] = false;
	Hyperion::PlayerData[playerid][Hyperion::OnArea] = false;
	Hyperion::PlayerData[playerid][Hyperion::WeaponType] = HYPERION_WEAPON_NONE;
	Hyperion::PlayerData[playerid][Hyperion::TeamID] = NO_TEAM;
	Hyperion::PlayerData[playerid][Hyperion::GuardID] = HYPERION_INVALID_GUARD;
	Hyperion::PlayerData[playerid][Hyperion::WeaponTick] = 0;

	Hyperion::CreatePlayerTextDraw(playerid);

	#if defined HYPER_OnPlayerConnect
		HYPER_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect HYPER_OnPlayerConnect
#if defined HYPER_OnPlayerConnect
	forward HYPER_OnPlayerConnect(playerid);
#endif

new CRC_HyperionInit = true,
	CRC_HyperionExit = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_HyperionInit){
		CRC_HyperionInit = false;
		Hyperion::Init();
	}
	#if defined HYPER_OnFilterScriptInit
		HYPER_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit HYPER_OnFilterScriptInit
#if defined HYPER_OnFilterScriptInit
	forward HYPER_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_HyperionInit){
		CRC_HyperionInit = false;
		Hyperion::Init();
	}
	#if defined HYPER_OnGameModeInit
		HYPER_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit HYPER_OnGameModeInit
#if defined HYPER_OnGameModeInit
	forward HYPER_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_HyperionExit){
		CRC_HyperionExit = false;
		Hyperion::Exit();
	}
	#if defined HYPER_OnFilterScriptExit
		HYPER_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit HYPER_OnFilterScriptExit
#if defined HYPER_OnFilterScriptExit
	forward HYPER_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_HyperionExit){
		CRC_HyperionExit = false;
		Hyperion::Exit();
	}
	#if defined HYPER_OnGameModeExit
		HYPER_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit HYPER_OnGameModeExit
#if defined HYPER_OnGameModeExit
	forward HYPER_OnGameModeExit();
#endif
//EOF