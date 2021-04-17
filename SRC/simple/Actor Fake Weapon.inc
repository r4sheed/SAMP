/*
#include <ADM/3DTryg>
*/

CreateDynamicActorWeapon(actorid,objectid,Float:offset_x,Float:offset_y,Float:offset_z,Float:rx,Float:ry,Float:rz){ 
	new Float:x,Float:y,Float:z,
		Float:tx,Float:ty,Float:tz,
		Float:angle; 

	GetDynamicActorPos(actorid,x,y,z); 
	GetDynamicActorFacingAngle(actorid,angle); 

	ShiftOffsetToPosition(x,y,z,0.0,0.0,angle,offset_x,offset_y,offset_z,tx,ty,tz);
	CreateDynamicObject(objectid,tx,ty,tz,rx,ry,CompRotationFloat(rz+angle)); 
}

CreateActorWeapon(actorid,objectid,Float:offset_x,Float:offset_y,Float:offset_z,Float:rx,Float:ry,Float:rz){ 
	new Float:x,Float:y,Float:z,
		Float:tx,Float:ty,Float:tz,
		Float:angle;

	GetActorPos(actorid,x,y,z); 
	GetActorFacingAngle(actorid,angle); 

	ShiftOffsetToPosition(x,y,z,0.0,0.0,angle,offset_x,offset_y,offset_z,tx,ty,tz);
	CreateDynamicObject(objectid,tx,ty,tz,rx,ry,CompRotationFloat(rz+angle)); 
}
