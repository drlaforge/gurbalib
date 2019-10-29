#include "../area.h"
inherit "std/room";

void setup(void){
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("Adams street");
	set_long("You're standing on Adams street.\n"+
			 "To the north you see the 7th avenue.\n"+
			 "To your east you see the lights from the city.\n");
	add_item("avenue", "It's a wide avenue running east and west through the village");
	add_item("lights", "You see the illuminate light from the buildings in the city");
	set_exits((["south" : ROOMS+"adam_street3",
				"north" : ROOMS+"adam_street5"]));
}

