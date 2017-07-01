#include "\x\cba\addons\main\script_macros_common.hpp"
/* -------------------------------------------
Macros:
    CfgFunction Macros

Parameters:
    VAR - NAME

Author:
    Dorbedo
------------------------------------------- */

#define QPATHOF_FUNC(var1) QUOTE(\MAINPREFIX\PREFIX\SUBPREFIX\COMPONENT\functions\fnc_##var1)
#define QPATHOF_FUNC2(var1,var2) QUOTE(\MAINPREFIX\PREFIX\SUBPREFIX\COMPONENT\functions\##var1\fnc_##var2)

/* -------------------------------------------
Macro: MPATH(VAR)
    this marco is used to convert a missiopath for the description.ext

Parameters:
    VAR - NAME

Author:
    Dorbedo
------------------------------------------- */
#define MPATH(VAR) __EVAL(MISSION_ROOT + 'VAR')

/* -------------------------------------------
Macro: CHECK()
    Checks Condition - Exit if true

    Hint: no ';' after CHECK()

Parameters:
    CODE - Condition to Check

Example:
    (begin example)
        // if is server exit
        CHECK(isServer)
    (end)

Author:
    Dorbedo
------------------------------------------- */
#define CHECK(CONDITION) if (CONDITION) exitWith {};
#define CHECKRET(CONDITION,RETURN) if (CONDITION) exitWith {RETURN;};
/* -------------------------------------------
Macro: TILGE
    deletes:
        - Marker
        - Objects (vehicles incl Crew)
        - Groups
        - Arrays including these

Parameters:
    none

Example:
    (begin example)
        [veh1  ,  group1  ,  [ "Marker1" , "marker2" ]  ,  [ [ Veh2 ] , soldier1 ] , [ group2 ] ]     TILGE;
        [soldier3,soldier4] TILGE;
        "marker3" TILGE;
    (end)

Author:
    Dorbedo
------------------------------------------- */
#define TILGE call TRIPLES(dorb,common,DOUBLES(fnc,delete))
/* -------------------------------------------
Macro: SCRIPT(VAR)
   Sets name of script
   Overrides CBA "SCRIPT"
   adds _fnc_scriptName due to compatibility with BIS-System
Parameters:
    NAME - Name of script [Indentifier]

Example:
    (begin example)
        SCRIPT(boom);
    (end)

Author:
    Dorbedo
------------------------------------------- */
#ifdef PART
    #undef SCRIPT
    #define SCRIPT(NAME) \
    private _fnc_scriptName = QUOTE(DOUBLES(ADDON,TRIPLES(fnc,PART,NAME))); \
    scriptName _fnc_scriptName
#else
    #undef SCRIPT
    #define SCRIPT(NAME) \
    private _fnc_scriptName = QUOTE(TRIPLES(ADDON,fnc,NAME)); \
    scriptName _fnc_scriptName
#endif

/* -------------------------------------------
Macro: SCRIPTIN(VAR)
   Sets name of an inner script
   adds _fnc_scriptName due to compatibility with BIS-System
Parameters:
    NAME - Name of script [Indentifier]

Example:
    (begin example)
        SCRIPTIN(boom);
    (end)

Author:
    Dorbedo
------------------------------------------- */
#ifdef PART
    #define SCRIPTIN(NAME,NAME2) \
    private _fnc_scriptName = QUOTE(TRIPLES(ADDON,fnc,TRIPLES(fnc,NAME,NAME2))); \
    scriptName _fnc_scriptName
#else
    #define SCRIPTIN(NAME,NAME2) \
    private _fnc_scriptName = QUOTE(DOUBLES(ADDON,TRIPLES(fnc,NAME,NAME2))); \
    scriptName _fnc_scriptName
#endif

#ifndef INCLUDE_HEADER
    #define INCLUDE_HEADER 1
#endif
#ifdef DEBUG_MODE_NORMAL
    #define INCLUDE_HEADER 2
