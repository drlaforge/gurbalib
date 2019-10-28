
inherit "std/room";
#include "../area.h"

void setup(void) {
  set_outdoors(1);
  set_light(1);
  short_desc = "a dark alley";
  long_desc="The dark alley end here.\n"+
            "The walls rise mightily above you and you feel very small.\n"+
            "The smell of rotten meat is less intense now but you can\n"+
            "still get a strong whiff of it.\n";
  dest_dir=({
             ROOM+"alley2","east",
	   });
  items_arr=({
         "walls","The walls is made of dark-gray concrete. Some pieces have"+
           " fallen off\nand the red stones under those can be seen"
	   });
  add_smell("meat","The smell of the rotten meat makes you sick.\n");
  add_smell("rotten meat","The smell of rotten meat makes you sick.");
}
