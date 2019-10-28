
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("the eden street");
  set_long_f("You are standing on Eden street on a hill.\n"+
    "To the south you can view the crossing with \n"+
    "7th avenue. Further north, the street seems\n"+
    "to come to an end.\n", 78);
  add_exit("south", ROOM+"eden7");
  add_exit("north", ROOM+"eden9");
   

}
