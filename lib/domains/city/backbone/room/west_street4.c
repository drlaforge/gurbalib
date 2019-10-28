/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
     

    set_outdoors(1); 
    set_light(1); 
    short_desc = "West Street";
 
    set_long_f(
	"You are on West Street. "+
	"The street continues to the west, and east into town. "+
	"Adams Street stretches away both north and south. "+
	"You can see a big intersection far to the west.\n");
    dest_dir = ({
	ROOM+"adam_street1","north",
	ROOM+"west_street3","east",
	ROOM+"west_streetend","west",
      ROOM+"southadams1","south",
		});
    items_arr = ({
	"street","Adams goes north, and West goes east/west",
	({"adams street","adam's street"}),"Adams Street goes north",
	"west street","West Street goes east and west",
	({"intersection","big intersection"}),"It is far to the west",
		});
}
