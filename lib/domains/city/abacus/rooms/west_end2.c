/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(0);
    set_light(1);
    short_desc = "end of West Street";
    
 
    set_long_f(
        "This is the end of West Street. Far off to the east you see the "+
        "town. You see Twilight Lane stretching out to the north. Also you "+
        "see a large sign to the south of here. You might want to read it.\n");
    dest_dir = ({
	ROOM+"twilight_1.c", "north",
        ROOM+"west1", "east",
        });
    items_arr = ({
              "street",
              "The street you're standing on",
	      "sign",
		"A large sign to the south of here you should read",
              "city",
              "The main city of Abacus",
          });
}

init()
{
 ::init();
 add_action("read_it","read");
}

int read_it(string str)
{
 if(str=="sign")
  {
   write("The sign is too far away to read - go south to see it!\n");
   return 1;
  }
 return 0;
}
