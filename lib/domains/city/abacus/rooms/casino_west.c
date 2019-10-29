
inherit "std/room";
#include "../area.h"
object ob;

void setup(void) {
     
  /*
   ob = clone_object ("obj/roulette");
   move_object (ob,this_object());
  */

    set_outdoors(0);
    set_light(1);
    short_desc = "In the roulette room";
    
    long_desc = 
        "You stand in a quite small room\n"
        + "in the casino. There is nothing\n"
        + "much of interest in here.\n";
    dest_dir = 
        ({
        ROOM+"casino", "north",
        });
}

