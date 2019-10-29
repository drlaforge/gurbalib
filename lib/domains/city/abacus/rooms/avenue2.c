/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

inherit "std/room";
#include "../area.h"

void setup(){
  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("An avenue");
  set_long("This is an avenue in one of the more remote parts of the\n"+
    "city centre. There is an old church to the north.\n");
  add_item("avenue", "An avenue");
  set_exits((["east" : ROOMS+"avenue1",
  "south" : ROOMS+"avenue3",
  "north" : "domains/Gangs/Inq/room/church2"]));
}

