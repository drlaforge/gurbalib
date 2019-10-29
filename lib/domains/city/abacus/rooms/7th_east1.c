#include "../area.h"

inherit "/std/room";

void setup(void){

	set_light(1);
	set_short("7th avenue east");
	set_long("You stand on the 7th avenue east from the Eden street.\n"+
		"There is a large crossing to the west and the \n"+
		"avenue continues east.\n");
	add_exit("west", ROOMS + "eden5");
	add_exit("east", ROOMS + "7th_east2");

}
