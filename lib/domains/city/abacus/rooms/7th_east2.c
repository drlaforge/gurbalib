#include "../area.h"

inherit "/std/room"; 

void setup(void){

	set_light(1);
	set_short("7th avenue east");
	set_long("You are walking eastwards along the 7th\n"+
		"avenue. The street starts to slope to the east\n"+
		"here. The avenue continues east and west.\n");
	add_exit("west", ROOMS + "7th_east1");
	add_exit("south", ROOMS + "boul6");
	add_exit("north", ROOMS + "nangels1");
	add_exit("east", ROOMS + "7th_east3");
}
