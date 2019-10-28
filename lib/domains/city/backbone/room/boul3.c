inherit "std/room";
#include "../area.h"
object ob;

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
    
 
    long_desc = 
        "You are walking along the Angels boulevard.\n"
        + "It splits up in a small crossing here. To the\n"
        + "west there is a dark and gloomy alley among the\n"
        + "skyscrapers.\n";
    dest_dir = 
        ({
        ROOM+"boul2", "south",0,
        ROOM+"boul4", "north",0,
        ROOM+"darkalley1", "west", 0,
        });
    items_arr = ({"skyscrapers","What do skyscrapers use to look like ?\n"+
		"They are high and impressing",
	      "alley","Go there to see how it looks like"
	      });
}

