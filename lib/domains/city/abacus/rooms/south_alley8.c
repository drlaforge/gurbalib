inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_outdoors(1);
  set_light(1);
  short_desc = "a dark alley crossing";
  long_desc = 
    "You've come to the end of the gloomy alley.\n"+
    "It makes an abrupt end here and a badly maintained road takes over.\n"+
    "The road goes east and west from here.\n";
  dest_dir =
    ({ROOM+"east_road1","east",
      ROOM+"south_alley7","north",
      });
  items_arr = ({"road","It hasn't been maintained for decades"
	    });
}
