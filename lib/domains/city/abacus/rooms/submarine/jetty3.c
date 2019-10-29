inherit "std/room";
#include "../area.h"

void setup(void) {
 set_light(1);
 set_outdoors(1);
 short_desc = "a small jetty";
 set_long_f("You stand on a small jetty. To the east you see the ocean "+
           "which seems to expand out for miles and miles. On the horizon "+
           "you see what appears to be some sort of large building. There "+
           "is a small yard lying to the north.");

 items_arr = ({"jetty",
	"A small jetty that protrudes into the water.",
	"small jetty",
	"A small jetty that protrudes into the water.",
	"water",
	"You probably would not want to swim in it.",
	"ocean",
	"The ocean is a deep blue.",
	"horizon",
	"This is as far as you can see.",
	"large building",
	"You are too far away to really see what the building is.",
	"building",
	"You are too far away to really see what the building is.",
	"yard",
	"It's an empty yard.",
	"small yard",
	"It's an empty yard.",});
  dest_dir = ({
    ROOM+"coast9", "west",
    ROOM+"submarine/jetty2", "east", });
 }
