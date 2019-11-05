#include "../area.h"

inherit "std/room";

void setup(){
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("A bend in an avenue");
	set_long("The avenue bends round here, going from the west to the north.");
	
	add_item("avenue", "It bends here, from west to north");
	
	set_exits((["north" : ROOMS+"avenue2",
				"west" : ROOMS+"avenue4"]));
}

