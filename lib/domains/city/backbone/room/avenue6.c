
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("End of the avenue");
  set_long_f("This is the end of the 7th avenue, the road turning\n"+
    "to the south here. You can see a big red thing to the west.\n", 78);
  add_item("avenue", "It's the road");
  add_item("road", "It's the avenue");
  add_exit("east", ROOM+"avenue5");
  add_exit("south", ROOM+"adam_street6");
  add_exit("west", "domains/Gangs/Tenno/room/entrance");
   

}
