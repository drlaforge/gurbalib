/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    
   set_outdoors(1);
   set_light(1);
   short_desc="Southern city docks";
 
   set_long_f(
	"The southern part of the old city docks. "+
	"To the east and west lie the vast warehouses, used to "+
	"store the incoming goods for the city. Long ago, just "+
	"about anything could be found inside, now they look deserted.\n");
   dest_dir = ({
	ROOM+"coast5","north",
	ROOM+"coast3","south",
	});
   items_arr = ({
	({"docks","city docks","old city docks"}),
	"Warehouses litter the docks here",
	({"warehouse","warehouses"}),"There seems to be no way in",
	});
}
