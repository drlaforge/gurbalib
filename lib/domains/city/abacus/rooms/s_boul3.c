inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
 
    long_desc = 
        "You are walking along Angels boulevard.\n"
        + "It continues north and south.\n";
    dest_dir = ({
        ROOM+"s_boul2", "north",
	ROOM+"s_boul4", "south",
        ROOM+"laser_shop", "west",
          "obj/auction/auction", "east",
        });
    items_arr = ({
          });
}

