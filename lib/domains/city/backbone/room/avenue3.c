
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("A bend in an avenue");
  set_long_f("The avenue bends round here, going from the west to the north.", 78);
  add_item("avenue", "It bends here, from west to north");
  add_exit("north", ROOM+"avenue2");
  add_exit("west", ROOM+"avenue4");
   

}
