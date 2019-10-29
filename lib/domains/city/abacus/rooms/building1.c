inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(0);
    set_light(1);
    short_desc = "in a building";
    
    long_desc = 
        "You stand in a building.\n"
        + "There is an opening to the west leading\n"
        + "back to the alley.\n";
    dest_dir = ({
        ROOM+"alley_04", "west",
        ROOM+"building2", "east",
        });
    items_arr = ({
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

