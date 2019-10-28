
inherit "std/room";
#include "../area.h"

void setup(void) {
     
     

    set_outdoors(1);
    set_light(1);
    short_desc = "A alley";
    
    long_desc = 
        "You are in a very narrow and gloomy alley.\n"
        + "Further west the alley seems come to a deadend.\n"
        + "There is a gun repair shop to the north.\n";
    dest_dir = 
        ({
        ROOM+"darkalley2", "east",
        ROOM+"darkalley4", "west",
        ROOM+"gun_rep", "north",
        });
}