#endif
#ifdef DEBUG_MODE_FULL
    #define INCLUDE_HEADER 3
#endif
#ifdef DEBUG_MODE_OFF
    #define INCLUDE_HEADER 0
#endif
#define PATHTO_SYS_LONG(var1,var2,var3,var4) ##var1\##var2\##var3\##var4.sqf
/* -------------------------------------------
Macro: PREP(VAR)
   compiling functions
   file: COMPONENT\functions\fnc_VAR.sqf
   adding an header to the function if DEBUG_MODE_NORMAL enabled (COMPONENT WIDE)
Parameters:
    VAR - Name of file [Indentifier]

Example:
    (begin example)
        #define COMPONENT main
        PREP(test);

        Result: PREFIX_main_fnc_test = *compiled function*;
    (end)

Author:
    Dorbedo
------------------------------------------- */
#ifdef PREP
    #undef PREP
#endif
#define PREP(var1) ['\MAINPREFIX\PREFIX\addons\COMPONENT\functions\TRIPLES(fnc,var1,.sqf))', 'TRIPLES(ADDON,fnc,var1)',INCLUDE_HEADER] COMPILE_SYS
/* -------------------------------------------
Macro: PREPS(VAR1,VAR2)
   compiling functions
   file: COMPONENT\functions\VAR1\fnc_VAR2.sqf
   adding an header to the function if DEBUG_MODE_NORMAL enabled (COMPONENT WIDE)
Parameters:
    VAR1 - Name of PART
    VAR2 - Name of file [Indentifier]

Example:
    (begin example)
        #define COMPONENT main
        PREPS(player,test);

        Result: PREFIX_main_fnc_player_test = *compiled function*;
    (end)

Author:
    Dorbedo
------------------------------------------- */
#ifdef PREPS
    #undef PREPS
#endif
#define PREPS(var1,var2) ['\MAINPREFIX\PREFIX\addons\COMPONENT\functions\var1\TRIPLES(fnc,var2,.sqf))', 'TRIPLES(ADDON,fnc,DOUBLES(var1,var2))',INCLUDE_HEADER] COMPILE_SYS
/* -------------------------------------------
Macro: PREPMAIN(VAR)
   compiling functions
   file: COMPONENT\functions\fnc_VAR.sqf
   adding an header to the function if DEBUG_MODE_NORMAL enabled (COMPONENT WIDE)
Parameters:
    VAR - Name of file [Indentifier]

Example:
    (begin example)
        #define COMPONENT main
        PREPMAIN(test);

        Result: PREFIX_fnc_test = *compiled function*;
    (end)

Author:
    Dorbedo
------------------------------------------- */
#ifdef PREPMAIN
    #undef PREPMAIN
#endif
#define PREPMAIN(var1) ['\MAINPREFIX\PREFIX\addons\COMPONENT\functions\TRIPLES(fnc,var1,.sqf))', 'TRIPLES(PREFIX,fnc,var1)',INCLUDE_HEADER] COMPILE_SYS


#ifndef STRING_MACROS_GUARD
    #define STRING_MACROS_GUARD
    #define LSTRING(var1) QUOTE(TRIPLES(STR,ADDON,var1))
    #define ELSTRING(var1,var2) QUOTE(TRIPLES(STR,DOUBLES(PREFIX,var1),var2))
    #define CSTRING(var1) QUOTE(TRIPLES($STR,ADDON,var1))
    #define ECSTRING(var1,var2) QUOTE(TRIPLES($STR,DOUBLES(PREFIX,var1),var2))
#endif

