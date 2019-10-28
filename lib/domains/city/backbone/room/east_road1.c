inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_outdoors(1);
  set_light(1);
  short_desc = "East Road";
  long_desc =
    "You're walking on something that used to be a great avenue.\n"+
    "Now the road looks more like a gravelled cemetary path.\n"+
    "Those lamp posts that are still working can barely light up the street.\n"+
    "The street continues east and west.\n";
  dest_dir =
    ({ROOM+"east_road2","east",
      ROOM+"south_alley8","west",
      });
  items = 
    ({"lamp posts","There aren't many that works, and those who do\nhave a hard time lighting this place up"
      });
}
