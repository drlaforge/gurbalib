inherit "std/room";
#include "../area.h"

void setup(void)
{
  /*set_outdoors(1); */
  set_light(1);
  set_short("At the south part of Independance street");
  set_long("This is the very south part of Independence street. "+
	     "The street continues to the north while the intersection "+
	     "with West street is to the south.");
  set_exits((["north" : ROOMS+"ind_street3",
  "south" : ROOMS+"west_street2"]));
}