/* -------------------------------------------
Macro(s): <PREFIX>POLAR_<POSTFIX>(PHI,RADIUS)
    prefix:
        non: arma-like polarcoordinates
             (angle between y-axis and radius)
        "N": normal polarcoordinates
             (angle between x-axis and radius)
    postfix:
        "X": x-value
        "Y": y-value
        "2D": 2D coordinate
        "3D": 3D coordinate (z = 0)

Parameters:
    0 : NUMBER
    1 : NUMBER

Example:
    (begin example)
        POLAR_3D(35,1)
    (end)

Author:
    iJesuz
------------------------------------------- */
#define POLAR_X(PHI,RADIUS) ((sin (PHI)) * (RADIUS))
#define POLAR_Y(PHI,RADIUS) ((cos (PHI)) * (RADIUS))
#define POLAR_2D(PHI,RADIUS) [POLAR_X(PHI,RADIUS),POLAR_Y(PHI,RADIUS)]
#define POLAR_3D(PHI,RADIUS) [POLAR_X(PHI,RADIUS),POLAR_Y(PHI,RADIUS),0]
#define NPOLAR_X(PHI,RADIUS) POLAR_Y(PHI,RADIUS)
#define NPOLAR_Y(PHI,RADIUS) POLAR_X(PHI,RADIUS)
#define NPOLAR_2D(PHI,RADIUS) [NPOLAR_X(PHI,RADIUS),NPOLAR_Y(PHI,RADIUS)]
#define NPOLAR_3D(PHI,RADIUS) [NPOLAR_X(PHI,RADIUS),NPOLAR_Y(PHI,RADIUS),0]

/* -------------------------------------------
Macro(s):
    ISCASVEHICLE(VAR)

    check if air-vehicle is a CAS vehicle

Parameters:
    CONFIGNAME - the type of the vehicle

Example:
    (begin example)
        ISCASVEHICLE('B_Heli_Attack_01_F')
        ISCASVEHICLE_C('B_Plane_CAS_01_F')
    (end)

Author:
    iJesuz
------------------------------------------- */

#define ISCASVEHICLE(ARG) [ARG, ["RHS_UH1Y_UNARMED"], ["RHS_UH1Y","rhsusf_f22","B_T_VTOL_01_armed_blue_F","B_T_VTOL_01_armed_F","B_T_VTOL_01_armed_olive_F"]] call EFUNC(whitelist,iscasvehicle)
#define ISCASVEHICLE_C(ARG) (ISCASVEHICLE(ARG))

/* -------------------------------------------
Macro: isHeadless
    Checks if function is called by HeadlessClient

Parameters:
    none

Example:
    (begin example)
        CHECK(isHC)
    (end)

Author:
    Dorbedo
------------------------------------------- */
#define isHeadless (!IsDedicated && !hasInterface)

/* -------------------------------------------
Macro:
    Some config helper

Parameters:
    none

Example:
    none

Author:
    Dorbedo
------------------------------------------- */
#define SOLDIER_SYS(VAR1,VAR2,VAR3,VAR4) class VAR1 { \
                            vehicle = QUOTE(VAR2); \
                            rank = QUOTE(VAR3); \
                            position[] = VAR4; \
                        };
