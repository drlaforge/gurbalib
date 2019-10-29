/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
    /*set_outdoors(1); */
    set_light(1); 
    set_short("West Street");
    set_long(
	"You are on West Street. "+
	"The street continues to the west, and east into town. "+
	"Adams Street stretches away both north and south. "+
	"You can see a big intersection far to the west.\n");
    set_exits((["north" : ROOMS+"adam_street1",
	"east" : ROOMS+"west_street3",
	"west" : ROOMS+"west_streetend",
      "south" : ROOMS+"southadams1"]));
    add_item("street","Adams goes north, and West goes east/west");
	add_item("adams street","adam's street","Adams Street goes north");
	add_item("west street","West Street goes east and west");
	add_item("intersection","big intersection","It is far to the west");
}

