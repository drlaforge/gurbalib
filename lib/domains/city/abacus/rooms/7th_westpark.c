#include "../area.h"

inherit "std/room/"; 


void setup(void){
  
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("The 7th avenue parking place");
	set_long("The 7th avenue ends up in a large parking place\n"+
		"here. It's a open area where those who have cars\n"+
		"are supposed to park them. The 7th avenue is to\n"+
		"the south and west.\n");
	set_exits((["west" : ROOMS + "avenue1",
				"south" : ROOMS + "7th_west3"]));
}

