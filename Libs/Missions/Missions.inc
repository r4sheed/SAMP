/*
 Missions.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: Streamer, ColAndreas
 Modules: 3DTryg, route_rand.inc, ExtendedGrenade (optional)

 File Version: 1.2.0
 Streamer Version: 2.9.5
 ColAndreas Version: 1.5.0
 3DTryg Version: Gen. 2 v1.0.0
 ExtendedGrenade Version: 1.1.0

 Functions:
 Missions::SetMissionsScrapKey(key);
 Missions::SetMissionsCorpseKey(key);
 Missions::SetMissionsBombKey(key);
 Missions::CountVehicleScrap(vehicleid);
 Missions::DropScrap(vehicleid);
 Missions::HealCorpse(playerid);
 Missions::CreateRadar(Float:x,Float:y,Float:z,Float:rz,worldid=0,interiorid=0,Float:speed=80.0);
 Missions::DestroyRadar(mobid);
 Missions::SetSpawnRectangle(mission_type,Float:minx,Float:miny,Float:maxx,Float:maxy,bool:spawn_validation=true);
 Missions::SetSpawnPolygon(mission_type,Float:points[],maxpoints=sizeof(points),bool:spawn_validation=true);

 Callbacks:
 OnPlayerEnterPatrol(playerid,mobid);
 OnPlayerDestroyPatrol(playerid,mobid);
 OnPlayerRobbed(playerid,mobid,mission_state);
 OnPlayerFoundCorpse(playerid,mobid);
 OnPlayerHitCorpse(playerid,mobid);
 OnPlayerFoundScrap(playerid,mobid);
 OnPlayerTakeScrap(playerid,mobid,mission_state,count_items);
 OnPlayerExceededSpeed(playerid,mobid,Float:speed,Float:max_speed);
 OnPlayerPutOutFire(playerid,mobid);
 OnPlayerVehicleDamagedByRoad(playerid,mobid,old_health,new_health,veh_damage);
 OnPlayerDestroyedTreeOnRoad(playerid,mobid);
 OnPlayerUnloadingScrap(playerid,count_items);
 OnPlayerHealCorpse(playerid,mobid);
 OnPlayerTryDisarmBomb(playerid,mobid);
 OnPlayerDisarmBomb(playerid,mobid,mission_state);
 OnPlayerFixedRoad(playerid,mobid);
 OnPlayerFixedGasPipe(playerid,mobid);
*/

#if defined _samp_included
	#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
		#error [ADM] This include requires SA:MP version 0.3.7
	#endif
#else
	#error [ADM] This include requires SA:MP Include
#endif

#if ((!defined Streamer_GetItemPos) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR) || (!defined RemoveDynamicObjectMaterialText))
	#error [ADM] This include required Streamer v2.9.5 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined COLANDREAS_VERSION
	#error [ADM] This include required ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#elseif (COLANDREAS_VERSION < 10500)
	#error [ADM] Update your ColAndreas v1.5.0 (github.com/Pottus/ColAndreas/releases)
#endif

#if !defined _route_rand
	#error [ADM] This include requires route_rand.inc and route_rand.bin
#endif

//Check Version 3DTryg.inc
#if !defined TRYG3D_REMASTERED_INCLUDE
	#error [ADM] This include required 3DTryg.inc Gen. 2 v1.0.0
#elseif !defined TRYG3D_VERSION
	#error [ADM] Update your 3DTryg.inc to Gen. 2 v1.0.0
#elseif (TRYG3D_VERSION < 10000)
	#error [ADM] Update your 3DTryg.inc to Gen. 2 v1.0.0
#endif

//Check Version ExtendedGrenade.inc
#if defined EXTENDED_GRENADE_VERSION
	#if (EXTENDED_GRENADE_VERSION < 10100)
		#error [ADM] Update your ExtendedGrenade.inc to v1.1.0
	#else
		#define MISSIONS_EXTENDED_GRENADE
	#endif
#endif

#if !defined TRYG3D_MOD_PLAYER
	#error [ADM] Module not initialized: TRYG3D_MOD_PLAYER (add #define TRYG3D_ENABLE_PLAYER before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_VEHICLE
	#error [ADM] Module not initialized: TRYG3D_MOD_VEHICLE (add #define TRYG3D_ENABLE_VEHICLE before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_UNIVERSAL
	#error [ADM] Module not initialized: TRYG3D_MOD_UNIVERSAL (add #define TRYG3D_ENABLE_UNIVERSAL before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_CAST3D
	#error [ADM] Module not initialized: TRYG3D_MOD_CAST3D (add #define TRYG3D_ENABLE_CAST3D before include 3DTryg.inc)
#endif

#if !defined TRYG3D_MOD_COLANDREAS
	#error [ADM] Module not initialized: TRYG3D_MOD_COLANDREAS (add #define TRYG3D_ENABLE_COLANDREAS before include 3DTryg.inc)
#endif

#if defined _MISSIONS_INCLUDE
	#endinput
#endif
#define _MISSIONS_INCLUDE
#define DYNAMIC_FILTERSCRIPT				"ALS:HOOK:METHOD"

#define MISSIONS_VERSION					(10200) //a.b.c 10000*a+100*b+c

#define Missions::							Missions_

#if !defined MISSIONS_MAX_BOMB
	#define MISSIONS_MAX_BOMB				30
#endif
#if MISSIONS_MAX_BOMB < 1 || MISSIONS_MAX_BOMB > 999
	#error [ADM] Definition MISSIONS_MAX_BOMB must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_WOOD
	#define MISSIONS_MAX_WOOD				100
#endif
#if MISSIONS_MAX_WOOD < 1 || MISSIONS_MAX_WOOD > 999
	#error [ADM] Definition MISSIONS_MAX_WOOD must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_RADAR
	#define MISSIONS_MAX_RADAR				100
#endif
#if MISSIONS_MAX_RADAR < 1 || MISSIONS_MAX_RADAR > 999
	#error [ADM] Definition MISSIONS_MAX_RADAR must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_SCRAP
	#define MISSIONS_MAX_SCRAP				20
#endif
#if MISSIONS_MAX_SCRAP < 1 || MISSIONS_MAX_SCRAP > 999
	#error [ADM] Definition MISSIONS_MAX_SCRAP must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_CORPSE
	#define MISSIONS_MAX_CORPSE				100
#endif
#if MISSIONS_MAX_CORPSE < 1 || MISSIONS_MAX_CORPSE > 999
	#error [ADM] Definition MISSIONS_MAX_CORPSE must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_DMGROUTE
	#define MISSIONS_MAX_DMGROUTE			100
#endif
#if MISSIONS_MAX_DMGROUTE < 1 || MISSIONS_MAX_DMGROUTE > 999
	#error [ADM] Definition MISSIONS_MAX_DMGROUTE must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_FIRE
	#define MISSIONS_MAX_FIRE				100
#endif
#if MISSIONS_MAX_FIRE < 1 || MISSIONS_MAX_FIRE > 999
	#error [ADM] Definition MISSIONS_MAX_FIRE must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_PATROL
	#define MISSIONS_MAX_PATROL				100
#endif
#if MISSIONS_MAX_PATROL < 1 || MISSIONS_MAX_PATROL > 999
	#error [ADM] Definition MISSIONS_MAX_PATROL must be in the range 1 - 999
#endif

#if !defined MISSIONS_MAX_GASPIPE
	#define MISSIONS_MAX_GASPIPE			30
#endif
#if MISSIONS_MAX_GASPIPE < 1 || MISSIONS_MAX_GASPIPE > 999
	#error [ADM] Definition MISSIONS_MAX_GASPIPE must be in the range 1 - 999
#endif

#if !defined MISSIONS_ROBBER_CHANCE
	#define MISSIONS_ROBBER_CHANCE			45.0
#endif

#if !defined MISSIONS_BOMB_FAIL_CHANCE
	#define MISSIONS_BOMB_FAIL_CHANCE		40.0
#endif

#if !defined MISSIONS_GASPIPE_DOT
	#define MISSIONS_GASPIPE_DOT			5.0
#endif

#if !defined MISSIONS_DATA_FILE
	#define MISSIONS_DATA_FILE 				"route_rand.bin"
#endif

#define MISSIONS_MAX_TYPES					9
#define MISSIONS_TYPE_BOMB					1
#define MISSIONS_TYPE_WOOD					2
#define MISSIONS_TYPE_SCRAP					3
#define MISSIONS_TYPE_CORPSE				4
#define MISSIONS_TYPE_DMGROUTE				5
#define MISSIONS_TYPE_FIRE					6
#define MISSIONS_TYPE_PATROL				7
#define MISSIONS_TYPE_GASPIPE				8

#define MISSIONS_STATE_FAIL_ROBBERY			0
#define MISSIONS_STATE_ROBBED				1

#define MISSIONS_SCRAP_FULL					0
#define MISSIONS_SCRAP_LOADED				1

#define MISSIONS_BOMB_DISARM_FAIL			0
#define MISSIONS_BOMB_DISARM_SUCCESS		1
#define MISSIONS_BOMB_DISARM_TOO_LATE		2

#define MISSIONS_EXTRA_ID_ROUTE				1000
#define MISSIONS_EXTRA_ID_WOOD				2000
#define MISSIONS_EXTRA_ID_PATROL			3000
#define MISSIONS_EXTRA_ID_CORPSE			4000
#define MISSIONS_EXTRA_ID_SCRAP				5000
#define MISSIONS_EXTRA_ID_RADAR				6000
#define MISSIONS_EXTRA_ID_BOMB				7000
#define MISSIONS_EXTRA_ID_GASPIPE			8000
#define MISSIONS_EXTRA_ID_FIRE				10000

#define MISSIONS_SPAWN_TYPE_RECTANGLE		0
#define MISSIONS_SPAWN_TYPE_POLYGON			1

#define WEAPON_CONFLAGRATION				108

enum Missions::EnumBomb {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_tick
};

enum Missions::EnumWood {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_tick,
	Float:f_health,
	Float:f_maxhealth
};

enum Missions::EnumRadar {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	Float:f_speed
};

enum Missions::EnumScrap {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_tick
};

enum Missions::EnumCorpse {
	bool:f_active,
	STREAMER_TAG_ACTOR:f_actor,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_tick
};

enum Missions::EnumRoute {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_tick,
	Float:f_health,
	Float:f_maxhealth
};

enum Missions::EnumGasPipe {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_effect,
	f_tick,
	Float:f_health,
	Float:f_maxhealth
};

enum Missions::EnumFire {
	bool:f_active,
	STREAMER_TAG_OBJECT:f_object,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	Float:f_health,
	Float:f_maxhealth,
	f_tick
};

enum Missions::EnumPatrol {
	bool:f_active,
	STREAMER_TAG_PICKUP:f_pickup,
	STREAMER_TAG_AREA:f_area,
	STREAMER_TAG_3D_TEXT_LABEL:f_text,
	STREAMER_TAG_MAP_ICON:f_icon,
	f_tick
};

