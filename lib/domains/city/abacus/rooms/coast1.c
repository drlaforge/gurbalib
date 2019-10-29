
inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="South end of the coastal road";
 
   set_long_f(
        "This is the coastal road. It runs along the coast. "+
        "To the south it joins 5th Avenue, and further north "+
        "you can see the dock and warehouse facilities of the "+
        "city. They were very important before the war, now "+
        "they seem neglected. To the east is the ocean. It does "+
        "not look inviting.\n");
   dest_dir = ({
        ROOM+"coast2","north",
        ROOM+"5th_avenue8","south",
        });
   items_arr = ({
        ({"road","coastal road"}),"It runs along the coast",
        ({"avenue","5th","5th avenue"}),"It lies to the south",
        "coast","Where the land meets the ocean",
        ({"dock","warehouse","facilities"}),"The old docks and warehouses",
        "ocean","The ocean looks very polluted and unhealthy!",
        });
}