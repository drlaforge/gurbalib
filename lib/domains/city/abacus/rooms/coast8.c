/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="Northern city docks";
 
   set_long_f(
	"This is the coastal road, running along the coast. "+
	"You are in the northern docks, where there are a number "+
	"of jetties designed for smaller ships and ferries. "+
	"The ocean to the east does not look pleasent.\n");
   dest_dir = ({
	ROOM+"coast9","north",
	ROOM+"coast7","south",
	});
   items_arr = ({
	({"road","coastal road"}),"It runs along the coast",
	"coast","Where the land meets the ocean",
	({"ship","ships","ferry","ferries"}),"Can't see any here",
	({"docks","jetties"}),"The city docks and jetties",
	"ocean","The ocean looks very polluted and unhealthy!",
	});
}
