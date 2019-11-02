#include "../area.h"

inherit "std/room";

void setup(void) {
	
    set_short("in an alley");
	set_long("You stand in a dark alley.\n"+
		"The alley continues north-south.\n");
		
	add_exit("north", ROOMS + "alley_02");
	add_exit("south", ROOMS + "alley_04");
	
    add_item("alley","It's dark and gloomy");
}

