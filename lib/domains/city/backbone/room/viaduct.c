/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
     
     

    set_outdoors(1); 
    set_light(1); 
    short_desc = "An old, broken viaduct.";
 
    set_long_f( 
	"This viaduct looks so old that you have a vague impression "+
	"that it will collapse under your feet. The ornate stonework "+
	"which must have been wonderful to see has completely "+
	"disappeared, and the surface is now just full of holes. "+
	"You can see the outline of the main city to the east.\n"); 
    dest_dir = ({
	ROOM+"west_street1","east",
	ROOM+"west_street2","west",
		});
    items_arr = ({
	({"stonework","ornate stonework","viaduct"}),
	"It must have been wonderfull, once.",
	({"surface","holes"}),"The surface is now full of holes.",
	({"outline","city"}),"You see the outlne of the city to the east.",
		});
}

