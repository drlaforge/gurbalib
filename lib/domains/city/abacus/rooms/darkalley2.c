inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "An alley";
    
    long_desc = 
        "The alley gets even darker now. This seems like \n"
        + "a place where the criminals and such people\n"
        + "use to hang around. There is a small gloomy bar to the\n"
        + "north which has a flashing neon sign above the door.\n"
        + "To the south you see the newly opened repair\n"
	+ "shop for weapons.\n";
    dest_dir = 
        ({
        ROOM+"darkalley3", "west",0,
        ROOM+"repair", "south","#test_if_open",
        ROOM+"darkalley1", "east",0,
        ROOM+"alleybar", "north",0,
        });
    items_arr = ({"sign","A really cool sign. It says: Buddy's Bar!",
              "bar","It's small and gloomy bar, but it still look cozy in a way",
              "shop","Go there to repair your weapons"
            });
}

test_if_open ()
{
    if ("players/bigfoot/alley/repair"->query_open())
        return 0;
    write ("The repairment shop isn't open at the moment.\n");
    return 1;
}
