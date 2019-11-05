#include "../area.h"

inherit "/std/room";

void setup(){

  set_short("a dark alley");
  set_long("The alley gets even darker.\n"+
    "A enormous wall rises in front of you to the north and bars\n"+
    "your way, but you can see a gloomy backyard to the west. You\n"+
    "really start asking yourself if you made the right choice\n"+
    "intruding into this domain. The alley continues to the south.\n");
  add_item("wall", "A huge threatening cement wall");
  add_item("backyard", "You can't see it that good from here");
  add_exit("west", ROOMS +"backyard");
  add_exit("south", ROOMS +"alley2");

}
