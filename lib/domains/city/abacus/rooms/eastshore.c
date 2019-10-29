
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("The shore of Nukelake");
  set_long_f("East street comes to an end here at the shore of the great Nukelake.\n"+
    "The waves roll high to the east but the street continues westwards.\n", 78);
  add_item("waves", "Large radiocative waves.");
  add_item("shore", "The shore of Nukelake.");
  add_item("nukelake", "A large and deep radioactive lake.");
  add_exit("west", ROOM+"east_street1");
   

}
