/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

inherit "/std/room"; 
#include "../area.h"

/* todo: figure out how colors work in new lib
string spLong(){
return("You're walking down Eve street. The street is lit up by the lamps and neons\n"+
"light that continiously run throughout the hours of the day. The smell of bacon\n"+
"flows in from the east. To the west you see a particularly large sign stating:\n"+
    colour_string("[CASINO UNDER NEW MANAGEMENT!]", "CYAN", "General", TP)+"\n");

}
*I'll copy the desc without colors down into the long desc, will be fixed later
*/

void setup(){
	  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("Eve street - outside roulette");
  add_item("lamps", "The lamp post light up the street very effictively");
  add_item("neons", "You see flashing neon lights throughout the street");
  add_item("sign", "The sign shows the word ROULETTE in various flashing colors");
  add_exit("west", ROOMS+"casino/lobby");
  add_exit("south", ROOMS+"yard");
  add_exit("east", ROOMS+"bacon/mb");
  add_exit("north", ROOMS+"eve_street2");
   
  set_long("You're walking down Eve street. The street is lit up by the lamps and neons\n"+
"light that continiously run throughout the hours of the day. The smell of bacon\n"+
"flows in from the east. To the west you see a particularly large sign stating:\n"+
"[%^RED%^CASINO UNDER NEW MANAGEMENT!%^RESET%^]");
}

