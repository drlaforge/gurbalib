/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
     

    set_outdoors(1); 
    set_light(1); 
    short_desc = "West Street nearing Central Square";
 
    set_long_f( 
	"The street you are standing on seems to have been a rather "+
	"well travelled and properous place in the distant past, but "+
	"you can tell that its days are over. The buildings on the edge "+
	"of the road look run down and deserted, and the road is in such "+
	"bad shape it is a wonder people can still walk on it. The old "+
	"HoloCorp building lies to the south, and is probably deserted too.\n");
    dest_dir = ({
	ROOM+"viaduct","east",
	ROOM+"west_street3","west",
	ROOM+"ind_street4","north",
		});
    items_arr = ({
	({"road","street"}),"A very run down street.",
	({"buildings","edge","building"}),"The buildings are deserted.",
	({"holocorp building","holocorp"}),"The HoloCorp building is probably deserted",
		});
}

