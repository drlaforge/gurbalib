
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("An avenue");
  set_long_f("This is an avenue in one of the more remote parts of the\n"+
    "city centre. There is an old church to the north.\n", 78);
  add_item("avenue", "An avenue");
  add_exit("east", ROOM+"avenue1");
  add_exit("south", ROOM+"avenue3");
  add_exit("north", "domains/Gangs/Inq/room/church2");
   

}
