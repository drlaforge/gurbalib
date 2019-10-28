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
    "To your west you see the wide mountains rise into the sky.\n"+
    "You see the lights from city to the east.\n"+
    "You see a sign saying 'McDonalds' to the west.\n", 78);
  add_item("lights", "The light from the city illuminates the area in a yellowish light");
  add_item("light", "The light from the city illuminates the area in a yellowish light");
  add_item("mountains", "You see the wide mountain range far west from here");
  add_item("sign", "As you suspected, it says 'McDonalds'");
  add_readable("sign");
  add_exit("north", ROOM+"adam_street4");
  add_exit("south", ROOM+"adam_street2");
  add_exit("west", ROOM+"macdonalds");
}
