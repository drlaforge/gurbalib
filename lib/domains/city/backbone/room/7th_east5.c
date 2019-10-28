
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("7th avenue east");
  set_long_f("You walk along the 7th avenue.\n"+
    "The ground gets slopes rather steep to the\n"+
    "east from here. The avenue continues\n"+
    "east and west.\n", 78);
  add_exit("west", ROOM+"7th_east4");
  add_exit("east", ROOM+"7th_east6");
   

}
