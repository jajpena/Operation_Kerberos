/*
	Author: iJesuz
	
	Description:
		Erstellt ein gesunkenes SDV mit Wachen

	Parameter(s):
		0 : Array - Position
		1 : Array of String - [Sidetaskname, Taskname]
*/
#include "script_component.hpp"

private ["_position", "_task_array", "_sdv", "_enemyPos", "_i", "_radius", "_dir", "_enemys", "_description", "_boat"];

params ["_position", "_task_array"];

#ifdef TEST
	_position = getMarkerPos "spawn_side";
#endif

_sdv = "B_SDV_01_F" createVehicle [-100,-100,0];
// _sdv enableSimulationGlobal false; // MP
_sdv enableSimulation false; // SP
_sdv setDamage 1;
uiSleep 5;
_sdv setVariable ["DORB_HAS_INTEL",true];
_sdv setVariable ["DORB_IS_TARGET",true];
_sdv setPosATL [_position select 0, _position select 1, 0];

[_position, 50, 0, 5] spawn FM(spawn_patrol_water);
[_position, 100, 1, 0] spawn FM(spawn_patrol_water);

fnc_SDVAction = {
	private ["_target", "_caller", "_id", "_task", "_main_task", "_pos"];
	_target = _this select 0;
	_caller = _this select 1;
	_id = _this select 2;
	_task = _this select 3 select 0;
	_main_task = _this select 3 select 1;

	_target removeAction _id;

	if (_target getVariable ["DORB_HAS_INTEL", false]) then {
		_caller setVariable ["DORB_HAS_INTEL", true];
		_target setVariable ["DORB_HAS_INTEL", false];

		hint "Informationen wurden vom Computer des SDV runtergeladen!";

		[0, {
			private ["_pos","_caller","_main_task"];
			params ["_caller","_main_task"];
			_pos = getMarkerPos "respawn_west";
			while { (_pos distance (getPos _caller)) > 25 AND (_caller != objNull) AND (alive _caller)} do  {};
			
			[-1,{_this spawn FM(disp_info)},["Nebenmission",["abgeschlossen"],"",true]] FMP;	
			#ifdef TEST
				LOG("[SIDEBY] U-Boot abgeschlossen!");
				LOG(FORMAT_3("[SIDEBY] pos: %1, fehlpos: %2, durchmesser: %3", 3, 0, 50));
			#else
				[_task, "Succeeded", true] call BIS_fnc_taskSetState;
				[_main_task, "targets", [3, 50]] call FM(obj_reward);
			#endif
		}, [_caller,_main_task]] FMP;
	} else {
		hint "Es wurden keine Informationen gefunden.";
	};
};

_description = "Eines unserer U-Boote ist gesunken. An Bord befanden sich sensible Informationen. Bergen Sie diese und bringen Sie sie zurück zur Basis.";

[-1,{_this spawn FM(disp_info)},["Nebenmission",["gesunkenes U-Boot"],"",true]] FMP;
#ifdef TEST
	LOG("[SIDEBY] U-Boot erstellt!");
#else
	[_task_array, true, [_description, "gesunkenes U-Boot", "Bergen"], _position,"AUTOASSIGNED",0,false,true,"",true] spawn BIS_fnc_setTask;
#endif

[-1, {
	private["_sdv", "_task_array"];
	params["_sdv","_task_array"];
	_sdv addAction ["Take Intel", {_this call fnc_SDVAction;}, _task_array];
}, [_sdv,_task_array]] FMP;

DORB_MISSION_FNC = DORB_MISSION_FNC + [ [_sdv, _task_array], "(_this select 0) addAction ['Take Intel', {_this call fnc_SDVAction;}, _this select 1];" ];
publicVariable DORB_MISSION_FNC;
