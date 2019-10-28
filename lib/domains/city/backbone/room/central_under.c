 
#include <time.h>

inherit "std/room";
#include "../area.h"
#include <tune.h>
object lockers;

init () {
  ::init();
   add_action ("south","south");
  if(this_player()->query_level() >= ROOKIE_LEVEL)
    write("DO NOT fresh this room! - Wishbone\n");
}
void setup(void) {

/* Lockers added by Wishbone - 16APR99 */
     if(!present("lockers",this_object())){
    lockers=clone_object("obj/lockers/lockers");
    move_object(lockers,this_object());
   }
  set_outdoors(0);
  set_light(1);
  short_desc = "Central Square subway station";  
  set_long_f("You are standing underneath Central Square. It seems "+ 
	"like this place hasn't been cleaned for decades. Grime covers "+
	"the walls everywhere, and you can see some foul looking puddles "+
	"in some of the corners. Every now and then, you can hear a "+
	"rumble from the subway station to to west. There is a staircase "+ 
	"leading upwards to the city above.\n"); 
  dest_dir = 
    ({
	ROOM+"central_under2","west",
	ROOM+"central_square","up",
    });
  items_arr = ({
	"walls","They are covered with a brown coloured	grime.",
	"puddles","They look like very stale water.",
	"corners","The corners have puddles.",
	"staircase","It leads up out of here.",
	"grime","A brownish grime covers the walls.",
        });
}

south() {
  write("You are about to walk off the platform, but you change your mind.\n"); 
   return 1;  
}