#if !defined Missions_ScrapSpawns
	new Float:Missions::ScrapSpawns[][4] = {
		{2080.634033,896.861389,7.863133,1.398017},
		{2142.217529,1012.950622,10.820312,268.473632},
		{2142.012451,854.660888,13.809225,177.629562},
		{1737.894409,878.754089,10.541501,42.894855},
		{1616.051879,928.601745,10.671875,270.353576},
		{1548.668334,975.843627,10.820312,89.871864},
		{1529.097412,1020.749877,10.820312,186.066009},
		{1468.166381,930.759643,10.820312,358.087768},
		{1279.567504,785.197082,10.820312,171.652709},
		{1550.258666,761.802551,10.827873,287.876922},
		{1476.586914,633.285949,10.820312,138.125579},
		{1746.376953,657.955566,11.065569,349.290832},
		{1699.011108,779.585449,11.064949,1.197629},
		{2326.351562,742.500183,10.820312,195.105972},
		{2316.649414,611.739318,10.820312,216.099487},
		{2502.742431,681.546508,10.820312,330.467224},
		{2758.089111,695.118347,10.898437,276.260009},
		{2871.515136,907.143432,10.750000,257.169921},
		{2873.082763,911.358337,10.750000,172.809921},
		{2562.311279,1302.761352,10.820312,94.235069},
		{2551.337402,1228.315429,10.820312,355.557617},
		{2572.826416,1225.074096,10.820312,176.015869},
		{2469.313232,1657.796264,10.820312,359.920867},
		{2475.866699,1658.719360,10.820312,351.774108},
		{2479.116699,1770.357299,10.820312,75.121551},
		{2579.860107,1896.906005,10.822219,0.860482},
		{2576.095214,1898.437377,10.828035,0.860482},
		{2493.687744,1900.730590,10.811492,2.137623},
		{2587.839111,2053.428466,11.183794,270.330078},
		{2605.370117,2087.168701,11.185234,176.932464},
		{2616.835693,2087.094726,11.185234,182.259155},
		{2830.566650,2011.566406,12.163568,166.568969},
		{2277.541015,2581.296875,9.816776,108.456657},
		{2238.973388,2677.651367,10.973732,48.754432},
		{1363.713500,2693.617431,10.973032,354.523895},
		{1177.196166,2662.483154,11.730304,132.078491},
		{1881.818359,1816.199462,12.743692,357.993957},
		{1686.182739,1756.782714,10.827319,112.048408},
		{1658.357543,1845.865356,10.912262,356.427337},
		{1286.340942,1929.770629,10.820312,194.119049},
		{1054.161865,1934.328247,10.820312,86.934623},
		{1032.977661,2074.180664,10.820312,86.284606},
		{972.997741,2243.142089,10.820312,23.954017},
		{1013.546508,2317.457031,10.820312,2.043826},
		{970.092407,2364.234863,10.820312,100.118064},
		{1089.208496,2355.911621,10.820312,18.000558},
		{1030.036132,2622.834716,10.964098,28.027269},
		{358.664886,2597.223876,16.484375,37.740734},
		{318.828948,2586.270019,16.501518,32.437355},
		{304.974456,2411.270996,16.557392,152.445190},
		{270.552368,2373.002929,16.484375,95.417999},
		{112.203964,2437.437744,16.476562,349.510314},
		{-170.707046,2538.458496,28.186502,245.337677},
		{-367.991210,2577.856445,39.984397,21.157234},
		{-388.628997,2491.434082,40.372352,237.985961},
		{-572.995483,2543.433593,54.009464,121.424842},
		{-795.173217,2713.355957,45.735286,108.554725},
		{-940.207702,2744.139892,46.214447,96.381469},
		{-915.980346,2704.818603,42.367187,78.352943},
		{-1362.743408,2640.995117,52.683193,0.644980},
		{-1479.026977,2536.088867,55.835937,193.155456},
		{-1598.161987,2651.458740,55.857414,200.362182},
		{-1810.958251,2044.226562,8.994381,171.535263},
		{-1453.179565,1866.784057,32.632812,160.110168},
		{-835.961303,1449.811035,14.734134,102.456306},
		{-838.282165,1596.959594,26.759700,113.276611},
		{-307.530639,1013.052856,19.593750,91.198066},
		{-302.441131,1084.234252,19.742187,282.936462},
		{-350.461334,1175.557617,19.742187,11.610636},
		{-304.460754,1164.829833,19.686088,78.374626},
		{-250.685363,1218.105590,19.742187,355.027160},
		{-89.290168,1328.355224,11.049989,276.620574},
		{-46.050922,1363.810913,10.301948,311.473419},
		{-97.549774,1745.935668,20.752950,177.847412},
		{-155.304183,2000.786865,15.371444,1.293919},
		{686.726379,2177.441650,23.360992,160.613677},
		{689.377258,1889.268920,5.593861,189.922317},
		{675.792297,1774.910522,6.566047,206.842483},
		{308.420440,1322.669433,10.865131,159.528686},
		{174.720855,1117.758300,15.659182,139.161880},
		{265.022094,964.031250,28.425598,201.829147},
		{236.336318,837.166198,14.451045,167.048767},
		{245.557647,686.738769,9.234779,174.568832},
		{66.834693,619.215637,7.925385,119.735015},
		{-104.620796,528.003601,7.057624,119.735015},
		{-105.023483,589.919494,2.857106,354.713836},
		{-160.300277,622.689697,2.967504,99.368141},
		{-427.371063,608.586975,16.718750,279.368133},
		{-775.841186,756.160217,18.890756,301.446655},
		{-912.444519,1191.589721,32.436145,348.760437},
		{-843.299743,1179.767089,34.247325,262.279663},
		{-714.877197,1217.066894,12.872953,109.539894},
		{-900.914123,813.099487,17.834108,187.078964},
		{-409.629882,703.031616,25.824981,298.626708},
		{834.528381,839.695556,11.922372,301.760009},
		{1051.519897,900.291015,12.014594,9.440628},
		{1004.860412,1073.133422,10.820312,184.908920},
		{1764.799194,926.776062,9.975251,166.085372},
		{1831.246093,1200.156982,9.613684,344.687072},
		{1746.003295,1580.371459,10.210833,74.927917},
		{1762.179565,1770.316040,9.595141,358.473876},
		{1828.291625,2020.646484,7.804986,168.760467},
		{1781.897705,2423.814941,10.354919,11.947350},
		{1658.272583,2508.865234,8.854361,311.328460},
		{2163.433105,1818.641601,10.820312,151.068710},
		{2101.687988,1239.550292,10.820312,326.850402},
		{2108.364013,1112.024780,10.820312,215.302673},
		{1916.828002,779.428100,10.820312,92.811538},
		{1777.535278,343.514038,18.946838,252.926406},
		{1825.487670,156.045333,34.431251,11.512504},
		{2307.952636,265.137268,22.987607,264.519744},
		{2336.205322,109.181320,26.484375,175.845596},
		{2352.172851,-4.981093,26.645410,182.112304},
		{2342.069824,-127.894691,26.733455,170.832199},
		{2258.186279,-82.913261,26.527740,63.044521},
		{1907.490478,14.695840,35.125000,179.292236},
		{1710.265502,129.524551,32.046745,57.404434},
		{1454.026977,39.454372,31.139526,308.218414},
		{1187.675415,201.205444,20.995294,73.384605},
		{1256.616210,392.708099,19.473384,92.643150},
		{1482.996337,412.170867,20.234375,256.976379},
		{1653.900146,352.324737,19.426700,225.016143},
		{1612.583618,178.783889,34.131130,169.555618},
		{1684.489868,-308.610351,44.913238,181.607437},
		{1680.675537,-457.519836,33.295211,177.075714},
		{1725.818969,-765.560119,53.674800,4.595676},
		{2224.372070,-1173.112426,25.726562,241.622955},
		{2364.545166,-1216.489501,27.597532,1.148928},
		{2405.724365,-1409.613037,24.082862,350.953857},
		{2406.877197,-1396.348022,24.117246,88.088096},
		{2410.935302,-1412.591186,24.095256,206.215866},
		{2410.852050,-1421.465454,23.997112,163.602127},
		{2860.047607,-1820.352416,11.049951,180.956970},
		{2856.672363,-1348.516235,11.070972,347.797149},
		{2882.118652,-1190.555419,10.875000,11.610687},
		{2916.512695,-780.594665,11.026348,352.810516},
		{2861.028808,-633.905822,11.000713,18.817426},
		{2860.630859,-393.815917,6.928040,206.964172},
		{2822.605224,-267.241119,9.850942,17.250734},
		{2880.889160,-109.102607,22.723876,303.616699},
		{2843.625976,85.993041,21.070569,23.517465},
		{2755.064208,61.388458,21.268390,88.041313},
		{2580.559082,61.609809,27.033063,90.234664},
		{2426.961425,356.293273,31.494356,0.000000},
		{1833.444213,212.201507,28.378139,148.201843},
		{1832.224487,921.963073,10.346413,339.940338}
	};
#endif

new bool:					Missions::Enabled[MISSIONS_MAX_TYPES],
	Float:					Missions::SpawnZonePolygon[MISSIONS_MAX_TYPES][TRYG3D_MAX_POLYGON_POINTS],
							Missions::SpawnZonePolygonSize[MISSIONS_MAX_TYPES],
							Missions::SpawnZoneType[MISSIONS_MAX_TYPES],
							Missions::CurrentWeather,
							Missions::VehicleWeight[MAX_VEHICLES],
	STREAMER_TAG_OBJECT:	Missions::VehicleScrap[MAX_VEHICLES][2],
							Missions::Timer[2],
							Missions::BombData[MISSIONS_MAX_BOMB][Missions::EnumBomb],
							Missions::WoodData[MISSIONS_MAX_WOOD][Missions::EnumWood],
							Missions::ScrapData[MISSIONS_MAX_SCRAP][Missions::EnumScrap],
							Missions::CorpseData[MISSIONS_MAX_CORPSE][Missions::EnumCorpse],
							Missions::RouteData[MISSIONS_MAX_DMGROUTE][Missions::EnumRoute],
							Missions::FireData[MISSIONS_MAX_FIRE][Missions::EnumFire],
							Missions::PatrolData[MISSIONS_MAX_PATROL][Missions::EnumPatrol],
							Missions::RadarData[MISSIONS_MAX_RADAR][Missions::EnumRadar],
							Missions::WoodUpperbound = -1,
							Missions::ScrapUpperbound = -1,
							Missions::CorpsesUpperbound = -1,
							Missions::RouteUpperbound = -1,
							Missions::FiresUpperbound = -1,
							Missions::PatrolUpperbound = -1,
							Missions::RadarUpperbound = -1,
							MISSIONS_SCRAP_KEY = KEY_YES,
							MISSIONS_CORPSE_KEY = KEY_YES,
							MISSIONS_BOMB_KEY = KEY_YES;

#if defined MISSIONS_EXTENDED_GRENADE
	new						Missions::GasPipeUpperbound = -1,
							Missions::GasPipeData[MISSIONS_MAX_GASPIPE][Missions::EnumGasPipe];
#endif

new Float:					Missions::SpawnZoneRectangle[MISSIONS_MAX_TYPES][4] = {
	{0.0,0.0,0.0,0.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0},
	{-3000.0,-3000.0,3000.0,3000.0}
};
	
#define Missions_Enable(%0)						(Missions::Enabled[(%0)] = (true))
#define Missions_IsEnabled(%0)					(Missions::Enabled[(%0)])
#define Missions_SetMissionsScrapKey(%0)		(MISSIONS_SCRAP_KEY = (%0))
#define Missions_SetMissionsCorpseKey(%0)		(MISSIONS_CORPSE_KEY = (%0))
#define Missions_SetMissionsBombKey(%0)			(MISSIONS_BOMB_KEY = (%0))
#define Missions_CountVehicleScrap(%0)			(Missions::VehicleWeight[(%0)])

