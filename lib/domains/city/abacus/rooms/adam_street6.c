/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

inherit "std/room";
#include "../area.h"

void setup(){
  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("Adams street");
  set_long("You're walking down Adams street.\n"+
    "To the east you see the buldings of the city.\n"+
    "Far to the west you see the enormous mountains.\n");
  add_item("buildings", "You see the high rising sky scrapers of the city to your east");
  add_item("mountains", "You see the wide mountain range far west from here");
  set_exits((["north" : ROOMS+"avenue6",
  "south" : ROOMS+"adam_street5"]));
}

