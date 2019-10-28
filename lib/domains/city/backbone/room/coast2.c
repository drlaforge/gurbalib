/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="Southern coastal road";
 
   set_long_f(
	"This is the coastal road, running along the coast. "+
	"The docks and warehouses of the city lie to the north."+
	"They were a focus for incoming goods before the war, now "+
	"they appear deserted. To the east is the ocean. It does "+
	"not look inviting.\n");
   dest_dir = ({
	ROOM+"coast3","north",
	ROOM+"coast1","south",
	});
   items_arr = ({
	({"road","coastal road"}),"It runs along the coast",
	"coast","Where the land meets the ocean",
	({"dock","warehouse","north"}),
	"The old docks and warehouses, looking very neglected",
	"ocean","The ocean looks very polluted and unhealthy!",
	});
}
