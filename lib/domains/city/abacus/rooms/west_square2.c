/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"
object cgdroid;
static int cgdroided;

void setup(void) {
     cgdroided=0;
     

/*
    add_object("/players/mycon/gifts/bucket",1);
*/

    /* Added for the interesting little burying droid..  Cygnus (10/2k) 
    if(!cgdroided)
      {
	cgdroid = clone_object("/players/cygnus/work/cgdroid");
	move_object(cgdroid, this_object());
	cgdroided = 1;
      }
*/
    set_short("approaching Central Square"); 
    set_long(
"The road is in much better condition than the ones further to the west, "+
"but it still has many potholes dotting the place. It starts to widen to "+
"the east, probably so that it can merge with the square in that direction. "+
"You can see deserted buildings around you.\n");
    set_light(1);
    /*set_outdoors(1); */
    add_item("road","It is covered with potholes.");
    add_item("buildings","building","deserted buildings","They look deserted and hardly worth exploring.");
    add_item("potholes","pothole","They are not that deep, but may make driving a nightmare.");

    set_exits((["east" : ROOMS+"west_square1.c",
        "west" : ROOMS+"west_street1.c",
        "south" : ROOMS+"south_alley1.c",
        "north" : "domains/docwagon/miniarea/rooms/entrance"]));
}

