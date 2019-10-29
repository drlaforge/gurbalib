/* Wishbone 12/96 */


inherit "std/room";
#include "../area.h"

init() {
        ::init(); 
        add_action("southeast","southeast"); 
        }

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "West Street";
    
 
    set_long_f( 
	"This is West Street as it continues to the west. Off "+
        "to the east lies the middle of town. To the southeast you "+
	"see a park.\n");
    dest_dir = ({
        ROOM+"west2","west",
        ROOM+"west_streetend", "east",
        });
    items_arr = ({
              ({"west street","street"}),
              "The street you're on",
              ({"middle","town"}),
              "The main town of Abacus",
              "park",
              "A park off to the southeast.  It's entrance is to the east",
 	      ({"entrance","park entrance"}),
		"The entrance is to the east",
         });
}

int southeast(){
	write("You can't get into the park this way.\n"+
		"Try the entrance to the east.\n");
	return 1;
}
