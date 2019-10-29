
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("A crossing");
  set_long_f("You are in a big crossing with several traffic lights.\n"+
    "The 7th avenue leads west and east and the Eden street\n"+
    "leads north and south.\n", 78);
  add_item("lights", "A post with three lights with different colours");
  add_item("traffic lights", "A post with three lights with different colours");
  add_exit("west", ROOM+"7th_west1");
  add_exit("south", ROOM+"eden4");
  add_exit("north", ROOM+"eden6");
  add_exit("east", ROOM+"7th_east1");
   

}
