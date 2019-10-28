
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("the eden street");
  set_long_f("You stand on Eden streets northern parts.\n"+
    "To the north the street continues up on a hill\n"+
    "and it slopes downwards to the south.\n", 78);
  add_exit("south", ROOM+"eden6");
  add_exit("north", ROOM+"eden8");
   

}
