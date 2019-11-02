#include "../area.h"

inherit "std/room";

void setup(void) {
	
	set_short("in an alley");
    
    set_long("You stand in an alley with east road to the north.\n"+
		"The alley continues southwards. There is a sign saying\n"+
		"'STOCKMARKET' pointing to the west, but a smaller sign\n"+
		"reads 'Closed'.\n");

    add_exit("north", ROOMS + "east_square1");
	add_exit("south", ROOMS + "alley_02");
	add_exit("west", "#my_west");
/*         "/players/thorwald/room/stock","west", */ 
    add_item("sign","The sign is pointing westwards, into a smaller alley");
	add_item("alley","The alley is dark and gloomy.\nYou wonder what people might live there");
}


int my_west() {
  write ("The stockmarket is temporarily closed.\n");
  return 1;
}
