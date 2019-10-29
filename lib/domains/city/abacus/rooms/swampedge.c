inherit "std/room";
#include "../area.h"

void setup(void) {
        set_outdoors(1);
        set_light(1);
        short_desc = "Road to swamp.";
        long_desc = 
               "The dirt road ends at the edge of what now you can tell\n"
             + "is a swamp.  The city can be seen far to the south.\n";
        dest_dir = ({
               ROOM+"swampe1","north",
               ROOM+"dirt2","south",
               });
        items_arr = ({
              "swamp",
                  "Dense growth of trees and plants that shroud the swamp in darkness.",
            ({"city","south"}),
                  "The ever expanding city is to the south.",
            ({"road","dirt road"}),
                  "A dirt road, it looks strangely well travelled.",
             ({"trees","plants"}),
                  "Trees and plants that make up the swamp.",
          });
}