#define SOLDIERR_1(TYPE,RANK) SOLDIER_SYS(soldier_1,TYPE,RANK,{ARR_3(0,0,0)})
#define SOLDIER_1(TYPE) SOLDIERR_1(TYPE,PRIVATE)
#define SOLDIERR_2(TYPE,RANK) SOLDIER_SYS(soldier_2,TYPE,RANK,{ARR_3(-1,-1,0)})
#define SOLDIER_2(TYPE) SOLDIERR_2(TYPE,PRIVATE)
#define SOLDIERR_3(TYPE,RANK) SOLDIER_SYS(soldier_3,TYPE,RANK,{ARR_3(1,-1,0)})
#define SOLDIER_3(TYPE) SOLDIERR_3(TYPE,PRIVATE)
#define SOLDIERR_4(TYPE,RANK) SOLDIER_SYS(soldier_4,TYPE,RANK,{ARR_3(-2,-2,0)})
#define SOLDIER_4(TYPE) SOLDIERR_4(TYPE,PRIVATE)
#define SOLDIERR_5(TYPE,RANK) SOLDIER_SYS(soldier_5,TYPE,RANK,{ARR_3(2,-2,0)})
#define SOLDIER_5(TYPE) SOLDIERR_5(TYPE,PRIVATE)
#define SOLDIERR_6(TYPE,RANK) SOLDIER_SYS(soldier_6,TYPE,RANK,{ARR_3(-3,-3,0)})
#define SOLDIER_6(TYPE) SOLDIERR_6(TYPE,PRIVATE)
#define SOLDIERR_7(TYPE,RANK) SOLDIER_SYS(soldier_7,TYPE,RANK,{ARR_3(3,-3,0)})
#define SOLDIER_7(TYPE) SOLDIERR_7(TYPE,PRIVATE)
#define SOLDIERR_8(TYPE,RANK) SOLDIER_SYS(soldier_8,TYPE,RANK,{ARR_3(-4,-4,0)})
#define SOLDIER_8(TYPE) SOLDIERR_8(TYPE,PRIVATE)
#define SOLDIERR_9(TYPE,RANK) SOLDIER_SYS(soldier_9,TYPE,RANK,{ARR_3(4,-4,0)})
#define SOLDIER_9(TYPE) SOLDIERR_9(TYPE,PRIVATE)
#define SOLDIERR_10(TYPE,RANK) SOLDIER_SYS(soldier_10,TYPE,RANK,{ARR_3(-5,-5,0)})
#define SOLDIER_10(TYPE) SOLDIERR_10(TYPE,PRIVATE)
#define SOLDIERR_11(TYPE,RANK) SOLDIER_SYS(soldier_11,TYPE,RANK,{ARR_3(5,-5,0)})
#define SOLDIER_11(TYPE) SOLDIERR_11(TYPE,PRIVATE)
#define SOLDIERR_12(TYPE,RANK) SOLDIER_SYS(soldier_12,TYPE,RANK,{ARR_3(-6,-6,0)})
#define SOLDIER_12(TYPE) SOLDIERR_12(TYPE,PRIVATE)
#define SOLDIERR_13(TYPE,RANK) SOLDIER_SYS(soldier_13,TYPE,RANK,{ARR_3(6,-6,0)})
#define SOLDIER_13(TYPE) SOLDIERR_13(TYPE,PRIVATE)
#define SOLDIERR_14(TYPE,RANK) SOLDIER_SYS(soldier_14,TYPE,RANK,{ARR_3(-7,-7,0)})
#define SOLDIER_14(TYPE) SOLDIERR_14(TYPE,PRIVATE)
#define SOLDIERR_15(TYPE,RANK) SOLDIER_SYS(soldier_15,TYPE,RANK,{ARR_3(7,-7,0)})
#define SOLDIER_15(TYPE) SOLDIERR_15(TYPE,PRIVATE)

/* -------------------------------------------
Macro: HASH-System
    Hash system - Original from ACRE2,
    was modified to make it fit with CBA and own system
    additional hash macros were created

Author:
    Dorbedo
Original Author:
    ACRE2(https://github.com/IDI-Systems/acre2)
------------------------------------------- */
#include "script_hashes.hpp"

/* -------------------------------------------
Macro: ACTIVEMOD_BW
    Checks if the Mod  is loaded

Parameters:
    none

Example:
    (begin example)
        If ACTIVEMOD_BW then ...
    (end)

Author:
    Dorbedo
------------------------------------------- */
#define ACTIVEMOD_ACRE (isClass(configFile >> "CfgPatches" >> "acre_main"))
#define ACTIVEMOD_BW (isClass(configFile >> "CfgPatches" >> "BWA3_Tracked"))

/* -------------------------------------------
Macro: LINKFUNC()
    recompiling helper

Parameters:
    none

Example:

Author:
    Dorbedo
------------------------------------------- */
#define LINKFUNC(VAR1) FUNC(VAR1)
#define LINKEFUNC(VAR1,VAR2) EFUNC(VAR1,VAR2)
