
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("7th avenue");
  set_long_f("You stand on the 7th avenue. The street\n"+
    "bends to the north here, and ends up in \n"+
    "a large parking place. The street also\n"+
    "continues east.\n", 78);
  add_exit("north", ROOM+"7th_westpark");
  add_exit("east", ROOM+"7th_west2");
   

}
