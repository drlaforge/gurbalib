#include "../area.h"
inherit STD_ROOM;

object ob;

void setup(void) {
     
    /*set_outdoors(1);*/
    set_light(1);
    set_short("Angels boulevard");
    set_long("You are walking along the Angels boulevard.\n"
        + "It splits up in a small crossing here. To the\n"
        + "west there is a dark and gloomy alley among the\n"
        + "skyscrapers.\n");
    set_exits(([
        "south" : ROOMS + "boul2",
        "north" : ROOMS + "boul4",
        "west" : ROOMS + "darkalley1",
        ]));
		
    add_item("skyscrapers","What do skyscrapers use to look like ?\n"+
		"They are high and impressing");
	add_item("alley","Go there to see how it looks like");
}

