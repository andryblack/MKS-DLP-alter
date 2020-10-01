#ifndef __languages_H
#define __languages_H

#include "includes.h"
#include "main.h"


#define	LNG_LANGS_COUNT		(uint8_t)2


typedef enum 
{
	LSTR____ = (uint32_t)0,
	LSTR_TESTSTRING,

// abbreviation
	LSTR_SHORT_MONDAY,
	LSTR_SHORT_TUESDAY,
	LSTR_SHORT_WEDNESDAY,
	LSTR_SHORT_THURSDAY,
	LSTR_SHORT_FRIDAY,
	LSTR_SHORT_SATURDAY,
	LSTR_SHORT_SUNDAY,
	
	LSTR_SHORT_JANUARY,
	LSTR_SHORT_FEBRUARY,
	LSTR_SHORT_MARCH,
	LSTR_SHORT_APRIL,
	LSTR_SHORT_MAY,
	LSTR_SHORT_JUNE,
	LSTR_SHORT_JULY,
	LSTR_SHORT_AUGUST,
	LSTR_SHORT_SEPTEMBER,
	LSTR_SHORT_OCTOBER,
	LSTR_SHORT_NOVEMBER,
	LSTR_SHORT_DECEMBER,
	
	LSTR_SHORTHOUR,
	LSTR_SHORTMINUTE,
	LSTR_SHORTSECOND,
	LSTR_SHORTMILLIMETERS,
	LSTR_SHORTMILLILITERS,
	LSTR_MM_MIN,
	LSTR_MM_SEC,
	LSTR_MM_SEC2,
	LSTR_KB,
	LSTR_MB,

	LSTR_ON_CAPS,
	LSTR_OFF_CAPS,

// Screen captions
	LSTR_BACK,
	LSTR_MAINMENU,
	LSTR_PRINT,
	LSTR_SERVICE,
	LSTR_INFO,
	LSTR_LANGUAGE,
	LSTR_MOVEZ,
	LSTR_UVTEST,
	LSTR_SETTINGS_FULL,
	LSTR_FILEVIEW_CAPTION,
	LSTR_PRINTING_CAPTION,
	LSTR_CLOCKSET_CAPTION,

	LSTR_SETTINGS_SHORT,
	
// Info screen
	LSTR_VERSION,
	LSTR_LIGHT_TIME,
	LSTR_DISPLAY_TIME,
	LSTR_FAN_TIME,
	LSTR_TOTALPRINT_TIME,
	LSTR_URL,
	LSTR_UIAUTHOR,
	
// Move Z screen
	LSTR_005MM,
	LSTR_02MM,
	LSTR_1MM,
	LSTR_10MM,
	LSTR_30MM,
	LSTR_MOVEHOME,
	LSTR_SETZ0,
	LSTR_STOPMOVE,
	
// Message box captions
	LSTR_WARNING,
	LSTR_ERROR,
	LSTR_CONFIRM_ACT,
	LSTR_WAIT,
	LSTR_COMPLETED,
// Message box buttons
	LSTR_OK,
	LSTR_CANCEL,
	LSTR_YES,
	LSTR_NO,
// Message box texts
	LSTR_MSG_HOME_FIRST,
	LSTR_MSG_ENDSTOP_NOT_FOUND,
	LSTR_MSG_ENDSTOP_ERROR,
	LSTR_MSG_CFGFILE_LOAD_QUEST,
	LSTR_MSG_CFGFILE_LOADING,
	LSTR_MSG_FILE_OPEN_ERROR,
	LSTR_MSG_CFGFILE_LOADED,
	LSTR_MSG_UNKNOWN_SECTNAME_IN_CFG,
	LSTR_MSG_UNKNOWN_PARAMNAME_IN_CFG,
	LSTR_MSG_INVALID_PARAMVAL_IN_CFG,
	LSTR_MSG_SURE_NO_MODEL_ON_PLATFORM,
	LSTR_MSG_SAVING_SETTINGS,
	LSTR_MSG_SET_CURRENT_Z0_QUEST,
	LSTR_MSG_SET_CURRENT_Z0_SUCCESS,
	LSTR_MSG_PRINT_COMPLETED,
	LSTR_MSG_PRINT_CANCEL_QUEST,
	LSTR_MSG_PRINT_CANCELING,
	LSTR_MSG_PRINT_CANCELED,
	LSTR_MSG_MODEL_TOO_HIGH,
	LSTR_MSG_DELETE_FILE_QUEST,
	LSTR_MSG_ERROR_DELETING_FILE,
	LSTR_MSG_FILE_DELETED,

// Settings screen
	LSTR_CLOCK,
	LSTR_LIFT_ON_PAUSE,
	LSTR_LIFT_ON_COMPLETION,
	LSTR_BUZZER,
	LSTR_ON,
	LSTR_OFF,

// Numpad screen
	LSTR_AC,

// Fileview screen
	LSTR_FILESIZE,
	LSTR_FILETIME,
	LSTR_TOTAL_LAYERS,
	LSTR_PRINT_TIME,
	LSTR_LAYER_THICKNESS,
	LSTR_ANTIALIASING,
	LSTR_TIME_LIGHT,
	LSTR_TIME_BOTTOM_LIGHT,
	LSTR_TIME_PAUSE_LIGHT,
	LSTR_LIFT_HEIGHT,
	LSTR_LIFT_SPEED,
	LSTR_DROP_SPEED,
	LSTR_RESIN_VOLUME,
	LSTR_IND_LAYERS_SETTINGS,

// Printing screen
	LSTR_TIME,	
	LSTR_LAYERS,	
	LSTR_PRINTING_CAPS,	
	LSTR_PAUSE_CAPS,	

// Clock set screen
	LSTR_CLOCK_HOURS_NAME,
	LSTR_CLOCK_MINUTES_NAME,
	LSTR_CLOCK_DAY_NAME,
	LSTR_CLOCK_MONTH_NAME,
	LSTR_CLOCK_YEAR_NAME,

// UV Test screen
	LSTR_UVTEST_LIGHT,
	LSTR_UVTEST_DISPLAY,
	LSTR_IMAGE_LOADING,

// Printing parameters screen
	LSTR_PP_PRINTING_PARAMETERS,
	LSTR_PP_LIGHT_BOTTOM,
	LSTR_PP_LIGHT,
	LSTR_PP_LIFT_HEIGHT,
	LSTR_PP_LIFT_SPEED,
	LSTR_PP_DROP_SPEED,
	LSTR_PP_LIGHT_PAUSE,
	LSTR_PP_AA,
	LSTR_PP_IND_SETTINGS,


	_LSTR_LASTITEM,

	_LSTR_MAXITEM = 0xFFFFFFFF
} LNG_STRING_ID;


typedef struct
{
	char		*name;
	char		**strings;
} LNG_LANGUAGE;




char*		LANG_GetString(LNG_STRING_ID id);
char*		LANG_GetLanguageName(uint8_t lang);
void		LANG_SetLanguage(uint8_t lang);
uint8_t		LANG_GetLanduagesCount();





#endif /*__languages_H */

