
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("7th avenue east");
  set_long_f("You stand on the 7th avenue east from the Eden street.\n"+
    "There is a large crossing to the west and the \n"+
    "avenue continues east.\n", 78);
  add_exit("west", ROOM+"eden5");
  add_exit("east", ROOM+"7th_east2");
   

}
