#include "../area.h"

inherit "std/room";

void setup(void) {
	
	set_light(1);
    set_short("intersection on West Street");
 
    set_long(
	"You're at an intersection on West Street. It leads east "+
	"into town, and west to the old suburbs. "+
	"There is a dark alley leading northwards to the Devil's "+
	"territory. There is also the park entrance to the south.\n");
    
	add_exit("north", ROOMS + "alley1");
	add_exit("south", "#my_park");
	add_exit("east", ROOMS + "west_street4");
	add_exit("west", ROOMS + "west3");

	add_item("west street","street","You're standing on it");
	add_item("intersection","An intersection on West Street");
	add_item("alley","dark alley", "The alley leads into the Devil's territory");
	add_item("park","entrance","park entrance", "The park lies to the south");
	add_item("territory","The territory of the Devil's gang");
}

int my_park()
	{
		write("The gate to the park is locked and you can't find a way to get around it");
		return 1;
	}