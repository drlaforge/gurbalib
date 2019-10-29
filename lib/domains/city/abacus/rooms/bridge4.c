/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */
/* Kal - Updated description to more accurately depict the mud - August '03 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Abacus Shoreline Bridge");
  set_long_f("You are standing on the bridge connects the mainland to the shore. "+
    "It starts to make a steep descent to the shore here, and the closer you "+
    "are to sea level, you hear the river rumble ever louder. The enviroment has "+
    "seemed angry ever since the war. The bridge descends further East towards "+
    "the shore, and climbs Westward to the mainland.\n");
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
  add_item(({"shore","island","peninsula","land","shoreline"}),
    "The shore is connected to the mainland by the bridge, and by an isthmus\n"+
    "further to the south. It serves as a break for the harsh current, and as\n"+
    "a platform for docking, as the former shipping district lies to the south.");
  add_item(({"mainland","city"}),
    "At the Eastern end of the bridge stands the city. Skyscrapers tower above\n"+
    "shanty towns and ruins, making the seawall look like a footnote. It's quite\n"+
    "a magnificent view.");
  add_sound(({"water","river","roar","rumble","rumbling"}),
    "The river rumbles and roars like an angry beast.");
  add_exit("east", ROOM+"bridge5");
  add_exit("west", ROOM+"bridge3");
   

}