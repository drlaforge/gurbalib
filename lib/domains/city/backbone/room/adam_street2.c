/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Adams street");
  set_long_f("You're walking down Adams street.\n"+
    "To the east you see the buildings of the city.\n"+
    "Far to the west you see the enormous mountains.\n", 78);
  add_item("buildings", "You see the high rising sky scrapers of the city to your east");
  add_item("mountains", "You see the wide mountain range far west from here");
  add_exit("north", ROOM+"adam_street3");
  add_exit("south", ROOM+"adam_street1");
   

}
