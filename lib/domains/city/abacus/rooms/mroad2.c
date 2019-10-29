inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_light(1);
  set_outdoors(1);
  short_desc = "a very narrow and dark alley";
  long_desc =
    "You're standing in an extremely narrow alley.\n"+
    "The buildings around you look very old and deserted.\n"+
    "Further east you see an opening in one of the buildings.\n";
  dest_dir = ({
    ROOM+"mroad3","east",
    ROOM+"mroad1","west",
  });
  items_arr = ({
    "alley","It's extremely narrow, and there is almost no light at all",
    "buildings","They rise high above you and make you feel very small"
    });
}
