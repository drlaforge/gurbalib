/* Wishbone 12/96 */

inherit "std/room";

#include "../area.h" 

void setup(void) {
    /*set_outdoors(1); */
    set_light(1); 
    set_short("An old, broken viaduct."); 
    set_long( 
		"This viaduct looks so old that you have a vague impression "+
		"that it will collapse under your feet. The ornate stonework "+
		"which must have been wonderful to see has completely "+
		"disappeared, and the surface is now just full of holes. "+
		"You can see the outline of the main city to the east.\n"); 
    set_exits((["east" : ROOMS + "west_street1",
				"west" : ROOMS+"west_street2",
			]));
    add_item("stonework","ornate stonework","viaduct","It must have been wonderfull, once.");
    add_item("surface","holes","The surface is now full of holes.");
    add_item("outline","city","You see the outline of the city to the east.");
}


