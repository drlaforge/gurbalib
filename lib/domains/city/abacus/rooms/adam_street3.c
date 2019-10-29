#include "../area.h"
inherit "std/room";


void setup(void){

	set_light(1);
	set_short("Adams street");
	set_long("You're walking down Adams street.\n"+
		"To your west you see the wide mountains rise into the sky.\n"+
		"You see the lights from city to the east.\n"+
		"You see a sign saying 'McDonalds' to the west.\n");
	add_item("lights", "The light from the city illuminates the area in a yellowish light");
	add_item("light", "The light from the city illuminates the area in a yellowish light");
	add_item("mountains", "You see the wide mountain range far west from here");
	add_item("sign", "As you suspected, it says 'McDonalds'");
	set_exits((["north" : ROOMS + "adam_street4",
		"south" : ROOMS + "adam_street2",
		"west" : ROOMS + "macdonalds"]));
	
	set_objects(OBJ + "md_sign.c");
}

