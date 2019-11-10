inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "angels boulevard";
    
 
    long_desc = 
        "The boulevard ends here, connecting to\n"+
	"the 7th avenue. There are still a few machines\n"+
	"around, constructing new areas. You also see a sign,\n"+
	"pointing down along a broad stairway. The 7th avenue is\n"+
	"north from here and the boulevard continues south.\n";
    dest_dir = 
        ({
	ROOM+"7th_east2","north", 0,
        ROOM+"boul5","south", 0,
        });
    items_arr = ({"machines","The machines are used when building houses",
	      "&The machines sound awful.","@You feel the smell of oil "+
	      "and grease fill your nose.","sign","The sign is pointing"+
	      " down and says: Subway!",({"stairway","stairs"}),
	      "It's a long and broad set of stairs"});
}

init() {
  ::init();
  add_action("read","read");
}

read (str) {
  if (str != "sign")
    return 0;
  command ("exa sign",this_player());
  return 1;
}
