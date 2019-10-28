
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("eden street");
  set_long_f("You stand on the Eden street.\n"+
    "There is a large crossing to the south. Further \n"+
    "north the street starts winding upwards.\n"+
    "The street continues north and south.\n", 78);
  add_exit("south", ROOM+"eden5");
  add_exit("north", ROOM+"eden7");
   

}
