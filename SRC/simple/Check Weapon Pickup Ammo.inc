/*
#include <ADM/StreamerFunction>
*/

forward CheckPlayerWeaponPickup(playerid,pickupid); //OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP:pickupid);

public CheckPlayerWeaponPickup(playerid,pickupid){
	if(GetDynamicPickupType(pickupid) == 2){
		switch(GetDynamicPickupModel(pickupid)){
		
			//Slot 0
			case 331: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,0,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 1
			case 333..339, 341: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,1,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 2
			case 346..348: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,2,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 3
			case 349..351: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,3,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 4
			case 352..353, 372: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,4,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 5
			case 355..356: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,5,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 6
			case 357..358: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,6,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 7
			case 359..362: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,7,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 8
			case 342..344, 363: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,8,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 9
			case 365..367: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,9,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 10
			case 321..326: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,10,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 11
			case 368..369, 371: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,11,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 12
			case 364: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,12,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
		}
	}
	return 1;
}