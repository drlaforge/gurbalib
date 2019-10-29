inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
    
 
    set_long_f( 
        "You are walking along the Angels Boulevard. "
        + "There are less skyscrapers to the north but "
        + "some large houses fill the area instead. "
	+ "The boulevard continues north and south. "
	+ "There is a yard to an old university to the east.\n");
    dest_dir = 
        ({
        ROOM+"boul5", "north",
	ROOM+"boul3", "south",
	"domains/Gangs/Hackers/room/yard","east",
        });
    items_arr = ({ "skyscrapers","They aren't as high and dusty as further south",
	       "houses","It looks like some rich people live in these area",
	       "university","It looks rather old, it seems to be still used"+
	       " in some way",
	       "yard","It's the yard in front of the university",
   });
}

