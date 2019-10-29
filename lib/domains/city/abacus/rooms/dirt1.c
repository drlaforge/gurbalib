inherit "std/room";
#include "../area.h"

void setup(void) {
        set_outdoors(1);
        set_light(1);
        short_desc = "Road to swamp.";
        long_desc = 
               "This is the beginning of a long dirt road leading \n"
              +"off towards what appears to be a forest from here.\n";
        dest_dir = ({
               ROOM+"dirt2","north",
               ROOM+"nangels2","south",
               });
        items_arr = ({
              "forest",
                  "Dense growth of trees and plants, it kinda hard to make out from here.",
            ({"city","south"}),
                  "The ever expanding city is to the south.",
            ({"road","dirt road","long dirt road"}),
                  "A dirt road, it looks strangely well travelled.",
          });
    }
