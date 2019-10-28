inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
 
    long_desc = 
        "You are walking along Angels boulevard.\n"
        + "It continues north and south. East you have the ARC studios.\n";
    dest_dir = ({
        ROOM+"s_boul3", "south",
        ROOM+"s_boul1", "north",
	/* "players/poldark/radio/room/radio1", "east", */        });
    items_arr = ({
          });
}
