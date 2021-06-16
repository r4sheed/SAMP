/*
 DataConvert.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.
 Contributors: Crayder, Shiny

 Website: https://adm.ct8.pl

 Plugins: SScanf
 Modules: None

 File Version: 2.3.0
 SScanf Version: 2.8.2

 Definitions:
 FIRST_FILE_ADDRESS
 INVALID_FILE_ID
 INVALID_FILE_HANDLE
 INT_NUMBER_LEN
 HEX_NUMBER_LEN
 BIN_NUMBER_LEN
 OCT_NUMBER_LEN

 Functions:
 DataConvert::strcopy(const input[],output[]);  //string copy for warning 224: indeterminate array size
 fstrcopy(const input[],output[],maxdest = sizeof(output));   //fast string copy
 ABCToCBA(const input[],output[]);
 AnyToInt(string[],type,&bool:flag);
 IntToAny(value,output[],type);
 rot13(string[]);
 code128(const input[],output[]);
 swap_int({Float,_}:int1,{Float,_}:int2);
 swap_string(string1[], string2[], dest1 = sizeof(string1), dest2 = sizeof(string2));
 ContainInSeries(value,...);
 ContainInSeriesFloat(Float:value,Float:...);
 StringEqual(string1[],string2[],ignorecase);
 StringNotEqual(string1[],string2[],ignorecase);
 base64_decode(const input[],output[]); //d:base64
 base64_encode(const input[],output[]); //e:base64
 StripNewLine(string[]);
 strreplace(string[],const search[],const replacement[],bool:ignorecase = false,pos = 0,limit = -1,maxlength = sizeof(string));
 strlower(string[]);
 strupper(string[]);
 DataConvert::InvertString(const input[], output[], maxdest = sizeof(output));
 DataConvert::StringToHexString(const input[], output[], maxdest = sizeof(output));
 DataConvert::HexStringToString(const input[], output[], maxdest = sizeof(output));

 File functions:
 GetFileHandleID(File:handle);
 GetFileID(File:handle);
 fcopy(const input[],output[]);
 frename(oldname[],newname[]);
 DataConvert::FileCreate(const name[]);
 DataConvert::MergeFile(const first_file[],const second_file[],bool:erase_second=false);
 DataConvert::MergeFileGroup(const group_name[],const output[],upperbound_index,bool:erase_input=false);
 DataConvert::SplitFile(const input[],const output[],max_size,&upperbound_index=0);

 Validators:
 IsDecimalNumber(const string[]);
 IsHexNumber(const string[]);
 IsBinaryNumber(const string[]);
 IsOctalNumber(const string[]);
 IsFloatNumber(const string[]);

 Convert to Bool:
 StringToBool(const string[]);
 IntToBool(value);

 Convert to Int:
 StringToInt(const string[]);
 BoolToInt(bool:boolean);
 HexToInt(const string[]);
 BinToInt(const string[]);
 OctToInt(const string[]);

 Convert to Hex:
 IntToHex(value);
 IntToHexEx(value);
 BinToHex(const string[]);
 BinToHexEx(const string[]);
 OctToHex(const string[]);

 Convert to Bin:
 IntToBin(value);
 HexToBin(const string[]);
 OctToBin(const string[]);

 Convert to Oct:
 IntToOct(value);
 HexToOct(const string[]);
 BinToOct(const string[]);

 Binary Data Convert:
 FloatToInt(Float:value); //Convert Float binary data to Integer binary data !
 IntToFloat(value); //Convert Integer binary data to Float binary data !

*/

#if !defined sscanf
	#error [ADM] This include required SScanf v2.8.2
#endif

#if defined _Data_Convert
	#endinput
#endif
#define _Data_Convert

#if defined _base64_included
	#error [ADM] Please remove deprecated file base64.inc
#endif

#define Data_Convert_Version						(20300) //a.b.c 10000*a+100*b+c
#if defined GetPlayerCustomSkin
	#define DATACONVERT_SAMP_VERSION				"0.3 DL"
#else
	#define DATACONVERT_SAMP_VERSION				"0.3.7"
#endif

#define DataConvert::								DC_

new const DataConvert::LettersTable[] = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
};
	
new const DataConvert::Decoder[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  62, 0,  0,  0,  63, 52, 53,
	54, 55, 56, 57, 58, 59, 60, 61, 0,  0,
	0,  0,  0,  0,  0,  0,  1,  2,  3,  4,
	5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 0,  0,  0,  0,  0,  0,  26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0
};

