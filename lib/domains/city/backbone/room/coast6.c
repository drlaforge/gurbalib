/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="City docks";
 
   set_long_f(
	"The road heads west here, around a vast warehouse. "+
	"More of the docks and jetties lie to the north. "+
	"Some of them appear to still be in use. Perhaps it is "+
	"possible to catch a boat to somewhere else. "+
	"The ocean to the east does not look pleasant.\n");
   dest_dir = ({
	ROOM+"coast7","north",
	ROOM+"coast5","west",
	});
   items_arr = ({
	({"road","coastal road"}),"It runs along the coast",
	"coast","Where the land meets the ocean",
	({"warehouse","vast warehouse"}),
	"It is just a vast warehouse. There is no way in",
	({"docks","jetties"}),"More of the city docks and jetties",
	"ocean","The ocean looks very polluted and unhealthy!",
	});
}
