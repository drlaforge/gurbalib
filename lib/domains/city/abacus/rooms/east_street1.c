/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */
/* Kal - Updated description to more accurately depict the mud - August '03 */

#include <def.h> 
inherit STD_ROOM;
#include "../area.h"   

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("End of East Street");
  set_long_f("East Street ends here.\n"+
    "It sort of melts into the rocks and mutant plants, fading away "+
    "into the ocean. A small coastal road starts here and runs to "+
    "the south. East Street runs back to the city's core.\n");
  add_item(({"ocean","plants","mutant plants","rocks","street"}),
    "East Street fades into the ocean, rocks and plant life dotting\n"+
    "its surfice. It once continued further, before the ice caps melted.");
  add_item(({"mainland","city"}),
    "At the Eastern end of the bridge stands the city. Skyscrapers tower above\n"+
    "shanty towns and ruins, making the seawall look like a footnote. It's quite\n"+
    "a magnificent view.");
  add_item(({"seawall","sea wall"}),
    "You can't see it very well from here, but it looks like a pedastal on\n"+
    "which the city stands.");
  add_item("bridge","The bridge lies to the east, connecting this shore to the mainland.");
  add_exit("west", ROOM+"bridge5");
  add_exit("south", ROOM+"coast9");
}