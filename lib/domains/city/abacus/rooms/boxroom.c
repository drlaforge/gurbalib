
inherit "std/room";
#include "../area.h"

void setup(void) {
  if (!present ("drunkard",this_object())) { move_object(clone_object ("obj/monsters/sleeping"),this_object()); }
     

    set_outdoors(0);
    set_light(1);
    short_desc = "in a large paper box!";
    
    long_desc = 
        "You \"stand\" in a large paper box.\n"+
	  "";
    dest_dir = ({
        ROOM+"alley_05", "out",
        });
    items_arr = ({
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

