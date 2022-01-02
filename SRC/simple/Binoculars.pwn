#include <a_samp>
#include <izcmd>
#include <colandreas>

#define TRYG3D_ENABLE_PLAYER
#define TRYG3D_ENABLE_COLANDREAS
#define TRYG3D_ENABLE_UNIVERSAL

#include <3DTryg/3DTryg>

stock GetPlayerNick(playerid){
	new pnick[MAX_PLAYER_NAME];
	GetPlayerName(playerid,pnick,sizeof(pnick));
	return pnick;
}

CMD:binoculars(playerid){
	new szLIST[3096], buffer[128], cnt = 0;
	Tryg3D::Foreach(i){
		if(playerid == i) continue;
		if(Tryg3D::IsPlayerSpawned(i)){
			if(Tryg3D::ItemOnPlayerScreen(playerid,i,item_player)){
				format(buffer,sizeof(buffer),"{FFFFFF}%d. {00FF00}%s\n",i,GetPlayerNick(i));
				strcat(szLIST,buffer);
				cnt++;
			}
		}
	}
	if(cnt == 0) szLIST = "{FFFFFF}I do not see anyone nearby\n";
	ShowPlayerDialog(playerid,0,DIALOG_STYLE_LIST,"Binoculars",szLIST,"{00FF00}Exit","");
	return 1;
}