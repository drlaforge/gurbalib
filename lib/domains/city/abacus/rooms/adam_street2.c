#include "../area.h"
inherit "std/room";

void setup(void){
	
	set_light(1);
	set_short("Adams street");
	set_long("You're walking down Adams street.\n"+
		"To the east you see the buildings of the city.\n"+
		"Far to the west you see the enormous mountains.\n");
	add_item("buildings", "You see the high rising sky scrapers of the city to your east");
	add_item("mountains", "You see the wide mountain range far west from here");
	set_exits((["north" : ROOMS + "adam_street3",
				"south" : ROOMS + "adam_street1"]));
}