//PartName:Forward
forward OnPlayerEnterPatrol(playerid,mobid);
forward OnPlayerDestroyPatrol(playerid,mobid);
forward OnPlayerRobbed(playerid,mobid,mission_state);
forward OnPlayerFoundCorpse(playerid,mobid);
forward OnPlayerHitCorpse(playerid,mobid);
forward OnPlayerFoundScrap(playerid,mobid);
forward OnPlayerTakeScrap(playerid,mobid,mission_state,count_items);
forward OnPlayerExceededSpeed(playerid,mobid,Float:speed,Float:max_speed);
forward OnPlayerPutOutFire(playerid,mobid);
forward OnPlayerVehicleDamagedByRoad(playerid,mobid,old_health,new_health,veh_damage);
forward OnPlayerDestroyedTreeOnRoad(playerid,mobid);
forward OnPlayerUnloadingScrap(playerid,count_items);
forward OnPlayerHealCorpse(playerid,mobid);
forward OnPlayerTryDisarmBomb(playerid,mobid);
forward OnPlayerDisarmBomb(playerid,mobid,mission_state);
forward OnPlayerFixedRoad(playerid,mobid);
forward OnPlayerFixedGasPipe(playerid,mobid);

//PartName:Main
stock Missions::Init(){
	if(!fexist(MISSIONS_DATA_FILE)){
		printf("[ADM] Error: Can't load Missions::Init() file '/scriptfiles/%s' not exist",MISSIONS_DATA_FILE);
		return 0;
	} else {
		Missions::Timer[0] = SetTimerEx("Missions_Generate",15*60*1000,true,"");
		Missions::Timer[1] = SetTimerEx("Missions_Update",500,true,"");
		printf("[ADM] Info: Load Faction Mini Missions by Abyss Morgan");
	}
	return 1;
}

stock Missions::Exit(){
	KillTimer(Missions::Timer[0]);
	KillTimer(Missions::Timer[1]);
	return 1;
}

T3D:function Missions::Update(){
	if(Missions::IsEnabled(MISSIONS_TYPE_BOMB)){
		Missions::OnBombUpdate();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_FIRE)){
		if(Missions::CurrentWeather == 8 || Missions::CurrentWeather == 16){
			for(new i = 0; i <= Missions::FiresUpperbound; i++){
				if(Missions::FireData[i][f_active]){
					Missions::FireData[i][f_health] -= 10.0;
				}
			}
		}
		Missions::OnFiresUpdate();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_WOOD)){
		Missions::OnWoodsUpdate();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_SCRAP)){
		Missions::OnScrapsUpdate();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_CORPSE)){
		Missions::OnCorpsesUpdate();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_DMGROUTE)){
		Missions::OnRoutesUpdate();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_PATROL)){
		Missions::OnPatrolsUpdate();
	}
	#if defined MISSIONS_EXTENDED_GRENADE
		if(Missions::IsEnabled(MISSIONS_TYPE_GASPIPE)){
			Missions::OnGasPipesUpdate();
		}
	#endif
}

T3D:function Missions::Generate(){
	if(Missions::IsEnabled(MISSIONS_TYPE_WOOD)){
		Missions::GenerateWood();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_SCRAP)){
		Missions::GenerateScrap();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_CORPSE)){
		Missions::GenerateCorpse();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_DMGROUTE)){
		Missions::GenerateRoute();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_FIRE)){
		Missions::GenerateFire();
	}
	if(Missions::IsEnabled(MISSIONS_TYPE_PATROL)){
		Missions::GeneratePatrol();
		if(Missions::CurrentWeather == 19){
			for(new i = 0; i <= Missions::PatrolUpperbound; i++){
				if(Missions::PatrolData[i][f_active]){
					Missions::DestroyPatrol(i);
				}
			}
		}
	}
	#if defined MISSIONS_EXTENDED_GRENADE
		if(Missions::IsEnabled(MISSIONS_TYPE_GASPIPE)){
			Missions::GenerateGasPipe();
		}
	#endif
}

stock Missions::IsValidSkin(skinid){
	if(skinid < 0 || skinid > 311) return 0;
	if(skinid == 74) return 0;
	return 1;
}

stock Missions::GetRandomSkin(){
	new rand;
	try_:
	rand = random(311)+1;
	if(!Missions::IsValidSkin(rand)) goto try_;
	return rand;
}

stock Missions::SetSpawnRectangle(mission_type,Float:minx,Float:miny,Float:maxx,Float:maxy,bool:spawn_validation=true){
	new Missions::validation_status = false;
	if(spawn_validation){
		new Float:x,Float:y,Float:z;
		switch(mission_type){
			case MISSIONS_TYPE_WOOD, MISSIONS_TYPE_DMGROUTE, MISSIONS_TYPE_PATROL, MISSIONS_TYPE_GASPIPE: {
				if(fexist(MISSIONS_DATA_FILE)){
					new File:inpf = fopen(MISSIONS_DATA_FILE,io_read);
					if(!inpf) return INVALID_ROUTE_ID;
					for(new i = 0; i < MAX_ROUTE_RANDOM; i++){
						RR_MergeFloat(x,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						RR_MergeFloat(y,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						RR_MergeFloat(z,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						if(Tryg3D::IsPointInRectangle(x,y,minx,miny,maxx,maxy)){
							Missions::validation_status = true;
							break;
						}
					}
					fclose(inpf);
				}
			}
			case MISSIONS_TYPE_SCRAP: {
				for(new i = 0, j = sizeof(Missions::ScrapSpawns); i < j; i++){
					if(Tryg3D::IsPointInRectangle(Missions::ScrapSpawns[i][0],Missions::ScrapSpawns[i][1],minx,miny,maxx,maxy)){
						Missions::validation_status = true;
						break;
					}
				}
			}
			default: Missions::validation_status = true;
		}
		#pragma unused z
	}
	if(!spawn_validation || Missions::validation_status){
		Missions::SpawnZoneType[mission_type] = MISSIONS_SPAWN_TYPE_RECTANGLE;
		Missions::SpawnZoneRectangle[mission_type][0] = minx;
		Missions::SpawnZoneRectangle[mission_type][1] = miny;
		Missions::SpawnZoneRectangle[mission_type][2] = maxx;
		Missions::SpawnZoneRectangle[mission_type][3] = maxy;
		return 1;
	}
	return 0;
}

stock Missions::SetSpawnPolygon(mission_type,Float:points[],maxpoints=sizeof(points),bool:spawn_validation=true){
	if(maxpoints > MAX_POLYGON_POINTS) return 0;
	new Missions::validation_status = false;
	if(spawn_validation){
		new Float:x,Float:y,Float:z;
		switch(mission_type){
			case MISSIONS_TYPE_WOOD, MISSIONS_TYPE_DMGROUTE, MISSIONS_TYPE_PATROL, MISSIONS_TYPE_GASPIPE: {
				if(fexist(MISSIONS_DATA_FILE)){
					new File:inpf = fopen(MISSIONS_DATA_FILE,io_read);
					if(!inpf) return INVALID_ROUTE_ID;
					for(new i = 0; i < MAX_ROUTE_RANDOM; i++){
						RR_MergeFloat(x,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						RR_MergeFloat(y,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						RR_MergeFloat(z,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						if(Tryg3D::IsPointInPolygon(x,y,points,maxpoints)){
							Missions::validation_status = true;
							break;
						}
					}
					fclose(inpf);
				}
			}
			case MISSIONS_TYPE_SCRAP: {
				for(new i = 0, j = sizeof(Missions::ScrapSpawns); i < j; i++){
					if(Tryg3D::IsPointInPolygon(Missions::ScrapSpawns[i][0],Missions::ScrapSpawns[i][1],points,maxpoints)){
						Missions::validation_status = true;
						break;
					}
				}
			}
			default: Missions::validation_status = true;
		}
	}
	if(!spawn_validation || Missions::validation_status){
		Missions::SpawnZoneType[mission_type] = MISSIONS_SPAWN_TYPE_POLYGON;
		for(new i = 0; i < maxpoints; i++){
			Missions::SpawnZonePolygon[mission_type][i] = points[i];
		}
		Missions::SpawnZonePolygonSize[mission_type] = maxpoints;
		return 1;
	}
	return 0;
}

stock Missions::DisarmBomb(playerid){
	new max_areas = GetPlayerNumberDynamicAreas(playerid);
	if(max_areas){
		new STREAMER_TAG_AREA:player_areas[128], mobid, Float:x, Float:y, Float:z;
		GetPlayerDynamicAreas(playerid,player_areas,max_areas);
		for(new k = 0; k < max_areas; k++){
			if(k >= 128) break;
			mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID) - MISSIONS_EXTRA_ID_BOMB;
			if(mobid >= 0 && mobid < MISSIONS_MAX_BOMB){
				if(player_areas[k] == Missions::BombData[mobid][f_area]){
					if(CallLocalFunction("OnPlayerTryDisarmBomb","dd",playerid,mobid)){
						GetDynamicObjectPos(Missions::BombData[mobid][f_object],x,y,z);
						if(IsPlayerInRangeOfPoint(playerid,10.0,x,y,z)){
							ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,0,0,0,0,0);
							if(Missions::BombData[mobid][f_tick] >= 1790){
								CallLocalFunction("OnPlayerDisarmBomb","ddd",playerid,mobid,MISSIONS_BOMB_DISARM_TOO_LATE);
								return 1;
							}
							if(Tryg3D::IsProbable(MISSIONS_BOMB_FAIL_CHANCE)){
								CallLocalFunction("OnPlayerDisarmBomb","ddd",playerid,mobid,MISSIONS_BOMB_DISARM_FAIL);
								Missions::BombData[mobid][f_tick] = 1794;
							} else {
								CallLocalFunction("OnPlayerDisarmBomb","ddd",playerid,mobid,MISSIONS_BOMB_DISARM_SUCCESS);
								Missions::BombData[mobid][f_active] = false;
								Missions::BombData[mobid][f_tick] = 0;
								if(IsValidDynamicObject(Missions::BombData[mobid][f_object])){
									DestroyDynamicObject(Missions::BombData[mobid][f_object]);
									Missions::BombData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
								}
								if(IsValidDynamicMapIcon(Missions::BombData[mobid][f_icon])){
									DestroyDynamicMapIcon(Missions::BombData[mobid][f_icon]);
									Missions::BombData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
								}
								if(IsValidDynamic3DTextLabel(Missions::BombData[mobid][f_text])){
									DestroyDynamic3DTextLabel(Missions::BombData[mobid][f_text]);
									Missions::BombData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
								}
								if(IsValidDynamicArea(Missions::BombData[mobid][f_area])){
									DestroyDynamicArea(Missions::BombData[mobid][f_area]);
									Missions::BombData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
								}
							} 		
							return 1;
						} 
					}
					return 1;
				}
			}
			mobid = -1;
		}
	}
	return 1;
}

stock Missions::DropScrap(vehicleid){
	if(Missions::VehicleWeight[vehicleid] > 0){
		if(IsValidDynamicObject(Missions::VehicleScrap[vehicleid][0])){
			DestroyDynamicObject(Missions::VehicleScrap[vehicleid][0]);
			Missions::VehicleScrap[vehicleid][0] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		}
		if(Missions::VehicleWeight[vehicleid] > 1){
			if(IsValidDynamicObject(Missions::VehicleScrap[vehicleid][1])){
				DestroyDynamicObject(Missions::VehicleScrap[vehicleid][1]);
				Missions::VehicleScrap[vehicleid][1] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
			}
		}
		Missions::VehicleWeight[vehicleid] = 0;
	}
	return 1;
}

stock Missions::HealCorpse(playerid){
	if(IsPlayerInAnyVehicle(playerid)) return 1;
	new max_areas = GetPlayerNumberDynamicAreas(playerid);
	if(max_areas){
		new STREAMER_TAG_AREA:player_areas[128], mobid, Float:x, Float:y, Float:z;
		GetPlayerDynamicAreas(playerid,player_areas,max_areas);
		for(new k = 0; k < max_areas; k++){
			if(k >= 128) break;
			mobid = Streamer::GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID) - MISSIONS_EXTRA_ID_CORPSE;
			if(mobid >= 0 && mobid < MISSIONS_MAX_CORPSE){
				if(player_areas[k] == Missions::CorpseData[mobid][f_area]){
					GetDynamicActorPos(Missions::CorpseData[mobid][f_actor],x,y,z);
					if(IsPlayerInRangeOfPoint(playerid,3.0,x,y,z)){
						if(CallLocalFunction("OnPlayerHealCorpse","dd",playerid,mobid)){
							ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,0,0,0,0,0);
							Missions::DestroyCorpse(mobid);
						}
					}
					return 1;
				}
			}
			mobid = -1;
		}
	}
	return 1;
}

//PartName:Bomb
stock Missions::OnBombUpdate(){
	for(new mobid = 0; mobid < MISSIONS_MAX_BOMB; mobid++){
		Missions::BombData[mobid][f_tick]++;
		if(Missions::BombData[mobid][f_tick] == 600){
			new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:rz, mission_type = MISSIONS_TYPE_BOMB;
			switch(Missions::SpawnZoneType[mission_type]){
				case MISSIONS_SPAWN_TYPE_RECTANGLE: {
					Tryg3D::GetPointInRectangle(Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3],x,y);
					while(Tryg3D::IsPointInWater(x,y,0.0)){
						Tryg3D::GetPointInRectangle(Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3],x,y);
					}
				}
				case MISSIONS_SPAWN_TYPE_POLYGON: {
					Tryg3D::GetPointInPolygon(Missions::SpawnZonePolygon[mission_type],x,y,Missions::SpawnZonePolygonSize[mission_type]);
					while(Tryg3D::IsPointInWater(x,y,0.0)){
						Tryg3D::GetPointInPolygon(Missions::SpawnZonePolygon[mission_type],x,y,Missions::SpawnZonePolygonSize[mission_type]);
					}
				}
			}
			ColAndreas::FindZ_For2DCoord(x,y,z);
			Tryg3D::GetPointInWallForPoint(x,y,z+1.5,5000.0,tx,ty,tz);
			Tryg3D::GetRotationFor2Point2D(tx,ty,x,y,rz);
			Missions::BombData[mobid][f_text] = CreateDynamic3DTextLabel("EMP Explosive",0xFF0000FF,tx,ty,tz,35.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0);
			Missions::BombData[mobid][f_object] = CreateDynamicObject(363,tx,ty,tz,0.0,0.0,Tryg3D::CompressRotation(rz+180.0));
			Missions::BombData[mobid][f_icon] = CreateDynamicMapIcon(tx,ty,tz,37,1,0,0,-1,300.0);
			Missions::BombData[mobid][f_area] = CreateDynamicSphere(tx,ty,tz,25.0,0,0,-1);
			Missions::BombData[mobid][f_active] = true;
			Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::BombData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_BOMB);
		} else if(Missions::BombData[mobid][f_tick] >= 1800){
			if(Missions::BombData[mobid][f_active]){
				new Float:tx,Float:ty,Float:tz;
				GetDynamicObjectPos(Missions::BombData[mobid][f_object],tx,ty,tz);
				Tryg3D::CastExplosion(tx,ty,tz,7,25.0,0,0,-1,200.0);
				Tryg3D::CastExplosion(tx-2.5,ty-2.5,tz,7,25.0,0,0,-1,200.0);
				Tryg3D::CastExplosion(tx-2.5,ty+2.5,tz,7,25.0,0,0,-1,200.0);
				Tryg3D::CastExplosion(tx+2.5,ty-2.5,tz,7,25.0,0,0,-1,200.0);
				Tryg3D::CastExplosion(tx+2.5,ty+2.5,tz,7,25.0,0,0,-1,200.0);
				if(IsValidDynamicObject(Missions::BombData[mobid][f_object])){
					DestroyDynamicObject(Missions::BombData[mobid][f_object]);
					Missions::BombData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
				}
				if(IsValidDynamicMapIcon(Missions::BombData[mobid][f_icon])){
					DestroyDynamicMapIcon(Missions::BombData[mobid][f_icon]);
					Missions::BombData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
				}
				if(IsValidDynamic3DTextLabel(Missions::BombData[mobid][f_text])){
					DestroyDynamic3DTextLabel(Missions::BombData[mobid][f_text]);
					Missions::BombData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
				}
				if(IsValidDynamicArea(Missions::BombData[mobid][f_area])){
					DestroyDynamicArea(Missions::BombData[mobid][f_area]);
					Missions::BombData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
				}
				Tryg3D::Foreach(i){
					if(IsPlayerInRangeOfPoint(i,150.0,tx,ty,tz)){
						if(IsPlayerInAnyVehicle(i)){
							new engine,lights, alarm, bonnet, boot, doors, objective, vehid = GetPlayerVehicleID(i);
							GetVehicleParamsEx(vehid,engine,lights,alarm,doors,bonnet,boot,objective);
							SetVehicleParamsEx(vehid,0,0,alarm,doors,bonnet,boot,objective);
						}
					}
					
				}
				Missions::BombData[mobid][f_active] = false;
			}
			Missions::BombData[mobid][f_tick] = 0;
		}
	}
}

