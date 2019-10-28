inherit "std/room";
#include "../area.h"

void setup(void)
{
  set_outdoors(1);
  set_light(1);
  set_short("At the south part of Independance street");
 
  set_long_f("This is the very south part of Independence street. "+
	     "The street continues to the north while the intersection "+
	     "with West street is to the south.");

  add_exit("north",ROOM+"ind_street3");
  add_exit("south",ROOM+"west_street2");
}
