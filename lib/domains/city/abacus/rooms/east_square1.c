/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

inherit "std/room";
#include "../area.h"

void setup(){
  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("East of City Centre Square");
  set_long("You are standing on an intersection between the main street of the\n"+
    "city and Eden avenue, which starts here and continues to the north.\n"+
    "As with the rest of the city, all of the buildings in this area are\n"+
    "desolate and neglected.\n");
  add_item("avenue", "It starts here and continues to the north.");
  add_item("Eden avenue", "It starts here and continues to the north.");
  add_item("main street", "The street goes from the east to the west.");
  add_item("buildings", "They look abandoned and empty.");
  add_item("street", "The street goes from the east to the west.");
  set_exits((["south" : ROOMS+"alley_01",
  "west" : ROOMS+"central_square",
  "north" : ROOMS+"eden1",
  "east" : ROOMS+"east_square2"]));
}