//PartName:Wood
stock Missions::GetWoodID(){
	if(Missions::WoodUpperbound >= MISSIONS_MAX_WOOD) return -1;
	for(new i = 0; i < MISSIONS_MAX_WOOD; i++){
		if(!Missions::WoodData[i][f_active]){
			if(i > Missions::WoodUpperbound) Missions::WoodUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreateWood(Float:x,Float:y,Float:z,worldid=0,interiorid=0,Float:health=100.0,Float:max_health=250.0,Float:force_angle=270.0){
	new mobid = Missions::GetWoodID();
	if(mobid == -1) return 0;
	
	Missions::WoodData[mobid][f_active] = true;
	Missions::WoodData[mobid][f_health] = health;
	Missions::WoodData[mobid][f_maxhealth] = max_health;
	
	new Float:rx,Float:ry;
	Tryg3D::GetGroundRotation(x,y,0.25,rx,ry);
	Missions::WoodData[mobid][f_object] = CreateDynamicObject(846,x,y,z+0.5,rx,ry,force_angle,worldid,interiorid,-1,100.0);
	Missions::WoodData[mobid][f_area] = CreateDynamicSphere(x,y,z,20.0,worldid,interiorid);
	Missions::WoodData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,7,1,0,0,-1,100.0);
	Missions::WoodData[mobid][f_tick] = gettime()+2*60*60;
	
	new buffer[64];
	format(buffer,sizeof(buffer),"Tree %.1f HP",Tryg3D::NMTVF(Missions::WoodData[mobid][f_health],Missions::WoodData[mobid][f_maxhealth]));
	Missions::WoodData[mobid][f_text] = CreateDynamic3DTextLabel(buffer,0xCC0000FF,x,y,z+1.0,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,worldid,interiorid);
	
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::WoodData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_WOOD);
	return 1;
}

stock Missions::DestroyWood(mobid){
	if(!Missions::WoodData[mobid][f_active]) return 0;
	if(IsValidDynamicObject(Missions::WoodData[mobid][f_object])){
		DestroyDynamicObject(Missions::WoodData[mobid][f_object]);
		Missions::WoodData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::WoodData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::WoodData[mobid][f_text]);
		Missions::WoodData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::WoodData[mobid][f_area])){
		DestroyDynamicArea(Missions::WoodData[mobid][f_area]);
		Missions::WoodData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicMapIcon(Missions::WoodData[mobid][f_icon])){
		DestroyDynamicMapIcon(Missions::WoodData[mobid][f_icon]);
		Missions::WoodData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}
	Missions::WoodData[mobid][f_active] = false;
	if(Missions::WoodUpperbound == mobid) Missions::WoodUpperbound--;
	return 1;
}

stock Missions::CreateRandomWood(){
	new RandomPos[Vectors3D], mission_type = MISSIONS_TYPE_WOOD;
	switch(Missions::SpawnZoneType[mission_type]){
		case MISSIONS_SPAWN_TYPE_RECTANGLE: {
			GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			while(!Tryg3D::IsPointInRectangle(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3])){
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			}
		}
		case MISSIONS_SPAWN_TYPE_POLYGON: {
			GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			while(!Tryg3D::IsPointInPolygon(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygon[mission_type],Missions::SpawnZonePolygonSize[mission_type])){
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			}
		}
	}
	Missions::CreateWood(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
}

stock Missions::OnWoodsUpdate(){
	new buffer[64], c_time = gettime();
	for(new i = 0; i <= Missions::WoodUpperbound; i++){
		if(Missions::WoodData[i][f_active]){
			if(c_time > Missions::WoodData[i][f_tick]){
				Missions::DestroyWood(i);
			} else {
				if(Missions::WoodData[i][f_health] < Missions::WoodData[i][f_maxhealth] && Missions::WoodData[i][f_health] > 5.0){
					Missions::WoodData[i][f_health] += 0.05;
				}
				format(buffer,sizeof(buffer),"Tree %.1f HP",Tryg3D::NMTVF(Missions::WoodData[i][f_health],Missions::WoodData[i][f_maxhealth]));
				UpdateDynamic3DTextLabelText(Missions::WoodData[i][f_text],0xCC0000FF,buffer);
			}
		}
	}
}

stock Missions::GenerateWood(){
	new p_cnt = 0;
	for(new i = 0; i <= Missions::WoodUpperbound; i++){
		if(Missions::WoodData[i][f_active]){
			p_cnt++;
		}
	}
	if(p_cnt < MISSIONS_MAX_WOOD){
		for(new i = 0; i < 5; i++){
			Missions::CreateRandomWood();
		}
	}
}


//PartName:Scrap
stock Missions::GetScrapID(){
	for(new i = 0; i < MISSIONS_MAX_SCRAP; i++){
		if(!Missions::ScrapData[i][f_active]){
			if(i > Missions::ScrapUpperbound) Missions::ScrapUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreateScrap(Float:x,Float:y,Float:z,Float:rz,worldid=0,interiorid=0){
	new mobid = Missions::GetScrapID();
	if(mobid == -1) return 0;
	
	Missions::ScrapData[mobid][f_active] = true;
	
	Missions::ScrapData[mobid][f_object] = CreateDynamicObject(12957,x,y,z,0.0,0.0,rz,worldid,interiorid,-1,100.0);
	Missions::ScrapData[mobid][f_area] = CreateDynamicSphere(x,y,z,10.0,worldid,interiorid);
	Missions::ScrapData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,47,1,0,0,-1,100.0);
	Missions::ScrapData[mobid][f_tick] = gettime()+2*60*60;
	
	Missions::ScrapData[mobid][f_text] = CreateDynamic3DTextLabel("Scrap",0xCC0000FF,x,y,z,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,worldid,interiorid);
	
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::ScrapData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_SCRAP);
	return 1;
}

stock Missions::DestroyScrap(mobid){
	if(!Missions::ScrapData[mobid][f_active]) return 0;
	if(IsValidDynamicObject(Missions::ScrapData[mobid][f_object])){
		DestroyDynamicObject(Missions::ScrapData[mobid][f_object]);
		Missions::ScrapData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::ScrapData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::ScrapData[mobid][f_text]);
		Missions::ScrapData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::ScrapData[mobid][f_area])){
		DestroyDynamicArea(Missions::ScrapData[mobid][f_area]);
		Missions::ScrapData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicMapIcon(Missions::ScrapData[mobid][f_icon])){
		DestroyDynamicMapIcon(Missions::ScrapData[mobid][f_icon]);
		Missions::ScrapData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}
	Missions::ScrapData[mobid][f_active] = false;
	if(Missions::ScrapUpperbound == mobid) Missions::ScrapUpperbound--;
	return 1;
}

