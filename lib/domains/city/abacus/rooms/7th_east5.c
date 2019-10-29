#include "../area.h"

inherit "/std/room";

void setup(void){

	set_light(1);
	set_short("7th avenue east");
	set_long("You walk along the 7th avenue.\n"+
		"The ground gets slopes rather steep to the\n"+
		"east from here. The avenue continues\n"+
		"east and west.\n");
	add_exit("west", ROOMS + "7th_east4");
	add_exit("east", ROOMS + "7th_east6");
}
