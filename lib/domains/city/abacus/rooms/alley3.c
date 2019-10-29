
/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"



void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("a dark alley");
  set_long_f("The alley gets even darker.\n"+
    "A enormous wall rises in front of you to the north and bars\n"+
    "your way, but you can see a gloomy backyard to the west. You\n"+
    "really start asking yourself if you made the right choice\n"+
    "intruding into this domain. The alley continues to the south.\n", 78);
  add_item("wall", "A huge threatening cement wall");
  add_item("backyard", "You can't see it that good from here");
  add_exit("west", ROOM+"backyard");
  add_exit("south", ROOM+"alley2");

}
