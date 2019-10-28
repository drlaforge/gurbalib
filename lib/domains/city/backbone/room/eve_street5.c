
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Eve street");
  set_long_f("You're standing on Eve street.\n"+
    "The street extends north and south\n"+
    "through the tall buildings on each side.\n"+
    "Further north you see the 7th avenue.\n", 78);
  add_item("buildings", "The buildings extend way up in the sky");
  add_exit("south", ROOM+"eve_street4");
  add_exit("north", ROOM+"7th_west2");
   

}
