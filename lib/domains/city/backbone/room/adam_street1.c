/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Adams street");
  set_long_f("You're walking on Adams street.\n"+
    "This is the west most part of the city.\n"+
    "You see the scrapers of the town to your east.\n", 78);
  add_item("scrapers", "You see the high rising scrapers, inside the core of the town,\n"+
    "to your east\n");
  add_exit("north", ROOM+"adam_street2");
  add_exit("south", ROOM+"west_street4");
   

}
