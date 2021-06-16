/*
 hashtag.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: None

 Website: https://adm.ct8.pl

 Plugins: SScanf
 Modules: RGB

 File Version: 1.2.0

 Functions:
 GetHashTag(playerid,text[],hashtag_color=0xCC0000FF,back_color=0xFFFFFFFF,max_len=sizeof(text));
 HashTag::name(playerid);

 Callbacks:
 OnHashTagPresented(hashtag[]);
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

#if defined _text_hashtag
	#endinput
#endif
#define _text_hashtag

#define HashTag::%1(%2)					forward ht_%1(%2); public ht_%1(%2)
#define HashTagAlias::%1(%2)			ht_%1(%2)

forward OnHashTagPresented(hashtag[]);

stock GetHashTag(playerid,text[],hashtag_color=0xCC0000FF,back_color=0xFFFFFFFF,max_len=sizeof(text)){
	while(strfind(text,"##") != -1){
		strreplace(text,"##","#",.maxlength=max_len);
	}
	new len = strlen(text), pos = 0, hashtag_start, hashtag_stop;
	while(hashtag_stop != -1 && pos < len && pos != -1 && (hashtag_start = strfind(text,"#",false,pos)) != -1){
		new hashtag_zone[28];
		
		hashtag_stop = strfind(text," ",false,hashtag_start);
		if(hashtag_stop == -1){
			strmid(hashtag_zone,text,hashtag_start+1,len);
		} else {
			strmid(hashtag_zone,text,hashtag_start+1,hashtag_stop);
		}
		pos += strlen(hashtag_zone) + 1;
		if(strlen(hashtag_zone) >= 2 && strlen(hashtag_zone) <= 28){
			for(new k = 0, l = strlen(hashtag_zone); k < l; k++) hashtag_zone[k] = tolower(hashtag_zone[k]);
			new hash_call[32];
			format(hash_call,sizeof(hash_call),"ht_%s",hashtag_zone);
			CallRemoteFunction(hash_call,"i",playerid);
			CallLocalFunction("OnHashTagPresented","s",hashtag_zone);
			
			if(hashtag_stop != -1){
				strins(text,RGB::GetColorRGBA(back_color),hashtag_stop,max_len);
				pos += 4;
			}
			strins(text,RGB::GetColorRGBA(hashtag_color),hashtag_start,max_len);
			pos += 4;
			len = strlen(text);
		}
	}
}

//EOF