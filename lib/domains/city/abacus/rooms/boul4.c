#include "../area.h"

inherit STD_ROOM;

void setup(void) {
    
	/*set_outdoors(1);*/
    set_light(1);
    set_short("Angels boulevard");
	set_long("You are walking along the Angels Boulevard. "
        + "There are less skyscrapers to the north but "
        + "some large houses fill the area instead. "
		+ "The boulevard continues north and south. "
		+ "There is a yard to an old university to the east.\n");
    set_exits(([
    "north" : ROOMS + "boul5",
	"south" : ROOMS + "boul3",
	"east" : "domains/Gangs/Hackers/room/yard",
		]));
		
    add_item("skyscrapers","They aren't as high and dusty as further south");
	add_item("houses","It looks like some rich people live in these area");
	add_item("university","It looks rather old, it seems to be still used"+
	       " in some way");
	add_item("yard","It's the yard in front of the university");
}

