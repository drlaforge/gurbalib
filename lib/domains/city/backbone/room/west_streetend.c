/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
     

    set_outdoors(1); 
    set_light(1); 
    short_desc = "intersection on West Street";
 
    set_long_f(
	"You're at an intersection on West Street. It leads east "+
	"into town, and west to the old suburbs. "+
	"There is a dark alley leading northwards to the Devil's "+
	"territory. There is also the park entrance to the south.\n");
    dest_dir = ({
	ROOM+"alley1","north",
	ROOM+"park/park0","south",
	ROOM+"west_street4","east",
       ROOM+"west3","west",
		});
    items_arr = ({
	({"west street","street"}),"You're standing on it",
	"intersection","An intersection on West Street",
	({"alley","dark alley"}),
	"The alley leads into the Devil's territory",
	({"park","entrance","park entrance"}),
	"The park lies to the south",
	"territory","The territory of the Devil's gang",
		});
}
