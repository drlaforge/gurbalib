inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the eastern edge of a large desolate wasteland. "+
	"There are high cliff walls running to the east that give "+
	"the impression that this wasteland is actually an immense blast crater. "+
	"A huge amount of rubble lies to the west, and you can make out an "+
	"oil rig to the north.\n");
  dest_dir = ({
	ROOM+"waste/land43","north",
	ROOM+"waste/land23","south",
       });
  items_arr = ({
	"edge","You are at the eastern edge",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls run north and east here",
	({"crater","blast crater"}),"This whole area is one large blast crater",
	({"rubble","building"}),"The rubble was once a building, long ago",
	({"rig","oil rig"}),"The oil rig lies to the north",
       });
 }
