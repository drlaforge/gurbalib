#include <ansi.h>
#include <config.h>

#define HAND ROOM+"poker/hand"

/*  board dimensions  *//*  (DO NOT CHANGE THESE, CODE DOES NOT SUPPORT IT) */#define WIDTH 8
#define HEIGHT 8
 
/*  returns from take_turn */#define COLUMN_FULL -1 
#define GAME_OVER -2 
#define GAME_TIED -3
                         
/*  icons represented by grid values */#define ICON ({ "  ", "##", "()", "XX", "[]" })
                          
#define DO(x) tell_object(me, x+"\n")   
