inherit "std/room";
#include "../area.h"

void setup(void) {
        set_outdoors(1);
        set_light(1);
        short_desc = "End of Angels";
 
        long_desc = 
               "You are standing on the northern part of Angels.  To\n"
             + "the west is a construction site, and to the south\n"
             + "Angels Boulevard continues.\n";
        dest_dir = ({
               ROOM+"nangels2","north",0,
               ROOM+"7th_east2","south","#mysouth",
               ROOM+"building","west",0,
               });
        items_arr = ({
            ({"city","south"}),
                  "The ever expanding city is to the south.",
            ({"road","dirt road"}),
                  "A dirt road, it looks strangely well travelled.",
            ({"site","construction site"}),
                    "It looks like some sort of major construction project.",
          });
}

int mysouth() {
  if(this_player()->query_npc())
    return 1;
}

