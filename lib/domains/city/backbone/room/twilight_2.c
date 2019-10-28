
inherit "/std/room";
#include "../area.h"

void setup(){
    
    
   set_short("Twilight Lane");
   set_long_f("More of the same deserted road, it continues north and south from here. "+
      "To the north you see the faint outlines of buildings.\n", 78);
   add_item("desert", "It is a desert. Not much you can say about that.");
   add_item(({ "building","outlines","outline","outlines of buildings","buildings", }),
      "You can't really see them too clearly.");
   set_light(1);
   set_outdoors(1);
    
   add_exit("south", ROOM+"twilight_1");
   add_exit("north", ROOM+"twilight_3");
   add_item(({"lane","road","twilight lane","twilight",}), "The cracked pavement that you walk on is all that remains of this roadway.");
}

