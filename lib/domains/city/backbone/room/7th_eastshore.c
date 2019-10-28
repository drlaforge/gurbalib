
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("the shore");
  set_long_f("The 7th avenue comes to an end here at the\n"+
    "shore of the great Nukelake. The waves rolls\n"+
    "high to the east but the avenue continues\n"+
    "westwards.\n", 78);
  add_exit("west", ROOM+"7th_east6");
   

}
