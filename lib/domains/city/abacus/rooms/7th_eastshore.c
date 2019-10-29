#include "../area.h"

inherit "/std/room/";

void setup(void){

	set_light(1);
	set_short("the shore");
	set_long("The 7th avenue comes to an end here at the\n"+
		"shore of the great Nukelake. The waves rolls\n"+
		"high to the east but the avenue continues\n"+
		"westwards.\n");
	add_exit("west", ROOMS + "7th_east6");
}
