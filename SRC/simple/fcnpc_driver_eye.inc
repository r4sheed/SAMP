/*
1. NPC need attached sphere
2. on npc update you check first if player is in sphere then next if player is in SphericalSectorEx
3. other conditions you can understand i think
4. NPC have options for random send local message to player (like leave this road nigga), npc can call police after waiting to long or can call to Roadside assistance if is blocked by vehicle
for detect vehicle collision you need add

Tryg3D::InitVehicleCollision(); //OnGameModeInit / OnFilterScriptInit
*/

SetTimerEx("example",true,1000);


new npc_rec[32], buffer[256];
for(new i = 0; i < MAX_BUS_DRIVER; i++){
	KierowcaAutokaru[i] = FCNPC::Create(bus_data[i][n_name]);
	PInfo[KierowcaAutokaru[i]][playerTeam] = FACTION_KTP;
	format(npc_rec,sizeof(npc_rec),"busdriver_%d",bus_data[i][n_line]);
	Autokar[i] = CreateVehicle(437,bus_data[i][Bus_X],bus_data[i][Bus_Y],bus_data[i][Bus_Z],bus_data[i][Bus_A],0,0,0);
	ToggleVehicleCollision(Autokar[i],false);
	VInfo[Autokar[i]][vehicleCompany] = FACTION_KTP;
	UpdateVehicleText(Autokar[i]);
	OczyKierowcy[i] = CreateDynamicSphere(0.0,0.0,0.0,50.0,0,0);
	AttachDynamicAreaToVehicle(OczyKierowcy[i],Autokar[i]);
	FCNPC::Spawn(KierowcaAutokaru[i],61,bus_data[i][Bus_X],bus_data[i][Bus_Y],bus_data[i][Bus_Z]);
	FCNPC::PutInVehicle(KierowcaAutokaru[i],Autokar[i],0);
	FCNPC::SetInvulnerable(KierowcaAutokaru[i],true);
	if(bus_data[i][n_delay] == 0){
		FCNPC::StartPlayingPlayback(KierowcaAutokaru[i],npc_rec,_,true);
	} else {
		SetTimerEx("BUS_InitPlay",bus_data[i][n_delay],false,"dd",KierowcaAutokaru[i],i);
	}
	//ShowNPCInTabList(KierowcaAutokaru[i]);
	SetPlayerScore(KierowcaAutokaru[i],1000);
	SetPlayerColor(KierowcaAutokaru[i],0xFFFF00FF);
	SwitchVehicleEngine(Autokar[i],true);
	SwitchVehicleLight(Autokar[i],true);

	format(buffer,sizeof(buffer),"{00AAFF}[%d]\n{81E500}petruck.pl",bus_data[i][n_line]);
	CreateDynamic3DTextLabel(buffer,0xFFFFFFFF,0.0,0.0,1.0,25.0,INVALID_PLAYER_ID,Autokar[i]);
}
	
public example(){
	for(new i = 0; i < MAX_BUS_DRIVER; i++){
		if(!KierowcaAutokaruPlay[i]){
			FCNPC::OnUpdate(KierowcaAutokaru[i]);
		}
	}
}


