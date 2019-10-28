/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "West Street";
    
 
    set_long_f( 
        "You're standing on West Street. Off to the west the street "+
        "continues towards the old suburbs, and to the east it heads "+
	"back into the middle of town.\n");
    dest_dir = ({
        ROOM+"west1", "west",
        ROOM+"west3", "east",
        });
    items_arr = ({
              ({"west street","street"}),
		"The very street you're walking on",
              ({"middle","town"}),"The main town to the east",
	      ({"suburbs","old suburbs"}),"They lie to the west",
          });
}
