inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_light(1);
  set_outdoors(1);
  short_desc = "a very narrow and dark alley";
  long_desc =
    "The narrow alley ends here, before an opening\n"+
    "in one of the buildings.\n"+
    "The opening seems to be some sort of a store.\n";
  dest_dir = ({
    ROOM+"mroom","south",
    ROOM+"mroad2","west",
  });
  items_arr = ({
    "opening","The opening leads south, to some sort of store",
    "alley","It's extremely narrow, and there is almost no light at all",
    "buildings","They rise high above you and make you feel very small"
    });
}

init() {
  ::init();
  add_action("check","south");
}

check() {
  write("Sorry. The shop has been closed due to a fire.\n");
  return 1;
}

