#define MAINPREFIX x
#define PREFIX dorb

#include "\x\dorb\addons\main\script_version.hpp"

#define VERSION MAJOR.MINOR.PATCHLVL.BUILD
#define VERSION_AR MAJOR,MINOR,PATCHLVL,BUILD
#define VERSION_PLUGIN MAJOR.MINOR.PATCHLVL.BUILD

#define REQUIRED_VERSION 1.70
#define REQUIRED_CBA_VERSION {3,2,0}

#ifdef COMPONENT_BEAUTIFIED
    #define COMPONENT_NAME QUOTE(DORB - COMPONENT_BEAUTIFIED)
#else
    #define COMPONENT_NAME QUOTE(DORB - COMPONENT)
#endif

