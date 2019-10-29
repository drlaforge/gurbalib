#include "../area.h"

inherit "std/room"; 


void setup(){
  
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("7th avenue west");
	set_long("You stand on the 7th avenue, west from\n"+
		"the Eden street. The avenue continues east and west.\n"+
		"To the south you see the flashing lights from Eve street.\n");
	add_item("lights", "Throughout Eve street, neon lights light up the entire street");
	set_exits((["west" : ROOMS + "7th_west3",
				"south" : ROOMS + "eve_street5",
				"east" : ROOMS + "7th_west1"]));
}

