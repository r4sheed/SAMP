/*
 BitFunctions.inc
 Copyright © 2021 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: None
 Modules: None

 File Version: 1.8.0

 bit 0 - 31:
 (bit 31) --> 11111111000000001111010001010000 <-- (bit 0)

 Example cell mode:
 Mode 2 (cell id 15) --> 11 11 11 11 00 00 00 00 11 11 01 00 01 01 00 00 <-- (cell id 0)
 Mode 4 (cell id 7) --> 1111 1111 0000 0000 1111 0100 0101 0000 <-- (cell id 0)
 Mode 8 (cell id 3) --> 11111111 00000000 11110100 01010000 <-- (cell id 0)
 Mode 16 (cell id 1) --> 1111111100000000 1111010001010000 <-- (cell id 0)

 General Macros:
 GetValueBit(value,bit);
 SetValueBit(&value,bit,power);  //power 0 or 1
 SetValueBitTrue(&value,bit);
 SetValueBitFalse(&value,bit);
 GetCellValue(value,cellid,mode);
 SetCellValue(&value,cellid,mode,power);
 GetCellValueEx(value,offset,cellsize);
 SetCellValueEx(&value,offset,cellsize,power);
 InvertValue(value);
 InvertValueEx(value,key); //default key 0xFFFFFFFF
 bool:CheckValue(value,&count=0); //even - false,uneven - true

 File Byte Macros:
 ExtractValue(value,&byte1,&byte2,&byte3,&byte4);
 ExtractFloat(Float:value,&byte1,&byte2,&byte3,&byte4);
 MergeValue(&value,byte1,byte2,byte3,byte4);
 MergeFloat(&Float:value,byte1,byte2,byte3,byte4);
 MergeValueEx(byte1,byte2,byte3,byte4);
 Float:MergeFloatEx(byte1,byte2,byte3,byte4);

 Dynamic Toggle Config Macros:
 GetConfigAddress(itemid);
 GetConfigBit(itemid);
 GetConfigSize(max_items);
 IsToggleConfigInformation(variable,itemid);
 ToggleConfigInformation(variable,itemid,value); //values: 1/0
*/

#if defined _bit_function
	#endinput
#endif
#define _bit_function

#define BitFunction_Version					(10800) //a.b.c 10000*a+100*b+c

//General Macros
#define GetValueBit(%0,%1)					((%0) >>> (%1) & 0x01)
#define SetValueBit(%0,%1,%2)				((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define SetValueBitTrue(%0,%1)				((%0) |= (0x01 << (%1)))
#define SetValueBitFalse(%0,%1)				((%0) &= ~(0x01 << (%1)))

#define InvertValue(%0)						((%0) ^ 0xFFFFFFFF)
#define InvertValueEx(%0,%1) 				((%0) ^ (%1))

#define SetCellValue(%0,%1,%2,%3)			((%0) = (((%0) & ~((((0x01 << (%2))-1) << (%1)*(%2)))) | ((%3) << (%1)*(%2))))
#define GetCellValue(%0,%1,%2)				(((%0) & (((0x01 << (%2))-1) << (%1)*(%2))) >>> ((%1)*(%2)))

#define SetCellValueEx(%0,%1,%2,%3)			((%0) = (((%0) & ~((((0x01 << (%2))-1) << (%1)))) | ((%3) << (%1))))
#define GetCellValueEx(%0,%1,%2)			(((%0) & (((0x01 << (%2))-1) << (%1))) >>> (%1))

//File Byte Macros
#define ExtractValue(%0,%1,%2,%3,%4)		((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define ExtractFloat(%0,%1,%2,%3,%4)		((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define MergeValue(%0,%1,%2,%3,%4)			((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define MergeFloat(%0,%1,%2,%3,%4)			((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#define MergeValueEx(%1,%2,%3,%4)			(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4))
#define MergeFloatEx(%1,%2,%3,%4)			(Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

//Dynamic Toggle Config Macros
#define GetConfigAddress(%0)				(floatround((%0)/32))
#define GetConfigBit(%0)					((%0) % 32)
#define GetConfigSize(%0)					(((%0) / 32)+1)

#define IsToggleConfigInformation(%0,%1)	GetValueBit(%0[GetConfigAddress(%1)],GetConfigBit(%1))
#define ToggleConfigInformation(%0,%1,%2)	SetValueBit(%0[GetConfigAddress(%1)],GetConfigBit(%1),((%2) & 0x1))

stock bool:CheckValue(value,&count=0){
	new int = 0;
	for(new i = 31; i >= 0; i--){
		if(GetValueBit(value,i)){
			int++;
		}
	}
	count = int;
	if(int % 2 == 0) return false;
	return true;
}

//EOF