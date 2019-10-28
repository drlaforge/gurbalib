
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

string spLong(){
return("You're walking down Eve street. The street is lit up by the lamps and neons\n"+
"light that continiously run throughout the hours of the day. The smell of bacon\n"+
"flows in from the east. To the west you see a particularly large sign stating:\n"+
    colour_string("[CASINO UNDER NEW MANAGEMENT!]", "CYAN", "General", TP)+"\n");

}

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Eve street - outside roulette");
  add_item("lamps", "The lamp post light up the street very effictively");
  add_item("neons", "You see flashing neon lights throughout the street");
  add_item("sign", "The sign shows the word ROULETTE in various flashing colors");
  add_exit("west", ROOM+"casino/lobby");
  add_exit("south", ROOM+"yard");
  add_exit("east", ROOM+"bacon/mb");
  add_exit("north", ROOM+"eve_street2");
   
  set_long( spLong() );

}
