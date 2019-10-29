/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "West Street";
    
 
    set_long_f( 
        "This is a continuation of West Street.  There is not much out here. "+
	"Other that that, the road used to head out to some of the "+
	"more afluent suburbs of the city.\n");
    dest_dir = ({
        ROOM+"west_end2", "west",
        ROOM+"west2", "east",
        });
    items_arr = ({
              "street","The street you're walking on",
              "exit","An exit onto I-10",
              "i-10","Interstate 10 off to the west",
	      ({"suburbs","afluent suburbs"}),
		"They used to lie to the west of the city.",
          });
}

