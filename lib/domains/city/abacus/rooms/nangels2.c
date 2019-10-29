inherit "std/room";
#include "../area.h"

void setup(void) {
        set_outdoors(1);
        set_light(1);
        short_desc = "End of Angels";
 
        long_desc = 
               "This is the northern most end of Angels Boulevard.\n"
             + "A dirt road continues from here to the north.\n";
        dest_dir = ({
               ROOM+"dirt1","north",
               ROOM+"nangels1","south",
               });
        items_arr = ({
            ({"city","south"}),
                  "The ever expanding city is to the south.",
            ({"road","dirt road"}),
                  "A dirt road, it looks strangely well travelled.",
          });
}
