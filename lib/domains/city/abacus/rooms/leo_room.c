inherit "std/room";
#include "../area.h"

void setup(void) {
     
    set_outdoors(0);
    set_light(1);
    short_desc = "In a dark shaft";
    long_desc = 
         "You stand in a dark shaft.\n"
	+ "You see an opening in the floor,\n"
        + "leading to the elevator.\n"
	+ "There is a door to the east.\n"
        + "";
    items_arr = ({
	({"shaft","dark shaft"}),"It's a dark shaft!",
	"opening","The opening leads to the elevator.",
	"door","It's a door, leading east.",
	});
    dest_dir = ({
	ROOM+"leo_room2","east",
	});
}
