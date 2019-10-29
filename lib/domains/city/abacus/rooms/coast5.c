/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="Warehouses on the docks";
 
   set_long_f(
	"The road swings east and south here, to go around a "+
	"vast warehouse. To the east you can see the ocean.\n");
   dest_dir = ({
	ROOM+"coast6","east",
	ROOM+"coast4","south",
	});
   items_arr = ({
	"ocean","It looks very big, and very wet",
	({"warehouse","vast warehouse"}),"There seems to be no way in",
	});
}
