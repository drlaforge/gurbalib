inherit "std/room";
#include "../area.h"

init () {
  ::init();
  add_action ("west","west");
}

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "in an alley";
    
    long_desc = 
"You stand in an alley with east road to the north.\n"+
"The alley continues southwards. There is a sign saying\n"+
"'STOCKMARKET' pointing to the west, but a smaller sign\n"+
"reads 'Closed'.\n";

    dest_dir = ({
        ROOM+"east_square1", "north",
        ROOM+"alley_02","south",
/*         "/players/thorwald/room/stock","west", */    });
    items_arr = ({
      "sign","The sign is pointing westwards, into a smaller alley",
      "alley","The alley is dark and gloomy.\nYou wonder what people might live there",
          });
}

int south () {
  write ("A bomb raid has stopped the path southwards.\n");
  write ("Come back later!\n");
  return 1;
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

int query_roommaker_access() {  return 1;  }

int west() {
  return 0;
  write ("The stockmarket is temporarily closed.\n");
  return 1;
}
