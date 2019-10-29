inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
 
    long_desc = 
        "You are walking along Angels boulevard.\n"
        + "It continues south. North you have East street.\n";
    dest_dir = ({
        ROOM+"s_boul2", "south",
        ROOM+"east_square3", "north",
        });
    items_arr = ({
          });
}

