#include "../area.h"

inherit "std/room";


void setup(void) {
	
	set_light(1);
	set_short("a dark alley");
	set_long("The dark alley ends here.\n"+
            "The walls rise mightily above you and you feel very small.\n"+
			"Worms and rats are crawling in the dirty corners of the\n"+
            "alley. You don't feel welcome around here.\n");
	
	add_exit("west", ROOMS + "alley2");
	
	add_item("rat","A disgusting rat","rats","Some disgusting rats");
	add_item("worm","A slimy bloodworm","worms","Some slimy bloodworms");
    add_item("wall","walls", "The walls seems to lean over above you and tell you to leave");
}