#if !defined isnull
	#define isnull(%1) 					((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define INT_NUMBER_LEN					12
#define HEX_NUMBER_LEN					12
#define BIN_NUMBER_LEN					36
#define OCT_NUMBER_LEN					14
#define DC_MAX_FILE_SIZE				(68157440)	//64 MB

#define FIRST_FILE_ADDRESS				(0x004E5A18)
#define INVALID_FILE_ID					(0xFFB1A5E7)
#define INVALID_FILE_HANDLE				(File:0)
#define GetFileHandleID(%0)				(_:%0)
#define StringToInt(%0)					strval(%0)

//swapvars by Crayder
#define swap_int(%0,%1)					(((%0) ^= (%1)), ((%1) ^= (%0)), ((%0) ^= (%1)))

#define BoolToInt(%0)					((%0)?1:0)
#define IntToBool(%0)					(((%0) == 1)?true:false)

#define FloatToInt(%0)					(_:%0)
#define IntToFloat(%0)					(Float:%0)

#define StringEqual(%0,%1,%2) 			(!strcmp((%0),(%1),(%2)))
#define StringNotEqual(%0,%1,%2)		(strcmp((%0),(%1),(%2)) != 0)

stock ABCToCBA(const input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[j-(i+1)] = input[i];
	}
	output[strlen(input)] = EOS;
}

stock AnyToInt(const string[],type,&bool:flag){
	new DC_Symbol, len = strlen(string), i = 1, value;
	if(string[0] >= 0x30 && string[0] <= 0x39){
		value = string[0] - 48;
	} else {
		value = string[0] - 55;
	}
	if(value >= type){
		flag = false;
		return 0;
	}

	while(i < len){
		if(string[i] >= 0x30 && string[i] <= 0x39){
			DC_Symbol = string[i] - 48;
		} else {
			DC_Symbol = string[i] - 55;
		}
		if(DC_Symbol >= type){
			flag = false;
			return 0;
		}
		value = value * type + DC_Symbol;
		i++;
	}
	flag = true;
	return value;
}

stock IntToAny(value,output[],type){
	new tmp = value, val[256], i = 0;
	while(tmp > 0){
		val[i] = (tmp % type);
		if(val[i] < 10){
			val[i] += 0x30;
		} else {
			val[i] += 0x37;
		}
		tmp /= type;
		i++;
	}
	val[i] = EOS;
	ABCToCBA(val,output);
}

stock DataConvert::strcopy(const input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++) output[i] = input[i];
	output[strlen(input)] = EOS;
}

#if !defined strcopy
	#define strcopy DataConvert::strcopy
#endif

stock fstrcopy(const input[],output[],maxdest = sizeof(output)){
	output[0] = EOS;
	strcat(output,input,maxdest);
	output[strlen(input)] = EOS;
}

stock bool:IsDecimalNumber(const string[]){
	new value = 0;
	return !(sscanf(string,"d",value));
}

stock bool:IsHexNumber(const string[]){
	new value = 0;
	return !(sscanf(string,"x",value));
}

stock bool:IsBinaryNumber(const string[]){
	new value = 0;
	return !(sscanf(string,"b",value));
}

stock bool:IsOctalNumber(const string[]){
	new value = 0;
	return !(sscanf(string,"o",value));
}

stock bool:IsFloatNumber(const string[]){
	new Float:value = 0;
	return !(sscanf(string,"f",value));
}

stock bool:swap_string(string1[],string2[],dest1 = sizeof(string1),dest2 = sizeof(string2)){
	if(dest1 < strlen(string2) || dest2 < strlen(string1)) return false;
	new swap_size = dest1;
	if(dest2 > swap_size) swap_size = dest2;
	for(new i = 0; i < swap_size; i++){
		swap_int(string1[i],string2[i]);
	}
	return true;
}

stock GetFileID(File:handle){
	return (handle == INVALID_FILE_HANDLE)?INVALID_FILE_ID:((GetFileHandleID(handle)-FIRST_FILE_ADDRESS)/32);
}

stock BinToInt(const string[]){
	new value = 0;
	if(sscanf(string,"b",value)) return 0;
	return value;
}

stock HexToBin(const string[]){
	new DC_Result[BIN_NUMBER_LEN], value = 0;
	sscanf(string,"x",value);
	format(DC_Result,sizeof(DC_Result),"%b",value);
	return DC_Result;
}

