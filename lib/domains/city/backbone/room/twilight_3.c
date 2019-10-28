
inherit "/std/room";
#include "../area.h"

void setup(){
    
    
   set_short("Twilight Lane");
   set_long_f("Here Twilight Lane comes to an abrupt halt thanks to a sturdy "+
      "barricade. The road continues to the south from here. To the north, you can "+
      "see the outlines of buildings, but you're not quite sure what they are.\n", 78);
   add_item(({"blockage","sturdy barricade","barricade"}), " [ Property of Torn Sky : Thru-traffic Restricted ] ");
   add_item(({ "building","outlines","outline","outlines of buildings","buildings", }),
      "You can't really see them too clearly - but they are buildings.");
   set_light(1);
   set_outdoors(1);
    
   add_exit("south", ROOM+"twilight_2");
   add_exit("west", ROOM+"convoy/westConvoy");
   add_exit("north", ROOM+"twilight_3", "#no_torn");
   add_item(({"lane","road","twilight lane","twilight",}), "The cracked pavement that you walk on is all that remains of this roadway.");
}

int no_torn(){
   write("You can not enter Torn Sky, it seems to be blocked off again.\n");
   return 1;
}


