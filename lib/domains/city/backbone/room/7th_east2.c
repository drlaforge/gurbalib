
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("7th avenue east");
  set_long_f("You are walking eastwards along the 7th\n"+
    "avenue. The street starts to slope to the east\n"+
    "here. The avenue continues east and west.\n", 78);
  add_exit("west", ROOM+"7th_east1");
  add_exit("south", ROOM+"boul6");
  add_exit("north", ROOM+"nangels1");
  add_exit("east", ROOM+"7th_east3");
   

}
