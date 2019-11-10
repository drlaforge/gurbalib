#include "../area.h"

inherit STD_ROOM; 

void setup(void) {
     
    /*set_outdoors(1);*/
    set_light(1);
    set_short("Angels boulevard");
    set_long("You are walking along the Angels boulevard.\n"
        + "It continues to the north and the East street is\n"
        + "to the south.\n");
    
	set_exits((["south" : ROOMS + "east_square3",
				"north" : ROOMS + "boul2",
				]));
}