stock Missions::CreateRandomScrap(){
	new rand, mission_type = MISSIONS_TYPE_SCRAP;
	switch(Missions::SpawnZoneType[mission_type]){
		case MISSIONS_SPAWN_TYPE_RECTANGLE: {
			rand = random(sizeof(Missions::ScrapSpawns));
			while(!Tryg3D::IsPointInRectangle(Missions::ScrapSpawns[rand][0],Missions::ScrapSpawns[rand][1],Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3])){
				rand = random(sizeof(Missions::ScrapSpawns));
			}
		}
		case MISSIONS_SPAWN_TYPE_POLYGON: {
			rand = random(sizeof(Missions::ScrapSpawns));
			while(!Tryg3D::IsPointInPolygon(Missions::ScrapSpawns[rand][0],Missions::ScrapSpawns[rand][1],Missions::SpawnZonePolygon[mission_type],Missions::SpawnZonePolygonSize[mission_type])){
				rand = random(sizeof(Missions::ScrapSpawns));
			}
		}
	}
	
	Missions::CreateScrap(Missions::ScrapSpawns[rand][0],Missions::ScrapSpawns[rand][1],Missions::ScrapSpawns[rand][2],Missions::ScrapSpawns[rand][3]);
}

stock Missions::OnScrapsUpdate(){
	new c_time = gettime();
	for(new i = 0; i <= Missions::ScrapUpperbound; i++){
		if(Missions::ScrapData[i][f_active]){
			if(c_time > Missions::ScrapData[i][f_tick]){
				Missions::DestroyScrap(i);
			}
		}
	}
}

stock Missions::GenerateScrap(){
	new p_cnt = 0;
	for(new i = 0; i <= Missions::ScrapUpperbound; i++){
		if(Missions::ScrapData[i][f_active]){
			p_cnt++;
		}
	}
	if(p_cnt < MISSIONS_MAX_SCRAP){
		for(new i = 0; i < 20; i++){
			Missions::CreateRandomScrap();
		}
	}
}


//PartName:Corpse
stock Missions::GetCorpseID(){
	if(Missions::CorpsesUpperbound >= MISSIONS_MAX_CORPSE) return -1;
	for(new i = 0; i < MISSIONS_MAX_CORPSE; i++){
		if(!Missions::CorpseData[i][f_active]){
			if(i > Missions::CorpsesUpperbound) Missions::CorpsesUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreateCorpse(Float:x,Float:y,Float:z,worldid=0,interiorid=0){
	if(Missions::CurrentWeather == 8 || Missions::CurrentWeather == 16) return 0;
	new mobid = Missions::GetCorpseID();
	if(mobid == -1) return 0;
	
	Missions::CorpseData[mobid][f_active] = true;
	Missions::CorpseData[mobid][f_actor] = CreateDynamicActor(Missions::GetRandomSkin(),x,y,z+1.0,random(360)*1.0,1,100.0,worldid,interiorid,-1,100);
	ApplyDynamicActorAnimation(Missions::CorpseData[mobid][f_actor],"PED","FLOOR_HIT",4.1,1,0,0,0,0);
	Missions::CorpseData[mobid][f_area] = CreateDynamicSphere(x,y,z,3.0,worldid,interiorid);
	Missions::CorpseData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,22,1,0,0,-1,100.0);
	Missions::CorpseData[mobid][f_tick] = gettime()+2*60*60;
	
	Missions::CorpseData[mobid][f_text] = CreateDynamic3DTextLabel("Injured Man",0xCC0000FF,x,y,z,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1,worldid,interiorid);
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::CorpseData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_CORPSE);
	return 1;
}

stock Missions::DestroyCorpse(mobid){
	if(!Missions::CorpseData[mobid][f_active]) return 0;
	if(IsValidDynamicActor(Missions::CorpseData[mobid][f_actor])){
		DestroyDynamicActor(Missions::CorpseData[mobid][f_actor]);
		Missions::CorpseData[mobid][f_actor] = STREAMER_TAG_ACTOR:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::CorpseData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::CorpseData[mobid][f_text]);
		Missions::CorpseData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::CorpseData[mobid][f_area])){
		DestroyDynamicArea(Missions::CorpseData[mobid][f_area]);
		Missions::CorpseData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicMapIcon(Missions::CorpseData[mobid][f_icon])){
		DestroyDynamicMapIcon(Missions::CorpseData[mobid][f_icon]);
		Missions::CorpseData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}
	Missions::CorpseData[mobid][f_active] = false;
	if(mobid == Missions::CorpsesUpperbound) Missions::CorpsesUpperbound--;
	return 1;
}

stock Missions::CreateRandomCorpse(){
	new RandomPos[Vectors3D], Float:tx, Float:ty, Float:tz, mission_type = MISSIONS_TYPE_CORPSE;
	switch(Missions::SpawnZoneType[mission_type]){
		case MISSIONS_SPAWN_TYPE_RECTANGLE: {
			Tryg3D::GetPointInRectangle(Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3],RandomPos[T3D:X],RandomPos[T3D:Y]);
			while(Tryg3D::IsPointInWater(RandomPos[T3D:X],RandomPos[T3D:Y],0.0)){
				Tryg3D::GetPointInRectangle(Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3],RandomPos[T3D:X],RandomPos[T3D:Y]);
			}
		}
		case MISSIONS_SPAWN_TYPE_POLYGON: {
			Tryg3D::GetPointInPolygon(Missions::SpawnZonePolygon[mission_type],RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygonSize[mission_type]);
			while(Tryg3D::IsPointInWater(RandomPos[T3D:X],RandomPos[T3D:Y],0.0)){
				Tryg3D::GetPointInPolygon(Missions::SpawnZonePolygon[mission_type],RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygonSize[mission_type]);
			}
		}
	}
	ColAndreas::FindZ_For2DCoord(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
	
	Missions::CreateCorpse(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]+1.0);
	
	new rand = random(3);
	for(new i = 1; i <= rand; i++){
		Tryg3D::GetPointInCircle(RandomPos[T3D:X],RandomPos[T3D:Y],10.0,tx,ty);
		while(Tryg3D::IsPointInWater(tx,ty,0.0)){
			Tryg3D::GetPointInCircle(RandomPos[T3D:X],RandomPos[T3D:Y],10.0,tx,ty);
		}
		ColAndreas::FindZ_For2DCoord(tx,ty,tz);
		Missions::CreateCorpse(tx,ty,tz+1.0);
	}
}

stock Missions::OnCorpsesUpdate(){
	new c_time = gettime();
	for(new i = 0; i <= Missions::CorpsesUpperbound; i++){
		if(Missions::CorpseData[i][f_active]){
			if(c_time > Missions::CorpseData[i][f_tick]){
				Missions::DestroyCorpse(i);
			}
		}
	}
}

stock Missions::GenerateCorpse(){
	if(Missions::CurrentWeather == 8 || Missions::CurrentWeather == 16) return 0;
	new p_cnt = 0;
	for(new i = 0; i <= Missions::CorpsesUpperbound; i++){
		if(Missions::CorpseData[i][f_active]){
			p_cnt++;
		}
	}
	if(p_cnt < MISSIONS_MAX_CORPSE){
		for(new i = 0; i < 5; i++){
			Missions::CreateRandomCorpse();
		}
	}
	return 1;
}

//PartName:Route
stock Missions::GetRouteID(){
	for(new i = 0; i < MISSIONS_MAX_DMGROUTE; i++){
		if(!Missions::RouteData[i][f_active]){
			if(i > Missions::RouteUpperbound) Missions::RouteUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreateRoute(Float:x,Float:y,Float:z,worldid=0,interiorid=0,Float:health=100.0,Float:max_health=250.0){
	new mobid = Missions::GetRouteID();
	if(mobid == -1) return 0;
	
	Missions::RouteData[mobid][f_active] = true;
	Missions::RouteData[mobid][f_health] = health;
	Missions::RouteData[mobid][f_maxhealth] = max_health;
	
	new Float:rx,Float:ry;
	Tryg3D::GetGroundRotation(x,y,0.25,rx,ry);
	Missions::RouteData[mobid][f_object] = CreateDynamicObject(18782,x,y,z,rx,ry,0.0,worldid,interiorid,-1,100.0);
	SetDynamicObjectMaterial(Missions::RouteData[mobid][f_object],0,5794,"roads_lawn","greyground256");
	Missions::RouteData[mobid][f_area] = CreateDynamicSphere(x,y,z,20.0,worldid,interiorid);
	Missions::RouteData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,11,1,0,0,-1,100.0);
	Missions::RouteData[mobid][f_tick] = gettime()+2*60*60;
	
	new buffer[64];
	format(buffer,sizeof(buffer),"Damaged route %.1f HP",Tryg3D::NMTVF(Missions::RouteData[mobid][f_health],Missions::RouteData[mobid][f_maxhealth]));
	Missions::RouteData[mobid][f_text] = CreateDynamic3DTextLabel(buffer,0xCC0000FF,x,y,z,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,worldid,interiorid);
	
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::RouteData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_ROUTE);
	return 1;
}

stock Missions::DestroyRoute(mobid){
	if(!Missions::RouteData[mobid][f_active]) return 0;
	if(IsValidDynamicObject(Missions::RouteData[mobid][f_object])){
		DestroyDynamicObject(Missions::RouteData[mobid][f_object]);
		Missions::RouteData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::RouteData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::RouteData[mobid][f_text]);
		Missions::RouteData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::RouteData[mobid][f_area])){
		DestroyDynamicArea(Missions::RouteData[mobid][f_area]);
		Missions::RouteData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicMapIcon(Missions::RouteData[mobid][f_icon])){
		DestroyDynamicMapIcon(Missions::RouteData[mobid][f_icon]);
		Missions::RouteData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}
	Missions::RouteData[mobid][f_active] = false;
	if(Missions::RouteUpperbound == mobid) Missions::RouteUpperbound--;
	return 1;
}

stock Missions::CreateRandomRoute(){
	new RandomPos[Vectors3D], mission_type = MISSIONS_TYPE_DMGROUTE;
	switch(Missions::SpawnZoneType[mission_type]){
		case MISSIONS_SPAWN_TYPE_RECTANGLE: {
			GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			while(!Tryg3D::IsPointInRectangle(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3])){
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			}
		}
		case MISSIONS_SPAWN_TYPE_POLYGON: {
			GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			while(!Tryg3D::IsPointInPolygon(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygon[mission_type],Missions::SpawnZonePolygonSize[mission_type])){
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			}
		}
	}
	Missions::CreateRoute(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
}

stock Missions::OnRoutesUpdate(){
	new buffer[64], c_time = gettime();
	for(new i = 0; i <= Missions::RouteUpperbound; i++){
		if(Missions::RouteData[i][f_active]){
			if(c_time > Missions::RouteData[i][f_tick]){
				Missions::DestroyRoute(i);
			} else {
				if(Missions::RouteData[i][f_health] < Missions::RouteData[i][f_maxhealth] && Missions::RouteData[i][f_health] > 5.0){
					Missions::RouteData[i][f_health] += 0.05;
				}
				format(buffer,sizeof(buffer),"Damaged route %.1f HP",Tryg3D::NMTVF(Missions::RouteData[i][f_health],Missions::RouteData[i][f_maxhealth]));
				UpdateDynamic3DTextLabelText(Missions::RouteData[i][f_text],0xCC0000FF,buffer);
			}
		}
	}
}

