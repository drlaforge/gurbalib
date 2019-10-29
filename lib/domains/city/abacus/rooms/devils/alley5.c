
inherit "std/room";
#include "../area.h"

void setup(void) {
  set_outdoors(1);
  set_light(1);
  short_desc = "a dark alley";
  long_desc="The dark alley ends here.\n"+
            "The walls rise mightily above you and you feel very small.\n"+
	    "Worms and rats are crawling in the dirty corners of the\n"+
            "alley. You don't feel welcome around here.\n";
  dest_dir=({
             ROOM+"alley2","west",
	   });
  items_arr=({
          "rat","A disgusting rat","rats","Some disgusting rats",
	  "worm","A slimy bloodworm","worms","Some slimy bloodworms",
          ({"wall","walls"}),
          "The walls seems to lean over above you and tell you to leave",
	  });
}
