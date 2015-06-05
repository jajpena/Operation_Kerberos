/*
	Author: Dorbedo

	Description:
	Creates Mission "Return to Base".
	
	Parameter(s):
		0 :	ARRAY - Position der letzten AO
		
	Returns:
	BOOL
*/
#include "script_component.hpp"
CHECK(!isServer)
PARAMS_1(_position);
private["_ort","_position_rescue","_pow"];
_position_home = getMarkerPos "respawn_west";

//////////////////////////////////////////////////
////// Nachricht anzeigen 					 /////
//////////////////////////////////////////////////

[-1,{["rtb",1] call FM(disp_localization)}] FMP;

//////////////////////////////////////////////////
////// Überprüfung + Ende 					 /////
//////////////////////////////////////////////////

#define INTERVALL 15
#define CONDITION {_a=0;{If (_x distance (_this select 0) < 300) then {_a=_a+1;};} forEach playableUnits;If (_a == (count playableUnits)) then {true}else{false};}
#define CONDITIONARGS [_position_home]
#define SUCESSCONDITION {true}
#define ONSUCESS {LOG('Alle zurückgekehrt');[-1,{['rtb',2] call FM(disp_localization);}] FMP;[_position, 2000] spawn FM(cleanup_big);}
[INTERVALL,CONDITION,CONDITIONARGS,SUCESSCONDITION,ONSUCESS] call FM(taskhandler);

LOG("Exit RTB");