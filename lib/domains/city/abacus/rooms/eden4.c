
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Eden street");
  set_long_f("You are walking along the Eden street\n"+
    "The street continues north and south.\n", 78);
  add_exit("south", ROOM+"eden3_2");
  add_exit("north", ROOM+"eden5");
   

}
