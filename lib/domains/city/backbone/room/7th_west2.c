
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("7th avenue west");
  set_long_f("You stand on the 7th avenue, west from\n"+
    "the Eden street. The avenue continues east and west.\n"+
    "To the south you see the flashing lights from Eve street.\n", 78);
  add_item("lights", "Throughout Eve street, neon lights light up the entire street");
  add_exit("west", ROOM+"7th_west3");
  add_exit("south", ROOM+"eve_street5");
  add_exit("east", ROOM+"7th_west1");
   

}
