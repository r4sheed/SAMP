/*************************************************************************************************************************************
 *                                                                                                                                   *
 *                                                        )(   SWAP File   )(                                                        *
 *                                                                                                                                   *
 * Copyright © 2021 Abyss Morgan. All rights reserved.                                                                               *
 * Contributors: Katarina Calzaghe                                                                                                   *
 *                                                                                                                                   *
 * Website: https://adm.ct8.pl                                                                                                       *
 *                                                                                                                                   *
 * Plugins: None                                                                                                                     *
 * Modules: None                                                                                                                     *
 *                                                                                                                                   *
 * File Version: 1.3.0                                                                                                               *
 *                                                                                                                                   *
 * Data types:                                                                                                                       *
 * String -  X bytes string                                                                                                          *
 * Block -   the same as string but don't check EOS on R/W functions                                                                 *
 * Array -   4 bytes array cells                                                                                                     *
 * Float -   4 bytes float value                                                                                                     *
 * Integer - 4 bytes integer value                                                                                                   *
 * Enum -    full enum read/write (Required ZeeX Compiler + #define SWAP_ENABLE_ENUM_SUPPORT )                                       *
 *                                                                                                                                   *
 * Functions:                                                                                                                        *
 * SWAP::create_empty(const name[]);                       //create new empty file (not recommended)                                 *
 * SWAP::create_block(const name[],size);                  //create block for empty file (not recommended, big fragmentation)        *
 * SWAP::reserve(const name[],size);                       //reserve new SWAP file size (recommended)                                *
 * SWAP::format(const name[],const key[][],k_len=sizeof(key[])); //format new SWAP file (use after SWAP::reserve, not recommended)   *
 * SWAP::format_random(const name[]);                      //format new SWAP file (use after SWAP::reserve, recommended)             *
 * SWAP::decrypt_file(const input[],const output[],const key[][],k_len=sizeof(key[]));                                               *
 * SWAP::read_string(const name[],const key[][],position,text[],len,k_len=sizeof(key[]));                                            *
 * SWAP::write_string(const name[],const key[][],position,const text[],max_dest=sizeof(text),k_len=sizeof(key[]));                   *
 * SWAP::read_array(const name[],const key[][],position,array[],len,k_len=sizeof(key[]));                                            *
 * SWAP::write_array(const name[],const key[][],position,const array[],max_dest=sizeof(array),k_len=sizeof(key[]));                  *
 * SWAP::write_block(const name[],const key[][],position,const text[],max_dest=sizeof(text),k_len=sizeof(key[]));                    *
 * SWAP::read_int(const name[],const key[][],position,k_len=sizeof(key[]));                                                          *
 * SWAP::write_int(const name[],const key[][],position,value,k_len=sizeof(key[]));                                                   *
 * SWAP::read_float(const name[],const key[][],position,k_len=sizeof(key[]));                                                        *
 * SWAP::write_float(const name[],const key[][],position,Float:value,k_len=sizeof(key[]));                                           *
 * SWAP::read_byte(const name[],const key[][],position,k_len=sizeof(key[]));                                                         *
 * SWAP::write_byte(const name[],const key[][],position,value,k_len=sizeof(key[]));                                                  *
 *                                                                                                                                   *
 * Enum Functions (Katarina Calzaghe):                                                                                               *
 * SWAP::Volume<volume_id,variable,enum_name>(const name[],const key[][]); //public declaration                                      *
 * SWAP::VarSave(volume_id,variable);                                                                                                *
 * SWAP::VarLoad(volume_id,variable);                                                                                                *
 * SWAP::EnumSize(enum_name);                                                                                                        *
 * SWAP::ForeachEnum(variable,enum_name);                                                                                            *
 * SWAP::VarAccess(var_name,enum_name,itemid);                                                                                       *
 *                                                                                                                                   *
 * RAM Functions:                                                                                                                    *
 * RAM::Create(const name[],const key[][],block_size,max_blocks,k_len=sizeof(key[]));   //Create RAM with SWAP::format_random        *
 * RAM::CreateEx(const name[],const key[][],block_size,max_blocks,k_len=sizeof(key[])); //Create RAM with SWAP::format               *
 * RAM::ResetVariables(const name[],const key[][],k_len=sizeof(key[]));                                                              *
 * RAM::CreateVariable(const name[],const key[][],k_len=sizeof(key[]));                                                              *
 * RAM::DestroyVariable(const name[],const key[][],&variableid,k_len=sizeof(key[]));                                                 *
 * RAM::GetBlockSize(const name[],const key[][],k_len=sizeof(key[]));                                                                *
 * RAM::GetMaxBlock(const name[],const key[][],k_len=sizeof(key[]));                                                                 *
 * RAM::GetVariableAddress(const name[],const key[][],variableid,k_len=sizeof(key[]));                                               *
 * RAM::read_string(const name[],const key[][],variableid,text[],len,k_len=sizeof(key[]));                                           *
 * RAM::write_string(const name[],const key[][],variableid,const text[],max_dest=sizeof(text),k_len=sizeof(key[]));                  *
 * RAM::write_block(const name[],const key[][],variableid,text[],max_dest=sizeof(text),k_len=sizeof(key[]));                         *
 * RAM::read_array(const name[],const key[][],variableid,array[],len,k_len=sizeof(key[]));                                           *
 * RAM::write_array(const name[],const key[][],variableid,array[],max_dest=sizeof(array),k_len=sizeof(key[]));                       *
 * RAM::SaveLog(const name[],const key[][],string[],k_len=sizeof(key[]));                                                            *
 *                                                                                                                                   *
 *************************************************************************************************************************************/

