inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_outdoors(1);
  set_light(1);
  short_desc = "East Road";
  long_desc = 
    "Standing on the road you barely see your own hands in the darkness.\n"+
    "There is almost no light at all at this place.\n"+
    "You can see some car wrecks lying beside the road.\n"+
    "On the side walk you also see some old stains of dried blood.\n";
  dest_dir = 
    ({ROOM+"metal","north",
      ROOM+"east_end","east",
      ROOM+"east_road1","west",
      });
  items_arr = ({
    "wrecks","It's just unusable car junk that has no value at all",
    "stains","Another victim of the unprovoked violence"
    });
}
