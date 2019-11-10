#include "../area.h"

inherit STD_ROOM; 


void setup(){

	set_light(1);
	/*set_outdoors(1);
	set_dig(1);*/
	set_short("A street");
	set_long("You walk along the Eden street leading\n"+
		"to a newly rebuilded part of the city.\n"+
		"To the east you can see the Abacus Central Bank and to the west is the Money Exchange office.\n"+
		"The street continues to the north.\n");
  
	add_exit("south", ROOMS + "east_square1");
	add_exit("north", ROOMS + "eden2");
	add_exit("west", ROOMS + "mexroom");
	add_exit("east", "domains/city/abacus/bank/lobby");
   

}