stock BinToHex(const string[]){
	new DC_Result[HEX_NUMBER_LEN], value = 0;
	if(sscanf(string,"b",value)){
		format(DC_Result,sizeof(DC_Result),"0");
	} else {
		format(DC_Result,sizeof(DC_Result),"%06x",value);
	}
	return DC_Result;
}

stock BinToHexEx(const string[]){
	new DC_Result[HEX_NUMBER_LEN], value = 0;
	if(sscanf(string,"b",value)){
		format(DC_Result,sizeof(DC_Result),"0");
	} else {
		format(DC_Result,sizeof(DC_Result),"%x",value);
	}
	return DC_Result;
}

stock IntToBin(value){
	new DC_Result[BIN_NUMBER_LEN];
	format(DC_Result,sizeof(DC_Result),"%b",value);
	return DC_Result;
}

stock bool:StringToBool(const string[]){
	return (string[0] != '0');
}

stock HexToInt(const string[]){
	new value = 0;
	if(sscanf(string,"x",value)) return 0;
	return value;
}

stock IntToHex(value){
	new DC_Result[HEX_NUMBER_LEN];
	format(DC_Result,sizeof(DC_Result),"%06x",value);
	return DC_Result;
}

stock IntToHexEx(value){
	new DC_Result[HEX_NUMBER_LEN];
	format(DC_Result,sizeof(DC_Result),"%x",value);
	return DC_Result;
}

stock OctToInt(const string[]){
	new value = 0;
	if(sscanf(string,"o",value)) return 0;
	return value;
}

stock OctToHex(const string[]){
	new DC_Result[HEX_NUMBER_LEN], value = 0;
	if(sscanf(string,"o",value)){
		format(DC_Result,sizeof(DC_Result),"0");
	} else {
		format(DC_Result,sizeof(DC_Result),"%x",value);
	}
	return DC_Result;
}

stock OctToBin(const string[]){
	new DC_Result[BIN_NUMBER_LEN], value = 0;
	if(sscanf(string,"o",value)){
		format(DC_Result,sizeof(DC_Result),"0");
	} else {
		format(DC_Result,sizeof(DC_Result),"%b",value);
	}
	return DC_Result;
}

stock rot13(string[]){
	for(new i = 0, j = strlen(string); i < j; i++){
		if('a' <= string[i] <= 'z'){
			string[i] = (string[i] - 'a' + 13) % 26 + 'a';
		} else if('A' <= string[i] <= 'Z'){
			string[i] = (string[i] - 'A' + 13) % 26 + 'A';
		}
	}
}

stock code128(const input[],output[]){
	for(new i = 0, j = strlen(input); i < j; i++){
		output[i] = (0xFF & input[i]+128);
	}
	output[strlen(input)] = EOS;
}

stock bool:ContainInSeries(value,...){
	for(new i = 1, j = numargs(); i < j; i++){
		if(getarg(i) == value) return true;
	}
	return false;
}

stock bool:ContainInSeriesFloat(Float:value,Float:...){
	for(new i = 1, j = numargs(); i < j; i++){
		if((Float:getarg(i)) == value) return true;
	}
	return false;
}

stock IntToOct(value){
	new DC_Result[OCT_NUMBER_LEN];
	IntToAny(value,DC_Result,8);
	return DC_Result;
}

stock HexToOct(const string[]){
	new DC_Result[OCT_NUMBER_LEN];
	IntToAny(HexToInt(string),DC_Result,8);
	return DC_Result;
}

stock BinToOct(const string[]){
	new DC_Result[OCT_NUMBER_LEN];
	IntToAny(BinToInt(string),DC_Result,8);
	return DC_Result;
}

stock strlower(string[]){
	for(new i = 0, j = strlen(string); i < j; i++){
		string[i] = tolower(string[i]);
	}
}

stock strupper(string[]){
	for(new i = 0, j = strlen(string); i < j; i++){
		string[i] = toupper(string[i]);
	}
}

stock StripNewLine(string[]){
	new len = strlen(string);
	if(string[0] == 0) return 0;
	if(string[(len-1)]=='\n' || string[(len-1)]=='\r'){
		string[(len-1)] = 0;
		if(string[0] == 0) return 0;
		if(string[(len-2)]=='\n' || string[(len-2)]=='\r'){
			string[(len-2)] = 0;
		}
	}
	return 1;
}

