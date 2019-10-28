
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Part of the old city");
  set_long_f("This avenue forms part of the old city, the bulk of\n"+
    "which sprawls to the south, and the south-east.\n"+
    "Not much remains though, since the holocaust.\n", 78);
  add_item("city", "The city lies to the south mainly");
  add_item("old city", "The city lies to the south mainly");
  add_exit("east", ROOM+"avenue3");
  add_exit("west", ROOM+"avenue5");
   

}
