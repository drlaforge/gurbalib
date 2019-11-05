#include "../area.h"

inherit "std/room";


void setup(){
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("Part of the old city");
	set_long("This avenue forms part of the old city, the bulk of\n"+
		"which sprawls to the south, and the south-east.\n"+
		"Not much remains though, since the holocaust.\n");
	
	add_item("city", "The city lies to the south mainly");
	add_item("old city", "The city lies to the south mainly");
		
		set_exits((["east" : ROOMS+"avenue3",
					"west" : ROOMS+"avenue5"]));
}

