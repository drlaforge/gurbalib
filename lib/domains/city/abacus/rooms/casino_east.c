
inherit "std/room";
#include "../area.h"

object ob;
void setup(void) {
     
  /* The blackjack is bugged: 
	- no casino i have been to scores a dealer win for a push
     Someone fix this one day.. - Wishbone

    ob = clone_object ("obj/blackjack");
    move_object (ob,this_object());
   */

    set_outdoors(0);
    set_light(1);
    short_desc = "In a casino at the black jack table";
    
    long_desc = 
        "You stand in a small room of the casino.\n"
       + "The only exit from the room leads south, but you stop\n"+
         "to consider a quick game before leaving.\n";
    dest_dir = 
        ({
        ROOM+"casino", "south",
        });
}

