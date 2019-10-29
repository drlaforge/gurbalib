#include ROOM+".h"

void setup() {
   dest_dir = ({ROOM+"vill_track","west",
	   ROOM+"yard","north",
	   ROOM+"narr_alley","south",
	   ROOM+"square1","east"});
   set_short("Village road");
   set_long(
"A long road going east through the village. The road narrows to a " +
"track to the west. There is an alley to the north and the south.");
}
