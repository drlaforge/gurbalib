/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="Southern city docks";
 
   set_long_f(
	"The southern end of the old city docks. "+
	"To the north there are many jetties and warehouses."+
	"You guess that this area was very important before the war. "+
	"Now it appears deserted. The ocean is to the east.\n");
   dest_dir = ({
	ROOM+"coast4","north",
	ROOM+"coast2","south",
	});
   items_arr = ({
	({"dock","warehouse","end","jetties","jetty","warehouses",
		"docks","southern end"}),
	"Warehouses and jetties litter the docks",
	"ocean","The ocean looks very polluted and unhealthy!",
	});
}
