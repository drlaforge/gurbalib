
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("A street");
  set_long_f("You walk along the Eden street leading\n"+
    "to a newly rebuilded part of the city.\n"+
    "To the east you can see the Abacus Central Bank and to the west is the Money Exchange office.\n"+
    "The street continues to the north.\n", 78);
  add_exit("south", ROOM+"east_square1");
  add_exit("north", ROOM+"eden2");
  add_exit("west", ROOM+"mexroom");
  add_exit("east", "domains/Areas/city/bank/lobby");
   

}
