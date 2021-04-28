/*
 SOI.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: None
 Modules: None

 File Version: 1.0.0

 Notice:
 Required directory /scriptfiles/SOI

 Options:
 DISABLE_SOI_CACHE - Disable Cache Functions

 Functions:
 SOI::GetSkinOffset(modelid,skinid,&bone,&Float:x,&Float:y,&Float:z,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:sx=0.0,&Float:sy=0.0,&Float:sz=0.0);

 Cache Functions:
 SOI::GetDefaultSkinOffset(&bone,&Float:x,&Float:y,&Float:z,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:sx=0.0,&Float:sy=0.0,&Float:sz=0.0);
 SOI::SetDefaultSkinOffset(bone,Float:x,Float:y,Float:z,Float:rx=0.0,Float:ry=0.0,Float:rz=0.0,Float:sx=1.0,Float:sy=1.0,Float:sz=1.0);
 SOI::GetTempSkinOffset(skinid,&bone,&Float:x,&Float:y,&Float:z,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:sx=1.0,&Float:sy=1.0,&Float:sz=1.0);
 SOI::SetTempSkinOffset(skinid,bone,Float:x,Float:y,Float:z,Float:rx=0.0,Float:ry=0.0,Float:rz=0.0,Float:sx=1.0,Float:sy=1.0,Float:sz=1.0);
 SOI::LoadTempData(modelid);
 SOI::DumpTempData();
*/

#if defined _SOI_FILES
	#endinput
#endif
#define _SOI_FILES

#define SOI_FILES_VERSION 					(10000)			//a.b[c] 10000*a+100*b+c

#define SOI_HEADER_KEY						"SOI 1.0 ADM"	//You can never change !!!

#define MAX_SKINS							(312)
#define SOI_FILE_SIZE 						(11555)

#define SOI_Function::						stock
#define SOI_Public::%0(%1)					forward %0(%1); public %0(%1)

#define SOI::								SOI_

