/*
#include <ADM/3DTryg>
*/


CMD:petrolcap(playerid){ 
	new vid = GetPlayerVehicleID(playerid), 
		Float:x, Float:y, Float:z, Float:rx, Float:rz, 
		Float:vx, Float:vy, Float:vz, Float:angle;
	 
	GetVehiclePos(vid,vx,vy,vz); 
	GetVehicleZAngle(vid,angle); 
	GetVehicleModelInfo(GetVehicleModel(vid),VEHICLE_MODEL_INFO_PETROLCAP,x,y,z); 

	if(Tryg3D::GetRotationFor2Point3D(0.0,0.0,0.0,x,y,z,rx,rz)){ 
		new Float:dist = VectorSize(x,y,z) + 1.0; 
		Tryg3D::GetPointInFront3D(vx,vy,vz,rx,CompRotationFloat(angle+rz),dist,x,y,z);
		SetPlayerCheckpoint(playerid,x,y,z,3.0); 
	} else { 
		//doesn't have petrolcap (0.0,0.0,0.0) 
	} 
	return 1; 
}