inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
    
 
    long_desc = 
        "You are walking along the impressive Angels boulevard\n"
      + "which leads north from here. The East street\n"
      + "can be seen to the south.\n";
    dest_dir = 
        ({
        ROOM+"boul1", "south",
        ROOM+"boul3", "north",
      });
  }