stock Missions::GenerateRoute(){
	new p_cnt = 0;
	for(new i = 0; i <= Missions::RouteUpperbound; i++){
		if(Missions::RouteData[i][f_active]){
			p_cnt++;
		}
	}
	if(p_cnt < MISSIONS_MAX_DMGROUTE){
		for(new i = 0; i < 20; i++){
			Missions::CreateRandomRoute();
		}
	}
}

#if defined MISSIONS_EXTENDED_GRENADE

	//PartName:GasPipe
	stock Missions::GetGasPipeID(){
		for(new i = 0; i < MISSIONS_MAX_GASPIPE; i++){
			if(!Missions::GasPipeData[i][f_active]){
				if(i > Missions::GasPipeUpperbound) Missions::GasPipeUpperbound = i;
				return i;
			}
		}
		return -1;
	}

	stock Missions::CreateGasPipe(Float:x,Float:y,Float:z,worldid=0,interiorid=0,Float:health=100.0,Float:max_health=250.0){
		new mobid = Missions::GetGasPipeID();
		if(mobid == -1) return 0;
		
		Missions::GasPipeData[mobid][f_active] = true;
		Missions::GasPipeData[mobid][f_health] = health;
		Missions::GasPipeData[mobid][f_maxhealth] = max_health;
		
		new Float:rx,Float:ry;
		Tryg3D::GetGroundRotation(x,y,0.25,rx,ry);
		Missions::GasPipeData[mobid][f_object] = CreateDynamicObject(2983,x,y,z-0.2,Tryg3D::CompressRotation(rx+270.0),0.0,0.0,worldid,interiorid,-1,100.0);
		Missions::GasPipeData[mobid][f_area] = CreateDynamicSphere(x,y,z,20.0,worldid,interiorid);
		Missions::GasPipeData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,11,1,0,0,-1,100.0);
		Missions::GasPipeData[mobid][f_tick] = gettime()+2*60*60;
		Missions::GasPipeData[mobid][f_effect] = Grenade::CreateGrenadeEffect(GRENADE_SPECIAL_WEAPON_TEARGAS,GRENADE_EFFECT_SMALL_SMOKE,x,y,z,worldid,interiorid,-1,100.0,MISSIONS_GASPIPE_DOT,0.0,7200,INVALID_PLAYER_ID);
		
		new buffer[64];
		format(buffer,sizeof(buffer),"Damaged gas pipe %.1f HP",Tryg3D::NMTVF(Missions::GasPipeData[mobid][f_health],Missions::GasPipeData[mobid][f_maxhealth]));
		Missions::GasPipeData[mobid][f_text] = CreateDynamic3DTextLabel(buffer,0xCC0000FF,x,y,z,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,worldid,interiorid);
		
		Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::GasPipeData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_GASPIPE);
		return 1;
	}

	stock Missions::DestroyGasPipe(mobid){
		if(!Missions::GasPipeData[mobid][f_active]) return 0;
		if(IsValidDynamicObject(Missions::GasPipeData[mobid][f_object])){
			DestroyDynamicObject(Missions::GasPipeData[mobid][f_object]);
			Missions::GasPipeData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		}
		if(IsValidDynamic3DTextLabel(Missions::GasPipeData[mobid][f_text])){
			DestroyDynamic3DTextLabel(Missions::GasPipeData[mobid][f_text]);
			Missions::GasPipeData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
		}
		if(IsValidDynamicArea(Missions::GasPipeData[mobid][f_area])){
			DestroyDynamicArea(Missions::GasPipeData[mobid][f_area]);
			Missions::GasPipeData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
		}
		if(IsValidDynamicMapIcon(Missions::GasPipeData[mobid][f_icon])){
			DestroyDynamicMapIcon(Missions::GasPipeData[mobid][f_icon]);
			Missions::GasPipeData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
		}
		if(Missions::GasPipeData[mobid][f_effect] != INVALID_GRENADE_ID){
			Grenade::DestroyEffect(Missions::GasPipeData[mobid][f_effect]);
			Missions::GasPipeData[mobid][f_effect] = INVALID_GRENADE_ID;
		}
		Missions::GasPipeData[mobid][f_active] = false;
		if(Missions::GasPipeUpperbound == mobid) Missions::GasPipeUpperbound--;
		return 1;
	}

	stock Missions::CreateRandomGasPipe(){
		new RandomPos[Vectors3D], mission_type = MISSIONS_TYPE_GASPIPE;
		switch(Missions::SpawnZoneType[mission_type]){
			case MISSIONS_SPAWN_TYPE_RECTANGLE: {
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
				while(!Tryg3D::IsPointInRectangle(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3])){
					GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
				}
			}
			case MISSIONS_SPAWN_TYPE_POLYGON: {
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
				while(!Tryg3D::IsPointInPolygon(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygon[mission_type],Missions::SpawnZonePolygonSize[mission_type])){
					GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
				}
			}
		}
		Missions::CreateGasPipe(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
	}

	stock Missions::OnGasPipesUpdate(){
		new buffer[64], c_time = gettime();
		for(new i = 0; i <= Missions::GasPipeUpperbound; i++){
			if(Missions::GasPipeData[i][f_active]){
				if(c_time > Missions::GasPipeData[i][f_tick]){
					Missions::DestroyGasPipe(i);
				} else {
					if(Missions::GasPipeData[i][f_health] < Missions::GasPipeData[i][f_maxhealth] && Missions::GasPipeData[i][f_health] > 5.0){
						Missions::GasPipeData[i][f_health] += 0.05;
					}
					format(buffer,sizeof(buffer),"Damaged gas pipe %.1f HP",Tryg3D::NMTVF(Missions::GasPipeData[i][f_health],Missions::GasPipeData[i][f_maxhealth]));
					UpdateDynamic3DTextLabelText(Missions::GasPipeData[i][f_text],0xCC0000FF,buffer);
				}
			}
		}
	}

	stock Missions::GenerateGasPipe(){
		new p_cnt = 0;
		for(new i = 0; i <= Missions::GasPipeUpperbound; i++){
			if(Missions::GasPipeData[i][f_active]){
				p_cnt++;
			}
		}
		if(p_cnt < MISSIONS_MAX_GASPIPE){
			for(new i = 0; i < 20; i++){
				Missions::CreateRandomGasPipe();
			}
		}
	}
#endif

//PartName:Fire
stock Missions::GetFireID(){
	if(Missions::FiresUpperbound >= MISSIONS_MAX_FIRE) return -1;
	for(new i = 0; i < MISSIONS_MAX_FIRE; i++){
		if(!Missions::FireData[i][f_active]){
			if(i > Missions::FiresUpperbound) Missions::FiresUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreateFire(Float:x,Float:y,Float:z,bool:explode=true,worldid=0,interiorid=0,Float:health=100.0,Float:max_health=250.0){
	if(Missions::CurrentWeather == 8 || Missions::CurrentWeather == 16) return 0;
	if(interiorid == -1) interiorid = 0;
	if(worldid == -1) worldid = 0;
	if(interiorid > 0 || worldid > 0) return 0;
	new mobid = Missions::GetFireID();
	if(mobid == -1) return 0;
	
	Missions::FireData[mobid][f_active] = true;
	Missions::FireData[mobid][f_health] = health;
	Missions::FireData[mobid][f_maxhealth] = max_health;
	Missions::FireData[mobid][f_object] = CreateDynamicObject(18691,x,y,z-1.0,0.0,0.0,0.0,worldid,interiorid,-1,100.0);
	Missions::FireData[mobid][f_area] = CreateDynamicSphere(x,y,z,20.0,worldid,interiorid);
	Missions::FireData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,20,1,0,0,-1,100.0);
	Missions::FireData[mobid][f_tick] = gettime()+2*60*60;
	
	new buffer[64];
	format(buffer,sizeof(buffer),"Fire %.1f HP",Tryg3D::NMTVF(Missions::FireData[mobid][f_health],Missions::FireData[mobid][f_maxhealth]));
	Missions::FireData[mobid][f_text] = CreateDynamic3DTextLabel(buffer,0xCC0000FF,x,y,z+0.5,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1,worldid,interiorid);
	
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::FireData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_FIRE);
	
	if(explode){
		Tryg3D::CastExplosion(x,y,z,8,5.0,worldid,interiorid,-1,200.0);
	}
	return 1;
}

stock Missions::DestroyFire(mobid){
	if(!Missions::FireData[mobid][f_active]) return 0;
	if(IsValidDynamicObject(Missions::FireData[mobid][f_object])){
		DestroyDynamicObject(Missions::FireData[mobid][f_object]);
		Missions::FireData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::FireData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::FireData[mobid][f_text]);
		Missions::FireData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::FireData[mobid][f_area])){
		DestroyDynamicArea(Missions::FireData[mobid][f_area]);
		Missions::FireData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicMapIcon(Missions::FireData[mobid][f_icon])){
		DestroyDynamicMapIcon(Missions::FireData[mobid][f_icon]);
		Missions::FireData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}
	Missions::FireData[mobid][f_active] = false;
	if(mobid == Missions::FiresUpperbound) Missions::FiresUpperbound--;
	return 1;
}

stock Missions::CreateRandomFire(){
	new RandomPos[Vectors3D], Float:tx, Float:ty, Float:tz, mission_type = MISSIONS_TYPE_FIRE;
	switch(Missions::SpawnZoneType[mission_type]){
		case MISSIONS_SPAWN_TYPE_RECTANGLE: {
			Tryg3D::GetPointInRectangle(Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3],RandomPos[T3D:X],RandomPos[T3D:Y]);
			while(Tryg3D::IsPointInWater(RandomPos[T3D:X],RandomPos[T3D:Y],0.0)){
				Tryg3D::GetPointInRectangle(Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3],RandomPos[T3D:X],RandomPos[T3D:Y]);
			}
		}
		case MISSIONS_SPAWN_TYPE_POLYGON: {
			Tryg3D::GetPointInPolygon(Missions::SpawnZonePolygon[mission_type],RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygonSize[mission_type]);
			while(Tryg3D::IsPointInWater(RandomPos[T3D:X],RandomPos[T3D:Y],0.0)){
				Tryg3D::GetPointInPolygon(Missions::SpawnZonePolygon[mission_type],RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygonSize[mission_type]);
			}
		}
	}
	ColAndreas::FindZ_For2DCoord(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
	
	Missions::CreateFire(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]+0.2);
	
	new rand = random(6);
	for(new i = 1; i <= rand; i++){
		Tryg3D::GetPointInCircle(RandomPos[T3D:X],RandomPos[T3D:Y],10.0,tx,ty);
		while(Tryg3D::IsPointInWater(tx,ty,0.0)){
			Tryg3D::GetPointInCircle(RandomPos[T3D:X],RandomPos[T3D:Y],10.0,tx,ty);
		}
		ColAndreas::FindZ_For2DCoord(tx,ty,tz);
		Missions::CreateFire(tx,ty,tz+0.2);
	}
}

