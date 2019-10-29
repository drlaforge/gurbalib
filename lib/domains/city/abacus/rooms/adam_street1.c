#include "../area.h"
inherit "std/room";

void setup(void){

	set_short("Adams street");
	set_long("You're walking on Adams street.\n"+
		"This is the west most part of the city.\n"+
		"You see the scrapers of the town to your east.\n");
	add_item("scrapers", "You see the high rising scrapers, inside the core of the town,\n"+
		"to your east\n");
		
	set_exits((["north" : ROOMS + "adam_street2",
				"south" : ROOMS + "west_street4"]));
}

