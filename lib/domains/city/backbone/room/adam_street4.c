/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Adams street");
  set_long_f("You're standing on Adams street.\n"+
    "To the north you see the 7th avenue.\n"+
    "To your east you see the lights from the city.\n", 78);
  add_item("avenue", "It's a wide avenue running east and west through the village");
  add_item("lights", "You see the illuminate light from the buildings in the city");
  add_exit("south", ROOM+"adam_street3");
  add_exit("north", ROOM+"adam_street5");
   

}
