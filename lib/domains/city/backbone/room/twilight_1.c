
inherit "/std/room";
#include "../area.h"

void setup(){
    
    
   set_short("Twilight Lane");
   set_long_f("This cracked old pavement is all that remains of Twilight Lane. "+
      "Looking to the north you see more of the same deserted road. To the south you "+
      "see West Street, which leads back into the city.\n", 78);
   set_light(1);
   set_outdoors(1);
    
   add_exit("south", ROOM+"west_end2");
   add_exit("north", ROOM+"twilight_2");
   add_item(({"west street", "street"}), "It is to the south of here.");
   add_item(({"lane","road","roadway","twilight lane","twilight",}), "The cracked pavement that you walk on is all that remains of this roadway.");
}

