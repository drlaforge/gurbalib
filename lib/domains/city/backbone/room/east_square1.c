
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("East of City Centre Square");
  set_long_f("You are standing on an intersection between the main street of the\n"+
    "city and Eden avenue, which starts here and continues to the north.\n"+
    "As with the rest of the city, all of the buildings in this area are\n"+
    "desolate and neglected.\n", 78);
  add_item("avenue", "It starts here and continues to the north.");
  add_item("Eden avenue", "It starts here and continues to the north.");
  add_item("main street", "The street goes from the east to the west.");
  add_item("buildings", "They look abandoned and empty.");
  add_item("street", "The street goes from the east to the west.");
  add_exit("south", ROOM+"alley_01");
  add_exit("west", ROOM+"central_square");
  add_exit("north", ROOM+"eden1");
  add_exit("east", ROOM+"east_square2");
   

}
