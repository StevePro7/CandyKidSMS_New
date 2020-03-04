// TODO - do I want to put this in the fixed bank??

#ifndef _LOCALE_MANAGER_H_
#define _LOCALE_MANAGER_H_

//#define LOCALE_BUILD_VERSION	"V1.0"

//#define LOCALE_TITLE1_TEXT		"CANDY"
//#define LOCALE_TITLE2_TEXT		" KID "
//
//#define LOCALE_HIGHS_TEXT		" HIGH"
//#define LOCALE_SCORE_TEXT		"SCORE"
//#define LOCALE_LIVES_TEXT		"LIVES"
//#define LOCALE_LEVEL_TEXT		"LEVEL"
//#define LOCALE_BOOST_TEXT		"BOOST"

//#define LOCALE_WORLD_TEXT		"WORLD"
//#define LOCALE_ROUND_TEXT		"ROUND"

//#define LOCALE_PLAY1_TEXT		"PLAY"
//#define LOCALE_MODES_TEXT		"MODE"

#define LOCALE_BLANK_WIDTH		"                          "
//#define LOCALE_BLANK_WIDTH		"12345678901234567890123456"
#define LOCALE_BLANK_SIZE8		"        "
//#define XYZCALE_BLANK_SIZE8		"12345678"
#define LOCALE_BLANK_SIZE17		"                 "
#define LOCALE_BLANK_SIZE18		"                  "

#define LOCALE_SELECT_ARROW		">"
#define LOCALE_SELECT_SPACE		" "

//#define LOCALE_PRESS_START		"PRESS START"
#define LOCALE_INSERT_COINS		"INSERT COIN(S)"


#define LOCALE_PRESS_CHEAT		"CHEAT!"
//#define LOCALE_PRESS_MODES		"MODE!"

#define LOCALE_TUTORIAL_NO		"00"

//#define LOCALE_SELECT_ENTRY		"SELECT BEGINNING"
//#define LOCALE_ENTRY_OPT1		"TUTORIAL"
//#define LOCALE_ENTRY_OPT2		"NEW GAME"

#define LOCALE_SELECT_TEXT		"SELECT"
#define LOCALE_SELECT_DIFF		"SELECT DIFFICULTY"
#define LOCALE_DIFF_EASY		"EASY"
#define LOCALE_DIFF_HARD		"HARD"

#define LOCALE_SELECT_PACE		"SELECT GAME SPEED"
#define LOCALE_PACE_SLOW		"SLOW"
#define LOCALE_PACE_FAST		"FAST"

#define LOCALE_SELECT_LEVEL		"SELECT LEVEL"
#define LOCALE_SELECT_WORLD		"WORLD"
#define LOCALE_SELECT_ROUND		"ROUND"

#define LOCALE_RESET_MESSAGE1	" RESET: "
#define LOCALE_RESET_MESSAGE2	" PLAYER "

#define LOCALE_PASS_MESSAGE1	"LEVEL IS"
#define LOCALE_PASS_MESSAGE2	"COMPLETE"
#define LOCALE_PASS_MESSAGE3	"PERFECT!"

#define LOCALE_BONUS_MESSAGE1	"SORRY NO"
#define LOCALE_BONUS_MESSAGE2	"BONUS :("
#define LOCALE_BONUS_MESSAGE3	"2000 PTS"
#define LOCALE_BONUS_MESSAGE4	"BONUS :)"

//#define LOCALE_DEAD_MESSAGE1	"AAAARGH!"
//#define LOCALE_DEAD_MESSAGE2	"YOU DIED"

#define LOCALE_CONT_MESSAGE		"CONTINUE"
#define LOCALE_CONT_YESORNO		" YES  NO"

#define LOCALE_GAME_MESSAGE1	"  GAME  "
#define LOCALE_GAME_MESSAGE2	"  OVER  "

#define LOCALE_BEAT_MESSAGE1	"CANDYKID"
#define LOCALE_BEAT_MESSAGE2	"  WINS  "

void engine_locale_manager_draw_text( unsigned char index, unsigned char x, unsigned char y );

#endif//_LOCALE_MANAGER_H_