#include "../area.h"

inherit STD_ROOM;

void setup(void) {
     
	/*set_outdoors(1);*/
    set_light(1);
    set_short("Angels boulevard");
    set_long("You are walking along the impressive Angels boulevard\n"
      + "which leads north from here. The East street\n"
      + "can be seen to the south.\n");
     
	set_exits(([
		"south" : ROOMS + "boul1",
         "north" : ROOMS + "boul3",
		]));
  }

