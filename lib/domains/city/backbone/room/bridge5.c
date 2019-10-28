/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */
/* Kal - Updated description to more accurately depict the mud - August '03 */

#include <def.h>
    
inherit STD_ROOM;
#include "../area.h"


void setup(){

   
   
  set_light(2);
  set_outdoors(1);
  set_dig(1);
  set_short("East Street on the Shore");
  set_long_f("You stand at the end of the Shoreline Bridge, towards the Northern "+
    "end of the shore. Just looking at the bridge, the solid ground "+
    "feels comforting. East Street continues East to the ocean, and West "+
    "to the mainland, via the bridge.\n");
    add_item(({"bridge","shoreline bridge","abacus shoreline bridge"}),
    "A massive bridge of steel and concrete, crossing the river. However\n"+
    "it looks fragile - A victim of the nuclear war. Someone decided to reinforce\n"+
    "it recently, as you can see steel beams haphazardly welded to the structure.");
  add_item(({"seawall","sea wall"}),
    "You can't see it very well from here, but it looks like a pedastal on\n"+
    "which the city stands.");
  add_item(({"river","ocean","basin","sewage","water","sea"}),
    "You look over the side of the bridge at the river, and notice it isn't\n"+
    "really a river at all. It's an inlet from the sea, which you can see\n"+
    "further to the north. As you look closer, you notice a river does flow\n"+
    "into it - an underground river of sewage, forming a large basin between\n"+
    "the sea wall and the peninsula.");
  add_item(({"shore","island","peninsula","land","ground","shoreline"}),
    "The shore is a peninsula, connected in the south to the mainland by an isthmus,\n"+
    "and by the bridge here. Docks dot the land, running on the ocean side to the\n"+
    "old warehouses. Mostly abandonded save for the docks, though some of the more\n"+
    "eccentric folk have taken up residence in the mansions which still stand.");
  add_item("mansions",
    "Once prime real estate overlooking the ocean, mansions were built here for\n"+
    "the city's elite. The're rather hazardous now, prone to natural dissasters\n"+
    "being so close to the sea.");
  add_item(({"mainland","city"}),
    "At the Eastern end of the bridge stands the city. Skyscrapers tower above\n"+
    "shanty towns and ruins, making the seawall look like a footnote. It's quite\n"+
    "a magnificent view.");
  add_object("/domains/required/objects/bag", 1);
  add_exit("west", ROOM+"bridge4");
  add_exit("east", ROOM+"east_street1");
   

}