stock Missions::OnFiresUpdate(){
	new buffer[64], c_time = gettime();
	for(new i = 0; i <= Missions::FiresUpperbound; i++){
		if(Missions::FireData[i][f_active]){
			if(c_time > Missions::FireData[i][f_tick] || (Missions::FireData[i][f_health] < 0.0 && (Missions::CurrentWeather == 8 || Missions::CurrentWeather == 16))){
				Missions::DestroyFire(i);
			} else {
				if(Missions::FireData[i][f_health] < Missions::FireData[i][f_maxhealth] && Missions::FireData[i][f_health] > 5.0){
					Missions::FireData[i][f_health] += 0.05;
				}
				format(buffer,sizeof(buffer),"Fire %.1f HP",Tryg3D::NMTVF(Missions::FireData[i][f_health],Missions::FireData[i][f_maxhealth]));
				UpdateDynamic3DTextLabelText(Missions::FireData[i][f_text],0xCC0000FF,buffer);
			}
		}
	}
}

stock Missions::GenerateFire(){
	if(Missions::CurrentWeather == 8 || Missions::CurrentWeather == 16) return 0;
	new p_cnt = 0;
	for(new i = 0; i <= Missions::FiresUpperbound; i++){
		if(Missions::FireData[i][f_active]){
			p_cnt++;
		}
	}
	if(p_cnt < 85){
		for(new i = 0; i < 5; i++){
			Missions::CreateRandomFire();
		}
	}
	return 1;
}


//PartName:Patrol
stock Missions::GetPatrolID(){
	if(Missions::PatrolUpperbound >= MISSIONS_MAX_PATROL) return -1;
	for(new i = 0; i < MISSIONS_MAX_PATROL; i++){
		if(!Missions::PatrolData[i][f_active]){
			if(i > Missions::PatrolUpperbound) Missions::PatrolUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreatePatrol(Float:x,Float:y,Float:z,worldid=0,interiorid=0){
	if(Missions::CurrentWeather == 19) return 0;
	new mobid = Missions::GetPatrolID();
	if(mobid == -1) return 0;
	
	Missions::PatrolData[mobid][f_active] = true;
	
	Missions::PatrolData[mobid][f_pickup] = CreateDynamicPickup(18646,1,x,y,z+2.5,worldid,interiorid,-1,100.0);
	Missions::PatrolData[mobid][f_area] = CreateDynamicSphere(x,y,z,8.0,worldid,interiorid);
	Missions::PatrolData[mobid][f_icon] = CreateDynamicMapIcon(x,y,z,30,1,0,0,-1,100.0);
	Missions::PatrolData[mobid][f_tick] = gettime()+2*60*60;
	
	Missions::PatrolData[mobid][f_text] = CreateDynamic3DTextLabel("Unsafe sector",0xCC0000FF,x,y,z,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1,worldid,interiorid);
	
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::PatrolData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_PATROL);
	return 1;
}

stock Missions::DestroyPatrol(mobid){
	if(!Missions::PatrolData[mobid][f_active]) return 0;
	if(IsValidDynamicPickup(Missions::PatrolData[mobid][f_pickup])){
		DestroyDynamicPickup(Missions::PatrolData[mobid][f_pickup]);
		Missions::PatrolData[mobid][f_pickup] = STREAMER_TAG_PICKUP:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::PatrolData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::PatrolData[mobid][f_text]);
		Missions::PatrolData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::PatrolData[mobid][f_area])){
		DestroyDynamicArea(Missions::PatrolData[mobid][f_area]);
		Missions::PatrolData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicMapIcon(Missions::PatrolData[mobid][f_icon])){
		DestroyDynamicMapIcon(Missions::PatrolData[mobid][f_icon]);
		Missions::PatrolData[mobid][f_icon] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}
	Missions::PatrolData[mobid][f_active] = false;
	if(Missions::PatrolUpperbound == mobid) Missions::PatrolUpperbound--;
	return 1;
}