public FCNPC::OnUpdate(npcid){
	new idx = -1;
	for(new i = 0; i < MAX_BUS_DRIVER; i++){
		if(npcid == KierowcaAutokaru[i]){
			idx = i;
			break;
		}
	}
	
	if(idx != -1){
		new Float:z_angle,
			Float:x,Float:y,Float:z,
			Float:px,Float:py,Float:pz;
		FCNPC::GetPosition(npcid,x,y,z);
		GetVehicleZAngle(Autokar[idx],z_angle);
		new ctp = 1;
		if(IsAnyPlayerInDynamicArea(OczyKierowcy[idx])){
			foreach(new i : Player){
				if(IsPlayerInDynamicArea(i,OczyKierowcy[idx]) && GetPlayerVehicleID(i) != Autokar[idx]){
					GetPlayerPos(i,px,py,pz);
					if(Tryg3D::IsPointInSphericalSectorEx(px,py,pz,x,y,z,0.0,z_angle,15.0,VERTICAL_CAMERA_RADIUS,35.0) && !IsPlayerPaused(i)){
						if(KierowcaAutokaruPlay[idx]){
							if(FCNPC::GetSpeed(npcid) > 0.0){
								if(IsPlayerInAnyVehicle(i)){
									switch(random(5)){
										case 0: cmd_l(npcid,"ruszaj się !");
										case 1: cmd_l(npcid,"jak ty jeździsz penisie !");
										case 2: cmd_l(npcid,"no co jest, jazda...");
										case 3: cmd_l(npcid,"z drogi !!!");
										case 4: cmd_l(npcid,"wciskaj ten pedał gazu.");
									}
								} else {
									switch(random(3)){
										case 0: cmd_l(npcid,"jazda mi z ulicy !");
										case 1: cmd_l(npcid,"trzymaj się chodnika przechodniu...");
										case 2: cmd_l(npcid,"ruszaj się !");
									}
								}
							}
							FCNPC::PausePlayingPlayback(npcid);
							KierowcaAutokaruPlay[idx] = false;
							KierowcaAutokaruPauseTime[idx] = gettime() + 60 * 2;
						} else {
							if(KierowcaAutokaruPauseTime[idx] != 0 && gettime() > KierowcaAutokaruPauseTime[idx]){
								if(PInfo[i][playerTeam] != FACTION_POLICE && PInfo[i][playerTeam] != FACTION_WOJ){
									if(GetPlayerWantedLevel(i) == 0){
										SetPlayerWantedLevel(i,1);
										Scigany(i);
										if(ctp){
											ctp = 0;
											new buffer[144];
											format(buffer,sizeof(buffer),"# {FF0000}%s [%i] wzywa Policje",PInfo[npcid][playerName],npcid);
											SendClientMessageToFaction(FACTION_POLICE,buffer);
											KierowcaAutokaruPauseTime[idx] = gettime() + 60 * 2;
										}
									}
								}
							}
						}
						return 1;
					}
				}
			}
		}
		//GetPointInFront3D(x,y,z,0.0,z_angle,4.0,px,py,pz);
		Tryg3D::GetPointInFrontOfVehicle3D(Autokar[idx],x,y,z,6.5);
		Tryg3D::GetPointInFrontOfVehicle3D(Autokar[idx],px,py,pz,8.0);
		new Float:T3D:x,Float:T3D:y,Float:T3D:z;
		if(Tryg3D::MovePointColWithVehicle(x,y,z,px,py,pz,T3D:x,T3D:y,T3D:z) != INVALID_VEHICLE_ID){
			if(KierowcaAutokaruPlay[idx]){
				if(FCNPC::GetSpeed(npcid) > 0.0){
					cmd_l(npcid,"Auto na drodze!");
				}
				FCNPC::PausePlayingPlayback(npcid);
				KierowcaAutokaruPlay[idx] = false;
				KierowcaAutokaruPauseTime[idx] = gettime() + 30;
			} else {
				if(KierowcaAutokaruPauseTime[idx] != 0 && gettime() > KierowcaAutokaruPauseTime[idx]){
					new buffer[144];
					format(buffer,sizeof(buffer),"# {FF0000}%s [%i] wzywa Pomoc Drogową",PInfo[npcid][playerName],npcid);
					SendClientMessageToFaction(FACTION_PD,buffer);
					KierowcaAutokaruPauseTime[idx] = gettime() + 60;
				}
			}
			return 1;
		}
		
		if(!KierowcaAutokaruPlay[idx]){
			FCNPC::ResumePlayingPlayback(npcid);
			KierowcaAutokaruPlay[idx] = true;
			KierowcaAutokaruPauseTime[idx] = 0;
		}
		return 1;
	}
	return 1;
}