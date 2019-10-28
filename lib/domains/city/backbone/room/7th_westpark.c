
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("The 7th avenue parking place");
  set_long_f("The 7th avenue ends up in a large parking place\n"+
    "here. It's a open area where those who have cars\n"+
    "are supposed to park them. The 7th avenue is to\n"+
    "the south and west.\n", 78);
  add_exit("west", ROOM+"avenue1");
  add_exit("south", ROOM+"7th_west3");
   

}
