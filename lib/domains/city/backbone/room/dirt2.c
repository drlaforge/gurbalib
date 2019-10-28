inherit "std/room";
#include "../area.h"

void setup(void) {
        set_outdoors(1);
        set_light(1);
        short_desc = "Long dirt road.";
        long_desc = 
               "A long dirt road going north and south. To the north is the\nforest, and back to the south is the city.\n";
        dest_dir = ({
               ROOM+"swampedge","north",
               ROOM+"dirt1","south",
               });
        items_arr = ({
	     ({"swamp","forest"}),
                  "Dense growth of trees and plants, it looks kinda dark in there.",
            ({"city","south"}),
                  "The ever expanding city is to the south.",
            ({"road","dirt road","long dirt road"}),
                  "A dirt road, it looks strangely well travelled.",
          });
    }