stock fcopy(const input[],output[]){
	if(!fexist(input)) return 0;
	if(fexist(output)) return 0;
	new File:inpf = fopen(input,io_read),
		File:outf = fopen(output,io_write);
	if(!inpf || !outf) return 0;
	for(new i = flength(inpf); i > 0; i--){
		fputchar(outf,fgetchar(inpf,0,false),false);
	}
	fclose(inpf);
	fclose(outf);
	return 1;
}

#if !defined _YSF_included
	stock frename(oldname[],newname[]){
		if(!fexist(oldname)) return 0;
		if(fexist(newname)) return 0;
		if(!fcopy(oldname,newname))	return 0;
		fremove(oldname);
		return 1;
	}
#endif

stock strreplace(string[],const search[],const replacement[],bool:ignorecase = false,pos = 0,limit = -1,maxlength = sizeof(string)){
	if(limit == 0) return 0;

	new sublen = strlen(search),
		replen = strlen(replacement),
		bool:packed = ispacked(string),
		maxlen = maxlength,
		len = strlen(string),
		count = 0;
	
	if(packed) maxlen *= 4;
	if(!sublen) return 0;
	
	while(-1 != (pos = strfind(string, search, ignorecase, pos))){
		strdel(string, pos, pos + sublen);
		len -= sublen;
		
		if(replen && len + replen < maxlen){
			strins(string, replacement, pos, maxlength);

			pos += replen;
			len += replen;
		}

		// Is there a limit of number of replacements, if so, did we break it?
		if(limit != -1 && ++count >= limit)	break;
	}

	return count;
}

//base64 by Shiny
stock base64_decode(const input[],output[]){
	new SpaceReplacer = '=', len = strlen(input), Position;
	
	for(new i = 0; i < len; i++){
		new char_[2];
		char_[0] = DataConvert::Decoder[input[i++]];
		char_[1] = DataConvert::Decoder[input[i]];
		char_[0] = (char_[0] << 2) | ((char_[1] >> 4) & 3);
		Position += format(output[Position], len, "%c", char_[0]);
		
		if(++i < len){
			char_[0] = input[i];
			if(char_[0] == SpaceReplacer) break;
			char_[0] = DataConvert::Decoder[input[i]];
			char_[1] = ((char_[1] << 4) & 240) | ((char_[0] >> 2) & 15);
			Position += format(output[Position], len, "%c", char_[1]);
		}
		
		if(++i < len){
			char_[1] = input[i];
			if(char_[1] == SpaceReplacer) break;
			char_[1] = DataConvert::Decoder[input[i]];
			char_[0] = ((char_[0] << 6) & 192) | char_[1];
			Position += format(output[Position], len, "%c", char_[0]);
		}
	}
}

stock base64_encode(const input[],output[]){
	new SpaceReplacer = '=', len = strlen(input), Position;
	
	for(new i = 0 ; i < len ; i++){
		new Character;
		Character = (input[i] >> 2) & 63;
		Position += format(output[Position], len, "%c", DataConvert::LettersTable[Character]);
		Character = (input[i] << 4) & 63;
		
		if(++i < len){
			Character |= (input[i] >> 4) & 15;
		}
		Position += format(output[Position], len, "%c", DataConvert::LettersTable[Character]);

		if(i < len){
			Character = (input[i] << 2) & 63;
			
			if(++i < len){
				Character |= (input[i] >> 6) & 3;
			}
			Position += format(output[Position], len, "%c", DataConvert::LettersTable[Character]);
		} else {
			i++;
			Position += format(output[Position], len, "%c", SpaceReplacer);
		}

		if(i < len){
			Character = input[i] & 63;
			Position += format(output[Position], len, "%c", DataConvert::LettersTable[Character]);
		} else {
			Position += format(output[Position], len, "%c", SpaceReplacer);
		}
	}
}

stock DataConvert::FileCreate(const name[]){
	if(!fexist(name)){
		new File:cfile = fopen(name,io_readwrite);
		fwrite(cfile,"");
		fclose(cfile);
		return 1;
	}
	return 0;
}

stock DataConvert::InvertString(const input[], output[], maxdest = sizeof(output)){
	new asize = strlen(input);
	if(maxdest < asize) return 0;
	for(new i = 0; i < asize; i++) output[i] = (input[i] ^ 0xFF);
	output[asize] = EOS;
	return1;
}

