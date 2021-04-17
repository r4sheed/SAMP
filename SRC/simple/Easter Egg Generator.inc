/*
Random Easter Egg Generator (Decoration)

#include <a_samp>
#include <streamer>
#include <colandreas> //OR mapandreas
#include <ADM/3DTryg> //http://forum.sa-mp.com/showthread.php?t=591010
*/

#define MAX_EASTER_EGG		10000

stock EasterEggCreate(){
	new Float:piox, Float:pioy, Float:pioz;
	GetRandomPointInRectangle(-3000.0,-3000.0,3000.0,3000.0,piox,pioy);
	while(IsPointInWater(piox,pioy,0.0)){
		GetRandomPointInRectangle(-3000.0,-3000.0,3000.0,3000.0,piox,pioy);
	}
	CA_FindZ_For2DCoord(piox,pioy,pioz);
	new tmpobj = CreateDynamicObject(19341,piox,pioy,pioz+0.55,0.0,0.0,0.0,0,0,-1,50.0);
	switch(random(14)){
		case 1: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","ws_gayflag1");
		case 2: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","Smileyface2");
		case 3: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","orang006");
		case 4: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","brown013");
		case 5: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","red032");
		case 6: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","yello007");
		case 7: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","wood051");
		case 8: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","waterclear256");
		case 9: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","tubelite");
		case 10: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","marb002");
		case 11: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","grey002");
		case 12: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","metal013");
		case 13: SetDynamicObjectMaterial(tmpobj,0,18841,"MickyTextures","brick008");
	}
}

public OnFilterScriptInit(){
	
	for(new i = 0; i < MAX_EASTER_EGG; i++){
		EasterEggCreate();
	}
	
	return 1;
}