stock Missions::CreateRandomPatrol(){
	new RandomPos[Vectors3D], mission_type = MISSIONS_TYPE_PATROL;
	switch(Missions::SpawnZoneType[mission_type]){
		case MISSIONS_SPAWN_TYPE_RECTANGLE: {
			GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			while(!Tryg3D::IsPointInRectangle(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZoneRectangle[mission_type][0],Missions::SpawnZoneRectangle[mission_type][1],Missions::SpawnZoneRectangle[mission_type][2],Missions::SpawnZoneRectangle[mission_type][3])){
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			}
		}
		case MISSIONS_SPAWN_TYPE_POLYGON: {
			GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			while(!Tryg3D::IsPointInPolygon(RandomPos[T3D:X],RandomPos[T3D:Y],Missions::SpawnZonePolygon[mission_type],Missions::SpawnZonePolygonSize[mission_type])){
				GetRandomRoutePoint(MISSIONS_DATA_FILE,RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
			}
		}
	}
	Missions::CreatePatrol(RandomPos[T3D:X],RandomPos[T3D:Y],RandomPos[T3D:Z]);
}

stock Missions::OnPatrolsUpdate(){
	new c_time = gettime();
	for(new i = 0; i <= Missions::PatrolUpperbound; i++){
		if(Missions::PatrolData[i][f_active]){
			if(c_time > Missions::PatrolData[i][f_tick]){
				Missions::DestroyPatrol(i);
			}
		}
	}
}

stock Missions::GeneratePatrol(){
	if(Missions::CurrentWeather == 19) return 0;
	new p_cnt = 0;
	for(new i = 0; i <= Missions::PatrolUpperbound; i++){
		if(Missions::PatrolData[i][f_active]){
			p_cnt++;
		}
	}
	if(p_cnt < MISSIONS_MAX_PATROL){
		for(new i = 0; i < 5; i++){
			Missions::CreateRandomPatrol();
		}
	}
	return 1;
}

//PartName:Radar
stock Missions::GetRadarID(){
	if(Missions::RadarUpperbound >= MISSIONS_MAX_RADAR) return -1;
	for(new i = 0; i < MISSIONS_MAX_RADAR; i++){
		if(!Missions::RadarData[i][f_active]){
			if(i > Missions::RadarUpperbound) Missions::RadarUpperbound = i;
			return i;
		}
	}
	return -1;
}

stock Missions::CreateRadar(Float:x,Float:y,Float:z,Float:rz,worldid=0,interiorid=0,Float:speed=80.0){
	new mobid = Missions::GetRadarID();
	if(mobid == -1) return 0;
	
	Missions::RadarData[mobid][f_active] = true;
	
	Missions::RadarData[mobid][f_object] = CreateDynamicObject(18880,x,y,z-1.0,0.0,0.0,Tryg3D::CompressRotation(rz+180.0),worldid,interiorid,-1,100.0);
	Missions::RadarData[mobid][f_area] = CreateDynamicCircle(x,y,20.0,worldid,interiorid);
	Missions::RadarData[mobid][f_speed] = speed;
	
	new buffer[100];
	format(buffer,sizeof(buffer),"(%d) Speed camera [%.0f KM/H]",mobid,speed);
	Missions::RadarData[mobid][f_text] = CreateDynamic3DTextLabel(buffer,0x33FF33FF,x,y,z+5.0,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,worldid,interiorid);
	
	Streamer::SetIntData(STREAMER_TYPE_AREA,Missions::RadarData[mobid][f_area],E_STREAMER_EXTRA_ID,mobid+MISSIONS_EXTRA_ID_RADAR);
	return 1;
}

stock Missions::DestroyRadar(mobid){
	if(!Missions::RadarData[mobid][f_active]) return 0;
	if(IsValidDynamicObject(Missions::RadarData[mobid][f_object])){
		DestroyDynamicObject(Missions::RadarData[mobid][f_object]);
		Missions::RadarData[mobid][f_object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	if(IsValidDynamic3DTextLabel(Missions::RadarData[mobid][f_text])){
		DestroyDynamic3DTextLabel(Missions::RadarData[mobid][f_text]);
		Missions::RadarData[mobid][f_text] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}
	if(IsValidDynamicArea(Missions::RadarData[mobid][f_area])){
		DestroyDynamicArea(Missions::RadarData[mobid][f_area]);
		Missions::RadarData[mobid][f_area] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}
	Missions::RadarData[mobid][f_active] = false;
	if(Missions::RadarUpperbound == mobid) Missions::RadarUpperbound--;
	return 1;
}

//PartName:Hooks
//Hook: SetWeather
stock Missions::SetWeather(weatherid){
	Missions::CurrentWeather = weatherid;
	return SetWeather(weatherid);
}

#if defined _ALS_SetWeather
	#undef SetWeather
#else
	#define _ALS_SetWeather
#endif
#define SetWeather Missions_SetWeather

//Hook: OnPlayerEnterDynamicArea
public OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid){
	
	for(new mobid = 0; mobid < MISSIONS_MAX_BOMB; mobid++){
		if(Missions::BombData[mobid][f_area] == areaid){
			if(Missions::BombData[mobid][f_active]){
				if(Missions::BombData[mobid][f_tick] < 1740 && Missions::BombData[mobid][f_tick] > 600){
					Missions::BombData[mobid][f_tick] = 1740;
				}
			}
			break;
		}
	}
	new mobid, extra_id = Streamer::GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_EXTRA_ID);

	mobid = extra_id - MISSIONS_EXTRA_ID_PATROL;
	if(mobid >= 0 && mobid < MISSIONS_MAX_PATROL){
		if(areaid == Missions::PatrolData[mobid][f_area]){
			if(CallLocalFunction("OnPlayerEnterPatrol","dd",playerid,mobid)){
				CallLocalFunction("OnPlayerDestroyPatrol","dd",playerid,mobid);
				Missions::DestroyPatrol(mobid);
			} else {
				if(Tryg3D::IsProbable(MISSIONS_ROBBER_CHANCE)){
					CallLocalFunction("OnPlayerRobbed","ddd",playerid,mobid,MISSIONS_STATE_ROBBED);
				} else {
					CallLocalFunction("OnPlayerRobbed","ddd",playerid,mobid,MISSIONS_STATE_FAIL_ROBBERY);
				}
			}
		}
	}
	
	mobid = extra_id - MISSIONS_EXTRA_ID_CORPSE;
	if(mobid >= 0 && mobid < MISSIONS_MAX_CORPSE){
		if(areaid == Missions::CorpseData[mobid][f_area]){
			if(GetPlayerVehicleSeat(playerid) == 0){
				if(!CallLocalFunction("OnPlayerFoundCorpse","dd",playerid,mobid)){
					if(IsPlayerInAnyVehicle(playerid)){
						CallLocalFunction("OnPlayerHitCorpse","dd",playerid,mobid);
					}
				}
			}
		}
	}
	
	if(IsPlayerInAnyVehicle(playerid)){
		if(GetPlayerVehicleSeat(playerid) == 0){
			new vehicleid = GetPlayerVehicleID(playerid);
			
			mobid = extra_id - MISSIONS_EXTRA_ID_SCRAP;
			if(mobid >= 0 && mobid < MISSIONS_MAX_SCRAP){
				if(areaid == Missions::ScrapData[mobid][f_area]){
					if(GetVehicleModel(vehicleid) == 578){
						if(GetPlayerVehicleSeat(playerid) == 0){
							if(CallLocalFunction("OnPlayerFoundScrap","dd",playerid,mobid)){
								if(Missions::VehicleWeight[vehicleid] < 2){
									Missions::VehicleWeight[vehicleid]++;
									CallLocalFunction("OnPlayerTakeScrap","dddd",playerid,mobid,MISSIONS_SCRAP_LOADED,Missions::VehicleWeight[vehicleid]);
									Missions::DestroyScrap(mobid);
									switch(Missions::VehicleWeight[vehicleid]){
										case 1: {
											if(IsValidDynamicObject(Missions::VehicleScrap[vehicleid][0])){
												DestroyDynamicObject(Missions::VehicleScrap[vehicleid][0]);
												Missions::VehicleScrap[vehicleid][0] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
											}
											Missions::VehicleScrap[vehicleid][0] = CreateDynamicObject(12957,0.0,0.0,-900.0,0.0,0.0,0.0);
											AttachDynamicObjectToVehicle(Missions::VehicleScrap[vehicleid][0],vehicleid,0.2,-1.0,0.5,0.0,0.0,180.0);
										}
										case 2: {
											if(IsValidDynamicObject(Missions::VehicleScrap[vehicleid][1])){
												DestroyDynamicObject(Missions::VehicleScrap[vehicleid][1]);
												Missions::VehicleScrap[vehicleid][1] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
											}
											Missions::VehicleScrap[vehicleid][1] = CreateDynamicObject(12957,0.0,0.0,-900.0,0.0,0.0,0.0);
											AttachDynamicObjectToVehicle(Missions::VehicleScrap[vehicleid][1],vehicleid,-0.2,-2.9,1.25,20.0,0.0,0.0);
										}
									}
								} else {
									CallLocalFunction("OnPlayerTakeScrap","dd",playerid,mobid,MISSIONS_SCRAP_FULL);
								}
							}
						}
					}
				}
			}
			
			mobid = extra_id - MISSIONS_EXTRA_ID_RADAR;
			if(mobid >= 0 && mobid < MISSIONS_MAX_RADAR){
				if(areaid == Missions::RadarData[mobid][f_area]){
					new Float:vspeed = Tryg3D::GetVehicleSpeed(vehicleid);
					if(vspeed > Missions::RadarData[mobid][f_speed]){
						if(Tryg3D::IsVehicleFlag(Tryg3D::GetVehicleFlags(vehicleid),VF_STREET)){
							CallLocalFunction("OnPlayerExceededSpeed","ddff",playerid,mobid,vspeed,Missions::RadarData[mobid][f_speed]);
						}
					}
				}
			}
		}
	}
	
	#if defined MISQ1_OnPlayerEnterDynamicArea
		MISQ1_OnPlayerEnterDynamicArea(playerid,areaid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea MISQ1_OnPlayerEnterDynamicArea
#if defined MISQ1_OnPlayerEnterDynamicArea
	forward MISQ1_OnPlayerEnterDynamicArea(playerid,STREAMER_TAG_AREA:areaid);
#endif

//Hook: OnPlayerUpdate
public OnPlayerUpdate(playerid){
	
	new max_areas = GetPlayerNumberDynamicAreas(playerid), extra_id;
	if(max_areas){
		new keys, updown, leftright, STREAMER_TAG_AREA:player_areas[128], mobid, Float:p_health, Float:x, Float:y, Float:z, modelid, vid;
		GetPlayerKeys(playerid,keys,updown,leftright);
		GetPlayerDynamicAreas(playerid,player_areas,max_areas);
		modelid = GetVehicleModel(GetPlayerVehicleID(playerid));
		for(new k = 0; k < max_areas; k++){
			if(k >= 128) break;
			extra_id = Streamer::GetIntData(STREAMER_TYPE_AREA,player_areas[k],E_STREAMER_EXTRA_ID);
			
			mobid = extra_id - MISSIONS_EXTRA_ID_FIRE;
			if(mobid >= 0 && mobid < MISSIONS_MAX_FIRE){
				if(player_areas[k] == Missions::FireData[mobid][f_area]){
					GetDynamicObjectPos(Missions::FireData[mobid][f_object],x,y,z);
					if(Tryg3D::IsPlayerAimingAt(playerid,x,y,z,20.0)){
						if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,20.0,x,y,z) && (modelid == 407 || modelid == 601)){
							Missions::FireData[mobid][f_health] -= 3.0;
							if(Missions::FireData[mobid][f_health] <= 0.0){
								CallLocalFunction("OnPlayerPutOutFire","dd",playerid,mobid);
								Missions::DestroyFire(mobid);
							}
						} else if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,5.0,x,y,z) && GetPlayerWeapon(playerid) == 42){
							Missions::FireData[mobid][f_health] -= 1.0;
							if(Missions::FireData[mobid][f_health] <= 0.0){
								CallLocalFunction("OnPlayerPutOutFire","dd",playerid,mobid);
								Missions::DestroyFire(mobid);
							}
						}
					}
					GetPlayerHealth(playerid,p_health);
					if(IsPlayerInRangeOfPoint(playerid,3.0,x,y,z)){
						if(p_health > 0.0){
							Tryg3D::GivePlayerDamage(playerid,0.1,INVALID_PLAYER_ID,WEAPON_CONFLAGRATION,3);
						}
					}
				}
			}
			
			mobid = extra_id - MISSIONS_EXTRA_ID_ROUTE;
			if(mobid >= 0 && mobid < MISSIONS_MAX_DMGROUTE){
				if(player_areas[k] == Missions::RouteData[mobid][f_area]){
					GetDynamicObjectPos(Missions::RouteData[mobid][f_object],x,y,z);
					vid = GetPlayerVehicleID(playerid);
					GetVehicleHealth(vid,p_health);
					if(Tryg3D::IsPlayerAimingAt(playerid,x,y,z,10.0)){
						if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,10.0,x,y,z) && (modelid == 486)){
							Missions::RouteData[mobid][f_health] -= 3.0;
							if(Missions::RouteData[mobid][f_health] <= 0.0){
								CallLocalFunction("OnPlayerFixedRoad","dd",playerid,mobid);
								Missions::DestroyRoute(mobid);
							}
						} else if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,5.0,x,y,z) && GetPlayerWeapon(playerid) == 6){
							ApplyAnimation(playerid,"DILDO","DILDO_G",4.1,0,0,0,0,0,0);
							Missions::RouteData[mobid][f_health] -= 1.0;
							if(Missions::RouteData[mobid][f_health] <= 0.0){
								CallLocalFunction("OnPlayerFixedRoad","dd",playerid,mobid);
								Missions::DestroyRoute(mobid);
							}
						}
					}
					if(vid != 0 && modelid != 486 && IsPlayerInRangeOfPoint(playerid,5.0,x,y,z) && GetPlayerVehicleSeat(playerid) == 0){
						if(p_health > 350.0){
							new Float:veh_damage = Tryg3D::GetVehicleSpeed(vid)*0.2;
							SetVehicleHealth(vid,p_health-veh_damage);
							CallLocalFunction("OnPlayerVehicleDamagedByRoad","ddfff",playerid,mobid,p_health,p_health-veh_damage,veh_damage);
						}
					}
				}
			}
			
			#if defined MISSIONS_EXTENDED_GRENADE
				mobid = extra_id - MISSIONS_EXTRA_ID_GASPIPE;
				if(mobid >= 0 && mobid < MISSIONS_MAX_GASPIPE){
					if(player_areas[k] == Missions::GasPipeData[mobid][f_area]){
						GetDynamicObjectPos(Missions::GasPipeData[mobid][f_object],x,y,z);
						if(Tryg3D::IsPlayerAimingAt(playerid,x,y,z,10.0)){
							if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,5.0,x,y,z)){
								ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,0,0,0,0,0);
								Missions::GasPipeData[mobid][f_health] -= 5.0;
								if(Missions::GasPipeData[mobid][f_health] <= 0.0){
									CallLocalFunction("OnPlayerFixedGasPipe","dd",playerid,mobid);
									Missions::DestroyGasPipe(mobid);
								}
							}
						}
					}
			}
			#endif
			
			mobid = extra_id - MISSIONS_EXTRA_ID_WOOD;
			if(mobid >= 0 && mobid < MISSIONS_MAX_WOOD){
				if(player_areas[k] == Missions::WoodData[mobid][f_area]){
					GetDynamicObjectPos(Missions::WoodData[mobid][f_object],x,y,z);
					if(Tryg3D::IsPlayerAimingAt(playerid,x,y,z,10.0)){
						if((keys & KEY_FIRE) && IsPlayerInRangeOfPoint(playerid,3.0,x,y,z) && GetPlayerWeapon(playerid) == 9){
							Missions::WoodData[mobid][f_health] -= 1.0;
							if(Missions::WoodData[mobid][f_health] <= 0.0){
								CallLocalFunction("OnPlayerDestroyedTreeOnRoad","dd",playerid,mobid);
								Missions::DestroyWood(mobid);
							}
						}
					}
				}
			}
			
			mobid = -1;
		}
	}
	
	#if defined Missions_OnPlayerUpdate
		Missions_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate Missions_OnPlayerUpdate
#if defined Missions_OnPlayerUpdate
	forward Missions_OnPlayerUpdate(playerid);
#endif

//Hook: OnVehicleSpawn
public OnVehicleSpawn(vehicleid){
	Missions::DropScrap(vehicleid);
	#if defined MISQ1_OnVehicleSpawn
		MISQ1_OnVehicleSpawn(vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn MISQ1_OnVehicleSpawn
#if defined MISQ1_OnVehicleSpawn
	forward MISQ1_OnVehicleSpawn(vehicleid);
#endif

//Hook: OnPlayerKeyStateChange
public OnPlayerKeyStateChange(playerid,newkeys,oldkeys){
	if(Tryg3D::KeyPressed(MISSIONS_SCRAP_KEY)){
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0){
			new vid = GetPlayerVehicleID(playerid);
			if(GetVehicleModel(vid) == 578){
				if(CallLocalFunction("OnPlayerUnloadingScrap","dd",playerid,Missions::VehicleWeight[vid])){
					Missions::DropScrap(vid);
				}
			}
		}
	}
	if(Tryg3D::KeyPressed(MISSIONS_CORPSE_KEY)){
		Missions::HealCorpse(playerid);
	}
	if(Tryg3D::KeyPressed(MISSIONS_BOMB_KEY)){
		Missions::DisarmBomb(playerid);
	}
	#if defined MISQ1_OnPlayerKeyStateChange
		MISQ1_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange MISQ1_OnPlayerKeyStateChange
#if defined MISQ1_OnPlayerKeyStateChange
	forward MISQ1_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif
 
//Hook: DestroyVehicle
stock MISQ1_DestroyVehicle(vehicleid){
	Missions::DropScrap(vehicleid);
	return DestroyVehicle(vehicleid);
}
 
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle MISQ1_DestroyVehicle

new bool:CRC_MissionsInit = true,
	bool:CRC_MissionsExit = true;
	
//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_MissionsInit){
		CRC_MissionsInit = false;
		Missions::Init();
	}
	#if defined Missions_OnFilterScriptInit
		Missions::OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Missions_OnFilterScriptInit
#if defined Missions_OnFilterScriptInit
	forward Missions_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_MissionsInit){
		CRC_MissionsInit = false;
		Missions::Init();
	}
	#if defined Missions_OnGameModeInit
		Missions::OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Missions_OnGameModeInit
#if defined Missions_OnGameModeInit
	forward Missions_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_MissionsExit){
		CRC_MissionsExit = false;
		Missions::Exit();
	}
	#if defined Missions_OnFilterScriptExit
		Missions::OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit Missions_OnFilterScriptExit
#if defined Missions_OnFilterScriptExit
	forward Missions_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_MissionsExit){
		CRC_MissionsExit = false;
		Missions::Exit();
	}
	#if defined Missions_OnGameModeExit
		Missions::OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit Missions_OnGameModeExit
#if defined Missions_OnGameModeExit
	forward Missions_OnGameModeExit();
#endif
//EOF