stock DataConvert::StringToHexString(const input[], output[], maxdest = sizeof(output)){
	new asize = strlen(input), offset = 0;
	if((asize*2) > maxdest) return 0;
	for(new i = 0; i < asize; i++){
		output[offset] = (0xF & (input[i] >> 4));
		if(output[offset] < 10){
			output[offset] += 48;
		} else {
			output[offset] += 55;
		}
		output[offset+1] = (0xF & input[i]);
		if(output[offset+1] < 10){
			output[offset+1] += 48;
		} else {
			output[offset+1] += 55;
		}
		offset += 2;
	}
	output[asize*2] = EOS;
	return 1;
}

stock DataConvert::HexStringToString(const input[], output[], maxdest = sizeof(output)){
	new asize = (strlen(input)/2), offset = 0, unit[2];
	if(asize > maxdest) return 0;
	for(new i = 0; i < asize; i++){
		if(input[offset] >= 97){
			unit[0] = (input[offset]-87);
		} else if(input[offset] < 58){
			unit[0] = (input[offset]-48);
		} else {
			unit[0] = (input[offset]-55);
		}
		if(input[offset+1] >= 97){
			unit[1] = (input[offset+1]-87);
		} else if(input[offset+1] < 58){
			unit[1] = (input[offset+1]-48);
		} else {
			unit[1] = (input[offset+1]-55);
		}
		output[i] = (unit[0]*16)+unit[1];
		offset += 2;
	}
	output[asize] = EOS;
	return 1;
}

stock DataConvert::MergeFile(const first_file[],const second_file[],bool:erase_second=false){
	if(!fexist(first_file)) return 0;
	if(!fexist(second_file)) return 0;
	
	new File:inpf = fopen(second_file,io_read);
	if(!inpf) return 0;
	new asize = flength(inpf), idx = 0;
	if(asize > DC_MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return 0;
	}
	new File:outf = fopen(first_file,io_append);
	if(!outf){
		fclose(inpf);
		return 0;
	}
	while(idx < asize){
		fputchar(outf,fgetchar(inpf,0,false),false);
		idx++;
	}
	fclose(inpf);
	fclose(outf);
	if(erase_second){
		fremove(second_file);
	}
	return 1;
}

stock DataConvert::MergeFileGroup(const group_name[],const output[],upperbound_index,bool:erase_input=false){
	if(fexist(output)) return 0;
	DataConvert::FileCreate(output);
	new part_file[256], File:inpf, idx, asize;
	for(new i = 0; i <= upperbound_index; i++){
		new File:outf = fopen(output,io_append);
		format(part_file,sizeof(part_file),"%s_%04d",group_name,i);
		if(!fexist(part_file)){
			fclose(inpf);
			return 0;
		}
		inpf = fopen(part_file,io_read);
		idx = 0, asize = flength(inpf);
		
		while(idx < asize){
			fputchar(outf,fgetchar(inpf,0,false),false);
			idx++;
		}
		fclose(inpf);
		fclose(outf);
		if(erase_input){
			fremove(part_file);
		}
	}
	return 1;
}

stock DataConvert::SplitFile(const input[],const output[],max_size,&upperbound_index=0){
	if(!fexist(input)) return 0;
	new File:inpf = fopen(input,io_read);
	if(!inpf) return 0;
	new asize = flength(inpf), idx = 0;
	if(asize > DC_MAX_FILE_SIZE || asize < 0){
		fclose(inpf);
		return 0;
	}
	new used_mem = 0, part_file[256], current_status = false;
	
	upperbound_index = 0;
	
	format(part_file,sizeof(part_file),"%s_%04d",output,upperbound_index);
	DataConvert::FileCreate(part_file);

	new File:outf = fopen(part_file,io_write);
	if(!outf){
		fclose(inpf);
		return 0;
	}
	current_status = true;
	
	while(idx < asize){
		fputchar(outf,fgetchar(inpf,0,false),false);
		used_mem++;
		idx++;
		if(used_mem >= max_size){
			used_mem = 0;
			fclose(outf);
			current_status = false;
			if(idx < asize){
				upperbound_index++;
				format(part_file,sizeof(part_file),"%s_%04d",output,upperbound_index);
				DataConvert::FileCreate(part_file);
				outf = fopen(part_file,io_write);
				current_status = true;
			}
		}
	}
	fclose(inpf);
	if(current_status) fclose(outf);
	return 1;
}

#define e:base64 					base64_encode
#define d:base64 					base64_decode

//EOF