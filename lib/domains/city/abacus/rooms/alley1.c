
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("the beginning of a dark alley");
  set_long_f("You are in the beginning of a dark alley. Your body\n"+
    "throws long pale shadows on the ground. A sign on the\n"+
    "wall says: 'Keep out! This domain belongs to the Devils, the\n"+
    "warriors of the street.' The alley continues to the north.\n"+
    "The west steet is to the south.\n", 78);
  add_readable("sign");
  add_item("sign", "A dirty sign with the text: 'Keep out! This domain belongs to the\n"+
    "Devils, the Warriors of the Street!'");
  add_exit("south", ROOM+"west_streetend");
  add_exit("north", ROOM+"alley2");

}