//BitFunctions.inc
#define SOI_ExtractValue(%0,%1,%2,%3,%4)	((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define SOI_ExtractFloat(%0,%1,%2,%3,%4)	((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define SOI_MergeValue(%0,%1,%2,%3,%4)		((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define SOI_MergeFloat(%0,%1,%2,%3,%4)		((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#if !defined DISABLE_SOI_CACHE
	enum SOI::SkinsTemp {
		bool:SOI::set,
		SOI::bone,
		Float:SOI::x,
		Float:SOI::y,
		Float:SOI::z,
		Float:SOI::rx,
		Float:SOI::ry,
		Float:SOI::rz,
		Float:SOI::sx,
		Float:SOI::sy,
		Float:SOI::sz
	};
	
	enum SOI::TempFile {
		bool:SOI::active,
		SOI::modelid
	};

	static SOI::TempSkinsData[MAX_SKINS][SOI::SkinsTemp],
		SOI::DefaultValues[SOI::SkinsTemp],
		SOI::TempFileData[SOI::TempFile];
	
	stock SOI::GetDefaultSkinOffset(&bone,&Float:x,&Float:y,&Float:z,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:sx=0.0,&Float:sy=0.0,&Float:sz=0.0){
		if(!SOI::TempFileData[SOI::active]) return 0;
		bone = SOI::DefaultValues[SOI::bone];
		x = SOI::DefaultValues[SOI::x];
		y = SOI::DefaultValues[SOI::y];
		z = SOI::DefaultValues[SOI::z];
		rx = SOI::DefaultValues[SOI::rx];
		ry = SOI::DefaultValues[SOI::ry];
		rz = SOI::DefaultValues[SOI::rz];
		sx = SOI::DefaultValues[SOI::sx];
		sy = SOI::DefaultValues[SOI::sy];
		sz = SOI::DefaultValues[SOI::sz];
		return 1;
	}
	
	stock SOI::SetDefaultSkinOffset(bone,Float:x,Float:y,Float:z,Float:rx=0.0,Float:ry=0.0,Float:rz=0.0,Float:sx=1.0,Float:sy=1.0,Float:sz=1.0){
		if(!SOI::TempFileData[SOI::active]) return 0;
		SOI::DefaultValues[SOI::bone] = bone;
		SOI::DefaultValues[SOI::x] = x;
		SOI::DefaultValues[SOI::y] = y;
		SOI::DefaultValues[SOI::z] = z;
		SOI::DefaultValues[SOI::rx] = rx;
		SOI::DefaultValues[SOI::ry] = ry;
		SOI::DefaultValues[SOI::rz] = rz;
		SOI::DefaultValues[SOI::sx] = sx;
		SOI::DefaultValues[SOI::sy] = sy;
		SOI::DefaultValues[SOI::sz] = sz;
		return 1;
	}
	
	stock SOI::GetTempSkinOffset(skinid,&bone,&Float:x,&Float:y,&Float:z,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:sx=1.0,&Float:sy=1.0,&Float:sz=1.0){
		if(!SOI::TempFileData[SOI::active]) return 0;
		if(skinid < 0 || skinid >= MAX_SKINS) return 0;
		bone = SOI::TempSkinsData[skinid][SOI::bone];
		x = SOI::TempSkinsData[skinid][SOI::x];
		y = SOI::TempSkinsData[skinid][SOI::y];
		z = SOI::TempSkinsData[skinid][SOI::z];
		rx = SOI::TempSkinsData[skinid][SOI::rx];
		ry = SOI::TempSkinsData[skinid][SOI::ry];
		rz = SOI::TempSkinsData[skinid][SOI::rz];
		sx = SOI::TempSkinsData[skinid][SOI::sx];
		sy = SOI::TempSkinsData[skinid][SOI::sy];
		sz = SOI::TempSkinsData[skinid][SOI::sz];
		return 1;
	}
	
	stock SOI::SetTempSkinOffset(skinid,bone,Float:x,Float:y,Float:z,Float:rx=0.0,Float:ry=0.0,Float:rz=0.0,Float:sx=1.0,Float:sy=1.0,Float:sz=1.0){
		if(!SOI::TempFileData[SOI::active]) return 0;
		if(skinid < 0 || skinid >= MAX_SKINS) return 0;
		SOI::TempSkinsData[skinid][SOI::set] = true;
		SOI::TempSkinsData[skinid][SOI::bone] = bone;
		SOI::TempSkinsData[skinid][SOI::x] = x;
		SOI::TempSkinsData[skinid][SOI::y] = y;
		SOI::TempSkinsData[skinid][SOI::z] = z;
		SOI::TempSkinsData[skinid][SOI::rx] = rx;
		SOI::TempSkinsData[skinid][SOI::ry] = ry;
		SOI::TempSkinsData[skinid][SOI::rz] = rz;
		SOI::TempSkinsData[skinid][SOI::sx] = sx;
		SOI::TempSkinsData[skinid][SOI::sy] = sy;
		SOI::TempSkinsData[skinid][SOI::sz] = sz;
		return 1;
	}
	
	stock SOI::LoadTempData(modelid){
		new file_name[64];
		format(file_name,sizeof(file_name),"/SOI/%d.soi",modelid);
		if(!fexist(file_name)){
			for(new skinid = 0; skinid < MAX_SKINS; skinid++){
				SOI::TempSkinsData[skinid][SOI::set] = false;
				SOI::TempSkinsData[skinid][SOI::bone] = 0;
				SOI::TempSkinsData[skinid][SOI::x] = 0.0;
				SOI::TempSkinsData[skinid][SOI::y] = 0.0;
				SOI::TempSkinsData[skinid][SOI::z] = 0.0;
				SOI::TempSkinsData[skinid][SOI::rx] = 0.0;
				SOI::TempSkinsData[skinid][SOI::ry] = 0.0;
				SOI::TempSkinsData[skinid][SOI::rz] = 0.0;
				SOI::TempSkinsData[skinid][SOI::sx] = 0.0;
				SOI::TempSkinsData[skinid][SOI::sy] = 0.0;
				SOI::TempSkinsData[skinid][SOI::sz] = 0.0;
			}
			SOI::TempFileData[SOI::active] = true;
			SOI::TempFileData[SOI::modelid] = modelid;
			return 1;
		}
		new File:inpf = fopen(file_name,io_read);
		if(!inpf) return 0;
		if(flength(inpf) != SOI_FILE_SIZE){
			fclose(inpf);
			return 0;
		}
	
		//Get Header
		new h_len = strlen(SOI_HEADER_KEY), h_key[32];
		for(new i = 0; i < h_len; i++){
			h_key[i] = fgetchar(inpf,0,false);
		}
		h_key[h_len] = EOS;
		if(!strcmp(h_key,SOI_HEADER_KEY,true)){
			for(new skinid = 0; skinid < MAX_SKINS; skinid++){
				SOI::MergeValue(SOI::TempSkinsData[skinid][SOI::bone],0,0,0,fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::x],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::y],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::z],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::rx],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::ry],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::rz],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::sx],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::sy],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::MergeFloat(SOI::TempSkinsData[skinid][SOI::sz],fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SOI::TempSkinsData[skinid][SOI::set] = true;
			}
			SOI::TempFileData[SOI::active] = true;
			SOI::TempFileData[SOI::modelid] = modelid;
			fclose(inpf);
			return 1;
		} else {
			fclose(inpf);
			return 0;
		}
	}
	
	stock SOI::DumpTempData(){
		if(!SOI::TempFileData[SOI::active]) return 0;
		new file_name[64];
		format(file_name,sizeof(file_name),"/SOI/%d.soi",SOI::TempFileData[SOI::modelid]);
		if(fexist(file_name)) fremove(file_name);
		new File:outf = fopen(file_name,io_write);
		if(!outf) return 0;
		
		new int1, int2, int3, int4, bone,
			Float:x,Float:y,Float:z,
			Float:rx,Float:ry,Float:rz,
			Float:sx,Float:sy,Float:sz;
		
		fwrite(outf,SOI_HEADER_KEY);
		for(new skinid = 0; skinid < MAX_SKINS; skinid++){
			if(!SOI::TempSkinsData[skinid][SOI::set]){
				SOI::GetDefaultSkinOffset(bone,x,y,z,rx,ry,rz,sx,sy,sz);
				SOI::SetTempSkinOffset(skinid,bone,x,y,z,rx,ry,rz,sx,sy,sz);
			}
		}
		for(new skinid = 0; skinid < MAX_SKINS; skinid++){
			SOI::ExtractValue(SOI::TempSkinsData[skinid][SOI::bone],int1,int2,int3,int4);
			fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::x],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::y],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::z],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::rx],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::ry],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::rz],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::sx],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::sy],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SOI::ExtractFloat(SOI::TempSkinsData[skinid][SOI::sz],int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
		}
		fclose(outf);
		return 1;
	}

#endif

stock SOI::GetSkinOffset(modelid,skinid,&bone,&Float:x,&Float:y,&Float:z,&Float:rx=0.0,&Float:ry=0.0,&Float:rz=0.0,&Float:sx=0.0,&Float:sy=0.0,&Float:sz=0.0){
	if(skinid < 0 || skinid >= MAX_SKINS) return 0;
	new file_name[64];
	format(file_name,sizeof(file_name),"/SOI/%d.soi",modelid);
	if(!fexist(file_name)) return 0;
	new File:inpf = fopen(file_name,io_read);
	if(!inpf) return 0;
	if(flength(inpf) != SOI_FILE_SIZE){
		fclose(inpf);
		return 0;
	}

	fseek(inpf,11+(skinid*37),seek_start);
	SOI::MergeValue(bone,0,0,0,fgetchar(inpf,0,false));
	SOI::MergeFloat(x,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(y,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(z,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(rx,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(ry,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(rz,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(sx,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(sy,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	SOI::MergeFloat(sz,fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false),fgetchar(inpf,0,false));
	fclose(inpf);
	return 1;
}

//EOF