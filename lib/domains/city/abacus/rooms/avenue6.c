/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

inherit "std/room";
#include "../area.h"

void setup(){
  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("End of the avenue");
  set_long("This is the end of the 7th avenue, the road turning\n"+
    "to the south here. You can see a big red thing to the west.\n");
  add_item("avenue", "It's the road");
  add_item("road", "It's the avenue");
  set_exits((["east" : ROOMS+"avenue5",
  "south" : ROOMS+"adam_street6",
  "west" : "domains/Gangs/Tenno/room/entrance"]));
}

