inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
    
 
    long_desc = 
        "You are walking along the Angels boulevard.\n"
        + "It continues to the north and the East street is\n"
        + "to the south.\n";
    dest_dir = 
        ({
        ROOM+"east_square3", "south",
        ROOM+"boul2", "north",
        });
}

