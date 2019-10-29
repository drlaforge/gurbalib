/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="Northern city docks";
 
   set_long_f(
	"This is the northern end of the coastal road, which "+
	"runs along the coast. Around here there are a number "+
	"of jetties designed for smaller ships and ferries. "+
	"The warehouses lie to the south. "+
	"The ocean to the east does not look pleasant.\n");
   dest_dir = ({
	ROOM+"east_street1","north",
	ROOM+"coast8","south",
        ROOM+"submarine/jetty3","east",
	});
   items_arr = ({
	({"road","coastal road"}),"It runs along the coast",
	"coast","Where the land meets the ocean",
	({"ship","ships","ferry","ferries"}),"Can't see any here",
	({"docks","jetties"}),"The city docks and jetties",
	"ocean","The ocean looks very polluted and unhealthy!",
	"warehouses","They lie to the south",
	});
}
