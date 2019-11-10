#include "../area.h"

inherit STD_ROOM;

void setup(void) {
     
	/*set_outdoors(1);*/
    set_light(1);
    set_short("angels boulevard"); 
    set_long("The boulevard ends here, connecting to\n"+
		"the 7th avenue. There are still a few machines\n"+
		"around, constructing new areas. You also see a sign,\n"+
		"pointing down along a broad stairway. The 7th avenue is\n"+
		"north from here and the boulevard continues south.\n");
    set_exits(([
	"north" : ROOMS + "7th_east2",
    "south" : ROOMS + "boul5",
		]));
    
	add_item{"machines","The machines are used when building houses",
	      "&The machines sound awful.","@You feel the smell of oil "+
	      "and grease fill your nose.","sign","The sign is pointing"+
	      " down and says: Subway!");
	add_item("stairway","stairs", "It's a long and broad set of stairs");
}

/*add Sign*/