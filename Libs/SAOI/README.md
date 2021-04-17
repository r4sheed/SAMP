# San Andreas Object Image Loader (Professional) v2.5.0


###### What is that ? This is the script allows you to load binary objects file which have a dynamic structure.


## Documentation:
- [Technical Data](https://github.com/AbyssMorgan/SAOI/blob/master/documents/Technical%20Data.txt)
- [Supported Functions](https://github.com/AbyssMorgan/SAOI/blob/master/documents/Supported%20Functions.txt)
- [SAOI File Structure](https://github.com/AbyssMorgan/SAOI/blob/master/documents/SAOI%20File%20Structure.txt)

## How to use SAOI:
- Download and extract SAOI Generator (Windows).zip
- Place the objects in a text file that contains the code of objects in pawn.

##### Example:
```
//do not create callbacks OnFilterScriptInit!
new tmpobj = CreateDynamicObject(10755,-124.5100000,125.7300000,261.8080100,0.0000000,0.0000000,89.9990000,-1,-1,-1,800.0,800.0);
SetDynamicObjectMaterial(tmpobj,0,10817,"airportgnd_sfse","black64",0x00000000);
SetDynamicObjectMaterial(tmpobj,1,10817,"airportgnd_sfse","black64",0x00000000);
SetDynamicObjectMaterial(tmpobj,2,10817,"airportgnd_sfse","black64",0x00000000);
SetDynamicObjectMaterial(tmpobj,3,10817,"airportgnd_sfse","black64",0x00000000);

//additional
SAOI::SetPositionFlag(MY_SAOI_FILE,1025.1938,1356.8513,10.8377,183.2121,0,0);

SAOI::SetBumperIP(MY_SAOI_FILE,"127.0.0.1");
SAOI::SetBumperPort(MY_SAOI_FILE,7777);

//example for RemoveBuildingForPlayer
//LV-LOT Old Gate
RemoveBuildingForPlayer(playerid,8311,1277.0,1206.8,12.9,1.0);
RemoveBuildingForPlayer(playerid,8312,1277.0,1206.8,12.9,1.0);

//example for area
new tmp_area = CreateDynamicCircle(911.87738,-671.97540,150.0);
CreateDynamicObject(869,911.87738,-671.97540,115.60636,-12.96000,-38.52000,0.00000,0,0,.areaid=tmp_area);
```

- Place the file in the folder "pawn_code"
- Run saoi.cmd
- Enter the full name of the file (example: file.txt)
- Enter data: Author (max 32 character), Version (max 32 character), Description (max 128 character)
- Submit and wait until the converter will create a file .saoi
- Use SAOI_FileManager.pwn


## How to install SAOI_FileManager:
- Create folder scriptfiles\SAOI


## How to fast import files to boot:
- Create file scriptfiles\SAOI\SaoiFiles.txt
- Place the file name is in the file SaoiFiles.txt

##### Example:
```
text.saoi
myobject.saoi
```


## SAOI_FileManager Commands:
- /saoicmd - show saoi cmd


## Videos:
- [SAOI File Generator](https://www.youtube.com/watch?v=M_WiwgS-Kqk)
- [SAOI File Manager v1.9](https://www.youtube.com/watch?v=tcJitQRub-E)

## Issues:
- RemoveBuildingForPlayer: When a saoi file is unloaded, online players will not see again removed buildings. They see them only after re-entering the server.

## Remote Control:
```
//GameMode/FilterScripts
forward SAOI_OnRemovedBuildings(playerid,buildings);
forward SAOI_OnVehicleDestroyed(vehicleid);
forward SAOI_OnVehicleCreated(vehicleid);
forward SAOI_IsAdmin(playerid);

//e.g. SAOI_ToggleVisibleItems("/SAOI/Wyspas.saoi",playerid,STREAMER_TYPE_OBJECT,0);
stock SAOI_ToggleVisibleItems(const name[],playerid,type,toggle){
	return CallRemoteFunction("SAOI_ToggleVisibleItems","sddd",name,playerid,type,toggle);
}

public SAOI_OnRemovedBuildings(playerid,buildings){

	return 1;
}

public SAOI_OnVehicleDestroyed(vehicleid){

	return 1;
}

public SAOI_OnVehicleCreated(vehicleid){

	return 1;
}

public SAOI_IsAdmin(playerid){
	//you code
	//don't need add rcon admin
	//return 1 if admin, 0 if not
}
```