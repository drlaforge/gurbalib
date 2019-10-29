inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_light(1);
  set_outdoors(1);
  short_desc = "a very narrow and dark alley";
  long_desc =
    "You're walking in a very narrow, dark alley.\n"+
    "The tall buildings around you almost seem to swallow you.\n"+
    "The alley makes an abrupt turn and continues eastwards.\n";
  dest_dir = ({
    ROOM+"mroad2","east",
    ROOM+"east_end","north",
  });
  items_arr = ({
    "alley","It's extremely narrow, and there is almost no light at all",
    "buildings","They rise high above you and make you feel very small"
    });
}
