inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the northern edge of a large desolate wasteland. "+
	"There are high cliff walls blocking the way north and a vast "+
	"quantity of rubble blocking the south. To the east there "+
	"appears to be the conture of an oil rig.\n");
  dest_dir = ({
	ROOM+"waste/land41","west",
	ROOM+"waste/land43","east",
       });
  items_arr = ({
	"edge","You are at the northern edge of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls run west and east here",
	({"building","rubble"}),"Lots of rubble. It may have been a building, once",
	({"rig","oil rig"}),"The oil rig lies to the east",
       });
 }
