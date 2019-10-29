inherit "std/room";
#include "../area.h"

void setup(void)
{
   
   

  (ROOM+"convoy/westConvoy.c")->foo();
  set_outdoors(1);
  set_light(1);

  short_desc = "gates to Ded City";

  set_long_f( 
    "You are right outside the gates to Ded City. This is the only opening in the "+
    "high wall surrounding Ded City, and it is often patrolled by Dedhed guards. "+
    "The gates are open, and it looks like they have not been closed for a long time. "+
    "All around you is burning desert. An old but well built road leads north and "+
    "south here. North looks completely desolate and south is the shimmering heat of "+
    "the Great Desert. All other directions look completely hostile and unpassable.\n");

  dest_dir = 
  ({
	"blah","north","#i_would_walk_500_miles",
	"/domains/Areas/desert/backbone/desert1","south",0,
  });

  items_arr = ({
    ({"opening","gates","gate"}),
    "The gates are open, and they haven't been closed for a long time",
    ({"wall","high wall","Ded City","ded city"}),
    "None of the houses of Ded City are visible because due to the high wall",
    ({"desert","burning desert","great desert","heat","shimmering heat"}),
    "A desert... sand... heat... what did you expect?",
    ({"road","old road","well built road"}),
    "The road leads north and south, and looks like it was once an interstate or similar"
  });

}

init()
{
  ::init();
  add_action("can_i_go_west",({"west","w"}));
}

can_i_go_west()
{
  if(present("guard",this_object()) && (!this_player()->query_npc()))
   {
     writef("The guard blocks your way into the village.\n");
     return 1;
   }
}

i_would_walk_500_miles()
{
  writef("You remember from the journey down that it is a very long way north before you "+
	"get anywhere. You decide it would be better just to wait for the APC to pick "+
	"you up.\n");
  return 1;
}