#if defined _SWAP_include
	#endinput
#endif
#define _SWAP_include

#define SWAP_Version							(10300) //a.b.c 10000*a+100*b+c

#define SWAP::									SWAP_
#define RAM::									RAM_

#define SWAP_WRITE								0
#define SWAP_READ								1

#if !defined MAX_SWAP_RAM_ITEMS
	#define MAX_SWAP_RAM_ITEMS					32768
#endif

#define SWAP_ExtractValue(%0,%1,%2,%3,%4)		((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define SWAP_ExtractFloat(%0,%1,%2,%3,%4)		((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define SWAP_MergeValueEx(%1,%2,%3,%4)			(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4))
#define SWAP_MergeFloatEx(%1,%2,%3,%4)			(Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#define SWAP_GetValueBit(%0,%1)					((%0) >>> (%1) & 0x01)
#define SWAP_SetValueBit(%0,%1,%2)				((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

//Dynamic Toggle Config Macros
#define SWAP_GetConfigAddress(%0)				(floatround((%0)/32))
#define SWAP_GetConfigBit(%0)					((%0) % 32)
#define SWAP_GetConfigSize(%0)					(((%0) / 32)+1)

#define SWAP_IsToggleConfigInformation(%0,%1)	SWAP::GetValueBit(%0[SWAP::GetConfigAddress(%1)],SWAP::GetConfigBit(%1))
#define SWAP_ToggleConfigInformation(%0,%1,%2)	SWAP::SetValueBit(%0[SWAP::GetConfigAddress(%1)],SWAP::GetConfigBit(%1),((%2) & 0x1))

