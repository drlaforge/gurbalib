/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
    /*set_outdoors(1); */
    set_light(1); 
    set_short("West Street nearing Central Square");
    set_long( 
	"The street you are standing on seems to have been a rather "+
	"well travelled and properous place in the distant past, but "+
	"you can tell that its days are over. The buildings on the edge "+
	"of the road look run down and deserted, and the road is in such "+
	"bad shape it is a wonder people can still walk on it. The old "+
	"HoloCorp building lies to the south, and is probably deserted too.\n");
    set_exits(([
	"east" : ROOMS+"viaduct",
	"west" : ROOMS+"west_street3",
	"north" : ROOMS+"ind_street4",
		]));
    add_item("road","street","A very run down street.");
    add_item("buildings","edge","building","The buildings are deserted.");
    add_item("holocorp building","holocorp","The HoloCorp building is probably deserted");
}


