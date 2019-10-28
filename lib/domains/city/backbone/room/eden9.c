
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("a dead end of edenstreet");
  set_long_f("You have come to the end of Eden street.\n"+
    "There is a round zone where the cars can turn\n"+
    "around here. The street continues to the south.\n", 78);
  add_exit("south", ROOM+"eden8");
   

}