#if defined SWAP_ENABLE_ENUM_SUPPORT
	#define SWAP_VarSave(%0,%1)						SWAP::W_%1(%0)
	#define SWAP_VarLoad(%0,%1)						SWAP::R_%1(%0)
	#define SWAP_ForeachEnum(%0,%1)					for(new %0 = 0; %0 < _:%1; %0++)
	#define SWAP_VarAccess(%0,%1,%2)				%0[%1:%2]
	#define SWAP_EnumSize(%0)						(4 * _:%0)

	#pragma tabsize 0

	#define SWAP_write_enum(%1,%2,%3,%4,%5) \
		if(!fexist(%1)) return 0; \
		new File:outf = fopen(%1,io_readwrite); \
		if(!outf) return 0; \
		fseek(outf,%3,seek_start); \
		new k_len = sizeof(%2[]), step = (%3 % k_len), int1, int2, int3, int4; \
		SWAP::ForeachEnum(i,%5){ \
			SWAP::ExtractValue(SWAP::VarAccess(%4,%5,i),int1,int2,int3,int4); \
			fputchar(outf,((int1+%2[SWAP::WRITE][step++ % k_len]) & 0xFF),false); \
			fputchar(outf,((int2+%2[SWAP::WRITE][step++ % k_len]) & 0xFF),false); \
			fputchar(outf,((int3+%2[SWAP::WRITE][step++ % k_len]) & 0xFF),false); \
			fputchar(outf,((int4+%2[SWAP::WRITE][step++ % k_len]) & 0xFF),false); \
		} \
		fclose(outf); \
		return 1
		
	#define SWAP_read_enum(%1,%2,%3,%4,%5) \
		if(!fexist(%1)) return 0; \
		new File:inpf = fopen(%1,io_read); \
		if(!inpf) return 0; \
		fseek(inpf,%3,seek_start); \
		new k_len = sizeof(%2[]), step = (%3 % k_len); \
		SWAP::ForeachEnum(i,%5){ \
			SWAP::VarAccess(%4,%5,i) = SWAP::MergeValueEx(((fgetchar(inpf,0,false)+%2[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+%2[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+%2[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+%2[SWAP::READ][step++ % k_len]) & 0xFF)); \
		} \
		fclose(inpf); \
		return 1

	#define SWAP_Volume<%0,%1,%2>(%3,%4); \
		stock SWAP::W_%1(%0){ \
			SWAP::write_enum(%3,%4,%0*SWAP::EnumSize(%2),%1[%0],%2); \
		} \
		stock SWAP::R_%1(%0){ \
			SWAP::read_enum(%3,%4,%0*SWAP::EnumSize(%2),%1[%0],%2); \
		}
#endif

stock SWAP::create_empty(const name[]){
	if(fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	fwrite(outf,"");
	fclose(outf);
	return 1;
}

stock SWAP::create_block(const name[],size){
	if(size <= 0 || !fexist(name)) return 0;
	new File:outf = fopen(name,io_append);
	if(!outf) return 0;
	new asize = flength(outf);
	for(new i = 0; i < size; i++){
		fputchar(outf,random(256),false);
	}
	fclose(outf);
	return asize;
}

stock SWAP::reserve(const name[],size){
	if(fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	fseek(outf,size-1,seek_start);
	fputchar(outf,0,false);
	fclose(outf);
	return 1;
}

stock SWAP::format(const name[],const key[][],k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite), step, len = flength(outf);
	for(new i = 0; i < len; i++){
		fputchar(outf,((key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::format_random(const name[]){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite), len = flength(outf);
	for(new i = 0; i < len; i++){
		fputchar(outf,random(256),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::decrypt_file(const input[],const output[],const key[][],k_len=sizeof(key[])){
	if(!fexist(input)) return 0;
	if(fexist(output)) return 0;
	new File:inpf = fopen(input,io_read), step, len = flength(inpf);
	SWAP::reserve(output,len);
	new File:outf = fopen(output,io_readwrite);
	if(!outf) return 0;
	for(new i = 0; i < len; i++){
		fputchar(outf,((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),false);
	}
	fclose(inpf);
	fclose(outf);
	return 1;
}

stock SWAP::read_string(const name[],const key[][],position,text[],len,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len);
	for(new i = 0; i < len; i++){
		text[i] = (fgetchar(inpf,0,false) + key[SWAP::READ][step++ % k_len]) & 0xFF;
	}
	fclose(inpf);
	return 1;
}

stock SWAP::write_string(const name[],const key[][],position,const text[],max_dest=sizeof(text),k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), len = strlen(text);
	for(new i = 0; i < len; i++){
		fputchar(outf,((text[i]+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	}
	if(len < max_dest){
		fputchar(outf,(key[SWAP::WRITE][step++ % k_len]),false);
	}
	for(new i = len+1; i < max_dest; i++){
		fputchar(outf,random(256),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::write_block(const name[],const key[][],position,const text[],max_dest=sizeof(text),k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len);
	for(new i = 0; i < max_dest; i++){
		fputchar(outf,((text[i]+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::read_array(const name[],const key[][],position,array[],len,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len);
	for(new i = 0; i < len; i++){
		array[i] = SWAP::MergeValueEx(((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF));
	}
	fclose(inpf);
	return 1;
}

stock SWAP::write_array(const name[],const key[][],position,const array[],max_dest=sizeof(array),k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), int1, int2, int3, int4;
	for(new i = 0; i < max_dest; i++){
		SWAP::ExtractValue(array[i],int1,int2,int3,int4);
		fputchar(outf,((int1+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
		fputchar(outf,((int2+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
		fputchar(outf,((int3+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
		fputchar(outf,((int4+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	}
	fclose(outf);
	return 1;
}

stock SWAP::read_int(const name[],const key[][],position,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len), value = SWAP::MergeValueEx(((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF));
	fclose(inpf);
	return value;
}

stock SWAP::write_int(const name[],const key[][],position,value,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), int1, int2, int3, int4;
	SWAP::ExtractValue(value,int1,int2,int3,int4);
	fputchar(outf,((int1+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int2+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int3+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int4+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fclose(outf);
	return 1;
}

stock SWAP::read_byte(const name[],const key[][],position,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return 0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len), value = ((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF);
	fclose(inpf);
	return value;
}

stock SWAP::write_byte(const name[],const key[][],position,value,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len);
	fputchar(outf,((value+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fclose(outf);
	return 1;
}

stock Float:SWAP::read_float(const name[],const key[][],position,k_len=sizeof(key[])){
	if(!fexist(name)) return 0.0;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return 0.0;
	fseek(inpf,position,seek_start);
	new step = (position % k_len), Float:value = SWAP::MergeFloatEx(((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF),((fgetchar(inpf,0,false)+key[SWAP::READ][step++ % k_len]) & 0xFF));
	fclose(inpf);
	return value;
}

stock SWAP::write_float(const name[],const key[][],position,Float:value,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return 0;
	fseek(outf,position,seek_start);
	new step = (position % k_len), int1, int2, int3, int4;
	SWAP::ExtractFloat(value,int1,int2,int3,int4);
	fputchar(outf,((int1+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int2+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int3+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fputchar(outf,((int4+key[SWAP::WRITE][step++ % k_len]) & 0xFF),false);
	fclose(outf);
	return 1;
}

stock RAM::GetBlockSize(const name[],const key[][],k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	return SWAP::read_int(name,key[SWAP::READ],0x04,k_len);
}

stock RAM::GetMaxBlock(const name[],const key[][],k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	return SWAP::read_int(name,key[SWAP::READ],0x00,k_len);
}

stock RAM::GetVariableAddress(const name[],const key[][],variableid,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	return (((SWAP::read_int(name,key,0x00,k_len)-1)/8)+1) + 0x08 + (SWAP::read_int(name,key,0x04,k_len)*variableid);
}

stock RAM::read_string(const name[],const key[][],variableid,text[],len,k_len=sizeof(key[])){
	return SWAP::read_string(name,key,RAM::GetVariableAddress(name,key,variableid,k_len),text,len,k_len);
}

stock RAM::write_string(const name[],const key[][],variableid,const text[],max_dest=sizeof(text),k_len=sizeof(key[])){
	return SWAP::write_string(name,key,RAM::GetVariableAddress(name,key,variableid,k_len),text,max_dest,k_len);
}

stock RAM::write_block(const name[],const key[][],variableid,const text[],max_dest=sizeof(text),k_len=sizeof(key[])){
	return SWAP::write_block(name,key,RAM::GetVariableAddress(name,key,variableid,k_len),text,max_dest,k_len);
}

stock RAM::read_array(const name[],const key[][],variableid,array[],len,k_len=sizeof(key[])){
	return SWAP::read_array(name,key,RAM::GetVariableAddress(name,key,variableid,k_len),array,len,k_len);
}

stock RAM::write_array(const name[],const key[][],variableid,const array[],max_dest=sizeof(array),k_len=sizeof(key[])){
	return SWAP::write_array(name,key,RAM::GetVariableAddress(name,key,variableid,k_len),array,max_dest,k_len);
}

stock RAM::ResetVariables(const name[],const key[][],k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new header = ((SWAP::read_int(name,key,0,k_len)-1)/32)+1;
	for(new x = 0; x < header; x++){
		SWAP::write_int(name,key,0x08+(x*4),0,k_len);
	}
	return 1;
}

stock RAM::Create(const name[],const key[][],block_size,max_blocks,k_len=sizeof(key[])){
	if(fexist(name)) return 0;
	new size, header;
	header = 0x08 + 4*(((max_blocks-1)/32)+1);
	size = header + (block_size*max_blocks);
	size += 4096 - (size % 4096);
	
	SWAP::reserve(name,size);
	SWAP::format_random(name);
	
	SWAP::write_int(name,key,0,max_blocks,k_len);
	SWAP::write_int(name,key,4,block_size,k_len);
	RAM::ResetVariables(name,key,k_len);
	return size;
}

stock RAM::CreateEx(const name[],const key[][],block_size,max_blocks,k_len=sizeof(key[])){
	if(fexist(name)) return 0;
	new size, header;
	header = 0x08 + 4*(((max_blocks-1)/32)+1);
	size = header + (block_size*max_blocks);
	size += 4096 - (size % 4096);
	
	SWAP::reserve(name,size);
	SWAP::format(name,key,k_len);
	
	SWAP::write_int(name,key,0,max_blocks,k_len);
	SWAP::write_int(name,key,4,block_size,k_len);
	RAM::ResetVariables(name,key,k_len);
	return size;
}

stock RAM::CreateVariable(const name[],const key[][],k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new swap_header[SWAP::GetConfigSize(MAX_SWAP_RAM_ITEMS)], max_blocks = SWAP::read_int(name,key,0x00,k_len);
	SWAP::read_array(name,key,0x08,swap_header,((max_blocks-1)/32)+1,k_len);
	for(new i = 1; i < max_blocks; i++){
		if(!SWAP::IsToggleConfigInformation(swap_header,i)){
			SWAP::ToggleConfigInformation(swap_header,i,1);
			SWAP::write_array(name,key,0x08,swap_header,((max_blocks-1)/32)+1,k_len);
			return i;
		}
	}
	return 0;
}

stock RAM::DestroyVariable(const name[],const key[][],&variableid,k_len=sizeof(key[])){
	if(!fexist(name)) return 0;
	new swap_header[SWAP::GetConfigSize(MAX_SWAP_RAM_ITEMS)], max_blocks = SWAP::read_int(name,key,0x00,k_len);
	SWAP::read_array(name,key,0x08,swap_header,((max_blocks-1)/32)+1,k_len);
	SWAP::ToggleConfigInformation(swap_header,variableid,1);
	SWAP::write_array(name,key,0x08,swap_header,((max_blocks-1)/32)+1,k_len);
	variableid = 0;
	return 1;
}

stock RAM::SaveLog(const name[],const key[][],string[],k_len=sizeof(key[])){
	if(!fexist(name)) RAM::CreateEx(name,key,384,MAX_SWAP_RAM_ITEMS,k_len);
	new logid = RAM::CreateVariable(name,key,k_len);
	if(logid == 0){
		RAM::ResetVariables(name,key,k_len);
		logid = RAM::CreateVariable(name,key,k_len);
	}
	static wl_date[3],wl_time[3],wl_str[384];
	getdate(wl_date[0],wl_date[1],wl_date[2]);
   	gettime(wl_time[0],wl_time[1],wl_time[2]);
   	format(wl_str,sizeof(wl_str),"[%02d.%02d.%02d %02d:%02d:%02d] %s",wl_date[0],wl_date[1],wl_date[2],wl_time[0],wl_time[1],wl_time[2],string);
	return RAM::write_string(name,key,logid,wl_str,384,k_len);
}

//EOF