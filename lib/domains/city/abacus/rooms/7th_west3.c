#include "../area.h"

inherit "std/room"; 


void setup(){
	
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("7th avenue");
	set_long("You stand on the 7th avenue. The street\n"+
		"bends to the north here, and ends up in \n"+
		"a large parking place. The street also\n"+
		"continues east.\n");
	set_exits((["north" : ROOMS+"7th_westpark",
				"east" : ROOMS+"7th_west2"]));
}

