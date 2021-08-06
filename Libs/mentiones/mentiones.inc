/*
 mentiones.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: None

 Website: https://adm.ct8.pl

 Plugins: SScanf
 Modules: RGB, DataConvert

 File Version: 1.3.1

 Functions:
 GetMentiones(playerid,text[],mention_color=0xCC0000FF,back_color=0xFFFFFFFF,max_len=sizeof(text));
 GetAllowedMentions();
 SetAllowedMentions(number);

 Callbacks:
 OnPlayerMentioned(playerid,targetid);
*/

#if !defined sscanf
	#error [ADM] This include required SScanf v2.8.2
#endif

#if !defined _rgb_function
	#error [ADM] This include required RGB.inc
#endif

//Check Version DataConvert.inc
#if !defined _Data_Convert
	#error [ADM] This include required DataConvert.inc v2.3.0
#elseif !defined Data_Convert_Version
	#error [ADM] Update your DataConvert.inc to v2.3.0
#elseif (Data_Convert_Version < 20300)
	#error [ADM] Update your DataConvert.inc to v2.3.0
#endif

#if defined _text_mentiones
	#endinput
#endif
#define _text_mentiones

new _adm_max_allowed_mentions = 0;

#define GetAllowedMentions()		_adm_max_allowed_mentions
#define SetAllowedMentions(%0)		_adm_max_allowed_mentions = (%0)

forward OnPlayerMentioned(playerid,targetid);

stock GetMentiones(playerid,text[],mention_color=0xCC0000FF,back_color=0xFFFFFFFF,max_len=sizeof(text)){
	while(strfind(text,"@@") != -1){
		strreplace(text,"@@","@",.maxlength=max_len);
	}
	new len = strlen(text), pos = 0, mentiones_start, mentiones_stop, p_name[MAX_PLAYER_NAME], o_name[48], n_name[48], used_tags = 0;
	while((mentiones_stop != -1 && pos < len && pos != -1 && (mentiones_start = strfind(text,"@",false,pos)) != -1) && (GetAllowedMentions() == 0 || (used_tags < GetAllowedMentions()))){
		p_name = "";
		mentiones_stop = strfind(text," ",false,mentiones_start);
		if(mentiones_stop == -1){
			strmid(p_name,text,mentiones_start+1,len);
		} else {
			strmid(p_name,text,mentiones_start+1,mentiones_stop);
		}
		if(strlen(p_name) > 0 && strlen(p_name) <= MAX_PLAYER_NAME){
			new targetid = INVALID_PLAYER_ID;
			sscanf(p_name,"u",targetid);
			if(IsPlayerConnected(targetid)){
				format(o_name,sizeof(o_name),"@%s",p_name);
				GetPlayerName(targetid,p_name,MAX_PLAYER_NAME);
				if(mentiones_stop != -1){
					format(n_name,sizeof(n_name),"%s@%s%s",RGB::GetColorRGBA(mention_color),p_name,RGB::GetColorRGBA(back_color));
				} else {
					format(n_name,sizeof(n_name),"%s@%s",RGB::GetColorRGBA(mention_color),p_name);
				}
				strreplace(text,o_name,n_name,true,pos,1,max_len);
				CallRemoteFunction("OnPlayerMentioned","ii",playerid,targetid);
				pos += strlen(n_name);
				len = strlen(text);
				used_tags++;
			}
		}
		pos++;
	}
}

//EOF